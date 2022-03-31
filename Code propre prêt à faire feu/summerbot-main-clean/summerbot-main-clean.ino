
// Bibliothèques générales :
#include <Arduino.h>
#include <Servo.h>


// Les protocoles:

#include "src/protocols/trajetSummer.h"
#include "src/protocols/trajetWinter.h"


// Les capteurs :

#include "src/summerbot-sensormanager/SensorManager.h"

// Le code pour les déplacement et l'ia:
#include "src/summerbot-motionbase/MotionBase.h"
#include "ia.hpp"

// Les variables constantes pour faciliter le code :
#include "pinout.h"

//Les actionneurs :
#include "src/summerbot-actionneurs/summerbot-actionneurs.hpp"
#include "src/summerbot-actionneurs/simple-crane.hpp"
#include "modules.hpp"


//================= PANNEAU DE CONFIGURATION (1) ================================//
//                  Ceci est à changer chaque année                              //
//              Tout ne sera peut être pas à changer                             //
//      mais il faut au moins être au courant de ces paramètres                  //
//                                                                               //
// 1) Les paramètres du match ---------------------------------------------------//

#define MATCHLENGHT 100000 //longueur du match en millisec                       //


// notre point de départ en repérage absolu-> Créez vous un repère vous même !   //
//(utile si on veut vérifier notre trajectoire plus tard)                        //

#define START_X 100 // largeur                                                   //
#define START_Y (isGreenSide?2900:100)// longueur                                //
#define START_A (isGreenSide?-90:90)// angle                                     //

// 2) Les capteurs --------------------------------------------------------------//
// Distance de détection des capteurs                                            //
#define DISTANCE_THRESHOLD_MOVING_FORWARD 250 // devant                          //
#define DISTANCE_THRESHOLD_MOVING_BACKWARD 700 // derrière                       //

long collisionStart;
bool collisionPossible = false;
bool timeLimitDisplayed = false;
#define DETECTION_THRESHOLD 300 // en milliseconde

// Création du pointeur qui ira pointer sur l'objet                              //
SensorManager *sensorManager = NULL;

// code de détection de collision sur le point de se produire                    //
// (les capteurs repèrent quelque chose en dessous de la limite demandée)        //
//Insérer dans le if le code de detection de collision                           //

bool collisionDetected(){ 
  if(
(analogRead(IRS1)-DISTANCE_THRESHOLD_MOVING_FORWARD>0) ||
(analogRead(IRS2)-DISTANCE_THRESHOLD_MOVING_FORWARD>0) || // voilà le code en    //
(analogRead(IRS3)-DISTANCE_THRESHOLD_MOVING_FORWARD>0) || //place pour le moment //
(analogRead(IRS4)-DISTANCE_THRESHOLD_MOVING_FORWARD>0) ||
(analogRead(IRS5)-DISTANCE_THRESHOLD_MOVING_FORWARD>0) 

  ){
    return true;
  }else{
  return false;
  }
}

// 3) Les moteurs (déplacement) -------------------------------------------------//
// ATTENTION les moteurs qui servent actuellement sont des moteurs pas à pas     //
// il fonctionnent comme des servomoteurs.                                       //
// Ils sont lents mais n'ont pas besoin d'asservissement                         //

//                              A NE PAS CHANGER !!!                             //
//                         (Sauf si changement de moteur)                        //

#define STEPS_PER_REV 200 // pour un tour de roue, le moteur avance de 200 crans //

// Préparation de la base roulante                                               //
long startTime;
IntervalTimer motionTimer;
DualDRV8825* dd; //on crée l'objet moteur                                        //
MotionBase *mb; // on crée l'objet motion base                                   //

// Le code executé par le timer. Fonctionnement des moteurs                      //
void motionLoop() {
  mb->update();
}

// 4) Les servomoteurs (actionneurs) --------------------------------------------//
// on crée ici les objet de type Servo                                           //
// exemple syntaxe : Servo servopince;                                           //

Servo servopanique;
Servo servobalai;

// 5) Préparation de l'IA -------------------------------------------------------//
IA *ia;

//===============================================================================//


