int LED[4] = {7, 6, 5, 4};
int numLeds = 4;
int interval = 100;
  
void setup() {
  for(int i =0;i<numLeds;i++){
    pinMode(LED[i], OUTPUT);
  }
}

void loop() {
  for(int a = 0; a < numLeds; a++){
    digitalWrite(LED[a], HIGH);
    delay(interval);
    if(a+1<=numLeds) digitalWrite(LED[a+1], HIGH);
    delay(interval);
    digitalWrite(LED[a], LOW);
  }
  for(int a = numLeds-1; a >= 0; a--){
    digitalWrite(LED[a], HIGH);
    delay(interval);
    if(a-1>=0) digitalWrite(LED[a-1], HIGH);
    delay(interval);
    digitalWrite(LED[a], LOW);
  }
}
