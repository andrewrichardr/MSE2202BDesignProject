//This program pings the ultrasonic sensors, then outputs the data on the USART bus

//Pin Assignments, MSE-Duino-2
#define F_ULTRASONIC_IN  2
#define F_ULTRASONIC_OUT 3
#define R_ULTRASONIC_IN  4
#define R_ULTRASONIC_OUT 5
#define L_ULTRASONIC_IN  6
#define L_ULTRASONIC_OUT 7

unsigned long F_ultrasonic_dist;
unsigned long R_ultrasonic_dist;
unsigned long L_ultrasonic_dist;
unsigned long Fecho;
unsigned long Recho;
unsigned long Lecho;

void setup() {
  Serial.begin(9600);
  
  pinMode(F_ULTRASONIC_IN, OUTPUT);
  pinMode(F_ULTRASONIC_OUT, INPUT);
  pinMode(R_ULTRASONIC_IN, OUTPUT);
  pinMode(R_ULTRASONIC_OUT, INPUT);
  pinMode(L_ULTRASONIC_IN, OUTPUT);
  pinMode(L_ULTRASONIC_OUT, INPUT);
}

void loop() {
  pingFront();
  pingLeft();
  pingRight();

  Serial.print("L");
  Serial.print(L_ultrasonic_dist);
  Serial.print("R");
  Serial.print(R_ultrasonic_dist);
  Serial.print("F");
  Serial.println(F_ultrasonic_dist);
}

void pingFront(){
  digitalWrite(F_ULTRASONIC_IN, HIGH);
  delayMicroseconds(10);
  digitalWrite(F_ULTRASONIC_IN, LOW);
  FRecho = pulseIn(F_ULTRASONIC_OUT, HIGH, 10000);
  if(Fecho) F_ultrasonic_dist = Fecho/58;
}

void pingRight(){
  digitalWrite(R_ULTRASONIC_IN, HIGH);
  delayMicroseconds(10);
  digitalWrite(R_ULTRASONIC_IN, LOW);
  RIecho = pulseIn(R_ULTRASONIC_OUT, HIGH, 10000);
  if(Recho) R_ultrasonic_dist = Recho/58;
}

void pingLeft(){
  digitalWrite(L_ULTRASONIC_IN, HIGH);
  delayMicroseconds(10);
  digitalWrite(L_ULTRASONIC_IN, LOW);
  RIecho = pulseIn(L_ULTRASONIC_OUT, HIGH, 10000);
  if(Lecho) L_ultrasonic_dist = Lecho/58;
}
