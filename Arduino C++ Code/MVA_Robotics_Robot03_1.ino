#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
//
//  Instantiate an Adafruit_PWMServoDriver object
//
//  When the object is instantiated without specifying an address parameter, 
//  the object uses the default address 0x40. You can also specify the address
//  if you want. 
//
//  Specifying the address is required when chaining boards and when using
//  a board that has been hardware configured with an offset from the base
//  I2C address of 0x40. Altering the address can also be done to avoid a 
//  conflict with another I2C board. 

Adafruit_PWMServoDriver pwmServoDriverFrontLegs = Adafruit_PWMServoDriver(0x40);// Adafruit_PWMServoDriver(0x40) - front four legs
Adafruit_PWMServoDriver pwmServoDriverRearLegs = Adafruit_PWMServoDriver(0x41); // Adafruit_PWMServoDriver(0x41) - rear four legs

const int Leg2_R_ServoMotor1_ChannelNum = 0;						// 2nd Leg, Right Side, Motor 1, Channel 0 on Adafruit_PWMServoDriver(0x40)
const int Leg2_R_ServoMotor2_ChannelNum = 1;						// 2nd Leg, Right Side, Motor 2, Channel 1 on Adafruit_PWMServoDriver(0x40)
const int Leg2_R_ServoMotor3_ChannelNum = 2;						// 2nd Leg, Right Side, Motor 3, Channel 2 on Adafruit_PWMServoDriver(0x40)

const int Leg1_R_ServoMotor1_ChannelNum = 4;						// 1st Leg, Right Side, Motor 1, Channel 4 on Adafruit_PWMServoDriver(0x40)
const int Leg1_R_ServoMotor2_ChannelNum = 5;						// 1st Leg, Right Side, Motor 2, Channel 5 on Adafruit_PWMServoDriver(0x40)
const int Leg1_R_ServoMotor3_ChannelNum = 6;						// 1st Leg, Right Side, Motor 3, Channel 6 on Adafruit_PWMServoDriver(0x40)

const int Leg1_L_ServoMotor1_ChannelNum = 8;						// 1st Leg, Left Side, Motor 1, Channel 8 on Adafruit_PWMServoDriver(0x40)
const int Leg1_L_ServoMotor2_ChannelNum = 9;						// 1st Leg, Left Side, Motor 2, Channel 9 on Adafruit_PWMServoDriver(0x40)
const int Leg1_L_ServoMotor3_ChannelNum = 10;						// 1st Leg, Left Side, Motor 3, Channel 10 on Adafruit_PWMServoDriver(0x40)

const int Leg2_L_ServoMotor1_ChannelNum = 12;						// 2nd Leg, Left Side, Motor 1, Channel 12 on Adafruit_PWMServoDriver(0x40)
const int Leg2_L_ServoMotor2_ChannelNum = 13;						// 2nd Leg, Left Side, Motor 2, Channel 13 on Adafruit_PWMServoDriver(0x40)
const int Leg2_L_ServoMotor3_ChannelNum = 14;						// 2nd Leg, Left Side, Motor 3, Channel 14 on Adafruit_PWMServoDriver(0x40)

const int Leg4_L_ServoMotor1_ChannelNum = 0;						// 4th Leg, Left Side, Motor 1, Channel 0 on Adafruit_PWMServoDriver(0x41)
const int Leg4_L_ServoMotor2_ChannelNum = 1;						// 4th Leg, Left Side, Motor 2, Channel 1 on Adafruit_PWMServoDriver(0x41)
const int Leg4_L_ServoMotor3_ChannelNum = 2;						// 4th Leg, Left Side, Motor 3, Channel 2 on Adafruit_PWMServoDriver(0x41)

const int Leg3_L_ServoMotor1_ChannelNum = 4;						// 3rd Leg, Left Side, Motor 1, Channel 4 on Adafruit_PWMServoDriver(0x41)
const int Leg3_L_ServoMotor2_ChannelNum = 5;						// 3rd Leg, Left Side, Motor 2, Channel 5 on Adafruit_PWMServoDriver(0x41)
const int Leg3_L_ServoMotor3_ChannelNum = 6;						// 3rd Leg, Left Side, Motor 3, Channel 6 on Adafruit_PWMServoDriver(0x41)

const int Leg3_R_ServoMotor1_ChannelNum = 8;						// 3rd Leg, Right Side, Motor 1, Channel 8 on Adafruit_PWMServoDriver(0x41)
const int Leg3_R_ServoMotor2_ChannelNum = 9;						// 3rd Leg, Right Side, Motor 2, Channel 9 on Adafruit_PWMServoDriver(0x41)
const int Leg3_R_ServoMotor3_ChannelNum = 10;						// 3rd Leg, Right Side, Motor 3, Channel 10 on Adafruit_PWMServoDriver(0x41)

const int Leg4_R_ServoMotor1_ChannelNum = 12;						// 4th Leg, Right Side, Motor 1, Channel 12 on Adafruit_PWMServoDriver(0x41)
const int Leg4_R_ServoMotor2_ChannelNum = 13;						// 4th Leg, Right Side, Motor 2, Channel 13 on Adafruit_PWMServoDriver(0x41)
const int Leg4_R_ServoMotor3_ChannelNum = 14;						// 4th Leg, Right Side, Motor 3, Channel 14 on Adafruit_PWMServoDriver(0x41)

const int archUp_Command = 1;										//	1.	arch up - arch body up off ground
const int crouchDown_Command = 2;									//	2.	crouch down - crouch body down to ground
const int leftSideDown_Command = 3;									//	3.	left side down right side up
const int rightSideDown_Command = 4;								//	4.	right side down left side up
const int standStill_Command = 5;									//	5.	stand still ("home" position for servos)
const int twistLeft_Command = 6;									//	6.	twist body left
const int twistRight_Command = 7;									//	7.	twist body right
const int frontEndUp_Command = 8;									//	8.	front up with rear down
const int backEndUp_Command = 9;									//	9.	rear up with front down

const int idleRandom_Command = 10;									//	10.	home position idle - idle leg twitches and random movements
const int probeFrontLegs_Command = 11;								//	11.	arch back and reach/probe with front legs

const int r2l2ForwardWalking_Command = 12;							//	12.	left/right walking forward with two legs on each side moving 
const int oneLegForwardWalking_Command = 13;						//	13.	rearward-most leg takes step forward walking forward
const int turnLeft_Command = 14;									//	14.	turn left - smaller steps on left (25%) 
const int turnHardLeft_Command = 15;								//	15.	turn hard left
const int turnRight_Command = 16;									//	16.	turn right - smaller steps on right (25)
const int turnHardRight_Command = 17;								//	17.	turn hard right
const int rotateLeft_Command = 18;									//	18.	rotate/spin left - back-step on left while stepping forward on right
const int rotateRight_Command = 19;									//	19.	rotate/spin right - back-step on right while stepping forward on left

const int r2l2BackwardWalking_Command = 20;							//	20.	left/right walking backward with two legs on each side moving 
const int oneLegBackwardWalking_Command = 21;						//	21.	forward-most leg takes step back walking backward



int legSpeed01_DelayTime;
int legSpeed02_DelayTime;
int legSpeed03_DelayTime;
int legSpeed04_DelayTime;
int legSpeed05_DelayTime;
int legSpeed06_DelayTime;
int legSpeed07_DelayTime;
int legSpeed08_DelayTime;
int legSpeed09_DelayTime;
int legSpeed10_DelayTime;
int legSpeed11_DelayTime;
int legSpeed12_DelayTime;
int legSpeed13_DelayTime;

int legSpeedDefault;
int legSpeed;

int Leg1_L_ServoMotor1_Home;
int Leg1_L_ServoMotor2_Home;
int Leg1_L_ServoMotor3_Home;

int Leg2_L_ServoMotor1_Home;
int Leg2_L_ServoMotor2_Home;
int Leg2_L_ServoMotor3_Home;

int Leg3_L_ServoMotor1_Home;
int Leg3_L_ServoMotor2_Home;
int Leg3_L_ServoMotor3_Home;

int Leg4_L_ServoMotor1_Home;
int Leg4_L_ServoMotor2_Home;
int Leg4_L_ServoMotor3_Home;

int Leg1_R_ServoMotor1_Home;
int Leg1_R_ServoMotor2_Home;
int Leg1_R_ServoMotor3_Home;

int Leg2_R_ServoMotor1_Home;
int Leg2_R_ServoMotor2_Home;
int Leg2_R_ServoMotor3_Home;

int Leg3_R_ServoMotor1_Home;
int Leg3_R_ServoMotor2_Home;
int Leg3_R_ServoMotor3_Home;

int Leg4_R_ServoMotor1_Home;
int Leg4_R_ServoMotor2_Home;
int Leg4_R_ServoMotor3_Home;

int Leg1_L_ServoMotor1_Standing;
int Leg1_L_ServoMotor2_Standing;
int Leg1_L_ServoMotor3_Standing;

int Leg2_L_ServoMotor1_Standing;
int Leg2_L_ServoMotor2_Standing;
int Leg2_L_ServoMotor3_Standing;

int Leg3_L_ServoMotor1_Standing;
int Leg3_L_ServoMotor2_Standing;
int Leg3_L_ServoMotor3_Standing;

int Leg4_L_ServoMotor1_Standing;
int Leg4_L_ServoMotor2_Standing;
int Leg4_L_ServoMotor3_Standing;

int Leg1_R_ServoMotor1_Standing;
int Leg1_R_ServoMotor2_Standing;
int Leg1_R_ServoMotor3_Standing;

int Leg2_R_ServoMotor1_Standing;
int Leg2_R_ServoMotor2_Standing;
int Leg2_R_ServoMotor3_Standing;

int Leg3_R_ServoMotor1_Standing;
int Leg3_R_ServoMotor2_Standing;
int Leg3_R_ServoMotor3_Standing;

int Leg4_R_ServoMotor1_Standing;
int Leg4_R_ServoMotor2_Standing;
int Leg4_R_ServoMotor3_Standing;

int Leg1_R_ServoMotor1_CrouchPos;
int Leg1_R_ServoMotor2_CrouchPos;
int Leg1_R_ServoMotor3_CrouchPos;

int Leg2_R_ServoMotor1_CrouchPos;
int Leg2_R_ServoMotor2_CrouchPos;
int Leg2_R_ServoMotor3_CrouchPos;

int Leg3_R_ServoMotor1_CrouchPos;
int Leg3_R_ServoMotor2_CrouchPos;
int Leg3_R_ServoMotor3_CrouchPos;

int Leg4_R_ServoMotor1_CrouchPos;
int Leg4_R_ServoMotor2_CrouchPos;
int Leg4_R_ServoMotor3_CrouchPos;

int Leg1_L_ServoMotor1_CrouchPos;
int Leg1_L_ServoMotor2_CrouchPos;
int Leg1_L_ServoMotor3_CrouchPos;

int Leg2_L_ServoMotor1_CrouchPos;
int Leg2_L_ServoMotor2_CrouchPos;
int Leg2_L_ServoMotor3_CrouchPos;

int Leg3_L_ServoMotor1_CrouchPos;
int Leg3_L_ServoMotor2_CrouchPos;
int Leg3_L_ServoMotor3_CrouchPos;

int Leg4_L_ServoMotor1_CrouchPos;
int Leg4_L_ServoMotor2_CrouchPos;
int Leg4_L_ServoMotor3_CrouchPos;

int Leg1_L_ServoMotor1_CurrentPos;									// set the current position of each legs to the home position for that leg
int Leg1_L_ServoMotor2_CurrentPos;
int Leg1_L_ServoMotor3_CurrentPos;

int Leg2_L_ServoMotor1_CurrentPos;
int Leg2_L_ServoMotor2_CurrentPos;
int Leg2_L_ServoMotor3_CurrentPos;

int Leg3_L_ServoMotor1_CurrentPos;
int Leg3_L_ServoMotor2_CurrentPos;
int Leg3_L_ServoMotor3_CurrentPos;

int Leg4_L_ServoMotor1_CurrentPos;
int Leg4_L_ServoMotor2_CurrentPos;
int Leg4_L_ServoMotor3_CurrentPos;

int Leg1_R_ServoMotor1_CurrentPos;
int Leg1_R_ServoMotor2_CurrentPos;
int Leg1_R_ServoMotor3_CurrentPos;

int Leg2_R_ServoMotor1_CurrentPos;
int Leg2_R_ServoMotor2_CurrentPos;
int Leg2_R_ServoMotor3_CurrentPos;

int Leg3_R_ServoMotor1_CurrentPos;
int Leg3_R_ServoMotor2_CurrentPos;
int Leg3_R_ServoMotor3_CurrentPos;

int Leg4_R_ServoMotor1_CurrentPos;
int Leg4_R_ServoMotor2_CurrentPos;
int Leg4_R_ServoMotor3_CurrentPos;

int Leg_HipMoveForwardIncrement;									// define the movement distances for the 4:4 walk forward - full range motion = (10 * increment)
int Leg_HipMoveUpDownIncrement;
int Leg_KneeMoveUpDownIncrement;

long time_CurrentTime;												// define timing variables for sequencing 4:4 leg motion
long time_DelayBetweenSteps;
long time_TimeForNextStep;
long time_DelayBetweenIdleMovements;
long time_TimeForIdleMovement;

int messageIn;
int current_Command;												// set the current command

bool loopThruCommands;												//
bool init_Complete;													// boolean for initialize complete
bool R1R3L2L4_forward;												// boolean for whether LR walking forward is already in progress
bool R1R3L2L4_backward;												// boolean for whether LR walking backward is already in progress
bool lastStepWasLeft;												// use to alternate left:right sequence for 4:4 walking



