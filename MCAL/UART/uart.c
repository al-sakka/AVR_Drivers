/******************************************************************************
*
* Module: UART
*
* File Name: uart.c
*
* Description: Source file for the AVR UART driver
*
* Author: Abdallah El-Sakka
*
*******************************************************************************/

#include "uart.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../Utils/common_macros.h"
#include <avr/io.h>

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
void UART_init(const UART_ConfigType * Config_Ptr)
{
    /*********** UART Frame ***********
     *          Asynchronous         *
     *          1 stop-bit           *
     *          8-bits Data          *
    **********************************/

    /* Double transmission speed */
    UCSRA = (1 << U2X);

    /************************** UCSRB Description **************************
     * RXCIE = 0 Disable USART RX Complete Interrupt Enable
     * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
     * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
     * RXEN  = 1 Receiver Enable
     * RXEN  = 1 Transmitter Enable
     * UCSZ2 = 0 For 8-bit data mode
     * RXB8 & TXB8 not used for 8-bit data mode
    ***********************************************************************/
    UCSRB = (1 << RXEN) | (1 << TXEN);

    /************************** UCSRC Description **************************
     * URSEL   = 1 The URSEL must be one when writing the UCSRC
     * UMSEL   = Asynch/Synch Operation
     * UPM1:0  = parity bit
     * USBS    = stop bit
     * UCSZ1:0 = For data mode
     * UCPOL   = Used with the Synchronous operation only
     ***********************************************************************/
    uint8 temp_UCSRC = (1 << URSEL);

    if(Config_Ptr->stop_bit)
    {
    	temp_UCSRC |= (1 << USBS);
    }

    switch(Config_Ptr->bit_data)
    {
		case _5_bit:
			break;
		case _6_bit:
			temp_UCSRC |= (1 << UCSZ0);
			break;
		case _7_bit:
			temp_UCSRC |= (1 << UCSZ1);
			break;
		case _8_bit:
			temp_UCSRC |= (1 << UCSZ1) | (1 << UCSZ0);
			break;
		case _9_bit:
			temp_UCSRC |= (1 << UCSZ1) | (1 << UCSZ0);
			UCSRB |= (1 << UCSZ2);
			break;
		default:
			break;
    }

    switch(Config_Ptr->parity)
    {
		case Disabled:
			break;
		case Even_Parity:
			temp_UCSRC |= (1 << UPM1);
			break;
		case Odd_Parity:
			temp_UCSRC |= (1 << UPM1) | (1 << UPM0);
			break;
    }

    UCSRC |= (temp_UCSRC);

    uint16 UBRR_val = (uint16)((((CPU_FREQUENCY) / (8UL * Config_Ptr->baud_rate))) - (1));

    /* First LSB 8-bits from the BAUD_RATE inside UBRRL and last MSB 4-bits in UBRRH */
    UBRRL = (UBRR_val);
    UBRRH = (UBRR_val) >> (NUM_OF_PINS);
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(uint8 data)
{
    /*
    * UDRE flag is set when the Tx buffer (UDR) is empty and ready for transmitting a new byte
    */
    while(BIT_IS_CLEAR(UCSRA, UDRE));

    /*
     * Put the required data in the UDR register and it clear the UDRE flag as UDR register is not empty
     */
    UDR = (data);
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_receiveByte(void)
{
    /* RXC flag is set when the UART receive data */
    while(BIT_IS_CLEAR(UCSRA, RXC));

    /*
    * Read the received data from the Rx buffer (UDR)
    * The RXC flag will be cleared after read the data
    */
    return (UDR);
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8* str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(str[i] != '\0')
	{
		UART_sendByte(str[i]);
		i++;
	}
}

/*
 * Description :
 * Receive the required string until the COMMON_CHAR symbol through UART from the other UART device.
 */
void UART_receiveString(uint8* str)
{
	uint8 i = 0;

	/* Receive the first byte */
	str[i] = UART_receiveByte();

	/* Receive the whole string until the '#' */
	while(str[i] != '#')
	{
		i++;
		str[i] = UART_receiveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	str[i] = '\0';
}
