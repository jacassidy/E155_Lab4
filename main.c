// main.c
// James Kaden Cassidy kacassidy@hmc.edu 9/30/25
// GPIO pin A6 driven to tune of melodies

// Includes for libraries
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_FLASH.h"
#include "starter.h"
#include "STM32L432KC_TIM.h"
#include "STM32L432KC_GPIO.h"

int main(void) {
    // Configure flash to add waitstates to avoid timing errors
    configureFlash();

    // Setup the PLL and switch clock source to the PLL
    configureClock();
    
    // Connect system clock to tim 15, 16
    configureTimer15();
    setupPWM_TIM16();
    
    for(volatile int i = 0; i < (sizeof(notes) / (2*sizeof(int))); i++) {
      setPWM(notes[i][0]);
      wait(notes[i][1]);
    }
    
    setPWM(0);
    wait(500);
    wait(500);
    wait(500);

    for(volatile int i = 0; i < (sizeof(chorus) / (2*sizeof(int))); i++) {
      setPWM(chorus[i][0]);
      wait(chorus[i][1]);
    }

    return 0;
}