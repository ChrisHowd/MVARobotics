#include <Wire.h>;
#include <Servo.h>;

int servoPin;

int servoStop;
int servoSpeed;

int switchPin;

Servo myServo;

void setup()
{
	// program the servo motor
	servoPin = 3;
	myServo.attach(servoPin);

	servoStop = 1500;
	servoSpeed = servoStop;
	myServo.writeMicroseconds(servoSpeed);

	// program a switch
	switchPin = 8;
	pinMode(switchPin, INPUT);
	digitalWrite(switchPin, HIGH);			// use the internal resister in the Arduino to hold the Pin HIGH

}

void loop()
{
	int speedIncrement;

	// controlling the servo without a switch installed, specify values for speedIncrement
	//speedIncrement = 200;
	//moveServo(speedIncrement);
	//delay(5000); 
	//speedIncrement = -200;
	//moveServo(speedIncrement);
	//delay(5000);


	// controlling the servo with the switch installed, set speedIncrement based on the state of the switch
	speedIncrement = readSwitch();
	moveServo(speedIncrement);
}

void moveServo(int mySpeedIncr)
{
	myServo.writeMicroseconds(servoStop + mySpeedIncr);

}

int readSwitch()
{
	int pinReading;
	pinReading = digitalRead(switchPin);

	if (pinReading == HIGH)
	{
		return 200;
	}
	else
	{
		return -200;
	}
}