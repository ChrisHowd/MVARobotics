#include <Servo\Servo.h>

int pinDataAvailableRed;
int pinMessageReceivedGreen;

int pinServoMotor;
Servo myServo;

int messageIn;
int messageOut;

void setup()
{
	pinDataAvailableRed = 10;
	pinMessageReceivedGreen = 3;

	pinServoMotor = 11;

	pinMode(pinDataAvailableRed, OUTPUT);
	pinMode(pinMessageReceivedGreen, OUTPUT);
	
	myServo.attach(pinServoMotor);

	Serial.begin(9600);
}

void loop()
{
	if (Serial.available()>0)
	{
		analogWrite(pinDataAvailableRed, 255);

		myServo.writeMicroseconds(1600);

		messageIn = Serial.read();



		delay(5000);


		if (messageIn == 'G')
		{
			analogWrite(pinMessageReceivedGreen, 255);
			myServo.writeMicroseconds(2000);
			delay(5000);

		}
		else
		{
			analogWrite(pinMessageReceivedGreen, 0);
			myServo.writeMicroseconds(1500);
		}

	}
	else
	{
		analogWrite(pinDataAvailableRed, 0);
		myServo.writeMicroseconds(1500);
	}

}