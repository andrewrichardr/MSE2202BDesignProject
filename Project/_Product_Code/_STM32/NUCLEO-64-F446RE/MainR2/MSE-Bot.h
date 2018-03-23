//Main Class

//Compile Options and Reqs:
//  Board: Nucleo-64
//  Part Number: F446RE
//  Upload Method: STLink

#include <Wire.h>
#include <Stream.h>
#include <SPI.h>
#include <Servo.h>

#define STARTING_TASK 				1; 		// 1 = find the cube, 2 = find the pyramid, 3 = insert pyramid into cube

//pin assignments
#define LEFT_MOTOR					PA9
#define RIGHT_MOTOR					PC7

#define LR_ULTRASONIC_IN			PC1
#define LR_ULTRASONIC_OUT			PC0
#define LF_ULTRASONIC_IN			PA4
#define LF_ULTRASONIC_OUT			PB0
#define F_ULTRASONIC_IN				PA0
#define F_ULTRASONIC_OUT			PA1

#define CUBE_INTAKE_1				PA5
#define CUBE_INTAKE_2				PA6

#define PYR_INTAKE_1				PA7
#define PYR_INTAKE_2				PB6

#define HALL_EFFECT					PB1
#define REED_SW 					PC4
#define IR_CONTROL 					PB12
#define LF_LIMIT_SW 				PB13
#define LR_LIMIT_SW 				PB15
#define RF_LIMIT_SW 				PB14
#define RR_LIMIT_SW 				PB2

//Ultrasonic input on USART2
//IR on UART3
//Compass input on I2C1
#define MAG3110_I2C_ADDRESS         0x0E
#define MAG3110_OUT_X_MSB			0x01
#define MAG3110_CTRL_REG1			0x10
#define MAG3110_ACTIVE_MODE			0x01
//Encoder input on I2C3

//Program Parameters
#define WALL_TARGET_DIST			200
#define PARALLEL_TOLERANCE			50
#define TURN_THRESHOLD				500

#define FORWARD_SPEED				1700
#define REVERSE_SPEED				1300
#define TURN_AXIS_F					1600
#define TURN_AXIS_R					1400

#define PYR_INTAKE_UP				180 		//Arbitrary Number for now
#define PYR_INTAKE_DOWN				0 			//Arbitrary Number for now

#define CUBE_INTAKE_OPEN			180 		//Arbitrary Number for now
#define CUBE_INTAKE_CLOSE			0 			//Arbitrary Number for now

class MSEBot
{
private:
	short currentTask = STARTING_TASK; 
	bool hasCube = 0;

	unsigned long LR_ultrasonic_dist;
	unsigned long LF_ultrasonic_dist;
	unsigned long F_ultrasonic_dist;
	unsigned long LRecho;
	unsigned long LFecho;
	unsigned long Fecho;

	Servo leftMotor;
    Servo rightMotor;

	void init();
	void PingUltra();
	void readUltra();
	void TurnOnAxis();
	void goForward();
	void moveIn();
	void moveOut();
	int scanIR();
	void initCompass();
	void readCompass(int* x, int* y, int* z);

	void parallelFollow();
public:
	void GO();

};
