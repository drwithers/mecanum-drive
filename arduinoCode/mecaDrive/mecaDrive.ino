#include <IRremote.hpp>
#include "motor.hpp"
#include "vehicleConfig.hpp"

const long MONITOR_INTERVAL = 250; 

Motor frontRightMotor(FRONT_EN_A_PIN, FRONT_IN_1_PIN, FRONT_IN_2_PIN);
Motor frontLeftMotor(FRONT_EN_B_PIN, FRONT_IN_3_PIN, FRONT_IN_4_PIN);
Motor backRightMotor(BACK_EN_B_PIN, BACK_IN_3_PIN, BACK_IN_4_PIN);
Motor backLeftMotor(BACK_EN_A_PIN, BACK_IN_1_PIN, BACK_IN_2_PIN);

bool isDone = false;
unsigned long previousMillis = 0;  

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

  // if (!isDone)
  // {
  //   frontRightMotor.setSpeed(-1.0);
  //   frontLeftMotor.setSpeed(-1.0);
  //   backRightMotor.setSpeed(1.0);
  //   backLeftMotor.setSpeed(1.0);
    
  //   delay(5000);

  //   frontRightMotor.setSpeed(0.2);
  //   frontLeftMotor.setSpeed(0.2);
  //   backRightMotor.setSpeed(-0.2);
  //   backLeftMotor.setSpeed(-0.2);
    
  //   delay(5000);
    
  //   isDone = true;
  // }
  // else
  // {
  //   // analogWrite(FRONT_EN_A_PIN, 0);
  //   // digitalWrite(FRONT_IN_1_PIN, LOW);
  //   // digitalWrite(FRONT_IN_2_PIN, LOW);
  //   frontRightMotor.stop();
  //   digitalWrite(FRONT_IN_3_PIN, LOW);
  //   digitalWrite(FRONT_IN_4_PIN, LOW);
  //   digitalWrite(BACK_IN_1_PIN, LOW);
  //   digitalWrite(BACK_IN_2_PIN, LOW);
  //   digitalWrite(BACK_IN_3_PIN, LOW);
  //   digitalWrite(BACK_IN_4_PIN, LOW);
  // }

  if (currentMillis - previousMillis >= MONITOR_INTERVAL) {
    previousMillis = currentMillis;

    if (IrReceiver.decode())
    {
      uint16_t cmd = IrReceiver.decodedIRData.command;
      Serial.print("cmd: 0x"); Serial.println(cmd,HEX);
  //    Serial.println(IrReceiver.decodedIRData.decodedRawData,HEX);
  //    IrReceiver.printIRResultShort(&Serial); // optional use new print version
      IrReceiver.resume(); // Enable receiving of the next value
      digitalWrite(STATUS_LED_PIN, HIGH);
    }
    else
    {
      digitalWrite(STATUS_LED_PIN, LOW);
    }
    
  }
}
