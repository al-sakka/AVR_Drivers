/******************************************************************************
*
* Module: Timer
*
* File Name: timer.c
*
* Description: Source file for the Timer driver
*
* Author: Abdallah El-Sakka
*
*******************************************************************************/

#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*******************************************************************************
*                                Definitions                                  *
*******************************************************************************/

/* Callbacks for each timer */
static volatile void (*g_timer0_callBackPtr)(void) = (NULL_PTR);
static volatile void (*g_timer1_callBackPtr)(void) = (NULL_PTR);
static volatile void (*g_timer2_callBackPtr)(void) = (NULL_PTR);

/*******************************************************************************
*                       Interrupt Service Routines                            *
*******************************************************************************/

/* Timer0 ISRs */
ISR(TIMER0_OVF_vect)
{
	if((g_timer0_callBackPtr) != (NULL_PTR)) (*g_timer0_callBackPtr)();
}

ISR(TIMER0_COMP_vect)
{
	if((g_timer0_callBackPtr) != (NULL_PTR)) (*g_timer0_callBackPtr)();
}

/* Timer1 ISRs */
ISR(TIMER1_OVF_vect)
{
	if((g_timer1_callBackPtr) != (NULL_PTR)) (*g_timer1_callBackPtr)();
}

ISR(TIMER1_COMPA_vect)
{
	if((g_timer1_callBackPtr) != (NULL_PTR)) (*g_timer1_callBackPtr)();
}

/* Timer2 ISRs */
ISR(TIMER2_OVF_vect)
{
	if((g_timer2_callBackPtr) != (NULL_PTR)) (*g_timer2_callBackPtr)();
}

ISR(TIMER2_COMP_vect)
{
	if((g_timer2_callBackPtr) != (NULL_PTR)) (*g_timer2_callBackPtr)();
}

/*******************************************************************************
 *                      Functions Definitions                                  *
*******************************************************************************/

/*
 * Description: Function to initialize the Timer driver
 */
void Timer_init(const Timer_ConfigType * Config_Ptr)
{
	switch(Config_Ptr->timer_ID)
	{
		case TIMER0:
			TCCR0 = (Config_Ptr->timer_mode == NORMAL_MODE) ? (1 << FOC0) : ((1 << FOC0) | (1 << WGM01));
			OCR0 = (Config_Ptr->timer_compare_MatchValue);
			TCNT0 = (Config_Ptr->timer_InitialValue);
			TCCR0 |= (Config_Ptr->timer_clock);
			TIMSK |= (Config_Ptr->timer_mode == NORMAL_MODE) ? (1 << TOIE0) : (1 << OCIE0);
			break;

		case TIMER1:
			TCCR1A = (1 << FOC1A);
			TCCR1B = (Config_Ptr->timer_mode == COMPARE_MODE) ? (1 << WGM12) | (Config_Ptr->timer_clock) : (Config_Ptr->timer_clock) ;
			OCR1A = (Config_Ptr->timer_compare_MatchValue);
			TIMSK |= (Config_Ptr->timer_mode == NORMAL_MODE) ? (1 << TOIE1) : (1 << OCIE1A) ;
			TCNT1 = (Config_Ptr->timer_InitialValue);
			break;

		case TIMER2:
			TCCR2 = (Config_Ptr->timer_mode == NORMAL_MODE) ? (1 << FOC2) : ((1 << FOC2) | (1 << WGM21));
			OCR2 = (Config_Ptr->timer_compare_MatchValue);
			TCNT2 = (Config_Ptr->timer_InitialValue);
			TCCR2 |= (Config_Ptr->timer_clock);
			TIMSK |= (Config_Ptr->timer_mode == NORMAL_MODE) ? (1 << TOIE2) : (1 << OCIE2) ;
			break;
	}
}

/*
 * Description: Function to disable the Timer via Timer_ID.
 */
void Timer_deInit(Timer_ID a_timer_type)
{
	switch(a_timer_type)
	{
		case TIMER0:
			TCCR0 = 0;
			TIMSK &= ~((1 << TOIE0) | (1 << OCIE0));
			break;

		case TIMER1:
			TCCR1A = 0;
			TCCR1B = 0;
			TIMSK &= ~((1 << TOIE1) | (1 << OCIE1A));
			break;

		case TIMER2:
			TCCR2 = 0;
			TIMSK &= ~((1 << TOIE2) | (1 << OCIE2));
			break;
	}
}

/*
 * Description: Function to set the Call Back function address to the required Timer.
 */
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID a_timer_ID)
{
	switch(a_timer_ID)
	{
		case TIMER0:
			g_timer0_callBackPtr = (a_ptr);
			break;
		case TIMER1:
			g_timer1_callBackPtr = (a_ptr);
			break;
		case TIMER2:
			g_timer2_callBackPtr = (a_ptr);
			break;
	}
}



