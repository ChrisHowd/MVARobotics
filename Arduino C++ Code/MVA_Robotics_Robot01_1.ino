#include <Wire\Wire.h>
#include <Servo\Servo.h>											// include the Arduino servo library

// Step 1: define servo motor objects and control variables
Servo leftServoMotor;												// servo motor object, back left
Servo rightServoMotor;												// servo motor object, back right

int pinLeftServo;													// pin for controlling left servo
int pinRightServo;													// pin for controlling right servo

int servoSpeedLeftStop;												// PWM setting to STOP the Back Left wheel
int servoSpeedLeftForward;											// slow forward speed
int servoSpeedLeftBackward;											// slow slow backward 

int servoSpeedRightStop;											// PWM setting to STOP the Back Right wheel
int servoSpeedRightForward;											// slow forward speed
int servoSpeedRightBackward;										// slow backward speed

// Step 2: define variables for configuring and monitoring the bump sensors
int pinSensorFL;													// Front Left bump sensor (uses digital pin 3)
int pinSensorFR;													// Front Right bump sensor (uses digital pin 4)
int pinSensorBL;													// Back Left bump sensor (uses digital pin 5)
int pinSensorBR;													// Back Right bump sensor (uses digital pin 6)

int sensorValueFL;													// Value (Reading) for the Front Left bump sensor 
int sensorValueFR;													// Value (Reading) for the Front Right bump sensor 
int sensorValueBL;													// Value (Reading) for the Back Left bump sensor 
int sensorValueBR;													// Value (Reading) for the Back Right bump sensor 

bool bumpersClear;


// Step 3 - define variables for wheel speed diagnostics testing
bool wheelSpeedDiagnostics;											// true/false to determine if a wheel speed diagnostics test is running 
bool wheelSpeedDiagnosticsCalculatingRPM;							// true/false if wheel speed diagnostics is running for RPM calculations
long diagnosticSpeedTestWaitTime;									// time duration for a diagnostics test
																	//		60 seconds (60000 milliseconds) is used for calculating RPMs
																	//		10 seconds is used when just cycling through the diagnostics settings
int testSpeed;														// speed used during wheel speed diagnostics test (starts slow and increases)
int diagnosticSequenceCounter;										// wheel speed diagnostics testing sequence counter 
int maxDiagnosticCounter;											// the number of diagnostic tests


// Step 4 - define variables for the final program using bump sensors
bool liveMode;														// when liveMode == true, the robot moves autonomously and uses sensor inputs
bool robotInitialized;												// used to ensure that the robot has been initialized

int robotStatus;													// used to check what the robot is doing

long currentTime;													// the current time counter (milliseconds since program started)
long waitTime;														// time duration to pause robot after bumping an object (in milliseconds)
long previousTime;													// the time at which the previous bump event occurred (milliseconds since program started)
long resumeMovementTime;											// the time at which movement can resume
long keepMoving;

// Step 5 - shut down switch
bool shutDown;
int pinShutdown;
int shutdownReading;

