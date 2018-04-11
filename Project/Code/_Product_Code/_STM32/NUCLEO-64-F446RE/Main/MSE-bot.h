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
#define LEFT_MOTOR                        D10
#define RIGHT_MOTOR                       D9

#define LR_ULTRASONIC_IN                  A1
#define LR_ULTRASONIC_OUT                 A0
#define LF_ULTRASONIC_IN                  A3
#define LF_ULTRASONIC_OUT                 A2
#define F_ULTRASONIC_IN                   A5
#define F_ULTRASONIC_OUT                  A4

#define CUBE_INTAKE_ARM                   D12
#define CUBE_INTAKE_CLAW                  D8

#define PYR_INTAKE_LIFT                   D13
#define PYR_INTAKE_WHEELS                 D3

//#define TARGET_PYR_SW                     PB15
#define START_SW                          PC13
#define PYR_INTAKE_SW            PG0
#define LIFT_LIMIT_SW0                    PB2   //upper switch for retracted position
#define LIFT_LIMIT_SW1                    PB1   //lower switch for extended position

//Program Parameters
#define WALL_TARGET_DIST                  13 * 58 // 11 cm * 58 = 638
#define WALL_TARGET_TOLERANCE             30 // 1cm
#define PARALLEL_TOLERANCE                60 // 1.5cm
#define TURN_THRESHOLD                    600
#define SWERVE_DELAY                      2000
#define PING_MS                           10

#define FORWARD_SPEED_FAST                1800
#define REVERSE_SPEED_FAST                1200
#define FORWARD_SPEED_SLOW                1650
#define REVERSE_SPEED_SLOW                1350
#define STOP_VALUE                        1500

#define CUBE_MAG_GEN_THRESH               2000
#define CUBE_MAG_ACCURATE_THRESH          4500
#define IR_TIME_TOLERANCE                 2000
#define CUBE_INTAKE_OPEN                  65
#define CUBE_INTAKE_CLOSE                 105


class MSEBot {
  public:
    bool _speedMode = 1;

    unsigned int _LR_ultrasonic_dist;
    unsigned int _LF_ultrasonic_dist;
    unsigned int _F_ultrasonic_dist;
    unsigned int _LRecho;
    unsigned int _LFecho;
    unsigned int _Fecho;
    unsigned int _LastIRTime = 0;

    char _IRValues[4] = {'A', 'E', 'I', 'O'};
    bool _IRsw = 1; // 1 for AE, 0 for IO
    bool _ArmPosition = 0;
    bool _LiftPosition = 1;
    bool _TurnCount = 0; // counter for turn direction for finding pyramid

    int _compassHeading;
    int _compassMagnitude;

    sensors_event_t compassData;

    Servo _leftMotor;
    Servo _rightMotor;
    Servo _armMotor;
    Servo _clawMotor;
    Servo _liftMotor;
    Servo _intakeMotor;

    Adafruit_LSM303 AccelMag;

  public:
    void init();

    void findWall();
    void PingUltra();
    void PingFront();
    void TurnOnAxisL();
    void TurnOnAxisR();
    void goForward();
    void goReverse();
    void moveIn();
    void moveOut();
    void StopDrive();
    bool scanIRFocused();
    bool scanIRWide();
    bool hasPyramid();
    void readCompass();
    short checkForCube();
    void checkForPyramid();
    void parallelFollow();
    void scanField();
    void intakeOn();
    void placePyramid();
    void setSpeed(bool speed);
    void closeClaw();
    void openClaw();
    void moveArmIn();
    void moveArmOut();
    void moveLift(bool position);



};

