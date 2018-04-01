#include "MSE-Bot.h"

void MSEBot::init(){
  //Robot Initialization Function, Call this in setup() of the Arduino Sketch
  int initTime = millis();

  //Initialize Buses
  Serial.begin(115200);
  //Serial1.begin(115200);  //UART1 for external Ultrasonic Controller
  Serial3.begin(2400);    //UART3 for IR sensor
  Serial4.begin(2400);    //UART4 for IR sensor
  Wire.begin();           //I2C1 for Compass and Accel
  Wire.setClock(400000);

  //Initialize GPIO Pins
  pinMode(13, OUTPUT);
  pinMode(LR_ULTRASONIC_IN, OUTPUT);
  pinMode(LF_ULTRASONIC_IN, OUTPUT);
  pinMode(F_ULTRASONIC_IN, OUTPUT);
  pinMode(LR_ULTRASONIC_OUT, INPUT);
  pinMode(LF_ULTRASONIC_OUT, INPUT);
  pinMode(F_ULTRASONIC_OUT, INPUT);
  pinMode(LEFT_MOTOR, OUTPUT);
  pinMode(RIGHT_MOTOR, OUTPUT);
  pinMode(CUBE_INTAKE_ARM, OUTPUT);
  pinMode(CUBE_INTAKE_CLAW, OUTPUT);
  pinMode(PYR_INTAKE_LIFT, OUTPUT);
  pinMode(PYR_INTAKE_WHEELS, OUTPUT);
  pinMode(START_SW, INPUT);

  //Initialize Actuators
  _leftMotor.attach(LEFT_MOTOR);
  _rightMotor.attach(RIGHT_MOTOR);
  _armMotor.attach(CUBE_INTAKE_ARM);
  _clawMotor.attach(CUBE_INTAKE_CLAW);
  _liftMotor.attach(PYR_INTAKE_LIFT);
  _intakeMotor.attach(PYR_INTAKE_WHEELS);
  _armMotor.write(100); // slightly above horizontal
  _clawMotor.write(CUBE_INTAKE_OPEN); // open position
  _liftMotor.write(PYR_INTAKE_UP); // up position

  //Initialize Sensors
  AccelMag = Adafruit_LSM303_Mag_Unified(12345);
  AccelMag.enableAutoRange(true);

  Serial.println("Initialized in "); Serial.print(initTime-millis()); Serial.println("ms! Starting operation on request!");
/*
  digitalWrite(13, HIGH);
  digitalWrite(START_SW, HIGH);
  while(1) {
    if(digitalRead(START_SW)) break;   //Initializes then waits for the signal to start going, possibly do this over WiFi in a future version
  }
  */
}
#define PING_MS 10
void MSEBot::PingUltra(){
  digitalWrite(F_ULTRASONIC_IN, HIGH);
  delayMicroseconds(PING_MS); 
  digitalWrite(F_ULTRASONIC_IN, LOW);
  _Fecho = pulseIn(F_ULTRASONIC_OUT, HIGH, 10000);
  if(_Fecho) _F_ultrasonic_dist = _Fecho;

  digitalWrite(LF_ULTRASONIC_IN, HIGH);
  delayMicroseconds(PING_MS);  
  digitalWrite(LF_ULTRASONIC_IN, LOW);
  _LFecho = pulseIn(LF_ULTRASONIC_OUT, HIGH, 10000);
  if(_LFecho) _LF_ultrasonic_dist = _LFecho;

  digitalWrite(LR_ULTRASONIC_IN, HIGH);
  delayMicroseconds(PING_MS);  
  digitalWrite(LR_ULTRASONIC_IN, LOW);
  _LRecho = pulseIn(LR_ULTRASONIC_OUT, HIGH, 10000);
  if(_LRecho) _LR_ultrasonic_dist = _LRecho;

  //Serial.print(" F: "); Serial.print(_F_ultrasonic_dist); Serial.print(" LF: "); Serial.print(_LF_ultrasonic_dist); Serial.print(" LR: "); Serial.println(_LR_ultrasonic_dist);
}

void MSEBot::TurnOnAxisL(){
  if(_speedMode){
    _leftMotor.writeMicroseconds(FORWARD_SPEED_FAST);
    _rightMotor.writeMicroseconds(REVERSE_SPEED_FAST);
  }
  else{
    _leftMotor.writeMicroseconds(FORWARD_SPEED_SLOW);
    _rightMotor.writeMicroseconds(REVERSE_SPEED_SLOW);
  }
}

void MSEBot::TurnOnAxisR(){
  if(_speedMode){
    _leftMotor.writeMicroseconds(REVERSE_SPEED_FAST);
    _rightMotor.writeMicroseconds(FORWARD_SPEED_FAST);
  }
  else{
    _leftMotor.writeMicroseconds(REVERSE_SPEED_SLOW);
    _rightMotor.writeMicroseconds(FORWARD_SPEED_SLOW);
  }
}

void MSEBot::StopDrive(){
  _leftMotor.writeMicroseconds(STOP_VALUE);
  _rightMotor.writeMicroseconds(STOP_VALUE);
}

void MSEBot::goForward(){
  if(_speedMode){
    _leftMotor.writeMicroseconds(FORWARD_SPEED_FAST);
    _rightMotor.writeMicroseconds(FORWARD_SPEED_FAST);
  }
  else{
    _leftMotor.writeMicroseconds(FORWARD_SPEED_SLOW);
    _rightMotor.writeMicroseconds(FORWARD_SPEED_SLOW);
  }
  Serial.println("Forward");
}

