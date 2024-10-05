/******************************************************************************
*
* Module: LCD
*
* File Name: lcd.h
*
* Description: Header file for the LCD driver
*
* Author: Abdallah El-Sakka
*
*******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "../std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
*******************************************************************************/

#define LCD_DATA_BITS_MODE  (4)

#define RS_PORT_ID          (PORTA_ID)
#define RS_PIN_ID           (PIN1_ID)

#define EN_PORT_ID          (PORTA_ID)
#define EN_PIN_ID           (PIN2_ID)

#define LCD_DATA_PORT_ID    (PORTA_ID)

#if (LCD_DATA_BITS_MODE == (4))

#define LCD_DB4_PIN_ID      (PIN3_ID)
#define LCD_DB5_PIN_ID      (PIN4_ID)
#define LCD_DB6_PIN_ID      (PIN5_ID)
#define LCD_DB7_PIN_ID      (PIN6_ID)

#endif

/* LCD Commands */
#define LCD_CLEAR_SCREEN                     (0x01)
#define LCD_GO_TO_HOME                       (0x02)
#define LCD_TWO_LINES_EIGHT_BITS_MODE        (0x38)
#define LCD_TWO_LINES_FOUR_BITS_MODE         (0x28)
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   (0x33)
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   (0x32)
#define LCD_CURSOR_OFF                       (0x0C)
#define LCD_CURSOR_ON                        (0x0E)
#define LCD_SET_CURSOR_LOCATION              (0x80)
#define LCD_SET_CGRAM_ADDR                   (0x40)

/*******************************************************************************
 *                      Functions Prototypes                                   *
*******************************************************************************/

/*
 * Description :
 * Initialize the LCD
 */
void LCD_init(void);

/*
 * Description :
 * Send the required command to the screen
 */
void LCD_sendCommand(uint8 command);

/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(uint8 data);

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char* s);

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(uint8 row, uint8 col);

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowCol(uint8 row, uint8 col, const char* str);

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_displayInt(uint32 data);

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void);

/*
 * Description :
 * Display a custom character on LCD
 */
void LCD_displayCustomChar(uint8 location, uint8 charma[]);

#endif  /* LCD_H_ */
