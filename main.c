// main.c
// GPIO blink LED with clock configuration
// Josh Brake
// jbrake@hmc.edu
// 9/16/24

// Includes for libraries
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_FLASH.h"
#include "starter.h"
#include "STM32L432KC_TMR.h"

int main(void) {
    // Configure flash to add waitstates to avoid timing errors
    configureFlash();

    // Setup the PLL and switch clock source to the PLL
    configureClock();
    
    // Connect system clock to tim 1, 15, 16
    configureTimers();
    
    for(int i = 0; i <sizeof(notes); i++) {
      setPWM(notes[i][0]);
      wait(notes[i][1]);
    }

    return 0;
}