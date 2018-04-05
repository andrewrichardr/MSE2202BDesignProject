#include "MSE-bot.h"
MSEBot Robot;

void setup() {
    Robot.init();
    Robot.moveArmOut();
    Robot.openClaw();
    Robot.findWall();

}

void loop() {
Robot.parallelFollow();
Robot.readCompass();
Serial.println(Robot._compassMagnitude);
if(Robot._compassMagnitude> 4500){
  delay(150);
  Robot.closeClaw();
}
  /*
  
   while (true) { //Loop until robot finds the cube
        Robot.parallelFollow(); // Follows walls of arena and scans for cube
        if (Robot.checkForCube()) { // Finds cube within large or small distance
            Robot.setSpeed(0);
            if (Robot.checkForCube() == 1) { // Finds cube within gripping distance
                Robot.closeClaw(); // Pulls cube into robot
                Robot.moveArm(0);
                if (Robot.checkForCube() != 1) { // If we failed to pick up the cube try again
                    Robot.openClaw();
                    Robot.moveArm(1);
                    continue;
                }
                Robot.setSpeed(1); // setup for finding pyramid
                Robot.TurnOnAxisL();
                delay(5000); // Turn 160 degrees
                break; 
            }
        }
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

