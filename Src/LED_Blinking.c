/*  AIM: Blink the Internal LED (LED3) with a certain delay.

    EXPLANATION:
    Internal LED (LED5) is connected to Pin 5 of PortB.
    We have two API's available
        1. Toggle the pin
        2. To write output to a pin.
    With a certain amount of delay either we can call the Toggle API which will handle the bink automatically, or we can write SET and RESET alternatively to the pin with a certain amount of delay.
*/

#include "REES52_UNO_gpio.h"

void delay(void)
{
    for (volatile long i = 0; i < 500000; ++i)
        ;
}

int main()
{
    // Set Internal LED pin i.e. PB5 to output mode.
    GPIO_OutputPin(PORTB, PIN5);

    while (1)
    {
        // 1. Toggle the Pin Output.
        GPIO_ToggleOutputPin(PORTB, PIN5);
        delay();

        // 2. Write 1 and 0 alternatively to the Pin Output.
        GPIO_WriteToOutputPin(PORTB, PIN5, SET);
        delay();
        GPIO_WriteToOutputPin(PORTB, PIN5, RESET);
        delay();
    }

    return 0;
}