void setup()
{
	// Step 1 - set up the servo motors to PWM pins 10 and 11
	pinLeftServo = 11;
	pinRightServo = 10;

	leftServoMotor.attach(pinLeftServo);
	rightServoMotor.attach(pinRightServo);

	servoSpeedLeftStop = 1500;										// Stop Left Wheel
	servoSpeedRightStop = 1500;										// Stop Right Wheel

	servoSpeedLeftForward = servoSpeedLeftStop + 75;				// forward left wheel
	servoSpeedRightForward = servoSpeedRightStop - 71;				// forward right wheel

	servoSpeedLeftBackward = servoSpeedLeftStop - 40;				// slow backward left wheel
	servoSpeedRightBackward = servoSpeedRightStop + 40;				// slow backward right wheel


	// Step 2 - set up the bump sensors on pins 3-6
	pinSensorFL = 4;												// for the Front Left bump sensor, use digital pin 4
	pinSensorFR = 3;												// for the Front Right bump sensor, use digital pin 3
	pinSensorBL = 5;												// for the Back Left bump sensor, use digital pin 5
	pinSensorBR = 6;												// for the Back Right bump sensor, use digital pin 6

	pinMode(pinSensorFL, INPUT);									// specify that the pin will be used for INPUT
	digitalWrite(pinSensorFL, HIGH);								// set the pin HIGH so that pull-up resistor is enabled
	pinMode(pinSensorFR, INPUT);									// specify that the pin will be used for INPUT
	digitalWrite(pinSensorFR, HIGH);								// set the pin HIGH so that pull-up resistor is enabled
	pinMode(pinSensorBL, INPUT);									// specify that the pin will be used for INPUT
	digitalWrite(pinSensorBL, HIGH);								// set the pin HIGH so that pull-up resistor is enabled
	pinMode(pinSensorBR, INPUT);									// specify that the pin will be used for INPUT
	digitalWrite(pinSensorBR, HIGH);								// set the pin HIGH so that pull-up resistor is enabled


	// Step 3 - assign wheel speed diagnostics settings
	wheelSpeedDiagnostics = false;									// run routines for checking wheel turning speeds
	if (wheelSpeedDiagnostics == true)
	{
		liveMode = false;											// do not run autonomously if running wheel speed diagnostics tests
	}
	else
	{
		liveMode = true;											// run autonomously using the bump sensors 
	}

	diagnosticSequenceCounter = 1;									// the counter controls what test is running, as follows
	maxDiagnosticCounter = 8;										// the number of diagnostic tests

	wheelSpeedDiagnosticsCalculatingRPM = false;					// when true, run diagnostics test for 60 seconds, otherwise run 10 seconds
	if (wheelSpeedDiagnosticsCalculatingRPM == true)				//
	{
		diagnosticSpeedTestWaitTime = 60000;						// 60 seconds, run wheel speed test for 60 seconds to calculate (count) RPM

	}
	else
	{
		diagnosticSpeedTestWaitTime = 10000;						// 10 seconds, run wheel speed test for 10 seconds

	}


	// Step 4 - assign live mode settings
	currentTime = millis();											// get a timer reading in milliseconds. this is how long the program instance has been running
	resumeMovementTime = currentTime;								// when the program starts, the robot has no resume movement delay 
	previousTime = currentTime;										// when the program starts, the robot has had no previous bump sersor triggers
	waitTime = 5000;												// there is a 5000 milliseconds (5 second) delay when the robot bumps into something 

	robotStatus = 0;												// robot has not been initialized. The full list of value settings for robotStatus are:
																	//	0:	robot has not been initialized
																	//	1:	robot is moving normally
																	//	2:	robot is stopped because a bump sensor was triggered
																	//	3:	robot is changing course after a bump sensor was triggered
																	//	4:	robot bumped a sensor while trying to change course after bumping a sensor

	robotInitialized = false;										// ensure that the initialize routine is called in Loop()

	pinShutdown = 8;												// use digital pin 8 for the shutdown switch
	pinMode(pinShutdown, INPUT);									// we will read the pin as a switch
	digitalWrite(pinShutdown, HIGH);								// set the pin HIGH so that pull-up resistor is enabled
	shutdownReading = HIGH;
	shutDown = false;
}

void loop()
{
	if (shutDown == false)
	{
		shutdownReading = digitalRead(pinShutdown);
		if (shutdownReading == LOW)
		{
			liveMode = false;
			shutDown = true;
		}
	}

	// calibrate the wheel speed
	if (wheelSpeedDiagnostics == true)
	{
		// enter the diagnostics testing routine to calibrate wheel speeds
		diagnosticsTesting();
	}


	// Control based on sensor inputs (not running in demoMode)
	if (liveMode == true)
	{
		if (robotInitialized == false)
		{
			wheelsAllStop();									// ensure that all servos are stopped
			delay(5000);										// wait for 5 seconds

			wheelsForwardAll(1);								// start moving forward at the slowest speed

			robotInitialized = true;							// set the boolean for initialized to true
			robotStatus = 1;									// set the status to moving normally
		}

		checkBumpSensors();										// read the bump sensor pins

		// if any of the bump sensors has been hit 
		if(sensorValueFL == LOW || sensorValueFR == LOW || sensorValueBL == LOW || sensorValueBR == LOW)
		{
			// if the robot has already stopped in response to a bumped sensor, then maybe it can resume moving
			if (robotStatus == 2)
			{
				resumeMovement();
			}

			// the robot is either trying to resume (status = 3), is moving normally (status = 1), or bumped a sensor while trying to resume (robotStatus = 4)  
			else
			{
				wheelsAllStop();									// stop the robot

				//when a bumper is hit
				//	1.	check to see if the robot was trying to maneuver after bumping a sensor when it bumped the current sensor (might be stuck)
				//	2.	set resumeMovementTime
				//	3.	set robotStatus
				
				if (robotStatus == 3 || robotStatus == 4)
				{
					robotStatus = 4;								// status is hit a bumper wihile trying to resume moving, could be stuck
					resumeMovement();								

				}
				else
				{
					robotStatus = 2;								// status is waiting to resume (bumper hit)
				}
				
				currentTime = millis();								// get the time millis()
				resumeMovementTime = currentTime + waitTime;		// calculate the time when the robot will resume moving

			}

		}

	}

}


