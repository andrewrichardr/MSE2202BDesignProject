#include "MSE-bot.h"
MSEBot Robot;

void setup() {
    Robot.init();
}

void loop() {
    while (true) { //Loop until finds the cube;
        Robot.parallelFollow();
        if (Robot.checkForCube()) {
            Robot.setSpeed(0);
            Robot.parallelFollow();
            if (Robot.checkForCube() == 1) {
                Robot.closeClaw();
                break; //Need to write logic if the cube does not get picked up but claw is closed
            }
        }
    }

    while (true) { //Loop until finds the pyramid
        Robot.moveOut();
        delay(700);
        Robot.goForward();
        delay(700);
        while (true) {
            Robot.TurnOnAxisL();
            if (Robot.scanIRWide()) {

            }
        }
    }
    
    while(true){
      
    }

    while(true){
      
    }
}
