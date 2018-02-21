/*
  Button Tester

  This program is meant to test the functionality of all used buttons of "Projects2". It will serial print wich buttons are pressed.
  Analog pins are 18+
  The program requires the TimerOne library: github.com/PaulStoffregen/TimerOne

  The circuit:
    At each pin there is a switch connected, and the switch to the ground.

  Created 2-01-17
  By Dwight Van der Velpen
  Modified 5-01-17
  By Dwight Van der Velpen
*/

/*---------------------------------------------------------------------------------------------------*/
/* Includes */
#include <TimerOne.h>

/*---------------------------------------------------------------------------------------------------*/
/* Global Variables */
byte pinList[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0, A1, A2};
bool pinFlags[sizeof(pinList)];

/*---------------------------------------------------------------------------------------------------*/
/* Setup */
void setup() {
  /* Serial setup */
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }

  /* Pin setup */
  for (int i = 0; i < sizeof(pinList); i++) {
    pinMode(pinList[i], INPUT_PULLUP);
  }

  /* Timer setup */
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(printFlags); // blinkLED to run every second

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
  bool anyFlag = false;
  
  Serial.print(" Pressed buttons: ");
  for (int i = 0; i < sizeof(pinList); i++) {
    if(pinFlags[i]){
      anyFlag = true;
      String output = String(pinList[i], DEC);
      Serial.print(output);
      Serial.print(" ");
    }
  }
  if (!anyFlag) Serial.println("none");
  else Serial.println();
}

