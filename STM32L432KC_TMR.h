// James Kaden Cassidy kacassidy@hmc.edu 9/28/2025
// STM32L432KC_TMR.h
// Header for TMR functions

#ifndef STM32L4_GPIO_H
#define STM32L4_GPIO_H

#include <stdint.h> // Include stdint header

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#define __IO volatile

#define TIM16_BASE (0x40014400U)
#define TIM15_BASE (0x40014000U)

typedef struct {
  __IO uint32_t CR1;       // 0x00
  __IO uint32_t CR2;       // 0x04
  __IO uint32_t UNLISTED1; // 0x08
  __IO uint32_t DIER;      // 0x0C
  __IO uint32_t SR;        // 0x10
  __IO uint32_t EGR;       // 0x14
  __IO uint32_t CCMR1;     // 0x18
  __IO uint32_t UNLISTED2; // 0x1C
  __IO uint32_t CCER;      // 0x20
  __IO uint32_t CNT;       // 0x24
  __IO uint32_t PSC;       // 0x28
  __IO uint32_t ARR;       // 0x2C
  __IO uint32_t RCR;       // 0x30
  __IO uint32_t CCR1;      // 0x34
  __IO uint32_t UNLISTED3; // 0x38
  __IO uint32_t UNLISTED4; // 0x3C
  __IO uint32_t UNLISTED5; // 0x40
  __IO uint32_t BDTR;      // 0x44
} TIMER16_struct;

typedef struct {
  __IO uint32_t CR1;       // 0x00
  __IO uint32_t CR2;       // 0x04
  __IO uint32_t SMCR;      // 0x08
  __IO uint32_t DIER;      // 0x0C
  __IO uint32_t SR;        // 0x10
  __IO uint32_t EGR;       // 0x14
  __IO uint32_t CCMR1;     // 0x18
  __IO uint32_t UNLISTED2; // 0x1C
  __IO uint32_t CCER;      // 0x20
  __IO uint32_t CNT;       // 0x24
  __IO uint32_t PSC;       // 0x28
  __IO uint32_t ARR;       // 0x2C
  __IO uint32_t RCR;       // 0x30
  __IO uint32_t CCR1;      // 0x34
  __IO uint32_t UNLISTED3; // 0x38
  __IO uint32_t UNLISTED4; // 0x3C
  __IO uint32_t UNLISTED5; // 0x40
  __IO uint32_t BDTR;      // 0x44

} TIMER15_struct;

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

// Values for GPIO pins ("val" arguments)
#define GPIO_LOW    0
#define GPIO_HIGH   1

// Base addresses for GPIO ports
#define GPIOA_BASE  (0x48000000UL)

// Arbitrary GPIO functions for pinMode()
#define GPIO_INPUT  0
#define GPIO_OUTPUT 1
#define GPIO_ALT    2
#define GPIO_ANALOG 3

///////////////////////////////////////////////////////////////////////////////
// Bitfield struct for GPIO
///////////////////////////////////////////////////////////////////////////////

#define TIM15 ((TIMER15_struct *) TIM15_BASE)
#define TIM16 ((TIMER16_struct *) TIM16_BASE)

// GPIO register structs here
typedef struct {
    volatile uint32_t MODER;   // GPIO Offset 0x00 GPIO port mode register
    volatile uint32_t OTYPER;  // GPIO Offset 0x04
    volatile uint32_t OSPEEDR; // GPIO Offset 0x08
    volatile uint32_t PURPDR;  // GPIO Offset 0x0C
    volatile uint32_t IDR;     // GPIO Offset 0x10
    volatile uint32_t ODR;     // GPIO Offset 0x14
    volatile uint32_t BSRR;    // GPIO Offset 0x18
    volatile uint32_t LCKR;    // GPIO Offset 0x1C
    volatile uint32_t AFRL;    // GPIO Offset 0x20
    volatile uint32_t AFRH;    // GPIO Offset 0x24
} GPIO;

// Pointers to GPIO-sized chunks of memory for each peripheral
#define GPIOA ((GPIO *) GPIOA_BASE)

#define GPIO GPIOA

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void pinMode(int pin, int function);

int digitalRead(int pin);

void digitalWrite(int pin, int val);

void togglePin(int pin);

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void configureTimers(void);
void wait(int millis);
void setPWM(int hz);

#endif


