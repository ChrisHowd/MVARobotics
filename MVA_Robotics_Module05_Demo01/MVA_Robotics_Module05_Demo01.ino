#include <Wire\Wire.h>

int sensorPin;
int analogReading;
float sensorVoltage;
float sensorDistance;
float distanceMultiplierVoltsPerInch;



void setup()
{
	sensorPin = A0;
	sensorVoltage = 0;
	sensorDistance = 0;
	distanceMultiplierVoltsPerInch = 5.0/512.0;

	pinMode(sensorPin, INPUT);

}

void loop()
{
	analogReading = analogRead(sensorPin);			// int value between 0 and 1023
													//		voltage = analogReding/205

	sensorVoltage = (5.0 / 1023.0) * analogReading;
	sensorDistance = sensorVoltage / distanceMultiplierVoltsPerInch;
	delay(500);
}
