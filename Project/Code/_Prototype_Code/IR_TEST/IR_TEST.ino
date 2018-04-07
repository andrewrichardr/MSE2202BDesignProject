void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(2400);
  pinMode(13, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  char Rx = Serial1.read();
  Serial.println(Rx );

}
