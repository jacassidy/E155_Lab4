// STM32L432KC_TMR.c
// James Kaden Cassidy kacassidy@hmc.edu 9/28/2025
// Contains setup for timer 15 and use within wait function

#include "STM32L432KC_TIM.h"
#include "STM32L432KC_RCC.h"

#define READ_BIT(value, bit)   (((value) >> (bit)) & 0x1U)
#define SET_BIT(value, bit)    ((value) |=  (1U << (bit)))
#define CLEAR_BIT(value, bit)  ((value) &= ~(1U << (bit)))
#define TOGGLE_BIT(value, bit) ((value) ^=  (1U << (bit)))

// connects clock to timer 15 and enables counter
void configureTimer15(void){
  SET_BIT(RCC->APB2ENR, 16);
  SET_BIT(TIM15->CR1, 0);
}

// uses timer15 to create accurate delay in ms
void wait(int millis){

  uint32_t PSC_value          = 0x31FU;                                 // prescalar 800
  uint32_t wait_clock_cycles  = millis * 100;                           // prescalar 800 so only need to wait 100 clock cycles per millisecond
  uint32_t ARR_value          = (wait_clock_cycles & 0xFFFFU);
  
  // load autoreload
  TIM15->ARR = ARR_value;
  TIM15->PSC = PSC_value;
  
  // clear UG bit to ensure update evevnt on UG set
  CLEAR_BIT(TIM15->EGR, 0);
  // set UG bit to trigger update in EGR
  SET_BIT(TIM15->EGR, 0);
  // clear counter to begin count at 0
  TIM15->CNT = 0x0;

  // clear UIF bit in SR reg
  CLEAR_BIT(TIM15->SR, 0);

  // wait until UIF bit is set
  while (READ_BIT(TIM15->SR, 0) != 1){
    uint32_t dummby = 1;
  }
}
