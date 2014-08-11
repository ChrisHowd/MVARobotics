#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield_V2\Adafruit_MotorShield.h>
#include "Adafruit_MotorShield_V2\\utility\Adafruit_PWMServoDriver.h"


// declare variables 
// -----------------------------------------
bool robotInitialized;										//
bool performDiagnosticsChecks;								//
bool armDiagnostics;										//
bool wheelSpeedDiagnostics;									//
bool sensorDiagnostics;										//
bool areaMapped;											//
bool monitoringArea;										//
bool intruderDetected;										//
bool intruderStopped;										//
//
int armLRCenterPosition;									// Robot Arm, rotation center position
int armLRLeftPosition;										// Robot Arm, rotation 90 deg counter-clockwise (left) 
int armLRRightPosition;										// Robot Arm, rotation 90 deg clockwise (left) 
//
int armUDUpPosition;										// Robot Arm, up-down center (up) position
int armUDFrontPosition;										// Robot Arm, up-down forward position
int armUDBackPosition;										// Robot Arm, up-down back position
// 
int currPosR;												// current position, rotation
int currPosUD;												// current position, up/down
int destPosR;												// destination position, rotation
int destPosUD;												// destination position, up/down

//
uint8_t wheelBL_speed;										// Wheel, Back Left, speed: 0-255
uint8_t wheelBL_direction;									// Wheel, Back Left, direction: FORWARD, REVERSE (and RELEASE) 
uint8_t wheelBR_speed;										// Wheel, Back Right, speed: 0-255
uint8_t wheelBR_direction;									// Wheel, Back Right, direction: FORWARD, REVERSE (and RELEASE) 
uint8_t wheelFL_speed;										// Wheel, Front Left, speed: 0-255
uint8_t wheelFL_direction;									// Wheel, Front Left, direction: FORWARD, REVERSE (and RELEASE) 
uint8_t wheelFR_speed;										// Wheel, Front Right, speed: 0-255
uint8_t wheelFR_direction;									// Wheel, Front Right, direction: FORWARD, REVERSE (and RELEASE) 
//
// 
Adafruit_MotorShield AFMS = Adafruit_MotorShield();			// declare the Motor Shield
//
Adafruit_DCMotor *motorBackLeft;							// declare each of the four gearmotor objects
Adafruit_DCMotor *motorBackRight;							//
Adafruit_DCMotor *motorFrontRight;							//
Adafruit_DCMotor *motorFrontLeft;							//
// declare the two Robot Arm servo motor objects
Servo armServoMotorLeftRight;								//
Servo armServoMotorUpDown;									//
// declare the three sensor servo motor objects
Servo sensorServoFL;										//
Servo sensorServoFR;										//
Servo sensorServoBR;										//
//
int sensorServoFLLeftPosition;								//
int sensorServoFLFrontPosition;								//
int sensorServoFRFrontPosition;								//
int sensorServoFRRightPosition;								//
int sensorServoBRRightPosition;								//
int sensorServoBRBackPosition;								//
//	
int sensorValueFL;											//
int sensorValueFR;											//
int sensorValueBR;											//
//
float sensorVoltageFL;										//
float sensorVoltageFR;										//
float sensorVoltageBR;										//
//
float sensorDistanceFL;										//
float sensorDistanceFR;										//
float sensorDistanceBR;										//
//
float sumDistFLSmoothed;									//  
float sumDistFRSmoothed;									//
float sumDistBRSmoothed;									//
//
float avgDistFLSmoothed;									//
float avgDistFRSmoothed;									//
float avgDistBRSmoothed;									//
//
float distWallOne;											//
float distWallTwo;											//
float distWallThree;										//
float distWallFour;											//
float orientationDegrees;									// Orientation of the robot relative to Wall One (0-360 degrees)
//		Where 0 deg is facing Wall One
//		Clockwise Positive degrees
//
float xCoordinatePos;										//
float yCoordinatePos;										//
float xCoordinateMax;										//
float yCoordinateMax;										//
//
float distBetweenSensors;									//

float intruderDirection;

void setup()
{
	distBetweenSensors = 7.0;								// the ultrasonic sensors are seperated by 7 inches (approximately 178 mm)
	//
	// attach the Robot Arm servo motors to PWM pins 9 and 10
	armServoMotorLeftRight.attach(10);						//
	armServoMotorUpDown.attach(9);							//
	// attach the Sensor servo motors to PWM pins 4, 5, and 6
	sensorServoFL.attach(4);								//
	sensorServoFR.attach(5);								//
	sensorServoBR.attach(6);								//

	sensorServoFLLeftPosition = 1610;						// point left,		larger numbers move counter clockwise
	sensorServoFLFrontPosition = 750;						// point forward,	larger numbers move counter clockwise
	sensorServoFRFrontPosition = 1700;						// point forward,	larger numbers move counter clockwise 
	sensorServoFRRightPosition = 800;						// point right,		larger numbers move counter clockwise 
	sensorServoBRRightPosition = 1700;						// point right,		larger numbers move counter clockwise 
	sensorServoBRBackPosition = 800;						// point back,		larger numbers move counter clockwise 


	motorBackLeft = AFMS.getMotor(1);						//
	motorBackRight = AFMS.getMotor(2);						//
	motorFrontRight = AFMS.getMotor(3);						//
	motorFrontLeft = AFMS.getMotor(4);						//

	armLRCenterPosition = 1500;								// Robot Arm, rotation center position
	armLRLeftPosition = armLRCenterPosition - 1100;			// Robot Arm, rotation 90 deg counter-clockwise (left) 
	armLRRightPosition = armLRCenterPosition + 1100;		// Robot Arm, rotation 90 deg clockwise (left) 
	//
	armUDUpPosition = 1500;									// Robot Arm, up-down center (up) position
	armUDFrontPosition = armUDUpPosition + 700;				// Robot Arm, up-down forward position
	armUDBackPosition = armUDUpPosition - 1100;				// Robot Arm, up-down back position
	//
	wheelBL_speed = 100;									// Wheel, Back Left, speed: 0-255
	wheelBR_speed = 100;									// Wheel, Back Right, speed: 0-255
	wheelFL_speed = 100;									// Wheel, Front Left, speed: 0-255
	wheelFR_speed = 100;									// Wheel, Front Right, speed: 0-255

	AFMS.begin();											// create with the default frequency 1.6KHz, OR with a different frequency, say 1KHz AFMS.begin(1000) 

	// Set the speed to start, from 0 (off) to 255 (max speed)
	motorBackLeft->setSpeed(wheelBL_speed);					//
	motorBackLeft->run(FORWARD);							//
	motorBackLeft->run(RELEASE);							//
	//
	motorBackRight->setSpeed(wheelBR_speed);				//
	motorBackRight->run(FORWARD);							//
	motorBackRight->run(RELEASE);							//

	motorFrontLeft->setSpeed(wheelFL_speed);				//
	motorFrontLeft->run(FORWARD);							//
	motorFrontLeft->run(RELEASE);							//
	//
	motorFrontRight->setSpeed(wheelFR_speed);				//
	motorFrontRight->run(FORWARD);							//
	motorFrontRight->run(RELEASE);							//

	robotInitialized = false;								//
	performDiagnosticsChecks = true;						//
	armDiagnostics = true;									//
	wheelSpeedDiagnostics = false;							//
	sensorDiagnostics = false;								//
	areaMapped = false;										//
	monitoringArea = false;									//
	intruderDetected = false;								//
	intruderStopped = false;								//

}

