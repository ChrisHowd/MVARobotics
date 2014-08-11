#include <Wire\Wire.h>
#include <Servo\Servo.h>

int pinRotationServo;
int pinUpDownServo;

Servo servoRotation;
Servo servoUpDown;

int servoRotationHomePos;
int servoRotationMinPos;
int servoRotationMaxPos;

int servoUpDownHomePos;
int servoUpDownMinPos;
int servoUpDownMaxPos;

int servoMovementStepSize;

int demoMode;
int demoMoveOneStep;
int demoMoveSmoothed;

void setup()
{
	pinRotationServo = 3;
	pinUpDownServo = 10;

	servoRotation.attach(pinRotationServo);
	servoUpDown.attach(pinUpDownServo);

	servoRotationHomePos = 1500;
	servoRotationMinPos = servoRotationHomePos - 1000;
	servoRotationMaxPos = servoRotationHomePos + 1000;

	servoUpDownHomePos = 1500;
	servoUpDownMinPos = servoUpDownHomePos - 1000;
	servoUpDownMaxPos = servoUpDownHomePos + 800;

	servoRotation.writeMicroseconds(servoRotationHomePos);
	servoUpDown.writeMicroseconds(servoUpDownMinPos);

}

void loop()
{
	//fullRangeMovesDemo();
	//fullRangeMovesDemo();

	//steppedMoveDemo();
	//steppedMoveDemo();

}

void fullRangeMovesDemo()
{
	// Move as follows
	//	1.	forward center
	//	2.	forward left
	//	3.	forward right
	//	4.	forward center
	//
	// center and down forward
	servoRotation.writeMicroseconds(servoRotationHomePos);
	servoUpDown.writeMicroseconds(servoUpDownMinPos);
	delay(5000);

	// left and down forward
	servoRotation.writeMicroseconds(servoRotationMinPos);
	servoUpDown.writeMicroseconds(servoUpDownMinPos);
	delay(1000);

	// right and down forward
	servoRotation.writeMicroseconds(servoRotationMaxPos);
	servoUpDown.writeMicroseconds(servoUpDownMinPos);
	delay(1000);

	// center and down forward
	servoRotation.writeMicroseconds(servoRotationHomePos);
	servoUpDown.writeMicroseconds(servoUpDownMinPos);
	delay(1000);

}


void steppedMoveDemo()
{
	// Move as follows
	//	1.	forward center
	//	2.	forward left
	//	3.	forward right
	//	4.	forward center
	//

	int currentPosR;
	int currentPosUD;

	int movetoPosR;
	int movetoPosUD;

	//	1.	forward center
	currentPosR = servoRotationHomePos;
	currentPosUD = servoUpDownMinPos;
	movetoPosR = servoRotationHomePos;
	movetoPosUD = servoUpDownMinPos;

	steppedMove(currentPosR, currentPosUD, movetoPosR, movetoPosUD);
	delay(5000);

	//	2.	forward left
	currentPosR = movetoPosR;
	currentPosUD = movetoPosUD;
	movetoPosR = servoRotationMaxPos;
	movetoPosUD = servoUpDownMinPos;

	steppedMove(currentPosR, currentPosUD, movetoPosR, movetoPosUD);
	delay(1000);


	//	3.	forward right
	currentPosR = movetoPosR;
	currentPosUD = movetoPosUD;
	movetoPosR = servoRotationMinPos;
	movetoPosUD = servoUpDownMinPos;

	steppedMove(currentPosR, currentPosUD, movetoPosR, movetoPosUD);
	delay(1000);


	//	4.	forward center
	currentPosR = movetoPosR;
	currentPosUD = movetoPosUD;
	movetoPosR = servoRotationHomePos;
	movetoPosUD = servoUpDownMinPos;

	steppedMove(currentPosR, currentPosUD, movetoPosR, movetoPosUD);
	delay(1000);

}

void steppedMove(int currPosR, int currPosUD, int destPosR, int destPosUD)
{
	int distMoveR = destPosR - currPosR;
	int distMoveUD = destPosUD - currPosUD;

	//int delayTime[10] = { 70, 80, 90, 110, 150, 150, 110, 90, 80, 70 };
	//long delayTime[10];
	//float incrStepDist[10] = { .01, .03, .06, .15, .25, .25, .15, .06, .03, .01 };
	//float incrStepCumPos[10] = { .01, .04, .10, .25, .50, .75, .90, .96, .99, 1.0 };
	//int incrPositionsR[10];
	//int incrPositionsUD[10];

	long delayTime[20];
	float incrStepDist[20] = { .005, .005, .010, .010, .020, .040, .080, .100, .110, .120, .120, .110, .100, .080, .040, .020, .010, .010, .005, .005};
	float incrStepCumPos[20] = { .005, .010, .020, .030, .050, .090, .170, .270, .380, .500, .620, .730, .830, .910, .950, .970, .980, .990, .995, 1.000 };
	int incrPositionsR[20];
	int incrPositionsUD[20];

	for (int i = 0; i < 20; i++)
	{
		incrPositionsR[i] = currPosR + (distMoveR * incrStepCumPos[i]);
		incrPositionsUD[i] = currPosUD + (distMoveUD * incrStepCumPos[i]);

		delayTime[i] = 20 + (abs(distMoveR * incrStepDist[i]) / 20) + (abs(distMoveR * incrStepDist[i]) / 10) + (abs(distMoveR * incrStepDist[i]) / 6);
	}

	for (int i = 0; i < 20; i++)
	{
		servoRotation.writeMicroseconds(incrPositionsR[i]);
		servoUpDown.writeMicroseconds(incrPositionsUD[i]);
		
		delay( delayTime[i] );

	}

}