#include <Arduino.h>
#define LEFT -1
#define RIGHT 1
class Hand_robot
{
private:
    void setspeed(int spd);
    void startTimer(unsigned long _duration);
    bool isTimerExpired();
    void resetTimer();
public:
    uint16_t Motor1;
    uint16_t Motor2;
    uint16_t Motor3;
    uint16_t MotorPWM = 0;
    int inverse = 0;
    unsigned long startTime = 0;
    unsigned long duration = 0;
    Hand_robot(uint16_t Motor1, uint16_t Motor2, uint16_t Motor3, uint16_t MotorPWM, int inverse);
    ~Hand_robot();
    void begin();
    void HandRotateWithSpeed(String _direction,int pwm_val, int timer);
    void HandRotate(String _direction);
    void Hand_Stop();
};