void loop()
{
	if (robotInitialized == false) initializeRobot();		// initialize robot on startup
	//
	if (performDiagnosticsChecks == true)					// check to see if running diagnostics
	{																		//	
		if (armDiagnostics == true) testArmMovement();						// run arm positioning diagnostics
		if (wheelSpeedDiagnostics == true) testGearmotors();				// run wheel speed diagnostics
		if (sensorDiagnostics == true) testSensorPositioningAndReadings();	// run sensor positioning and distance measurement diagnostics 
		//
	}														//
	else if (intruderStopped == false)						// if running live and intruder has not been stopped, then
	{														//
		if (areaMapped == false)							// check to see if the area has been mapped
		{													//
			mapArea();										// map the area
		}													//
		else												// check to see if the 
		{													//
			if (monitoringArea == false)					//
			{												//
				moveToCenterPosition();								//
			}												//
			else											//
			{												//
				if (intruderDetected == false)				//
				{											//
					checkForIntruder();						//
				}											//
				else										//
				{											//
					stopIntruder();							//
				}											//
			}												//
		}													//
	}														//
}


void initializeRobot()
{
	// place code here to initialize robot

	// position sensors: left, front, back	
	sensorServoFL.writeMicroseconds(sensorServoFLLeftPosition);		// point left,		larger numbers move counter clockwise
	sensorServoFR.writeMicroseconds(sensorServoFRFrontPosition);	// point forward,	larger numbers move counter clockwise
	sensorServoBR.writeMicroseconds(sensorServoBRBackPosition);		// point back,		larger numbers move counter clockwise
	delay(500);

	readSensorVoltages();
	delay(1000);

	// position servos to the front/right/back
	sensorServoFL.writeMicroseconds(sensorServoFLFrontPosition);	// point forward,	larger numbers move counter clockwise
	sensorServoFR.writeMicroseconds(sensorServoFRRightPosition);	// point right,		larger numbers move counter clockwise
	sensorServoBR.writeMicroseconds(sensorServoBRRightPosition);	// point right,		larger numbers move counter clockwise
	delay(500);

	readSensorVoltages();
	delay(1000);


	// STOP
	motorBackLeft->setSpeed(0);
	motorBackRight->setSpeed(0);
	motorFrontLeft->setSpeed(0);
	motorFrontRight->setSpeed(0);
	delay(1000);


	armServoMotorLeftRight.writeMicroseconds(armLRCenterPosition);
	armServoMotorUpDown.writeMicroseconds(armUDUpPosition);
	currPosR = armLRCenterPosition;
	currPosUD = armUDUpPosition;
	
	robotInitialized = true;

}


void mapArea()
{

	designateWallOne();												// Orient the robot parallel to the wall on the right, 270 deg orientation

	moveToCenterPosition();											// Move to the center of the container area

	areaMapped = true;

}


void calcRobotCoordinates()
{
	// Coordinates are relative to the containment area corner at the intersection of Wall One and Wall Two
	//		X-coordinate values increase as the robot moves toward Wall Three
	//		Y-coordinate values increase as the robot moves toward Wall Four
	//
	xCoordinatePos = distWallOne;
	yCoordinatePos = distWallTwo;

	xCoordinateMax = distWallOne + distWallThree + distBetweenSensors;
	yCoordinateMax = distWallTwo + distWallFour + distBetweenSensors;



}


void moveToCenterPosition()
{
	// use the following to navigate to the center position:
	//		orientationDegrees
	//		xCoordinatePos and yCoordinatePos
	//		xCoordinateMax and yCoordinateMax
	//
	monitoringArea = false;

	float offCenterX;
	float offCenterY;
	int speed;
	long duration;

	if (orientationDegrees == 0.0)
	{

	}

	if (orientationDegrees == 90.0)
	{

	}

	if (orientationDegrees == 180.0)
	{

	}

	if (orientationDegrees == 270.0)								// facing Wall Four
	{
		sensorServoFL.writeMicroseconds(sensorServoFLFrontPosition);		// aim FL sensor Forward
		sensorServoFR.writeMicroseconds(sensorServoFRRightPosition);		// aim FR sensor Right
		sensorServoBR.writeMicroseconds(sensorServoBRBackPosition);			// aim BR sensor Back
		readSensorVoltages();

		offCenterY = avgDistBRSmoothed - avgDistFLSmoothed;
		speed = 30;

		if (offCenterY > 4)
		{
			while (offCenterY > 2)
			{
				duration = 150 * abs(offCenterY);
				robotBackwardSlow(speed, duration);

				readSensorVoltages();
				offCenterY = avgDistBRSmoothed - avgDistFLSmoothed;;

			}
		}

		else if (offCenterY < -4)
		{
			while (offCenterY < -2)
			{
				duration = 150 * abs(offCenterY);
				robotForwardSlow(speed, duration);

				readSensorVoltages();
				offCenterY = avgDistBRSmoothed - avgDistFLSmoothed;

			}

		}

		sensorServoFL.writeMicroseconds(sensorServoFLLeftPosition);			// aim FL sensor Left
		sensorServoFR.writeMicroseconds(sensorServoFRFrontPosition);		// aim FR sensor Forward
		sensorServoBR.writeMicroseconds(sensorServoBRRightPosition);		// aim BR sensor Right
		readSensorVoltages();

		offCenterX = avgDistBRSmoothed - avgDistFLSmoothed;

		if (abs(offCenterX) > 4)
		{
			// Need to rotate clockwise 90 degrees (+/- 30 degrees)
			robotSpinClockwise90();


			// Align to Wall Two
			sensorServoFL.writeMicroseconds(sensorServoFLFrontPosition);			// aim FL sensor Forward
			sensorServoFR.writeMicroseconds(sensorServoFRRightPosition);			// aim FR sensor Right
			sensorServoBR.writeMicroseconds(sensorServoBRRightPosition);			// aim BR sensor Right
			readSensorVoltages();

			speed = 50;
			duration = 250;

			if (avgDistBRSmoothed - avgDistFRSmoothed > 1)
			{
				while (avgDistBRSmoothed - avgDistFRSmoothed > 0.5)
				{
					robotSpinCounterClockwise(speed, duration);
					readSensorVoltages();

				}
			}

			if (avgDistBRSmoothed - avgDistFRSmoothed < -1)
			{
				while (avgDistBRSmoothed - avgDistFRSmoothed < -0.5)
				{
					// rotate clockwise
					robotSpinClockwise(speed, duration);
					readSensorVoltages();

				}
			}


			//	10. orientationDeg = orientationDeg + 90 
			orientationDegrees += 90.0;

			//	11. if (orientationDeg > 300) orientationDeg = 0;
			if (orientationDegrees > 300.0) orientationDegrees = 0.0;


			// aim the two front sensors forward
			sensorServoFL.writeMicroseconds(sensorServoFLFrontPosition);			// aim FL sensor Forward
			sensorServoFR.writeMicroseconds(sensorServoFRRightPosition);			// aim FR sensor Right
			sensorServoBR.writeMicroseconds(sensorServoBRBackPosition);				// aim BR sensor Back

			//	12. get distance measurements
			readSensorVoltages();

			//	14. offCenterX = xCoordinatePos - (xCoordinateMax / 2);
			offCenterX = avgDistBRSmoothed - avgDistFLSmoothed;
			speed = 30;

			//	15. if (offCenterX > 4), move backward
			if (offCenterX > 4)
			{
				while (offCenterX > 2)
				{
					duration = 150 * abs(offCenterX);
					robotBackwardSlow(speed, duration);

					readSensorVoltages();

					offCenterX = avgDistBRSmoothed - avgDistFLSmoothed;

				}
			}

			//	15. if (offCenterX < -4), move forward
			else if (offCenterX < -4)
			{
				while (offCenterX < -2)
				{
					duration = 150 * abs(offCenterX);
					robotForwardSlow(speed, duration);

					readSensorVoltages();

					offCenterX = avgDistBRSmoothed - avgDistFLSmoothed;

				}

			}

		}

	}

	monitoringArea = true;

}


