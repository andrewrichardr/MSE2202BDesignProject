#include <Servo.h>
unsigned long milliseconds;
unsigned long potPos;
int a=0;
int b=0;
bool fwd=1;
unsigned int currMillis;
unsigned int prevMillis;
unsigned char intervalTx;
unsigned char intervalRx;
int LED[4] = {7, 6, 5, 4};
int numLeds = 4;
Servo servo1;

void setup()
{
  for(int i=0;i<numLeds;i++)
  { 
    pinMode(LED[i], OUTPUT);
  }
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  digitalWrite(2, HIGH);  
  Serial.begin(9600);
  servo1.attach(9);
}

void loop()
{
  if(digitalRead(3)){
    while(!digitalRead(2) && intervalTx < 1000){
      milliseconds = 1;
      while(!digitalRead(2)){
        Serial.println(milliseconds++);
      }
    }
    intervalTx = milliseconds/(unsigned long)10;
  }
  else {
    potPos = analogRead(0);
    intervalTx = 100*potPos/(unsigned long)1023;
  }

  Serial.write(intervalTx);

  if(Serial.available()) intervalRx = Serial.read();

  currMillis = millis();
  if(currMillis - prevMillis >= intervalRx)
  {
    prevMillis = currMillis;
    incrementState();
  }
}

void incrementState()
{
  if(a==0) fwd = 1;
  if(a==numLeds-1) fwd = 0;
  while(fwd){
    if(b==0){
      digitalWrite(LED[a], HIGH);
        b++;
        break;
    }
    if(a+1<=numLeds && b == 1){
        digitalWrite(LED[a+1], HIGH);
        b++;
        break;  
    } 
    if(b==2){
      digitalWrite(LED[a], LOW);
      a++;
      b=0;
      break;
    }
  }
  while(!fwd){
    if(b==0){
      digitalWrite(LED[a], HIGH);
        b++;
        break;
    }
    if(a-1>=0 && b == 1){
        digitalWrite(LED[a-1], HIGH);
        b++;  
        break;
    } 
    if(b==2){
      digitalWrite(LED[a], LOW);
      a--;
      b=0;
      break;
    }
  }
  servoState(a);
}

void servoState(int s){
  if(s==0) servo1.write(0);
  if(s==1) servo1.write(60);
  if(s==2) servo1.write(120);
  if(s==3) servo1.write(180);
}
