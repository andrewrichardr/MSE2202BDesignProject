#define FFORWARD 1850
#define FREVERSE 1150
#define STOP 1500

unsigned long ul_Echo_Time;
#include <Servo.h>
Servo servo1;
Servo servo2;
void setup() {
  // put your setup code here, to run once:
  servo1.attach(8);
  servo2.attach(9);
  Serial.begin(9600);
  pinMode(D4, INPUT);
  pinMode(D13, OUTPUT);
  pinMode(PC1, INPUT);
  pinMode(PC0, OUTPUT);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  servo1.writeMicroseconds(FFORWARD);
  servo2.writeMicroseconds(FFORWARD);
  delay(1000);
  servo1.writeMicroseconds(STOP);
  servo2.writeMicroseconds(STOP);
    delay(300);
  servo1.writeMicroseconds(FFORWARD);
  servo2.writeMicroseconds(FREVERSE);
    delay(500);
  servo1.writeMicroseconds(STOP);
  servo2.writeMicroseconds(STOP);
    delay(300);
  servo1.writeMicroseconds(FREVERSE);
  servo2.writeMicroseconds(FREVERSE);
      delay(1000);
  servo1.writeMicroseconds(STOP);
  servo2.writeMicroseconds(STOP);
  delay(300);
    servo1.writeMicroseconds(FFORWARD);
  servo2.writeMicroseconds(FREVERSE);
    delay(500);
  servo1.writeMicroseconds(STOP);
  servo2.writeMicroseconds(STOP);
    delay(300);
  
  

}
void Ping()
{
  //Ping Ultrasonic
  //Send the Ultrasonic Range Finder a 10 microsecond pulse per tech spec
  digitalWrite(PC0, HIGH);
  delayMicroseconds(10);  //The 10 microsecond pause where the pulse in "high"
  digitalWrite(PC0, LOW);
  //use command pulseIn to listen to Ultrasonic_Data pin to record the
  //time that it takes from when the Pin goes HIGH until it goes LOW 
  ul_Echo_Time = pulseIn(PC1, HIGH, 10000);

  if(ul_Echo_Time != 0){
    Serial.println(ul_Echo_Time/58);
  }
}  
