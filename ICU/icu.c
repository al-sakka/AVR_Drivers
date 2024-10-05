/******************************************************************************
*
* Module: ICU
*
* File Name: icu.c
*
* Description: Source file for the ICU driver
*
* Author: Abdallah El-Sakka
*
*******************************************************************************/

#include "icu.h"
#include "../GPIO/gpio.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*******************************************************************************
*                           Global Variables                                  *
*******************************************************************************/

/*
 * Global variable to hold the address of the call back function in the application
 */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
*                       Interrupt Service Routines                            *
*******************************************************************************/

ISR(TIMER1_CAPT_vect)
{
    if(g_callBackPtr != (NULL_PTR))
    {
        /* call the callBack function after edge is detected */
        (*g_callBackPtr)();
    }
}

/*******************************************************************************
*                      Functions Definitions                                  *
*******************************************************************************/

/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_init(const ICU_ConfigType* Config_Ptr)
{
    GPIO_setupPinDirection(ICP1_PORT_ID, ICP1_PIN_ID, PIN_INPUT);

    /* Set Timer1 in Normal Mode */
    TCCR1A = (1 << FOC1A) | (1 << FOC1B);

    /* Insert Required Clock */
    TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock);

    /* Insert Required Edge */
    TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->edge) << ICES1);

    /* Initialize Timer1 */
    TCNT1 = (0x00);

    /* Initialize value for IC Register */
    ICR1 = (0x00);

    /* Enable IC Interrupt */
    SET_BIT(TIMSK, TICIE1);
}

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBack(void(*a_ptr)(void))
{
    g_callBackPtr = (a_ptr);
}

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const ICU_EdgeType a_edgeType)
{
    /* Insert Required Edge */
    TCCR1B = (TCCR1B & 0xBF) | ((a_edgeType) << (ICES1));
}

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void)
{
    return (ICR1);
}

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void)
{
    TCNT1 = (0x00);
}

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_deInit(void)
{
    /* Clear Timer1 Registers */
    TCCR1A = (0x00);
    TCCR1B = (0x00);
    TCNT1  = (0x00);
    ICR1   = (0x00);

    /* Disable IC Interrupt */
    CLEAR_BIT(TIMSK, TICIE1);

    /* Reset callBack function */
    g_callBackPtr = (NULL_PTR);
}