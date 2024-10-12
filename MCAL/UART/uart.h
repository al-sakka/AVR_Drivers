/******************************************************************************
*
* Module: UART
*
* File Name: uart.h
*
* Description: Header file for the AVR UART driver
*
* Author: Abdallah El-Sakka
*
*******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "../../Utils/std_types.h"

/*******************************************************************************
*                                Definitions                                  *
*******************************************************************************/

#define BAUD_RATE           (9600UL)
#define STR_COMMON_CHAR     ('#')

/*******************************************************************************
*                                Function Prototypes                           *
*******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * Enable the UART.
 * Setup the UART baud rate.
 */
void UART_init(void);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_receiveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 * str);

/*
 * Description :
 * Receive the required string until the COMMON_CHAR symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 * str);

#endif      /* UART_H_ */