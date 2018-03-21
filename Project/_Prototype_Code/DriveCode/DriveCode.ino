//#define DEBUG_ULTRASONIC

#include <Servo.h>
Servo leftMotor;
Servo rightMotor;

#define LEFT_MOTOR PA9
#define RIGHT_MOTOR PC7

#define FR_ULTRASONIC_IN PC1
#define FR_ULTRASONIC_OUT PC0
#define LF_ULTRASONIC_IN PA4
#define LF_ULTRASONIC_OUT PB0

#define WALL_LOWER_THRESHOLD 5
#define WALL_UPPER_THRESHOLD 10

#define TURN_THRESHOLD 10

#define FORWARD_SPEED 1850
#define REVERSE_SPEED 1850

long FR_ultrasonic_dist;
long LF_ultrasonic_dist;
unsigned long FRecho;
unsigned long LFecho;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(FR_ULTRASONIC_IN, OUTPUT);
  pinMode(LF_ULTRASONIC_IN, OUTPUT);
  pinMode(FR_ULTRASONIC_OUT, INPUT);
  pinMode(LF_ULTRASONIC_OUT, INPUT);

  pinMode(LEFT_MOTOR, OUTPUT);
  pinMode(RIGHT_MOTOR, OUTPUT);
  leftMotor.attach(LEFT_MOTOR);
  rightMotor.attach(RIGHT_MOTOR);

}

void loop() {
  // put your main code here, to run repeatedly:
  pingFR();
  pingLF();

  if(abs(LF_ultrasonic_dist - FR_ultrasonic_dist) <= 10){
    goForward();
    Serial.print("Forward  ");
  }
  else if(LF_ultrasonic_dist < FR_ultrasonic_dist){
    moveIn();
    Serial.print("Move In  ");
  }
  else{
    moveOut();
    Serial.print("Move Out  ");
  }



  Serial.print("LF: ");
  Serial.print(LF_ultrasonic_dist);
  Serial.print("  FR: ");
  Serial.println(FR_ultrasonic_dist);

}

void pingFR(){

  //Ping Ultrasonic
  //Send the Ultrasonic Range Finder a 10 microsecond pulse per tech spec
  digitalWrite(FR_ULTRASONIC_IN, HIGH);
  delayMicroseconds(10);  //The 10 microsecond pause where the pulse in "high"
  digitalWrite(FR_ULTRASONIC_IN, LOW);
  //use command pulseIn to listen to Ultrasonic_Data pin to record the
  //time that it takes from when the Pin goes HIGH until it goes LOW 
  FRecho = pulseIn(FR_ULTRASONIC_OUT, HIGH, 10000);
  if(FRecho) FR_ultrasonic_dist = FRecho;
}

void pingLF(){

  //Ping Ultrasonic
  //Send the Ultrasonic Range Finder a 10 microsecond pulse per tech spec
  digitalWrite(LF_ULTRASONIC_IN, HIGH);
  delayMicroseconds(10);  //The 10 microsecond pause where the pulse in "high"
  digitalWrite(LF_ULTRASONIC_IN, LOW);
  //use command pulseIn to listen to Ultrasonic_Data pin to record the
  //time that it takes from when the Pin goes HIGH until it goes LOW 
  LFecho = pulseIn(LF_ULTRASONIC_OUT, HIGH, 10000);
  if(LFecho) LF_ultrasonic_dist = LFecho;
}

void TurnOnAxis(int deg){
  leftMotor.writeMicroseconds(1250);
  rightMotor.writeMicroseconds(1750);
  delay(500); 
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


