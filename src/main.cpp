#include <Arduino.h>
#include "Hand_robot.h"

// handControl is the main method for control robot hand
// Motor1  is param for control motor forward
// Motor2  is param for control motor backward
// Motor3  is param for turn on , turn off motor open(1) off(0)
// MotorPWM is param for set speed to motor (0,255)
// inverse is param for initial hand ("LEFT" or "RIGHT")
Hand_robot handLeft = Hand_robot(30, 31, 32, 5, LEFT);
Hand_robot handRight = Hand_robot(34, 35, 39, 6, RIGHT);

const int maxSubstrings = 10;
const int maxSubstringLength = 8; // Maximum length of each substring

char inputBuffer[100];                              // Buffer to store input from Serial Monitor
char substrings[maxSubstrings][maxSubstringLength]; // Array to store the substrings

void setup()
{
  handLeft.begin();
  handRight.begin();
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0)
  {
    // Read input from Serial Monitor
    String s = Serial.readStringUntil('\n');
    s.toCharArray(inputBuffer,s.length());

    // Delimiter for strtok
    const char delimiter[] = ",";

    // Use strtok to split the string
    char *token ;
    token = strtok(inputBuffer, delimiter);

    int count = 0;

    // Iterate through the tokens and store them in the array
    while (token != NULL && count < maxSubstrings)
    {
      strncpy(substrings[count], token, maxSubstringLength);
      substrings[count][maxSubstringLength - 1] = '\0'; // Null-terminate the substring
      token = strtok(NULL, delimiter);
      count++;
    }

    // Print the substrings
    for (int i = 0; i < count; ++i)
    {
      Serial.print("parameter ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(substrings[i]);
    }
    int i_mode = atoi(substrings[0]);

    if (i_mode == 1)
    {
      int i_speed = atoi(substrings[2]);
      int i_timer = atoi(substrings[3]);
      handLeft.HandRotateWithSpeed(substrings[1], i_speed, i_timer);
      handRight.HandRotateWithSpeed(substrings[1], i_speed, i_timer);
    }
    else if (i_mode == 2)
    {
      handLeft.HandRotate(substrings[1]);
      handRight.HandRotate(substrings[1]);
    }
    else if (i_mode == 3)
    {
      for (int i = 0; i < 6; i++)
      {
        handLeft.HandRotate("fwd");
        handRight.HandRotate("back");
        handLeft.HandRotate("back");
        handRight.HandRotate("fwd");
      }
    }
    strcpy(substrings[0], 0);
    strcpy(substrings[1], 0);
    strcpy(substrings[2], 0);
    strcpy(substrings[3], 0);

  }
}