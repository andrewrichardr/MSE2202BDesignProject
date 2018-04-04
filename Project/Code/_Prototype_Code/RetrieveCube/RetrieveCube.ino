#include <Wire.h>
#include <math.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>

Adafruit_LSM303 lsm;

void setup() 
{
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif
  Serial.begin(9600);
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
    while (1);
  }
}

void loop() 
{
  int x, y, z;
  lsm.read();
  x = lsm.magData.x;
  y = lsm.magData.y;
  z = lsm.magData.z;

   int mag = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
      Serial.print("  Magnitude: "); Serial.println(mag);
}
