#ifndef GPIO_H
#define GPIO_H

/**
 * @file    gpio.h
 * @brief   GPIO peripheral definitions and function prototypes for STM32F446
 * @author  STM32F4 Community
 * @date    June 2024
 * 
 * This header file provides GPIO definitions, register offsets, and function
 * prototypes for configuring and controlling GPIO pins on the STM32F446.
 */

#include <stdint.h>

/* Import from Startup.c */
#define FLASH_BASE      0x08000000UL
#define SRAM1_BASE      0x20000000UL
#define SRAM2_BASE      0x2001C000UL
#define PERIPH_BASE     0x40000000UL
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)
#define RCC_BASE        (AHB1PERIPH_BASE + 0x3800UL)

/* GPIO Base Addresses */
#define GPIOA_BASE      (AHB1PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE      (AHB1PERIPH_BASE + 0x0400UL)
#define GPIOC_BASE      (AHB1PERIPH_BASE + 0x0800UL)
#define GPIOD_BASE      (AHB1PERIPH_BASE + 0x0C00UL)
#define GPIOE_BASE      (AHB1PERIPH_BASE + 0x1000UL)
#define GPIOF_BASE      (AHB1PERIPH_BASE + 0x1400UL)
#define GPIOG_BASE      (AHB1PERIPH_BASE + 0x1800UL)
#define GPIOH_BASE      (AHB1PERIPH_BASE + 0x1C00UL)

/* RCC Registers */
#define RCC_AHB1ENR     (RCC_BASE + 0x30UL)
#define RCC_AHB1RSTR    (RCC_BASE + 0x10UL)

/* GPIO Register Offsets */
#define GPIO_MODER      0x00UL
#define GPIO_OTYPER     0x04UL
#define GPIO_OSPEEDR    0x08UL
#define GPIO_PUPDR      0x0CUL
#define GPIO_IDR        0x10UL
#define GPIO_ODR        0x14UL
#define GPIO_BSRR       0x18UL
#define GPIO_LCKR       0x1CUL
#define GPIO_AFRL       0x20UL
#define GPIO_AFRH       0x24UL

/* GPIO Mode Definitions */
#define GPIO_MODE_INPUT     0x0UL
#define GPIO_MODE_OUTPUT    0x1UL
#define GPIO_MODE_AF        0x2UL
#define GPIO_MODE_ANALOG    0x3UL

/* GPIO Output Speed Definitions */
#define GPIO_SPEED_LOW      0x0UL
#define GPIO_SPEED_MEDIUM   0x1UL
#define GPIO_SPEED_HIGH     0x2UL
#define GPIO_SPEED_VERY_HIGH 0x3UL

/* GPIO Pull-up/Pull-down Definitions */
#define GPIO_PULL_NONE      0x0UL
#define GPIO_PULL_UP        0x1UL
#define GPIO_PULL_DOWN      0x2UL

/* GPIO Output Type Definitions */
#define GPIO_OTYPE_PP       0x0UL  /* Push-pull */
#define GPIO_OTYPE_OD       0x1UL  /* Open-drain */

/* Alternate Function Definitions */
#define GPIO_AF0            0x0UL
#define GPIO_AF1            0x1UL
#define GPIO_AF2            0x2UL
#define GPIO_AF3            0x3UL
#define GPIO_AF4            0x4UL
#define GPIO_AF5            0x5UL
#define GPIO_AF6            0x6UL
#define GPIO_AF7            0x7UL
#define GPIO_AF8            0x8UL
#define GPIO_AF9            0x9UL
#define GPIO_AF10           0xAUL
#define GPIO_AF11           0xBUL
#define GPIO_AF12           0xCUL
#define GPIO_AF13           0xDUL
#define GPIO_AF14           0xEUL
#define GPIO_AF15           0xFUL

/* Function Prototypes */

/**
 * @brief Enable clock for GPIO port
 * @param port GPIO port base address
 */
void gpio_enable_clock(uint32_t port);

/**
 * @brief Set GPIO pin mode (input/output/alternate function/analog)
 * @param port GPIO port base address
 * @param pin Pin number (0-15)
 * @param mode GPIO mode
 */
void gpio_set_pin_mode(uint32_t port, int pin, uint32_t mode);

/**
 * @brief Set GPIO pin output speed
 * @param port GPIO port base address
 * @param pin Pin number (0-15)
 * @param speed Output speed
 */
void gpio_set_pin_speed(uint32_t port, int pin, uint32_t speed);

/**
 * @brief Set GPIO pin pull-up/pull-down
 * @param port GPIO port base address
 * @param pin Pin number (0-15)
 * @param pull Pull configuration
 */
void gpio_set_pin_pull(uint32_t port, int pin, uint32_t pull);

/**
 * @brief Set GPIO pin output type
 * @param port GPIO port base address
 * @param pin Pin number (0-15)
 * @param otype Output type (push-pull or open-drain)
 */
void gpio_set_pin_otype(uint32_t port, int pin, uint32_t otype);

/**
 * @brief Read GPIO pin input value
 * @param port GPIO port base address
 * @param pin Pin number (0-15)
 * @return Pin state (0 or 1)
 */
uint32_t gpio_read_pin(uint32_t port, int pin);

/**
 * @brief Write GPIO pin output value
 * @param port GPIO port base address
 * @param pin Pin number (0-15)
 * @param value Output value (0 or 1)
 */
void gpio_write_pin(uint32_t port, int pin, uint32_t value);

/**
 * @brief Toggle GPIO pin state
 * @param port GPIO port base address
 * @param pin Pin number (0-15)
 */
void gpio_toggle_pin(uint32_t port, int pin);

/**
 * @brief Set GPIO pin using BSRR (atomic)
 * @param port GPIO port base address
 * @param pin Pin number (0-15)
 */
void gpio_set_pin(uint32_t port, int pin);

/**
 * @brief Clear GPIO pin using BSRR (atomic)
 * @param port GPIO port base address
 * @param pin Pin number (0-15)
 */
void gpio_clear_pin(uint32_t port, int pin);

/**
 * @brief Lock GPIO pin configuration
 * @param port GPIO port base address
 * @param pin Pin number (0-15)
 */
void gpio_lock_pin(uint32_t port, int pin);

/**
 * @brief Set alternate function for GPIO pin (AFRL for pins 0-7)
 * @param port GPIO port base address
 * @param pin Pin number (0-7)
 * @param af Alternate function number
 */
void gpio_set_alternate_function_low(uint32_t port, int pin, uint32_t af);

/**
 * @brief Set alternate function for GPIO pin (AFRH for pins 8-15)
 * @param port GPIO port base address
 * @param pin Pin number (8-15)
 * @param af Alternate function number
 */
void gpio_set_alternate_function_high(uint32_t port, int pin, uint32_t af);

#endif /* GPIO_H */