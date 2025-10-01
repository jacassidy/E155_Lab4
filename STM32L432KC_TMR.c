// James Kaden Cassidy kacassidy@hmc.edu 9/28/2025
// STM32L432KC_TMR.c
// Code for TMR functions

#include "bitwiseRW.h"
#include "STM32L432KC_TMR.h"
#include "STM32L432KC_RCC.h"

void configureAHB(int presc) {
  // Default value acceptable
}

void configureAPB(int presc, int timer_number) {
  // Default prescalar values acceptable

  int APB_timer_enable_bit = 0;
  switch(timer_number) {
    case 16: // timer 16
      APB_timer_enable_bit = 17;
      break;
    case 15: // timer 15
      APB_timer_enable_bit = 16;
      break;
  }

  SET_BIT(RCC->APB2ENR, APB_timer_enable_bit);
}

void configureMultiplier(int presc) {
  // Default values acceptable
}

void configureTimer(int timer_num){
  
}

void configureTimers(){
  configureTimer(15);
  configureTimer(16);
}

void wait(int millis){
  // reset timer 15

  uint32_t PSC_value          = 0x31FU;                                 // prescalar 800
  uint32_t wait_clock_cycles  = millis * 100;                           // prescalar 800 so only need to wait 100 clock cycles per millisecond
  uint32_t ARR_value          = (wait_clock_cycles & 0xFFFFU);
  //uint32_t RCR_value          = ((wait_clock_cycles >> 16) & 0x00FFU);
  
  // load autoreload and repitition counter
  TIM15->ARR = ARR_value;
  //TIM15->RCR = RCR_value;
  TIM15->PSC = PSC_value;


  // clear UG bit to ensure update evevnt on UG set
  TIM15->SR &= 0x0U;
  // set UG bit to trigger update in EGR
  TIM15->SR |= 0x1U;
  // clear counter to begin count at 0
  

  // clear UIF bit in SR reg
  TIM15->SR &= 0x0U;

  // wait until UIF bit is set
  while (TIM15->SR & 0x1U) {

  }
}