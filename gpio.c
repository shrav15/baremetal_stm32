#include "gpio.h"
#include <stdint.h>

/* GPIO device structure */
typedef struct {
    uint32_t port;
    int pin;
} GPIO_Device;

/* Enable clock for GPIO port */
void gpio_enable_clock(uint32_t port) {
    volatile uint32_t* rcc_ahb1enr = (uint32_t*)RCC_AHB1ENR;
    
    if (port == GPIOA_BASE) {
        *rcc_ahb1enr |= (1 << 0);  /* Enable GPIOA clock */
    } else if (port == GPIOB_BASE) {
        *rcc_ahb1enr |= (1 << 1);  /* Enable GPIOB clock */
    } else if (port == GPIOC_BASE) {
        *rcc_ahb1enr |= (1 << 2);  /* Enable GPIOC clock */
    } else if (port == GPIOD_BASE) {
        *rcc_ahb1enr |= (1 << 3);  /* Enable GPIOD clock */
    } else if (port == GPIOE_BASE) {
        *rcc_ahb1enr |= (1 << 4);  /* Enable GPIOE clock */
    } else if (port == GPIOF_BASE) {
        *rcc_ahb1enr |= (1 << 5);  /* Enable GPIOF clock */
    } else if (port == GPIOG_BASE) {
        *rcc_ahb1enr |= (1 << 6);  /* Enable GPIOG clock */
    } else if (port == GPIOH_BASE) {
        *rcc_ahb1enr |= (1 << 7);  /* Enable GPIOH clock */
    }
}

/* Set GPIO pin mode */
void gpio_set_pin_mode(uint32_t port, int pin, uint32_t mode) {
    volatile uint32_t* moder = (uint32_t*)(port + GPIO_MODER);
    
    /* Clear the mode bits for the pin */
    *moder &= ~(0x3UL << (pin * 2));
    
    /* Set the mode bits */
    *moder |= (mode << (pin * 2));
}

/* Set GPIO pin speed */
void gpio_set_pin_speed(uint32_t port, int pin, uint32_t speed) {
    volatile uint32_t* ospeedr = (uint32_t*)(port + GPIO_OSPEEDR);
    
    /* Clear the speed bits for the pin */
    *ospeedr &= ~(0x3UL << (pin * 2));
    
    /* Set the speed bits */
    *ospeedr |= (speed << (pin * 2));
}

/* Set GPIO pin pull-up/pull-down */
void gpio_set_pin_pull(uint32_t port, int pin, uint32_t pull) {
    volatile uint32_t* pupdr = (uint32_t*)(port + GPIO_PUPDR);
    
    /* Clear the pull bits for the pin */
    *pupdr &= ~(0x3UL << (pin * 2));
    
    /* Set the pull bits */
    *pupdr |= (pull << (pin * 2));
}

/* Set GPIO pin output type (push-pull or open-drain) */
void gpio_set_pin_otype(uint32_t port, int pin, uint32_t otype) {
    volatile uint32_t* otyper = (uint32_t*)(port + GPIO_OTYPER);
    
    if (otype) {
        *otyper |= (1UL << pin);   /* Open-drain */
    } else {
        *otyper &= ~(1UL << pin);  /* Push-pull */
    }
}

/* Read GPIO pin input */
uint32_t gpio_read_pin(uint32_t port, int pin) {
    volatile uint32_t* idr = (uint32_t*)(port + GPIO_IDR);
    return (*idr >> pin) & 1;
}

/* Write GPIO pin output */
void gpio_write_pin(uint32_t port, int pin, uint32_t value) {
    volatile uint32_t* odr = (uint32_t*)(port + GPIO_ODR);
    
    if (value) {
        *odr |= (1UL << pin);
    } else {
        *odr &= ~(1UL << pin);
    }
}

/* Toggle GPIO pin */
void gpio_toggle_pin(uint32_t port, int pin) {
    volatile uint32_t* odr = (uint32_t*)(port + GPIO_ODR);
    *odr ^= (1UL << pin);
}

/* Set GPIO pin using BSRR register (atomic) */
void gpio_set_pin(uint32_t port, int pin) {
    volatile uint32_t* bsrr = (uint32_t*)(port + GPIO_BSRR);
    *bsrr = (1UL << pin);  /* Set the pin */
}

/* Clear GPIO pin using BSRR register (atomic) */
void gpio_clear_pin(uint32_t port, int pin) {
    volatile uint32_t* bsrr = (uint32_t*)(port + GPIO_BSRR);
    *bsrr = (1UL << (pin + 16));  /* Clear the pin */
}

/* Lock GPIO pin configuration */
void gpio_lock_pin(uint32_t port, int pin) {
    volatile uint32_t* lckr = (uint32_t*)(port + GPIO_LCKR);
    
    /* Set the lock bit */
    *lckr = (1UL << pin) | (1UL << 16);
    *lckr = (1UL << pin);
    *lckr = (1UL << pin) | (1UL << 16);
    
    /* Read to confirm lock */
    (void)(*lckr);
}

/* Set alternate function for GPIO pin (low register AFRL) */
void gpio_set_alternate_function_low(uint32_t port, int pin, uint32_t af) {
    volatile uint32_t* afrl = (uint32_t*)(port + GPIO_AFRL);
    
    /* Clear the AF bits for the pin */
    *afrl &= ~(0xFUL << (pin * 4));
    
    /* Set the AF bits */
    *afrl |= (af << (pin * 4));
}

/* Set alternate function for GPIO pin (high register AFRH) */
void gpio_set_alternate_function_high(uint32_t port, int pin, uint32_t af) {
    volatile uint32_t* afrh = (uint32_t*)(port + GPIO_AFRH);
    
    /* Adjust pin number for AFRH (pins 8-15) */
    int pin_offset = pin - 8;
    
    /* Clear the AF bits for the pin */
    *afrh &= ~(0xFUL << (pin_offset * 4));
    
    /* Set the AF bits */
    *afrh |= (af << (pin_offset * 4));
}




