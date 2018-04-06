#include "MSE-Bot.h"

void MSEBot::init(){
  //Robot Initialization Function, Call this in setup() of the Arduino Sketch
  int initTime = millis();

  //Initialize Buses
  Serial.begin(9600);
  Serial7.begin(2400);    //UART7 for pyramid IR sensor
  Serial8.begin(2400);    //UART8 for front IR sensor
  Wire.begin();           //I2C1 for Compass and Accel
  Wire.setClock(400000);

  //Initialize GPIO Pins
  //pinMode(13, OUTPUT);
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
  pinMode(PYR_INTAKE_SW, INPUT);
  digitalWrite(PYR_INTAKE_SW, HIGH);
  pinMode(LIFT_LIMIT_SW0, INPUT);
  pinMode(LIFT_LIMIT_SW1, INPUT);
  pinMode(START_SW, INPUT);

  //Initialize Actuators
  _leftMotor.attach(LEFT_MOTOR);
  _rightMotor.attach(RIGHT_MOTOR);
  _armMotor.attach(CUBE_INTAKE_ARM);
  _clawMotor.attach(CUBE_INTAKE_CLAW);
  _liftMotor.attach(PYR_INTAKE_LIFT);
  _intakeMotor.attach(PYR_INTAKE_WHEELS);
  _clawMotor.write(CUBE_INTAKE_OPEN); // open position

  //Initialize Sensors
  AccelMag.begin();

  _liftMotor.writeMicroseconds(1600);
  Serial.print("Initialized in "); Serial.print(initTime-millis()); Serial.println("ms! Starting operation on request!");
  
  //Wait for start button to be pressed
  while(!digitalRead(START_SW)) {}

  Serial.println("Starting...");
  
  //Initialize Intake Positions
  //moveLift(0); // up position


  
  /*
  digitalWrite(13, HIGH);
  digitalWrite(START_SW, HIGH);
  */


}

void MSEBot::PingUltra(){ // Ping ultrasonic sensors and record values in member variables
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

void MSEBot::PingFront(){
    digitalWrite(F_ULTRASONIC_IN, HIGH);
  delayMicroseconds(PING_MS); 
  digitalWrite(F_ULTRASONIC_IN, LOW);
  _Fecho = pulseIn(F_ULTRASONIC_OUT, HIGH, 10000);
  if(_Fecho) _F_ultrasonic_dist = _Fecho;
}

void MSEBot::TurnOnAxisL(){ // Set speeds for turning left
  if(_speedMode){
    _leftMotor.writeMicroseconds(FORWARD_SPEED_FAST);
    _rightMotor.writeMicroseconds(REVERSE_SPEED_FAST);
  }
  else{
    _leftMotor.writeMicroseconds(FORWARD_SPEED_SLOW);
    _rightMotor.writeMicroseconds(REVERSE_SPEED_SLOW);
  }
}

void MSEBot::TurnOnAxisR(){ // Set speeds for turning right
  if(_speedMode){
    _leftMotor.writeMicroseconds(REVERSE_SPEED_FAST);
    _rightMotor.writeMicroseconds(FORWARD_SPEED_FAST);
  }
  else{
    _leftMotor.writeMicroseconds(REVERSE_SPEED_SLOW);
    _rightMotor.writeMicroseconds(FORWARD_SPEED_SLOW);
  }
}

void MSEBot::StopDrive(){ // Set speeds to stop
  _leftMotor.writeMicroseconds(STOP_VALUE);
  _rightMotor.writeMicroseconds(STOP_VALUE);
}

void MSEBot::goForward(){ // Set speeds to go forward
  if(_speedMode){
    _leftMotor.writeMicroseconds(FORWARD_SPEED_FAST);
    _rightMotor.writeMicroseconds(FORWARD_SPEED_FAST);
  }
  else{
    _leftMotor.writeMicroseconds(FORWARD_SPEED_SLOW);
    _rightMotor.writeMicroseconds(FORWARD_SPEED_SLOW);
  }
  //Serial.println("Forward");
}

void MSEBot::goReverse(){ // Set values to go in reverse
  if(_speedMode){
    _leftMotor.writeMicroseconds(REVERSE_SPEED_FAST);
    _rightMotor.writeMicroseconds(REVERSE_SPEED_FAST);
  }
  else{
    _leftMotor.writeMicroseconds(REVERSE_SPEED_SLOW);
    _rightMotor.writeMicroseconds(REVERSE_SPEED_SLOW);
  }
    //Serial.println("Reverse");
}

void MSEBot::moveIn(){ // Move in towards right side
  if(_speedMode){
    _leftMotor.writeMicroseconds(STOP_VALUE);
    _rightMotor.writeMicroseconds(FORWARD_SPEED_FAST);
  }
  else{
    _leftMotor.writeMicroseconds(STOP_VALUE);
    _rightMotor.writeMicroseconds(FORWARD_SPEED_SLOW);
  }
    //Serial.println("in");
}

void MSEBot::moveOut(){ // Move out away from right side
  if(_speedMode){
    _leftMotor.writeMicroseconds(FORWARD_SPEED_FAST);
    _rightMotor.writeMicroseconds(STOP_VALUE);
  }
  else{
    _leftMotor.writeMicroseconds(FORWARD_SPEED_SLOW);
    _rightMotor.writeMicroseconds(STOP_VALUE);
  }
    //Serial.println("out");
}

void MSEBot::moveArmOut() {
  Serial.println("Moving Arm");
  _armMotor.writeMicroseconds(1100);
  delay(5000);
  _armMotor.writeMicroseconds(STOP_VALUE);
} 

void MSEBot::moveArmIn() {
  Serial.println("Moving Arm");
  _armMotor.writeMicroseconds(1800);
  delay(5000);
  _armMotor.writeMicroseconds(STOP_VALUE);
} 

void MSEBot::moveLift(bool position) {
  if(position) { // if we want lift down
    if(!_LiftPosition) { // if lift up
      //while(!digitalRead(LIFT_LIMIT_SW1)) {
        _liftMotor.writeMicroseconds(REVERSE_SPEED_SLOW); // move down until hits outer switch
        delay(2000);
      _liftMotor.writeMicroseconds(STOP_VALUE);
      _LiftPosition = 1;
    }
  }
  else { // if we want lift retracted or up
    if(_LiftPosition) {
      //while(!digitalRead(LIFT_LIMIT_SW0)) {
        _liftMotor.writeMicroseconds(FORWARD_SPEED_SLOW); // move up until hits inner switch
      delay(2000);
      _liftMotor.writeMicroseconds(STOP_VALUE);
      _LiftPosition = 0;
    }
  }
}

bool MSEBot::scanIRFocused(){ // Scan using rear shrouded IR
  char value = Serial7.read();
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
  _LastIRTime = millis();
    return 1;
  } 
  else{
    return 0;
  }
}

