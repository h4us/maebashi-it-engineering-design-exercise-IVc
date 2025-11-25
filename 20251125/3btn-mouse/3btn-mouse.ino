/*
  ButtonMouseControl

  For Leonardo and Due boards only.

  Controls the mouse from five pushbuttons on an Arduino Leonardo, Micro or Due.

  Hardware:
  - five pushbuttons attached to D2, D3, D4, D5, D6

  The mouse movement is always relative. This sketch reads four pushbuttons,
  and uses them to set the movement of the mouse.

  WARNING: When you use the Mouse.move() command, the Arduino takes over your
  mouse! Make sure you have control before you use the mouse commands.

  created 15 Mar 2012
  modified 27 Mar 2012
  by Tom Igoe

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/usb/ButtonMouseControl/

  modified to only using 3 buttons by Takanobu Inafuku
*/

#include "Mouse.h"

// set pin numbers for the five buttons:
const int aButton = 2;
const int bButton = 3;
const int mouseButton = 4;

int range = 5;           // output range of X or Y movement; affects movement speed
int responseDelay = 10;  // response delay of the mouse, in ms


void setup() {
  // initialize the buttons' inputs:
  pinMode(aButton, INPUT_PULLUP);
  pinMode(bButton, INPUT_PULLUP);
  pinMode(mouseButton, INPUT_PULLUP);
  Mouse.begin();
}

void loop() {
  // read the buttons:
  int upState = !digitalRead(aButton) && digitalRead(mouseButton);
  int downState = !digitalRead(bButton) && digitalRead(mouseButton);
  int rightState = !digitalRead(aButton) && !digitalRead(mouseButton);
  int leftState = !digitalRead(bButton) && !digitalRead(mouseButton);
  int clickState = !digitalRead(mouseButton) && digitalRead(aButton) && digitalRead(bButton);

  // calculate the movement distance based on the button states:
  int xDistance = (leftState - rightState) * range;
  int yDistance = (upState - downState) * range;

  // if X or Y is non-zero, move:
  if ((xDistance != 0) || (yDistance != 0)) {
    Mouse.move(xDistance, yDistance, 0);
  }

  // if the mouse button is pressed:
  if (clickState == 1) {
    // if the mouse is not pressed, press it:
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  } else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }

  // a delay so the mouse doesn't move too fast:
  delay(responseDelay);
}