float distanceToWallOne()
{
	// check orientation to determine which sensor(s) can point at Wall One
	if (orientationDegrees == 0.0)
	{
		// use left and right front sensors (FL and FR) pointing Front
		sensorServoFL.writeMicroseconds(sensorServoFLFrontPosition);	// aim sensorFL FRONT
		sensorServoFR.writeMicroseconds(sensorServoFRFrontPosition);	// aim sensorFR FRONT
		delay(1000);
		readSensorVoltages();
		distWallOne = (avgDistFLSmoothed + avgDistFRSmoothed) / 2;

	}

	if (orientationDegrees == 90.0)
	{
		// use front left sensor (FL) pointing Left
		sensorServoFL.writeMicroseconds(sensorServoFLLeftPosition);		// aim sensorFL Left
		delay(1000);
		readSensorVoltages();
		distWallOne = avgDistFLSmoothed;
	}

	if (orientationDegrees == 180.0)
	{
		// use back right sensor (BR) pointing Back
		sensorServoBR.writeMicroseconds(sensorServoBRBackPosition);		// aim sensorBR BACK
		delay(1000);
		readSensorVoltages();
		distWallOne = avgDistBRSmoothed;

	}

	if (orientationDegrees == 270.0)
	{
		// use front and back right side sensors (FR and BR) pointing Right
		sensorServoFR.writeMicroseconds(sensorServoFRRightPosition);	// aim sensorFR RIGHT
		sensorServoBR.writeMicroseconds(sensorServoBRRightPosition);	// aim sensorBR RIGHT
		delay(1000);
		readSensorVoltages();
		distWallOne = (avgDistFRSmoothed + avgDistBRSmoothed) / 2;

	}

}



float distanceToWallTwo()
{
	// check orientation to determine which sensor(s) can point at Wall One
	if (orientationDegrees == 0.0)
	{
		// use front and back right side sensors pointing Right
		sensorServoFR.writeMicroseconds(sensorServoFRRightPosition);	// aim sensorFR RIGHT
		sensorServoBR.writeMicroseconds(sensorServoBRRightPosition);	// aim sensorBR RIGHT
		delay(1000);
		readSensorVoltages();
		distWallTwo = (avgDistFRSmoothed + avgDistBRSmoothed) / 2;

	}

	if (orientationDegrees == 90.0)
	{
		// use front left and front right sensors pointing Front
		sensorServoFL.writeMicroseconds(sensorServoFLFrontPosition);	// aim sensorFL FRONT
		sensorServoFR.writeMicroseconds(sensorServoFRFrontPosition);	// aim sensorFR FRONT
		delay(1000);
		readSensorVoltages();
		distWallTwo = (avgDistFLSmoothed + avgDistFRSmoothed) / 2;

	}

	if (orientationDegrees == 180.0)
	{
		// use front left sensor pointing Left
		sensorServoFL.writeMicroseconds(sensorServoFLLeftPosition);		// aim sensorFL Left
		delay(1000);
		readSensorVoltages();
		distWallTwo = avgDistFLSmoothed;

	}

	if (orientationDegrees == 270.0)
	{
		// use back right sensor pointing Back
		sensorServoBR.writeMicroseconds(sensorServoBRBackPosition);		// aim sensorBR BACK
		delay(1000);
		readSensorVoltages();
		distWallTwo = avgDistBRSmoothed;

	}

}



float distanceToWallThree()
{
	// check orientation to determine which sensor(s) can point at Wall One
	if (orientationDegrees == 0.0)
	{
		// use back right sensors pointing Back
		sensorServoBR.writeMicroseconds(sensorServoBRBackPosition);		// aim sensorBR BACK
		delay(1000);
		readSensorVoltages();
		distWallThree = avgDistBRSmoothed;

	}

	if (orientationDegrees == 90.0)
	{
		// use front abd back right side sensors pointing Right
		sensorServoFR.writeMicroseconds(sensorServoFRRightPosition);	// aim sensorFR RIGHT
		sensorServoBR.writeMicroseconds(sensorServoBRRightPosition);	// aim sensorBR RIGHT
		delay(1000);
		readSensorVoltages();
		distWallThree = (avgDistFRSmoothed + avgDistBRSmoothed) / 2;

	}

	if (orientationDegrees == 180.0)
	{
		// use front left and front right sensors pointing Front
		sensorServoFL.writeMicroseconds(sensorServoFLFrontPosition);	// aim sensorFL FRONT
		sensorServoFR.writeMicroseconds(sensorServoFRFrontPosition);	// aim sensorFR FRONT
		delay(1000);
		readSensorVoltages();
		distWallThree = (avgDistFLSmoothed + avgDistFRSmoothed) / 2;

	}

	if (orientationDegrees == 270.0)
	{
		// use front left sensor pointing Left
		sensorServoFL.writeMicroseconds(sensorServoFLLeftPosition);		// aim sensorFL Left
		delay(1000);
		readSensorVoltages();
		distWallThree = avgDistFLSmoothed;

	}

}



float distanceToWallFour()
{
	// check orientation to determine which sensor(s) can point at Wall One
	if (orientationDegrees == 0.0)
	{
		// use front left sensor pointing Left
		sensorServoFL.writeMicroseconds(sensorServoFLLeftPosition);		// aim sensorFL Left
		delay(1000);
		readSensorVoltages();
		distWallFour = avgDistFLSmoothed;

	}

	if (orientationDegrees == 90.0)
	{
		// use back right sensors pointing Back
		sensorServoBR.writeMicroseconds(sensorServoBRBackPosition);		// aim sensorBR BACK
		delay(1000);
		readSensorVoltages();
		distWallFour = avgDistBRSmoothed;

	}

	if (orientationDegrees == 180.0)
	{
		// use front and back right side sensors pointing Right
		sensorServoFR.writeMicroseconds(sensorServoFRRightPosition);	// aim sensorFR RIGHT
		sensorServoBR.writeMicroseconds(sensorServoBRRightPosition);	// aim sensorBR RIGHT
		delay(1000);
		readSensorVoltages();
		distWallFour = (avgDistFRSmoothed + avgDistBRSmoothed) / 2;

	}

	if (orientationDegrees == 270.0)
	{
		// use front left and front right sensors pointing Front
		sensorServoFL.writeMicroseconds(sensorServoFLFrontPosition);	// aim sensorFL FRONT
		sensorServoFR.writeMicroseconds(sensorServoFRFrontPosition);	// aim sensorFR FRONT
		delay(1000);
		readSensorVoltages();
		distWallFour = (avgDistFLSmoothed + avgDistFRSmoothed) / 2;

	}

}


