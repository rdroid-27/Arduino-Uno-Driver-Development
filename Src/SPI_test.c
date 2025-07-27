#include <string.h>
#include "atmega328p.h"

void delay(void)
{
    for (volatile long i = 0; i < 500000; ++i)
        ;
}

int main(void)
{
    // --- SPI Setup ---
    /*
    PB5     SCK
    PB4     MISO
    PB3     MOSI
    PB2     SS
    */
    GPIO_OutputPin(PORTB, PIN3);
    GPIO_OutputPin(PORTB, PIN5);
    GPIO_OutputPin(PORTB, PIN2);
    GPIO_InputPin(PORTB, PIN4);

    // Enable SPI in Master mode, Fosc/16, CPOL/CPHA low
    SPI_Handle_t SPI_Handle;

    SPI_Handle.pSPI = SPI;

    SPI_Handle.SPIConfig.SPI_DeviceMode = SPI_MODE_MASTER;
    SPI_Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV16;
    SPI_Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
    SPI_Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;

    SPI_Init(&SPI_Handle);
    SPI_PeripheralControl(SPI, ENABLE); // Very important!

    // <---------------------------------------------------->
    //              Transmit dummy data
    // const char data[] = "Hello World";
    // for (uint8_t i = 0; i < strlen(data); i++)
    // {
    //     SPI_SendData(SPI, (uint8_t *)(&data[i]), 1);
    // }

    // // --- Disable SPI and Reclaim PB5 as GPIO ---
    // SPI_PeripheralControl(SPI, DISABLE);

    // // Reconfigure PB5 as GPIO Output
    // GPIO_OutputPin(PORTB, PIN5);
    // GPIO_WriteToOutputPin(PORTB, PIN5, RESET);

    // // --- Blink LED on PB5 ---
    // while (1)
    // {
    //     GPIO_ToggleOutputPin(PORTB, PIN5); // Toggle
    //     delay();
    // }
    // <----------------------------------------------------->

    // <----------------------------------------------------->
    //            Send and Recieve data at same time
    const char data[] = "Hello World";
    char received[strlen(data) + 1]; // +1 for null terminator

    for (uint8_t i = 0; i < strlen(data); i++)
    {
        SPI_TransmitReceive(SPI, (uint8_t *)(&data[i]), (uint8_t *)(&received[i]), 1);
    }

    received[strlen(data)] = '\0'; // Null-terminate
    SPI_PeripheralControl(SPI, DISABLE);

    GPIO_OutputPin(PORTB, PIN5);
    GPIO_WriteToOutputPin(PORTB, PIN5, RESET);

    if (strcmp(data, received) == 0)
    {
        // LED Blink if matched
        while (1)
        {
            GPIO_ToggleOutputPin(PORTB, PIN5);
            delay();
        }
    }
    else
    {
        // Solid ON = Mismatch
        while (1)
        {
            GPIO_WriteToOutputPin(PORTB, PIN5, SET);
        }
    }
    // <----------------------------------------------------->

    return 0;
}
