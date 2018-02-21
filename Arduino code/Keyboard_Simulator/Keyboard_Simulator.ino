/*
  Keyboard simulator

  This program is meant to simulate a keyboard to use in "Projects2".
  The program requires the TimerOne library: github.com/PaulStoffregen/TimerOne

  The circuit:
    At each pin there is a switch connected, and the switch to the ground.

  Usefull links:
    arduino.cc/en/Reference/MouseKeyboard
    arduino.cc/en/Reference/KeyboardPress
    arduino.cc/en/Reference/KeyboardModifiers
    
  Created 2-01-17
  By Dwight Van der Velpen
  Modified 5-01-17
  By Dwight Van der Velpen
*/

/*---------------------------------------------------------------------------------------------------*/
/* Includes */
#include <TimerOne.h>
#include <Keyboard.h>

/*---------------------------------------------------------------------------------------------------*/
/* Global Variables */
const byte pinList[] = { A3, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0, A1, A2}; // A3 added for Bluetooth Fix
const char linkedChars[] = {  
  'x', 'w', 's', 'q', KEY_F2, KEY_F4, KEY_F1, 'a', 'z', 
  KEY_RIGHT_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, KEY_RETURN, 
  KEY_BACKSPACE, KEY_UP_ARROW
};

bool pinFlags[sizeof(pinList)];
bool previousFlags[sizeof(pinList)];

/*---------------------------------------------------------------------------------------------------*/
/* Setup */
void setup() {
  /* Keyboard setup */
  Keyboard.begin();
  Keyboard.releaseAll();

  /* Pin setup */
  for (int i = 0; i < sizeof(pinList); i++) {
    pinMode(pinList[i], INPUT_PULLUP);
  }

  /* Timer setup */
  Timer1.initialize(100);
  Timer1.attachInterrupt(printFlags); // blinkLED to run every milisecond

}

/*---------------------------------------------------------------------------------------------------*/
/* Loop */
void loop() {
  for (int i = 0; i < sizeof(pinList); i++) {
   pinFlags[i] = !digitalRead(pinList[i]);
  }
}

/*---------------------------------------------------------------------------------------------------*/
/* Print Routine */
void printFlags(void) {  
  for (int i = 0; i < sizeof(pinList); i++) {
    if (pinFlags[i] && !previousFlags[i]){
      Keyboard.press(linkedChars[i]);
    }
    else if (!pinFlags[i] && previousFlags[i]){
      Keyboard.release(linkedChars[i]);
    }
    previousFlags[i] = pinFlags[i];
  }
}

