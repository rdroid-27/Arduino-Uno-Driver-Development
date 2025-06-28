/*  AIM:
    Generate an Interrupt when a Push Button is pressed.

    EXPLANATION:
    1 leg of button is connected to input pin PD2 and the other with ground. The active Pull-up configuration of the pin will keep the pin high.
    Whenever the Button is pressed, the input pin will be pulled to ground (low).
    Check the input pin, and when found low, trigger the interrupt (INT0 mapped with PD2) and inside the ISR turn on the LED.
*/

#include "REES52_UNO_gpio.h"

// INT0 ISR
void __vector_1(void) __attribute__((signal, used));
void __vector_1(void)
{

    GPIO_WriteToOutputPin(PORTB, PIN5, SET);
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

    // Configure Interrupt Registers
    SREG |= (1 << 7);   // I (Global Interrupt Enable)
    EICRA |= (1 << 1);  // ISC01 = 1
    EICRA &= ~(1 << 0); // ISC00 = 0
    EIMSK |= (1 << 0);  // INT0 Enabled

    while (1)
        ;

    return 0;
}