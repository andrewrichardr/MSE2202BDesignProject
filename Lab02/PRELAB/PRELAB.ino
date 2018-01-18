int LED[4] = {7, 6, 5, 4};
int numLeds = 4;
int interval = 100;
  
void setup() {
  int sizel = 4;//sizeof(LED)/sizeof(LED[0]);
  for(int i =0;i<sizel;i++){
    pinMode(LED[i], OUTPUT);
  }
}

void loop() {
    for(int a = 0; a < numLeds; a++){
      digitalWrite(LED[a], HIGH);
      delay(interval);
    }
    for(int a = 0; a < numLeds; a++){
      digitalWrite(LED[a], LOW);
      delay(interval);
    }
    for(int a = numLeds-1; a >= 0; a--){
      digitalWrite(LED[a], HIGH);
      delay(interval);
    }
    for(int a = numLeds-1; a >= 0; a--){
    digitalWrite(LED[a], LOW);
      delay(interval);
    }
}
