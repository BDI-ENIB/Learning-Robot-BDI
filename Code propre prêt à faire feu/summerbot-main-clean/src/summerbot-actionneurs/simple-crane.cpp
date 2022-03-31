#include "simple-crane.hpp"
#include <Servo.h>
#include <Arduino.h>

	static Servo* Rotate;
	static Servo* Grabber;

SimpleCrane::SimpleCrane(int pinRotate, int pinGrabber){

	Rotate = new Servo();
	Rotate->attach(pinRotate);
	Grabber = new Servo();
	Grabber->attach(pinGrabber);

}

	void SimpleCrane::resetCrane()
	{
		
		Rotate->write(0); // Rotate en position 0 dans le setup
	 	Grabber->write(0); // Grabber en position 0 dans le setups
	}

	// Servo part :

  // Rotate control
	void SimpleCrane::Servo_rota_pince(bool sens, int absolute_value_rota_grab)
	{
		if (sens == LOW)
		{
			int sign = -1;
			int valeur_rota_grab = sign * absolute_value_rota_grab;
			Rotate->write(valeur_rota_grab); // RECALCULER LA VALEUR
		}
		else
		{
			int sign = 1;
			int valeur_rota_grab = sign * absolute_value_rota_grab;
			Rotate->write(valeur_rota_grab); // RECALCULER LA VALEUR
		}
	}

	void SimpleCrane::Servo_open_pince(int value_open_pince)
			{
				Grabber->write(value_open_pince); // Grabber fait ouvir la pince (chercher aussi la bonne valeur pour la pince)
			}

 	void SimpleCrane::Servo_close_pince(int value_close_pince)
			{
				Grabber->write(value_close_pince); // Grabber fait fermer la pince (voir pour la valeur aussi)
			}

