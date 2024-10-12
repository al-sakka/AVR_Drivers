/******************************************************************************
*
* Module: GPIO
*
* File Name: gpio.c
*
* Description: Source file for the AVR GPIO driver
*
* Author: Abdallah El-Sakka
*
*******************************************************************************/
#include "gpio.h"

/* Arrays for DDR, PORT and PIN registers */
static volatile uint8* ddr[] = {&DDRA, &DDRB, &DDRC, &DDRD};
static volatile uint8* port[] = {&PORTA, &PORTB, &PORTC, &PORTD};
static volatile uint8* pin[] = {&PINA, &PINB, &PINC, &PIND};

/*
*   Description:
*   Setup the direction of the required pin I/O
*/
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction)
{
    if(CHECK_PIN(pin_num) || CHECK_PORT(port_num)) return;

    if(direction == PIN_OUTPUT)
    {
        SET_BIT(*ddr[port_num], pin_num);
    }
    else
    {
        CLEAR_BIT(*ddr[port_num], pin_num);
    }
}

/*
*   Description:
*   Write the logic value on the required pin LOW/HIGH
*/
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
    if(CHECK_PIN(pin_num) || CHECK_PORT(port_num)) return;

    if(value == LOGIC_HIGH)
    {
        SET_BIT(*port[port_num], pin_num);
    }
    else
    {
        CLEAR_BIT(*port[port_num], pin_num);
    }
}

/*
*   Description:
*   Read and return the value of the pin LOW/HIGH
*/
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
    if(CHECK_PIN(pin_num) || CHECK_PORT(port_num)) return 0xFF;     /* Indicates an Error */

    // if(*pin[port_num] & (1 << pin_num))
    if(BIT_IS_SET(*pin[port_num], pin_num))
    {
        return LOGIC_HIGH;
    }
    else
    {
        return LOGIC_LOW;
    }
}

/*
*   Description:
*   Setup the direction of the required port (all pins) I/O
*/
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
    if(CHECK_PORT(port_num)) return;

    *ddr[port_num] = direction;

}

/*
*   Description:
*   Write a value on the port (all pins)
*/
void GPIO_writePort(uint8 port_num, uint8 value)
{
    if(port_num >= NUM_OF_PORTS) return;

    *port[port_num] = value;
}

/*
*   Description:
*   Read and return value of the port
*/
uint8 GPIO_readPort(uint8 port_num)
{
    if(CHECK_PORT(port_num)) return 0xFF;       /* Indicates an Error */
    return *pin[port_num];
}
