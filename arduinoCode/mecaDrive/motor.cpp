#include "motor.hpp"

Motor::Motor(int enPin, int in1Pin, int in2Pin) 
    : m_enPin(enPin), m_in1Pin(in1Pin), m_in2Pin(in2Pin)
{
  pinMode(m_enPin, OUTPUT);
  pinMode(m_in1Pin, OUTPUT);
  pinMode(m_in2Pin, OUTPUT);
  analogWrite(m_enPin, 0);
  digitalWrite(m_in1Pin, LOW);
  digitalWrite(m_in2Pin, LOW);
}

void Motor::stopMotor()
{
  analogWrite(m_enPin, 0);
  digitalWrite(m_in1Pin, HIGH);
  digitalWrite(m_in2Pin, HIGH);
}

void Motor::setMotorSpeed(float power)
{
  int pwm = power*MAX_MOTOR_PWM;
  pwm = abs(pwm);
  pwm = min(pwm,MAX_MOTOR_PWM);
  if (0 <= power)
  {
    forward(pwm);
  }
  else
  {
    backward(pwm);
  }
}

void Motor::forward(int pwm)
{
  analogWrite(m_enPin, pwm);
  digitalWrite(m_in1Pin, HIGH);
  digitalWrite(m_in2Pin, LOW);
}

void Motor::backward(int pwm)
{
  analogWrite(m_enPin, pwm);
  digitalWrite(m_in1Pin, LOW);
  digitalWrite(m_in2Pin, HIGH);
}
