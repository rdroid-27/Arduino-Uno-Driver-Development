#ifndef REES52_UNO_SPI_H
#define REES52_UNO_SPI_H

#include "atmega328p.h"

// SPI Macros
#define SPI_MODE_MASTER             1
#define SPI_MODE_SLAVE              0

#define SPI_SCLK_SPEED_DIV4         0
#define SPI_SCLK_SPEED_DIV16        1
#define SPI_SCLK_SPEED_DIV64        2
#define SPI_SCLK_SPEED_DIV128       3
#define SPI_SCLK_SPEED_DIV2         4
#define SPI_SCLK_SPEED_DIV8         5
#define SPI_SCLK_SPEED_DIV32        6
#define SPI_SCLK_SPEED_DIV64_2X     7

#define SPI_CPOL_HIGH               1
#define SPI_CPOL_LOW                0

#define SPI_CPHA_HIGH               1
#define SPI_CPHA_LOW                0

#define SPI_DATA_MSB                0
#define SPI_DATA_LSB                1

// SPI Configuration Structure
typedef struct
{
    volatile uint8_t SPI_DeviceMode; // Device mode: Master (1) or Slave (0)
    volatile uint8_t SPI_SclkSpeed;  // Serial clock speed (baud rate control)
    volatile uint8_t SPI_CPOL;       // Clock polarity: Low (0) or High (1) when idle
    volatile uint8_t SPI_CPHA;       // Clock phase: Data sampling edge (1st or 2nd)
    volatile uint8_t SPI_DORD;       // Data Order: LSB or MSB of the data word is send first
} SPI_Config_t;

typedef struct
{
    SPI_RegDef_t *pSPI;
    SPI_Config_t SPIConfig;
} SPI_Handle_t;

/**************************************************************
 *                     SPI Driver API Prototypes             *
 **************************************************************/
// Enable or disable SPI
void SPI_PeripheralControl(SPI_RegDef_t *pSPI, uint8_t EnorDi);

// Initializes the SPI peripheral with the specified configuration
void SPI_Init(SPI_Handle_t *pSPIHandle);

// Sends data using the SPI peripheral in blocking mode
void SPI_SendData(SPI_RegDef_t *pSPI, uint8_t *pTxBuffer, uint32_t len);

// Receives data using the SPI peripheral in blocking mode
void SPI_RecieveData(SPI_RegDef_t *pSPI, uint8_t *pRxBuffer, uint32_t len);

void SPI_TransmitReceive(SPI_RegDef_t *pSPI, uint8_t *pTxBuffer, uint8_t *pRxBuffer, uint32_t len);

// Enables or disables the interrupt for the given SPI IRQ number
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t ENorDI);

// Sets the priority of the given SPI interrupt number
void SPI_IRQPriorityConfig(uint32_t IRQPriority, uint8_t IRQNumber);

// Handles the SPI interrupt and clears the flags
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);

#endif // REES52_UNO_SPI_H
