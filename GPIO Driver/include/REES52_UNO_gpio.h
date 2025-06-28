#include "atmega328p.h"

// Pin Number
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

#define SET 1
#define RESET 0

// API Function Prototypes
void GPIO_InputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_InputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber);

void GPIO_OutputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_OutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber);

// Read/Write value function for Pins and Port.
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber);
uint8_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);

// Activate/Deactivate Pull-up Resistor when Pin is in Input mode.
void Activate_Pin_Pullup(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber);
void Deactivate_Pin_Pullup(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber);

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber, uint8_t value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint8_t value);

// Toggle the values of a GPIO Pin or Port irrespective of value of DDRnx/DDRx.
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber);
void GPIO_ToggleOutputPort(GPIO_RegDef_t *pGPIOx);
