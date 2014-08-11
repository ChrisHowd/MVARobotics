/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Mega 2560 or Mega ADK, Platform=avr, Package=arduino
*/

#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
#define __AVR_ATmega2560__
#define ARDUINO 105
#define ARDUINO_MAIN
#define __AVR__
#define __avr__
#define F_CPU 16000000L
#define __cplusplus
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__

#define __builtin_va_list
#define __builtin_va_start
#define __builtin_va_end
#define __DOXYGEN__
#define __attribute__(x)
#define NOINLINE __attribute__((noinline))
#define prog_void
#define PGM_VOID_P int
            
typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}

//
//
void initializeRobot();
void mapArea();
void calcRobotCoordinates();
void moveToCenterPosition();
float distanceToWallOne();
float distanceToWallTwo();
float distanceToWallThree();
float distanceToWallFour();
void designateWallOne();
void checkForIntruder();
void stopIntruder();
void testArmMovement();
void testGearmotors();
void testSensorPositioningAndReadings();
void readSensorVoltages();
void analyzeSensorData(float arr[], int n, int sensorPinNumber);
void robotBackwardSlow(int spd, long duration);
void robotForwardSlow(int spd, long duration);
void robotSpinCounterClockwise(int spd, long duration);
void robotSpinCounterClockwise90();
void robotSpinClockwise(int spd, long duration);
void robotSpinClockwise90();
void wheelsAllStop();
void wheelsLeftStop();
void wheelsRightStop();
void wheelsForwardAll(int spd);
void wheelsForwardLeft(int spd);
void wheelsForwardRight(int spd);
void wheelsBackwardAll(int spd);
void wheelsBackwardLeft(int spd);
void wheelsBackwardRight(int spd);
void armUpCenter();
void armFrontCenter();
void armFrontLeft();
void armFrontRight();
void armBackCenter();
void armBackLeft();
void armBackRight();
void steppedMove(int currPosR, int currPosUD, int destPosR, int destPosUD);

#include "C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "C:\Program Files (x86)\Arduino\hardware\arduino\variants\mega\pins_arduino.h" 
#include "C:\Users\cahowd\SkyDrive\Documents\Robotics\Code\MVA_Robotics_Robot02_1\MVA_Robotics_Robot02_1.ino"
#endif
