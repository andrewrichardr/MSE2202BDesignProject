#include <Servo.h>
int LED[4] = {7, 6, 5, 4};
int numLeds = 4;
unsigned long interval = 100;
Servo servo1;

uint8_t uartRx;
  
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


void servoState(int a){
  if(a==0) servo1.write(0);
  if(a==1) servo1.write(60);
  if(a==2) servo1.write(120);
  if(a==3) servo1.write(180);
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
  
  for(int a = 0; a < numLeds; a++){
    Serial.write(LED[a]);

    prevMillis = currMillis;
    while(currMillis - prevMillis <= interval){
      currMillis = millis();
    }
    
    if(a+1<=numLeds) Serial.write(LED[a+1]);
    
    prevMillis = currMillis;
    while(currMillis - prevMillis <= interval){
      currMillis = millis();
    }
    
    Serial.write(255-LED[a]);
  }
  
  for(int a = numLeds-1; a >= 0; a--){
    Serial.write(LED[a]);

    prevMillis = currMillis;
    while(currMillis - prevMillis <= interval){
      currMillis = millis();
    }
    
    if(a-1>=0) Serial.write(LED[a-1]);
    prevMillis = currMillis;
    while(currMillis - prevMillis <= interval){
      currMillis = millis();
    }

    Serial.write(255-LED[a]);
  }


  Serial.readBytes(uartRx, 1);
  
  if(uartRx < numLeds) {
    digitalWrite(LED[uartRx], HIGH);
    servoState(uartRx);
  }
  if(uartRx > numLeds) {
    digitalWrite(LED[255-uartRx], LOW);
    servoState(255-uartRx);
  }
}


