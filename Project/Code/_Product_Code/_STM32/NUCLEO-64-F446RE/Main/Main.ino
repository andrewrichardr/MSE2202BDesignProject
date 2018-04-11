#include "MSE-bot.h"
MSEBot Robot;

void setup() {
  Robot.init();
  Robot.moveLift(1);
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
                hasCube = 1;
                break; 
            }
    }
    while(!hasPyr){
bool focused, wide;
         
    //Loop until finds the pyramid
    while(!wide || !focused) {
      wide = Robot.scanIRWide();
      focused = Robot.scanIRFocused();
      
      Robot.TurnOnAxisL();
      delay(300);
      Robot.goForward();
      delay(300);

      if(focused){
        Robot.intakeOn();
        delay(100);
        Robot.goForward();
        delay(500);
        Robot.StopDrive();
        Robot.moveLift(0);
        Robot.openClaw();
      }
      if(wide){
        Robot.TurnOnAxisL();
        delay(7500);
        Robot.intakeOn();
        delay(100);
        Robot.goForward();
        delay(500);
        Robot.StopDrive();
        Robot.moveLift(0);
        delay(100);
                Robot.openClaw();
        
      }

        
    }

    Robot.StopDrive();
 
    
    // Slowly pinpoint pyramid with shrouded IR
    while(!Robot.scanIRFocused()) {
      if(Robot.scanIRFocused()){
          break;
        }
        Robot.TurnOnAxisL();
        if(Robot.scanIRFocused()){
          break;
        }
        if(Robot.scanIRFocused()){
          break;
        }
    }

    Robot.StopDrive();
    Robot.intakeOn();

    delay(500);
    
    // Push into pyramid with intake until it's in the intake
    while(!Robot.hasPyramid()){ 
        Robot.goForward();
        delay(10000);
        break;
    }
    
    Robot.placePyramid();
    
    }
/*    */
}

