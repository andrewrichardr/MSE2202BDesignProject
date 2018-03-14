#include <Servo.h>
Servo leftMotor;
Servo rightMotor;

#define LEFT_MOTOR PA9
#define RIGHT_MOTOR PA7

void setup() {
  // put your setup code here, to run once:
  pinMode(LEFT_MOTOR, OUTPUT);
  pinMode(RIGHT_MOTOR, OUTPUT);
  leftMotor.attach(LEFT_MOTOR);
  rightMotor.attach(RIGHT_MOTOR);

}

void loop() {
  // put your main code here, to run repeatedly:
  leftMotor.writeMicroseconds(1800);
  rightMotor.writeMicroseconds(1800);
}
