#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     ,               sensorI2CCustom)
#pragma config(Sensor, S3,     ,               sensorI2CCustom)
#pragma config(Sensor, S4,     touchSensor,    sensorTouch)
#pragma config(Motor,  motorA,          lightMotor,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     LF,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     RF,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     LR,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     RR,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     lifterMotor,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    left_servo,           tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    shoulder,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    wrist,                tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    extra_servo,          tServoStandard)
#pragma config(Servo,  srvo_S1_C4_6,    right_servo,          tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "joystickdriver.c"

#include "drivers/common.h"
#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-gyro.h"
#include "drivers/hitechnic-magfield.h"
#include "drivers/hitechnic-irseeker-v2.h"
#include "drivers/lego-touch.h"
#include "drivers/lego-light.h"
#include "drivers/lego-ultrasound.h"

const tMUXSensor HTIRS2 = msensor_S2_1;
const tMUXSensor LEGOLS = msensor_S2_2;
const tMUXSensor LEGOUS = msensor_S2_3;
const tMUXSensor LEGOUS2 = msensor_S2_4;
const tMUXSensor HTGYRO = msensor_S3_1;

#define mainScreen 1
#define driveForwardManual 2
#define driveSideManual 3
#define ringLiftManual 4
#define grabersManual 5
#define grabersAdjust 6
#define lightSensorMotor 7
#define LFmotor 8
#define RFmotor 9
#define LRmotor 10
#define RRmotor 11
#define shoulderManual 12
#define wristManual 13
#define sensorsView 14
#define extraServo 15

#define grippersDown 0
#define grippersMed 1
#define grippersUp 2

int sonar;
int sonar2;
int IR_value;
int gyro;
int light_value;
int extraServoValue;

int grabberPositions = 0;

int testNumber = 1;
int displayScreen;

bool rightButton = false;
bool leftButton = false;

bool testRunning = false;

