#include <stdint.h>

#define MCUCR_BaseAddr  0x55 // MCU Control Register
#define SREG_BaseAddr   0x5F // AVR Status Register
#define GPIOB_BaseAddr  0x23 // General Purpose I/O B
#define GPIOC_BaseAddr  0x26 // General Purpose I/O C
#define GPIOD_BaseAddr  0x29 // General Purpose I/O D
#define EICRA_BaseAddr  0x69 // External Interrupt Control Register A
#define EIMSK_BaseAddr  0x3D // External Interrupt Mask Register
#define EIFR_BaseAddr   0x3C // External Interrupt Flag Register
#define PCICR_BaseAddr  0x68 // Pin Change Interrupt Control Register
#define PCIFR_BaseAddr  0x3B // Pin Change Interrupt Flag Register
#define PCMSK2_BaseAddr 0x6D // Pin Change Mask Register 2
#define PCMSK1_BaseAddr 0x6C // Pin Change Mask Register 1
#define PCMSK0_BaseAddr 0x6B // Pin Change Mask Register 0

// General Registers Definition
#define MCUCR (*((uint8_t *)MCUCR_BaseAddr))
#define SREG  (*((uint8_t *)SREG_BaseAddr))

// GPIO Register Definition
typedef struct
{
    volatile uint8_t PINx;
    volatile uint8_t DDRx;
    volatile uint8_t PORTx;
} GPIO_RegDef_t;

#define PORTB ((GPIO_RegDef_t *)GPIOB_BaseAddr)
#define PORTC ((GPIO_RegDef_t *)GPIOC_BaseAddr)
#define PORTD ((GPIO_RegDef_t *)GPIOD_BaseAddr)


// Interrupts Registers Definitions
#define EICRA   (*(volatile uint8_t *)EICRA_BaseAddr)
#define EIMSK   (*(volatile uint8_t *)EIMSK_BaseAddr)
#define EIFR    (*(volatile uint8_t *)EIFR_BaseAddr)
#define PCICR   (*(volatile uint8_t *)PCICR_BaseAddr)
#define PCIFR   (*(volatile uint8_t *)PCIFR_BaseAddr)
#define PCMSK2  (*(volatile uint8_t *)PCMSK2_BaseAddr)
#define PCMSK1  (*(volatile uint8_t *)PCMSK1_BaseAddr)
#define PCMSK0  (*(volatile uint8_t *)PCMSK0_BaseAddr)