void designateWallOne()
{
	// position sensor servos 
	sensorServoFL.writeMicroseconds(sensorServoFLFrontPosition);	// point forward
	sensorServoFR.writeMicroseconds(sensorServoFRRightPosition);	// point right
	sensorServoBR.writeMicroseconds(sensorServoBRRightPosition);	// point right

	delay(1000);													// wait 1 second to allow servos to complete move

	readSensorVoltages();											// reads 50 values on each sensor and filters out false readings

	// begin aligning the robot to the wall that is to the right side of the robot

	float wallMisalignment = avgDistFRSmoothed - avgDistBRSmoothed;	// the difference between the two sensors need to be less than 0.5 inch (6mm)

	if (wallMisalignment > 0.5)
	{
		while (wallMisalignment > 0.5)
		{
			// the front of robot is further from the wall than the back
			robotSpinClockwise(50, 300);									// spin clockwise for 300 mSec

			readSensorVoltages();										// read the sensors

			wallMisalignment = avgDistFRSmoothed - avgDistBRSmoothed;	// recalculate misalignment 

		}

	}
	else if (wallMisalignment < -0.5)
	{
		while (wallMisalignment < -0.5)
		{
			// the back of robot is further from the wall than the front
			robotSpinCounterClockwise(50, 300);							// spin counter-clockwise for 300 mSec

			readSensorVoltages();										// read the sensors

			wallMisalignment = avgDistFRSmoothed - avgDistBRSmoothed;	// recalculate misalignment

		}


	}

	// verify that Wall Alignment has been achieved

	readSensorVoltages();										// read the sensors

	wallMisalignment = avgDistFRSmoothed - avgDistBRSmoothed;	// calculate misalignment 

	if (wallMisalignment > 0.5)
	{
		while (wallMisalignment > 0.5)
		{
			// the front of robot is further from the wall than the back
			robotSpinClockwise(50, 300);									// spin clockwise for 300 mSec

			readSensorVoltages();										// read the sensors

			wallMisalignment = avgDistFRSmoothed - avgDistBRSmoothed;	// recalculate misalignment 

		}

	}
	else if (wallMisalignment < -0.5)
	{
		while (wallMisalignment < -0.5)
		{
			// the back of robot is further from the wall than the front
			robotSpinCounterClockwise(50, 300);							// spin counter-clockwise for 300 mSec

			readSensorVoltages();										// read the sensors

			wallMisalignment = avgDistFRSmoothed - avgDistBRSmoothed;	// recalculate misalignment

		}


	}



	orientationDegrees = 270.0;										// robot is parallel to Wall One with Wall One to the right.
	//
	//	Diagram showing possible Wall One orientation (could be any of the four walls)
	//  _________________________________________________________________________________________
	//  |																						|
	//  |									Wall												|
	//  |									Four												|
	//  |																						|
	//  |																						|
	//  |												\  /	 \  /							|
	//  |												_\/_______\/_							|
	//	|											>>>>|S1		  S2|<<<<<<<<					|
	//	|												|			|							|
	//	|												|			|							|
	//	|												|			|							|
	//	|												|			|							|
	//	| Wall											|  270 Deg	|							| Wall
	//	| Three											|			|							|  One
	//	|												|			|							|
	//	|												|			|							|
	//	|												|		    |							|
	//	|												|_________S3|<<<<<<<<					|
	//  |														  /\							|
	//  |														 /	\							|
	//  |																						|
	//  |																						|
	//  |																						|
	//  |_______________________________________________________________________________________|
	//										
	//										Wall Two

}


void checkForIntruder()
{
	// place code here to scan for intruders
	intruderDetected = false;

	float alertDistance = 10;

	int degreeOffset;

	int servoFLIncrement = abs(sensorServoFLFrontPosition - sensorServoFLLeftPosition) / 3;
	int servoFRIncrement = abs(sensorServoFRFrontPosition - sensorServoFRRightPosition) / 3;
	int servoBRIncrement = abs(sensorServoBRRightPosition - sensorServoBRBackPosition) / 3;

	int servoFLPosition;
	int servoFRPosition;
	int servoBRPosition;

	while (intruderDetected == false)
	{
		// scan 150 degree range with each sensor 

		// position sensor servos at a minimum clockwise position (larger numbers move counter clockwise) 
		servoFLPosition = sensorServoFLFrontPosition - servoFLIncrement;
		servoFRPosition = sensorServoFRRightPosition - servoFRIncrement;
		servoBRPosition = sensorServoBRBackPosition - servoBRIncrement;

		sensorServoFL.writeMicroseconds(servoFLPosition);		// 
		sensorServoFR.writeMicroseconds(servoFRPosition);
		sensorServoBR.writeMicroseconds(servoBRPosition);

		degreeOffset = 0;
		while (degreeOffset <= 150)
		{
			readSensorVoltages();										// read the sensors

			if (avgDistFLSmoothed < alertDistance)
			{
				//robotSpinClockwise(150, 10000);
				intruderDetected = true;

				// calculate the relative direction of the intruder:
				//	minimum position for sensorFL (30 degrees clockwise from forward) 
				//	degreeOffset

				if (degreeOffset <= 60)
				{
					// intruder is in front of the robot within about 30 degrees
					intruderDirection = 0.0;

				}

				if (degreeOffset >= 90 && degreeOffset <= 150)
				{
					// intruder is to the left of the robot (within about 30 degrees)
					intruderDirection = -90.0;

				}

			}

			if (avgDistFRSmoothed < alertDistance)
			{
				//robotSpinClockwise(150, 10000);
				intruderDetected = true;

				if (degreeOffset <= 60)
				{
					// intruder is to the right side of the robot within about 30 degrees
					intruderDirection = 90.0;

				}

				if (degreeOffset >= 90 && degreeOffset <= 150)
				{
					// intruder is in front of the robot (within about 30 degrees)
					intruderDirection = 0.0;

				}

			}

			if (avgDistBRSmoothed < alertDistance)
			{
				//robotSpinClockwise(150, 10000);
				intruderDetected = true;

				// calculate the relative direction of the intruder:
				//	minimum position for sensorFL (30 degrees clockwise from forward) 
				//	degreeOffset

				if (degreeOffset <= 60)
				{
					// intruder is behind the robot within about 30 degrees
					intruderDirection = 180.0;

				}

				if (degreeOffset >= 90 && degreeOffset <= 150)
				{
					// intruder is to the right of the robot (within about 30 degrees)
					intruderDirection = 90.0;

				}


			}


			servoFLPosition += servoFLIncrement;
			servoFRPosition += servoFRIncrement;
			servoBRPosition += servoBRIncrement;

			sensorServoFL.writeMicroseconds(servoFLPosition);		// 
			sensorServoFR.writeMicroseconds(servoFRPosition);
			sensorServoBR.writeMicroseconds(servoBRPosition);

			degreeOffset += 30;

		}

	}

}


