#include <Wire\Wire.h>
#include <Servo\Servo.h>

Servo leftServoMotor;
Servo rightServoMotor;

int leftServoPin;
int rightServoPin;

int servoSpeedLeftForward;
int servoSpeedRightForward;

int servoSpeedLeftBackward;
int servoSpeedRightBackward;

int servoSpeedLeftStop;
int servoSpeedRightStop;

//Create a boolean that can be used to turn diagnostics on and off and implement diagnostics inside loop()
bool diagnosticsMode;

void setup()
{
	leftServoPin = 3;
	rightServoPin = 10;

	leftServoMotor.attach(leftServoPin);
	rightServoMotor.attach(rightServoPin);

	servoSpeedLeftStop = 1490;
	servoSpeedRightStop = 1500;

	servoSpeedLeftForward = servoSpeedLeftStop + 109;			// maybe try 109
	servoSpeedLeftBackward = servoSpeedLeftStop - 60;			// keep 60

	servoSpeedRightForward = servoSpeedRightStop - 100;			// keep 100
	servoSpeedRightBackward = servoSpeedRightStop + 65;			// maybe try 65

	diagnosticsMode = true;
}

void loop()
{
	if (diagnosticsMode == true)
	{
		// Step 1 - zero out the Servos at 1500
		//robotStop();

		// Step 2 - Run Forward calibration
		//robotForward();

		// Step 3 - run Backward calibration
		robotBackward();

	}

}

//Create the required functions
void controlLeftWheelSpeed(int spd)
{
	leftServoMotor.writeMicroseconds(spd);
}

void controlRightWheelSpeed(int spd)
{
	rightServoMotor.writeMicroseconds(spd);
}

void robotForward()
{
	leftServoMotor.writeMicroseconds(servoSpeedLeftForward);
	rightServoMotor.writeMicroseconds(servoSpeedRightForward);
}

void robotBackward()
{
	leftServoMotor.writeMicroseconds(servoSpeedLeftBackward);
	rightServoMotor.writeMicroseconds(servoSpeedRightBackward);
}

void robotStop()
{
	leftServoMotor.writeMicroseconds(servoSpeedLeftStop);
	rightServoMotor.writeMicroseconds(servoSpeedRightStop);
}
