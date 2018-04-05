#include "MSE-bot.h"
MSEBot Robot;

void setup() {
    Robot.init();
    //Robot.moveArmOut();
    Robot.openClaw();
    Robot.findWall();

}

void loop() {
  while(1){
    
    Robot.parallelFollow();

    Robot.readCompass();

    if(Robot._compassMagnitude> 2000){
      Robot.setSpeed(0);
      if(Robot._compassMagnitude> 4500){
        delay(105);
        Robot.closeClaw();
        Robot.setSpeed(1);
        break;
      }
    }
/*
  while(1){
    Robot.TurnOnAxisL();
    delay(300);
    Robot.goForward();
  }
  

    /*
    //Loop until finds the pyramid
    while(!Robot.scanIRWide()) {
        Robot.scanField();
    }
    
    Robot.setSpeed(0);
    
    // Slowly pinpoint pyramid with shrouded IR
    while(!Robot.scanIRFocused()) {
        Robot.TurnOnAxisL();
    }
    
    Robot.intakeOn();
    
    // Push into pyramid with intake until it's in the intake
    while(!Robot.hasPyramid()){ 
        Robot.goForward();
        Robot.checkForPyramid();
    }
    
    Robot.placePyramid();
    */
}
}