void stopIntruder()
{
	intruderStopped = false;

	// place code here to stop intruder
	sensorServoFL.writeMicroseconds(sensorServoFLFrontPosition);		// 
	sensorServoFR.writeMicroseconds(sensorServoFRRightPosition);
	sensorServoBR.writeMicroseconds(sensorServoBRBackPosition);

	// move arm down and swing it from side to side

	// move toward intruder
	if (intruderDirection == 0.0)
	{
		// move forward, speed = 30, duration = 500
		robotForwardSlow(30, 500);

	}

	if (intruderDirection == 90.0)
	{
		// spin clockwise 90 degrees
		robotSpinClockwise(150, 2000);

		// move forward, speed = 30, duration = 500
		robotForwardSlow(30, 500);


	}

	if (intruderDirection == 180.0)
	{
		// move backward, speed = 30, duration = 500
		robotBackwardSlow(30, 500);

		// spin clockwise 180 degrees
		robotSpinClockwise(150, 3000);

	}

	if (intruderDirection == -90.0)
	{
		// spin counter-clockwise 90 degrees
		robotSpinCounterClockwise(150, 2000);

		// move forward, speed = 30, duration = 500
		robotForwardSlow(30, 500);

	}

	// swing arm from side to side
	//armFrontCenter();
	destPosR = currPosR;
	destPosUD = armUDFrontPosition;
	steppedMove(currPosR, currPosUD, destPosR, destPosUD);
	currPosR = destPosR;
	currPosUD = destPosUD;
	delay(200);

	//armFrontLeft();
	destPosR = armLRLeftPosition;
	destPosUD = armUDFrontPosition;
	steppedMove(currPosR, currPosUD, destPosR, destPosUD);
	currPosR = destPosR;
	currPosUD = destPosUD;
	delay(200);

	//armFrontCenter();
	destPosR = armLRCenterPosition;
	destPosUD = armUDFrontPosition;
	steppedMove(currPosR, currPosUD, destPosR, destPosUD);
	currPosR = destPosR;
	currPosUD = destPosUD;
	delay(200);

	//armFrontRight();
	destPosR = armLRRightPosition;
	destPosUD = armUDFrontPosition;
	steppedMove(currPosR, currPosUD, destPosR, destPosUD);
	currPosR = destPosR;
	currPosUD = destPosUD;
	delay(200);

	//armFrontCenter();
	destPosR = currPosR;
	destPosUD = armUDFrontPosition;
	steppedMove(currPosR, currPosUD, destPosR, destPosUD);
	currPosR = destPosR;
	currPosUD = destPosUD;
	delay(200);

	//armFrontLeft();
	destPosR = armLRLeftPosition;
	destPosUD = armUDFrontPosition;
	steppedMove(currPosR, currPosUD, destPosR, destPosUD);
	currPosR = destPosR;
	currPosUD = destPosUD;
	delay(200);

	//armFrontCenter();
	destPosR = armLRCenterPosition;
	destPosUD = armUDFrontPosition;
	steppedMove(currPosR, currPosUD, destPosR, destPosUD);
	currPosR = destPosR;
	currPosUD = destPosUD;
	delay(200);

	//armFrontRight();
	destPosR = armLRRightPosition;
	destPosUD = armUDFrontPosition;
	steppedMove(currPosR, currPosUD, destPosR, destPosUD);
	currPosR = destPosR;
	currPosUD = destPosUD;
	delay(200);

	//armFrontCenter();
	destPosR = armLRCenterPosition;
	destPosUD = armUDFrontPosition;
	steppedMove(currPosR, currPosUD, destPosR, destPosUD);
	currPosR = destPosR;
	currPosUD = destPosUD;
	delay(200);

	//armUpCenter();
	destPosR = armLRCenterPosition;
	destPosUD = armUDUpPosition;
	steppedMove(currPosR, currPosUD, destPosR, destPosUD);
	currPosR = destPosR;
	currPosUD = destPosUD;
	delay(200);

	moveToCenterPosition();

	intruderStopped = true;

}


void testArmMovement()
{
	//armUpCenter();

	//armFrontCenter();
	destPosR = currPosR;
	destPosUD = armUDFrontPosition;
	steppedMove(currPosR, currPosUD, destPosR, destPosUD);
	currPosR = destPosR;
	currPosUD = destPosUD;
	delay(200);

	//armFrontLeft();
	destPosR = armLRLeftPosition;
	destPosUD = armUDFrontPosition;
	steppedMove(currPosR, currPosUD, destPosR, destPosUD);
	currPosR = destPosR;
	currPosUD = destPosUD;
	delay(200);
	
	//armFrontCenter();
	destPosR = armLRCenterPosition;
	destPosUD = armUDFrontPosition;
	steppedMove(currPosR, currPosUD, destPosR, destPosUD);
	currPosR = destPosR;
	currPosUD = destPosUD;
	delay(200);
	
	//armFrontRight();
	destPosR = armLRRightPosition;
	destPosUD = armUDFrontPosition;
	steppedMove(currPosR, currPosUD, destPosR, destPosUD);
	currPosR = destPosR;
	currPosUD = destPosUD;
	delay(200);

	//armFrontCenter();
	destPosR = armLRCenterPosition;
	destPosUD = armUDFrontPosition;
	steppedMove(currPosR, currPosUD, destPosR, destPosUD);
	currPosR = destPosR;
	currPosUD = destPosUD;
	delay(200);

	//armUpCenter();
	destPosR = armLRCenterPosition;
	destPosUD = armUDUpPosition;
	steppedMove(currPosR, currPosUD, destPosR, destPosUD);
	currPosR = destPosR;
	currPosUD = destPosUD;
	delay(200);

}