void resumeMovement()
{
	//check the current time and see how much time has passed since the last time the robot bumped into something
	currentTime = millis();

	if (currentTime > resumeMovementTime)
	{
		if (robotStatus == 2)
		{
			robotStatus = 3;										// update status - try to resume moving
		}


		// ==========================
		// see which bumpers were hit
		// ==========================
		

		if (sensorValueFL == LOW && sensorValueFR == LOW)			//	both front bumpers
		{

			if (robotBackward(1, 2000) == true)						// backup for 2 seconds, returns true as long as it didn't hit anything
			{
				
				if (robotSpinLeft(1, 1500) == true)					// spin clockwise for 1.5 seconds
				{
					wheelsForwardAll(1);							// then start moving forward again and set robotStatus
					robotStatus = 1;
				}
				else robotStatus = 4;								// bumped a sensor while trying to resume moving

			}

			else robotStatus = 4;								// bumped a sensor while trying to resume moving
		}


		if(sensorValueBR == LOW && sensorValueBR == LOW)			// both back bumpers
		{

			if (robotForwardAll(1, 2000) == true)					// forward for 2 seconds, returns true as long as it didn't hit anything
			{

				if (robotSpinRight(1, 1500) == true)				// spin counter-clockwise for 1.5 seconds
				{
					wheelsForwardAll(1);							// then start moving forward again and set robotStatus
					robotStatus = 1;
				}
				else robotStatus = 4;								// bumped a sensor while trying to resume moving

			}

			else robotStatus = 4;									// bumped a sensor while trying to resume moving

		}

		
		if(sensorValueFL == 0)										// front left bumper
		{

			if (robotRightTurnBackward(1, 2000) == true)			// move back-right for 2 seconds, returns true as long as it didn't hit anything
			{

				if (robotBackward(1, 1000) == true)					// move straignt back for 1 second, returns true as long as it didn't hit anything
				{

					if (robotSpinRight(1, 1500) == true)			// spin counter-clockwise for 1.5 seconds
					{
						wheelsForwardAll(1);						// then start moving forward again and set robotStatus
						robotStatus = 1;
					}

					else robotStatus = 4;							// bumped a sensor while trying to resume moving

				}

				else robotStatus = 4;								// bumped a sensor while trying to resume moving

			}

			else robotStatus = 4;									// bumped a sensor while trying to resume moving

		}

		// front right bumper
		if(sensorValueFR == 0)
		{

			if (robotLeftTurnBackward(1, 2000) == true)				// move back-left for 2 seconds, returns true as long as it didn't hit anything
			{

				if (robotBackward(1, 1000) == true)					// move straight back for 1 seconds, returns true as long as it didn't hit anything
				{

					if (robotSpinLeft(1, 1500) == true)				// spin clockwise for 1.5 seconds
					{
						wheelsForwardAll(1);						// then start moving forward again and set robotStatus
						robotStatus = 1;
					}

					else robotStatus = 4;							// bumped a sensor while trying to resume moving

				}

				else robotStatus = 4;								// bumped a sensor while trying to resume moving

			}

			else robotStatus = 4;								// bumped a sensor while trying to resume moving

		}


		// back left bumper
		if(sensorValueBL == 0)
		{

			if (robotRightTurnForward(1, 500) == true)				// pull forward-right for 1/2 second, returns true as long as it didn't hit anything
			{
				wheelsForwardAll(1);								// then start moving forward again and set robotStatus
				robotStatus = 1;
			}

			else robotStatus = 4;									// bumped a sensor while trying to resume moving

		}

		// back right bumper
		if(sensorValueFR == 0)
		{

			if (robotLeftTurnForward(1, 500) == true)				// pull forward-right for 1/2 second, returns true as long as it didn't hit anything
			{
				wheelsForwardAll(1);								// then start moving forward again and set robotStatus
				robotStatus = 1;
			}

			else robotStatus = 4;									// bumped a sensor while trying to resume moving

		}


		// both left bumpers
		if (sensorValueFL == 0 && sensorValueBL == 0)
		{
			// backup straight back for 5 inches
			// then backup turning the back end of the robot to the Right (right wheel stopped) for 45 degrees
			// then backup straight back for 8 inches
			// then spin clockwise 90-120 degrees
			// then start moving forward again

		}

		// both right bumpers
		if (sensorValueFR == 0 && sensorValueBR == 0)
		{
			// backup straight back for 5 inches
			// then backup turning the back end of the robot to the Left (left wheel stopped) for 45 degrees
			// then backup straight back for 8 inches
			// then spin counter-clockwise 90-120 degrees
			// then start moving forward again

		}

	}

}


