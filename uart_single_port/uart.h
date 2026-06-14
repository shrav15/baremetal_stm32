#ifndef UART_H
#define UART_H


#include <stdint.h>
/*
1. define the base address of the rcc 

*/
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

typedef struct UART{
    volatile uint32_t SR;    /*!< UART Status register,                   Address offset: 0x00 */
    volatile uint32_t DR;    /*!< UART Data register,                     Address offset: 0x04 */
    volatile uint32_t BRR;   /*!< UART Baud rate register,                Address offset: 0x08 */
    volatile uint32_t CR1;   /*!< UART Control register 1,                Address offset: 0x0C */
    volatile uint32_t CR2;   /*!< UART Control register 2,                Address offset: 0x10 */
    volatile uint32_t CR3;   /*!< UART Control register 3,                Address offset: 0x14 */
    volatile uint32_t GTPR;  /*!< UART Guard time and prescaler register, Address offset: 0x18 */
} UART_TypeDef;

UART_TypeDef *UART4 = (UART_TypeDef *)_UART4; // BASE ADDRESSS 


void uart_init(uint32_t baud_rate);


/*
enable the clock cycle 
usart is in bus 2 
uart 4 and 5 are in bus 1 
#define _RCC_BASE        ((uint32_t)(0x40023800))
clock bus :-  #define _RCC_AHB1ENR     (*(volatile uint32_t *)(_RCC_BASE + 0x30)) // AHB1 Peripheral Clock Enable Register
0x4000 4C00 - 0x4000 4FFF UA
pa0 , pa1 and pa15 ( rts) 

// clock signal base 19 - set bit 
// clock signal base 0 - set bit 
// set 0 , 1 
clear the bit 


#define _RCC_BASE        ((uint32_t)(0x40023800))
#define _GPIOA_BASE      ((uint32_t)(0x40020000)) // PS5 MEANS 10:11
#define _UART4 ((uint32_t)(0x0x40004C00 ))

#define _GPIOA_MODER     (*(volatile uint32_t *)(_GPIOA_BASE + 0x00))
#define _RCC_AHB1ENR     (*(volatile uint32_t *)(_RCC_BASE + 0x30)) // AHB1 Peripheral Clock Enable Register
#define _RCC_ABH1RSTSR     (*(volatile uint32_t *)(_RCC_BASE + 0x10)) // AHB1 Peripheral Reset Register
#define _RCC_AHB1LPENR     (*(volatile uint32_t *)(_RCC_BASE + 0x50)) // AHB1 Peripheral Clock Enable in Low Power Mode Register
#define _GPIOA_ODR (*(volatile uint32_t *)(_GPIOA_BASE + 0x14))
#define _GPIOA_BSRR (*(volatile uint32_t *)(_GPIOA_BASE + 0x18))
#define _GPIOA_AFRL_0 ( * ( volatile uint32_t *) (_GPIOA_BASE +0x20 )) // 0000 0000 
#define _GPIOA_AFRL_1 ( * ( volatile uint32_t *) (_GPIOA_BASE +0x24 )) // 0000 0000 
#define _UART4_BRR  ( * ( volatile uint32_t *) (_UART4 +0x08 )) // 0000 0000 
if baud rate is 9600 then clock mhz / 9600 that is the baud eate set 
PIN 0 
GPIOA_MODER &= ~(11 << (0 * 2) );
GPIOA_MODER |= (10 << (0 * 2));

PIN 1 
GPIOA_MODER &= ~(11 << (1 * 2) );
GPIOA_MODER |= (10 << (1 * 2);

GPIOx_AFRL  PIN 0 WRITE 8 AND PIN 1 WRITE 8 

_GPIOA_AFRL_0 |= (1000 << 0);
_GPIOA_AFRL_0 |= (1000 << 4);
setting baud rate 
_UART4_BRR = ( 1 / 9600);
defining the data bit size ( 8 bita of data and 1 as parity) total 9 bits of data 
USART_CR1 |= ( 1 << 12);

12 and 13 bit is set to zero 
USART_CR2 &= ~(10 << 12);
#define te 3
#define re 2 
#define ue 13 
_UART4 |= ( 1 << 3) | (1 << 2) | ( 1 << 13);


Set TE (Bit 3): Set the Transmitter Enable bit to 1. This causes the UART to send an idle frame as its first transmission
.
Set RE (Bit 2): Set the Receiver Enable bit to 1. This activates the receiver to begin searching for a start bit on the RX line
.
Set UE (Bit 13): Finally, set the USART Enable bit to 1. This enables the entire peripheral and its internal prescalers
.
 while(!(UART4->SR & (1 << 7))); sending the data 

 receiving the data :- 
 for reading the data 
 while(!(UART4->SR & (1 << 5)));
*/

#endif /* UART_H */