void testGearmotors()
{
	bool testForwardReverse = true;									//
	bool testRotation = true;										//

	uint8_t i;														// Speed Control - a uint8_t data type is used by the Adafruit board for Speed Control   

	long forwardDurationIncrement;									// Forward Distance - the forwardDurationIncrement establishes the distance that the robot moves forward 
	long backwardDurationIncrement;									//
	long clockwiseDurationIncrement;								//
	long counterclockwiseDurationIncrement;							//

	long forwardDurationIncrement4inch;								// 
	long backwardDurationIncrement4inch;							//
	long forwardDurationIncrement8inch;								// 
	long backwardDurationIncrement8inch;							//
	long forwardDurationIncrement12inch;							// 
	long backwardDurationIncrement12inch;							//

	long clockwiseDurationIncrement90deg;							//
	long counterclockwiseDurationIncrement90deg;					//
	long clockwiseDurationIncrement180deg;							//
	long counterclockwiseDurationIncrement180deg;					//


	if (testForwardReverse == true)
	{
		// Begin the Forward Movement Test
		//
		//		By adjusting the value of forwardDurationIncrement, 
		//		you can control how far the robot moves forward.
		//
		//		Move Values
		//			4 inches, forwardDurationIncrement = ?
		//			8 inches, forwardDurationIncrement = 40
		//			12 inches, forwardDurationIncrement = ?
		//
		//

		motorBackLeft->run(FORWARD);
		motorBackRight->run(FORWARD);
		motorFrontLeft->run(FORWARD);
		motorFrontRight->run(FORWARD);

		forwardDurationIncrement4inch = 20;
		forwardDurationIncrement8inch = 40;
		forwardDurationIncrement12inch = 80;
		forwardDurationIncrement = forwardDurationIncrement4inch;

		for (i = 50; i<150; i = i + 5) {
			motorBackLeft->setSpeed(i);
			motorBackRight->setSpeed(i);
			motorFrontLeft->setSpeed(i);
			motorFrontRight->setSpeed(i);
			delay(forwardDurationIncrement);
		}

		for (i = 150; i>50; i = i - 5) {
			motorBackLeft->setSpeed(i);
			motorBackRight->setSpeed(i);
			motorFrontLeft->setSpeed(i);
			motorFrontRight->setSpeed(i);
			delay(forwardDurationIncrement);
		}

		// STOP
		motorBackLeft->setSpeed(0);
		motorBackRight->setSpeed(0);
		motorFrontLeft->setSpeed(0);
		motorFrontRight->setSpeed(0);
		delay(5000);

		// Begin the Backward Movement Test
		//
		//		By adjusting the value of backwardDurationIncrement, 
		//		you can control how far the robot moves backward 
		//
		//		Move Values
		//			4 inches, backwardDurationIncrement = ?
		//			8 inches, backwardDurationIncrement = 40
		//			4 inches, backwardDurationIncrement = ?
		//			4 inches, backwardDurationIncrement = ?
		//
		//

		motorBackLeft->run(BACKWARD);
		motorBackRight->run(BACKWARD);
		motorFrontLeft->run(BACKWARD);
		motorFrontRight->run(BACKWARD);

		backwardDurationIncrement4inch = 20;
		backwardDurationIncrement8inch = 40;
		backwardDurationIncrement12inch = 80;
		backwardDurationIncrement = backwardDurationIncrement4inch;

		for (i = 50; i<150; i = i + 5) {
			motorBackLeft->setSpeed(i);
			motorBackRight->setSpeed(i);
			motorFrontLeft->setSpeed(i);
			motorFrontRight->setSpeed(i);
			delay(backwardDurationIncrement);
		}

		for (i = 150; i>50; i = i - 5) {
			motorBackLeft->setSpeed(i);
			motorBackRight->setSpeed(i);
			motorFrontLeft->setSpeed(i);
			motorFrontRight->setSpeed(i);
			delay(backwardDurationIncrement);
		}

		// STOP
		motorBackLeft->setSpeed(0);
		motorBackRight->setSpeed(0);
		motorFrontLeft->setSpeed(0);
		motorFrontRight->setSpeed(0);
		delay(5000);

	}

	if (testRotation == true)
	{
		// Begin the Clockwise Rotation Test
		//
		//		By adjusting the value of backwardDurationIncrement, 
		//		you can control how far the robot moves backward 
		//
		//		Rotation Values
		//			90 degrees, clockwiseDurationIncrement = 84
		//			180 degrees, clockwiseDurationIncrement = ?
		//
		//
		motorBackLeft->run(FORWARD);
		motorBackRight->run(BACKWARD);
		motorFrontLeft->run(FORWARD);
		motorFrontRight->run(BACKWARD);

		clockwiseDurationIncrement90deg = 84;
		clockwiseDurationIncrement180deg = 84;
		clockwiseDurationIncrement = clockwiseDurationIncrement90deg;

		for (i = 50; i<150; i = i + 5) {
			motorBackLeft->setSpeed(i);
			motorBackRight->setSpeed(i);
			motorFrontLeft->setSpeed(i);
			motorFrontRight->setSpeed(i);
			delay(clockwiseDurationIncrement);
		}

		for (i = 150; i>50; i = i - 5) {
			motorBackLeft->setSpeed(i);
			motorBackRight->setSpeed(i);
			motorFrontLeft->setSpeed(i);
			motorFrontRight->setSpeed(i);
			delay(clockwiseDurationIncrement);
		}

		// STOP
		motorBackLeft->setSpeed(0);
		motorBackRight->setSpeed(0);
		motorFrontLeft->setSpeed(0);
		motorFrontRight->setSpeed(0);
		delay(5000);

		// Begin the Counter-Clockwise Rotation Test
		//
		//		By adjusting the value of backwardDurationIncrement, 
		//		you can control how far the robot moves backward 
		//
		//		Rotation Values
		//			90 degrees, clockwiseDurationIncrement = 72
		//			180 degrees, clockwiseDurationIncrement = ?
		//
		//
		motorBackLeft->run(BACKWARD);
		motorBackRight->run(FORWARD);
		motorFrontLeft->run(BACKWARD);
		motorFrontRight->run(FORWARD);

		counterclockwiseDurationIncrement90deg = 72;
		counterclockwiseDurationIncrement180deg = 72;
		counterclockwiseDurationIncrement = counterclockwiseDurationIncrement90deg;

		for (i = 50; i<150; i = i + 5) {
			motorBackLeft->setSpeed(i);
			motorBackRight->setSpeed(i);
			motorFrontLeft->setSpeed(i);
			motorFrontRight->setSpeed(i);
			delay(counterclockwiseDurationIncrement);
		}

		for (i = 150; i>50; i = i - 5) {
			motorBackLeft->setSpeed(i);
			motorBackRight->setSpeed(i);
			motorFrontLeft->setSpeed(i);
			motorFrontRight->setSpeed(i);
			delay(counterclockwiseDurationIncrement);
		}

		// STOP
		motorBackLeft->setSpeed(0);
		motorBackRight->setSpeed(0);
		motorFrontLeft->setSpeed(0);
		motorFrontRight->setSpeed(0);
		delay(5000);

	}


	// End Motor Testing
	motorBackLeft->run(RELEASE);
	motorBackRight->run(RELEASE);
	motorFrontLeft->run(RELEASE);
	motorFrontRight->run(RELEASE);

}


void testSensorPositioningAndReadings()
{
	// position servos to the middle position
	//sensorServoFL.writeMicroseconds(1500);			// larger numbers move counter clockwise
	//sensorServoFR.writeMicroseconds(1500);			// larger numbers move counter clockwise
	//sensorServoBR.writeMicroseconds(1500);			// larger numbers move counter clockwise
	//delay(1000);

	// position servos to the left/front/right
	sensorServoFL.writeMicroseconds(sensorServoFLLeftPosition);				// point left,		larger numbers move counter clockwise
	sensorServoFR.writeMicroseconds(sensorServoFRFrontPosition);			// point forward,	larger numbers move counter clockwise
	sensorServoBR.writeMicroseconds(sensorServoBRBackPosition);				// point back,		larger numbers move counter clockwise
	delay(2000);

	readSensorVoltages();
	delay(3000);

	// position servos to the front/right/back
	sensorServoFL.writeMicroseconds(sensorServoFLFrontPosition);				// point forward,	larger numbers move counter clockwise
	sensorServoFR.writeMicroseconds(sensorServoFRRightPosition);				// point right,		larger numbers move counter clockwise
	sensorServoBR.writeMicroseconds(sensorServoBRRightPosition);				// point right,		larger numbers move counter clockwise
	delay(2000);

	readSensorVoltages();
	delay(3000);

}
void readSensorVoltages()
{
	const int iterations = 50;

	float distanceFL[iterations];
	float distanceFR[iterations];
	float distanceBR[iterations];

	float sumDistFL = 0.0;
	float sumDistFR = 0.0;
	float sumDistBR = 0.0;

	float avgDistFL = 0.0;
	float avgDistFR = 0.0;
	float avgDistBR = 0.0;

	float minDistFL = 5000.0;
	float minDistFR = 5000.0;
	float minDistBR = 5000.0;

	float maxDistFL = 0.0;
	float maxDistFR = 0.0;
	float maxDistBR = 0.0;

	float sumDevaitionFromMeanSqFL = 0;
	float sumDevaitionFromMeanSqFR = 0;
	float sumDevaitionFromMeanSqBR = 0;

	float stddevDistFL = 0.0;
	float stddevDistFR = 0.0;
	float stddevDistBR = 0.0;


	bool analyzeComplete = false;

	// StdDev = sqrt( sum( (n - M)^2) / N), 
	// Standard Deviation = square root of ( ( the sum of deviations from the mean squared ) / number of values ) )

	for (int i = 0; i<iterations; i++)
	{
		sensorValueFL = analogRead(A2);						//
		delay(40);
		sensorValueFR = analogRead(A1);						//
		//delay(40);
		sensorValueBR = analogRead(A0);						//
		//delay(40);
		distanceFL[i] = sensorValueFL * 0.56;			// distance = analog reading * (5.0V / 1023.0) * (512.0in / 5.0V) = analog reading * (512.0 inches / 1023.0) 
		distanceFR[i] = sensorValueFR * 0.56;			//
		distanceBR[i] = sensorValueBR * 0.56;			//

		//delay(40);

	}


	analyzeSensorData(distanceFL, iterations, 2);
	analyzeSensorData(distanceFR, iterations, 1);
	analyzeSensorData(distanceBR, iterations, 0);

	analyzeComplete = true;

}