void MSEBot::goReverse(){
  if(_speedMode){
    _leftMotor.writeMicroseconds(REVERSE_SPEED_FAST);
    _rightMotor.writeMicroseconds(REVERSE_SPEED_FAST);
  }
  else{
    _leftMotor.writeMicroseconds(REVERSE_SPEED_SLOW);
    _rightMotor.writeMicroseconds(REVERSE_SPEED_SLOW);
  }
    Serial.println("Reverse");
}

void MSEBot::moveIn(){
  if(_speedMode){
    _leftMotor.writeMicroseconds(STOP_VALUE);
    _rightMotor.writeMicroseconds(FORWARD_SPEED_FAST);
  }
  else{
    _leftMotor.writeMicroseconds(STOP_VALUE);
    _rightMotor.writeMicroseconds(FORWARD_SPEED_SLOW);
  }
    Serial.println("in");
}

void MSEBot::moveOut(){
  if(_speedMode){
    _leftMotor.writeMicroseconds(FORWARD_SPEED_FAST);
    _rightMotor.writeMicroseconds(STOP_VALUE);
  }
  else{
    _leftMotor.writeMicroseconds(FORWARD_SPEED_SLOW);
    _rightMotor.writeMicroseconds(STOP_VALUE);
  }
    Serial.println("out");
}

bool MSEBot::scanIRFocused(){
  char value = Serial3.read();
  int idx1, idx2;
  if(_IRsw){
    idx1 = 0;
    idx2 = 1;
  }
  else{
    idx1 = 2;
    idx2 = 3;
  }
  if(value == _IRValues[idx1] || value == _IRValues[idx2]){
    return 1;
  } 
  else{
    return 0;
  }
}

bool MSEBot::scanIRWide(){
  char value = Serial4.read();
  int idx1, idx2;
  if(_IRsw){
    idx1 = 0;
    idx2 = 1;
  }
  else{
    idx1 = 2;
    idx2 = 3;
  }
  if(value == _IRValues[idx1] || value == _IRValues[idx2]){
    return 1;
  } 
  else{
    return 0;
  }
}

void MSEBot::readCompass(){
  AccelMag.getEvent(&compassData);
  _compassMagnitude = sqrt(pow(AccelMag.raw.x, 2)+pow(AccelMag.raw.y, 2)+pow(AccelMag.raw.z, 2));
  //_compassHeading = atan2(AccelMag.magnetic.x, AccelMag.magnetic.y)*180/3.14159;

  Serial.print(" MAG: "); Serial.println(_compassMagnitude);
}

short MSEBot::checkForCube(){
  readCompass();
  if(_compassMagnitude > CUBE_MAG_ACCURATE_THRESH) return 1;  //return 1 if the mag field exceeds the threshold of the cube being held in the claw
  if(_compassMagnitude > CUBE_MAG_GEN_THRESH) return 2;       //return 2 if the mag field exceeds the threshold of the cube being in the vicinity of the claw
  else return 0;                                              //return 0 if the cube is not near by
}

void MSEBot::parallelFollow(){
  PingUltra();
  unsigned int parallel = abs(_LF_ultrasonic_dist - _LR_ultrasonic_dist);
  unsigned int distance = abs(_LF_ultrasonic_dist - WALL_TARGET_DIST);

  if(parallel < PARALLEL_TOLERANCE && distance < WALL_TARGET_TOLERANCE){ //Everything is fine and dandy
    goForward();
  }
  else if(_LF_ultrasonic_dist > _LR_ultrasonic_dist && distance < WALL_TARGET_TOLERANCE){ //Distance is ok, Robot is not parallel
    moveIn();
  }
  else if(_LF_ultrasonic_dist < _LR_ultrasonic_dist && distance < WALL_TARGET_TOLERANCE){ //Distance is ok, Robot is not parallel
    moveOut();
  }
  else if(_LF_ultrasonic_dist < WALL_TARGET_DIST ){ //Distance is too close
    moveOut();
  }
  else{ //Distance is too far
    moveIn();
  }
    
  while(_F_ultrasonic_dist < 2*TURN_THRESHOLD){ //Turn until Front Ultrasonic is measureing a large distance
    TurnOnAxisL();
    PingUltra();
  }
}

void MSEBot::placePyramid() {/*
	_liftMotor.write(PYR_INTAKE_UP);
	_armMotor.write(0); // some value close to ground
	_clawMotor.write(CUBE_INTAKE_OPEN);
	delay(100);
	_leftMotor.writeMicroseconds(FORWARD_SPEED);
	_rightMotor.writeMicroseconds(FORWARD_SPEED);
	delay(300); // test this value
	TurnOnAxisL(); // test this value
	delay(100);
	_liftMotor.write(PYR_INTAKE_DOWN);
	_intakeMotor.writeMicroseconds(1250); // push pyramid back out
  */
}	

void MSEBot::setSpeed(bool speed){
  if(speed){ //speed == 1: FAST
    _speedMode = 1;
  }
  else{ //speed == 0: SLOW
    _speedMode = 0;
  }
}

void MSEBot::closeClaw(){
  _clawMotor.write(CUBE_INTAKE_CLOSE);
}

void MSEBot::openClaw(){
  _clawMotor.write(CUBE_INTAKE_OPEN);
}
