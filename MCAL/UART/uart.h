 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "../../Utils/std_types.h"

#define BAUD_RATE           (9600UL)
#define STR_COMMON_CHAR     ('#')
//#define MCU_READY			(0x10)

#define NEW_PASS_MODE		(0)
#define OPEN_DOOR_MODE		(1)
#define CHANGE_PASS_MODE	(2)
#define ALARM_SIGNAL		(3)

/*******************************************************************************
 *                      Functions Prototypes                                   *
*******************************************************************************/

typedef enum
{
	Disabled,
	Even_Parity = 2,
	Odd_Parity
	
} UART_ParityMode ;

typedef enum
{
	_1_bit,
	_2_bit
	
} UART_StopBitMode;

typedef struct
{
	uint8 bit_data;
	UART_ParityMode parity;
	UART_StopBitMode stop_bit;
	uint32 baud_rate;

} UART_ConfigType;


/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