void setup() {
	Serial.begin(9600);

	pwmServoDriverFrontLegs.begin();
	pwmServoDriverFrontLegs.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

	pwmServoDriverRearLegs.begin();
	pwmServoDriverRearLegs.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

	legSpeed01_DelayTime = 48;  // 48 =  33%
	legSpeed02_DelayTime = 32;  // 32 =  50%
	legSpeed03_DelayTime = 24;  // 24 =  67%
	legSpeed04_DelayTime = 20;  // 20 =  80%
	legSpeed05_DelayTime = 16;  // 16 = 100%  *** Default speed ***
	legSpeed06_DelayTime = 13;  // 13 = 123%
	legSpeed07_DelayTime = 10;  // 10 = 160%
	legSpeed08_DelayTime = 8;   //  8 = 200%
	legSpeed09_DelayTime = 6;   //  6 = 267%
	legSpeed10_DelayTime = 5;   //  5 = 320%
	legSpeed11_DelayTime = 4;   //  4 = 400%
	legSpeed12_DelayTime = 3;   //  3 = 533%
	legSpeed13_DelayTime = 2;   //  2 = 800%

	legSpeedDefault;
	legSpeed;

	Leg1_L_ServoMotor1_Home = 410;									// 410 - smaller numbers moves backward - front leg pointed slightly forward
	Leg1_L_ServoMotor2_Home = 420;									// 420 - smaller numbers moves down
	Leg1_L_ServoMotor3_Home = 490;									// 490 - smaller numbers moves up

	Leg2_L_ServoMotor1_Home = 420;									// 420 - smaller numbers moves backward - middle leg pointed straight out 
	Leg2_L_ServoMotor2_Home = 400;									// 400 - smaller numbers moves down
	Leg2_L_ServoMotor3_Home = 540;									// 540 - smaller numbers moves up

	Leg3_L_ServoMotor1_Home = 420;									// 420 - smaller numbers moves backward - back leg pointed slightly backward
	Leg3_L_ServoMotor2_Home = 430;									// 430 - smaller numbers moves down
	Leg3_L_ServoMotor3_Home = 610;									// 610 - smaller numbers moves up

	Leg4_L_ServoMotor1_Home = 400;									// 400 - smaller numbers moves backward - back leg pointed slightly backward
	Leg4_L_ServoMotor2_Home = 420;									// 420 - smaller numbers moves down
	Leg4_L_ServoMotor3_Home = 580;									// 580 - smaller numbers moves up

	Leg1_R_ServoMotor1_Home = 380;									// 380 - larger numbers move backward - front leg pointed slightly forward
	Leg1_R_ServoMotor2_Home = 280;									// 280 - smaller numbers moves up
	Leg1_R_ServoMotor3_Home = 200;									// 200 - smaller numbers moves down

	Leg2_R_ServoMotor1_Home = 410;									// 410 - larger numbers moves backward - middle leg pointed straight out  
	Leg2_R_ServoMotor2_Home = 276;									// 276 - smaller numbers moves up
	Leg2_R_ServoMotor3_Home = 170;									// 170 - smaller numbers moves down

	Leg3_R_ServoMotor1_Home = 360;									// 360 - larger numbers moves backward - middle leg pointed straight out

	// SERVO FOR LEG3_R IS FAILING OR NEEDS MAINTENANCE
	Leg3_R_ServoMotor2_Home = 310;									// 310 - smaller numbers moves up [SERVO IS FAILING]
	Leg3_R_ServoMotor3_Home = 205;									// 205 - smaller numbers moves down

	Leg4_R_ServoMotor1_Home = 360;									// 360 - larger numbers moves backward - middle leg pointed straight out
	Leg4_R_ServoMotor2_Home = 260;									// 260 - smaller numbers moves up
	Leg4_R_ServoMotor3_Home = 190;									// 190 - smaller numbers moves down

	Leg1_L_ServoMotor1_Standing = Leg1_L_ServoMotor1_Home;			// -  0: smaller numbers moves forward - front leg pointed slightly forward
	Leg1_L_ServoMotor2_Standing = Leg1_L_ServoMotor2_Home - 260;	// -260: smaller numbers moves down
	Leg1_L_ServoMotor3_Standing = Leg1_L_ServoMotor3_Home - 220;	// -220: smaller numbers moves up

	Leg2_L_ServoMotor1_Standing = Leg2_L_ServoMotor1_Home;			// -  0: smaller numbers moves forward - middle leg pointed straight out 
	Leg2_L_ServoMotor2_Standing = Leg2_L_ServoMotor2_Home - 250;	// -250: smaller numbers moves down
	Leg2_L_ServoMotor3_Standing = Leg2_L_ServoMotor3_Home - 225;	// -225: smaller numbers moves up

	Leg3_L_ServoMotor1_Standing = Leg3_L_ServoMotor1_Home;			// -  0: smaller numbers moves forward - back leg pointed slightly backward
	Leg3_L_ServoMotor2_Standing = Leg3_L_ServoMotor2_Home - 250;	// -250: smaller numbers moves down
	Leg3_L_ServoMotor3_Standing = Leg3_L_ServoMotor3_Home - 245;	// -245: smaller numbers moves up

	Leg4_L_ServoMotor1_Standing = Leg4_L_ServoMotor1_Home;			// -  0: smaller numbers moves forward - back leg pointed slightly backward
	Leg4_L_ServoMotor2_Standing = Leg4_L_ServoMotor2_Home - 250;	// -250: smaller numbers moves down
	Leg4_L_ServoMotor3_Standing = Leg4_L_ServoMotor3_Home - 245;	// -245: smaller numbers moves up

	Leg1_R_ServoMotor1_Standing = Leg1_R_ServoMotor1_Home;			// +  0: larger numbers move forward - front leg pointed slightly forward
	Leg1_R_ServoMotor2_Standing = Leg1_R_ServoMotor2_Home + 250;	// +250: smaller numbers moves up
	Leg1_R_ServoMotor3_Standing = Leg1_R_ServoMotor3_Home + 190;	// +190: smaller numbers moves down

	Leg2_R_ServoMotor1_Standing = Leg2_R_ServoMotor1_Home;			// +  0: larger numbers moves forward - middle leg pointed straight out  
	Leg2_R_ServoMotor2_Standing = Leg2_R_ServoMotor2_Home + 250;	// +250: smaller numbers moves up
	Leg2_R_ServoMotor3_Standing = Leg2_R_ServoMotor3_Home + 180;	// +180: smaller numbers moves down

	Leg3_R_ServoMotor1_Standing = Leg3_R_ServoMotor1_Home;			// +  0: larger numbers moves forward - middle leg pointed straight out
	Leg3_R_ServoMotor2_Standing = Leg3_R_ServoMotor2_Home + 225;	// +225: smaller numbers moves up
	Leg3_R_ServoMotor3_Standing = Leg3_R_ServoMotor3_Home + 190;	// +190: smaller numbers moves down

	Leg4_R_ServoMotor1_Standing = Leg4_R_ServoMotor1_Home;			// +  0: larger numbers moves forward - middle leg pointed straight out
	Leg4_R_ServoMotor2_Standing = Leg4_R_ServoMotor2_Home + 250;	// +250: smaller numbers moves up
	Leg4_R_ServoMotor3_Standing = Leg4_R_ServoMotor3_Home + 180;	// +180: smaller numbers moves down


	Leg1_L_ServoMotor1_CrouchPos = Leg1_L_ServoMotor1_Home;			// +  0: smaller numbers moves forward - front leg pointed slightly forward
	Leg1_L_ServoMotor2_CrouchPos = Leg1_L_ServoMotor2_Home + 90;	// + 90: smaller numbers moves down
	Leg1_L_ServoMotor3_CrouchPos = Leg1_L_ServoMotor3_Home + 0;		// +  0: smaller numbers moves up

	Leg2_L_ServoMotor1_CrouchPos = Leg2_L_ServoMotor1_Home;			// +  0: smaller numbers moves forward - middle leg pointed straight out 
	Leg2_L_ServoMotor2_CrouchPos = Leg2_L_ServoMotor2_Home + 90;	// + 90: smaller numbers moves down
	Leg2_L_ServoMotor3_CrouchPos = Leg2_L_ServoMotor3_Home + 10;	// + 10: smaller numbers moves up

	Leg3_L_ServoMotor1_CrouchPos = Leg3_L_ServoMotor1_Home;			// +  0: smaller numbers moves forward - back leg pointed slightly backward
	Leg3_L_ServoMotor2_CrouchPos = Leg3_L_ServoMotor2_Home + 100;	// +100: smaller numbers moves down
	Leg3_L_ServoMotor3_CrouchPos = Leg3_L_ServoMotor3_Home + 5;		// +  5: smaller numbers moves up

	Leg4_L_ServoMotor1_CrouchPos = Leg4_L_ServoMotor1_Home;			// +  0: smaller numbers moves forward - back leg pointed slightly backward
	Leg4_L_ServoMotor2_CrouchPos = Leg4_L_ServoMotor2_Home + 100;	// +100: smaller numbers moves down
	Leg4_L_ServoMotor3_CrouchPos = Leg4_L_ServoMotor3_Home + 5;		// +  5: smaller numbers moves up

	Leg1_R_ServoMotor1_CrouchPos = Leg1_R_ServoMotor1_Home;			// -  0: larger numbers move forward - front leg pointed slightly forward
	Leg1_R_ServoMotor2_CrouchPos = Leg1_R_ServoMotor2_Home - 100;	// -100: smaller numbers moves up
	Leg1_R_ServoMotor3_CrouchPos = Leg1_R_ServoMotor3_Home - 25;	// - 25: smaller numbers moves down

	Leg2_R_ServoMotor1_CrouchPos = Leg2_R_ServoMotor1_Home;			// -000: larger numbers moves forward - middle leg pointed straight out  
	Leg2_R_ServoMotor2_CrouchPos = Leg2_R_ServoMotor2_Home - 100;	// -100: smaller numbers moves up
	Leg2_R_ServoMotor3_CrouchPos = Leg2_R_ServoMotor3_Home - 20;	// - 20: smaller numbers moves down

	Leg3_R_ServoMotor1_CrouchPos = Leg3_R_ServoMotor1_Home;			// -  0: larger numbers moves forward - middle leg pointed straight out
	Leg3_R_ServoMotor2_CrouchPos = Leg3_R_ServoMotor2_Home - 90;	// - 90: smaller numbers moves up
	Leg3_R_ServoMotor3_CrouchPos = Leg3_R_ServoMotor3_Home - 25;	// - 25 smaller numbers moves down

	Leg4_R_ServoMotor1_CrouchPos = Leg4_R_ServoMotor1_Home;			// -  0: larger numbers moves forward - middle leg pointed straight out
	Leg4_R_ServoMotor2_CrouchPos = Leg4_R_ServoMotor2_Home - 100;	// -100: smaller numbers moves up
	Leg4_R_ServoMotor3_CrouchPos = Leg4_R_ServoMotor3_Home - 30;	// - 30: smaller numbers moves down


	Leg1_L_ServoMotor1_CurrentPos = Leg1_L_ServoMotor1_Home;
	Leg1_L_ServoMotor2_CurrentPos = Leg1_L_ServoMotor2_Home;
	Leg1_L_ServoMotor3_CurrentPos = Leg1_L_ServoMotor3_Home;

	Leg2_L_ServoMotor1_CurrentPos = Leg2_L_ServoMotor1_Home;
	Leg2_L_ServoMotor2_CurrentPos = Leg2_L_ServoMotor2_Home;
	Leg2_L_ServoMotor3_CurrentPos = Leg2_L_ServoMotor3_Home;

	Leg3_L_ServoMotor1_CurrentPos = Leg3_L_ServoMotor1_Home;
	Leg3_L_ServoMotor2_CurrentPos = Leg3_L_ServoMotor2_Home;
	Leg3_L_ServoMotor3_CurrentPos = Leg3_L_ServoMotor3_Home;

	Leg4_L_ServoMotor1_CurrentPos = Leg4_L_ServoMotor1_Home;
	Leg4_L_ServoMotor2_CurrentPos = Leg4_L_ServoMotor2_Home;
	Leg4_L_ServoMotor3_CurrentPos = Leg4_L_ServoMotor3_Home;

	Leg1_R_ServoMotor1_CurrentPos = Leg1_R_ServoMotor1_Home;
	Leg1_R_ServoMotor2_CurrentPos = Leg1_R_ServoMotor2_Home;
	Leg1_R_ServoMotor3_CurrentPos = Leg1_R_ServoMotor3_Home;

	Leg2_R_ServoMotor1_CurrentPos = Leg2_R_ServoMotor1_Home;
	Leg2_R_ServoMotor2_CurrentPos = Leg2_R_ServoMotor2_Home;
	Leg2_R_ServoMotor3_CurrentPos = Leg2_R_ServoMotor3_Home;

	Leg3_R_ServoMotor1_CurrentPos = Leg3_R_ServoMotor1_Home;
	Leg3_R_ServoMotor2_CurrentPos = Leg3_R_ServoMotor2_Home;
	Leg3_R_ServoMotor3_CurrentPos = Leg3_R_ServoMotor3_Home;

	Leg4_R_ServoMotor1_CurrentPos = Leg4_R_ServoMotor1_Home;
	Leg4_R_ServoMotor2_CurrentPos = Leg4_R_ServoMotor2_Home;
	Leg4_R_ServoMotor3_CurrentPos = Leg4_R_ServoMotor3_Home;



	Leg_HipMoveForwardIncrement = 3;								// define the movement distances for the 4:4 walk forward - full range motion = (10 * increment)
	Leg_HipMoveUpDownIncrement = 8;
	Leg_KneeMoveUpDownIncrement = 4;

	time_CurrentTime = 0;											// define timing variables for sequencing 4:4 leg motion
	time_DelayBetweenSteps = legSpeed * 100;
	time_TimeForNextStep = time_CurrentTime + time_DelayBetweenSteps;
	time_DelayBetweenIdleMovements = random(250, 3001);
	time_TimeForIdleMovement = time_CurrentTime + time_DelayBetweenIdleMovements;

	loopThruCommands = false;
	init_Complete = false;											// boolean for initialize complete
	R1R3L2L4_forward = false;										// boolean for whether LR walking forward is already in progress
	lastStepWasLeft = false;										// use to alternate left:right sequence for 4:4 walking

	legSpeedDefault = legSpeed05_DelayTime;							// the range is 1-13 (legSpeed01_DelayTime - legSpeed13_DelayTime)
	legSpeed = legSpeedDefault;

	//current_Command = idleRandom_Command;							// startup command (action/behavior/movement) is random idle leg movements
	//current_Command = r2l2ForwardWalking_Command;
	//current_Command = archUp_Command;								// startup command (action/behavior/movement) is arched up - standing
	//current_Command = crouchDown_Command;							// startup command (action/behavior/movement) is arched up - standing

}

