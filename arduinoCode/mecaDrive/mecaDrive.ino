#include <Arduino.h>
#include "motor.hpp"
#include "vehicleConfig.hpp"

//IR receiver based on MinimalReceiver example from IRremote.hpp library
//https://github.com/Arduino-IRremote/Arduino-IRremote
#include "TinyIRReceiver.hpp"

const long IR_MONITOR_INTERVAL = 250; 

Motor frontRightMotor(FRONT_EN_A_PIN, FRONT_IN_1_PIN, FRONT_IN_2_PIN);
Motor frontLeftMotor(FRONT_EN_B_PIN, FRONT_IN_3_PIN, FRONT_IN_4_PIN);
Motor backRightMotor(BACK_EN_B_PIN, BACK_IN_3_PIN, BACK_IN_4_PIN);
Motor backLeftMotor(BACK_EN_A_PIN, BACK_IN_1_PIN, BACK_IN_2_PIN);

bool isDone = false;
unsigned long previousMillis = 0;  
float irMotorSpeed = 1.0;

volatile struct TinyIRReceiverCallbackDataStruct sCallbackData;

void setPwmFequencies();

void setup()
{
  setPwmFequencies();
  Serial.begin(115200);
  Serial.println(F("START " __FILE__ " from " __DATE__));
  initPCIInterruptForTinyReceiver();
  Serial.println(F("Ready to receive NEC IR signals at pin " STR(IR_INPUT_PIN)));
  pinMode(STATUS_LED_PIN, OUTPUT);
}

void loop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= IR_MONITOR_INTERVAL) {
    previousMillis = currentMillis;

    if (sCallbackData.justWritten)
    {
      sCallbackData.justWritten = false;
      Serial.print(F(" Command=0x"));
      Serial.println(sCallbackData.Command, HEX);
      digitalWrite(STATUS_LED_PIN, HIGH);
    }
    else
    {
      digitalWrite(STATUS_LED_PIN, LOW);
      sCallbackData.Command = 0x0;
    }
    
    switch (sCallbackData.Command)
    {
      case 0x18:
      case 0x15:
        //Forward (NORTH)
        frontRightMotor.setMotorSpeed(irMotorSpeed);
        frontLeftMotor.setMotorSpeed(irMotorSpeed);
        backRightMotor.setMotorSpeed(irMotorSpeed);
        backLeftMotor.setMotorSpeed(irMotorSpeed);
        break;
      case 0x52:
      case 0x19:
        //Backward (SOUTH)
        frontRightMotor.setMotorSpeed(-irMotorSpeed);
        frontLeftMotor.setMotorSpeed(-irMotorSpeed);
        backRightMotor.setMotorSpeed(-irMotorSpeed);
        backLeftMotor.setMotorSpeed(-irMotorSpeed);
        break;
      case 0x16:
        //Turn Left
        frontRightMotor.setMotorSpeed(irMotorSpeed);
        frontLeftMotor.setMotorSpeed(-irMotorSpeed);
        backRightMotor.setMotorSpeed(irMotorSpeed);
        backLeftMotor.setMotorSpeed(-irMotorSpeed);
        break;
      case 0x0D:
        //Turn Right
        frontRightMotor.setMotorSpeed(-irMotorSpeed);
        frontLeftMotor.setMotorSpeed(irMotorSpeed);
        backRightMotor.setMotorSpeed(-irMotorSpeed);
        backLeftMotor.setMotorSpeed(irMotorSpeed);
        break;
      case 0x08:
        //WEST
        frontRightMotor.setMotorSpeed(irMotorSpeed);
        backLeftMotor.setMotorSpeed(irMotorSpeed);
        frontLeftMotor.setMotorSpeed(-irMotorSpeed);
        backRightMotor.setMotorSpeed(-irMotorSpeed);
        break;
      case 0x5A:
        //EAST
        frontRightMotor.setMotorSpeed(-irMotorSpeed);
        backLeftMotor.setMotorSpeed(-irMotorSpeed);
        frontLeftMotor.setMotorSpeed(irMotorSpeed);
        backRightMotor.setMotorSpeed(irMotorSpeed);
        break;
      case 0x5E:
        //NORTH-EAST
        frontRightMotor.stopMotor();
        backLeftMotor.stopMotor();
        frontLeftMotor.setMotorSpeed(irMotorSpeed);
        backRightMotor.setMotorSpeed(irMotorSpeed);
        break;
      case 0x0C:
        //NORTH-WEST
        frontRightMotor.setMotorSpeed(irMotorSpeed);
        backLeftMotor.setMotorSpeed(irMotorSpeed);
        frontLeftMotor.stopMotor();
        backRightMotor.stopMotor();
        break;
      case 0x42:
        //SOUTH-WEST
        frontRightMotor.stopMotor();
        backLeftMotor.stopMotor();
        frontLeftMotor.setMotorSpeed(-irMotorSpeed);
        backRightMotor.setMotorSpeed(-irMotorSpeed);
        break;
      case 0x4A:
        //SOUTH-EAST
        frontRightMotor.setMotorSpeed(-irMotorSpeed);
        backLeftMotor.setMotorSpeed(-irMotorSpeed);
        frontLeftMotor.stopMotor();
        backRightMotor.stopMotor();
        break;
        //TODO: This change of speed is causing something to break in the IR receiver.
      case 0x44:
        irMotorSpeed = 0.3;
        break;
      case 0x40:
        irMotorSpeed = 0.6;
        break;
      case 0x43:
        irMotorSpeed = 1.0;
        break;
      default:
        frontRightMotor.stopMotor();
        frontLeftMotor.stopMotor();
        backRightMotor.stopMotor();
        backLeftMotor.stopMotor();
        break;
    }
  }
} /* loop */

void setPwmFequencies()
{
  // Source http://domoticx.com/arduino-pwm-frequency-and-timers/
  // set timer 1 divisor to  1024 for PWM frequency of    30.64 Hz
  TCCR1B = TCCR1B & B11111000 | B00000101;
  // set timer 2 divisor to  1024 for PWM frequency of    30.64 Hz
  TCCR2B = TCCR2B & B11111000 | B00000111;
}

void handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat)
{
    sCallbackData.Address = aAddress;
    sCallbackData.Command = aCommand;
    sCallbackData.isRepeat = isRepeat;
    sCallbackData.justWritten = true;
}
