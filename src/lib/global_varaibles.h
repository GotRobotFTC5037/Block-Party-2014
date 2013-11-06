#pragma systemFile								// treat as system file to eliminate warnings for unused variables
//
//============================================================
// Define sensor multiplexor connectivity and port allocations
//============================================================
const tMUXSensor HTIRS2 = msensor_S3_1;     // HiTechnic Infrared sensor
const tMUXSensor HTGYRO = msensor_S2_1;			// HiTechnic GYRO sensor

bool gyroTrue = false;

//=========================================================
// Robot constants
//=========================================================

#define ANGLE_SENSOR_CIRCUMFERENCE 17.6
#define DRIVE_WHEELS_CIRCUMFERENCE 26

//=========================================================
// Smoke test varaibles
//=========================================================

int smoke_test_num = 1;
int smoke_test_total = 12;
int smoke_run = false;

//=========================================================
// Misc
//=========================================================

int auto_missions = 4;
int drive_heading = 0;

bool Joy1Enabled = false;
bool Joy2Enabled = false;

//=============================================================
// Define user configurable parameters
//=============================================================
int mission_number = 1;
int start_delay = 0;
int gyroCalTime = 5;

//=============================================================
// Gyro variables
//=============================================================
int gyro_noise = 0;
long starttime = 0;
int drift = 0;
float constHeading = 0;
float relHeading = 0;
long currtime = 0;
long prevtime = 0;
int rawgyro = 0;

//=============================================================
// Sensor variables
//=============================================================
int bearingAC = 0;
float IR_Bearing = 0.0;
int acS[5];
float currDir = 0.0;

//==============================================================
// Define screen related variables
//==============================================================
#define s_clear 0
#define s_mission 1
#define s_start_delay 2
#define s_cal_time 3
#define s_gyro_cal 4
#define s_ready 5
#define s_delay_wait 6
#define s_gyro_show 7
#define s_error 8
#define s_smoke_test 9
#define s_smoke_run 10

int screen_state = 1;

//==============================================================
// Define error numbers
//==============================================================
#define e_none 0
#define e_gyro_cal 1
#define e_gyro_mux 2
#define e_sensor_mux 3
#define e_joysticks 4

int error = 0;

//==============================================================================
// Define the text to be displayed for each mission
//==============================================================================
string MissionNames1 [] = {
	"        ",
	"Test 1  ",
	"Test 2  ",
	"Test 3  ",
	"Test 4  ",
	"Test 5  ",
	"Test 6  ",
	"Test 7  ",
	"Test 8  ",
	"Test 9  ",
	"Test 10 ",
	"Test 11 ",
	"Test 12 ",
	"Test 13 ",
	"Test 14 ",
	"Test 15 ",
	"Test 16 ",
	"Test 17 ",
	"Test 18 ",
	"Test 19 ",
	"Test 20 ",
	"Test 21 ",
	"Test 22 "};

//==============================================================================
// Define the text to be displayed for the errors
//==============================================================================
string error_list1 [] = {
	"Unknown ",
	"GyroCal ",
	"Gyro    ",
	"Sensor  ",
	"joystick",
	"Test 5  ",
	"Test 6  ",
	"Test 7  ",
	"Test 8  ",
	"Test 9  ",
	"Test 10 ",
	"Test 11 ",
	"Test 12 ",
	"Test 13 ",
	"Test 14 ",
	"Test 15 ",
	"Test 16 ",
	"Test 17 ",
	"Test 18 ",
	"Test 19 ",
	"Test 20 ",
	"Test 21 ",
	"Test 22 "};

	string error_list2 [] = {
	"error   ",
	"Failure ",
	"Mux     ",
	"Mux     ",
	"fail    ",
	"Test 5  ",
	"Test 6  ",
	"Test 7  ",
	"Test 8  ",
	"Test 9  ",
	"Test 10 ",
	"Test 11 ",
	"Test 12 ",
	"Test 13 ",
	"Test 14 ",
	"Test 15 ",
	"Test 16 ",
	"Test 17 ",
	"Test 18 ",
	"Test 19 ",
	"Test 20 ",
	"Test 21 ",
	"Test 22 "};

//==============================================================================
// Define the text to be displayed for smoke test line 1
//==============================================================================
string smoke_test1 [] = {
	"Unknown ",
	"GyroCal ",
	"Gyro    ",
	"Sensor  ",
	"Test 4  ",
	"Test 5  ",
	"Test 6  ",
	"Test 7  ",
	"Test 8  ",
	"Test 9  ",
	"Test 10 ",
	"Test 11 ",
	"Test 12 ",
	"Test 13 ",
	"Test 14 ",
	"Test 15 ",
	"Test 16 ",
	"Test 17 ",
	"Test 18 ",
	"Test 19 ",
	"Test 20 ",
	"Test 21 ",
	"Test 22 "};

	//==============================================================================
// Define the text to be displayed for smoke test line 2
//==============================================================================
string smoke_test2 [] = {
	"Unknown ",
	"GyroCal ",
	"Gyro    ",
	"Sensor  ",
	"Test 4  ",
	"Test 5  ",
	"Test 6  ",
	"Test 7  ",
	"Test 8  ",
	"Test 9  ",
	"Test 10 ",
	"Test 11 ",
	"Test 12 ",
	"Test 13 ",
	"Test 14 ",
	"Test 15 ",
	"Test 16 ",
	"Test 17 ",
	"Test 18 ",
	"Test 19 ",
	"Test 20 ",
	"Test 21 ",
	"Test 22 "};
