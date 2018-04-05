#include "MSE-bot.h"
MSEBot Robot;

void setup() {
  Robot.init();
  Robot.moveArmOut();
  Robot.openClaw();
  Robot.findWall();
}

void loop() {
  bool hasCube= 0;
  bool hasPyr= 0;
   while (!hasCube) { //Loop until robot finds the cube
        Robot.parallelFollow(); // Follows walls of arena and scans for cube
         Robot.readCompass();
         Serial.println(Robot._compassMagnitude); 
            if (Robot._compassMagnitude> 5000) { // Finds cube within gripping distance
              delay(500);
              Robot.StopDrive();
              delay(1000);
                Robot.closeClaw(); // Pulls cube into robot
                delay(500);
                Robot.moveArmIn();
                if (Robot.checkForCube() != 1) { // If we failed to pick up the cube try again
                    Robot.openClaw();
                    Robot.moveArmOut();
                    hasCube= 1;
                    continue;
                }
                Robot.setSpeed(1); // setup for finding pyramid
                Robot.TurnOnAxisL();
                delay(500); // Turn 20 degrees
                break; 
            }
    }

    while(!hasPyr){
      Robot.StopDrive();
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

