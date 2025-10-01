// STM32L432KC_TIM.h
// James Kaden Cassidy kacassidy@hmc.edu 9/28/2025
// Header for TIM functions

#include <stdint.h> // Include stdint header

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#define __IO volatile

#define TIM15_BASE (0x40014000U)

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
// Bitfield struct for GPIO
///////////////////////////////////////////////////////////////////////////////

#define TIM15 ((TIMER15_struct *) TIM15_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void configureTimer15(void);
void wait(int millis);


