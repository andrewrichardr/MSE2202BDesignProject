//#define DEBUG_ULTRASONIC

#include <Servo.h>
Servo leftMotor;
Servo rightMotor;

#include <Wire.h>

#define LEFT_MOTOR PA9
#define RIGHT_MOTOR PC7

#define LR_ULTRASONIC_IN PC1
#define LR_ULTRASONIC_OUT PC0
#define LF_ULTRASONIC_IN PA4
#define LF_ULTRASONIC_OUT PB0
#define F_ULTRASONIC_IN PA0
#define F_ULTRASONIC_OUT PA1

#define WALL_LOWER_THRESHOLD 5
#define WALL_UPPER_THRESHOLD 10

#define TURN_THRESHOLD 10

#define FORWARD_SPEED 1850
#define REVERSE_SPEED 1850

#define LIMIT_SW PA3

#define COMPASS_I2C_ADDR 0x1E

long LR_ultrasonic_dist;
long LF_ultrasonic_dist;
long F_ultrasonic_dist;
unsigned long LRecho;
unsigned long LFecho;
unsigned long Fecho;

int x, y, z;

bool turning = 0;

void lmswitch(){
  
  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

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

 // attachInterrupt(digitalPinToInterrupt(LIMIT_SW), lmswitch, FALLING);

  //Wire.begin();
  //Wire.beginTransmission(COMPASS_I2C_ADDR);
  //Wire.write(0x02);
 // Wire.write(0x00);
//  Wire.endTransmission();

}

void loop() {
  // put your main code here, to run repeatedly:
  pingLR();
  pingLF();
  pingF();

  if(abs(LF_ultrasonic_dist - LR_ultrasonic_dist) <= 50){
    goForward();
    Serial.print("Forward  ");
  }
  else if(LF_ultrasonic_dist > LR_ultrasonic_dist){
    moveIn();
    Serial.print("Move In  ");
  }
  else{
    moveOut();
    Serial.print("Move Out  ");
  }

  while(F_ultrasonic_dist < 1000){
    TurnOnAxis();
    Serial.println("Turning");
    pingF();
  }

  Serial.print(LF_ultrasonic_dist);
  Serial.print(" ");
  Serial.print(LR_ultrasonic_dist);
  Serial.print(" ");
  Serial.println(F_ultrasonic_dist);

}

void pingLR(){


  digitalWrite(LR_ULTRASONIC_IN, HIGH);
  delayMicroseconds(10);  //The 10 microsecond pause where the pulse in "high"
  digitalWrite(LR_ULTRASONIC_IN, LOW);

  LRecho = pulseIn(LR_ULTRASONIC_OUT, HIGH, 10000);
  if(LRecho) LR_ultrasonic_dist = LRecho;
}

void pingLF(){

  digitalWrite(LF_ULTRASONIC_IN, HIGH);
  delayMicroseconds(10);  //The 10 microsecond pause where the pulse in "high"
  digitalWrite(LF_ULTRASONIC_IN, LOW);

  LFecho = pulseIn(LF_ULTRASONIC_OUT, HIGH, 10000);
  if(LFecho) LF_ultrasonic_dist = LFecho;
}

void pingF(){

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


