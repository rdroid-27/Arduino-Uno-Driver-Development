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
        pSPI->SPCR &= ~(1 << 6);
}

// Initializes the SPI peripheral with the specified configuration
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    // 1. Enable the SPI, SPI interrupt and disable the power reduction
    pSPIHandle->pSPI->SPCR |= (1 << 6);
    pSPIHandle->pSPI->SPCR |= (1 << 7);
    PRR &= ~(1 << 2);

    // 2. Configure the device mode
    pSPIHandle->pSPI->SPCR &= ~(1 << 4);
    pSPIHandle->pSPI->SPCR |= (pSPIHandle->SPIConfig.SPI_DeviceMode << 4);

    // 3. Configure the SCK speed
    pSPIHandle->pSPI->SPCR &= ~(3 << 0);

    if (pSPIHandle->SPIConfig.SPI_SclkSpeed > SPI_SCLK_SPEED_DIV128)
        pSPIHandle->pSPI->SPSR |= (1 << 0);
    else
        pSPIHandle->pSPI->SPSR &= ~(1 << 0);

    pSPIHandle->pSPI->SPCR |= ((pSPIHandle->SPIConfig.SPI_SclkSpeed % 4) << 0);

    // 4. Configure the CPOL
    pSPIHandle->pSPI->SPCR &= ~(1 << 3);
    pSPIHandle->pSPI->SPCR |= (pSPIHandle->SPIConfig.SPI_CPOL << 3);

    // 5. Configure the CPHA
    pSPIHandle->pSPI->SPCR &= ~(1 << 2);
    pSPIHandle->pSPI->SPCR |= (pSPIHandle->SPIConfig.SPI_CPHA << 2);
}

void SPI_SendData(SPI_RegDef_t *pSPI, uint8_t *pTxBuffer, uint32_t len)
{
    // All the bits are sent
    while (len > 0)
    {
        // Wait for Tx buffer to be empty
        while (!(pSPI->SPSR & (1 << 7)))
            ;

        pSPI->SPDR = *(pTxBuffer);
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