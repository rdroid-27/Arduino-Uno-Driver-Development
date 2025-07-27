#include "REES52_UNO_spi.h"

/*
PB5     SCK
PB4     MISO
PB3     MOSI
PB2     SS
*/

// Enable or disable SPI
void SPI_PeripheralControl(SPI_RegDef_t *pSPI, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
        pSPI->SPCR |= (1 << 6);
    else
    {
        pSPI->SPCR = 0x00; // Disable SPI
        pSPI->SPSR = 0x00;
    }
}

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    // First Reset All SPI Registers;
    pSPIHandle->pSPI->SPCR = 0x00;
    pSPIHandle->pSPI->SPSR = 0x00;

    // pSPIHandle->pSPI->SPCR |= (1 << 7);
    // PRR &= ~(1 << 2);

    uint8_t tempSPCR = 0;
    uint8_t tempSPSR = 0;

    // 1. Configure the device mode
    tempSPCR |= (pSPIHandle->SPIConfig.SPI_DeviceMode << 4);

    // 2. Configure the SCK speed
    if (pSPIHandle->SPIConfig.SPI_SclkSpeed > SPI_SCLK_SPEED_DIV128)
        tempSPSR |= (1 << 0);
    else
        tempSPSR &= ~(1 << 0);

    tempSPCR |= ((pSPIHandle->SPIConfig.SPI_SclkSpeed % 4) << 0);

    // 3. Configure the CPOL
    tempSPCR |= (pSPIHandle->SPIConfig.SPI_CPOL << 3);

    // 4. Configure the CPHA
    tempSPCR |= (pSPIHandle->SPIConfig.SPI_CPHA << 2);

    // 5. Set data order
    tempSPCR |= (pSPIHandle->SPIConfig.SPI_DORD << 5); // DORD is bit 5

    // // // 1. Enable the SPI, SPI interrupt and disable the power reduction
    // tempSPCR |= (1 << 7);
    // SREG |= (1 << 7);

    // Write to registers
    pSPIHandle->pSPI->SPCR = tempSPCR;
    pSPIHandle->pSPI->SPSR = tempSPSR;
}

void SPI_SendData(SPI_RegDef_t *pSPI, uint8_t *pTxBuffer, uint32_t len)
{
    // All the bits are sent
    while (len > 0)
    {
        pSPI->SPDR = *(pTxBuffer);

        // Wait for Tx buffer to be empty
        while (!(pSPI->SPSR & (1 << 7)))
            ;

        len--;
        pTxBuffer++;
    }
    return;
}

void SPI_RecieveData(SPI_RegDef_t *pSPI, uint8_t *pRxBuffer, uint32_t len)
{
    // All the bits are sent
    while (len > 0)
    {
        // Wait for Rx buffer to be empty
        while (pSPI->SPSR & (1 << 7))
            ;

        *(pRxBuffer) = pSPI->SPDR;
        len--;
        pRxBuffer++;
    }
    return;
}

void SPI_TransmitReceive(SPI_RegDef_t *pSPI, uint8_t *pTxBuffer, uint8_t *pRxBuffer, uint32_t len)
{
    while (len > 0)
    {
        // Write data to SPDR
        pSPI->SPDR = *pTxBuffer;
        // Wait until transmit buffer is empty
        while (!(pSPI->SPSR & (1 << 7)))
            ;

        // Wait for reception to complete
        while (!(pSPI->SPSR & (1 << 7)))
            ;
        // Read data from SPDR
        *pRxBuffer = pSPI->SPDR;

        pTxBuffer++;
        pRxBuffer++;
        len--;
    }
}
