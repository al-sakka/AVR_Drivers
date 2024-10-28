/******************************************************************************
*
* Module: TWI(I2C)
*
* File Name: i2c.c
*
* Description: Source file for the TWI(I2C) driver
*
* Author: Abdallah El-Sakka
*
*******************************************************************************/

#include "i2c.h"
#include <avr/io.h>
#include "../../Utils/common_macros.h"

/*******************************************************************************
*                      Functions Definitions                                  *
*******************************************************************************/

/*
 * Initialize TWI(I2C) Protocol
 */
void I2C_init(void)
{
    /* Equation to calculate TWBR register value */
    uint8 twbr_value = (uint8)((CPU_FREQUENCY / BIT_RATE) - 16) / 2;

    TWBR = (twbr_value);
    TWSR = (INITIAL_VALUE_ZERO);

    /* Set master address */
    TWAR = (MASTER_ADDRESS);

    /* Enable TWI(I2C) */
    SET_BIT(TWCR, TWEN);
}

/*
 * Start Sending
 */
void I2C_start(void)
{
    /*
    * Clear the TWINT flag before sending the start bit (TWINT = 1)
    * Send the start bit by (TWSTA = 1)
    * Enable TWI Module (TWEN = 1)
    */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    /* Polling until start bit is sent successfully */
    while(BIT_IS_CLEAR(TWCR, TWINT));
}

/*
 * Stop Sending
 */
void I2C_stop(void)
{
    /*
    * Clear the TWINT flag before sending the stop bit (TWINT = 1)
    * send the stop bit by (TWSTO = 1)
    * Enable TWI Module (TWEN = 1)
    */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

/*
 * Write Data to be sent
 */
void I2C_writeByte(uint8 data)
{

    /*
    * Clear the TWINT flag before sending the data (TWINT = 1)
    * Enable TWI Module (TWEN = 1)
    */
    TWCR = (1 << TWINT) | (1 << TWEN);


    /* TWDR contains the next byte to be transmitted */
    TWDR = (data);

    /* Polling until data is sent successfully */
    while(BIT_IS_CLEAR(TWCR, TWINT));
}

/*
 * Read received fata from slave using ACK technique
 */
uint8 I2C_readByteWithACK(void)
{
    /*
    * Clear the TWINT flag before reading the data (TWINT = 1)
    * Enable sending ACK after reading or receiving data (TWEA = 1)
    * Enable TWI Module (TWEN = 1)
    */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

    /* Polling until data is received successfully */
    while(BIT_IS_CLEAR(TWCR, TWINT));

    /* Read Data */
    return ( TWDR );
}

/*
 * Read received fata from slave using NACK technique
 */
uint8 I2C_readByteWithNACK(void)
{
    /*
    * Clear the TWINT flag before reading the data (TWINT = 1)
    * Enable sending ACK after reading or receiving data (TWEA = 1)
    * Enable TWI Module (TWEN = 1)
    */
    TWCR = (1 << TWINT) | (1 << TWEN);

    /* Polling until data is received successfully */
    while(BIT_IS_CLEAR(TWCR, TWINT));

    /* Read Data */
    return ( TWDR );
}

/*
 *  Read status register
 */
uint8 I2C_getStatus(void)
{
    /* Masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    uint8 status = (TWSR) & (0xF8);

    /* These five bits reflect the status of the TWI logic and the Two-wire Serial Bus */
    return ( status );
}
