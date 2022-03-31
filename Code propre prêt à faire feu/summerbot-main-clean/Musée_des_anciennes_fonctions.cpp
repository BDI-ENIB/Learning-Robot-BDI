// boite noire à comprendre...
// Detection du starter, sans faux-départs
/*
void delayStarter() {
  double tmp = 0;
  boolean hasStarterBeenInserted = false;
  while (true) {
    tmp = (double)(tmp * 99.0 + digitalRead(STARTER)) / 100.0;
    if (!hasStarterBeenInserted && tmp >= 0.95) {
      hasStarterBeenInserted = true;
      Serial.println("Starter ready!");
      
    }
    if(hasStarterBeenInserted && tmp <= 0.05){
      return;
    }
    delay(1);
  }

}

// le fichier  hpp qui définissait des zones ou on pouvait faire des trucs (dits dans les noms des fonctions)
#ifndef NODES_HPP
#define NODES_HPP 1


class Node {
  private:
    int x, y;
    double a;
  public:
    int getX(){
      return x;
    }
    int getY(bool isGreenSide){
      return isGreenSide?y:3000-y;
    }
    double getA(bool isGreenSide){
      return isGreenSide?a:-a;
    }
    Node(int x, int y): x{x}, y{y}, a{0} {}
    Node(int x, int y,double a): x{x}, y{y}, a{a} {}
};

extern Node g_roadMain;
extern Node g_roadButton;
extern Node g_start;
extern Node g_cross1;
extern Node g_cross2;
extern Node g_cross3;

extern Node unloadingZones[];
extern Node RoadCubeLoadingZone[];
extern Node RealCubeLoadingZone[];
extern Node RoadBuldozerCubeLoadingZone[];
extern Node RealBuldozerCubeLoadingZone[];
#endif

// le fichier cpp qui va avec :
#include "nodes.hpp"
#include "robot.h"
#include "Arduino.h"

Node g_roadMain =Node(325,610);
Node g_roadButton =Node(325,1130);
Node g_start=Node(180,200);
Node g_cross1=Node(550,650);
Node g_cross2=Node(990,300);
Node g_cross3=Node(1500,900);

Node unloadingZones[]={
  Node(180+60,490),
  Node(180+60,670),
  Node(180+60,850)
};
Node RoadCubeLoadingZone[]={
  Node(540,610),
  Node(1190,610),
  Node(1500,610)
};
Node RealCubeLoadingZone[]={
  Node(540,850-ROBOT_1_W/2,PI/2),
  Node(1190,280+44+ROBOT_1_W/2,-PI/2),
  Node(1500,1100-ROBOT_1_W/2,PI/2)
};
Node RoadBuldozerCubeLoadingZone[]={
Node(840,1130,-PI/2),
Node(1540,610,-PI/2)
};
Node RealBuldozerCubeLoadingZone[]={
Node(840,850,PI),
Node(1540,200,9*PI/10)
};


// le fichier robot qui définissait les dimmensions du robot
#ifndef ROBOT_H
#define ROBOT_H

#define ROBOT_1_W 220
#define ROBOT_1_H 220
#define ROBOT_1_W_DEPLOYED (220+60)
#define ROBOT_1_H_DEPLOYED 220

#define ROBOT_2_W 220
#define ROBOT_2_H 220
#define ROBOT_2_W_DEPLOYED 220
#define ROBOT_2_H_DEPLOYED 220

#endif





*/