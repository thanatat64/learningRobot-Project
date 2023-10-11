#include <Arduino.h>
#include "handControl.h"

handControl handLeft = handControl(30, 31, 32, 5,LEFT);
handControl handRight = handControl(34, 35, 36, 6, RIGHT);


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
      String value1_str = input.substring(0, commaIndex); // Get the first value as a string
      String value2_str = input.substring(commaIndex + 1); // Get the second value as a string

      int value1 = value1_str.toInt();
      int value2 = value2_str.toInt(); // Convert the second value to an integer

      // Now you have value1 and value2 as your input variables
      // You can use them in your code as needed
      Serial.print("Received values: ");
      if (value1 > 0)
      {
        Serial.print(value1);
        Serial.print(", ");
      Serial.println(value2);
        handLeft.Hand_Full(value1,value2);
        handRight.Hand_Full(value1,value2);
      }else{
        Serial.print(value1_str);
        Serial.print(", ");
        Serial.println(value2);
        handLeft.Hand_Fix(value1_str,value2);
        handRight.Hand_Fix(value1_str,value2);
      }
    }
  }
}