// This is the main program loop
//
void loop()
{
	time_CurrentTime = millis();

	// check for initialization  
	if (init_Complete == false)
	{
		delay(2000);

		initialize_Legs();
		init_Complete = true;

		delay(1000);

	}
	else
	{
		// check for wireless message
		if (Serial.available()>0)
		{
			// Move and Hold Position
			// ======================
			// A - archUp_Command:					arch up with body raised high off ground
			// C - crouchDown_Command:				crouch down with body down to the ground
			// U - frontUp_Command:					front up with rear down
			// u - backUp_Command:					rear up with front down
			// D - leftSideDown_Command:			left side down right side up
			// d - rightSideDown_Command:			right side down left side up
			// T - twistLeft_Command:				body twists counter-clockwise on stationary "feet"
			// t - twistRight_Command:				body twists clockwise on stationary "feet"
			//
			// In-place Movements
			// ==================
			// I - idleRandom_Command:				move to home position with idle leg twitches and random movements
			// P - probeFrontLegs_Command:			arch back and reach/probe with front legs
			//
			// Moving Around
			// =============
			// F - r2l2ForwardWalking_Command:		left/right walking forward with two legs on each side moving 
			// B - r2l2BackwardWalking_Command:		left/right walking backward with two legs on each side moving 
			// L - turnLeft_Command:				turn left - smaller steps on left (50%)
			// l - turnHardLeft_Command:			turn hard left -  much smaller steps on left (25%)
			// R - turnRight_Command:				turn right - smaller steps on right (50%)
			// r - turnRight_Command:				turn hard right - much smaller steps on right (25%)
			// S - rotateLeft_Command:				spin counter clockwise - back-step on left while stepping forward on right
			// s - rotateRight_Command:				spin clockwise - back-step on right while stepping forward on left
			//
			// f - oneLegForwardWalking_Command:	rearward-most leg takes step forward walking forward
			// b - oneLegBackwardWalking_Command:	forward-most leg takes step back walking backward

			messageIn = Serial.read();

			if (messageIn == '0')
			{
				// set leg speed to speed 1
				legSpeed = legSpeed02_DelayTime;
			}

			if (messageIn == '1')
			{
				// set leg speed to speed 1
				legSpeed = legSpeed05_DelayTime;
			}

			if (messageIn == '2')
			{
				// set leg speed to speed 1
				legSpeed = legSpeed06_DelayTime;
			}

			if (messageIn == '3')
			{
				// set leg speed to speed 1
				legSpeed = legSpeed07_DelayTime;
			}

			if (messageIn == '4')
			{
				// set leg speed to speed 1
				legSpeed = legSpeed08_DelayTime;
			}

			if (messageIn == '5')
			{
				// set leg speed to speed 1
				legSpeed = legSpeed09_DelayTime;
			}

			if (messageIn == '6')
			{
				// set leg speed to speed 1
				legSpeed = legSpeed10_DelayTime;
			}

			if (messageIn == '7')
			{
				// set leg speed to speed 1
				legSpeed = legSpeed11_DelayTime;
			}

			if (messageIn == '8')
			{
				// set leg speed to speed 1
				legSpeed = legSpeed12_DelayTime;
			}

			if (messageIn == '9')
			{
				// set leg speed to speed 1
				legSpeed = legSpeed13_DelayTime;
			}

			if (messageIn == 'A')
			{
				// A - archUp_Command:					arch up with body raised high off ground
				current_Command = archUp_Command;
			}

			if (messageIn == 'C')
			{
				// C - crouchDown_Command:				crouch down with body down to the ground
				current_Command = crouchDown_Command;
			}

			if (messageIn == 'D')
			{
				// D - leftSideDown_Command:			left side down right side up
				current_Command = leftSideDown_Command;
			}

			if (messageIn == 'd')
			{
				// d - rightSideDown_Command:			right side down left side up
				current_Command = rightSideDown_Command;
			}

			if (messageIn == 'H')
			{
				// T - twistLeft_Command:			left side down right side up
				current_Command = standStill_Command;
			}

			if (messageIn == 'T')
			{
				// T - twistLeft_Command:			left side down right side up
				current_Command = twistLeft_Command;
			}

			if (messageIn == 't')
			{
				// d - rightSideDown_Command:			right side down left side up
				current_Command = twistRight_Command;
			}

			if (messageIn == 'U')
			{
				// U - frontUp_Command:					front up with rear down
				current_Command = frontEndUp_Command;
			}

			if (messageIn == 'u')
			{
				// u - backUp_Command:					rear up with front down
				current_Command = backEndUp_Command;
			}

			if (messageIn == 'I')
			{
				// I - idleRandom_Command:				move to home position with idle leg twitches and random movements
				initialize_Legs();
				current_Command = idleRandom_Command;
			}

			if (messageIn == 'P')
			{
				// P - probeFrontLegs_Command:			arch back and reach/probe with front legs
				current_Command = probeFrontLegs_Command;
			}

			if (messageIn == 'F')
			{
				// F - r2l2ForwardWalking_Command:		left/right walking forward with two legs on each side moving 
				initialize_Legs();
				current_Command = r2l2ForwardWalking_Command;
			}

			if (messageIn == 'B')
			{
				// B - r2l2BackwardWalking_Command:		left/right walking backward with two legs on each side moving 
				initialize_Legs();
				current_Command = r2l2BackwardWalking_Command;
			}

			if (messageIn == 'L')
			{
				// L - turnLeft_Command:				turn left - smaller steps on left (50%) 
				current_Command = turnLeft_Command;
			}

			if (messageIn == 'l')
			{
				// l - turnHardLeft_Command:				turn hard left - much smaller steps on left (25%) 
				current_Command = turnHardLeft_Command;
			}

			if (messageIn == 'R')
			{
				// R - turnRight_Command:				turn right - smaller steps on right (50%)
				current_Command = turnRight_Command;
			}

			if (messageIn == 'r')
			{
				// R - turnHardRight_Command:				turn hard right - much smaller steps on right (25%)
				current_Command = turnHardRight_Command;
			}

			if (messageIn == 'S')
			{
				// S - rotateLeft_Command:				spin counter clockwise - back-step on left while stepping forward on right
				current_Command = rotateLeft_Command;
			}

			if (messageIn == 's')
			{
				// s - rotateRight_Command:				spin clockwise - back-step on right while stepping forward on left
				current_Command = rotateRight_Command;
			}

			if (messageIn == 'f')
			{
				// f - oneLegForwardWalking_Command:	rearward-most leg takes step forward walking forward
				current_Command = oneLegForwardWalking_Command;
			}

			if (messageIn == 'b')
			{
				// b - oneLegBackwardWalking_Command:	forward-most leg takes step back walking backward
				current_Command = oneLegBackwardWalking_Command;
			}

		}

		// check for command option
		if (loopThruCommands == true)
		{
			// randomly select the current command that will run for 5 seconds
			current_Command = random(1, 17);
		}

		switch (current_Command)
		{
		case archUp_Command:
			commandArchUp();
			break;

		case crouchDown_Command:
			commandCrouchDown();
			break;

		case leftSideDown_Command:
			commandLeftSideDownRightSideUp();
			break;

		case rightSideDown_Command:
			commandRightSideDownLeftSideUp();
			break;

		case standStill_Command:
			initialize_Legs();
			break;

		case twistLeft_Command:
			break;

		case twistRight_Command:
			break;

		case frontEndUp_Command:
			break;

		case backEndUp_Command:
			break;

		case idleRandom_Command:
			commandIdleRandomMovement();
			break;

		case probeFrontLegs_Command:
			break;

		case r2l2ForwardWalking_Command:

			if (time_CurrentTime >= time_TimeForNextStep)
			{
				time_TimeForNextStep = time_CurrentTime + time_DelayBetweenSteps;

				commandR2L2Walking(1, 1);

			}

			break;

		case r2l2BackwardWalking_Command:

			if (time_CurrentTime >= time_TimeForNextStep)
			{
				time_TimeForNextStep = time_CurrentTime + time_DelayBetweenSteps;

				commandR2L2Walking(-1, -1);

			}

			break;

		case turnLeft_Command:

			if (time_CurrentTime >= time_TimeForNextStep)
			{
				time_TimeForNextStep = time_CurrentTime + time_DelayBetweenSteps;

				commandR2L2Walking(2, 1);

			}

			break;

		case turnHardLeft_Command:

			if (time_CurrentTime >= time_TimeForNextStep)
			{
				time_TimeForNextStep = time_CurrentTime + time_DelayBetweenSteps;

				commandR2L2Walking(4, 1);

			}

			break;

		case turnRight_Command:

			if (time_CurrentTime >= time_TimeForNextStep)
			{
				time_TimeForNextStep = time_CurrentTime + time_DelayBetweenSteps;

				commandR2L2Walking(1, 2);

			}

			break;

		case turnHardRight_Command:

			if (time_CurrentTime >= time_TimeForNextStep)
			{
				time_TimeForNextStep = time_CurrentTime + time_DelayBetweenSteps;

				commandR2L2Walking(1, 2);

			}

			break;

		case rotateLeft_Command:

			if (time_CurrentTime >= time_TimeForNextStep)
			{
				time_TimeForNextStep = time_CurrentTime + time_DelayBetweenSteps;

				commandR2L2Walking(-1, 1);

			}

			break;

		case rotateRight_Command:

			if (time_CurrentTime >= time_TimeForNextStep)
			{
				time_TimeForNextStep = time_CurrentTime + time_DelayBetweenSteps;

				commandR2L2Walking(1, -1);

			}

			break;

		case oneLegForwardWalking_Command:
			break;

		case oneLegBackwardWalking_Command:
			break;

		default:

			break;
		}

	}

}


void commandArchUp()
{
	Leg1_L_ServoMotor1_CurrentPos = Leg1_L_ServoMotor1_Standing;
	Leg1_L_ServoMotor2_CurrentPos = Leg1_L_ServoMotor2_Standing;
	Leg1_L_ServoMotor3_CurrentPos = Leg1_L_ServoMotor3_Standing;

	Leg2_L_ServoMotor1_CurrentPos = Leg2_L_ServoMotor1_Standing;
	Leg2_L_ServoMotor2_CurrentPos = Leg2_L_ServoMotor2_Standing;
	Leg2_L_ServoMotor3_CurrentPos = Leg2_L_ServoMotor3_Standing;

	Leg3_L_ServoMotor1_CurrentPos = Leg3_L_ServoMotor1_Standing;
	Leg3_L_ServoMotor2_CurrentPos = Leg3_L_ServoMotor2_Standing;
	Leg3_L_ServoMotor3_CurrentPos = Leg3_L_ServoMotor3_Standing;

	Leg4_L_ServoMotor1_CurrentPos = Leg4_L_ServoMotor1_Standing;
	Leg4_L_ServoMotor2_CurrentPos = Leg4_L_ServoMotor2_Standing;
	Leg4_L_ServoMotor3_CurrentPos = Leg4_L_ServoMotor3_Standing;

	Leg1_R_ServoMotor1_CurrentPos = Leg1_R_ServoMotor1_Standing;
	Leg1_R_ServoMotor2_CurrentPos = Leg1_R_ServoMotor2_Standing;
	Leg1_R_ServoMotor3_CurrentPos = Leg1_R_ServoMotor3_Standing;

	Leg2_R_ServoMotor1_CurrentPos = Leg2_R_ServoMotor1_Standing;
	Leg2_R_ServoMotor2_CurrentPos = Leg2_R_ServoMotor2_Standing;
	Leg2_R_ServoMotor3_CurrentPos = Leg2_R_ServoMotor3_Standing;

	Leg3_R_ServoMotor1_CurrentPos = Leg3_R_ServoMotor1_Standing;
	Leg3_R_ServoMotor2_CurrentPos = Leg3_R_ServoMotor2_Standing;
	Leg3_R_ServoMotor3_CurrentPos = Leg3_R_ServoMotor3_Standing;

	Leg4_R_ServoMotor1_CurrentPos = Leg4_R_ServoMotor1_Standing;
	Leg4_R_ServoMotor2_CurrentPos = Leg4_R_ServoMotor2_Standing;
	Leg4_R_ServoMotor3_CurrentPos = Leg4_R_ServoMotor3_Standing;

	// LEFT SIDE LEGS
	pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor1_ChannelNum, 0, Leg1_L_ServoMotor1_CurrentPos); //Leg1_L_ServoMotor1_CurrentPos
	pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor2_ChannelNum, 0, Leg1_L_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor3_ChannelNum, 0, Leg1_L_ServoMotor3_CurrentPos);

	pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor1_ChannelNum, 0, Leg2_L_ServoMotor1_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor2_ChannelNum, 0, Leg2_L_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor3_ChannelNum, 0, Leg2_L_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor1_ChannelNum, 0, Leg3_L_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor2_ChannelNum, 0, Leg3_L_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor3_ChannelNum, 0, Leg3_L_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor1_ChannelNum, 0, Leg4_L_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor2_ChannelNum, 0, Leg4_L_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor3_ChannelNum, 0, Leg4_L_ServoMotor3_CurrentPos);


	// RIGHT SIDE LEGS
	pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor1_ChannelNum, 0, Leg1_R_ServoMotor1_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor2_ChannelNum, 0, Leg1_R_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor3_ChannelNum, 0, Leg1_R_ServoMotor3_CurrentPos);

	pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor1_ChannelNum, 0, Leg2_R_ServoMotor1_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor2_ChannelNum, 0, Leg2_R_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor3_ChannelNum, 0, Leg2_R_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor1_ChannelNum, 0, Leg3_R_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor2_ChannelNum, 0, Leg3_R_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor3_ChannelNum, 0, Leg3_R_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor1_ChannelNum, 0, Leg4_R_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor2_ChannelNum, 0, Leg4_R_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor3_ChannelNum, 0, Leg4_R_ServoMotor3_CurrentPos);

}


