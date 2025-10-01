// James Kaden Cassidy kacassidy@hmc.edu 9/28/2025
// STM32L432KC_TMR.c
// Code for TMR functions

#include "STM32L432KC_TMR.h"
#include "STM32L432KC_RCC.h"

#define READ_BIT(value, bit)   (((value) >> (bit)) & 0x1U)
#define SET_BIT(value, bit)    ((value) |=  (1U << (bit)))
#define CLEAR_BIT(value, bit)  ((value) &= ~(1U << (bit)))
#define TOGGLE_BIT(value, bit) ((value) ^=  (1U << (bit)))

void pinMode(int pin, int function) {
    switch(function) {
        case GPIO_INPUT:
            GPIO->MODER &= ~(0b11 << 2*pin);
            break;
        case GPIO_OUTPUT:
            GPIO->MODER |= (0b1 << 2*pin);
            GPIO->MODER &= ~(0b1 << (2*pin+1));
            break;
        case GPIO_ALT:
            GPIO->MODER &= ~(0b1 << 2*pin);
            GPIO->MODER |= (0b1 << (2*pin+1));
            break;
        case GPIO_ANALOG:
            GPIO->MODER |= (0b11 << 2*pin);
            break;
    }
}

int digitalRead(int pin) {
    return ((GPIO->IDR) >> pin) & 1;
}

void digitalWrite(int pin, int val) {
    GPIO->ODR |= (1 << pin);
}

void togglePin(int pin) {
    // Use XOR to toggle
    GPIO->ODR ^= (1 << pin);
}

void configureAPB(int timer_num) {
  // Default prescalar values acceptable

  int APB_timer_enable_bit = 0;
  switch(timer_num) {
    case 16: // timer 16
      SET_BIT(RCC->APB2ENR, 17);
      SET_BIT(TIM16->CR1, 0);
      // setGPIO
      SET_BIT(RCC->AHB2ENR, 0);
      pinMode(6, GPIO_ALT);
      GPIO->AFRL |= (0b1110U << 24);
      TIM16->CCER |= 1U;
      SET_BIT(TIM16->CCER, 3);
      SET_BIT(TIM16->BDTR, 15);
      CLEAR_BIT(TIM16->CCMR1, 0);
      CLEAR_BIT(TIM16->CCMR1, 1);
      SET_BIT(TIM16->CCMR1, 3); // Enable ARR load to compare
      break;
    case 15: // timer 15
      SET_BIT(RCC->APB2ENR, 16);
      SET_BIT(TIM15->CR1, 0);
      break;
  }
}


void configureTimer(int timer_num){
  configureAPB(timer_num);
}

void configureTimers(void){
  configureTimer(15);
  configureTimer(16);
}

void wait(int millis){
  // reset timer 16

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

void setPWM(int hz) {

  uint32_t wait_counter_clock_cycles = 80000000 / hz;
  
  uint32_t PSC_value = 1;

  while (wait_counter_clock_cycles & 0xFFFF0000U){ // while more than 16 bits of cycle needed, shift 
    wait_counter_clock_cycles  /= 2;
    PSC_value                  *= 2;
  }

  uint32_t ARR_value          = wait_counter_clock_cycles;
  uint32_t CCR_value          = ARR_value >> 1;

  // load autoreload
  TIM16->ARR  = ARR_value;
  TIM16->PSC  = PSC_value - 1;
  TIM16->CCR1 = CCR_value;

  // TIM16->CCMR1 bits [1:0] = 0 for output mode on pin (CC1)

  if (hz == 0){
    // Freeze PWM
    CLEAR_BIT(TIM16->CCMR1, 6);
    CLEAR_BIT(TIM16->CCMR1, 5);
    CLEAR_BIT(TIM16->CCMR1, 4);
  } else {
    //Set PWM mode 1 (start high)
    SET_BIT(TIM16->CCMR1, 6);
    SET_BIT(TIM16->CCMR1, 5);
    CLEAR_BIT(TIM16->CCMR1, 4);
  }

  // clear UG bit to ensure update event on UG set
  CLEAR_BIT(TIM16->EGR, 0);
  // set UG bit to trigger update in EGR
  SET_BIT(TIM16->EGR, 0);
}

