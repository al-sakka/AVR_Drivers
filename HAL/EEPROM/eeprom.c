/******************************************************************************
*
* Module: 24C16-EEPROM
*
* File Name: eeprom.c
*
* Description: Source file for the 24C16-EEPROM driver
*
* Author: Abdallah El-Sakka
*
*******************************************************************************/

#include "eeprom.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/I2C/i2c.h"
#include "../../Utils/std_types.h"
#include <util/delay.h>

/*******************************************************************************
*                      Functions Definitions                                  *
*******************************************************************************/

/*
 * Write data (8-bits) in EEPROM memory
 */
uint8 EEPROM_writeByte(uint16 a_u16Addr, uint8 a_u8Data)
{
	/* Send the Start Bit */
    I2C_start();
    if(I2C_getStatus() != I2C_START) return (ERROR);

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    I2C_writeByte((uint8)(0xA0 | ((a_u16Addr & (0x0700)) >> (NUM_OF_PINS - 1))));
    if (I2C_getStatus() != I2C_MT_SLA_W_ACK) return (ERROR);

    /* Send the required memory location address */
    I2C_writeByte((uint8)(a_u16Addr));
    if (I2C_getStatus() != I2C_MT_DATA_ACK) return (ERROR);

    /* write byte to eeprom */
    I2C_writeByte(a_u8Data);
    if (I2C_getStatus() != I2C_MT_DATA_ACK) return (ERROR);

    /* Send the Stop Bit */
    I2C_stop();

    return (SUCCESS);
}

/*
 * Read data (8-bits) from EEPROM memory
 */
uint8 EEPROM_readByte(uint16 a_u16Addr, uint8* a_u8Data)
{
	/* Send the Start Bit */
    I2C_start();
    if (I2C_getStatus() != I2C_START) return (ERROR);

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    I2C_writeByte((uint8)((0xA0) | ((a_u16Addr & (0x0700)) >> (NUM_OF_PINS - 1))));
    if (I2C_getStatus() != I2C_MT_SLA_W_ACK) return (ERROR);

    /* Send the required memory location address */
    I2C_writeByte((uint8)(a_u16Addr));
    if (I2C_getStatus() != I2C_MT_DATA_ACK) return (ERROR);

    /* Send the Repeated Start Bit */
    I2C_start();
    if (I2C_getStatus() != I2C_REP_START) return (ERROR);

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    I2C_writeByte((uint8)((0xA0) | ((a_u16Addr & (0x0700)) >> (NUM_OF_PINS - 1)) | (1)));
    if (I2C_getStatus() != I2C_MT_SLA_R_ACK) return (ERROR);

    /* Read Byte from Memory without send ACK */
    *a_u8Data = I2C_readByteWithNACK();
    if (I2C_getStatus() != I2C_MR_DATA_NACK) return (ERROR);

    /* Send the Stop Bit */
    I2C_stop();

    return SUCCESS;
}

/*
 * Write String in EEPROM at a specific address
 */
uint8 EEPROM_writeString(uint16 u16addr, const uint8 *str)
{
    while (*str)
    {
        /* Write each character in the string to EEPROM */
        EEPROM_writeByte(u16addr++, *str++);
        _delay_ms(10);
    }
    /* Write null terminator to indicate end of string */
    EEPROM_writeByte(u16addr, '\0');
    _delay_ms(10);
    return SUCCESS;
}

/*
 * Read String from EEPROM at a specific address
 */
uint8 EEPROM_readString(uint16 u16addr, uint8 *str, uint8 maxLen)
{
    uint8 i = 0;
    uint8 data;

    /* Read each character from EEPROM until null terminator or maxLen */
    for (i = 0; i < maxLen - 1; i++)
    {
        if (EEPROM_readByte(u16addr++, &data) != SUCCESS)
        {
            return ERROR;  // Return error if read operation fails
        }
        str[i] = data;
        if (data == '\0')
        {
            return SUCCESS;  // Stop if null terminator is found
        }
    }
    str[i] = '\0';  // Ensure null termination if maxLen limit is reached
    return SUCCESS;
}