void commandRightSideDownLeftSideUp()
{
	Leg1_L_ServoMotor1_CurrentPos = Leg1_L_ServoMotor1_Standing;
	Leg1_L_ServoMotor2_CurrentPos = Leg1_L_ServoMotor2_Standing;
	Leg1_L_ServoMotor3_CurrentPos = Leg1_L_ServoMotor3_Standing;

	Leg2_L_ServoMotor1_CurrentPos = Leg2_L_ServoMotor1_Standing;
	Leg2_L_ServoMotor2_CurrentPos = Leg2_L_ServoMotor2_Standing;
	Leg2_L_ServoMotor3_CurrentPos = Leg2_L_ServoMotor3_Standing;

	Leg3_L_ServoMotor1_CurrentPos = Leg3_L_ServoMotor1_Standing;
	Leg3_L_ServoMotor2_CurrentPos = Leg3_L_ServoMotor2_Standing;
	Leg3_L_ServoMotor3_CurrentPos = Leg3_L_ServoMotor3_Standing;

	Leg4_L_ServoMotor1_CurrentPos = Leg4_L_ServoMotor1_Standing;
	Leg4_L_ServoMotor2_CurrentPos = Leg4_L_ServoMotor2_Standing;
	Leg4_L_ServoMotor3_CurrentPos = Leg4_L_ServoMotor3_Standing;


	Leg1_R_ServoMotor1_CurrentPos = Leg1_R_ServoMotor1_CrouchPos;
	Leg1_R_ServoMotor2_CurrentPos = Leg1_R_ServoMotor2_CrouchPos;
	Leg1_R_ServoMotor3_CurrentPos = Leg1_R_ServoMotor3_CrouchPos;

	Leg2_R_ServoMotor1_CurrentPos = Leg2_R_ServoMotor1_CrouchPos;
	Leg2_R_ServoMotor2_CurrentPos = Leg2_R_ServoMotor2_CrouchPos;
	Leg2_R_ServoMotor3_CurrentPos = Leg2_R_ServoMotor3_CrouchPos;

	Leg3_R_ServoMotor1_CurrentPos = Leg3_R_ServoMotor1_CrouchPos;
	Leg3_R_ServoMotor2_CurrentPos = Leg3_R_ServoMotor2_CrouchPos;
	Leg3_R_ServoMotor3_CurrentPos = Leg3_R_ServoMotor3_CrouchPos;

	Leg4_R_ServoMotor1_CurrentPos = Leg4_R_ServoMotor1_CrouchPos;
	Leg4_R_ServoMotor2_CurrentPos = Leg4_R_ServoMotor2_CrouchPos;
	Leg4_R_ServoMotor3_CurrentPos = Leg4_R_ServoMotor3_CrouchPos;


	// LEFT SIDE LEGS
	pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor1_ChannelNum, 0, Leg1_L_ServoMotor1_CurrentPos); //Leg1_L_ServoMotor1_CurrentPos
	pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor2_ChannelNum, 0, Leg1_L_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor3_ChannelNum, 0, Leg1_L_ServoMotor3_CurrentPos);

	pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor1_ChannelNum, 0, Leg2_L_ServoMotor1_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor2_ChannelNum, 0, Leg2_L_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor3_ChannelNum, 0, Leg2_L_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor1_ChannelNum, 0, Leg3_L_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor2_ChannelNum, 0, Leg3_L_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor3_ChannelNum, 0, Leg3_L_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor1_ChannelNum, 0, Leg4_L_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor2_ChannelNum, 0, Leg4_L_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor3_ChannelNum, 0, Leg4_L_ServoMotor3_CurrentPos);


	// RIGHT SIDE LEGS
	pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor1_ChannelNum, 0, Leg1_R_ServoMotor1_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor2_ChannelNum, 0, Leg1_R_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor3_ChannelNum, 0, Leg1_R_ServoMotor3_CurrentPos);

	pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor1_ChannelNum, 0, Leg2_R_ServoMotor1_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor2_ChannelNum, 0, Leg2_R_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor3_ChannelNum, 0, Leg2_R_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor1_ChannelNum, 0, Leg3_R_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor2_ChannelNum, 0, Leg3_R_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor3_ChannelNum, 0, Leg3_R_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor1_ChannelNum, 0, Leg4_R_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor2_ChannelNum, 0, Leg4_R_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor3_ChannelNum, 0, Leg4_R_ServoMotor3_CurrentPos);

}


void commandLeftSideDownRightSideUp()
{
	Leg1_L_ServoMotor1_CurrentPos = Leg1_L_ServoMotor1_CrouchPos;
	Leg1_L_ServoMotor2_CurrentPos = Leg1_L_ServoMotor2_CrouchPos;
	Leg1_L_ServoMotor3_CurrentPos = Leg1_L_ServoMotor3_CrouchPos;

	Leg2_L_ServoMotor1_CurrentPos = Leg2_L_ServoMotor1_CrouchPos;
	Leg2_L_ServoMotor2_CurrentPos = Leg2_L_ServoMotor2_CrouchPos;
	Leg2_L_ServoMotor3_CurrentPos = Leg2_L_ServoMotor3_CrouchPos;

	Leg3_L_ServoMotor1_CurrentPos = Leg3_L_ServoMotor1_CrouchPos;
	Leg3_L_ServoMotor2_CurrentPos = Leg3_L_ServoMotor2_CrouchPos;
	Leg3_L_ServoMotor3_CurrentPos = Leg3_L_ServoMotor3_CrouchPos;

	Leg4_L_ServoMotor1_CurrentPos = Leg4_L_ServoMotor1_CrouchPos;
	Leg4_L_ServoMotor2_CurrentPos = Leg4_L_ServoMotor2_CrouchPos;
	Leg4_L_ServoMotor3_CurrentPos = Leg4_L_ServoMotor3_CrouchPos;

	Leg1_R_ServoMotor1_CurrentPos = Leg1_R_ServoMotor1_Standing;
	Leg1_R_ServoMotor2_CurrentPos = Leg1_R_ServoMotor2_Standing;
	Leg1_R_ServoMotor3_CurrentPos = Leg1_R_ServoMotor3_Standing;

	Leg2_R_ServoMotor1_CurrentPos = Leg2_R_ServoMotor1_Standing;
	Leg2_R_ServoMotor2_CurrentPos = Leg2_R_ServoMotor2_Standing;
	Leg2_R_ServoMotor3_CurrentPos = Leg2_R_ServoMotor3_Standing;

	Leg3_R_ServoMotor1_CurrentPos = Leg3_R_ServoMotor1_Standing;
	Leg3_R_ServoMotor2_CurrentPos = Leg3_R_ServoMotor2_Standing;
	Leg3_R_ServoMotor3_CurrentPos = Leg3_R_ServoMotor3_Standing;

	Leg4_R_ServoMotor1_CurrentPos = Leg4_R_ServoMotor1_Standing;
	Leg4_R_ServoMotor2_CurrentPos = Leg4_R_ServoMotor2_Standing;
	Leg4_R_ServoMotor3_CurrentPos = Leg4_R_ServoMotor3_Standing;

	// LEFT SIDE LEGS
	pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor1_ChannelNum, 0, Leg1_L_ServoMotor1_CurrentPos); //Leg1_L_ServoMotor1_CurrentPos
	pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor2_ChannelNum, 0, Leg1_L_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor3_ChannelNum, 0, Leg1_L_ServoMotor3_CurrentPos);

	pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor1_ChannelNum, 0, Leg2_L_ServoMotor1_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor2_ChannelNum, 0, Leg2_L_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor3_ChannelNum, 0, Leg2_L_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor1_ChannelNum, 0, Leg3_L_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor2_ChannelNum, 0, Leg3_L_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor3_ChannelNum, 0, Leg3_L_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor1_ChannelNum, 0, Leg4_L_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor2_ChannelNum, 0, Leg4_L_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor3_ChannelNum, 0, Leg4_L_ServoMotor3_CurrentPos);


	// RIGHT SIDE LEGS
	pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor1_ChannelNum, 0, Leg1_R_ServoMotor1_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor2_ChannelNum, 0, Leg1_R_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor3_ChannelNum, 0, Leg1_R_ServoMotor3_CurrentPos);

	pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor1_ChannelNum, 0, Leg2_R_ServoMotor1_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor2_ChannelNum, 0, Leg2_R_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor3_ChannelNum, 0, Leg2_R_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor1_ChannelNum, 0, Leg3_R_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor2_ChannelNum, 0, Leg3_R_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor3_ChannelNum, 0, Leg3_R_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor1_ChannelNum, 0, Leg4_R_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor2_ChannelNum, 0, Leg4_R_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor3_ChannelNum, 0, Leg4_R_ServoMotor3_CurrentPos);

}


void commandCrouchDown()
{
	// Smooth tranition from current position to Crouch
	//
	//int leg1_L_motor2Movement = (Leg1_L_ServoMotor2_CurrentPos - Leg1_L_ServoMotor2_CrouchPos) / 10;
	//int leg1_L_motor3Movement = (Leg1_L_ServoMotor3_CurrentPos - Leg1_L_ServoMotor3_CrouchPos) / 10;


	//for (int i=0; i<10; i++)
	//{
	//	
	//	Leg1_L_ServoMotor1_CurrentPos += 0;							// leg 1, left side
	//	Leg1_L_ServoMotor2_CurrentPos += leg1_L_motor2Movement;
	//	Leg1_L_ServoMotor3_CurrentPos += leg1_L_motor3Movement;

	//	// leg 1 on left side
	//	pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor1_ChannelNum, 0, Leg1_L_ServoMotor1_CurrentPos);
	//	pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor2_ChannelNum, 0, Leg1_L_ServoMotor2_CurrentPos);
	//	pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor3_ChannelNum, 0, Leg1_L_ServoMotor3_CurrentPos);

	//	delay(20);													// give the motor time to move
	//}


	Leg1_L_ServoMotor1_CurrentPos = Leg1_L_ServoMotor1_CrouchPos;
	Leg1_L_ServoMotor2_CurrentPos = Leg1_L_ServoMotor2_CrouchPos;
	Leg1_L_ServoMotor3_CurrentPos = Leg1_L_ServoMotor3_CrouchPos;

	Leg2_L_ServoMotor1_CurrentPos = Leg2_L_ServoMotor1_CrouchPos;
	Leg2_L_ServoMotor2_CurrentPos = Leg2_L_ServoMotor2_CrouchPos;
	Leg2_L_ServoMotor3_CurrentPos = Leg2_L_ServoMotor3_CrouchPos;

	Leg3_L_ServoMotor1_CurrentPos = Leg3_L_ServoMotor1_CrouchPos;
	Leg3_L_ServoMotor2_CurrentPos = Leg3_L_ServoMotor2_CrouchPos;
	Leg3_L_ServoMotor3_CurrentPos = Leg3_L_ServoMotor3_CrouchPos;

	Leg4_L_ServoMotor1_CurrentPos = Leg4_L_ServoMotor1_CrouchPos;
	Leg4_L_ServoMotor2_CurrentPos = Leg4_L_ServoMotor2_CrouchPos;
	Leg4_L_ServoMotor3_CurrentPos = Leg4_L_ServoMotor3_CrouchPos;

	Leg1_R_ServoMotor1_CurrentPos = Leg1_R_ServoMotor1_CrouchPos;
	Leg1_R_ServoMotor2_CurrentPos = Leg1_R_ServoMotor2_CrouchPos;
	Leg1_R_ServoMotor3_CurrentPos = Leg1_R_ServoMotor3_CrouchPos;

	Leg2_R_ServoMotor1_CurrentPos = Leg2_R_ServoMotor1_CrouchPos;
	Leg2_R_ServoMotor2_CurrentPos = Leg2_R_ServoMotor2_CrouchPos;
	Leg2_R_ServoMotor3_CurrentPos = Leg2_R_ServoMotor3_CrouchPos;

	Leg3_R_ServoMotor1_CurrentPos = Leg3_R_ServoMotor1_CrouchPos;
	Leg3_R_ServoMotor2_CurrentPos = Leg3_R_ServoMotor2_CrouchPos;
	Leg3_R_ServoMotor3_CurrentPos = Leg3_R_ServoMotor3_CrouchPos;

	Leg4_R_ServoMotor1_CurrentPos = Leg4_R_ServoMotor1_CrouchPos;
	Leg4_R_ServoMotor2_CurrentPos = Leg4_R_ServoMotor2_CrouchPos;
	Leg4_R_ServoMotor3_CurrentPos = Leg4_R_ServoMotor3_CrouchPos;


	// LEFT SIDE LEGS
	pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor1_ChannelNum, 0, Leg1_L_ServoMotor1_CurrentPos); //Leg1_L_ServoMotor1_CurrentPos
	pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor2_ChannelNum, 0, Leg1_L_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor3_ChannelNum, 0, Leg1_L_ServoMotor3_CurrentPos);

	pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor1_ChannelNum, 0, Leg2_L_ServoMotor1_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor2_ChannelNum, 0, Leg2_L_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor3_ChannelNum, 0, Leg2_L_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor1_ChannelNum, 0, Leg3_L_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor2_ChannelNum, 0, Leg3_L_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor3_ChannelNum, 0, Leg3_L_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor1_ChannelNum, 0, Leg4_L_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor2_ChannelNum, 0, Leg4_L_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor3_ChannelNum, 0, Leg4_L_ServoMotor3_CurrentPos);


	// RIGHT SIDE LEGS
	pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor1_ChannelNum, 0, Leg1_R_ServoMotor1_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor2_ChannelNum, 0, Leg1_R_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor3_ChannelNum, 0, Leg1_R_ServoMotor3_CurrentPos);

	pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor1_ChannelNum, 0, Leg2_R_ServoMotor1_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor2_ChannelNum, 0, Leg2_R_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor3_ChannelNum, 0, Leg2_R_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor1_ChannelNum, 0, Leg3_R_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor2_ChannelNum, 0, Leg3_R_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor3_ChannelNum, 0, Leg3_R_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor1_ChannelNum, 0, Leg4_R_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor2_ChannelNum, 0, Leg4_R_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor3_ChannelNum, 0, Leg4_R_ServoMotor3_CurrentPos);

}