bool MSEBot::scanIRWide(){ // Scan using front unshrouded IR
  char value = Serial8.read();
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
  _LastIRTime = millis();
    return 1;
  } 
  else{
    return 0;
  }
}

bool MSEBot::hasPyramid(){ // Read if we have pyramid using limit switch
  return digitalRead(PYR_INTAKE_SW);
}

void MSEBot::readCompass(){ // Obtain magnetometer readings
  AccelMag.read();
  _compassMagnitude = sqrt(pow(AccelMag.magData.x, 2)+pow(AccelMag.magData.x, 2)+pow(AccelMag.magData.x, 2));
  //_compassHeading = atan2(AccelMag.magnetic.x, AccelMag.magnetic.y)*180/3.14159;
}

short MSEBot::checkForCube(){ // Compare magnetometer readings to see how close cube is
  readCompass();
  if(_compassMagnitude > CUBE_MAG_ACCURATE_THRESH) return 1;  //return 1 if the mag field exceeds the threshold of the cube being held in the claw
  if(_compassMagnitude > CUBE_MAG_GEN_THRESH) return 2;       //return 2 if the mag field exceeds the threshold of the cube being in the vicinity of the claw
  else return 0;                                              //return 0 if the cube is not near by
}

void MSEBot::checkForPyramid(){ // Checks previous instance of IR reading to see if robot is still pointing towards pyr
  while(_LastIRTime - millis() > IR_TIME_TOLERANCE) {
    scanIRFocused();
    TurnOnAxisL();
  }
}

void MSEBot::findWall(){
  PingUltra();
  goForward();
  while(_F_ultrasonic_dist > TURN_THRESHOLD) {
    PingUltra();
  }
  StopDrive();
  
}

