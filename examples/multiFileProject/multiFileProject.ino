/****************************************************************************************************************************
  multiFileProject.ino
  For STM32F/L/H/G/WB/MP1 boards with stm32duino Arduino_Core_STM32 core
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/STM32_ISR_Servo
  Licensed under MIT license
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#if !( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) || defined(STM32L5))
#error This code is designed to run on STM32F/L/H/G/WB/MP1 platform! Please check your Tools->Board setting.
#endif

#define STM32_ISR_SERVO_VERSION_MIN_TARGET      "STM32_ISR_Servo v1.1.0"
#define STM32_ISR_SERVO_VERSION_MIN             1001000

#include "multiFileProject.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "STM32_ISR_Servo.h"

void setup()
{
  Serial.begin(115200);

  while (!Serial);

  Serial.println("\nStart multiFileProject");
  Serial.println(STM32_ISR_SERVO_VERSION);

#if defined(STM32_ISR_SERVO_VERSION_MIN)

  if (STM32_ISR_SERVO_VERSION_INT < STM32_ISR_SERVO_VERSION_MIN)
  {
    Serial.print("Warning. Must use this example on Version equal or later than : ");
    Serial.println(STM32_ISR_SERVO_VERSION_MIN_TARGET);
  }

#endif
}

void loop()
{
  // put your main code here, to run repeatedly:
}
