// James Kaden Cassidy kacassidy@hmc.edu 9/28/2025
// STM32L432KC_TMR.h
// Header for TMR functions

#define STM32L4_GPIO_H

#include <stdint.h> // Include stdint header

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#define __IO volatile uint32_t

#define TIM16_BASE (0x40014400U)
#define TIM15_BASE (0x40014000U)

typedef struct {
  __IO CR1;       // 0x00
  __IO CR2;       // 0x04
  __IO UNLISTED1; // 0x08
  __IO DIER;      // 0x0C
  __IO SR;        // 0x10
  __IO EGR;       // 0x14
  __IO CCMR1;     // 0x18
  __IO UNLISTED2; // 0x1C
  __IO CCER;      // 0x20
  __IO CNT;       // 0x24
  __IO PSC;       // 0x28
  __IO ARR;       // 0x2C
  __IO RCR;       // 0x30
  __IO CCR1;      // 0x34
} TIMER16_struct;

typedef struct {
  __IO CR1;       // 0x00
  __IO CR2;       // 0x04
  __IO SMCR;      // 0x08
  __IO DIER;      // 0x0C
  __IO SR;        // 0x10
  __IO EGR;       // 0x14
  __IO CCMR1;     // 0x18
  __IO UNLISTED2; // 0x1C
  __IO CCER;      // 0x20
  __IO CNT;       // 0x24
  __IO PSC;       // 0x28
  __IO ARR;       // 0x2C
  __IO RCR;       // 0x30
  __IO CCR1;      // 0x34
} TIMER15_struct;

#define TIM15 ((TIMER16_struct *) TIM15_BASE)
#define TIM16 ((TIMER *) TIM16_BASE)


///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void configureTimerClock();
void wait(int millis);

