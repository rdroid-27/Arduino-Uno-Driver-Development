#include "REES52_UNO_gpio.h"

// If PORTxn is written logic one when the pin is configured as an input pin, the pull-up resistor is activated. To switch the
// pull-up resistor off, PORTxn has to be written logic zero or the pin has to be configured as an output pin.

// Define Mode of Pins and Port i.e. Input or Output.
void GPIO_InputPort(GPIO_RegDef_t *pGPIOx)
{
    pGPIOx->DDRx &= 0x00;
}
void GPIO_InputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber)
{
    pGPIOx->DDRx &= ~(1 << pinNumber);
}

void GPIO_OutputPort(GPIO_RegDef_t *pGPIOx)
{
    pGPIOx->DDRx |= 0xFF;
}
void GPIO_OutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber)
{
    pGPIOx->DDRx |= (1 << pinNumber);
}

// Read/Write value function for Pins and Port.
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber)
{
    return (uint8_t)((pGPIOx->PINx >> pinNumber) & 0x01);
}

uint8_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    return (uint8_t)(pGPIOx->PINx);
}

// Activate/Deactivate Pull-up Resistor when Pin is in Input mode.
void Activate_Pin_Pullup(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber)
{
    if (!((pGPIOx->DDRx >> pinNumber) & 0x01))
        pGPIOx->PORTx |= (1 << pinNumber);
}

void Deactivate_Pin_Pullup(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber)
{
    if (!((pGPIOx->DDRx >> pinNumber) & 0x01))
        pGPIOx->PORTx &= ~(1 << pinNumber);
}

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber, uint8_t value)
{
    if (value == SET)
        pGPIOx->PORTx |= (1 << pinNumber);
    else
        pGPIOx->PORTx &= ~(1 << pinNumber);
}

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint8_t value)
{
    pGPIOx->PORTx = value;
}

// Toggle the values of a GPIO Pin or Port irrespective of value of DDRnx/DDRx.
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber)
{
    pGPIOx->PINx = (1 << pinNumber);
}
void GPIO_ToggleOutputPort(GPIO_RegDef_t *pGPIOx)
{
    pGPIOx->PINx = 0xFF;
}