void diagnosticsTesting()
{

	currentTime = millis();

	// check to see if the wait time has occurred since the last diagnostic
	if (currentTime >= (previousTime + waitTime))
	{
		// set previousTime equal to currentTime
		previousTime = currentTime;

		switch (diagnosticSequenceCounter)
		{
		case 1:
			// stop
			robotStop();
			waitTime = 10000;
			break;

		case 2:
			// move forward slow
			wheelsForwardAll(1);
			waitTime = diagnosticSpeedTestWaitTime;
			break;

		case 3:
			// stop
			robotStop();
			waitTime = 10000;
			break;

		case 4:
			// move back slow
			wheelsBackwardAll(1);
			waitTime = diagnosticSpeedTestWaitTime;
			break;

		case 5:
			// stop
			robotStop();
			waitTime = 10000;
			break;

		default:
			robotStop();
			waitTime = 10000;
			break;

		}

		// increment the sequence counter
		diagnosticSequenceCounter += 1;

		// check for exceeding max actions
		if (diagnosticSequenceCounter > maxDiagnosticCounter)
		{
			// reset the action sequence counter to zero
			diagnosticSequenceCounter = 1;
		}

	}

}


void robotStop()
{
	wheelsAllStop();												// stop both servos
}

bool robotForwardAll(int spd, long timeDuration)
{
	wheelsForwardAll(1);											// backup straight back for 2 seconds

	return robotKeepMoving(timeDuration);							// continue current movement for timeDuration
																	//		return false if a bumber was hit
}


bool robotBackward(int spd, long timeDuration)
{
	wheelsBackwardAll(1);											// backup straight back for 2 seconds

	return robotKeepMoving(timeDuration);							// continue current movement for timeDuration
																	//		return false if a bumber was hit
}


bool robotLeftTurnForward(int spd, long timeDuration)
{
	// turn at speed = spd
	wheelsForwardRight(spd);
	wheelsLeftStop();

	return robotKeepMoving(timeDuration);							// continue current movement for timeDuration
																	//		return false if a bumber was hit
}


bool robotRightTurnForward(int spd, long timeDuration)
{
	// turn at speed = spd
	wheelsForwardLeft(spd);
	wheelsRightStop();

	return robotKeepMoving(timeDuration);							// continue current movement for timeDuration
																	//		return false if a bumber was hit
}


bool robotLeftTurnBackward(int spd, long timeDuration)
{
	// turn at speed = spd
	wheelsBackwardRight(spd);
	wheelsLeftStop();

	return robotKeepMoving(timeDuration);							// continue current movement for timeDuration
																	//		return false if a bumber was hit
}


bool robotRightTurnBackward(int spd, long timeDuration)
{
	// turn at speed = spd
	wheelsBackwardLeft(spd);
	wheelsRightStop();

	return robotKeepMoving(timeDuration);							// continue current movement for timeDuration
																	//		return false if a bumber was hit
}


bool robotSpinLeft(int spd, long timeDuration)
{
	// spin at speed = spd
	wheelsForwardLeft(spd);
	wheelsBackwardRight(spd);

	return robotKeepMoving(timeDuration);							// continue current movement for timeDuration
																	//		return false if a bumber was hit
}


