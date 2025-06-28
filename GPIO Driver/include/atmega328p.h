#include <stdint.h>

#define MCUCR_BaseAddr 0x55
#define GPIOB_BaseAddr 0x23
#define GPIOC_BaseAddr 0x26
#define GPIOD_BaseAddr 0x29

typedef struct
{
    volatile uint8_t PINx;
    volatile uint8_t DDRx;
    volatile uint8_t PORTx;
} GPIO_RegDef_t;

#define PORTB ((GPIO_RegDef_t *)GPIOB_BaseAddr)
#define PORTC ((GPIO_RegDef_t *)GPIOC_BaseAddr)
#define PORTD ((GPIO_RegDef_t *)GPIOD_BaseAddr)
