/******************************************************************************
*
* Module: SPI
*
* File Name: spi.h
*
* Description: Header file for the AVR SPI driver
*
* Author: Abdallah El-Sakka
*
*******************************************************************************/

#ifndef SPI_H_
#define SPI_H_

#include "../../Utils/std_types.h"

/*******************************************************************************
*                                Definitions                                  *
*******************************************************************************/

#define SS_PORT_ID          (PORTB_ID)
#define MOSI_PORT_ID        (PORTB_ID)
#define MISO_PORT_ID        (PORTB_ID)
#define SCK_PORT_ID         (PORTB_ID)

#define SS_PIN_ID           (PIN4_ID)
#define MOSI_PIN_ID         (PIN5_ID)
#define MISO_PIN_ID         (PIN6_ID)
#define SCK_PIN_ID          (PIN7_ID)

#define STR_COMMON_CHAR     ('#')
#define SPI_DEFAULT_DATA    (0xFF)

/*******************************************************************************
*                                Function Prototypes                           *
*******************************************************************************/

/*
 * Description :
 * Initialize the SPI device as Master.
 */
void SPI_initMaster(void);

/*
 * Description :
 * Initialize the SPI device as Slave.
 */
void SPI_initSlave(void);

/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
uint8 SPI_sendReceiveByte(uint8 data);

/*
 * Description :
 * Send the required string through SPI to the other SPI device.
 */
void SPI_sendString(const uint8* str);

/*
 * Description :
 * Receive the required string until the '#' symbol through SPI from the other SPI device.
 */
void SPI_receiveString(uint8* str);

#endif      /* SPI_H_ */