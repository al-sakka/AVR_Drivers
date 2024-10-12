 /******************************************************************************
 *
 * Module: Common - Macros
 *
 * File Name: Common_Macros.h
 *
 * Description: Commonly used Macros
 *
 * Author: Abdallah El-Sakka
 *
 *******************************************************************************/

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* Set a certain bit in any port */
#define SET_BIT(PORT, PIN) ((PORT) |= (1 << (PIN)))

/* Clear a certain bit in any port */
#define CLEAR_BIT(PORT,PIN) ((PORT) &= ~(1 << (PIN)))

/* Toggle a certain bit in any port */
#define TOGGLE_BIT(PORT, PIN) ((PORT) ^= (1 << (PIN)))

/* Rotate right a certain port with N rotates */
#define ROR(PORT, N) ((PORT) = ((PORT) >> (N)) | ((PORT) << (8 - (N))))

/* Rotate left a certain port with N rotates */
#define ROL(PORT, N) ((PORT) = ((PORT) << (N)) | ((PORT) >> (8 - (N))))

/* check if the pin is set */
#define BIT_IS_SET(PORT, PIN) ((PORT) & (1 << (PIN)))

/* check if the pin is cleared */
#define BIT_IS_CLEAR(PORT, PIN) (!((PORT) & (1 << (PIN))))

/* get a specific bit value */
#define GET_BIT(PORT, BIT) (((PORT) >> (BIT)) & 1)

#endif  /* COMMON_MACROS_H_ */