bool robotSpinRight(int spd, long timeDuration)
{
	// spin at speed = spd
	wheelsForwardRight(spd);
	wheelsBackwardLeft(spd);

	return robotKeepMoving(timeDuration);							// continue current movement for timeDuration
																	//		return false if a bumber was hit
}


bool robotKeepMoving(long duration)
{
	currentTime = millis();
	keepMoving = currentTime + duration;
	bumpersClear = true;

	if (duration > 450)
	{
		delay(350);													// allow just enough time for bump-switch to move off the object/wall  
	}

	while (currentTime < keepMoving)
	{
		currentTime = millis();
		checkBumpSensors();

		// if any on the bump sensors was triggered
		if (sensorValueFL == LOW || sensorValueFR == LOW || sensorValueBL == LOW || sensorValueBR == LOW)
		{
			bumpersClear = false;

		}

	}

	return bumpersClear;

}

void checkBumpSensors()
{
	sensorValueFL = digitalRead(pinSensorFL);
	sensorValueFR = digitalRead(pinSensorFR);
	sensorValueBL = digitalRead(pinSensorBL);
	sensorValueBR = digitalRead(pinSensorBR);

}


void wheelsAllStop()
{
	leftServoMotor.writeMicroseconds(servoSpeedLeftStop);
	rightServoMotor.writeMicroseconds(servoSpeedRightStop);
}


void wheelsLeftStop()
{
	leftServoMotor.writeMicroseconds(servoSpeedLeftStop);
}


void wheelsRightStop()
{
	rightServoMotor.writeMicroseconds(servoSpeedRightStop);
}


void wheelsForwardAll(int spd)
{
	switch (spd)
	{
	case 1:
		leftServoMotor.writeMicroseconds(servoSpeedLeftForward);
		rightServoMotor.writeMicroseconds(servoSpeedRightForward);
		break;

	default:
		leftServoMotor.writeMicroseconds(servoSpeedLeftForward);
		rightServoMotor.writeMicroseconds(servoSpeedRightForward);
		break;
	}

}


void wheelsForwardLeft(int spd)
{
	//	leftServoMotor.writeMicroseconds(servoSpeedLeftForward);

	switch (spd)
	{
	case 1:
		leftServoMotor.writeMicroseconds(servoSpeedLeftForward);
		break;

	default:
		leftServoMotor.writeMicroseconds(servoSpeedLeftForward);
		break;
	}

}


void wheelsForwardRight(int spd)
{
	//	Servo_WheelFR.write(wheelFR_fwd1);
	//	rightServoMotor.writeMicroseconds(servoSpeedRightForward);

	switch (spd)
	{
	case 1:
		rightServoMotor.writeMicroseconds(servoSpeedRightForward);
		break;

	default:
		rightServoMotor.writeMicroseconds(servoSpeedRightForward);
		break;
	}

}


void wheelsBackwardAll(int spd)
{
	//	leftServoMotor.writeMicroseconds(servoSpeedLeftBackward);
	//	rightServoMotor.writeMicroseconds(servoSpeedRightBackward);
	switch (spd)
	{
	case 1:
		leftServoMotor.writeMicroseconds(servoSpeedLeftBackward);
		rightServoMotor.writeMicroseconds(servoSpeedRightBackward);
		break;

	default:
		leftServoMotor.writeMicroseconds(servoSpeedLeftBackward);
		rightServoMotor.writeMicroseconds(servoSpeedRightBackward);
		break;
	}

}


void wheelsBackwardLeft(int spd)
{
	//	leftServoMotor.writeMicroseconds(servoSpeedLeftBackward);

	switch (spd)
	{
	case 1:
		leftServoMotor.writeMicroseconds(servoSpeedLeftBackward);
		break;

	default:
		leftServoMotor.writeMicroseconds(servoSpeedLeftBackward);
		break;
	}

}


void wheelsBackwardRight(int spd)
{
	//	rightServoMotor.writeMicroseconds(servoSpeedRightBackward);

	switch (spd)
	{
	case 1:
		rightServoMotor.writeMicroseconds(servoSpeedRightBackward);
		break;

	default:
		rightServoMotor.writeMicroseconds(servoSpeedRightBackward);
		break;
	}


}