void MSEBot::parallelFollow(){ // Follow walls at a set distace, parallel to wall, turn as necessary
  PingUltra();
  
  if(_F_ultrasonic_dist < TURN_THRESHOLD) {
    StopDrive();
    /*
    while(_LR_ultrasonic_dist > WALL_TARGET_DIST){ //Turn until Front Ultrasonic is measureing a large distance
    TurnOnAxisL();
    PingUltra();
    }
    */
    TurnOnAxisL();
    delay(100);
  }
  
  unsigned int parallel = abs(_LF_ultrasonic_dist - _LR_ultrasonic_dist);
 /* unsigned int distance = abs(_LF_ultrasonic_dist - WALL_TARGET_DIST);
  
  if(parallel < PARALLEL_TOLERANCE && distance < WALL_TARGET_TOLERANCE){ //Everything is fine and dandy
    goForward();
  }
  else if(_LF_ultrasonic_dist > PARALLEL_TOLERANCE + _LR_ultrasonic_dist){ //Distance is ok, Robot is not parallel
    moveIn();
  }
  else if(_LF_ultrasonic_dist + PARALLEL_TOLERANCE < _LR_ultrasonic_dist){ //Distance is ok, Robot is not parallel
    moveOut();
  }
*/
    if(parallel < PARALLEL_TOLERANCE){
    goForward();
  }
  else if(_LF_ultrasonic_dist > _LR_ultrasonic_dist){
    moveIn();
  }
  else{
    moveOut();
  }
}

void MSEBot::scanField() { // Swerve and scan field for pyramid as robot drives across it back andforth
TurnOnAxisL();
delay(300);
goForward();
delay(300);


/*
       if(scanIRWide()) {
          StopDrive();
          return;
        }
        PingUltra();
  if(_F_ultrasonic_dist < 3 * TURN_THRESHOLD) { // turn at walls
    if(_TurnCount) {
      TurnOnAxisR();
      unsigned long triggerTime= millis(); // turn 160 degrees
      while(millis() - triggerTime < 3000) {
        if(scanIRWide()) {
          StopDrive();
          return;
        }
        if(scanIRWide()) {
          StopDrive();
          return;
        }
        if(scanIRWide()) {
          StopDrive();
          return;
        }
      }
      _TurnCount = 0;
    }
    else {
      TurnOnAxisL();
      unsigned long triggerTime= millis(); // turn 160 degrees
      while(millis() - triggerTime < 3000) {
        if(scanIRWide()) {
         StopDrive();
          return;
        }
        if(scanIRWide()) {
          StopDrive();
          return;
        }
        if(scanIRWide()) {
          StopDrive();
          return;
        }
      }
      _TurnCount = 0;
    }
  }

  if(scanIRWide()) {
          StopDrive();
          return;
        }
  
  if((int)(millis() / SWERVE_DELAY) % 2) { // alternate between swerving left and right in real time
    _leftMotor.writeMicroseconds(FORWARD_SPEED_FAST);
    _rightMotor.writeMicroseconds(FORWARD_SPEED_FAST);
  }
  else {
    _leftMotor.writeMicroseconds(FORWARD_SPEED_FAST);
    _rightMotor.writeMicroseconds(FORWARD_SPEED_FAST);
  }

  if(scanIRWide()) {
          StopDrive();
          return;
        }
        */
} 

void MSEBot::intakeOn() { // get intake in position for retrieving pyramid
  _intakeMotor.writeMicroseconds(REVERSE_SPEED_FAST);
  moveLift(1);
}

void MSEBot::placePyramid() { // routine for putting cube in pyramid
  _intakeMotor.writeMicroseconds(STOP_VALUE);
  delay(1000);
  moveLift(0);
  openClaw(); // drop cube into funnel
  delay(1000);
  goReverse(); // back up a bit
  delay(2000); // test this value so cube under pyr
  StopDrive();
  delay(1000);
  moveLift(1);
  delay(1000);
  goReverse();
  _intakeMotor.writeMicroseconds(FORWARD_SPEED_FAST); // push pyramid back out with cube underneath
  delay(2000);
  StopDrive();  
} 

void MSEBot::setSpeed(bool speed){
  if(speed){ //speed == 1: FAST
    _speedMode = 1;
  }
  else{ //speed == 0: SLOW
    _speedMode = 0;
  }
}

void MSEBot::closeClaw(){ // close claw
  _clawMotor.write(CUBE_INTAKE_CLOSE);
}

void MSEBot::openClaw(){ // OPEN CLAW
  _clawMotor.write(CUBE_INTAKE_OPEN);
}
