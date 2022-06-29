#include <IRremote.hpp>
#include "motor.hpp"
#include "vehicleConfig.hpp"

const long IR_MONITOR_INTERVAL = 250; 

Motor frontRightMotor(FRONT_EN_A_PIN, FRONT_IN_1_PIN, FRONT_IN_2_PIN);
Motor frontLeftMotor(FRONT_EN_B_PIN, FRONT_IN_3_PIN, FRONT_IN_4_PIN);
Motor backRightMotor(BACK_EN_B_PIN, BACK_IN_3_PIN, BACK_IN_4_PIN);
Motor backLeftMotor(BACK_EN_A_PIN, BACK_IN_1_PIN, BACK_IN_2_PIN);

bool isDone = false;
unsigned long previousMillis = 0;  
float irMotorSpeed = 1.0;

void setPwmFequencies()
{
  // Source http://domoticx.com/arduino-pwm-frequency-and-timers/
  // set timer 1 divisor to  1024 for PWM frequency of    30.64 Hz
  TCCR1B = TCCR1B & B11111000 | B00000101;
  // set timer 2 divisor to  1024 for PWM frequency of    30.64 Hz
  TCCR2B = TCCR2B & B11111000 | B00000111;
}

void setup()
{
  setPwmFequencies();
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);
  pinMode(STATUS_LED_PIN, OUTPUT);
}

void loop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= IR_MONITOR_INTERVAL) {
    previousMillis = currentMillis;

    uint16_t irCmd(0);
    uint32_t irRaw(0);

    if (IrReceiver.decode())
    {
      irCmd = IrReceiver.decodedIRData.command;
      irRaw = IrReceiver.decodedIRData.decodedRawData;
      Serial.println();
      Serial.print("cmd: 0x"); Serial.println(irCmd,HEX);
      Serial.print("raw: 0x"); Serial.println(irRaw,HEX);
      IrReceiver.printIRResultShort(&Serial); // optional use new print version
      IrReceiver.resume(); // Enable receiving of the next value
      digitalWrite(STATUS_LED_PIN, HIGH);
    }
    else
    {
      digitalWrite(STATUS_LED_PIN, LOW);
    }

    switch (irCmd)
    {
      case 0x18:
      case 0x15:
        //Forward (NORTH)
        frontRightMotor.setSpeed(irMotorSpeed);
        frontLeftMotor.setSpeed(irMotorSpeed);
        backRightMotor.setSpeed(irMotorSpeed);
        backLeftMotor.setSpeed(irMotorSpeed);
        break;
      case 0x52:
      case 0x19:
        //Backward (SOUTH)
        frontRightMotor.setSpeed(-irMotorSpeed);
        frontLeftMotor.setSpeed(-irMotorSpeed);
        backRightMotor.setSpeed(-irMotorSpeed);
        backLeftMotor.setSpeed(-irMotorSpeed);
        break;
      case 0x16:
        //Turn Left
        frontRightMotor.setSpeed(irMotorSpeed);
        frontLeftMotor.setSpeed(-irMotorSpeed);
        backRightMotor.setSpeed(irMotorSpeed);
        backLeftMotor.setSpeed(-irMotorSpeed);
        break;
      case 0x0D:
        //Turn Right
        frontRightMotor.setSpeed(-irMotorSpeed);
        frontLeftMotor.setSpeed(irMotorSpeed);
        backRightMotor.setSpeed(-irMotorSpeed);
        backLeftMotor.setSpeed(irMotorSpeed);
        break;
      case 0x08:
        //WEST
        frontRightMotor.setSpeed(irMotorSpeed);
        backLeftMotor.setSpeed(irMotorSpeed);
        frontLeftMotor.setSpeed(-irMotorSpeed);
        backRightMotor.setSpeed(-irMotorSpeed);
        break;
      case 0x5A:
        //EAST
        frontRightMotor.setSpeed(-irMotorSpeed);
        backLeftMotor.setSpeed(-irMotorSpeed);
        frontLeftMotor.setSpeed(irMotorSpeed);
        backRightMotor.setSpeed(irMotorSpeed);
        break;
      case 0x5E:
        //NORTH-EAST
        frontRightMotor.stop();
        backLeftMotor.stop();
        frontLeftMotor.setSpeed(irMotorSpeed);
        backRightMotor.setSpeed(irMotorSpeed);
        break;
      case 0x0C:
        //NORTH-WEST
        frontRightMotor.setSpeed(irMotorSpeed);
        backLeftMotor.setSpeed(irMotorSpeed);
        frontLeftMotor.stop();
        backRightMotor.stop();
        break;
      case 0x42:
        //SOUTH-WEST
        frontRightMotor.stop();
        backLeftMotor.stop();
        frontLeftMotor.setSpeed(-irMotorSpeed);
        backRightMotor.setSpeed(-irMotorSpeed);
        break;
      case 0x4A:
        //SOUTH-EAST
        frontRightMotor.setSpeed(-irMotorSpeed);
        backLeftMotor.setSpeed(-irMotorSpeed);
        frontLeftMotor.stop();
        backRightMotor.stop();
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
        frontRightMotor.stop();
        frontLeftMotor.stop();
        backRightMotor.stop();
        backLeftMotor.stop();
        break;
    }
  }
} /* loop */