//==================================
// selector
//==================================
task selector()
{
	while(true)
	{
		testRunning = false;
		eraseDisplay();
		displayScreen = mainScreen;
		while(nNxtButtonPressed != kEnterButton)
		{
			if(nNxtButtonPressed == kLeftButton)
			{
				PlaySound(soundShortBlip);
				testNumber--;
				eraseDisplay();
				displayScreen = mainScreen;
				while(nNxtButtonPressed == kLeftButton){}
				eraseDisplay();
			}
			if(nNxtButtonPressed == kRightButton)
			{
				PlaySound(soundShortBlip);
				testNumber++;
				eraseDisplay();
				displayScreen = mainScreen;
				while(nNxtButtonPressed == kRightButton){}
				eraseDisplay();
			}
			if(testNumber < 1)testNumber = 13;
			if(testNumber > 13)testNumber = 1;
		}
		PlaySound(soundException);
		while(nNxtButtonPressed == kEnterButton){}
		testRunning = true;
		while(nNxtButtonPressed != kEnterButton)
		{
			if(testNumber != 5)
			{
				if(nNxtButtonPressed == kRightButton)
				{
					rightButton = true;
					PlaySound(soundShortBlip);
					while(nNxtButtonPressed == kRightButton){}
				}
				else rightButton = false;
				if(nNxtButtonPressed == kLeftButton)
				{
					leftButton = true;
					PlaySound(soundShortBlip);
					while(nNxtButtonPressed == kLeftButton){}
				}
				else leftButton = false;
			}
			else
			{

			}
		}
		while(nNxtButtonPressed == kEnterButton){}
		PlaySound(soundException);
	}
}
//==================================
// display
//==================================
task display()
{
	disableDiagnosticsDisplay();
	while(true)
	{
		switch(displayScreen)
		{
		case mainScreen:
			switch(testNumber)
			{
			case 1:
				nxtDisplayBigTextLine(1, "Drive");
				nxtDisplayBigTextLine(3, "Forward");
				break;
			case 2:
				nxtDisplayBigTextLine(1, "Drive");
				nxtDisplayBigTextLine(3, "Side");
				break;
			case 3:
				nxtDisplayBigTextLine(1, "Lift");
				break;
			case 4:
				nxtDisplayBigTextLine(1, "Grabbers");
				nxtDisplayBigTextLine(3, "Manual");
				break;
			case 5:
				nxtDisplayBigTextLine(1, "Grabbers");
				nxtDisplayBigTextLine(3, "Adjust");
				break;
			case 6:
				nxtDisplayBigTextLine(0, "Light");
				nxtDisplayBigTextLine(2, "Sensor");
				nxtDisplayBigTextLine(4, "Motor");
				break;
			case 7:
				nxtDisplayBigTextLine(0, "Left");
				nxtDisplayBigTextLine(2, "Front");
				nxtDisplayBigTextLine(4, "Motor");
				break;
			case 8:
				nxtDisplayBigTextLine(0, "Right");
				nxtDisplayBigTextLine(2, "Front");
				nxtDisplayBigTextLine(4, "Motor");
				break;
			case 9:
				nxtDisplayBigTextLine(0, "Left");
				nxtDisplayBigTextLine(2, "Rear");
				nxtDisplayBigTextLine(4, "Motor");
				break;
			case 10:
				nxtDisplayBigTextLine(0, "Right");
				nxtDisplayBigTextLine(2, "Rear");
				nxtDisplayBigTextLine(4, "Motor");
				break;
			case 11:
				nxtDisplayBigTextLine(0, "Arm/");
				nxtDisplayBigTextLine(2, "Shoulder");
				break;
			case 12:
				nxtDisplayBigTextLine(0, "Arm/");
				nxtDisplayBigTextLine(2, "wrist");
				break;
			case 13:
				nxtDisplayBigTextLine(1, "Sensors");
				break;
			case 14:
				nxtDisplayBigTextLine(0, "Extra");
				nxtDisplayBigTextLine(1, "servo");
				break;
			}
			break;
		case driveForwardManual:
			if(rightButton) nxtDisplayBigTextLine(6, "Forward");
			else if(leftButton) nxtDisplayBigTextLine(6, "Backward");
			else nxtDisplayBigTextLine(6, "Brake");
			break;
		case driveSideManual:
			if(rightButton) nxtDisplayBigTextLine(6, "Right");
			else if(leftButton) nxtDisplayBigTextLine(6, "Left");
			else nxtDisplayBigTextLine(6, "Brake");
			break;
		case ringLiftManual:
			nxtDisplayBigTextLine(6, "%4d", nMotorEncoder[lifterMotor]);
			break;
		case grabersManual:
			switch(grabberPositions)
			{
			case grippersUp:
				nxtDisplayBigTextLine(6, "Up");
				break;
			case grippersMed:
				nxtDisplayBigTextLine(6, "Medium");
				break;
			case grippersDown:
				nxtDisplayBigTextLine(6, "Down");
				break;
			}
			break;
		case grabersAdjust:
			break;
		case lightSensorMotor:
			if(rightButton) nxtDisplayBigTextLine(6, "Down");
			else if (leftButton) nxtDisplayBigTextLine(6, "Up");
			break;
		case LFmotor:
			if(rightButton) nxtDisplayBigTextLine(6, "Forward");
			else if (leftButton) nxtDisplayBigTextLine(6, "Backward");
			else nxtDisplayBigTextLine(6, "Brake");
			break;
		case RFmotor:
			if(rightButton) nxtDisplayBigTextLine(6, "Forward");
			else if (leftButton) nxtDisplayBigTextLine(6, "Backward");
			else nxtDisplayBigTextLine(6, "Brake");
			break;
		case LRmotor:
			if(rightButton) nxtDisplayBigTextLine(6, "Forward");
			else if (leftButton) nxtDisplayBigTextLine(6, "Backward");
			else nxtDisplayBigTextLine(6, "Brake");
			break;
		case RRmotor:
			if(rightButton) nxtDisplayBigTextLine(6, "Forward");
			else if (leftButton) nxtDisplayBigTextLine(6, "Backward");
			else nxtDisplayBigTextLine(6, "Brake");
			break;
		case shoulderManual:
			if(leftButton) nxtDisplayBigTextLine(6, "0");
			else if (rightButton) nxtDisplayBigTextLine(6, "255");
			break;
		case wristManual:
			if(leftButton) nxtDisplayBigTextLine(6, "130");
			else if (rightButton) nxtDisplayBigTextLine(6, "2451");
			break;
		case sensorsView:
			nxtDisplayBigTextLine(3, "%3d, %3d",sonar,sonar2);
			if(touchSensor) nxtDisplayBigTextLine(5, "true, %3d",light_value);
			else nxtDisplayBigTextLine(5, "false,%3d",light_value);
			break;
			case extraServo:
			nxtDisplayBigTextLine(5, "%3d", extraServoValue);
			break;
		}
	}
}
//==================================
// sensors
//==================================
task sensors()
{
	while(true)
	{
		sonar = LEGOUS;
		sonar2 = LEGOUS2;
		IR_value = HTIRS2;
		gyro = HTGYRO;
		light_value = LEGOLS;
	}
}