void initialize_Legs()
{

	Leg1_L_ServoMotor1_CurrentPos = Leg1_L_ServoMotor1_Home;
	Leg1_L_ServoMotor2_CurrentPos = Leg1_L_ServoMotor2_Home;
	Leg1_L_ServoMotor3_CurrentPos = Leg1_L_ServoMotor3_Home;

	Leg2_L_ServoMotor1_CurrentPos = Leg2_L_ServoMotor1_Home;
	Leg2_L_ServoMotor2_CurrentPos = Leg2_L_ServoMotor2_Home;
	Leg2_L_ServoMotor3_CurrentPos = Leg2_L_ServoMotor3_Home;

	Leg3_L_ServoMotor1_CurrentPos = Leg3_L_ServoMotor1_Home;
	Leg3_L_ServoMotor2_CurrentPos = Leg3_L_ServoMotor2_Home;
	Leg3_L_ServoMotor3_CurrentPos = Leg3_L_ServoMotor3_Home;

	Leg4_L_ServoMotor1_CurrentPos = Leg4_L_ServoMotor1_Home;
	Leg4_L_ServoMotor2_CurrentPos = Leg4_L_ServoMotor2_Home;
	Leg4_L_ServoMotor3_CurrentPos = Leg4_L_ServoMotor3_Home;

	Leg1_R_ServoMotor1_CurrentPos = Leg1_R_ServoMotor1_Home;
	Leg1_R_ServoMotor2_CurrentPos = Leg1_R_ServoMotor2_Home;
	Leg1_R_ServoMotor3_CurrentPos = Leg1_R_ServoMotor3_Home;

	Leg2_R_ServoMotor1_CurrentPos = Leg2_R_ServoMotor1_Home;
	Leg2_R_ServoMotor2_CurrentPos = Leg2_R_ServoMotor2_Home;
	Leg2_R_ServoMotor3_CurrentPos = Leg2_R_ServoMotor3_Home;

	Leg3_R_ServoMotor1_CurrentPos = Leg3_R_ServoMotor1_Home;
	Leg3_R_ServoMotor2_CurrentPos = Leg3_R_ServoMotor2_Home;
	Leg3_R_ServoMotor3_CurrentPos = Leg3_R_ServoMotor3_Home;

	Leg4_R_ServoMotor1_CurrentPos = Leg4_R_ServoMotor1_Home;
	Leg4_R_ServoMotor2_CurrentPos = Leg4_R_ServoMotor2_Home;
	Leg4_R_ServoMotor3_CurrentPos = Leg4_R_ServoMotor3_Home;


	// LEFT SIDE LEGS
	pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor1_ChannelNum, 0, Leg1_L_ServoMotor1_CurrentPos); //Leg1_L_ServoMotor1_CurrentPos
	pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor2_ChannelNum, 0, Leg1_L_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor3_ChannelNum, 0, Leg1_L_ServoMotor3_CurrentPos);

	pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor1_ChannelNum, 0, Leg2_L_ServoMotor1_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor2_ChannelNum, 0, Leg2_L_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor3_ChannelNum, 0, Leg2_L_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor1_ChannelNum, 0, Leg3_L_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor2_ChannelNum, 0, Leg3_L_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor3_ChannelNum, 0, Leg3_L_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor1_ChannelNum, 0, Leg4_L_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor2_ChannelNum, 0, Leg4_L_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor3_ChannelNum, 0, Leg4_L_ServoMotor3_CurrentPos);


	// RIGHT SIDE LEGS
	pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor1_ChannelNum, 0, Leg1_R_ServoMotor1_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor2_ChannelNum, 0, Leg1_R_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor3_ChannelNum, 0, Leg1_R_ServoMotor3_CurrentPos);

	pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor1_ChannelNum, 0, Leg2_R_ServoMotor1_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor2_ChannelNum, 0, Leg2_R_ServoMotor2_CurrentPos);
	pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor3_ChannelNum, 0, Leg2_R_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor1_ChannelNum, 0, Leg3_R_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor2_ChannelNum, 0, Leg3_R_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor3_ChannelNum, 0, Leg3_R_ServoMotor3_CurrentPos);

	pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor1_ChannelNum, 0, Leg4_R_ServoMotor1_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor2_ChannelNum, 0, Leg4_R_ServoMotor2_CurrentPos);
	pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor3_ChannelNum, 0, Leg4_R_ServoMotor3_CurrentPos);

}

void commandIdleRandomMovement()
{
	// *****
	//	CONSIDERATION: could use the value of time_DelayBetweenIdleMovements (random number 100-3000) to influence
	//	the speed and path of the movement. For example: 
	//		1. If the time before the next
	//

	// complete an idle movement if a random amount of time has passed since last movement
	if (time_CurrentTime >= time_TimeForIdleMovement)
	{
		// generate a random number 100-3000 (milliseconds) representing the time before the next random movement
		time_DelayBetweenIdleMovements = random(100, 801);

		// set the time for the next movement
		time_TimeForIdleMovement = time_CurrentTime + time_DelayBetweenIdleMovements;

		// choose a random leg to move
		int randLeg1to8 = random(1, 9);

		// move the chosen leg up by an incremental distance that is repeated inside a loop. incremental disctance is random
		int randUpDist5to10 = random(5, 11);

		// move the leg at a variable speed by introducing a random time delay inside the movement loop
		int randDelayTime = random(7, 25);

		// calculate the size of movement for the motors that raise and lower the leg
		int motor2Movement = (2 * randUpDist5to10) / 2;
		int motor3Movement = (2 * randUpDist5to10) / 5;

		// 
		switch (randLeg1to8)
		{
		case 1:
			// leg 1 left side
			for (int i = 0; i<10; i++)
			{
				// leg 1 left side - move up
				Leg1_L_ServoMotor1_CurrentPos += 0;
				Leg1_L_ServoMotor2_CurrentPos += motor2Movement;
				Leg1_L_ServoMotor3_CurrentPos += motor3Movement;

				// leg 1 on left side
				pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor1_ChannelNum, 0, Leg1_L_ServoMotor1_CurrentPos);
				pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor2_ChannelNum, 0, Leg1_L_ServoMotor2_CurrentPos);
				pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor3_ChannelNum, 0, Leg1_L_ServoMotor3_CurrentPos);

				delay(randDelayTime);
			}

			// delay at peak
			delay(randDelayTime * 10);

			for (int i = 0; i<10; i++)
			{
				// leg 1 left side - move back down
				Leg1_L_ServoMotor1_CurrentPos -= 0;
				Leg1_L_ServoMotor2_CurrentPos -= motor2Movement;
				Leg1_L_ServoMotor3_CurrentPos -= motor3Movement;

				// leg 1 on left side
				pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor1_ChannelNum, 0, Leg1_L_ServoMotor1_CurrentPos);
				pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor2_ChannelNum, 0, Leg1_L_ServoMotor2_CurrentPos);
				pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor3_ChannelNum, 0, Leg1_L_ServoMotor3_CurrentPos);

				delay(randDelayTime);
			}

			break;

		case 2:
			// leg 1 right side
			for (int i = 0; i<10; i++)
			{
				// leg 1 left side - move up
				Leg1_R_ServoMotor1_CurrentPos -= 0;
				Leg1_R_ServoMotor2_CurrentPos -= motor2Movement;
				Leg1_R_ServoMotor3_CurrentPos -= motor3Movement;

				// leg 1 on left side
				pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor1_ChannelNum, 0, Leg1_R_ServoMotor1_CurrentPos);
				pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor2_ChannelNum, 0, Leg1_R_ServoMotor2_CurrentPos);
				pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor3_ChannelNum, 0, Leg1_R_ServoMotor3_CurrentPos);

				delay(randDelayTime);
			}

			// delay at peak
			delay(randDelayTime * 10);

			for (int i = 0; i<10; i++)
			{
				// leg 1 left side - move back down
				Leg1_R_ServoMotor1_CurrentPos += 0;
				Leg1_R_ServoMotor2_CurrentPos += motor2Movement;
				Leg1_R_ServoMotor3_CurrentPos += motor3Movement;

				// leg 1 on left side
				pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor1_ChannelNum, 0, Leg1_R_ServoMotor1_CurrentPos);
				pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor2_ChannelNum, 0, Leg1_R_ServoMotor2_CurrentPos);
				pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor3_ChannelNum, 0, Leg1_R_ServoMotor3_CurrentPos);

				delay(randDelayTime);
			}

			break;

		case 3:
			// leg 2 left side
			for (int i = 0; i<10; i++)
			{
				// leg 2 left side - move up
				Leg2_L_ServoMotor1_CurrentPos += 0;
				Leg2_L_ServoMotor2_CurrentPos += motor2Movement;
				Leg2_L_ServoMotor3_CurrentPos += motor3Movement;

				// leg 2 on left side
				pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor1_ChannelNum, 0, Leg2_L_ServoMotor1_CurrentPos);
				pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor2_ChannelNum, 0, Leg2_L_ServoMotor2_CurrentPos);
				pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor3_ChannelNum, 0, Leg2_L_ServoMotor3_CurrentPos);

				delay(randDelayTime);
			}

			// delay at peak
			delay(randDelayTime * 10);

			for (int i = 0; i<10; i++)
			{
				// leg 2 left side - move back down
				Leg2_L_ServoMotor1_CurrentPos -= 0;
				Leg2_L_ServoMotor2_CurrentPos -= motor2Movement;
				Leg2_L_ServoMotor3_CurrentPos -= motor3Movement;

				// leg 2 on left side
				pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor1_ChannelNum, 0, Leg2_L_ServoMotor1_CurrentPos);
				pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor2_ChannelNum, 0, Leg2_L_ServoMotor2_CurrentPos);
				pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor3_ChannelNum, 0, Leg2_L_ServoMotor3_CurrentPos);

				delay(randDelayTime);
			}

			break;

		case 4:
			// leg 2 right side
			for (int i = 0; i<10; i++)
			{
				// leg 2 left side - move up
				Leg2_R_ServoMotor1_CurrentPos -= 0;
				Leg2_R_ServoMotor2_CurrentPos -= motor2Movement;
				Leg2_R_ServoMotor3_CurrentPos -= motor3Movement;

				// leg 2 on right side
				pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor1_ChannelNum, 0, Leg2_R_ServoMotor1_CurrentPos);
				pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor2_ChannelNum, 0, Leg2_R_ServoMotor2_CurrentPos);
				pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor3_ChannelNum, 0, Leg2_R_ServoMotor3_CurrentPos);

				delay(randDelayTime);
			}

			// delay at peak
			delay(randDelayTime * 10);

			for (int i = 0; i<10; i++)
			{
				// leg 2 right side - move back down
				Leg2_R_ServoMotor1_CurrentPos += 0;
				Leg2_R_ServoMotor2_CurrentPos += motor2Movement;
				Leg2_R_ServoMotor3_CurrentPos += motor3Movement;

				// leg 2 on right side
				pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor1_ChannelNum, 0, Leg2_R_ServoMotor1_CurrentPos);
				pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor2_ChannelNum, 0, Leg2_R_ServoMotor2_CurrentPos);
				pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor3_ChannelNum, 0, Leg2_R_ServoMotor3_CurrentPos);

				delay(randDelayTime);
			}

			break;

		case 5:
			// leg 3 left side
			for (int i = 0; i<10; i++)
			{
				// leg 3 left side - move up
				Leg3_L_ServoMotor1_CurrentPos += 0;
				Leg3_L_ServoMotor2_CurrentPos += motor2Movement;
				Leg3_L_ServoMotor3_CurrentPos += motor3Movement;

				// leg 3 on left side
				pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor1_ChannelNum, 0, Leg3_L_ServoMotor1_CurrentPos);
				pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor2_ChannelNum, 0, Leg3_L_ServoMotor2_CurrentPos);
				pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor3_ChannelNum, 0, Leg3_L_ServoMotor3_CurrentPos);

				delay(randDelayTime);
			}

			// delay at peak
			delay(randDelayTime * 10);

			for (int i = 0; i<10; i++)
			{
				// leg 3 left side - move back down
				Leg3_L_ServoMotor1_CurrentPos -= 0;
				Leg3_L_ServoMotor2_CurrentPos -= motor2Movement;
				Leg3_L_ServoMotor3_CurrentPos -= motor3Movement;

				// leg 3 on left side
				pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor1_ChannelNum, 0, Leg3_L_ServoMotor1_CurrentPos);
				pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor2_ChannelNum, 0, Leg3_L_ServoMotor2_CurrentPos);
				pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor3_ChannelNum, 0, Leg3_L_ServoMotor3_CurrentPos);

				delay(randDelayTime);
			}

			break;

		case 6:
			// leg 3 right side
			for (int i = 0; i<10; i++)
			{
				// leg 3 right side - move up
				Leg3_R_ServoMotor1_CurrentPos -= 0;
				Leg3_R_ServoMotor2_CurrentPos -= motor2Movement;
				Leg3_R_ServoMotor3_CurrentPos -= motor3Movement;

				// leg 3 on right side
				pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor1_ChannelNum, 0, Leg3_R_ServoMotor1_CurrentPos);
				pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor2_ChannelNum, 0, Leg3_R_ServoMotor2_CurrentPos);
				pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor3_ChannelNum, 0, Leg3_R_ServoMotor3_CurrentPos);

				delay(randDelayTime);
			}

			// delay at peak
			delay(randDelayTime * 10);

			for (int i = 0; i<10; i++)
			{
				// leg 3 right side - move back down
				Leg3_R_ServoMotor1_CurrentPos += 0;
				Leg3_R_ServoMotor2_CurrentPos += motor2Movement;
				Leg3_R_ServoMotor3_CurrentPos += motor3Movement;

				// leg 3 on left side
				pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor1_ChannelNum, 0, Leg3_R_ServoMotor1_CurrentPos);
				pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor2_ChannelNum, 0, Leg3_R_ServoMotor2_CurrentPos);
				pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor3_ChannelNum, 0, Leg3_R_ServoMotor3_CurrentPos);

				delay(randDelayTime);
			}

			break;

		case 7:
			// leg 4 left side
			for (int i = 0; i<10; i++)
			{
				// leg 4 left side - move up
				Leg4_L_ServoMotor1_CurrentPos += 0;
				Leg4_L_ServoMotor2_CurrentPos += motor2Movement;
				Leg4_L_ServoMotor3_CurrentPos += motor3Movement;

				// leg 4 on left side
				pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor1_ChannelNum, 0, Leg4_L_ServoMotor1_CurrentPos);
				pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor2_ChannelNum, 0, Leg4_L_ServoMotor2_CurrentPos);
				pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor3_ChannelNum, 0, Leg4_L_ServoMotor3_CurrentPos);

				delay(randDelayTime);
			}

			// delay at peak
			delay(randDelayTime * 10);

			for (int i = 0; i<10; i++)
			{
				// leg 4 left side - move back down
				Leg4_L_ServoMotor1_CurrentPos -= 0;
				Leg4_L_ServoMotor2_CurrentPos -= motor2Movement;
				Leg4_L_ServoMotor3_CurrentPos -= motor3Movement;

				// leg 4 on left side
				pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor1_ChannelNum, 0, Leg4_L_ServoMotor1_CurrentPos);
				pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor2_ChannelNum, 0, Leg4_L_ServoMotor2_CurrentPos);
				pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor3_ChannelNum, 0, Leg4_L_ServoMotor3_CurrentPos);

				delay(randDelayTime);
			}

			break;

		case 8:
			// leg 4 right side
			for (int i = 0; i<10; i++)
			{
				// leg 4 right side - move up
				Leg4_R_ServoMotor1_CurrentPos -= 0;
				Leg4_R_ServoMotor2_CurrentPos -= motor2Movement;
				Leg4_R_ServoMotor3_CurrentPos -= motor3Movement;

				// leg 4 on right side
				pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor1_ChannelNum, 0, Leg4_R_ServoMotor1_CurrentPos);
				pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor2_ChannelNum, 0, Leg4_R_ServoMotor2_CurrentPos);
				pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor3_ChannelNum, 0, Leg4_R_ServoMotor3_CurrentPos);

				delay(randDelayTime);
			}

			// delay at peak
			delay(randDelayTime * 10);

			for (int i = 0; i<10; i++)
			{
				// leg 4 right side - move back down
				Leg4_R_ServoMotor1_CurrentPos += 0;
				Leg4_R_ServoMotor2_CurrentPos += motor2Movement;
				Leg4_R_ServoMotor3_CurrentPos += motor3Movement;

				// leg 4 on left side
				pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor1_ChannelNum, 0, Leg4_R_ServoMotor1_CurrentPos);
				pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor2_ChannelNum, 0, Leg4_R_ServoMotor2_CurrentPos);
				pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor3_ChannelNum, 0, Leg4_R_ServoMotor3_CurrentPos);

				delay(randDelayTime);
			}

			break;

			// this is the end of the SELECT that checks for which leg to move
		}

		// this is the end of the IF that checks if it was time to complete an idle movement
	}

}


