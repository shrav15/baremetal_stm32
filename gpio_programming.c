#include "mbed.h"
#include "stdio.h"
#include <cstdio>

// main() runs in its own thread in the OS
/*
main thread is this :- 
*/


#define LED1_PIN 5

/* Delay function */
void delay(volatile int count) {
    for (volatile int i = 0; i < count * 45000; i++) {
        /* Do nothing, just waste time */
       // printf(".");
    }
}
#define _RCC_BASE        ((uint32_t)(0x40023800))

#define _GPIOA_BASE      ((uint32_t)(0x40020000)) // PS5 MEANS 10:11
#define _GPIOB_BASE      ((uint32_t)(0x40020400))
#define _GPIOC_BASE      ((uint32_t)(0x40020800))

#define _GPIOA_MODER     (*(volatile uint32_t *)(_GPIOA_BASE + 0x00))
#define _RCC_AHB1ENR     (*(volatile uint32_t *)(_RCC_BASE + 0x30)) // AHB1 Peripheral Clock Enable Register
#define _RCC_ABH1RSTSR     (*(volatile uint32_t *)(_RCC_BASE + 0x10)) // AHB1 Peripheral Reset Register
#define _RCC_AHB1LPENR     (*(volatile uint32_t *)(_RCC_BASE + 0x50)) // AHB1 Peripheral Clock Enable in Low Power Mode Register
#define _GPIOA_ODR (*(volatile uint32_t *)(_GPIOA_BASE + 0x14))
#define _GPIOA_BSRR (*(volatile uint32_t *)(_GPIOA_BASE + 0x18))

// Thread thread1; 
// DigitalOut led1(LED1);
// volatile bool running  = true;
// void thread_a (DigitalOut * led )
// {
    
//     while (running)
//     {
//         *led = ! *led;
//         ThisThread::sleep_for(1s);

//     }
// }
int main()
{
    // thread1.start(callback(thread_a , &led1));
    _RCC_AHB1ENR |= (1<<0); // Enable clock for GPIOA (assuming GPIOA is used)
    // congifure the bits in the GPIO port mode register to set the pin as output
    // For example, if GPIO_Pin is 5, you would set the corresponding bits in the GPIOA_MODER register to configure it as output
    _GPIOA_MODER &= ~(0x3 << (5 * 2)); // Clear the mode bits for the pin
    _GPIOA_MODER |= (0x1 << (5 * 2)); // Set the mode bits to output
    
    while (1) {
        
        // clear the bit 21 to set the pin low
       
        _GPIOA_BSRR &= ~(1 << 5); // Set the pin low
        _GPIOA_BSRR |= (1 << 21); // Set the pin low by default
        // clear bit 5 
        delay(500); // Delay for a while (adjust the delay as needed)
        printf("on\n");
        _GPIOA_BSRR &= ~(1 << 21); // Set the pin low by default
        _GPIOA_BSRR |= (1 << 5); // Set the pin high
        delay(500); // Delay for a while (adjust the delay as needed)
        printf("off\n");
       
    }
}