//==================================
// main program
//==================================
task main()
{
	StartTask(display);
	StartTask(selector);
	StartTask(sensors);

	servoChangeRate[shoulder] = 4;

	while(true)
	{
		if(testRunning)
		{
			switch(testNumber)
			{
				//----------------------------------
				// Drive Forward
				//----------------------------------
			case 1:
				displayScreen = driveForwardManual;
				if(rightButton)
				{
					motor[LF] = -60;
					motor[RF] = 60;
					motor[LR] = -60;
					motor[RR] = 60;
				}
				else if(leftButton)
				{
					motor[LF] = 60;
					motor[RF] = -60;
					motor[LR] = 60;
					motor[RR] = -60;
				}
				else
				{
					motor[LF] = 0;
					motor[RF] = 0;
					motor[LR] = 0;
					motor[RR] = 0;
				}
				break;
				//----------------------------------
				// Drive Sideways
				//----------------------------------
			case 2:
				displayScreen = driveSideManual;
				if(rightButton)
				{
					motor[LF] = -60;
					motor[RF] = -60;
					motor[LR] = 60;
					motor[RR] = 60;
				}
				else if(leftButton)
				{
					motor[LF] = 60;
					motor[RF] = 60;
					motor[LR] = -60;
					motor[RR] = -60;
				}
				else
				{
					motor[LF] = 0;
					motor[RF] = 0;
					motor[LR] = 0;
					motor[RR] = 0;
				}
				break;
				//----------------------------------
				// Lift
				//----------------------------------
			case 3:
				displayScreen = ringLiftManual;
				if(rightButton) motor[lifterMotor] = 80;
				else if(leftButton) motor[lifterMotor] = -80;
				else motor[lifterMotor] = 0;
				break;
				//----------------------------------
				// Grabbers Manual
				//----------------------------------
			case 4:
				displayScreen = grabersManual;
				if (rightButton)
				{
					grabberPositions++;
					while(rightButton){}
				}
				else if(leftButton)
				{
					grabberPositions--;
					while(leftButton){}
				}
				if (grabberPositions > 2) grabberPositions = 2;
				if (grabberPositions < 0) grabberPositions = 0;
				switch(grabberPositions)
				{
				case grippersUp:
					servo[right_servo] = 180;
					servo[left_servo] = 0;
					break;
				case grippersMed:
					servo[right_servo] = 90;
					servo[left_servo] = 90;
					break;
				case grippersDown:
					servo[right_servo] = 0;
					servo[left_servo] = 180;
					break;
				}
				break;
				//----------------------------------
				// Grabbers Adjust
				//----------------------------------
			case 5:
				displayScreen = grabersAdjust;
				break;
				//----------------------------------
				// Light Sensor Motor
				//----------------------------------
			case 6:
				displayScreen = lightSensorMotor;
				if(rightButton) motor[lightMotor] = -60;
				else if(leftButton) motor[lightMotor] = 60;
				break;
				//----------------------------------
				// Left Front Motor
				//----------------------------------
			case 7:
				displayScreen = LFmotor;
				if(rightButton) motor[LF] = -80;
				else if(leftButton) motor[LF] = 80;
				else motor[LF] = 0;
				break;
				//----------------------------------
				// Right Front Motor
				//----------------------------------
			case 8:
				displayScreen = LRmotor;
				if(rightButton) motor[RF] = -80;
				else if(leftButton) motor[RF] = 80;
				else motor[RF] = 0;
				break;
				//----------------------------------
				// Left Rear Motor
				//----------------------------------
			case 9:
				displayScreen = LRmotor;
				if(rightButton) motor[LR] = 80;
				else if(leftButton) motor[LR] = -80;
				else motor[LR] = 0;
				break;
				//----------------------------------
				// Right Rear Motor
				//----------------------------------
			case 10:
				displayScreen = RRmotor;
				if(rightButton) motor[RR] = 80;
				else if(leftButton) motor[RR] = -80;
				else motor[RR] = 0;
				break;
				//----------------------------------
				// Auto arm shoulder test
				//----------------------------------
			case 11:
				displayScreen = shoulderManual;
				if(leftButton) servo[shoulder] = 0;
				else if(rightButton)servo[shoulder] = 255;
				break;
				//---------------------------------
				// Auto arm wrist test
				//----------------------------------
			case 12:
				displayScreen = wristManual;
				if(leftButton) servo[wrist] = 130;
				else if(rightButton)servo[wrist] = 245;
				break;
				//----------------------------------
				// Sensors
				//----------------------------------
			case 13:
				displayScreen = sensorsView;
				break;
				//----------------------------------
				// Extra servo test
				//----------------------------------
			case 14:
				displayScreen = extraServo;
				if(leftButton) extraServoValue = extraServoValue+5;
				else if (rightButton) extraServoValue = extraServoValue-5;
				if(extraServoValue > 180) extraServoValue = 180;
				else if(extraServoValue < 0) extraServoValue = 0;
				servo[extra_servo] = extraServoValue;
				break;
			}
		}
	}
}