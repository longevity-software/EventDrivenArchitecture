/*
 * Atmega644PTimer.c
 *
 * Created: 27/12/2021 20:49:55
 *  Author: Graham
 */ 

#include "Atmega644PTimer.h"

#include <xc.h>
#include <avr/interrupt.h>

//
//	Local #defines
//
#define CLEAR_TIMER_ON_COMPARE_MATCH			0x02
#define CLOCK_DIVIDED_BY_1024					0x05
#define TIMER_COMPARE_MATCH_INTERRUPT_ENABLE	0x02

#define OUTPUT_COMPARE_VALUE			78

//
//	Local functions
//
static void NullFunction(void);

//
//	Local variables
//
static void (*InterruptServiceRoutine)(void);

//
//	Module Initialisation function
//
void ATM644PT_InitTimerFor10mS(void)
{
	// set up timer interrupt
	TCCR0A = CLEAR_TIMER_ON_COMPARE_MATCH;
	TCCR0B = CLOCK_DIVIDED_BY_1024;
	TIMSK0 = TIMER_COMPARE_MATCH_INTERRUPT_ENABLE;
		
	OCR0A = OUTPUT_COMPARE_VALUE;
	
	// set the interrupt service routine to our Null function
	InterruptServiceRoutine = NullFunction;
}

//
//	sets the function called under interrupt by the timer
//
void ATM644PT_SetfunctionToCallAt10MillisecondInterval(void (*function_ptr)(void))
{
	// check for null
	if ((void*)0 == function_ptr)
	{
		// set actual Interrupt Service Routine to our Null function.
		InterruptServiceRoutine = NullFunction;
		return;	
	}
	
	// Not null so set it.
	InterruptServiceRoutine = function_ptr;
}

//
//	Null function which intentionally does nothing, to be called if no other function has been set.
//
static void NullFunction(void)
{
	// intentionally do nothing.
}

// name:	ISR(TIMER0_COMPA_vect)
// Desc:	timer 0 compare match A interrupt.
ISR(TIMER0_COMPA_vect)
{
	InterruptServiceRoutine();
}
