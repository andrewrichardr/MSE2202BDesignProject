//Main Class

//Compile Options and Reqs:
//  Board: Nucleo-32
//  Part Number: L432KC
//  Upload Method: STLink

//Andrew Randell

#define UART_BAUD_RATE        115200

#define LR_ULTRASONIC_IN      D12
#define LR_ULTRASONIC_OUT     D11
#define LF_ULTRASONIC_IN      D10
#define LF_ULTRASONIC_OUT     D9
#define F_ULTRASONIC_IN       D8
#define F_ULTRASONIC_OUT      D7

void setup() {
  pinMode(LR_ULTRASONIC_IN, OUTPUT);
  pinMode(LF_ULTRASONIC_IN, OUTPUT);
  pinMode(F_ULTRASONIC_IN, OUTPUT);
  pinMode(LR_ULTRASONIC_OUT, INPUT);
  pinMode(LF_ULTRASONIC_OUT, INPUT);
  pinMode(F_ULTRASONIC_OUT, INPUT);

  Serial.begin(UART_BAUD_RATE);
}

void loop() {

  unsigned long _LR_ultrasonic_dist;
  unsigned long _LF_ultrasonic_dist;
  unsigned long _F_ultrasonic_dist;
  unsigned long _LRecho;
  unsigned long _LFecho;
  unsigned long _Fecho;

  while(true)
  {
    digitalWrite(F_ULTRASONIC_IN, HIGH);
    delayMicroseconds(10); 
    digitalWrite(F_ULTRASONIC_IN, LOW);
    _Fecho = pulseIn(F_ULTRASONIC_OUT, HIGH, 10000);
    if(_Fecho) _F_ultrasonic_dist = _Fecho;

    digitalWrite(LF_ULTRASONIC_IN, HIGH);
    delayMicroseconds(10);  
    digitalWrite(LF_ULTRASONIC_IN, LOW);
    _LFecho = pulseIn(LF_ULTRASONIC_OUT, HIGH, 10000);
    if(_LFecho) _LF_ultrasonic_dist = _LFecho;

    digitalWrite(LR_ULTRASONIC_IN, HIGH);
    delayMicroseconds(10);  
    digitalWrite(LR_ULTRASONIC_IN, LOW);
    _LRecho = pulseIn(LR_ULTRASONIC_OUT, HIGH, 10000);
    if(_LRecho) _LR_ultrasonic_dist = _LRecho;

    Serial.write(_F_ultrasonic_dist);
    Serial.write(",");
    Serial.write(_LF_ultrasonic_dist);
    Serial.write(",");
    Serial.write(_LR_ultrasonic_dist);
    Serial.write(",,");
  }
}
