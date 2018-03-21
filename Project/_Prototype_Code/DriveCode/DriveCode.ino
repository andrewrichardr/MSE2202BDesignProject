//#define DEBUG_ULTRASONIC

#include <Servo.h>
Servo leftMotor;
Servo rightMotor;

#include <Wire.h>

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

#define LIMIT_SW PA3

#define COMPASS_I2C_ADDR 0x1E

long FR_ultrasonic_dist;
long LF_ultrasonic_dist;
unsigned long FRecho;
unsigned long LFecho;

int x, y, z;

void lmswitch(){
  
  Wire.beginTransmission(COMPASS_I2C_ADDR);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
 
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(COMPASS_I2C_ADDR, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }
  
  //Print out values of each axis
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);
  Serial.print("  z: ");
  Serial.println(z);
  
}

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

  attachInterrupt(digitalPinToInterrupt(LIMIT_SW), lmswitch, FALLING);

  Wire.begin();
  Wire.beginTransmission(COMPASS_I2C_ADDR);
  Wire.write(0x02);
  Wire.write(0x00);
  Wire.endTransmission();

}

void loop() {
  // put your main code here, to run repeatedly:
  pingFR();
  pingLF();

  if(abs(LF_ultrasonic_dist - FR_ultrasonic_dist) <= 15){
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


