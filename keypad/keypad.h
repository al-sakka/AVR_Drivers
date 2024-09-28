 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the Keypad driver
 *
 * Author: Abdallah El-Sakka
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
*******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS             (4)
#define KEYPAD_NUM_ROWS             (4)

/* Keypad Matrix Port Configurations */
#define KEYPAD_ROW_PORT_ID          (PORTB_ID)
#define KEYPAD_FIRST_ROW_PIN_ID     (PIN4_ID)

#define KEYPAD_COL_PORT_ID          (PORTD_ID)
#define KEYPAD_FIRST_COL_PIN_ID     (PIN2_ID)

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED       (LOGIC_LOW)
#define KEYPAD_BUTTON_RELEASED      (LOGIC_HIGH)

/* Macro To Return Keypad Pressed Key (1 : 16) */
#define KEY_INDEX(ROW, COL) (((ROW) * (KEYPAD_NUM_COLS)) + (COL) + 1)

/*******************************************************************************
 *                      Functions Prototypes                                   *
*******************************************************************************/

/*
 * Description :
 * Get the Keypad pressed button
 */
uint8 KEYPAD_getPressedKey(void);

#endif  /* KEYPAD_H_ */