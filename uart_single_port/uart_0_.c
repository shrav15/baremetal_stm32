/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#define _RCC_BASE        ((uint32_t)(0x40023800))
#define _GPIOA_BASE      ((uint32_t)(0x40020000)) // PS5 MEANS 10:11
#define _UART4 ((uint32_t)(0x0x40004C00 ))


#define _RCC_AHB1ENR     (*(volatile uint32_t *)(_RCC_BASE + 0x30)) // AHB1 Peripheral Clock Enable Register
#define _RCC_ABH1RSTSR     (*(volatile uint32_t *)(_RCC_BASE + 0x10)) // AHB1 Peripheral Reset Register

#define _GPIOA_MODER     (*(volatile uint32_t *)(_GPIOA_BASE + 0x00))
#define  _GPIOA_ODR (*(volatile uint32_t *)(_GPIOA_BASE + 0x14))
#define _GPIOA_BSRR (*(volatile uint32_t *)(_GPIOA_BASE + 0x18))
#define _GPIOA_AFRL_0 ( * ( volatile uint32_t *) (_GPIOA_BASE +0x20 )) 
#define _GPIOA_AFRL_1 ( * ( volatile uint32_t *) (_GPIOA_BASE +0x24 )) 
#define _UART4_BRR  ( * ( volatile uint32_t *) (_UART4 +0x08 ))

typedef struct _UART{
    volatile uint32_t SR;    /*!< UART Status register,                   Address offset: 0x00 */
    volatile uint32_t DR;    /*!< UART Data register,                     Address offset: 0x04 */
    volatile uint32_t BRR;   /*!< UART Baud rate register,                Address offset: 0x08 */
    volatile uint32_t CR1;   /*!< UART Control register 1,                Address offset: 0x0C */
    volatile uint32_t CR2;   /*!< UART Control register 2,                Address offset: 0x10 */
    volatile uint32_t CR3;   /*!< UART Control register 3,                Address offset: 0x14 */
    volatile uint32_t GTPR;  /*!< UART Guard time and prescaler register, Address offset: 0x18 */
} UART_TypeDef;

UART_TypeDef *_UART4 = (UART_TypeDef *)_UART4; // BASE ADDRESSS 

void uart_init(uint32_t baud_rate)
{
    // enable the clock for GPIOA and UART4
    _RCC_AHB1ENR |= (1 << 0); // Enable clock for GPIOA
    _RCC_AHB1ENR |= (1 << 19); // Enable clock

    // uart 4 is connected to PA0 (TX) and PA1 (RX)
    // configure PA0 and PA1 as alternate function mode
    _GPIOA_MODER &= ~(0x3 << (0 * 2)); // Clear mode bits for PA0
    _GPIOA_MODER |= (0x2 << (0 * 2)); // Set mode bits to alternate function for PA0

    // configure PA1 as alternate function mode
    _GPIOA_MODER &= ~(0x3 << (1 * 2)); // Clear mode bits for PA1
    _GPIOA_MODER |= (0x2 << (1 * 2)); // Set mode bits to alternate function for PA1

    // configure the alternate function for PA0 and PA1 to AF8 (UART4)
    _GPIOA_AFRL_0 |= (1000 << 0);
    _GPIOA_AFRL_0 |= (1000 << 4);

    // set the baud rate
    int buadrate = ( 1 / baud_rate);
    _UART4_BRR = buadrate;
    UART4->CR1 |= (1 << 12); // Set the M bit to 0 for 8 data bits
    _UART4->CR1 |= ( 1 << 3) | (1 << 2) | ( 1 << 13);
}

void uart_send(uint8_t data)
{
    // Wait until the transmit data register is empty
    while (!(UART4->SR & (1 << 7)));

    // Write the data to the transmit data register
    UART4->DR = data;
}

void uart_send_string(const char *str)
{
    while (*str) {
        uart_send((uint8_t)(*str));
        str++;
    }
}
uint8_t uart_receive()
{
    uint8_t data;
    // Wait until the receive data register is not empty
    while (!(UART4->SR & (1 << 5)));

    // Read the data from the receive data register
    data = (uint8_t)(UART4->DR & 0xFF);
    return data;
}

int main()
{
    uart_init(9600);
    const char * _str  = "Hello World";
    uart_send_string(_str);


}
