#include "SensorManager.hpp"
#include <Arduino.h>

/* defines for every sensors on the summerbot board */

// IR
#define IRS1 A5
#define IRS2 A4
#define IRS3 A3
#define IRS4 A2
#define IRS5 A1
#define IRS6 A0
#define IRS7 A22
#define IRS8 A21

// US
#define USS1 34
#define USS2 33

/* SensorManager */
SensorManager* sensorManager;

/* Detection threshold distance for every sensor (mm) */
#define DISTANCETHRESHOLD 500

void setup (){
  sensorManager = new SensorManager();

  // registering 4 IR Sensors
  sensorManager->registerNewSensor(IRS1, SHARP);
  sensorManager->registerNewSensor(IRS2, SHARP);
  sensorManager->registerNewSensor(IRS3, SHARP);
  sensorManager->registerNewSensor(IRS4, SHARP);
  sensorManager->registerNewSensor(IRS5, SHARP);
  sensorManager->registerNewSensor(IRS6, SHARP);

  Serial.begin(9600);
}

void loop (){/*
  bool AdvDetected1 =sensorManager->detectObject(IRS1, DISTANCETHRESHOLD) ;
  bool AdvDetected2 =sensorManager->detectObject(IRS2, DISTANCETHRESHOLD) ;
  bool AdvDetected3 =sensorManager->detectObject(IRS3, DISTANCETHRESHOLD) ;
  bool AdvDetected4 =sensorManager->detectObject(IRS4, DISTANCETHRESHOLD) ;
  bool AdvDetected5 =sensorManager->detectObject(IRS5, DISTANCETHRESHOLD) ;
  bool AdvDetected6 =sensorManager->detectObject(IRS6, DISTANCETHRESHOLD);

  if(AdvDetected1){
    Serial.println("ADVERSAIRE 1 DETECTE !");
  delay(300);
}
  if(AdvDetected2){
  Serial.println("ADVERSAIRE 2 DETECTE !");
delay(300);
}
if(AdvDetected3){
  Serial.println("ADVERSAIRE 3 DETECTE !");
delay(300);
}
if(AdvDetected4){
  Serial.println("ADVERSAIRE 4 DETECTE !");
delay(300);
}
if(AdvDetected5){
  Serial.println("ADVERSAIRE 5 DETECTE !");
delay(300);
}
if(AdvDetected6){
  Serial.println("ADVERSAIRE 6 DETECTE !");
delay(300);
}
Serial.println(" ");
}*/
Serial.println((String)analogRead(IRS2)+","+
(String)analogRead(IRS3)+","+
(String)analogRead(IRS4)+","+
(String)analogRead(IRS5)+","+
(String)analogRead(IRS6)+","+
(String)analogRead(IRS1));
delay(50);
}
