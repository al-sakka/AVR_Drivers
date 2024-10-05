/******************************************************************************
*
* Module: GPIO
*
* File Name: gpio.h
*
* Description: Header file for the AVR GPIO driver
*
* Author: Abdallah El-Sakka
*
*******************************************************************************/
#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>
#include "../std_types.h"
#include "../common_macros.h"

/*******************************************************************************
*                                Definitions                                  *
*******************************************************************************/

#define NUM_OF_PORTS    (4u)
#define NUM_OF_PINS     (8u)

#define PORTA_ID        (0u)
#define PORTB_ID        (1u)
#define PORTC_ID        (2u)
#define PORTD_ID        (3u)

#define PIN0_ID         (0u)
#define PIN1_ID         (1u)
#define PIN2_ID         (2u)
#define PIN3_ID         (3u)
#define PIN4_ID         (4u)
#define PIN5_ID         (5u)
#define PIN6_ID         (6u)
#define PIN7_ID         (7u)

/* Check validity of pin count */
#define CHECK_PIN(pin_count)    ((pin_count) >= NUM_OF_PINS)

/* Check validity of port count */
#define CHECK_PORT(port_count)  ((port_count) >= NUM_OF_PORTS)

/*******************************************************************************
*                              Type Declerations                               *
*******************************************************************************/

typedef enum
{
    PIN_INPUT,  /* 0 */
    PIN_OUTPUT  /* 1 */

} GPIO_PinDirectionType;

typedef enum
{
    PORT_INPUT, /* 0 */
    PORT_OUTPUT = 0xFF

} GPIO_PortDirectionType;

/*******************************************************************************
*                                Function Prototypes                           *
*******************************************************************************/

/*
*   Description:
*   Setup the direction of the required pin I/O
*/
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);

/*
*   Description:
*   Write the logic value on the required pin LOW/HIGH
*/
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/*
*   Description:
*   Read and return the value of the pin LOW/HIGH
*/
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);

/*
*   Description:
*   Setup the direction of the required port (all pins) I/O
*/
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction);

/*
*   Description:
*   Write a value on the port (all pins)
*/
void GPIO_writePort(uint8 port_num, uint8 value);

/*
*   Description:
*   Read and return value of the port
*/
uint8 GPIO_readPort(uint8 port_num);

#endif  /* GPIO_H_ */
