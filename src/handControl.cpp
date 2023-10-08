#include "handControl.h"

handControl::handControl(uint16_t Motor1, uint16_t Motor2, uint16_t Motor3, uint16_t MotorPWM, int inverse)
{
    this->Motor1 = Motor1;
    this->Motor2 = Motor2;
    this->Motor3 = Motor3;
    this->MotorPWM = MotorPWM;
    this->inverse = inverse;
}

handControl::~handControl()
{
}

void handControl::begin()
{
    pinMode(this->Motor1, OUTPUT);
    pinMode(this->Motor2, OUTPUT);
    pinMode(this->Motor3, OUTPUT);
    pinMode(this->MotorPWM, OUTPUT);
    digitalWrite(this->Motor1, 0);
    digitalWrite(this->Motor2, 0);
    digitalWrite(this->Motor3, 0);
    analogWrite(this->MotorPWM, 255);
}

// /// @brief testFunc is test function for this project
// /// @param a is param first
// /// @param b is param second
void handControl::setspeed(int spd)
{
    if (spd*inverse < 0)
    {
        digitalWrite(Motor1, 1); // forward
        digitalWrite(Motor2, 0);
        digitalWrite(Motor3, 1);
    }
    else if (spd*inverse > 0)
    {
        digitalWrite(Motor1, 0); // back
        digitalWrite(Motor2, 1);
        digitalWrite(Motor3, 1);
    }
    else
    {
        digitalWrite(Motor1, 0);
        digitalWrite(Motor2, 0);
        digitalWrite(Motor3, 0);
        analogWrite(MotorPWM, 255);
    }
    analogWrite(MotorPWM, 255 - abs(spd));
}

// /// @brief testFunc is test function for this project
// /// @param a is param first
// /// @param b is param second
void handControl::startTimer(unsigned long _duration)
{
    startTime = millis();
    duration = _duration;
}

// /// @brief testFunc is test function for this project
// /// @param a is param first
// /// @param b is param second
bool handControl::isTimerExpired()
{
    return (millis() - startTime >= duration);
}

// /// @brief testFunc is test function for this project
// /// @param a is param first
// /// @param b is param second
void handControl::resetTimer()
{
    startTime = 0;
    duration = 0;
}

// /// @brief testFunc is test function for this project
// /// @param a is param first
// /// @param b is param second
void handControl::Hand_Full(int pwm_val, int timer)
{
    startTimer(timer);
    while (!isTimerExpired())
    {
        setspeed(pwm_val);
    }
    Hand_Stop();
}

// /// @brief testFunc is test function for this project
// /// @param a is param first
// /// @param b is param second
void handControl::Hand_Fix(String _direction, int timer)
{
    int direct = 0;
    if (_direction == "forward")
    {
        direct = 1;
    }
    if (_direction == "back")
    {
        direct = -1;
    }
    startTimer(timer);
    while (!isTimerExpired())
    {   
        setspeed(direct * 100);
    }
    Hand_Stop();
}

// /// @brief Hand_Stop isfunction for stop motor
void handControl::Hand_Stop()
{
    setspeed(0);
}

