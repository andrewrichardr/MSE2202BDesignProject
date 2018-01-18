#include <Servo.h>
int LED[4] = {7, 6, 5, 4};
int numLeds = 4;
unsigned long interval = 100;
Servo servo1;
  
void setup() {
  for(int i =0;i<numLeds;i++){
    pinMode(LED[i], OUTPUT);
  }
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  pinMode(3, INPUT);

  Serial.begin(9600);

  servo1.attach(9);
}

void loop() {

  unsigned long currMillis = millis();
  unsigned long prevMillis =0;
  unsigned long potPos = analogRead(0);

  if(digitalRead(3)){
    if(!digitalRead(2)) interval++;
  }
  else {
      interval = 100*potPos/(unsigned long)1023;
  }

  Serial.print("Interval: ");
  Serial.print(interval);
  Serial.print("\n");
  
  for(int a = 0; a < numLeds; a++){
    digitalWrite(LED[a], HIGH);
    if(a==0) servo1.write(0);
    if(a==1) servo1.write(60);
    if(a==2) servo1.write(120);
    if(a==3) servo1.write(180);

    prevMillis = currMillis;
    while(currMillis - prevMillis <= interval){
      currMillis = millis();
    }
    
    if(a+1<=numLeds) digitalWrite(LED[a+1], HIGH);
    
    prevMillis = currMillis;
    while(currMillis - prevMillis <= interval){
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
    while(currMillis - prevMillis <= interval){
      currMillis = millis();
    }
    
    if(a-1>=0) digitalWrite(LED[a-1], HIGH);
    prevMillis = currMillis;
    while(currMillis - prevMillis <= interval){
      currMillis = millis();
    }

    digitalWrite(LED[a], LOW);
  }
}


