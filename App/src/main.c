#include "stm32f4xx.h"

void delay(volatile int count);

int main(void) {
    // Enable clocks for GPIOA (button) and GPIOG (LED)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable GPIOA clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN; // Enable GPIOG clock

    // Configure PA0 as input (button)
    GPIOA->MODER &= ~(3U << (0 * 2)); // Input mode (00)

    // Configure PG13 as output (LED)
    GPIOG->MODER &= ~(3U << (13 * 2)); // Clear mode for PG13
    GPIOG->MODER |= (1U << (13 * 2));  // Output mode (01)
    GPIOG->OTYPER &= ~(1U << 13);      // Push-Pull
    GPIOG->PUPDR &= ~(3U << (13 * 2)); // No Pull-Up/Down

    int button_state = 0; // Track button press state

    while (1) {
        if ((GPIOA->IDR & (1U << 0)) == 0) { // Button is active LOW
            if (button_state == 0) { 
                GPIOG->ODR ^= (1U << 13); // Toggle LED
                button_state = 1; // Mark button as pressed
            }
        } else {
            button_state = 0; // Reset when button is released
        }
        delay(10000);
    } 
}

// Simple delay function (blocking)
void delay(volatile int count) {
    while (count--) {
        // Busy-wait
    }



} 
