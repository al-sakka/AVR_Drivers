/******************************************************************************
*
* Module: Timer
*
* File Name: timer.h
*
* Description: Header file for the Timer driver
*
* Author: Abdallah El-Sakka
*
*******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "../../Utils/std_types.h"

/*******************************************************************************
*                                Definitions                                  *
*******************************************************************************/

typedef enum
{
	TIMER0,
	TIMER1,
	TIMER2

} Timer_ID;


typedef enum
{
	NO_CLK,
	F_CPU_CLK,

	/* TIMER0/1 Clock Modes */
	F_CPU_CLK_8,
	F_CPU_CLK_64,
	F_CPU_CLK_256,
	F_CPU_CLK_1024,
	Extern_Falling,
	Extern_Rising,

	/* TIMER2 Clock Modes */
    T2_CLK_8 = 2,
    T2_CLK_32,
    T2_CLK_64,
    T2_CLK_128,
    T2_CLK_256,
    T2_CLK_1024

} Timer_Clock;

typedef enum
{
	NORMAL_MODE,
	COMPARE_MODE

} Timer_Mode;

typedef struct
{
	Timer_ID timer_ID;
	uint16 timer_InitialValue;
	Timer_Clock timer_clock;
	Timer_Mode timer_mode;
	uint16 timer_compare_MatchValue;	/* Will be used in compare mode only*/

} Timer_ConfigType;

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*
 * Description: Function to initialize the Timer driver
 */
void Timer_init(const Timer_ConfigType * Config_Ptr);

/*
 * Description: Function to disable the Timer via Timer_ID.
 */
void Timer_deInit(Timer_ID a_timer_type);

/*
 * Description: Function to set the Call Back function address to the required Timer.
 */
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID a_timer_ID);

#endif  /* TIMER_H_ */
