#include "MSE-Bot.h"

void MSEBot::init(){
  Serial.begin(9600);
  Serial3.begin(2400); 

  pinMode(LR_ULTRASONIC_IN, OUTPUT);
  pinMode(LF_ULTRASONIC_IN, OUTPUT);
  pinMode(F_ULTRASONIC_IN, OUTPUT);
  pinMode(LR_ULTRASONIC_OUT, INPUT);
  pinMode(LF_ULTRASONIC_OUT, INPUT);
  pinMode(F_ULTRASONIC_OUT, INPUT);


  pinMode(LEFT_MOTOR, OUTPUT);
  pinMode(RIGHT_MOTOR, OUTPUT);
  leftMotor.attach(LEFT_MOTOR);
  rightMotor.attach(RIGHT_MOTOR);

}

void MSEBot::PingUltra(){

  digitalWrite(F_ULTRASONIC_IN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(F_ULTRASONIC_IN, LOW);
  Fecho = pulseIn(F_ULTRASONIC_OUT, HIGH, 10000);
  if(Fecho) LF_ultrasonic_dist = Fecho;

  digitalWrite(LF_ULTRASONIC_IN, HIGH);
  delayMicroseconds(10);  
  digitalWrite(LF_ULTRASONIC_IN, LOW);

  LFecho = pulseIn(LF_ULTRASONIC_OUT, HIGH, 10000);
  if(LFecho) LF_ultrasonic_dist = LFecho;

  digitalWrite(LR_ULTRASONIC_IN, HIGH);
  delayMicroseconds(10);  
  digitalWrite(LR_ULTRASONIC_IN, LOW);

  LRecho = pulseIn(LR_ULTRASONIC_OUT, HIGH, 10000);
  if(LRecho) LR_ultrasonic_dist = LRecho;

}

void MSEBot::TurnOnAxis(){
  leftMotor.writeMicroseconds(1250);
  rightMotor.writeMicroseconds(1750);
  delay(1000); 
}

void MSEBot::goForward(){
  leftMotor.writeMicroseconds(FORWARD_SPEED);
  rightMotor.writeMicroseconds(FORWARD_SPEED);
}

void MSEBot::moveIn(){
  leftMotor.writeMicroseconds(FORWARD_SPEED);
  rightMotor.writeMicroseconds(1500);
}

void MSEBot::moveOut(){
  leftMotor.writeMicroseconds(1500);
  rightMotor.writeMicroseconds(FORWARD_SPEED);	
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
		values[idx]  = Wire.read() << 8;	// MSB
		values[idx] |= Wire.read();			// LSB
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
	if(abs(LF_ultrasonic_dist - LR_ultrasonic_dist) <= PARALLEL_TOLERANCE){
		goForward();
	}
	else if(LF_ultrasonic_dist > LR_ultrasonic_dist){
		moveIn();
	}
	else{
		moveOut();
	}
	
	if(this->F_ultrasonic_dist < TURN_THRESHOLD){
		TurnOnAxis();
	}
	
	if(LF_ultrasonic_dist > WALL_TARGET_DIST){
		moveIn();
	}
	else{
		moveOut();
	}
}

void MSEBot::GO(){

	init();
	initCompass();
	int cx, cy, cz;

	switch(currentTask)
	{
		case 1: //Finding the Cube
		{
			while(!hasCube)
			{
				PingUltra();
				parallelFollow();
				readCompass(&cx, &cy, &cz);
				//some way of detecting the cube with the compass
				
			}
			currentTask++;  //This task completed, proceed to next task
		}
		case 2: //Finding the Pyramid
		{

			currentTask++;  //This task completed, proceed to next task
		}
		case 3: //Inserting the Cube in the Pyramid
		{

			currentTask++;  //This task completed, proceed to next task
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



