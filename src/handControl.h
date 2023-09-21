#include <Arduino.h>
class handControl
{
private:
    /* data */
    int var_private = 10;
public:
    handControl(/* args */);
    ~handControl();
    int var_public = 100;
    void testFunc(int a,int b);
};