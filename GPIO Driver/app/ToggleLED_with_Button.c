/*  AIM: Toggle LED everytime the Push Button is pressed.

    EXPLANATION:
    1 leg of button is connected to pin PD2 and the other with ground. The active Pull-up configuration of the pin will keep the pin high.
    Whenever the Button is pressed, the pin will be pulled to ground (low).
    Check the pin, and when found low, toggle the internal LED connected to PB5.
*/

#include "REES52_UNO_gpio.h"

void delay_20ms(void)
{
    for (volatile long i = 0; i < 10000; ++i)
        ;
}

// Check for Key Debouncing to remove any false inputs. If input is valid, return 1 else return 0.
int check_DeBounce(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber)
{
    if (!GPIO_ReadFromInputPin(pGPIOx, pinNumber))
    {
        delay_20ms();
        if (!GPIO_ReadFromInputPin(pGPIOx, pinNumber))
            return 1;
    }
    else if (GPIO_ReadFromInputPin(pGPIOx, pinNumber))
    {
        delay_20ms();
        if (GPIO_ReadFromInputPin(pGPIOx, pinNumber))
            return 0;
    }
    return -1;
}

int main()
{
    // Set Internal LED pin i.e. PB5 to output mode.
    GPIO_OutputPin(PORTB, PIN5);
    // Set Pin PD2 to input mode.
    GPIO_InputPin(PORTD, PIN2);
    // Activate the Internal Pull-Up Resistor for PD2.
    Activate_Pin_Pullup(PORTD, PIN2);
    // Initially turn Off the Internal LED.
    GPIO_WriteToOutputPin(PORTB, PIN5, RESET);
    // Variable to store Previous State of the Push Button.
    int PrevState = 0;

    while (1)
    {
        if (check_DeBounce(PORTD, PIN2) && !PrevState)
        {
            GPIO_ToggleOutputPin(PORTB, PIN5);
            PrevState = !(PrevState);
        }
        else if (!check_DeBounce(PORTD, PIN2) && PrevState)
        {
            PrevState = !(PrevState);
        }
    }

    return 0;
}