void commandR2L2Walking(int distLeft, int distRight)
{
	// Forward:					When distLeft=1 and distRight=1 (the robot walks straight forward)
	// Forward Left:			When distLeft=2 and distRight=1 (the robot turns Left as it walks)
	// Forward Right:			When distLeft=1 and distRight=2 (the robot turns Right as it walks)
	// Forward Hard Left:		When distLeft=3 and distRight=1 (the robot turns Hard Left as it walks)
	// Forward Hard Right:		When distLeft=1 and distRight=3 (the robot turns Hard Right as it walks)

	// Backward:				When distLeft=-1 and distRight=-1 (the robot walks straight backward)
	// Backward Left:			When distLeft=-2 and distRight=-1 (the robot turns Left as it walks backward)
	// Backward Right:			When distLeft=-1 and distRight=-2 (the robot turns Right as it walks backward)
	// Backward Hard Left:		When distLeft=-3 and distRight=-1 (the robot turns Hard Left as it walks backward)
	// Backward Hard Right:		When distLeft=-1 and distRight=-3 (the robot turns Hard Right as it walks backward)
	//
	// Spin Clockwise:			When distLeft=1 and distRight=-1 (the robot spins clockwise - left side walks forward while right side walks backward)
	// Spin Counter-Clockwise:	When distLeft=-1 and distRight=1 (the robot spins counter-clockwise - left side walks backward while right side walks forward)
	//
	//
	int incrementalMoveHipForwardBackwardLeft = Leg_HipMoveForwardIncrement / distLeft;		// 
	int incrementalMoveHipForwardBackwardRight = Leg_HipMoveForwardIncrement / distRight;	//
	int incrementalMoveHipUpDown = Leg_HipMoveUpDownIncrement;
	int incrementalMoveKneeUpDown = Leg_KneeMoveUpDownIncrement;

	// The backward step process is:
	//  1. Move L1L3R2R4 legs up above the home position to take weight off these legs
	//  < 8. Move R1R3L2L4 legs forward to home position (moving the body backward while other legs are off the floor) >
	//  2. Move L1L3R2R4 legs backward through air
	//  3. Move L1L3R2R4 legs down to the home position (slightly below the home position to take weight off other legs?)
	//
	//	4. Move R1R3L2L4 legs up above the home position to take weight off these legs
	//  5. Move L1L3R2R4 legs forward to home position (moving the body backward while other legs are off the floor)
	//	6. Move R1R3L2L4 legs backward through air
	//  7. Move R1R3L2L4 legs down to the home position (below the home position to take weight off other legs?)
	//
	// repeat...
	//  1. Move L1L3R2R4 legs up above the home position to take weight off these legs
	//
	//

	for (int i = 1; i <= 20; i++)
	{
		//  1. Move L1L3R2R4 legs up above the home position to take weight off these legs
		//  < 8. Move R1R3L2L4 legs forward to home position (moving the body backward while other legs are off the floor) >
		//  2. Move L1L3R2R4 legs backward through air
		//  3. Move L1L3R2R4 legs down to the home position (slightly below the home position to take weight off other legs?)


		// always set the "move-to" position for the legs
		//		1.	For the first half of the loop, leg positions are moving up
		//		2.	For the second half of the loop, leg positions are moving back down to home
		//
		if (i <= 10)
		{
			// first half of the loop, so set the position for moving left legs up
			Leg1_L_ServoMotor2_CurrentPos += incrementalMoveHipUpDown;
			Leg1_L_ServoMotor3_CurrentPos += incrementalMoveKneeUpDown;

			Leg3_L_ServoMotor2_CurrentPos += incrementalMoveHipUpDown;
			Leg3_L_ServoMotor3_CurrentPos += incrementalMoveKneeUpDown;

			// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
			Leg2_R_ServoMotor2_CurrentPos -= incrementalMoveHipUpDown;
			Leg2_R_ServoMotor3_CurrentPos -= incrementalMoveKneeUpDown;

			Leg4_R_ServoMotor2_CurrentPos -= incrementalMoveHipUpDown;
			Leg4_R_ServoMotor3_CurrentPos -= incrementalMoveKneeUpDown;

		}

		else
		{
			// move legs back down
			Leg1_L_ServoMotor2_CurrentPos -= incrementalMoveHipUpDown;
			Leg1_L_ServoMotor3_CurrentPos -= incrementalMoveKneeUpDown;

			Leg3_L_ServoMotor2_CurrentPos -= incrementalMoveHipUpDown;
			Leg3_L_ServoMotor3_CurrentPos -= incrementalMoveKneeUpDown;

			// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
			Leg2_R_ServoMotor2_CurrentPos += incrementalMoveHipUpDown;
			Leg2_R_ServoMotor3_CurrentPos += incrementalMoveKneeUpDown;

			Leg4_R_ServoMotor2_CurrentPos += incrementalMoveHipUpDown;
			Leg4_R_ServoMotor3_CurrentPos += incrementalMoveKneeUpDown;

		}

		// in the middle of the loop, while the L1L3R2R4 legs are raised off the ground, move them backward
		//
		if (i>5 && i<16)
		{
			// move legs backward (subtrack the forward increment for left legs)
			Leg1_L_ServoMotor1_CurrentPos -= incrementalMoveHipForwardBackwardLeft;
			Leg3_L_ServoMotor1_CurrentPos -= incrementalMoveHipForwardBackwardLeft;

			// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
			Leg2_R_ServoMotor1_CurrentPos += incrementalMoveHipForwardBackwardRight;
			Leg4_R_ServoMotor1_CurrentPos += incrementalMoveHipForwardBackwardRight;

		}

		// at the beginning of the loop, check to see if the R1R3L2L4 were moved backward in a previous loop
		//
		if (i>2 && i<13 && R1R3L2L4_backward == true)
		{
			// move R1R3L2L4 legs backward
			Leg1_R_ServoMotor1_CurrentPos -= incrementalMoveHipForwardBackwardRight;
			Leg3_R_ServoMotor1_CurrentPos -= incrementalMoveHipForwardBackwardRight;

			// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
			Leg2_L_ServoMotor1_CurrentPos += incrementalMoveHipForwardBackwardLeft;
			Leg4_L_ServoMotor1_CurrentPos += incrementalMoveHipForwardBackwardLeft;

			// set R1R3L2L4_backward to false once the position is reached
			if (i == 12)
			{
				R1R3L2L4_backward = false;
			}
		}

		// Now that all position settings have been calculated, perform the actual servo positioning
		//

		// leg 1 on left side
		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor1_ChannelNum, 0, Leg1_L_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor2_ChannelNum, 0, Leg1_L_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor3_ChannelNum, 0, Leg1_L_ServoMotor3_CurrentPos);

		// leg 1 right side
		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor1_ChannelNum, 0, Leg1_R_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor2_ChannelNum, 0, Leg1_R_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor3_ChannelNum, 0, Leg1_R_ServoMotor3_CurrentPos);

		// leg 2 left side
		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor1_ChannelNum, 0, Leg2_L_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor2_ChannelNum, 0, Leg2_L_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor3_ChannelNum, 0, Leg2_L_ServoMotor3_CurrentPos);

		// leg 2 on right side
		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor1_ChannelNum, 0, Leg2_R_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor2_ChannelNum, 0, Leg2_R_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor3_ChannelNum, 0, Leg2_R_ServoMotor3_CurrentPos);

		// leg 3 on left side
		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor1_ChannelNum, 0, Leg3_L_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor2_ChannelNum, 0, Leg3_L_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor3_ChannelNum, 0, Leg3_L_ServoMotor3_CurrentPos);

		// leg 3 right side
		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor1_ChannelNum, 0, Leg3_R_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor2_ChannelNum, 0, Leg3_R_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor3_ChannelNum, 0, Leg3_R_ServoMotor3_CurrentPos);

		// leg 4 left side
		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor1_ChannelNum, 0, Leg4_L_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor2_ChannelNum, 0, Leg4_L_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor3_ChannelNum, 0, Leg4_L_ServoMotor3_CurrentPos);

		// leg 4 on right side
		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor1_ChannelNum, 0, Leg4_R_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor2_ChannelNum, 0, Leg4_R_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor3_ChannelNum, 0, Leg4_R_ServoMotor3_CurrentPos);

		// delay the loop to control the speed of leg movement
		delay(legSpeed);
	}

	delay(legSpeed * 4);


	// this loop is for stepping the R1R3L2L4 legs backward and moving the L1L3R2R4 legs back to home
	for (int i = 1; i <= 20; i++)
	{
		//	4. Move R1R3L2L4 legs up above the home position to take weight off these legs
		//  5. Move L1L3R2R4 legs forward to home position (moving the body backward while other legs are off the floor)
		//	6. Move R1R3L2L4 legs backward through air
		//  7. Move R1R3L2L4 legs down to the home position (below the home position to take weight off other legs?)

		// set the "move-to" position
		if (i <= 10)
		{
			// move legs up
			Leg1_R_ServoMotor2_CurrentPos -= incrementalMoveHipUpDown;
			Leg1_R_ServoMotor3_CurrentPos -= incrementalMoveKneeUpDown;

			Leg3_R_ServoMotor2_CurrentPos -= incrementalMoveHipUpDown;
			Leg3_R_ServoMotor3_CurrentPos -= incrementalMoveKneeUpDown;

			// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
			Leg2_L_ServoMotor2_CurrentPos += incrementalMoveHipUpDown;
			Leg2_L_ServoMotor3_CurrentPos += incrementalMoveKneeUpDown;

			Leg4_L_ServoMotor2_CurrentPos += incrementalMoveHipUpDown;
			Leg4_L_ServoMotor3_CurrentPos += incrementalMoveKneeUpDown;

		}

		else
		{
			// move legs down
			Leg1_R_ServoMotor2_CurrentPos += incrementalMoveHipUpDown;
			Leg1_R_ServoMotor3_CurrentPos += incrementalMoveKneeUpDown;

			Leg3_R_ServoMotor2_CurrentPos += incrementalMoveHipUpDown;
			Leg3_R_ServoMotor3_CurrentPos += incrementalMoveKneeUpDown;

			// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
			Leg2_L_ServoMotor2_CurrentPos -= incrementalMoveHipUpDown;
			Leg2_L_ServoMotor3_CurrentPos -= incrementalMoveKneeUpDown;

			Leg4_L_ServoMotor2_CurrentPos -= incrementalMoveHipUpDown;
			Leg4_L_ServoMotor3_CurrentPos -= incrementalMoveKneeUpDown;

		}

		if (i>5 && i<16)
		{
			// move R1R3L2L4 legs backward
			Leg1_R_ServoMotor1_CurrentPos += incrementalMoveHipForwardBackwardRight;
			Leg3_R_ServoMotor1_CurrentPos += incrementalMoveHipForwardBackwardRight;

			// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
			Leg2_L_ServoMotor1_CurrentPos -= incrementalMoveHipForwardBackwardLeft;
			Leg4_L_ServoMotor1_CurrentPos -= incrementalMoveHipForwardBackwardLeft;

			// 
			R1R3L2L4_backward = true;
		}

		if (i>2 && i<13)
		{
			// the L1L3R2R4 legs were moved backward in the first loop above
			//
			// move the L1L3R2R4 legs forward
			Leg1_L_ServoMotor1_CurrentPos += incrementalMoveHipForwardBackwardLeft;
			Leg3_L_ServoMotor1_CurrentPos += incrementalMoveHipForwardBackwardLeft;

			// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
			Leg2_R_ServoMotor1_CurrentPos -= incrementalMoveHipForwardBackwardRight;
			Leg4_R_ServoMotor1_CurrentPos -= incrementalMoveHipForwardBackwardRight;

			//L1L3R2R4_forward = false;
		}


		// leg 1 on left side
		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor1_ChannelNum, 0, Leg1_L_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor2_ChannelNum, 0, Leg1_L_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor3_ChannelNum, 0, Leg1_L_ServoMotor3_CurrentPos);

		// leg 1 right side
		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor1_ChannelNum, 0, Leg1_R_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor2_ChannelNum, 0, Leg1_R_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor3_ChannelNum, 0, Leg1_R_ServoMotor3_CurrentPos);

		// leg 2 left side
		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor1_ChannelNum, 0, Leg2_L_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor2_ChannelNum, 0, Leg2_L_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor3_ChannelNum, 0, Leg2_L_ServoMotor3_CurrentPos);

		// leg 2 on right side
		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor1_ChannelNum, 0, Leg2_R_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor2_ChannelNum, 0, Leg2_R_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor3_ChannelNum, 0, Leg2_R_ServoMotor3_CurrentPos);

		// leg 3 on left side
		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor1_ChannelNum, 0, Leg3_L_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor2_ChannelNum, 0, Leg3_L_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor3_ChannelNum, 0, Leg3_L_ServoMotor3_CurrentPos);

		// leg 3 right side
		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor1_ChannelNum, 0, Leg3_R_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor2_ChannelNum, 0, Leg3_R_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor3_ChannelNum, 0, Leg3_R_ServoMotor3_CurrentPos);

		// leg 4 left side
		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor1_ChannelNum, 0, Leg4_L_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor2_ChannelNum, 0, Leg4_L_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor3_ChannelNum, 0, Leg4_L_ServoMotor3_CurrentPos);

		// leg 4 on right side
		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor1_ChannelNum, 0, Leg4_R_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor2_ChannelNum, 0, Leg4_R_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor3_ChannelNum, 0, Leg4_R_ServoMotor3_CurrentPos);

		delay(legSpeed);

	}

	delay(legSpeed * 4);


}


