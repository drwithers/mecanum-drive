#ifndef IRCONFIG_HPP
#define IRCONFIG_HPP

#define IR_INPUT_PIN    8
#define IR_FEEDBACK_LED_PIN 13
//#define NO_LED_FEEDBACK_CODE   // Activate this if you want to suppress LED feedback or if you do not have a LED. This saves 14 bytes code and 2 clock cycles per interrupt.
//#define DEBUG // to see if attachInterrupt is used
//#define TRACE // to see the state of the ISR state machine

#if !defined(STR_HELPER)
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#endif

#endif /* IRCONFIG_HPP */
