#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>
#include <math.h>

Adafruit_LSM303 lsm;

void setup() 
{
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif
  Serial.begin(115200);
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
    while (1);
  }
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

  int x, y, z, mag;
  
void loop() 
{



  
  x = lsm.magData.x;
  y = lsm.magData.y;
  z = lsm.magData.z;

    mag = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
    
  lsm.read();
  Serial.print("  X: "); Serial.print(lsm.accelData.x);
  Serial.print("  Y: "); Serial.print(lsm.accelData.y);
  Serial.print("  Z: "); Serial.print(lsm.accelData.z);
  Serial.print("  Magnitude: "); Serial.print(mag);
  Serial.print("  Heading:  "); Serial.println(atan2(y, x)*180/3.14);

  if(mag > 1000){
    digitalWrite(6, HIGH);
  }
  else {
    digitalWrite(6, LOW);
  }
    if(mag > 1500){
    digitalWrite(7, HIGH);
  }
  else {
    digitalWrite(7, LOW);
  }
    if(mag > 2000){
    digitalWrite(8, HIGH);
  }
  else {
    digitalWrite(8, LOW);
  }
    if(mag > 2500){
    digitalWrite(9, HIGH);
  }
  else {
    digitalWrite(9, LOW);
  }
}