void analyzeSensorData(float arr[], int n, int sensorPinNumber)
{

	bool swapped = true;									//
	int j = 0;												//
	float tmp;												//
	//	
	while (swapped)											//
	{														//
		swapped = false;									//
		j++;												//
		//
		for (int i = 0; i < n - j; i++)						//
		{													//
			if (arr[i] > arr[i + 1])						//
			{												//
				tmp = arr[i];								//
				arr[i] = arr[i + 1];						//
				arr[i + 1] = tmp;							//
				//
				swapped = true;								//
				//
			}												//
			//
		}													//
		//
	}														//
	//
	if (sensorPinNumber == 2)								//
	{														//
		sumDistFLSmoothed = 0.0;							//
		avgDistFLSmoothed = 0.0;							//	
		//
		for (int i = (n / 5) * 3; i<n; i++)					//
		{													//
			sumDistFLSmoothed += arr[i];					//
		}													//
		//
		avgDistFLSmoothed = sumDistFLSmoothed / (n - (n / 5) * 3);	//

		//if (arr[n] - arr[(n/5)*3] > 5) avgDistFLSmoothed = 0.0;

		//
	}														//
	//
	//
	if (sensorPinNumber == 1)								//
	{														//
		sumDistFRSmoothed = 0.0;							//
		avgDistFRSmoothed = 0.0;							//
		//
		for (int i = (n / 5) * 3; i<n; i++)					//
		{													//
			sumDistFRSmoothed += arr[i];					//
		}													//
		//
		avgDistFRSmoothed = sumDistFRSmoothed / (n - (n / 5) * 3);	//

		//if (arr[n] - arr[(n/5)*3] > 5) avgDistFRSmoothed = 0.0;

		//
	}														//
	//
	//
	if (sensorPinNumber == 0)								//		
	{														//
		sumDistBRSmoothed = 0.0;							//
		avgDistBRSmoothed = 0.0;							//
		//
		for (int i = (n / 5) * 3; i<n; i++)					//
		{													//
			sumDistBRSmoothed += arr[i];					//
		}													//
		//
		avgDistBRSmoothed = sumDistBRSmoothed / (n - (n / 5) * 3);	//

		//if (arr[n] - arr[(n/5)*3] > 5) avgDistBRSmoothed = 0.0;

		//
	}														//
	//
	//						
	//sensorVoltageFL = sensorValueFL * (5.0 / 1023.0);		// voltage = analog reading * (5.0V / 1023.0)
	//sensorVoltageFR = sensorValueFR * (5.0 / 1023.0);		//
	//sensorVoltageBR = sensorValueBR * (5.0 / 1023.0);		//
	//
	// ~9.8 mV / inch when using a +5V input
	//sensorDistanceFL = sensorValueFL * 102.4;				// distance = voltage * (512.0in / 5.0V)
	//sensorDistanceFR = sensorValueFR * 102.4;				//
	//sensorDistanceBR = sensorValueBR * 102.4;				//

	//sensorDistanceFL = sensorValueFL * 0.50048876;		// distance = analog reading * (5.0V / 1023.0) * (512.0in / 5.0V) = analog reading * (512.0 inches / 1023.0) 
	//sensorDistanceFR = sensorValueFR * 0.50048876;		//
	//sensorDistanceBR = sensorValueBR * 0.50048876;		//

	//sensorDistanceFL = sensorValueFL * 0.56;				// distance = analog reading * (5.0V / 1023.0) * (512.0in / 5.0V) = analog reading * (512.0 inches / 1023.0) 
	//sensorDistanceFR = sensorValueFR * 0.56;				//
	//sensorDistanceBR = sensorValueBR * 0.56;				//

	//sumDistFL +=  sensorDistanceFL;
	//sumDistFR +=  sensorDistanceFR;
	//sumDistBR +=  sensorDistanceBR;

	//if (sensorDistanceFL < minDistFL) minDistFL = sensorDistanceFL;
	//if (sensorDistanceFL > maxDistFL) maxDistFL = sensorDistanceFL;
	//if (sensorDistanceFR < minDistFR) minDistFR = sensorDistanceFR;
	//if (sensorDistanceFR > maxDistFR) maxDistFR = sensorDistanceFR;
	//if (sensorDistanceBR < minDistBR) minDistBR = sensorDistanceBR;
	//if (sensorDistanceBR > maxDistBR) maxDistBR = sensorDistanceBR;

	//avgDistFL = sumDistFL / iterations;
	//avgDistFR = sumDistFR / iterations;
	//avgDistBR = sumDistBR / iterations;

	//for (int i=0; i<iterations; i++)
	//{
	//	sumDevaitionFromMeanSqFL += sq(distanceFL[i] - avgDistFL); 
	//	sumDevaitionFromMeanSqFR += sq(distanceFR[i] - avgDistFR); 
	//	sumDevaitionFromMeanSqBR += sq(distanceBR[i] - avgDistBR); 
	//}

	//stddevDistFL = sqrt(sumDevaitionFromMeanSqFL/iterations);
	//stddevDistFR = sqrt(sumDevaitionFromMeanSqFR/iterations);
	//stddevDistBR = sqrt(sumDevaitionFromMeanSqBR/iterations);


}


void robotBackwardSlow(int spd, long duration)
{
	wheelsBackwardAll(spd);

	delay(duration);

	wheelsAllStop();

}


void robotForwardSlow(int spd, long duration)
{
	wheelsForwardAll(spd);

	delay(duration);

	wheelsAllStop();

}


void robotSpinCounterClockwise(int spd, long duration)
{
	// spin at speed = spd
	wheelsForwardRight(spd);
	wheelsBackwardLeft(spd);

	delay(duration);

	wheelsAllStop();
}

void robotSpinCounterClockwise90()
{
	motorBackLeft->run(BACKWARD);
	motorBackRight->run(FORWARD);
	motorFrontLeft->run(BACKWARD);
	motorFrontRight->run(FORWARD);

	int counterclockwiseDurationIncrement90deg = 72;
	int counterclockwiseDurationIncrement = counterclockwiseDurationIncrement90deg;

	for (int i = 50; i<150; i = i + 5) {
		motorBackLeft->setSpeed(i);
		motorBackRight->setSpeed(i);
		motorFrontLeft->setSpeed(i);
		motorFrontRight->setSpeed(i);
		delay(counterclockwiseDurationIncrement);
	}

	for (int i = 150; i>50; i = i - 5) {
		motorBackLeft->setSpeed(i);
		motorBackRight->setSpeed(i);
		motorFrontLeft->setSpeed(i);
		motorFrontRight->setSpeed(i);
		delay(counterclockwiseDurationIncrement);
	}

	// STOP
	motorBackLeft->setSpeed(0);
	motorBackRight->setSpeed(0);
	motorFrontLeft->setSpeed(0);
	motorFrontRight->setSpeed(0);

}

