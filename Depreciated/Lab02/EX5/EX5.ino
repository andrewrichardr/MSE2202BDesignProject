#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>

#include <Servo.h>
#include <SPI.h>
unsigned long milliseconds=1;
unsigned long potPos;
int a=0;
int b=0;
bool fwd=1;
unsigned int currMillis;
unsigned int prevMillis;
unsigned int interval = 100;
int LED[4] = {7, 6, 5, 4};
int numLeds = 4;

Servo servo1;
Servo servo2;

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
  SPI.begin();
  servo1.attach(8);
  servo2.attach(9);
  servo2.writeMicroseconds(1600);
}

void loop()
{
  if(0){
    while(!digitalRead(2) && interval < 1000){
      if(!digitalRead(2)){
        Serial.println(milliseconds++);
      }
    }
    interval = milliseconds/(unsigned long)10;
  }
  else {
    potPos = analogRead(0);
    interval = 100*potPos/(unsigned long)1023;
  }

  currMillis = millis();
  if(currMillis - prevMillis >= interval)
  {
    prevMillis = currMillis;
    //incrementState();
  }

SPI.transfer(0x5b);
potPos = analogRead(0);
Serial.println(potPos);
servo1.write(180*potPos/(unsigned long)1023);

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
