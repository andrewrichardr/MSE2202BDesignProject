#include <Servo.h>
int LED[4] = {7, 6, 5, 4};
int numLeds = 4;
unsigned char intervalRx = 100;
unsigned char intervalTx = 100;
Servo servo1;
unsigned long milliseconds;
  
void setup() {
  for(int i =0;i<numLeds;i++){
    pinMode(LED[i], OUTPUT);
  }
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  pinMode(3, INPUT);

  pinMode(1, OUTPUT);
  pinMode(0, INPUT);

  Serial.begin(4800);

  servo1.attach(9);
}

void loop() {

  unsigned long currMillis = millis();
  unsigned long prevMillis =0;
  unsigned long potPos = analogRead(0);

   if(digitalRead(3)){
    while(!digitalRead(2) && intervalTx < 1000){
      milliseconds = 1;
      while(!digitalRead(2)){
      milliseconds++;
    }
    }
    intervalTx = milliseconds/(unsigned char)10;
  }
  else {
    unsigned long pot = potPos/(unsigned long)1023;
      intervalTx = 255*pot;
  }

  Serial.write(intervalTx);

  intervalRx = Serial.read();
  
  for(int a = 0; a < numLeds; a++){
    digitalWrite(LED[a], HIGH);
    if(a==0) servo1.write(0);
    if(a==1) servo1.write(60);
    if(a==2) servo1.write(120);
    if(a==3) servo1.write(180);

    prevMillis = currMillis;
    while(currMillis - prevMillis <= intervalRx){
      currMillis = millis();
    }
    
    if(a+1<=numLeds) digitalWrite(LED[a+1], HIGH);
    
    prevMillis = currMillis;
    while(currMillis - prevMillis <= intervalRx){
      currMillis = millis();
    }
    
    digitalWrite(LED[a], LOW);
  }
  
  for(int a = numLeds-1; a >= 0; a--){
    digitalWrite(LED[a], HIGH);
    
    if(a==0) servo1.write(0);
    if(a==1) servo1.write(60);
    if(a==2) servo1.write(120);
    if(a==3) servo1.write(180);
    
    prevMillis = currMillis;
    while(currMillis - prevMillis <= intervalRx){
      currMillis = millis();
    }
    
    if(a-1>=0) digitalWrite(LED[a-1], HIGH);
    prevMillis = currMillis;
    while(currMillis - prevMillis <= intervalRx){
      currMillis = millis();
    }

    digitalWrite(LED[a], LOW);
  }
}


