/******************************************************************************
*
* Module: SPI
*
* File Name: spi.c
*
* Description: Source file for the AVR SPI driver
*
* Author: Abdallah El-Sakka
*
*******************************************************************************/

#include "spi.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../Utils/common_macros.h"
#include <avr/io.h>

/*******************************************************************************
*                                Function Prototypes                           *
*******************************************************************************/

/*
 * Description :
 * Initialize the SPI device as Master.
 */
void SPI_initMaster(void)
{
    GPIO_setupPinDirection(SS_PORT_ID, SS_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(MOSI_PORT_ID, MOSI_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(SCK_PORT_ID, SCK_PIN_ID, PIN_OUTPUT);

    GPIO_setupPinDirection(MISO_PORT_ID, MISO_PIN_ID, PIN_INPUT);

    /************************** SPCR Description **************************
     * SPIE          = 0 Disable SPI Interrupt
     * SPE           = 1 Enable SPI Driver
     * DORD          = 0 Transmit the MSB first
     * MSTR          = 1 Disable Master
     * CPOL          = 0 SCK is low when idle
     * CPHA          = 0 Sample Data with the raising edge
     * SPR1:0 SPI2X  = 00 0 Choose SPI clock = Fosc/4
     ***********************************************************************/
    SPCR = (1 << SPE) | (1 << MSTR);

    SPSR &= ~(1 << SPI2X);
}

/*
 * Description :
 * Initialize the SPI device as Slave.
 */
void SPI_initSlave(void)
{
    GPIO_setupPinDirection(SS_PORT_ID, SS_PIN_ID, PIN_INPUT);
    GPIO_setupPinDirection(MOSI_PORT_ID, MOSI_PIN_ID, PIN_INPUT);
    GPIO_setupPinDirection(SCK_PORT_ID, SCK_PIN_ID, PIN_INPUT);

    GPIO_setupPinDirection(MISO_PORT_ID, MISO_PIN_ID, PIN_OUTPUT);

    SPCR = (1 << SPE);

    SPSR &= ~(1 << SPI2X);
}

/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
uint8 SPI_sendReceiveByte(uint8 data)
{
    /* Writing to the SPDR register initiates data transmission */
    SPDR = (data);
 
    /* When a serial transfer is complete, the SPIF Flag is set. */
    while(BIT_IS_CLEAR(SPSR, SPIF));
    
    /*
     * : SPIF flag is cleared by first reading SPSR (with SPIF set)
     * and then accessing SPDR value
     */
    return (SPDR);
}

/*
 * Description :
 * Send the required string through SPI to the other SPI device.
 */
void SPI_sendString(const uint8* str)
{
    uint8 _ch = (INITIAL_VALUE_ZERO);
    uint8 receivedData = (INITIAL_VALUE_ZERO);       /* Will Receive Dummy Data */

    while(str[_ch] != NULL_CHAR)
    {
        receivedData = SPI_sendReceiveByte(str[_ch]);
        (++_ch);
    }
}

/*
 * Description :
 * Receive the required string until the '#' symbol through SPI from the other SPI device.
 */
void SPI_receiveString(uint8* str)
{
    uint8 _ch = (INITIAL_VALUE_ZERO);
    
    while(str[_ch] != (STR_COMMON_CHAR))
    {
        str[_ch] = SPI_sendReceiveByte(SPI_DEFAULT_DATA);
        (++_ch);
    }

    str[_ch] = (NULL_CHAR);
}