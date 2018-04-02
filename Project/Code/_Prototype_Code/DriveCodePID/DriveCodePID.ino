//#define DEBUG_ULTRASONIC

#include <Servo.h>
Servo leftMotor;
Servo rightMotor;

#include <Wire.h>

#define LEFT_MOTOR PA9
#define RIGHT_MOTOR PC7

#define LR_ULTRASONIC_IN                  PA8
#define LR_ULTRASONIC_OUT                 PC9
#define LF_ULTRASONIC_IN                  PB4
#define LF_ULTRASONIC_OUT                 PB10
#define F_ULTRASONIC_IN                   PB3
#define F_ULTRASONIC_OUT                  PB5

#define WALL_LOWER_THRESHOLD 5
#define WALL_UPPER_THRESHOLD 10

#define TURN_THRESHOLD 10

#define FORWARD_SPEED 1850
#define REVERSE_SPEED 1850

#define LIMIT_SW PA3

#define FOLLOW_DIST 500

long LR_ultrasonic_dist;
long LF_ultrasonic_dist;
long F_ultrasonic_dist;
unsigned long LRecho;
unsigned long LFecho;
unsigned long Fecho;

int setpoint = FOLLOW_DIST;
int threshold =20;
float error = 0;
//PID parameters
float integral = 0;
float derivative = 0;
float last_error = 0;
float PID_value = 0;
//tuning these parameters is pain in the ass.
//probably could use some optimisation to reach best option but too much work
float Kp = 0.7;
float Ki = 0.005;
float Kd = 1.3;
//These correction speed are purely experimental
//Needs to manually checked to get the appropriate correction speed
int correctionSpeedH=1850;
int correctionSpeedL=1700;

int correctionSpeedR = 53;
int rightWheelSpeed;
int leftWheelSpeed;
int base_speedLeft=1800;
int base_speedRight =1800;

int x, y, z;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(LR_ULTRASONIC_IN, OUTPUT);
  pinMode(LF_ULTRASONIC_IN, OUTPUT);
  pinMode(F_ULTRASONIC_IN, OUTPUT);
  pinMode(LR_ULTRASONIC_OUT, INPUT);
  pinMode(LF_ULTRASONIC_OUT, INPUT);
  pinMode(F_ULTRASONIC_OUT, INPUT);


  pinMode(LEFT_MOTOR, OUTPUT);
  pinMode(RIGHT_MOTOR, OUTPUT);
  leftMotor.attach(LEFT_MOTOR);
  rightMotor.attach(RIGHT_MOTOR);

}

void loop() {
  ping();
  pid_calculation();
  follow();
}

void follow(){

  //sets the PID_value to be lowest to -45 and highest to 45
  if(PID_value< -correctionSpeedL){
    PID_value = correctionSpeedL;
    //Serial.println(PID_value);
    //delay(1000);
  }
  if(PID_value> correctionSpeedH){
    PID_value = correctionSpeedH;
    //Serial.println(PID_value);
    // delay(1000);
  }

  if(PID_value < 0)
  {
    //away from the wall
    rightWheelSpeed = base_speedRight - PID_value   ;
    leftWheelSpeed = base_speedLeft - PID_value;
  }
  else
  {
    //right turn
    rightWheelSpeed = base_speedRight - PID_value;
    leftWheelSpeed = base_speedLeft - PID_value;
  }

  leftMotor.writeMicroseconds(leftWheelSpeed);
  rightMotor.writeMicroseconds(rightWheelSpeed);


  //sharp right turn(90 degree turn) when theres a wall on the left and wall at the front as well

  if(F_ultrasonic_dist < FOLLOW_DIST)
  {
  	while(F_ultrasonic_dist < 2*FOLLOW_DIST){
  	    TurnOnAxis();
  	    ping();
  	}
  }
}


void pid_calculation()          // does the pid calculation, setpoint can be changed either for left or right sensor   
{
  //IrDistance could be left or right depending on the wall follwing algorithm..
  error= LF_ultrasonic_dist - setpoint;

  //calculating integral 
  if(abs(error) < threshold)
  {
    integral = integral + error;
  }
  else
  {
    integral=0;
  }
  //taking the change in difference in reading
  derivative = error - last_error;
  last_error = error;
  //calulating PID value which is also an error value
  PID_value = int(error*Kp + integral*Ki + derivative*Kd);
  //return PID_value;
 // Serial.println(PID_value);
  //delay(1000);
}


void ping(){


  digitalWrite(LR_ULTRASONIC_IN, HIGH);
  delayMicroseconds(10);  //The 10 microsecond pause where the pulse in "high"
  digitalWrite(LR_ULTRASONIC_IN, LOW);

  LRecho = pulseIn(LR_ULTRASONIC_OUT, HIGH, 10000);
  if(LRecho) LR_ultrasonic_dist = LRecho;

  digitalWrite(LF_ULTRASONIC_IN, HIGH);
  delayMicroseconds(10);  //The 10 microsecond pause where the pulse in "high"
  digitalWrite(LF_ULTRASONIC_IN, LOW);

  LFecho = pulseIn(LF_ULTRASONIC_OUT, HIGH, 10000);
  if(LFecho) LF_ultrasonic_dist = LFecho;

  digitalWrite(F_ULTRASONIC_IN, HIGH);
  delayMicroseconds(10);  //The 10 microsecond pause where the pulse in "high"
  digitalWrite(F_ULTRASONIC_IN, LOW);
  Fecho = pulseIn(F_ULTRASONIC_OUT, HIGH, 10000);
  if(Fecho) F_ultrasonic_dist = Fecho;


}

void TurnOnAxis(){
  leftMotor.writeMicroseconds(1150);
  rightMotor.writeMicroseconds(1850);
}

void goForward(){
//Serial.println("Forward");
  leftMotor.writeMicroseconds(FORWARD_SPEED);
  rightMotor.writeMicroseconds(FORWARD_SPEED);
}
void moveIn(){
 // Serial.println("Move In");
  leftMotor.writeMicroseconds(FORWARD_SPEED);
  rightMotor.writeMicroseconds(1500);
}
void moveOut(){
  //Serial.println("Move Out");
  leftMotor.writeMicroseconds(1500);
  rightMotor.writeMicroseconds(FORWARD_SPEED);
}


