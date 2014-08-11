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
	digitalWrite(pinMotorDirectionDIR_A, moveForward);		// move forward
	analogWrite(pinMotorSpeedPWM_A, moveSpeedMax/2);		// middle speed
	delay(3000);											// 1 second

	analogWrite(pinMotorSpeedPWM_A, moveSpeedMax);			// increase to max speed
	delay(5000);											// 3 seconds

	analogWrite(pinMotorSpeedPWM_A, moveSpeedMax / 2);		// middle speed
	delay(3000);											// 1 second

	analogWrite(pinMotorSpeedPWM_A, moveSpeedStop);			// stop
	delay(3000);											// 3 second


	digitalWrite(pinMotorDirectionDIR_A, moveBackward);		// move forward
	analogWrite(pinMotorSpeedPWM_A, moveSpeedMax / 2);		// middle speed
	delay(3000);											// 1 second

	analogWrite(pinMotorSpeedPWM_A, moveSpeedMax);			// increase to max speed
	delay(5000);											// 3 seconds

	analogWrite(pinMotorSpeedPWM_A, moveSpeedMax / 2);		// middle speed
	delay(3000);											// 1 second

	analogWrite(pinMotorSpeedPWM_A, moveSpeedStop);			// stop
	delay(3000);											// 3 second

}



void back()
{
}

void forward()
{
}

void backward()
{
}

void stopped() //stop
{
}

void astop()
{
}



