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

#define MASTER_ADDRESS  (0b00000010)
#define BIT_RATE        (400000UL)

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

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
uint8 I2C_readByteWithACK(void);

/*
 * 
 */
uint8 TWI_getStatus(void);

#endif  /* I2C_H_ */