int pinMotorSpeedPWM_A = 3;									// use the pin labelled PWM A to control voltage (speed) for motor A
int pinMotorDirectionDIR_A = 12;							// use pin labelled DIR A to control the direction for motor A
															//
															// the Ardumotor shield does not use a special library

int moveForward = HIGH;										// forward move	
int moveBackward = LOW;										// backward move

int moveSpeedStop = 0;										// stopped	
int moveSpeedMax = 255;										// max speed	

void setup()
{
	pinMode(pinMotorSpeedPWM_A, OUTPUT);					// set motor control pins for output
	pinMode(pinMotorDirectionDIR_A, OUTPUT);

	digitalWrite(pinMotorDirectionDIR_A, moveForward);		// set direction to forward
	analogWrite(pinMotorSpeedPWM_A, moveSpeedStop);			// set speed to stop

}

void loop()
{
	motorSpeedTest();

}

void motorSpeedTest()
{
	motorDirectionAndSpeed(moveForward, moveSpeedMax / 2);	// move forward at 1/2 speed
	delay(3000);											// run for 3 seconds

	motorDirectionAndSpeed(moveForward, moveSpeedMax);		// move forward at full speed
	delay(5000);											// run for 5 seconds

	motorDirectionAndSpeed(moveForward, moveSpeedMax / 2);	// move forward at 1/2 speed
	delay(3000);											// run for 3 seconds

	motorDirectionAndSpeed(moveForward, moveSpeedStop);		// stop
	delay(3000);											// 3 seconds


	motorDirectionAndSpeed(moveBackward, moveSpeedMax / 2);	// move backward at 1/2 speed
	delay(3000);											// run for 3 seconds

	motorDirectionAndSpeed(moveBackward, moveSpeedMax);		// move backward at full speed
	delay(5000);											// run for 5 seconds

	motorDirectionAndSpeed(moveBackward, moveSpeedMax / 2);	// move backward at 1/2 speed
	delay(3000);											// run for 3 seconds

	motorDirectionAndSpeed(moveBackward, 0);				// stop
	delay(3000);											// 3 seconds

}

void motorDirectionAndSpeed(int dirA, int spdA)
{
	digitalWrite(pinMotorDirectionDIR_A, dirA);				// set the direction
	analogWrite(pinMotorSpeedPWM_A, spdA);					// set the speed

}