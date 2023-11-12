#include "Hand_robot.h"

/// @brief handControl is the main method for control robot hand
/// @param Motor1  is param for control motor forward
/// @param Motor2  is param for control motor backward
/// @param Motor3  is param for turn on , turn off motor open(1) off(0)
/// @param MotorPWM is param for set speed to motor (0,255)
/// @param inverse is param for initial hand ("LEFT" or "RIGHT")
Hand_robot::Hand_robot(uint16_t Motor1, uint16_t Motor2, uint16_t Motor3, uint16_t MotorPWM, int inverse)
{
    this->Motor1 = Motor1;
    this->Motor2 = Motor2;
    this->Motor3 = Motor3;
    this->MotorPWM = MotorPWM;
    this->inverse = inverse;
}

Hand_robot::~Hand_robot()
{
}

void Hand_robot::begin()
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

void Hand_robot::setspeed(int spd)
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

void Hand_robot::startTimer(unsigned long _duration)
{
    startTime = millis();
    duration = _duration;
}

bool Hand_robot::isTimerExpired()
{
    return (millis() - startTime >= duration);
}

void Hand_robot::resetTimer()
{
    startTime = 0;
    duration = 0;
}

/// @brief Hand_Full is function for control robot hand with speed and timer
/// @param pwm_val  is param for motor pwm speed
/// @param timer is param for set time 
void Hand_robot::HandRotateWithSpeed(String _direction,int pwm_val, int timer)
{
    int direct = 0;
    if(pwm_val > 255){
        pwm_val = 255;
    }
    if(pwm_val < 0 || timer > 3000){
        return;
    }
    if (_direction == "fwd")
    {
        direct = 1;
    }
    if (_direction == "back")
    {
        direct = -1;
    }
    if(pwm_val >=200 && timer>=1500){
        timer=1000;
    }
    startTimer(timer);
    while (!isTimerExpired())
    {
        setspeed(direct * pwm_val);
    }
    Hand_Stop();
}

/// @brief Hand_Fix is function for control robot hand with direction and timer
/// @param _direction is param for set direction to hand ("forward" or "backward")
/// @param timer is param for set time
void Hand_robot::HandRotate(String _direction)
{
    int direct = 0;
    if (_direction == "fwd")
    {
        direct = 1;
    }
    if (_direction == "back")
    {
        direct = -1;
    }
    startTimer(500);
    while (!isTimerExpired())
    {   
        setspeed(direct * 100);
    }
    Hand_Stop();
}

// /// @brief Hand_Stop isfunction for stop motor
void Hand_robot::Hand_Stop()
{
    setspeed(0);
}