void commandR2L2ForwardWalking()
{

	// The forward step process is:
	//  1. Move L1L3R2R4 legs up above the home position to take weight off these legs
	//  < 8. Move R1R3L2L4 legs backward to home position (moving the body forward while other legs are off the floor) >
	//  2. Move L1L3R2R4 legs forward through air
	//  3. Move L1L3R2R4 legs down to the home position (slightly below the home position to take weight off other legs?)
	//
	//	4. Move R1R3L2L4 legs up above the home position to take weight off these legs
	//  5. Move L1L3R2R4 legs backward to home position (moving the body forward while other legs are off the floor)
	//	6. Move R1R3L2L4 legs forward through air
	//  7. Move R1R3L2L4 legs down to the home position (below the home position to take weight off other legs?)
	//
	// repeat...
	//  1. Move L1L3R2R4 legs up above the home position to take weight off these legs
	//
	//

	for (int i = 1; i <= 20; i++)
	{
		//  1. Move L1L3R2R4 legs up above the home position to take weight off these legs
		//  < 8. Move R1R3L2L4 legs backward to home position (moving the body forward while other legs are off the floor) >
		//  2. Move L1L3R2R4 legs forward through air
		//  3. Move L1L3R2R4 legs down to the home position (slightly below the home position to take weight off other legs?)


		// always set the "move-to" position for the legs
		//		1.	For the first half of the loop, leg positions are moving up
		//		2.	For the second half of the loop, leg positions are mving back down to home
		//
		if (i <= 10)
		{
			// first half of the loop, so set the position for moving left legs up
			Leg1_L_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
			Leg1_L_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

			Leg3_L_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
			Leg3_L_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

			// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
			Leg2_R_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
			Leg2_R_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

			Leg4_R_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
			Leg4_R_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

		}

		else
		{
			// move legs back down
			Leg1_L_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
			Leg1_L_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

			Leg3_L_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
			Leg3_L_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

			// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
			Leg2_R_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
			Leg2_R_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

			Leg4_R_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
			Leg4_R_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

		}

		// in the middle of the loop, while the L1L3R2R4 legs are raised off the ground, move them forward
		//
		if (i>5 && i<16)
		{
			// move legs forward
			Leg1_L_ServoMotor1_CurrentPos += Leg_HipMoveForwardIncrement;
			Leg3_L_ServoMotor1_CurrentPos += Leg_HipMoveForwardIncrement;

			// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
			Leg2_R_ServoMotor1_CurrentPos -= Leg_HipMoveForwardIncrement;
			Leg4_R_ServoMotor1_CurrentPos -= Leg_HipMoveForwardIncrement;

		}

		// at the beginning of the loop, check to see if the R1R3L2L4 were moved forward in a previous loop
		//
		if (i>2 && i<13 && R1R3L2L4_forward == true)
		{
			// move R1R3L2L4 legs backward
			Leg1_R_ServoMotor1_CurrentPos += Leg_HipMoveForwardIncrement;
			Leg3_R_ServoMotor1_CurrentPos += Leg_HipMoveForwardIncrement;

			// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
			Leg2_L_ServoMotor1_CurrentPos -= Leg_HipMoveForwardIncrement;
			Leg4_L_ServoMotor1_CurrentPos -= Leg_HipMoveForwardIncrement;

			// set R1R3L2L4_forward to false once the position is reached
			if (i == 12)
			{
				R1R3L2L4_forward = false;
			}
		}

		// Now that all position settings have been calculated, perform the actual servo positioning
		//

		// leg 1 on left side
		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor1_ChannelNum, 0, Leg1_L_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor2_ChannelNum, 0, Leg1_L_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor3_ChannelNum, 0, Leg1_L_ServoMotor3_CurrentPos);

		// leg 1 right side
		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor1_ChannelNum, 0, Leg1_R_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor2_ChannelNum, 0, Leg1_R_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor3_ChannelNum, 0, Leg1_R_ServoMotor3_CurrentPos);

		// leg 2 left side
		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor1_ChannelNum, 0, Leg2_L_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor2_ChannelNum, 0, Leg2_L_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor3_ChannelNum, 0, Leg2_L_ServoMotor3_CurrentPos);

		// leg 2 on right side
		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor1_ChannelNum, 0, Leg2_R_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor2_ChannelNum, 0, Leg2_R_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor3_ChannelNum, 0, Leg2_R_ServoMotor3_CurrentPos);

		// leg 3 on left side
		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor1_ChannelNum, 0, Leg3_L_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor2_ChannelNum, 0, Leg3_L_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor3_ChannelNum, 0, Leg3_L_ServoMotor3_CurrentPos);

		// leg 3 right side
		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor1_ChannelNum, 0, Leg3_R_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor2_ChannelNum, 0, Leg3_R_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor3_ChannelNum, 0, Leg3_R_ServoMotor3_CurrentPos);

		// leg 4 left side
		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor1_ChannelNum, 0, Leg4_L_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor2_ChannelNum, 0, Leg4_L_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor3_ChannelNum, 0, Leg4_L_ServoMotor3_CurrentPos);

		// leg 4 on right side
		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor1_ChannelNum, 0, Leg4_R_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor2_ChannelNum, 0, Leg4_R_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor3_ChannelNum, 0, Leg4_R_ServoMotor3_CurrentPos);

		// delay the loop to control the speed of leg movement
		delay(legSpeed);
	}

	delay(legSpeed * 4);


	// this loop is for stepping the R1R3L2L4 legs forward and moving the L1L3R2R4 legs back
	for (int i = 1; i <= 20; i++)
	{
		//	4. Move R1R3L2L4 legs up above the home position to take weight off these legs
		//  5. Move L1L3R2R4 legs backward to home position (moving the body forward while other legs are off the floor)
		//	6. Move R1R3L2L4 legs forward through air
		//  7. Move R1R3L2L4 legs down to the home position (below the home position to take weight off other legs?)

		// set the "move-to" position
		if (i <= 10)
		{
			// move legs up
			Leg1_R_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
			Leg1_R_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

			Leg3_R_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
			Leg3_R_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

			// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
			Leg2_L_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
			Leg2_L_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

			Leg4_L_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
			Leg4_L_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

		}

		else
		{
			// move legs down
			Leg1_R_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
			Leg1_R_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

			Leg3_R_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
			Leg3_R_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

			// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
			Leg2_L_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
			Leg2_L_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

			Leg4_L_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
			Leg4_L_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

		}

		if (i>5 && i<16)
		{
			// move R1R3L2L4 legs forward
			Leg1_R_ServoMotor1_CurrentPos -= Leg_HipMoveForwardIncrement;
			Leg3_R_ServoMotor1_CurrentPos -= Leg_HipMoveForwardIncrement;

			// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
			Leg2_L_ServoMotor1_CurrentPos += Leg_HipMoveForwardIncrement;
			Leg4_L_ServoMotor1_CurrentPos += Leg_HipMoveForwardIncrement;

			// 
			R1R3L2L4_forward = true;
		}

		if (i>2 && i<13)
		{
			// the L1L3R2R4 legs were moved forward in the first loop above
			//
			// move the L1L3R2R4 legs backward
			Leg1_L_ServoMotor1_CurrentPos -= Leg_HipMoveForwardIncrement;
			Leg3_L_ServoMotor1_CurrentPos -= Leg_HipMoveForwardIncrement;

			// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
			Leg2_R_ServoMotor1_CurrentPos += Leg_HipMoveForwardIncrement;
			Leg4_R_ServoMotor1_CurrentPos += Leg_HipMoveForwardIncrement;

			//L1L3R2R4_forward = false;
		}


		// leg 1 on left side
		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor1_ChannelNum, 0, Leg1_L_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor2_ChannelNum, 0, Leg1_L_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor3_ChannelNum, 0, Leg1_L_ServoMotor3_CurrentPos);

		// leg 1 right side
		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor1_ChannelNum, 0, Leg1_R_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor2_ChannelNum, 0, Leg1_R_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor3_ChannelNum, 0, Leg1_R_ServoMotor3_CurrentPos);

		// leg 2 left side
		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor1_ChannelNum, 0, Leg2_L_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor2_ChannelNum, 0, Leg2_L_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor3_ChannelNum, 0, Leg2_L_ServoMotor3_CurrentPos);

		// leg 2 on right side
		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor1_ChannelNum, 0, Leg2_R_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor2_ChannelNum, 0, Leg2_R_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor3_ChannelNum, 0, Leg2_R_ServoMotor3_CurrentPos);

		// leg 3 on left side
		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor1_ChannelNum, 0, Leg3_L_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor2_ChannelNum, 0, Leg3_L_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor3_ChannelNum, 0, Leg3_L_ServoMotor3_CurrentPos);

		// leg 3 right side
		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor1_ChannelNum, 0, Leg3_R_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor2_ChannelNum, 0, Leg3_R_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor3_ChannelNum, 0, Leg3_R_ServoMotor3_CurrentPos);

		// leg 4 left side
		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor1_ChannelNum, 0, Leg4_L_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor2_ChannelNum, 0, Leg4_L_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor3_ChannelNum, 0, Leg4_L_ServoMotor3_CurrentPos);

		// leg 4 on right side
		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor1_ChannelNum, 0, Leg4_R_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor2_ChannelNum, 0, Leg4_R_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor3_ChannelNum, 0, Leg4_R_ServoMotor3_CurrentPos);

		delay(legSpeed);

	}

	delay(legSpeed * 4);

}