void setup () {

  //===================== PANNEAU DE LANCEMENT (2) ==============================//
  // à cette étape on va mettre le système en route,                             //
  //on dit quel objet info est relié à quel composant élec, on initialise        //
  //puis on dit que on est prêts à faire feu ^^                                  //

  // 0) Démarrage de la carte ---------------------------------------------------//
  //Serial (initialisation de l'usb, entre autre)                                //
  Serial.begin(9600);
  delay(2000);
  Serial.println("Teensy started");

  // 1) Paramètres du match -----------------------------------------------------//

  // Un pin qu'on relie ou pas à la masse pour savoir le coté soit par un fil 
  // ou un interrupteur en fonction de si vous êtes ou pas dans la dèche
  pinMode(SIDE, INPUT_PULLUP);
  // On regarde la position initiale du robot (quel côté)
  int isGreenSide = digitalRead(SIDE);


  // 2) Les capteurs -------------------------------------------------------------//
  pinMode(DIST_BACK_LEFT, INPUT_PULLUP);// demander à LM
  pinMode(DIST_BACK_RIGHT, INPUT_PULLUP);

    // capteurs SHARP
  sensorManager = new SensorManager();
  sensorManager->registerNewSensor(IRS2, SHARP);
  sensorManager->registerNewSensor(IRS3, SHARP);
  sensorManager->registerNewSensor(IRS1, SHARP);
  sensorManager->registerNewSensor(IRS4, SHARP);
  sensorManager->registerNewSensor(IRS5, SHARP);

  

 // 3) Les moteurs -- -------------------------------------------------------------//

  // on renseigne les paramètres des moteurs :                                     //       
  //steps per rev,left dir pin, left step pin, right dir pin,                      //
  // right step pin, mode pin 0, mode pin 1, mode pin 2                            //
  dd = new DualDRV8825(200, 32, 30, 31, 29, 26, 25, 24);

  // on initialise la motionbase. Les paramètres :                                 //
  //motors, wheel radius, robot radius, x, y, a                                    //
  mb = new MotionBase(dd, 114 / 2.0, 169.5 / 2.0 );

  // on informe la base roulante de sa position de départ                          //
  mb->setPosition(START_X,START_Y,START_A);

  //Timers: pour les moteurs                                                       //
  motionTimer.begin(motionLoop, 100); // 10kHz (100 is the period in microS)       //
  motionTimer.priority(1); //slightly above normal                                 //

 // 4) Les servomoteurs------------------------------------------------------------//

  servopanique.attach(SERVO4);
  servobalai.attach(SERVO1);

  // à changer quand on aura tout branché !
  //Modules::simplecrane= new SimpleCrane(SERVO4,SERVO2);


  // 5) AI -----------------------------------------------------------------------//

  ia = new IA(mb);
  // On donne les protocoles à l'IA :
  //syntaxe : ia->addProtocol(new TestProtocol(PRIORITY_MEDIUM));
  ia->addProtocol(new TrajetSummer(PRIORITY_MEDIUM));//premier protocole de 2020  //
  //ia->addProtocol(new TrajetWinter(PRIORITY_MEDIUM));//second protocole de 2020 //

  // On crée des valeurs au pif, 
  //les protocoles peuvent les utiliser pour communiquer entre eux
  // syntaxe : ia->setFlag("nom du Flag", valeur du flag);

  ia->setFlag("isGreenSide", isGreenSide);//utile !
  
  // 6) lancement du robot à proprement dit ---------------------------------------//

  // Le pin du starter
  pinMode(STARTER, INPUT_PULLUP);

  //Starter & Simulator
  //on boucle en attendant que le starter soit mis
  Serial.println("Waiting starter...");
  while(digitalRead(STARTER)) delay(100);
  Serial.println("Starter ready!");

  // puis enlevé ^^
  delay(1000);// on doit faire minimum une pause de 1 sec avant de l'enlever
  while(!digitalRead(STARTER)) delay(100);
  Serial.println("Starting!");

  //start time
  startTime = millis();

  ia->activate();
  Serial.println("AI activated!");
  servobalai.write(180);
}


void loop () {
  /**
   * Pour éviter que des reflets qui dure 10ms ne donne des movements saccadés
   * au robot, on attends d'avoir détecté un obstacle pendant une fraction de
   * seconde avant de s'arréter
   */
    if (collisionDetected()){
      collisionPossible = true;
      //afichage
      Serial.println("Adversaire détecté");
      Serial.println((String)analogRead(IRS2)+","+
                    (String)analogRead(IRS3)+","+
                    (String)analogRead(IRS4)+","+
                    (String)analogRead(IRS5)+","+
                    (String)analogRead(IRS1));
      delay(50);
    }
    else{
      collisionPossible = false;
      collisionStart = millis();
      //lever de drapeau 2020 les 10 sernières secondes
      if (((millis() - startTime) >= MATCHLENGHT-10)){
        servopanique.write(180);
      }
    }
 
   /* Si fin du match ou detection de collision*/
   
  if (((millis() - startTime) >= MATCHLENGHT) ||
    (collisionPossible && (millis()-collisionStart)>DETECTION_THRESHOLD)){
    mb->pause();
    return;
  }

  // si tout va bien
  mb->resume();
  ia->update();
}