void robotSpinClockwise(int spd, long duration)
{
	// spin at speed = spd
	wheelsBackwardRight(spd);
	wheelsForwardLeft(spd);

	delay(duration);

	wheelsAllStop();
}

void robotSpinClockwise90()
{
	motorBackLeft->run(FORWARD);
	motorBackRight->run(BACKWARD);
	motorFrontLeft->run(FORWARD);
	motorFrontRight->run(BACKWARD);

	int clockwiseDurationIncrement90deg = 84;
	int clockwiseDurationIncrement = clockwiseDurationIncrement90deg;

	for (int i = 50; i<150; i = i + 5) {
		motorBackLeft->setSpeed(i);
		motorBackRight->setSpeed(i);
		motorFrontLeft->setSpeed(i);
		motorFrontRight->setSpeed(i);
		delay(clockwiseDurationIncrement);
	}

	for (int i = 150; i>50; i = i - 5) {
		motorBackLeft->setSpeed(i);
		motorBackRight->setSpeed(i);
		motorFrontLeft->setSpeed(i);
		motorFrontRight->setSpeed(i);
		delay(clockwiseDurationIncrement);
	}

	// STOP
	motorBackLeft->setSpeed(0);
	motorBackRight->setSpeed(0);
	motorFrontLeft->setSpeed(0);
	motorFrontRight->setSpeed(0);

}

void wheelsAllStop()
{
	uint8_t i = 0;

	motorBackLeft->run(FORWARD);
	motorBackRight->run(FORWARD);
	motorFrontLeft->run(FORWARD);
	motorFrontRight->run(FORWARD);

	motorBackLeft->setSpeed(i);
	motorBackRight->setSpeed(i);
	motorFrontLeft->setSpeed(i);
	motorFrontRight->setSpeed(i);

}


void wheelsLeftStop()
{
	uint8_t i = 0;

	motorBackLeft->run(FORWARD);
	//motorBackRight->run(FORWARD);
	motorFrontLeft->run(FORWARD);
	//motorFrontRight->run(FORWARD);

	motorBackLeft->setSpeed(i);
	//motorBackRight->setSpeed(i);  
	motorFrontLeft->setSpeed(i);
	//motorFrontRight->setSpeed(i);  

}

void wheelsRightStop()
{
	uint8_t i = 0;

	//motorBackLeft->run(FORWARD);
	motorBackRight->run(FORWARD);
	//motorFrontLeft->run(FORWARD);
	motorFrontRight->run(FORWARD);

	//motorBackLeft->setSpeed(i);  
	motorBackRight->setSpeed(i);
	//motorFrontLeft->setSpeed(i);  
	motorFrontRight->setSpeed(i);

}

void wheelsForwardAll(int spd)
{
	uint8_t i = spd;

	motorBackLeft->run(FORWARD);
	motorBackRight->run(FORWARD);
	motorFrontLeft->run(FORWARD);
	motorFrontRight->run(FORWARD);

	motorBackLeft->setSpeed(i);
	motorBackRight->setSpeed(i);
	motorFrontLeft->setSpeed(i);
	motorFrontRight->setSpeed(i);

}

void wheelsForwardLeft(int spd)
{
	uint8_t i = spd;

	motorBackLeft->run(FORWARD);
	//motorBackRight->run(FORWARD);
	motorFrontLeft->run(FORWARD);
	//motorFrontRight->run(FORWARD);

	motorBackLeft->setSpeed(i);
	//motorBackRight->setSpeed(i);  
	motorFrontLeft->setSpeed(i);
	//motorFrontRight->setSpeed(i);  

}

void wheelsForwardRight(int spd)
{
	uint8_t i = spd;

	//motorBackLeft->run(FORWARD);
	motorBackRight->run(FORWARD);
	//motorFrontLeft->run(FORWARD);
	motorFrontRight->run(FORWARD);

	//motorBackLeft->setSpeed(i);  
	motorBackRight->setSpeed(i);
	//motorFrontLeft->setSpeed(i);  
	motorFrontRight->setSpeed(i);


}

void wheelsBackwardAll(int spd)
{
	uint8_t i = spd;

	motorBackLeft->run(BACKWARD);
	motorBackRight->run(BACKWARD);
	motorFrontLeft->run(BACKWARD);
	motorFrontRight->run(BACKWARD);

	motorBackLeft->setSpeed(i);
	motorBackRight->setSpeed(i);
	motorFrontLeft->setSpeed(i);
	motorFrontRight->setSpeed(i);

}

void wheelsBackwardLeft(int spd)
{
	uint8_t i = spd;

	motorBackLeft->run(BACKWARD);
	//motorBackRight->run(BACKWARD);
	motorFrontLeft->run(BACKWARD);
	//motorFrontRight->run(BACKWARD);

	motorBackLeft->setSpeed(i);
	//motorBackRight->setSpeed(i);  
	motorFrontLeft->setSpeed(i);
	//motorFrontRight->setSpeed(i);  

}

void wheelsBackwardRight(int spd)
{
	uint8_t i = spd;

	//motorBackLeft->run(BACKWARD);
	motorBackRight->run(BACKWARD);
	//motorFrontLeft->run(BACKWARD);
	motorFrontRight->run(BACKWARD);

	//motorBackLeft->setSpeed(i);  
	motorBackRight->setSpeed(i);
	//motorFrontLeft->setSpeed(i);  
	motorFrontRight->setSpeed(i);

}

void armUpCenter()
{
	steppedMove(currPosR, currPosUD, destPosR, destPosUD);
	armServoMotorLeftRight.writeMicroseconds(armLRCenterPosition);
	armServoMotorUpDown.writeMicroseconds(armUDUpPosition);
}

void armFrontCenter()
{
	// move to front center
	armServoMotorLeftRight.writeMicroseconds(armLRCenterPosition);
	armServoMotorUpDown.writeMicroseconds(armUDFrontPosition);
}

void armFrontLeft()
{
	// move to front left
	armServoMotorLeftRight.writeMicroseconds(armLRLeftPosition);
	armServoMotorUpDown.writeMicroseconds(armUDFrontPosition);
}

void armFrontRight()
{
	// move to front right
	armServoMotorLeftRight.writeMicroseconds(armLRRightPosition);
	armServoMotorUpDown.writeMicroseconds(armUDFrontPosition);
}

void armBackCenter()
{
	// move to back center
	armServoMotorLeftRight.writeMicroseconds(armLRCenterPosition);
	armServoMotorUpDown.writeMicroseconds(armUDBackPosition);
}

void armBackLeft()
{
	// move to back left
	armServoMotorLeftRight.writeMicroseconds(armLRRightPosition);
	armServoMotorUpDown.writeMicroseconds(armUDBackPosition);
}

void armBackRight()
{
	// move to back right
	armServoMotorLeftRight.writeMicroseconds(armLRLeftPosition);
	armServoMotorUpDown.writeMicroseconds(armUDBackPosition);
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
	float incrStepDist[20] = { .005, .005, .010, .010, .020, .040, .080, .100, .110, .120, .120, .110, .100, .080, .040, .020, .010, .010, .005, .005 };
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
		
		armServoMotorLeftRight.writeMicroseconds(incrPositionsR[i]);
		armServoMotorUpDown.writeMicroseconds(incrPositionsUD[i]);

		delay(delayTime[i]);

	}

}