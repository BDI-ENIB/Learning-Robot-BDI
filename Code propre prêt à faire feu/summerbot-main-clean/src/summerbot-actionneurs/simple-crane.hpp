// classe moteur, initialiser le moteur à 0 , le faire tourner (dans les deux sens) (avec vitesse, sens, longeur parcouru)
#ifndef CRANE_HPP
#define CRANE_HPP


//#include NODES_HPP
#include <Servo.h>

class SimpleCrane
/*
Manage the utilisation of a crane, composed by a motor and a claw composed of two servo-motor
*/
{

public:

	//pins of the claw
 	static Servo* Rotate;
	static Servo* Grabber;
  	int s_pinRotate;
 	int s_pinGrabber;
	//constructor
	SimpleCrane(int pinRotate, int pinGrabber);

	// reset Crane
	void resetCrane();

	//Servo functions
	void Servo_rota_pince(bool sens, int absolute_value_rota_grab); // rotation de la pince droite/gauche
 	void Servo_open_pince(int value_open_pince); // ouverture de la pince
 	void Servo_close_pince(int value_close_pince); // fermeture de la pince


};

#endif
