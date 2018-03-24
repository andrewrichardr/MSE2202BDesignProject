#include "MSE-Bot.h"

void MSEBot::init(){
  Serial.begin(9600);
  Serial1.begin(115200);  //UART1 for external Ultrasonic Controller
  Serial3.begin(2400);    //UART3 for IR sensor

  pinMode(LR_ULTRASONIC_IN, OUTPUT);
  pinMode(LF_ULTRASONIC_IN, OUTPUT);
  pinMode(F_ULTRASONIC_IN, OUTPUT);
  pinMode(LR_ULTRASONIC_OUT, INPUT);
  pinMode(LF_ULTRASONIC_OUT, INPUT);
  pinMode(F_ULTRASONIC_OUT, INPUT);


  pinMode(LEFT_MOTOR, OUTPUT);
  pinMode(RIGHT_MOTOR, OUTPUT);
  pinMode(CUBE_INTAKE_1, OUTPUT);
  pinMode(CUBE_INTAKE_2, OUTPUT);
  _leftMotor.attach(LEFT_MOTOR);
  _rightMotor.attach(RIGHT_MOTOR);
  _armMotor.attach(CUBE_INTAKE_1);
  _clawMotor.attach(CUBE_INTAKE_2);
  
  pinMode(HALL_EFFECT, INPUT);

  _armMotor.write(100); // slightly above horizontal
  _clawMotor.write(CUBE_INTAKE_OPEN); // open position
  _HallValue = HALL_EFFECT.analogRead();
  initCompass();

  Serial.println("Initialized!");
}

void MSEBot::PingUltra(){

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

}

void MSEBot::TurnOnAxis(){
  _armMotor.write(100); // lift arm slightly to be above wall
  _leftMotor.writeMicroseconds(TURN_AXIS_R);
  _rightMotor.writeMicroseconds(TURN_AXIS_F);
  delay(1000); 
  _armMotor.write(80); // pushed against top of wall
}

void MSEBot::goForward(){
  _leftMotor.writeMicroseconds(FORWARD_SPEED);
  _rightMotor.writeMicroseconds(FORWARD_SPEED);
}

void MSEBot::moveIn(){
  _leftMotor.writeMicroseconds(FORWARD_SPEED);
  _rightMotor.writeMicroseconds(1500);
}

void MSEBot::moveOut(){
  _leftMotor.writeMicroseconds(1500);
  _rightMotor.writeMicroseconds(FORWARD_SPEED); 
}


int MSEBot::scanIR(){
  return Serial3.read(); //Attached to CN10-2-3
}

void MSEBot::readCompass(int* x, int* y, int* z){
  // Start readout at X MSB address
  Wire.beginTransmission(MAG3110_I2C_ADDRESS);
  Wire.write(MAG3110_OUT_X_MSB);
  Wire.endTransmission();

  delayMicroseconds(2);

  // Read out data using multiple byte read mode
  Wire.requestFrom(MAG3110_I2C_ADDRESS, 6);
  while( Wire.available() != 6 ) {}

  // Combine registers
  uint16_t values[3];
  for(uint8_t idx = 0; idx <= 2; idx++)
  {
    values[idx]  = Wire.read() << 8;  // MSB
    values[idx] |= Wire.read();     // LSB
  }

  // Put data into referenced variables
  *x = (int) values[0];
  *y = (int) values[1];
  *z = (int) values[2];
}

void MSEBot::initCompass(){
  Wire.begin();
  Wire.setClock(400000);
  
  uint8_t MODE;
  
  Wire.beginTransmission(MAG3110_I2C_ADDRESS);
  Wire.write(MAG3110_CTRL_REG1);
  Wire.endTransmission();
  
  delayMicroseconds(2);
  
  Wire.requestFrom(MAG3110_I2C_ADDRESS, 1);
  while(Wire.available())
  {
    MODE = Wire.read();
  }
  
  Wire.beginTransmission(MAG3110_I2C_ADDRESS);
  Wire.write(MAG3110_CTRL_REG1);
  Wire.write((MODE | MAG3110_ACTIVE_MODE));
  Wire.endTransmission();
}


void MSEBot::parallelFollow(){
  if(abs(_LF_ultrasonic_dist - _LR_ultrasonic_dist) < PARALLEL_TOLERANCE){
    goForward();
  }
  else if(_LF_ultrasonic_dist > _LR_ultrasonic_dist){
    moveIn();
  }
  else{
    moveOut();
  }
  
  if(_F_ultrasonic_dist < TURN_THRESHOLD){
    TurnOnAxis();
  }
  
  if(abs(_LF_ultrasonic_dist - WALL_TARGET_DIST) < WALL_TARGET_TOLERANCE){
    moveIn();
  }
  else{
    moveOut();
  }
}

bool MSEBot::checkForCube(){
  int cx, cy, cz;
  //monitor compass output
  readCompass(&cx, &cy, &cz);

  if (abs(HALL_EFFECT.analogRead() - _HallValue) > HALL_EFFECT_THRESHOLD) {
    _clawMotor.write(CUBE_INTAKE_CLOSE); // closed position
  }
  
  return (abs(HALL_EFFECT.analogRead() - _HallValue) > HALL_EFFECT_THRESHOLD);
}

void MSEBot::GO(){

  switch(_currentTask)
  {
    case 1: //Finding the Cube
    {
    Serial.println("Searching for the cube...");
      while(!_hasCube)
      {
        PingUltra();
        parallelFollow();
        _hasCube = checkForCube();
          Serial.print("F: ");
  Serial.print(_F_ultrasonic_dist);
  Serial.print(" LF: ");
  Serial.print(_LF_ultrasonic_dist);
  Serial.print("  LR: ");
  Serial.println(_LR_ultrasonic_dist);
        
      }
      _currentTask++;  //This task completed, proceed to next task
    }
    case 2: //Finding the Pyramid
    {
    Serial.println("Searching for the Pyramid...");

      _currentTask++;  //This task completed, proceed to next task
    }
    case 3: //Inserting the Cube in the Pyramid
    {
    Serial.println("Loading Cube into Pyramid...");

      _currentTask++;  //This task completed, proceed to next task
    }
    case 4:
    {
      while(1)
      {
        Serial.println("TASK COMPLETED!!");
        Serial.println("please reset!");
        delay(1000);
      }
    }
  }
}

