/******************************************************************************
*
* Module: EEPROM
*
* File Name: eeprom.h
*
* Description: Header file for the EEPROM driver
*
* Author: Abdallah El-Sakka
*
*******************************************************************************/

#ifndef EEPROM_H_
#define EEPROM_H_

#include "../../Utils/std_types.h"

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

#endif  /* EEPROM_H_ */