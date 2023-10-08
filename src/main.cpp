#include <Arduino.h>
#include "handControl.h"

handControl handLeft = handControl(8, 9, 10, 11,LEFT);
handControl handRight = handControl(4, 5, 6, 7, RIGHT);


void setup() {
  handLeft.begin();
  handRight.begin();
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Read the entire line from Serial Monitor

    // Split the input string into two values using a comma as a delimiter
    int commaIndex = input.indexOf(',');
    if (commaIndex != -1) {
      String value1 = input.substring(0, commaIndex); // Get the first value as a string
      String value2_str = input.substring(commaIndex + 1); // Get the second value as a string

      int value2 = value2_str.toInt(); // Convert the second value to an integer

      // Now you have value1 and value2 as your input variables
      // You can use them in your code as needed
      Serial.print("Received values: ");
      Serial.print(value1);
      Serial.print(", ");
      Serial.println(value2);
      handLeft.Hand_Fix(value1,value2);
      handRight.Hand_Fix(value1,value2);
      // Hand_Left_Full(value1,value2);
      // Hand_Right_Full(value1, value2);
    }
  }
}