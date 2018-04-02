//Main Class

//Compile Options and Reqs:
//  Board: Nucleo-64
//  Part Number: F446RE
//  Upload Method: STLink

#include <Wire.h>
#include <Stream.h>
#include <SPI.h>
#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <math.h>

//pin assignments
#define LEFT_MOTOR                        PA9
#define RIGHT_MOTOR                       PC7

#define LR_ULTRASONIC_IN                  PA8
#define LR_ULTRASONIC_OUT                 PC9
#define LF_ULTRASONIC_IN                  PB4
#define LF_ULTRASONIC_OUT                 PB10
#define F_ULTRASONIC_IN                   PB3
#define F_ULTRASONIC_OUT                  PB5

#define CUBE_INTAKE_ARM                   PA5
#define CUBE_INTAKE_CLAW                  PA6

#define PYR_INTAKE_LIFT                   PA7
#define PYR_INTAKE_WHEELS                 PB6

#define TARGET_PYR_SW                     PB15
#define START_SW                          PB13
#define RF_LIMIT_SW                       PB14
#define RR_LIMIT_SW                       PB2
#define ARM_LIMIT_SW0                       		//inner switch for retracted position
#define ARM_LIMIT_SW1                       		//outer switch for extended position
#define LIFT_LIMIT_SW0                       		//upper switch for retracted position
#define LIFT_LIMIT_SW1                       		//lower switch for extended position

//Program Parameters
#define WALL_TARGET_DIST                  500
#define WALL_TARGET_TOLERANCE             100
#define PARALLEL_TOLERANCE                100
#define TURN_THRESHOLD                    75

#define FORWARD_SPEED_FAST                1850
#define REVERSE_SPEED_FAST                1150
#define FORWARD_SPEED_SLOW                1650
#define REVERSE_SPEED_SLOW                1350
#define STOP_VALUE                        1500

#define CUBE_MAG_GEN_THRESH               1000    //Arbitrary Number for now, Value that the magnetomoter will send then the robot is in the general vicinity of the cube
#define CUBE_MAG_ACCURATE_THRESH          2500    //Arbitrary Number for now, Value that the magnetomoter will send then the cube is in the claw
#define CUBE_INTAKE_OPEN                  90      //Arbitrary Number for now
#define CUBE_INTAKE_CLOSE                 0       //Arbitrary Number for now


class MSEBot {
private:
    bool _hasCube = 0;
    bool _speedMode = 1;

    unsigned int _LR_ultrasonic_dist;
    unsigned int _LF_ultrasonic_dist;
    unsigned int _F_ultrasonic_dist;
    unsigned int _LRecho;
    unsigned int _LFecho;
    unsigned int _Fecho;

    char _IRValues[4] = {'A', 'E', 'I', 'O'};
    bool _IRsw = 1;
	bool _ArmPosition = 0;
	bool _LiftPosition = 1;

    int _compassHeading;
    int _compassMagnitude;

    sensors_event_t compassData;

    Servo _leftMotor;
    Servo _rightMotor;
    Servo _armMotor;
    Servo _clawMotor;
    Servo _liftMotor;
    Servo _intakeMotor;

    Adafruit_LSM303_Mag_Unified AccelMag;

public:
	void init();

    void PingUltra();
    //void readUltra();
    void TurnOnAxisL();
    void TurnOnAxisR();
    void goForward();
    void goReverse();
    void moveIn();
    void moveOut();
    void StopDrive();
    bool scanIRFocused();
    bool scanIRWide();
    void readCompass();
    short checkForCube();
    void parallelFollow();
    void placePyramid();
    void setSpeed(bool speed);
    void closeClaw();
    void openClaw();
	void moveArm(bool position);
	void moveLift(bool position);



};