// motor.hpp
#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <Arduino.h>

class Motor {
  public:
    static const int MAX_MOTOR_PWM = 255;
    Motor(int enPin, int in1Pin, int in2Pin);
    void stop();
    void setSpeed(float power);
  
  private:
    void forward(int pwm);
    void backward(int pwm);
    int m_enPin{3};
    int m_in1Pin{2};
    int m_in2Pin{4};
};

#endif /* MOTOR_HPP */
