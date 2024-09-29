/******************************************************************************
*
* Module: ADC
*
* File Name: adc.h
*
* Description: header file for the ATmega16/32 ADC driver
*
* Author: Abdallah El-Sakka
*
*******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "../std_types.h"

/*******************************************************************************
*                                Definitions                                  *
*******************************************************************************/

#define ADC_MAXIMUM_VALUE    (1023u)
#define ADC_REF_VOLT_VALUE   (5u)

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*
* Description :
* Function responsible for initialize the ADC driver.
*/
void ADC_init(void);

/*
* Description :
* Function responsible for read analog data from a certain ADC channel
* and convert it to digital using the ADC driver.
*/
uint16 ADC_readChannel(uint8 channel_num);

#endif  /* ADC_H_ */