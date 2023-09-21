#include <Arduino.h>
#include "handControl.h"

// put function declarations here:
int myFunction(int, int);
handControl h1 = handControl();

void setup() {
  // put your setup code here, to run once:
  h1.testFunc(1,2);
  int temp1 = h1.var_public;
  // int temp2 = h1.var_private;
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}