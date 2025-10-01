// STM32L432KC_GPIO.c
// James Kaden Cassidy kacassidy@hmc.edu 9/28/2025
// Source code for GPIO functions, namely using timer 16 to create a pwm at a given frequency and fixed 50% duty cycle

#include "STM32L432KC_GPIO.h"
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

// Enables clock for tim15 and connects timer to gpio pin a6
void setupPWM_TIM16(void){
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
}

// sets the rate at which pwm pulses, is always 50% duty cycle
void setPWM(int hz) {

  uint32_t wait_counter_clock_cycles = 80000000 / hz; // get total System clock cycles per period
  
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