void oneLegForwardWalking()
{
	// find the rearmost leg and move it forward by a distance = stepForward
	//
	//		Left Side:	Current - Home is positive when the leg is toward the back
	//		Right Side:	Home - Current is positive when the leg is toward the back
	//
	int leg1_L_BackFromHome = Leg1_L_ServoMotor1_CurrentPos - Leg1_L_ServoMotor1_Home;
	int leg2_L_BackFromHome = Leg2_L_ServoMotor1_CurrentPos - Leg2_L_ServoMotor1_Home;
	int leg3_L_BackFromHome = Leg3_L_ServoMotor1_CurrentPos - Leg3_L_ServoMotor1_Home;
	int leg4_L_BackFromHome = Leg4_L_ServoMotor1_CurrentPos - Leg4_L_ServoMotor1_Home;

	int leg1_R_BackFromHome = Leg1_R_ServoMotor1_Home - Leg1_R_ServoMotor1_CurrentPos;
	int leg2_R_BackFromHome = Leg2_R_ServoMotor1_Home - Leg2_R_ServoMotor1_CurrentPos;
	int leg3_R_BackFromHome = Leg3_R_ServoMotor1_Home - Leg3_R_ServoMotor1_CurrentPos;
	int leg4_R_BackFromHome = Leg4_R_ServoMotor1_Home - Leg4_R_ServoMotor1_CurrentPos;

	int rearMostLeg = leg1_L_BackFromHome;
	int legNumber = 1;

	if (leg1_R_BackFromHome > rearMostLeg)
	{
		legNumber = 2;
	}

	if (leg2_L_BackFromHome > rearMostLeg)
	{
		legNumber = 3;
	}

	if (leg2_R_BackFromHome > rearMostLeg)
	{
		legNumber = 4;
	}


	if (leg3_L_BackFromHome > rearMostLeg)
	{
		legNumber = 5;
	}

	if (leg3_R_BackFromHome > rearMostLeg)
	{
		legNumber = 6;
	}


	if (leg4_L_BackFromHome > rearMostLeg)
	{
		legNumber = 7;
	}

	if (leg4_R_BackFromHome > rearMostLeg)
	{
		legNumber = 8;
	}

	switch (legNumber)
	{
	case 1:
		break;
	default:
		break;
	}
	// move all 8 legs back by a distance = (stepForward / 8)

}


void forwardStep_L1L3R2R4()
{
	// The forward step process is:
	//  1. Move leg up above the home position to take weight off leg
	//  2. Move leg forward through air
	//  3. Move leg down below home position to take weight off other legs
	//  4. Move leg backward to home position (moving the body forward while other legs are off the floor)
	//  5. Move leg up to home position (all motors are now returned to Home position)


	for (int i = 1; i <= 10; i++)
	{
		// set the "move-to" position
		Leg1_L_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
		Leg1_L_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

		Leg3_L_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
		Leg3_L_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

		// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
		Leg2_R_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
		Leg2_R_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

		Leg4_R_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
		Leg4_R_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

		//    
		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor2_ChannelNum, 0, Leg1_L_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor3_ChannelNum, 0, Leg1_L_ServoMotor3_CurrentPos);

		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor2_ChannelNum, 0, Leg3_L_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor3_ChannelNum, 0, Leg3_L_ServoMotor3_CurrentPos);

		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor2_ChannelNum, 0, Leg2_R_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor3_ChannelNum, 0, Leg2_R_ServoMotor3_CurrentPos);

		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor2_ChannelNum, 0, Leg4_R_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor3_ChannelNum, 0, Leg4_R_ServoMotor3_CurrentPos);

		delay(legSpeed);
	}

	delay(legSpeed * 4);

	for (int i = 1; i <= 10; i++)
	{
		Leg1_L_ServoMotor1_CurrentPos -= Leg_HipMoveForwardIncrement;
		Leg3_L_ServoMotor1_CurrentPos -= Leg_HipMoveForwardIncrement;

		// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
		Leg2_R_ServoMotor1_CurrentPos += Leg_HipMoveForwardIncrement;
		Leg4_R_ServoMotor1_CurrentPos += Leg_HipMoveForwardIncrement;

		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor1_ChannelNum, 0, Leg1_L_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor1_ChannelNum, 0, Leg3_L_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor1_ChannelNum, 0, Leg2_R_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor1_ChannelNum, 0, Leg4_R_ServoMotor1_CurrentPos);

		delay(legSpeed);
	}

	delay(legSpeed * 4);

	for (int i = 1; i <= 20; i++)
	{
		Leg1_L_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
		Leg1_L_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

		Leg3_L_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
		Leg3_L_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

		// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
		Leg2_R_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
		Leg2_R_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

		Leg4_R_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
		Leg4_R_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor2_ChannelNum, 0, Leg1_L_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor3_ChannelNum, 0, Leg1_L_ServoMotor3_CurrentPos);

		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor2_ChannelNum, 0, Leg3_L_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor3_ChannelNum, 0, Leg3_L_ServoMotor3_CurrentPos);

		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor2_ChannelNum, 0, Leg2_R_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor3_ChannelNum, 0, Leg2_R_ServoMotor3_CurrentPos);

		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor2_ChannelNum, 0, Leg4_R_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor3_ChannelNum, 0, Leg4_R_ServoMotor3_CurrentPos);

		delay(legSpeed);
	}

	delay(legSpeed * 4);

	for (int i = 1; i <= 10; i++)
	{
		Leg1_L_ServoMotor1_CurrentPos += Leg_HipMoveForwardIncrement;
		Leg3_L_ServoMotor1_CurrentPos += Leg_HipMoveForwardIncrement;

		// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
		Leg2_R_ServoMotor1_CurrentPos -= Leg_HipMoveForwardIncrement;
		Leg4_R_ServoMotor1_CurrentPos -= Leg_HipMoveForwardIncrement;

		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor1_ChannelNum, 0, Leg1_L_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor1_ChannelNum, 0, Leg3_L_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor1_ChannelNum, 0, Leg2_R_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor1_ChannelNum, 0, Leg4_R_ServoMotor1_CurrentPos);

		delay(legSpeed);
	}

	delay(legSpeed * 4);

	for (int i = 1; i <= 10; i++)
	{
		Leg1_L_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
		Leg1_L_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

		Leg3_L_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
		Leg3_L_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

		// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
		Leg2_R_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
		Leg2_R_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

		Leg4_R_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
		Leg4_R_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor2_ChannelNum, 0, Leg1_L_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_L_ServoMotor3_ChannelNum, 0, Leg1_L_ServoMotor3_CurrentPos);

		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor2_ChannelNum, 0, Leg3_L_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_L_ServoMotor3_ChannelNum, 0, Leg3_L_ServoMotor3_CurrentPos);

		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor2_ChannelNum, 0, Leg2_R_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_R_ServoMotor3_ChannelNum, 0, Leg2_R_ServoMotor3_CurrentPos);

		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor2_ChannelNum, 0, Leg4_R_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_R_ServoMotor3_ChannelNum, 0, Leg4_R_ServoMotor3_CurrentPos);

		delay(legSpeed);
	}

}

void forwardStep_L2L4R1R3()
{

	// The forward step process is:
	//  1. Move leg up above the home position to take weight off leg
	//  2. Move leg forward through air
	//  3. Move leg down below home position to take weight off other legs
	//  4. Move leg backward to home position (moving the body forward while other legs are off the floor)
	//  5. Move leg up to home position (all motors are now returned to Home position)

	for (int i = 1; i <= 10; i++)
	{
		// set the "move-to" position
		Leg1_R_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
		Leg1_R_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

		Leg3_R_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
		Leg3_R_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

		// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
		Leg2_L_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
		Leg2_L_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

		Leg4_L_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
		Leg4_L_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

		//    
		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor2_ChannelNum, 0, Leg1_R_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor3_ChannelNum, 0, Leg1_R_ServoMotor3_CurrentPos);

		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor2_ChannelNum, 0, Leg3_R_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor3_ChannelNum, 0, Leg3_R_ServoMotor3_CurrentPos);

		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor2_ChannelNum, 0, Leg2_L_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor3_ChannelNum, 0, Leg2_L_ServoMotor3_CurrentPos);

		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor2_ChannelNum, 0, Leg4_L_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor3_ChannelNum, 0, Leg4_L_ServoMotor3_CurrentPos);

		delay(legSpeed);
	}

	delay(legSpeed * 4);

	for (int i = 1; i <= 10; i++)
	{
		Leg1_R_ServoMotor1_CurrentPos += Leg_HipMoveForwardIncrement;
		Leg3_R_ServoMotor1_CurrentPos += Leg_HipMoveForwardIncrement;

		// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
		Leg2_L_ServoMotor1_CurrentPos -= Leg_HipMoveForwardIncrement;
		Leg4_L_ServoMotor1_CurrentPos -= Leg_HipMoveForwardIncrement;

		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor1_ChannelNum, 0, Leg1_R_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor1_ChannelNum, 0, Leg3_R_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor1_ChannelNum, 0, Leg2_L_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor1_ChannelNum, 0, Leg4_L_ServoMotor1_CurrentPos);

		delay(legSpeed);
	}

	delay(legSpeed * 4);

	for (int i = 1; i <= 20; i++)
	{
		Leg1_R_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
		Leg1_R_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

		Leg3_R_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
		Leg3_R_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

		// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
		Leg2_L_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
		Leg2_L_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

		Leg4_L_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
		Leg4_L_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor2_ChannelNum, 0, Leg1_R_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor3_ChannelNum, 0, Leg1_R_ServoMotor3_CurrentPos);

		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor2_ChannelNum, 0, Leg3_R_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor3_ChannelNum, 0, Leg3_R_ServoMotor3_CurrentPos);

		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor2_ChannelNum, 0, Leg2_L_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor3_ChannelNum, 0, Leg2_L_ServoMotor3_CurrentPos);

		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor2_ChannelNum, 0, Leg4_L_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor3_ChannelNum, 0, Leg4_L_ServoMotor3_CurrentPos);

		delay(legSpeed);
	}

	delay(legSpeed * 4);

	for (int i = 1; i <= 10; i++)
	{
		Leg1_R_ServoMotor1_CurrentPos -= Leg_HipMoveForwardIncrement;
		Leg3_R_ServoMotor1_CurrentPos -= Leg_HipMoveForwardIncrement;

		// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
		Leg2_L_ServoMotor1_CurrentPos += Leg_HipMoveForwardIncrement;
		Leg4_L_ServoMotor1_CurrentPos += Leg_HipMoveForwardIncrement;

		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor1_ChannelNum, 0, Leg1_R_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor1_ChannelNum, 0, Leg3_R_ServoMotor1_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor1_ChannelNum, 0, Leg2_L_ServoMotor1_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor1_ChannelNum, 0, Leg4_L_ServoMotor1_CurrentPos);

		delay(legSpeed);
	}

	delay(legSpeed * 4);

	for (int i = 1; i <= 10; i++)
	{
		Leg1_R_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
		Leg1_R_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

		Leg3_R_ServoMotor2_CurrentPos -= Leg_HipMoveUpDownIncrement;
		Leg3_R_ServoMotor3_CurrentPos -= Leg_KneeMoveUpDownIncrement;

		// servo motor orientatioon is reversed from side to side, so reverse sign of movement delta
		Leg2_L_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
		Leg2_L_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

		Leg4_L_ServoMotor2_CurrentPos += Leg_HipMoveUpDownIncrement;
		Leg4_L_ServoMotor3_CurrentPos += Leg_KneeMoveUpDownIncrement;

		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor2_ChannelNum, 0, Leg1_R_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg1_R_ServoMotor3_ChannelNum, 0, Leg1_R_ServoMotor3_CurrentPos);

		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor2_ChannelNum, 0, Leg3_R_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg3_R_ServoMotor3_ChannelNum, 0, Leg3_R_ServoMotor3_CurrentPos);

		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor2_ChannelNum, 0, Leg2_L_ServoMotor2_CurrentPos);
		pwmServoDriverFrontLegs.setPWM(Leg2_L_ServoMotor3_ChannelNum, 0, Leg2_L_ServoMotor3_CurrentPos);

		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor2_ChannelNum, 0, Leg4_L_ServoMotor2_CurrentPos);
		pwmServoDriverRearLegs.setPWM(Leg4_L_ServoMotor3_ChannelNum, 0, Leg4_L_ServoMotor3_CurrentPos);

		delay(legSpeed);
	}

}
