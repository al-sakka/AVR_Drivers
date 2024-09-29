/******************************************************************************
*
* Module: LCD
*
* File Name: lcd.c
*
* Description: Source file for the LCD driver
*
* Author: Abdallah El-Sakka
*
*******************************************************************************/

#include "../common_macros.h"
#include "../gpio/gpio.h"
#include <util/delay.h>
#include <stdio.h>
#include "lcd.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
*******************************************************************************/

/*
 * Description :
 * Initialize the LCD
 */
void LCD_init(void)
{
    GPIO_setupPinDirection(RS_PORT_ID, RS_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(EN_PORT_ID, EN_PIN_ID, PIN_OUTPUT);
    _delay_ms(20);      /* Power On Delay */

#if (LCD_DATA_BITS_MODE == (4))

    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, PIN_OUTPUT);

    /* 4-bit initialization of LCD */
    LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
    LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

    /* use 2-lines LCD + 4-bits data mode + 5*7 dot display mode */
    LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif (LCD_DATA_BITS_MODE == (8))

    GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);

    /* ues 2-lines LCD + 8-bits data mode + 5*7 display mode */
    LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);

#endif

    LCD_sendCommand(LCD_CURSOR_OFF);
    LCD_sendCommand(LCD_CLEAR_SCREEN);

}

/*
 * Description :
 * Send the required command to the screen
 */
void LCD_sendCommand(uint8 command)
{
    GPIO_writePin(RS_PORT_ID, RS_PIN_ID, LOGIC_LOW);
    _delay_ms(1);       /*    delay for processing Tas     */
    GPIO_writePin(EN_PORT_ID, EN_PIN_ID, LOGIC_HIGH);
    _delay_ms(1);       /* delay for processing Tpw - Tdws */

#if (LCD_DATA_BITS_MODE == (4))

    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command, PIN4_ID));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command, PIN5_ID));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command, PIN6_ID));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command, PIN7_ID));

    _delay_ms(1);        /* delay for processing Tdsw */
    GPIO_writePin(EN_PORT_ID, EN_PIN_ID, LOGIC_LOW);
    _delay_ms(1);        /*  delay for processing Th  */
    GPIO_writePin(EN_PORT_ID, EN_PIN_ID, LOGIC_HIGH);
    _delay_ms(1);       /*  delay for processing Tpw  */

    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command, PIN0_ID));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command, PIN1_ID));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command, PIN2_ID));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command, PIN3_ID));

#elif (LCD_DATA_BITS_MODE == (8))
    GPIO_writePort(LCD_DATA_PORT_ID, command);
#endif

    _delay_ms(1);       /* delay for processing Tdsw */
    GPIO_writePin(EN_PORT_ID, EN_PIN_ID, LOGIC_LOW);
    _delay_ms(1);       /*  delay for processing Th  */
}

/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(uint8 data)
{
    GPIO_writePin(RS_PORT_ID, RS_PIN_ID, LOGIC_HIGH);
    _delay_ms(1);       /*    delay for processing Tas     */
    GPIO_writePin(EN_PORT_ID, EN_PIN_ID, LOGIC_HIGH);
    _delay_ms(1);       /* delay for processing Tpw - Tdws */

#if (LCD_DATA_BITS_MODE == (4))

    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(data, PIN4_ID));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(data, PIN5_ID));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(data, PIN6_ID));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(data, PIN7_ID));

    _delay_ms(1);        /* delay for processing Tdsw */
    GPIO_writePin(EN_PORT_ID, EN_PIN_ID, LOGIC_LOW);
    _delay_ms(1);        /*  delay for processing Th  */
    GPIO_writePin(EN_PORT_ID, EN_PIN_ID, LOGIC_HIGH);
    _delay_ms(1);       /*  delay for processing Tpw  */

    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(data, PIN0_ID));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(data, PIN1_ID));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(data, PIN2_ID));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(data, PIN3_ID));

#elif (LCD_DATA_BITS_MODE == (8))
    GPIO_writePort(LCD_DATA_PORT_ID, data);
#endif

    _delay_ms(1);       /* delay for processing Tdsw */
    GPIO_writePin(EN_PORT_ID, EN_PIN_ID, LOGIC_LOW);
    _delay_ms(1);       /*  delay for processing Th  */
}

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char* const str)
{
    uint8 char_index;

    for(char_index = 0; str[char_index] != '\0'; ++char_index)
    {
        LCD_displayCharacter(str[char_index]);
    }
}

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 * rows: 0 : 3
 * cols: 0 : 15
 */
void LCD_moveCursor(uint8 row, uint8 col)
{
    uint8 rows_mem_mapping[4] = {0x00, 0x40, 0x10, 0x50};
    uint8 memory_address = col + rows_mem_mapping[row];

    LCD_sendCommand(memory_address | LCD_SET_CURSOR_LOCATION);
}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowCol(uint8 row, uint8 col, const char* const str)
{
    LCD_moveCursor(row, col);
    LCD_displayString(str);
}

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_displayInt(uint32 data)
{
    uint8 buff[16];
    sprintf(buff, "%lu", data);
    LCD_displayString(buff);
}

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void)
{
    LCD_sendCommand(LCD_CLEAR_SCREEN);
    _delay_ms(2);
    LCD_moveCursor(0, 0);
}

/*
 * Description :
 * Display a custom character on LCD
 */
void LCD_displayCustomChar(uint8 location, uint8 charmap[])
{
    location &= 0x7; /* Limit to 8 custom locations (0-7) */
    
    LCD_sendCommand(LCD_SET_CGRAM_ADDR | (location << 3)); /* Set CGRAM address */

    for(int i = 0; i < 8; i++)
    {
        LCD_displayCharacter(charmap[i]); /* Send each row of the pattern */
    }
}
