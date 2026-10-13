/*
  This code is copied from Arduino_CapacitiveTouch library's example: LoveButton.ino

  Modified by Takanobu Inafuku / inafact
 */

#include "Arduino_CapacitiveTouch.h"

CapacitiveTouch touchButton = CapacitiveTouch(D2);

/* - 複数指定可能
CapacitiveTouch touchButton2 = CapacitiveTouch(D3);
*/

void setup() {
  Serial.begin(9600);
  
  if(touchButton.begin()){
    Serial.println("Capacitive touch sensor [1] initialized.");
  } else {
    Serial.println("Failed to initialize capacitive touch sensor. Please use a supported pin.");
    exit(-1);
  }
  // - 選んだ導体に応じて調整する
  touchButton.setThreshold(2000);
  
  /* - 複数指定可能
  if(touchButton2.begin()){
    Serial.println("Capacitive touch sensor [2] initialized.");
  } else {
    Serial.println("Failed to initialize capacitive touch sensor 2. Please use a supported pin.");
    exit(-1);
  }
  // - 選んだ導体に応じて調整する
  touchButton2.setThreshold(1000);
  */
}

void loop() {
  int sensorValue = touchButton.read();
  Serial.print("Raw value [1]: ");
  Serial.println(sensorValue);
  if (touchButton.isTouched()) {
    Serial.println("Button 1 touched!");
  }

  /* - 複数指定可能
  int sensorValue2 = touchButton2.read();
  Serial.print("Raw value [2]: ");
  Serial.println(sensorValue2);
  if (touchButton2.isTouched()) {
    Serial.println("Button 2 touched!");
  }
  */
  
  delay(100);
}
