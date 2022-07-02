#include "mecaDriveChassis.hpp"

MecaDriveChassis::MecaDriveChassis(int enPinFR, int in1PinFR, int in2PinFR,
      int enPinFL, int in1PinFL, int in2PinFL,
      int enPinBR, int in1PinBR, int in2PinBR,
      int enPinBL, int in1PinBL, int in2PinBL)
          : frontRight(enPinFR, in1PinFR, in2PinFR),
            frontLeft(enPinFL, in1PinFL, in2PinFL),
            backRight(enPinBR, in1PinBR, in2PinBR),
            backLeft(enPinBL, in1PinBL, in2PinBL){}

void MecaDriveChassis::stopAll()
{
  frontRight.stopMotor();
  frontLeft.stopMotor();
  backRight.stopMotor();
  backLeft.stopMotor();
}

void MecaDriveChassis::direct(float theta, float power, float rotation)
{
  float frp = sin(theta - PI / 4) * power + rotation;
  float flp = cos(theta - PI / 4) * power - rotation;
  float brp = cos(theta - PI / 4) * power + rotation;
  float blp = sin(theta - PI / 4) * power - rotation;
  float limit = max(abs(frp), abs(flp));
  limit = max(limit, abs(brp));
  limit = max(limit, abs(blp));
  limit = max(limit, 1);
  frontRight.setMotorSpeed(frp/limit);
  frontLeft.setMotorSpeed(flp/limit);
  backRight.setMotorSpeed(brp/limit);
  backLeft.setMotorSpeed(blp/limit);
}

void MecaDriveChassis::translate(float theta, float power)
{
  frontRight.setMotorSpeed(sin(theta - PI / 4) * power);
  frontLeft.setMotorSpeed(cos(theta - PI / 4) * power);
  backRight.setMotorSpeed(cos(theta - PI / 4) * power);
  backLeft.setMotorSpeed(sin(theta - PI / 4) * power);
}

void MecaDriveChassis::rotate(float rotation)
{
  frontRight.setMotorSpeed(rotation);
  frontLeft.setMotorSpeed(-rotation);
  backRight.setMotorSpeed(rotation);
  backLeft.setMotorSpeed(-rotation);
}
