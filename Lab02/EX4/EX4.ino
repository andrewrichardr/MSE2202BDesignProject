unsigned long meas;
unsigned long potPos;
int a=0;
int b=0;
bool fwd=1;
unsigned int currMillis;
unsigned int prevMillis;
unsigned int interval = 100;
int LED[4] = {7, 6, 5, 4};
int numLeds = 4;

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
}

void loop()
{
  Serial.println("Int:");
  Serial.println(interval);
  if(digitalRead(3)){
    while(!digitalRead(2) && interval < 1000){
      meas = 1;
      while(!digitalRead(2)){
        Serial.println(meas++);
      }
    }
    interval = meas/(unsigned long)10;
  }
  else {
    potPos = analogRead(0);
    interval = 100*potPos/(unsigned long)1023;
  }

  currMillis = millis();
  if(currMillis - prevMillis >= interval)
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
}
