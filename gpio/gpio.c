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

/*
*   Description:
*   Setup the direction of the required pin I/O
*/
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction)
{
    if((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS))
    {
        /*
            Do Nothing
        */
    }
    else
    {
        switch(port_num)
        {
            case PORTA_ID:
                if(direction == PIN_OUTPUT)
                {
                    SET_BIT(DDRA, pin_num);
                }
                else
                {
                    CLEAR_BIT(DDRA, port_num);
                }

                break;

            case PORTB_ID:
                if(direction == PIN_OUTPUT)
                {
                    SET_BIT(DDRB, pin_num);
                }
                else
                {
                    CLEAR_BIT(DDRB, port_num);
                }

                break;

            case PORTC_ID:
                if(direction == PIN_OUTPUT)
                {
                    SET_BIT(DDRC, pin_num);
                }
                else
                {
                    CLEAR_BIT(DDRC, port_num);
                }

                break;

            case PORTD_ID:
                if(direction == PIN_OUTPUT)
                {
                    SET_BIT(DDRD, pin_num);
                }
                else
                {
                    CLEAR_BIT(DDRD, port_num);
                }

                break;
        }
    }
}

/*
*   Description:
*   Write the logic value on the required pin LOW/HIGH
*/
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
    if((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS))
    {
        /*
            Do Nothing
        */
    }
    else
    {
        switch(port_num)
        {
            case PORTA_ID:
                if(value == LOGIC_HIGH)
                {
                    SET_BIT(PORTA, pin_num);
                }
                else
                {
                    CLEAR_BIT(PORTA, pin_num);
                }

                break;

            case PORTB_ID:
                if(value == LOGIC_HIGH)
                {
                    SET_BIT(PORTB, pin_num);
                }
                else
                {
                    CLEAR_BIT(PORTB, pin_num);
                }

                break;

            case PORTC_ID:
                if(value == LOGIC_HIGH)
                {
                    SET_BIT(PORTC, pin_num);
                }
                else
                {
                    CLEAR_BIT(PORTC, pin_num);
                }

                break;

            case PORTD_ID:
                if(value == LOGIC_HIGH)
                {
                    SET_BIT(PORTD, pin_num);
                }
                else
                {
                    CLEAR_BIT(PORTD, pin_num);
                }

                break;
        }
    }
}

/*
*   Description:
*   Read and return the value of the pin LOW/HIGH
*/
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
    if((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS))
    {
        /*
            Do Nothing
        */
    }
    else
    {
        switch(port_num)
        {
            case PORTA_ID:
                if(PINA & (1 << pin_num))
                {
                    return LOGIC_HIGH;
                }
                else
                {
                    return LOGIC_LOW;
                }

                break;

            case PORTB_ID:
                if(PINB & (1 << pin_num))
                {
                    return LOGIC_HIGH;
                }
                else
                {
                    return LOGIC_LOW;
                }

                break;

            case PORTC_ID:
                if(PINC & (1 << pin_num))
                {
                    return LOGIC_HIGH;
                }
                else
                {
                    return LOGIC_LOW;
                }

                break;

            case PORTD_ID:
                if(PIND & (1 << pin_num))
                {
                    return LOGIC_HIGH;
                }
                else
                {
                    return LOGIC_LOW;
                }

                break;
        }
    }

    return 0;   /* Unreachable */
}

/*
*   Description:
*   Setup the direction of the required port (all pins) I/O
*/
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
    if(port_num >= NUM_OF_PORTS)
    {
        /*
            Do Nothing
        */
    }
    else
    {
        switch(port_num)
        {
            case PORTA_ID:
                DDRA = direction;
                break;

            case PORTB_ID:
                DDRB = direction;
                break;

            case PORTC_ID:
                DDRC = direction;
                break;

            case PORTD_ID:
                DDRD = direction;
                break;
        }
    }
}

/*
*   Description:
*   Write a value on the port (all pins)
*/
void GPIO_writePort(uint8 port_num, uint8 value)
{
    if(port_num >= NUM_OF_PORTS)
    {
        /*
            Do Nothing
        */
    }
    else
    {
        switch(port_num)
        {
            case PORTA_ID:
                PORTA = value;
                break;

            case PORTB_ID:
                PORTB = value;
                break;

            case PORTC_ID:
                PORTC = value;
                break;

            case PORTD_ID:
                PORTD = value;
                break;
        }
    }
}

/*
*   Description:
*   Read and return value of the port
*/
uint8 GPIO_readPort(uint8 port_num)
{
    if(port_num >= NUM_OF_PORTS)
    {
        /*
            Do Nothing
        */
    }
    else
    {
        switch(port_num)
        {
            case PORTA_ID:
                return PINA;
                break;

            case PORTB_ID:
                return PINB;
                break;

            case PORTC_ID:
                return PINC;
                break;

            case PORTD_ID:
                return PIND;
                break;
        }
    }

    return 0;   /* Unreachable */
}
