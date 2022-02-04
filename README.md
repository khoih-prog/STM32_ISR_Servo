# STM32_ISR_Servo Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/STM32_ISR_Servo.svg?)](https://www.ardu-badge.com/STM32_ISR_Servo)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/STM32_ISR_Servo.svg)](https://github.com/khoih-prog/STM32_ISR_Servo/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/STM32_ISR_Servo/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/STM32_ISR_Servo.svg)](http://github.com/khoih-prog/STM32_ISR_Servo/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>

---
---

## Table of Contents

* [Why do we need this STM32_ISR_Servo library](#why-do-we-need-this-stm32_isr_servo-library)
  * [Features](#features)
  * [Important Notes about using ISR](#important-notes-about-using-isr)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](#changelog)
  * [Releases v1.0.0](#releases-v100)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [More useful Information](#more-useful-information)
  * [STM32 Hardware Timers](#stm32-hardware-timers)
  * [New functions](#new-functions)
  * [What special in this STM32_ISR_Servo library](#what-special-in-this-STM32_ISR_Servo-library)
* [HOWTO Usage](#howto-usage)
* [Examples](#examples)
  * [ 1. STM32_ISR_MultiServos](examples/STM32_ISR_MultiServos)
  * [ 2. STM32_MultipleRandomServos](examples/STM32_MultipleRandomServos)
  * [ 3. STM32_MultipleServos](examples/STM32_MultipleServos)
  * [ 4. ISR_MultiServos](examples/ISR_MultiServos)
  * [ 5. MultipleRandomServos](examples/MultipleRandomServos)
  * [ 6. MultipleServos](examples/MultipleServos)
* [Example STM32_ISR_MultiServos](#example-stm32_isr_multiservos)
  * [1. File STM32_ISR_MultiServos.ino](#1-file-stm32_isr_multiservosino)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. STM32_MultipleRandomServos on NUCLEO_F767ZI](#1-stm32_multiplerandomservos-on-nucleo_f767zi)
  * [2. STM32_MultipleRandomServos on NUCLEO_H743ZI2](#2-stm32_multiplerandomservos-on-nucleo_h743zi2)
  * [3. STM32_ISR_MultiServos on NUCLEO_L552ZE_Q](#3-stm32_isr_multiservos-on-nucleo_l552ze_q)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Releases](#releases)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)


---
---

### Why do we need this [STM32_ISR_Servo library](https://github.com/khoih-prog/STM32_ISR_Servo)

#### Features

Imagine you have a system with a **mission-critical function** controlling a **robot arm** or doing something much more important. You normally use a software timer to poll, or even place the function in loop(). But what if another function is blocking the loop() or setup().

So your function might not be executed, and the result would be disastrous.

You'd prefer to have your function called, no matter what happening with other functions (busy loop, bug, etc.).

The correct choice is to use a **Hardware Timer with Interrupt** to call your function.

These hardware timers, using interrupt, still work even if other functions are blocking. Moreover, they are **much more precise** (certainly depending on clock frequency accuracy) than other software timers using millis() or micros(). That's necessary if you need to measure some data requiring better accuracy.

Functions using normal software timers, relying on loop() and calling millis(), won't work if the **loop() or setup() is blocked by certain operation**. For example, certain function is blocking while it's connecting to WiFi or some services.

This library enables you to use `1 Hardware Timer` on an STM32F/L/H/G/WB/MP1-based board to control up to `16 independent servo motors`.


#### Important Notes about using ISR

1. Inside the attached function, delay() won’t work and the value returned by millis() will not increment. Serial data received while in the function may be lost. You should declare as volatile any variables that you modify within the attached function.

2. Typically global variables are used to pass data between an ISR and the main program. To make sure variables shared between an ISR and the main program are updated correctly, declare them as volatile.

3. Avoid using Serial.print()-related functions inside ISR. Just for temporary debug purpose, but even this also can crash the system any time. Beware.

4. Your functions are now part of **ISR (Interrupt Service Routine)**, and must be `lean / mean`, and follow certain rules. More to read on:

[HOWTO Attach Interrupt](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)


### Currently supported Boards
 
1. **STM32F/L/H/G/WB/MP1 boards (with 32+K Flash)**

- Nucleo-144
- Nucleo-64
- Discovery
- Generic STM32F0, STM32F1, STM32F2, STM32F3, STM32F4, STM32F7 (with 64+K Flash): x8 and up
- STM32L0, STM32L1, STM32L4, STM32L5
- STM32G0, STM32G4
- STM32H7
- STM32WB
- STM32MP1
- LoRa boards
- 3-D printer boards
- Generic Flight Controllers
- Midatronics boards
 
---
---

## Changelog

### Releases v1.0.0

1. Basic 16 ISR-based servo controllers using 1 hardware timer for STM32F/L/H/G/WB/MP1-based board
2. Tested with **STM32L5 (NUCLEO_L552ZE_Q)** and **STM32H7 (NUCLEO_H743ZI2)**


---
---

## Prerequisites

1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
2. [`Arduino Core for STM32 v2.2.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32F/L/H/G/WB/MP1 boards. [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)

---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for `STM32_ISR_Servo`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/STM32_ISR_Servo.svg?)](https://www.ardu-badge.com/STM32_ISR_Servo) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [STM32_ISR_Servo](https://github.com/khoih-prog/STM32_ISR_Servo) page.
2. Download the latest release `STM32_ISR_Servo-main.zip`.
3. Extract the zip file to `STM32_ISR_Servo-main` directory 
4. Copy whole `STM32_ISR_Servo-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**STM32_ISR_Servo** library](https://platformio.org/lib/show/12702/STM32_ISR_Servo) by using [Library Manager](https://platformio.org/lib/show/12702/STM32_ISR_Servo/installation). Search for **STM32_ISR_Servo** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

## More useful Information

### STM32 Hardware Timers

The Timers of STM32s are numerous, yet very sophisticated and powerful.

In general, across the STM32 microcontrollers families, the timer peripherals that have the same name also have the same features set, but there are a few exceptions. 

For example, the **TIM1** timer peripheral is shared across the STM32F1 Series, STM32F2 Series and STM32F4 Series, but for the specific case of STM32F30x microcontrollers family, the TIM1 timer peripheral features a bit richer features set than the TIM1 present in the other families.

The general purpose timers embedded by the STM32 microcontrollers share the same backbone structure; they differ only on the level of features embedded by a given timer peripheral. 

The level of features integration for a given timer peripheral is decided based on the applications field that it targets.

The timer peripherals can be classified as:
• Advanced-configuration timers like TIM1 and TIM8 among others.
• General-purpose configuration timers like TIM2 and TIM3 among others
• Lite-configuration timers like TIM9, TIM10, TIM12 and TIM16 among others
• Basic-configuration timers like TIM6 and TIM7 among others.

For example, **STM32F103C8T6** has one advance timer, while **STM32F103VET6** has two advanced timers. **Nucleo-144 STM32F767ZI boards have 14 Timers, TIM1-TIM14**.


<p align="center">
    <img src="https://github.com/khoih-prog/STM32_TimerInterrupt/blob/main/pics/STM32Timers.png">
</p>


More information can be found at [**Embedded-Lab STM32 TIMERS**](http://embedded-lab.com/blog/stm32-timers/)

To be sure which Timer is available for the board you're using, check the Core Package's related files. For example, for **Nucleo-144 STM32F767ZI**, check these files:
1. `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/system/Drivers/CMSIS/Device/ST/STM32F7xx/Include/stm32f7xx.h`
2. `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/system/Drivers/CMSIS/Device/ST/STM32F7xx/Include/stm32f767xx.h`

The information will be as follows:

```
typedef struct
{
  __IO uint32_t CR1;         /*!< TIM control register 1,              Address offset: 0x00 */
  __IO uint32_t CR2;         /*!< TIM control register 2,              Address offset: 0x04 */
  __IO uint32_t SMCR;        /*!< TIM slave mode control register,     Address offset: 0x08 */
  __IO uint32_t DIER;        /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
  __IO uint32_t SR;          /*!< TIM status register,                 Address offset: 0x10 */
  __IO uint32_t EGR;         /*!< TIM event generation register,       Address offset: 0x14 */
  __IO uint32_t CCMR1;       /*!< TIM capture/compare mode register 1, Address offset: 0x18 */
  __IO uint32_t CCMR2;       /*!< TIM capture/compare mode register 2, Address offset: 0x1C */
  __IO uint32_t CCER;        /*!< TIM capture/compare enable register, Address offset: 0x20 */
  __IO uint32_t CNT;         /*!< TIM counter register,                Address offset: 0x24 */
  __IO uint32_t PSC;         /*!< TIM prescaler,                       Address offset: 0x28 */
  __IO uint32_t ARR;         /*!< TIM auto-reload register,            Address offset: 0x2C */
  __IO uint32_t RCR;         /*!< TIM repetition counter register,     Address offset: 0x30 */
  __IO uint32_t CCR1;        /*!< TIM capture/compare register 1,      Address offset: 0x34 */
  __IO uint32_t CCR2;        /*!< TIM capture/compare register 2,      Address offset: 0x38 */
  __IO uint32_t CCR3;        /*!< TIM capture/compare register 3,      Address offset: 0x3C */
  __IO uint32_t CCR4;        /*!< TIM capture/compare register 4,      Address offset: 0x40 */
  __IO uint32_t BDTR;        /*!< TIM break and dead-time register,    Address offset: 0x44 */
  __IO uint32_t DCR;         /*!< TIM DMA control register,            Address offset: 0x48 */
  __IO uint32_t DMAR;        /*!< TIM DMA address for full transfer,   Address offset: 0x4C */
  __IO uint32_t OR;          /*!< TIM option register,                 Address offset: 0x50 */
  __IO uint32_t CCMR3;       /*!< TIM capture/compare mode register 3,      Address offset: 0x54 */
  __IO uint32_t CCR5;        /*!< TIM capture/compare mode register5,       Address offset: 0x58 */
  __IO uint32_t CCR6;        /*!< TIM capture/compare mode register6,       Address offset: 0x5C */
  __IO uint32_t AF1;         /*!< TIM Alternate function option register 1, Address offset: 0x60 */
  __IO uint32_t AF2;         /*!< TIM Alternate function option register 2, Address offset: 0x64 */

} TIM_TypeDef;
```

and

```
#define PERIPH_BASE            0x40000000UL /*!< Base address of : AHB/ABP Peripherals   
/*!< Peripheral memory map */
#define APB1PERIPH_BASE        PERIPH_BASE

/*!< APB1 peripherals */
#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000UL)
#define TIM3_BASE             (APB1PERIPH_BASE + 0x0400UL)
#define TIM4_BASE             (APB1PERIPH_BASE + 0x0800UL)
#define TIM5_BASE             (APB1PERIPH_BASE + 0x0C00UL)
#define TIM6_BASE             (APB1PERIPH_BASE + 0x1000UL)
#define TIM7_BASE             (APB1PERIPH_BASE + 0x1400UL)
#define TIM12_BASE            (APB1PERIPH_BASE + 0x1800UL)
#define TIM13_BASE            (APB1PERIPH_BASE + 0x1C00UL)
#define TIM14_BASE            (APB1PERIPH_BASE + 0x2000UL)

/*!< APB2 peripherals */
#define TIM1_BASE             (APB2PERIPH_BASE + 0x0000UL)
#define TIM8_BASE             (APB2PERIPH_BASE + 0x0400UL)
#define TIM9_BASE             (APB2PERIPH_BASE + 0x4000UL)
#define TIM10_BASE            (APB2PERIPH_BASE + 0x4400UL)
#define TIM11_BASE            (APB2PERIPH_BASE + 0x4800UL)

...

#define TIM2                ((TIM_TypeDef *) TIM2_BASE)
#define TIM3                ((TIM_TypeDef *) TIM3_BASE)
#define TIM4                ((TIM_TypeDef *) TIM4_BASE)
#define TIM5                ((TIM_TypeDef *) TIM5_BASE)
#define TIM6                ((TIM_TypeDef *) TIM6_BASE)
#define TIM7                ((TIM_TypeDef *) TIM7_BASE)
#define TIM12               ((TIM_TypeDef *) TIM12_BASE)
#define TIM13               ((TIM_TypeDef *) TIM13_BASE)
#define TIM14               ((TIM_TypeDef *) TIM14_BASE)
...
#define TIM1                ((TIM_TypeDef *) TIM1_BASE)
#define TIM8                ((TIM_TypeDef *) TIM8_BASE)
...
#define TIM9                ((TIM_TypeDef *) TIM9_BASE)
#define TIM10               ((TIM_TypeDef *) TIM10_BASE)
#define TIM11               ((TIM_TypeDef *) TIM11_BASE)

```

### New functions

```
// returns last position in degrees if success, or -1 on wrong servoIndex
int getPosition(unsigned servoIndex);

// returns pulseWidth in microsecs (within min/max range) if success, or 0 on wrong servoIndex
unsigned int getPulseWidth(unsigned servoIndex);
```

### What special in this [STM32_ISR_Servo library](https://github.com/khoih-prog/STM32_ISR_Servo)

Now these new **16 ISR-based Servo controllers** just use one STM32 Hardware Timer. The number 16 is just arbitrarily chosen, and depending on application, you can increase that number to 32, 48, etc. without problem.

The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers

Therefore, their executions are not blocked by bad-behaving functions / tasks. This important feature is absolutely necessary for mission-critical tasks. 

The [**STM32_MultipleServos**](examples/STM32_MultipleServos) example, which controls 6 servos independently, will demonstrate the nearly perfect accuracy.

Being ISR-based servo controllers, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet and Blynk services.

This non-being-blocked important feature is absolutely necessary for mission-critical tasks.

---
---

## HOWTO Usage

How to use:

```
#if !( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) || defined(STM32L5))
  #error This code is designed to run on STM32F/L/H/G/WB/MP1 platform! Please check your Tools->Board setting.
#endif

#define TIMER_INTERRUPT_DEBUG       0
#define ISR_SERVO_DEBUG             1

#include "STM32_ISR_Servo.h"

// Default is TIMER_SERVO (TIM7 for many boards)
#define USE_STM32_TIMER_NO          TIMER_SERVO

// Published values for SG90 servos; adjust if needed
#define MIN_MICROS        800  //544
#define MAX_MICROS        2450

#define SERVO_PIN_1       D1
#define SERVO_PIN_2       D2
#define SERVO_PIN_3       D3
#define SERVO_PIN_4       D4
#define SERVO_PIN_5       D5
#define SERVO_PIN_6       D6

typedef struct
{
  int     servoIndex;
  uint8_t servoPin;
} ISR_servo_t;

#if ( defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32L5) )

  #define NUM_SERVOS        3
  
  ISR_servo_t ISR_servo[NUM_SERVOS] =
  {
    { -1, SERVO_PIN_1 }, { -1, SERVO_PIN_2 }, { -1, SERVO_PIN_3 }
  };

#else

  #define NUM_SERVOS        6

  ISR_servo_t ISR_servo[NUM_SERVOS] =
  {
    { -1, SERVO_PIN_1 }, { -1, SERVO_PIN_2 }, { -1, SERVO_PIN_3 }, { -1, SERVO_PIN_4 }, { -1, SERVO_PIN_5 }, { -1, SERVO_PIN_6 }
  };

#endif

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  delay(200);

  Serial.print(F("\nStarting STM32_MultipleServos on ")); Serial.println(BOARD_NAME);
  Serial.println(STM32_ISR_SERVO_VERSION);

  //Select STM32 timer USE_STM32_TIMER_NO
  STM32_ISR_Servos.useTimer(USE_STM32_TIMER_NO);

  for (int index = 0; index < NUM_SERVOS; index++)
  {
    ISR_servo[index].servoIndex = STM32_ISR_Servos.setupServo(ISR_servo[index].servoPin, MIN_MICROS, MAX_MICROS);

    if (ISR_servo[index].servoIndex != -1)
    {
      Serial.print(F("Setup OK Servo index = ")); Serial.println(ISR_servo[index].servoIndex);
    }
    else
    {
      Serial.print(F("Setup Failed Servo index = ")); Serial.println(ISR_servo[index].servoIndex);
    }
  }
}

void loop()
{
  int position;      // position in degrees

  for (position = 0; position <= 180; position += 5)
  {
    // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    for (int index = 0; index < NUM_SERVOS; index++)
    {
      STM32_ISR_Servos.setPosition(ISR_servo[index].servoIndex, (position + index * (180 / NUM_SERVOS)) % 180 );
    }
    
    // waits 1s for the servo to reach the position
    delay(1000);
  }

  for (position = 180; position >= 0; position -= 5)
  {
    // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    for (int index = 0; index < NUM_SERVOS; index++)
    {
      STM32_ISR_Servos.setPosition(ISR_servo[index].servoIndex, (position + index * (180 / NUM_SERVOS)) % 180);
    }
    
    // waits 1s for the servo to reach the position
    delay(1000);
  }

  delay(5000);
}
```

---
---

### Examples: 

 1. [STM32_ISR_MultiServos](examples/STM32_ISR_MultiServos)
 2. [STM32_MultipleRandomServos](examples/STM32_MultipleRandomServos) 
 3. [STM32_MultipleServos](examples/STM32_MultipleServos) 
 4. [ISR_MultiServos](examples/ISR_MultiServos)
 5. [MultipleRandomServos](examples/MultipleRandomServos)
 6. [MultipleServos](examples/MultipleServos)
 
---

### Example [STM32_ISR_MultiServos](examples/STM32_ISR_MultiServos)


#### 1. File [STM32_ISR_MultiServos.ino](examples/STM32_ISR_MultiServos/STM32_ISR_MultiServos.ino)

```cpp
#if !( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) || defined(STM32L5))
  #error This code is designed to run on STM32F/L/H/G/WB/MP1 platform! Please check your Tools->Board setting.
#endif

#define TIMER_INTERRUPT_DEBUG       0
#define ISR_SERVO_DEBUG             1

#include "STM32_ISR_Servo.h"

// Default is TIMER_SERVO (TIM7 for many boards)
#define USE_STM32_TIMER_NO          TIMER_SERVO

// Published values for SG90 servos; adjust if needed
#define MIN_MICROS      800  //544
#define MAX_MICROS      2450

#define SERVO_PIN_1       D6
#define SERVO_PIN_2       D7

int servoIndex1  = -1;
int servoIndex2  = -1;

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  delay(500);

  Serial.print(F("\nStarting STM32_ISR_MultiServos on ")); Serial.println(BOARD_NAME);
  Serial.println(STM32_ISR_SERVO_VERSION);
  
  //Select STM32 timer USE_STM32_TIMER_NO
  STM32_ISR_Servos.useTimer(USE_STM32_TIMER_NO);

  servoIndex1 = STM32_ISR_Servos.setupServo(SERVO_PIN_1, MIN_MICROS, MAX_MICROS);
  servoIndex2 = STM32_ISR_Servos.setupServo(SERVO_PIN_2, MIN_MICROS, MAX_MICROS);

  if (servoIndex1 != -1)
    Serial.println(F("Setup Servo1 OK"));
  else
    Serial.println(F("Setup Servo1 failed"));

  if (servoIndex2 != -1)
    Serial.println(F("Setup Servo2 OK"));
  else
    Serial.println(F("Setup Servo2 failed"));
}

void loop()
{
  int position;

  if ( ( servoIndex1 != -1) && ( servoIndex2 != -1) )
  {
    for (position = 0; position <= 180; position++)
    {
      // goes from 0 degrees to 180 degrees
      // in steps of 1 degree

      if (position % 30 == 0)
      {
        Serial.print(F("Servo1 pos = ")); Serial.print(position);
        Serial.print(F(", Servo2 pos = ")); Serial.println(180 - position);
      }

      STM32_ISR_Servos.setPosition(servoIndex1, position);
      STM32_ISR_Servos.setPosition(servoIndex2, 180 - position);
      // waits 30ms for the servo to reach the position
      delay(30);
    }
    
    delay(5000);

    for (position = 180; position >= 0; position--)
    {
      // goes from 180 degrees to 0 degrees
      if (position % 30 == 0)
      {
        Serial.print(F("Servo1 pos = ")); Serial.print(position);
        Serial.print(F(", Servo2 pos = ")); Serial.println(180 - position);
      }

      STM32_ISR_Servos.setPosition(servoIndex1, position);
      STM32_ISR_Servos.setPosition(servoIndex2, 180 - position);
      // waits 30ms for the servo to reach the position
      delay(30);
    }
    
    delay(5000);
  }
}
```
---
---

### Debug Terminal Output Samples

### 1. STM32_MultipleRandomServos on NUCLEO_F767ZI


```
Starting STM32_MultipleRandomServos on NUCLEO_F767ZI
STM32_ISR_Servo v1.0.0
[ISR_SERVO] STM32TimerInterrupt: Timer Input Freq (Hz) = 108000000
[ISR_SERVO] Frequency = 1000000.00 , _count = 10
[ISR_SERVO] Starting  ITimer OK
Setup OK Servo index = 0
Setup OK Servo index = 1
Setup OK Servo index = 2
Setup OK Servo index = 3
Setup OK Servo index = 4
Setup OK Servo index = 5
Servos @ 0 degree
Servos idx = 0, act. pos. (deg) = [ISR_SERVO] Idx = 0
[ISR_SERVO] cnt = 80 , pos = 0
0, pulseWidth (us) = [ISR_SERVO] Idx = 0
[ISR_SERVO] cnt = 80 , pos = 0
800
Servos idx = 1, act. pos. (deg) = [ISR_SERVO] Idx = 1
[ISR_SERVO] cnt = 80 , pos = 0
0, pulseWidth (us) = [ISR_SERVO] Idx = 1
[ISR_SERVO] cnt = 80 , pos = 0
800
Servos idx = 2, act. pos. (deg) = [ISR_SERVO] Idx = 2
[ISR_SERVO] cnt = 80 , pos = 0
0, pulseWidth (us) = [ISR_SERVO] Idx = 2
[ISR_SERVO] cnt = 80 , pos = 0
800
Servos idx = 3, act. pos. (deg) = [ISR_SERVO] Idx = 3
[ISR_SERVO] cnt = 80 , pos = 0
0, pulseWidth (us) = [ISR_SERVO] Idx = 3
[ISR_SERVO] cnt = 80 , pos = 0
800
Servos idx = 4, act. pos. (deg) = [ISR_SERVO] Idx = 4
[ISR_SERVO] cnt = 80 , pos = 0
0, pulseWidth (us) = [ISR_SERVO] Idx = 4
[ISR_SERVO] cnt = 80 , pos = 0
800
Servos idx = 5, act. pos. (deg) = [ISR_SERVO] Idx = 5
[ISR_SERVO] cnt = 80 , pos = 0
0, pulseWidth (us) = [ISR_SERVO] Idx = 5
[ISR_SERVO] cnt = 80 , pos = 0
800
Servos @ 90 degree
```

---

### 2. STM32_MultipleRandomServos on NUCLEO_H743ZI2


```
Starting STM32_MultipleRandomServos on NUCLEO_H743ZI2
STM32_ISR_Servo v1.0.0
[ISR_SERVO] STM32TimerInterrupt: Timer Input Freq (Hz) = 240000000
[ISR_SERVO] Frequency = 1000000.00 , _count = 10
[ISR_SERVO] Starting  ITimer OK
Setup OK Servo index = 0
Setup OK Servo index = 1
Setup OK Servo index = 2
Setup OK Servo index = 3
Setup OK Servo index = 4
Setup OK Servo index = 5
Servos @ 0 degree
Servos idx = 0, act. pos. (deg) = [ISR_SERVO] Idx = 0
[ISR_SERVO] cnt = 80 , pos = 0
0, pulseWidth (us) = [ISR_SERVO] Idx = 0
[ISR_SERVO] cnt = 80 , pos = 0
800
Servos idx = 1, act. pos. (deg) = [ISR_SERVO] Idx = 1
[ISR_SERVO] cnt = 80 , pos = 0
0, pulseWidth (us) = [ISR_SERVO] Idx = 1
[ISR_SERVO] cnt = 80 , pos = 0
800
Servos idx = 2, act. pos. (deg) = [ISR_SERVO] Idx = 2
[ISR_SERVO] cnt = 80 , pos = 0
0, pulseWidth (us) = [ISR_SERVO] Idx = 2
[ISR_SERVO] cnt = 80 , pos = 0
800
Servos idx = 3, act. pos. (deg) = [ISR_SERVO] Idx = 3
[ISR_SERVO] cnt = 80 , pos = 0
0, pulseWidth (us) = [ISR_SERVO] Idx = 3
[ISR_SERVO] cnt = 80 , pos = 0
800
Servos idx = 4, act. pos. (deg) = [ISR_SERVO] Idx = 4
[ISR_SERVO] cnt = 80 , pos = 0
0, pulseWidth (us) = [ISR_SERVO] Idx = 4
[ISR_SERVO] cnt = 80 , pos = 0
800
Servos idx = 5, act. pos. (deg) = [ISR_SERVO] Idx = 5
[ISR_SERVO] cnt = 80 , pos = 0
0, pulseWidth (us) = [ISR_SERVO] Idx = 5
[ISR_SERVO] cnt = 80 , pos = 0
800
Servos @ 90 degree
Servos idx = 0, act. pos. (deg) = [ISR_SERVO] Idx = 0
[ISR_SERVO] cnt = 162 , pos = 90
90, pulseWidth (us) = [ISR_SERVO] Idx = 0
[ISR_SERVO] cnt = 162 , pos = 90
1620
Servos idx = 1, act. pos. (deg) = [ISR_SERVO] Idx = 1
[ISR_SERVO] cnt = 162 , pos = 90
90, pulseWidth (us) = [ISR_SERVO] Idx = 1
[ISR_SERVO] cnt = 162 , pos = 90
1620
Servos idx = 2, act. pos. (deg) = [ISR_SERVO] Idx = 2
[ISR_SERVO] cnt = 162 , pos = 90
90, pulseWidth (us) = [ISR_SERVO] Idx = 2
[ISR_SERVO] cnt = 162 , pos = 90
1620
Servos idx = 3, act. pos. (deg) = [ISR_SERVO] Idx = 3
[ISR_SERVO] cnt = 162 , pos = 90
90, pulseWidth (us) = [ISR_SERVO] Idx = 3
[ISR_SERVO] cnt = 162 , pos = 90
1620
Servos idx = 4, act. pos. (deg) = [ISR_SERVO] Idx = 4
[ISR_SERVO] cnt = 162 , pos = 90
90, pulseWidth (us) = [ISR_SERVO] Idx = 4
[ISR_SERVO] cnt = 162 , pos = 90
1620
Servos idx = 5, act. pos. (deg) = [ISR_SERVO] Idx = 5
[ISR_SERVO] cnt = 162 , pos = 90
90, pulseWidth (us) = [ISR_SERVO] Idx = 5
[ISR_SERVO] cnt = 162 , pos = 90
1620
Servos @ 180 degree
Servos idx = 0, act. pos. (deg) = [ISR_SERVO] Idx = 0
[ISR_SERVO] cnt = 245 , pos = 180
180, pulseWidth (us) = [ISR_SERVO] Idx = 0
[ISR_SERVO] cnt = 245 , pos = 180
2450
Servos idx = 1, act. pos. (deg) = [ISR_SERVO] Idx = 1
[ISR_SERVO] cnt = 245 , pos = 180
180, pulseWidth (us) = [ISR_SERVO] Idx = 1
[ISR_SERVO] cnt = 245 , pos = 180
2450
Servos idx = 2, act. pos. (deg) = [ISR_SERVO] Idx = 2
[ISR_SERVO] cnt = 245 , pos = 180
180, pulseWidth (us) = [ISR_SERVO] Idx = 2
[ISR_SERVO] cnt = 245 , pos = 180
2450
Servos idx = 3, act. pos. (deg) = [ISR_SERVO] Idx = 3
[ISR_SERVO] cnt = 245 , pos = 180
180, pulseWidth (us) = [ISR_SERVO] Idx = 3
[ISR_SERVO] cnt = 245 , pos = 180
2450
Servos idx = 4, act. pos. (deg) = [ISR_SERVO] Idx = 4
[ISR_SERVO] cnt = 245 , pos = 180
180, pulseWidth (us) = [ISR_SERVO] Idx = 4
[ISR_SERVO] cnt = 245 , pos = 180
2450
Servos idx = 5, act. pos. (deg) = [ISR_SERVO] Idx = 5
[ISR_SERVO] cnt = 245 , pos = 180
180, pulseWidth (us) = [ISR_SERVO] Idx = 5
[ISR_SERVO] cnt = 245 , pos = 180
2450
Servos sweeps from 0-180 degress
```

---

### 3. STM32_ISR_MultiServos on NUCLEO_L552ZE_Q

```
Starting STM32_ISR_MultiServos on NUCLEO_L552ZE_Q
STM32_ISR_Servo v1.0.0
[ISR_SERVO] STM32TimerInterrupt: Timer Input Freq (Hz) = 110000000
[ISR_SERVO] Frequency = 1000000.00 , _count = 10
[ISR_SERVO] Starting  ITimer OK
Setup Servo1 OK
Setup Servo2 OK
Servo1 pos = 0, Servo2 pos = 180
Servo1 pos = 30, Servo2 pos = 150
Servo1 pos = 60, Servo2 pos = 120
Servo1 pos = 90, Servo2 pos = 90
Servo1 pos = 120, Servo2 pos = 60
Servo1 pos = 150, Servo2 pos = 30
Servo1 pos = 180, Servo2 pos = 0
Servo1 pos = 180, Servo2 pos = 0
Servo1 pos = 150, Servo2 pos = 30
Servo1 pos = 120, Servo2 pos = 60
Servo1 pos = 90, Servo2 pos = 90
Servo1 pos = 60, Servo2 pos = 120
Servo1 pos = 30, Servo2 pos = 150
Servo1 pos = 0, Servo2 pos = 180
Servo1 pos = 0, Servo2 pos = 180
Servo1 pos = 30, Servo2 pos = 150
Servo1 pos = 60, Servo2 pos = 120
Servo1 pos = 90, Servo2 pos = 90
Servo1 pos = 120, Servo2 pos = 60
Servo1 pos = 150, Servo2 pos = 30
Servo1 pos = 180, Servo2 pos = 0
```

---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level from 0 to 2. Be careful and using level 2 only for temporary debug purpose only.

```cpp
#define TIMER_INTERRUPT_DEBUG       1
#define ISR_SERVO_DEBUG             1
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.


---
---

## Releases

### Releases v1.0.0

1. Basic 16 ISR-based servo controllers using 1 hardware timer for STM32F/L/H/G/WB/MP1-based board
2. Tested with **STM32L5 (NUCLEO_L552ZE_Q)** and **STM32H7 (NUCLEO_H743ZI2)**

---
---

### Issues

Submit issues to: [STM32_ISR_Servo issues](https://github.com/khoih-prog/STM32_ISR_Servo/issues)

---
---

## TO DO

1. Search for bug and improvement.

---

## DONE

1. Similar features for Arduino (UNO, Mega, etc...), ESP32 and ESP8266
2. Add functions `getPosition()` and `getPulseWidth()`
3. Optimize the code
4. Add more complicated examples

---
---

### Contributions and thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library. Especially to these people who have directly or indirectly contributed to this [STM32_ISR_Servo library](https://github.com/khoih-prog/STM32_ISR_Servo)


---

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/STM32_ISR_Servo/blob/main/LICENSE)

---

## Copyright

Copyright 2021- Khoi Hoang
