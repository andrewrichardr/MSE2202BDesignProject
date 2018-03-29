//Main Class

//Compile Options and Reqs:
//  Board: Nucleo-64
//  Part Number: F446RE
//  Upload Method: STLink

#include <Wire.h>
#include <Stream.h>
#include <SPI.h>
#include <Servo.h>

#define STARTING_TASK         1;    // 1 = find the cube, 2 = find the pyramid, 3 = insert pyramid into cube

//pin assignments
#define LEFT_MOTOR          PA9
#define RIGHT_MOTOR         PC7

#define LR_ULTRASONIC_IN      PC1
#define LR_ULTRASONIC_OUT     PC0
#define LF_ULTRASONIC_IN      PA4
#define LF_ULTRASONIC_OUT     PB0
#define F_ULTRASONIC_IN       PA0
#define F_ULTRASONIC_OUT      PA1

#define CUBE_INTAKE_ARM       PA5
#define CUBE_INTAKE_CLAW       PA6

#define PYR_INTAKE_LIFT        PA7
#define PYR_INTAKE_WHEELS        PB6

#define HALL_EFFECT         PB1
#define REED_SW           PC4
#define IR_CONTROL          PB12
#define LF_LIMIT_SW         PB13
#define LR_LIMIT_SW         PB15
#define RF_LIMIT_SW         PB14
#define RR_LIMIT_SW         PB2

//Compass input on I2C1
#define MAG3110_I2C_ADDRESS         0x0E
#define MAG3110_OUT_X_MSB     0x01
#define MAG3110_CTRL_REG1     0x10
#define MAG3110_ACTIVE_MODE     0x01

//Encoder input on I2C3

//Program Parameters
#define WALL_TARGET_DIST      200
#define WALL_TARGET_TOLERANCE   100
#define PARALLEL_TOLERANCE      50
#define TURN_THRESHOLD        500

#define FORWARD_SPEED       1700
#define REVERSE_SPEED       1300
#define TURN_AXIS_F         1750
#define TURN_AXIS_R         1250

#define PYR_INTAKE_UP       180     //Arbitrary Number for now
#define PYR_INTAKE_DOWN       0       //Arbitrary Number for now

#define CUBE_INTAKE_OPEN      90     //Arbitrary Number for now
#define CUBE_INTAKE_CLOSE     0       //Arbitrary Number for now

#define HALL_EFFECT_THRESHOLD 50


class MSEBot
{
private:
  short _currentTask = STARTING_TASK; 
  bool _hasCube = 0;

  unsigned long _LR_ultrasonic_dist;
  unsigned long _LF_ultrasonic_dist;
  unsigned long _F_ultrasonic_dist;
  unsigned long _LRecho;
  unsigned long _LFecho;
  unsigned long _Fecho;
  unsigned long _HallValue;
  char _IRValue = 0;
  bool _IRsw = 1; // 1 for AE, 0 for IO

  int _cx, _cy, _cz;

  Servo _leftMotor;
    Servo _rightMotor;
    Servo _armMotor;
    Servo _clawMotor;
	Servo _liftMotor;
	Servo _intakeMotor;

  void PingUltra();
  void readUltra();
  void TurnOnAxis(int deg);
  void goForward();
  void moveIn();
  void moveOut();
  char scanIR();
  void initCompass();
  void readCompass(int* x, int* y, int* z);
  bool checkForCube();

  void parallelFollow();
  void placePyramid();
  
public:

  void init();
  void GO();

};
