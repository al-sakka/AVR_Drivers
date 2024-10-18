/******************************************************************************
*
* Module: TWI(I2C)
*
* File Name: i2c.h
*
* Description: Header file for the TWI(I2C) driver
*
* Author: Abdallah El-Sakka
*
*******************************************************************************/
 
#ifndef I2C_H_
#define I2C_H_

#include "../../Utils/std_types.h"

/*******************************************************************************
*                                Definitions                                  *
*******************************************************************************/

#define MASTER_ADDRESS  (0b00000010)    /* Master Address = 1 */
#define BIT_RATE        (400000UL)      /* 400 Kbs */

/* I2C Status Bits in the TWSR Register */
#define I2C_START         0x08 /* start has been sent */
#define I2C_REP_START     0x10 /* repeated start */

#define I2C_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define I2C_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define I2C_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define I2C_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define I2C_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                      Functions Prototypes                                   *
*******************************************************************************/

/*
 * Initialize TWI(I2C) Protocol
 */
void I2C_init(void);

/*
 * Start Sending
 */
void I2C_start(void);

/*
 * Stop Sending
 */
void I2C_stop(void);

/*
 * Write Data to be sent
 */
void I2C_writeByte(uint8 data);

/*
 * Read received fata from slave using ACK technique
 */
uint8 I2C_readByteWithACK(void);

/*
 * Read received fata from slave using NACK technique
 */
uint8 I2C_readByteWithNACK(void);

/*
 *  Read status register
 */
uint8 I2C_getStatus(void);

#endif  /* I2C_H_ */