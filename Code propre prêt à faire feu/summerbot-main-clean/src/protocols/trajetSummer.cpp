#include "trajetSummer.h"
#include <Arduino.h>// fonctions de base Arduino
#include "../../ia.hpp"
#include "../summerbot-actionneurs/simple-crane.hpp"
#include "../../modules.hpp"

void TrajetSummer::update(IA *ia){ //execute the next action of this protocol

  switch(state){
    case 0:
    if(initialPlacement == true){//330,750

    }
    break;
    case 1:
    ia->mb->translate(200);
    //Modules::simplecrane->resetCrane();
    break;
    case 2:
    ia->mb->rotate(PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 3:
    ia->mb->translate(1500);
    break;
    case 4:
    ia->mb->rotate(PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 5:
    ia->mb->translate(400);
    break;
    case 6:
    ia->mb->rotate(PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 7:
    ia->mb->translate(400); // PRAISE THE DEMON
    break;
    case 8:
    ia->mb->rotate(-PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 9:
    ia->mb->translate(700);
    break;
    case 10:
    ia->mb->rotate(PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 11:
    ia->mb->translate(400);
    break;
    case 12:
    ia->mb->rotate(PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 13:
    ia->mb->translate(1700);
    break;
    case 14:
    ia->mb->translate(-400);
    break;
    case 15:
    ia->mb->rotate(-PI/2*(ia->getFlag("side")?1:-1));
    break;
    case 16:
    ia->mb->translate(900);
    break;
    default:
    // Abnormal comportment
    break;
  }
  state++;
}

boolean TrajetSummer::isCompleted(){ //wether the last action of this protocol have already been executed or not
  return state>16;
}

unsigned short int TrajetSummer::getPriority(IA *ia){
  return priority;
}
