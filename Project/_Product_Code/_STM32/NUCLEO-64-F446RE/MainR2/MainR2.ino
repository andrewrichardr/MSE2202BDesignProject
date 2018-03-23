#include "MSE-Bot.h"

MSEBot Robot;
int x, y, z;

void setup(){
  Robot.init();
}

void loop() {
  Robot.readCompass(&x, &y, &z);
  Serial.print(" x: ");
  Serial.print(x);
  Serial.print(" y: ");
  Serial.print(y);
  Serial.print(" z: ");
  Serial.println(z);
}
