#include <Arduino.h>
#define LEFT -1
#define RIGHT 1
class handControl
{
private:
public:
    uint16_t Motor1;
    uint16_t Motor2;
    uint16_t Motor3;
    uint16_t MotorPWM = 0;
    int inverse = 0;
    unsigned long startTime = 0;
    unsigned long duration = 0;
    handControl(uint16_t Motor1, uint16_t Motor2, uint16_t Motor3, uint16_t MotorPWM, int inverse);
    ~handControl();
    void begin();
    void setspeed(int spd);
    void startTimer(unsigned long _duration);
    bool isTimerExpired();
    void resetTimer();
    void Hand_Full(int pwm_val, int timer);
    void Hand_Fix(String _direction,int timer);
    void Hand_Stop();
};