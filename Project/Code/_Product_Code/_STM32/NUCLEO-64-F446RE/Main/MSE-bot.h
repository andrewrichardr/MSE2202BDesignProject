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

#define STARTING_TASK                     1;      // 1 = find the cube, 2 = find the pyramid, 3 = insert pyramid into cube

//pin assignments
#define LEFT_MOTOR                        PA9
#define RIGHT_MOTOR                       PC7

#define LR_ULTRASONIC_IN                  PC1
#define LR_ULTRASONIC_OUT                 PC0
#define LF_ULTRASONIC_IN                  PA4
#define LF_ULTRASONIC_OUT                 PB0
#define F_ULTRASONIC_IN                   PA0
#define F_ULTRASONIC_OUT                  PA1

#define CUBE_INTAKE_ARM                   PA5
#define CUBE_INTAKE_CLAW                  PA6

#define PYR_INTAKE_LIFT                   PA7
#define PYR_INTAKE_WHEELS                 PB6

#define TARGET_PYR_SW                     PB13
#define START_SW                          PB15
#define RF_LIMIT_SW                       PB14
#define RR_LIMIT_SW                       PB2

//Program Parameters
#define WALL_TARGET_DIST                  200
#define WALL_TARGET_TOLERANCE             100
#define PARALLEL_TOLERANCE                50
#define TURN_THRESHOLD                    500

#define FORWARD_SPEED_FAST                1850
#define REVERSE_SPEED_FAST                1150
#define FORWARD_SPEED_SLOW                1650
#define REVERSE_SPEED_SLOW                1350
#define STOP_VALUE                        1500

#define PYR_INTAKE_UP                     180     //Arbitrary Number for now
#define PYR_INTAKE_DOWN                   0       //Arbitrary Number for now

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



};
