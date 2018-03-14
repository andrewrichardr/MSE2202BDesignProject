#include <Servo.h>

Servo leftDrive;
Servo rightDrive;
Servo pyramidLeft;
Servo pyramidRight;
Servo pyramidLift;
int frontUltPing = PC0, frontUltData = PC1, rightUltPing = PB0, rightUltData = PA4;



void setup() {
  // put your setup code here, to run once:
  leftDrive.attach(PA9);
  rightDrive.attach(PA7);
  pyramidLeft.attach();
  pyramidRight.attach();
  pyramidLift.attach();

  pinMode(frontUltPing, OUTPUT);
  pinMode(frontUltData, INPUT);
  pinMode(rightUltPing, OUTPUT);
  pinMode(rightUltData, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void turnLeft(int deg) {
  
  
}

void turnRight(int deg) {
  
}



