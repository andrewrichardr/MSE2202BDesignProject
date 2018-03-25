/*

 MSE 2202 Lab 2, Prelab, Version D
 Language: Arduino
 Author: Michael Naish
 Date: 12/01/16
 
 Rev 1 - Initial version
 
 */

const int ledPins[] = {
  4, 5, 6, 7};                             // select the digital pins for the LEDs
const int numberLEDs = 
  sizeof(ledPins) / sizeof(ledPins[0]);    // number of LEDs in display
const byte states[] = {                   // array of LED states
  B00000000, 
  B00010000, 
  B00110000,
  B01110000,
  B11110000,
  B11100000,
  B11000000,
  B10000000,
  B00000000};
int curState = 0;                          // current state of LEDs
boolean dir = 0;                           // direction: 0, ascending; 1, descending
unsigned long prevMillis = 0;              // start time for delay cycle, in milliseconds
unsigned long curMillis = 0;               // current time, in milliseconds
int pause = 100;                           // time delay for switching effect

void setup() {
  DDRD = DDRD | B11111100;                 // set all LED pins (except RX and TX) as outputs
}

void loop() {
  curMillis = millis();                    // get the current time in milliseconds
  if(curMillis - prevMillis > pause)       // check to see if elapsed time matched the desired delay
  {
    prevMillis = curMillis;                // update the start time for the next delay cycle
    PORTD = states[curState];              // write desired output state directly to PORTD (pins 0-7)
    if(!dir) {                             // "ascending"
      curState++;                          // shift to next state
    }
    else {                                 // "descending"
      curState--;                          // shift to previous state
    }
    // if at ends, change direction
    if(curState == numberLEDs * 2 || curState == 0) {
      dir = !dir;
    }
  }
}




