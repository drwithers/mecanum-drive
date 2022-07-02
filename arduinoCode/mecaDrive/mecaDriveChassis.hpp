#ifndef MECADRIVECHASSIS_HPP
#define MECADRIVECHASSIS_HPP

#include "motor.hpp"

class MecaDriveChassis
{
public:
  MecaDriveChassis(int enPinFR, int in1PinFR, int in2PinFR,
      int enPinFL, int in1PinFL, int in2PinFL,
      int enPinBR, int in1PinBR, int in2PinBR,
      int enPinBL, int in1PinBL, int in2PinBL);
  void translate(float theta, float power);
  void rotate(float rotation);
  void direct(float theta, float translatePower, float rotation);
  void stopAll();

private:
  Motor frontRight;
  Motor frontLeft;
  Motor backRight;
  Motor backLeft;
};

#endif /* MECADRIVECHASSIS_HPP */
