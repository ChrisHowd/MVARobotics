#include <Wire\Wire.h>
#include <Servo\Servo.h>

int pinSensorFL;
int pinSensorFR;
int pinSensorBL;
int pinSensorBR;

int sensorValueFL;
int sensorValueFR;
int sensorValueBL;
int sensorValueBR;

int robotState;

int myServoPin;
int myServoSpeed;
Servo myServo;

void setup()
{
	myServoPin = 11;
	myServo.attach(myServoPin);
	myServoSpeed = 200;
	myServo.writeMicroseconds(1500 + myServoSpeed);

	pinSensorFL = 4;
	pinSensorFR = 5;
	pinSensorBL = 6;
	pinSensorBR = 7;

	pinMode(pinSensorFL, INPUT);
	digitalWrite(pinSensorFL, HIGH);
	pinMode(pinSensorFR, INPUT);
	digitalWrite(pinSensorFR, HIGH);
	pinMode(pinSensorBL, INPUT);
	digitalWrite(pinSensorBL, HIGH);
	pinMode(pinSensorBR, INPUT);
	digitalWrite(pinSensorBR, HIGH);

}

void loop()
{
	robotState = readBumpSensors();
  
	myServo.writeMicroseconds(1500 + myServoSpeed*robotState);

}

int readBumpSensors()
{
	sensorValueFL = digitalRead(pinSensorFL);
	sensorValueFR = digitalRead(pinSensorFR);
	sensorValueBL = digitalRead(pinSensorBL);
	sensorValueBR = digitalRead(pinSensorBR);

	if (sensorValueFL == LOW || sensorValueFR == LOW || sensorValueBL == LOW || sensorValueBR == LOW)
	{
		return LOW;
	}
	else
	{
		return HIGH;
	}

}
