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
void UART_init(void)
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
     * UMSEL   = 0 Asynchronous Operation
     * UPM1:0  = 00 Disable parity bit
     * USBS    = 0 One stop bit
     * UCSZ1:0 = 11 For 8-bit data mode
     * UCPOL   = 0 Used with the Synchronous operation only
     ***********************************************************************/
    UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);

    uint16 UBRR_val = (uint16)(((F_CPU) / (8 * BAUD_RATE)) - (1));

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
    while(*str != NULL_CHAR)
    {
        UART_sendByte(  (*str)  );
        (++str);
    }
}

/*
 * Description :
 * Receive the required string until the COMMON_CHAR symbol through UART from the other UART device.
 */
void UART_receiveString(uint8* str)
{
    uint8 _ch = 0;

    while(str[_ch] != (STR_COMMON_CHAR))
    {
        str[_ch] = UART_receiveByte();
        (++_ch);
    }

    str[_ch] = NULL_CHAR;
}
