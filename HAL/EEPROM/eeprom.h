/******************************************************************************
*
* Module: 24C16-EEPROM
*
* File Name: eeprom.h
*
* Description: Header file for the 24C16-EEPROM driver
*
* Author: Abdallah El-Sakka
*
*******************************************************************************/

#ifndef EEPROM_H_
#define EEPROM_H_

#include "../../Utils/std_types.h"

#define COMM_ADDRESS	(0x0311)

/*******************************************************************************
*                      Functions Prototypes                                    *
*******************************************************************************/

/*
 * Save data (8-bits) in EEPROM memory
 */
uint8 EEPROM_writeByte(uint16 a_u16Addr, uint8 a_u8Data);

/*
 * Write data (8-bits) in EEPROM memory
 */
uint8 EEPROM_readByte(uint16 a_u16Addr, uint8* a_u8Data);

/*
 * Write String in EEPROM at a specific address
 */
uint8 EEPROM_writeString(uint16 u16addr, const uint8 *str);

/*
 * Read String from EEPROM at a specific address
 */
uint8 EEPROM_readString(uint16 u16addr, uint8 *str, uint8 maxLen);

#endif  /* EEPROM_H_ */
