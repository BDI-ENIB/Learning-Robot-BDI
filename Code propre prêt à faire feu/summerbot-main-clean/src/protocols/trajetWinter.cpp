#include "trajetWinter.h"
#include <Arduino.h>// fonctions de base Arduino

#include "../../ia.hpp"

//#include "../../modules.hpp"


void TrajetWinter::update(IA *ia){ //execute the next action of this protocol

  switch(state){
    case 0:
    if(initialPlacement == true){//330,750

    }
    break;
    case 1:
    ia->mb->rotate(PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 2:
    ia->mb->translate(680);
    break;
    case 3:
    ia->mb->rotate(-PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 4:
    ia->mb->translate(550);
    break;
    case 5:
    ia->mb->translate(10); //les pinces prennent le globlet rouge
    break;
    case 6:
    ia->mb->translate(10);
    break;
    case 7:
    ia->mb->translate(10);
    break;
    case 8:
    ia->mb->translate(10);
    break;
    case 9:
    ia->mb->translate(450);
    break;
    case 10:
    ia->mb->translate(-500);
    break;
    case 11:
    ia->mb->rotate(-3*PI/8*(ia->getFlag("side")?1:-1));
    break;
    case 12:
    ia->mb->translate(1000);
    break;
    case 13:
    ia->mb->rotate(-PI/8*(ia->getFlag("side")?1:-1));
    break;
    case 14:
    ia->mb->translate(600);
    break;
    case 15:
    ia->mb->translate(600);// A CHANGER EN FONCTION DE LA GIROUETTE
    break;
    case 16:
    ia->mb->rotate(-PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 17:
    ia->mb->translate(1100); //le robot place les goblets rouges dans le port
    break;
    default:
    // Abnormal comportment
    break;
  }
  state++;
}

boolean TrajetWinter::isCompleted(){ //wether the last action of this protocol have already been executed or not
  return state>17;
}

unsigned short int TrajetWinter::getPriority(IA *ia){
  return priority;
}
