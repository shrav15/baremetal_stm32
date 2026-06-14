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
#include "mbed.h"
#include <stdint.h>

// ============================================================================
// HARDWARE REGISTER DEFINITIONS (STM32F446RE Bare-Metal)
// ============================================================================

// Base address locations
#define _RCC_BASE        ((uint32_t)0x40023800)
#define _GPIOA_BASE      ((uint32_t)0x40020000)
#define _USART2_BASE     ((uint32_t)0x40004400) // USART2 Base Address

// Register mapping definitions
#define _RCC_AHB1ENR     (*(volatile uint32_t *)(_RCC_BASE + 0x30)) 
#define _RCC_APB1ENR     (*(volatile uint32_t *)(_RCC_BASE + 0x40)) 

#define _GPIOA_MODER     (*(volatile uint32_t *)(_GPIOA_BASE + 0x00))
#define _GPIOA_AFRL      (*(volatile uint32_t *)(_GPIOA_BASE + 0x20)) 

// UART Register Layout Structure
typedef struct  {
    volatile uint32_t SR;    /*!< UART Status register */
    volatile uint32_t DR;    /*!< UART Data register */
    volatile uint32_t BRR;   /*!< UART Baud rate register */
    volatile uint32_t CR1;   /*!< UART Control register 1 */
    volatile uint32_t CR2;   /*!< UART Control register 2 */
    volatile uint32_t CR3;   /*!< UART Control register 3 */
    volatile uint32_t GTPR;  /*!< UART Guard time and prescaler register */
} _USART_TypeDef;

// Instance mapping macro
#define USART2_REG ((_USART_TypeDef *)_USART2_BASE)

// ============================================================================
// BARE-METAL USART2 FUNCTIONS
// ============================================================================

void custom_usart2_init(uint32_t baud_rate)
{
    // 1. Enable peripheral system clocks
    _RCC_AHB1ENR |= (1 << 0);   // Enable clock for GPIOA
    _RCC_APB1ENR |= (1 << 17);  // Enable USART2 clock on APB1 bus (Bit 17)

    // 2. Configure pins PA2 (TX) and PA3 (RX) to Alternate Function mode
    _GPIOA_MODER &= ~((0x3 << (2 * 2)) | (0x3 << (3 * 2))); // Clear mode bits for PA2 and PA3
    _GPIOA_MODER |=  ((0x2 << (2 * 2)) | (0x2 << (3 * 2))); // Assign to Alternate Function value 0x2

    // 3. Connect PA2 and PA3 pins to routing line AF7 (USART2 uses AF7)
    _GPIOA_AFRL &= ~((0xF << 8) | (0xF << 12)); // Clear existing layout settings for pins 2 and 3
    _GPIOA_AFRL |=  ((7 << 8)   | (7 << 12));   // Set AF7 (binary 0111) for both pins

    // 4. Configure frame layout before system enablement
    USART2_REG->CR1 &= ~(1 << 12);   // Clear M bit to force standard 8 Data Bits mode
    USART2_REG->CR2 &= ~((0x3) << 12); // Explicitly choose 1 Stop bit configuration

    // 5. Calculate and apply speed configurations (Dynamic Mbed clock adjustment)
    // Mbed steps up SystemCoreClock to 180 MHz. APB1 bus runs at (SystemCoreClock / 4) = 45 MHz.
    uint32_t pclk1 = SystemCoreClock / 4; 
    uint32_t usartdiv = (pclk1 + (baud_rate / 2)) / baud_rate; // Integer math with rounding
    USART2_REG->BRR = usartdiv;

    // 6. Spin up active system operations
    USART2_REG->CR1 |= (1 << 3) | (1 << 2) | (1 << 13); // Turn on TE, RE, and UE registers
}

void custom_usart2_send(uint8_t data)
{
    // Wait until Transmit Data Register is Empty (TXE bit 7)
    while (!(USART2_REG->SR & (1 << 7)));
    
    // Pass data directly to transmit register
    USART2_REG->DR = data;
}

void custom_usart2_send_string(const char *str)
{
    while (*str) {
        custom_usart2_send((uint8_t)(*str));
        str++;
    }
}

uint8_t custom_usart2_receive(void)
{
    // Wait until Read Data Register is Not Empty (RXNE bit 5)
    while (!(USART2_REG->SR & (1 << 5)));

    // Return the read register value
    return (uint8_t)(USART2_REG->DR & 0xFF);
}

// ============================================================================
// APPLICATION ENTRY POINT
// ============================================================================

int main()
{
    // Initialize our register-level USART2 at 115200 Baud Rate
    custom_usart2_init(115200);

    // Send a startup validation message
    custom_usart2_send_string("\r\n--- STM32F446RE USART2 Onboard USB Test Complete ---\r\n");
    custom_usart2_send_string("Type any characters in Mbed Studio Serial Monitor to echo them back:\r\n");

    while (1) {
        // Blocks until a character is typed/received via the USB terminal
        uint8_t rx_data = custom_usart2_receive();

        // Echo the exact character back instantly
        custom_usart2_send(rx_data);
    }
}
