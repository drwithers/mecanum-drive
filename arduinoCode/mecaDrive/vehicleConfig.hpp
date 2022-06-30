// vehicleConfig.hpp
#ifndef VEHICLECONFIG_HPP
#define VEHICLECONFIG_HPP

// Pin constants
// MOTOR PINS
const int FRONT_EN_A_PIN = 3;
const int FRONT_IN_1_PIN = 2;
const int FRONT_IN_2_PIN = 4;
const int FRONT_IN_3_PIN = 5;
const int FRONT_IN_4_PIN = 7;
const int FRONT_EN_B_PIN = 9;
const int BACK_EN_A_PIN = 10;
const int BACK_IN_1_PIN = 15;
const int BACK_IN_2_PIN = 16;
const int BACK_IN_3_PIN = 17;
const int BACK_IN_4_PIN = 18;
const int BACK_EN_B_PIN = 11;

//OTHER PINS
const int STATUS_LED_PIN = 12;

//IR STUFF
#define IR_INPUT_PIN    8
#define IR_FEEDBACK_LED_PIN 13
//#define NO_LED_FEEDBACK_CODE   // Activate this if you want to suppress LED feedback or if you do not have a LED. This saves 14 bytes code and 2 clock cycles per interrupt.
//#define DEBUG // to see if attachInterrupt is used
//#define TRACE // to see the state of the ISR state machine

#if !defined(STR_HELPER)
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#endif

#endif /* VEHICLECONFIG_HPP */
