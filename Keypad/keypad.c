/******************************************************************************
*
* Module: KEYPAD
*
* File Name: keypad.c
*
* Description: Source file for the Keypad driver
*
* Author: Abdallah El-Sakka
*
*******************************************************************************/

#include "../GPIO/gpio.h"
#include "keypad.h"
#include <util/delay.h>

/*******************************************************************************
 *                      Functions Definitions                                  *
*******************************************************************************/

#if (KEYPAD_NUM_COLS == 4)

static uint8 KEYPAD_4x4_mapping(uint8 button_number)
{
    uint8 mapped_4x4_keypad[16] = {7, 8, 9, '%', 4, 5, 6, '*', 1, 2, 3, '-', 13, 0, '=', '+'};
    return (mapped_4x4_keypad[button_number - 1]);
}

#elif (KEYPAD_NUM_COLS == 3)

static uint8 KEYPAD_4x3_mapping(uint8 button_number)
{
    uint8 mapped_4x3_keypad[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#'};
    return (mapped_4x3_keypad[button_number - 1]);
}

#endif

/*
 * Description :
 * Get the Keypad pressed button
 */
uint8 KEYPAD_getPressedKey(void)
{
    uint8 index, row, col;

    for(index = 0; index < KEYPAD_NUM_ROWS; ++index)
    {
        GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + index, PIN_INPUT);
    }

    for(index = 0; index < KEYPAD_NUM_COLS; ++index)
    {
        GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + index, PIN_INPUT);
    }

    while(1)
    {
        for(row = 0; row < KEYPAD_NUM_ROWS; ++row)
        {
            GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row, PIN_OUTPUT);
            GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row, KEYPAD_BUTTON_PRESSED);

            for(col = 0; col < KEYPAD_NUM_COLS; ++col)
            {
                if(GPIO_readPin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + col) == KEYPAD_BUTTON_PRESSED)
                {
                    #if (KEYPAD_NUM_COLS == 4)
                    return KEYPAD_4x4_mapping(KEY_INDEX(row, col));
                    #elif (KEYPAD_NUM_COLS == 3)
                    return KEYPAD_4x3_mapping(KEY_INDEX(row, col));
                    #endif
                }
            }

            GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row, PIN_INPUT);
            _delay_ms(10);
        }
    }
}