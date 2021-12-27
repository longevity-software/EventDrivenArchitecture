/*
 * Atmega644PInterrupt.c
 *
 * Created: 27/12/2021 21:53:13
 *  Author: Graham
 */ 

#include "Atmega644PInterrupt.h"

#include <avr/interrupt.h>

//
// local type definitions 
//
typedef enum {NotEnabled, Enabled}eInterruptState;
	
static eInterruptState atm644pi_interrupt_state = NotEnabled;
static unsigned char atm644pi_pause_count = 0;

//
//	Enables interrupts and sets the local variables
//
void ATM644PI_EnableInterrupts(void)
{
	sei();
	
	atm644pi_pause_count = 0;
	atm644pi_interrupt_state = Enabled;	
}

//
//	Disables interrupts and sets the local variables
//
void ATM644PI_DisableInterrupts(void)
{
	cli();
	
	atm644pi_pause_count = 0;
	atm644pi_interrupt_state = NotEnabled;
}

//
//	Pauses interrupts if interrupts have been enabled.
//
void ATM644PI_PauseInterrupts(void)
{
	if (NotEnabled == atm644pi_interrupt_state)
	{
		// interrupts have not been enabled, so can't be paused
		return;	
	}
	
	// interrupts are enabled so can be paused
	cli();
		
	// we may be paused multiple times so keep count of how many
	atm644pi_pause_count++;
}

//
//	Resumes interrupts if all pauses have a matching resume.
//
void ATM644PI_ResumeInterrupts(void)
{
	if (0 == atm644pi_pause_count)
	{
		// we have not been paused so do not resume.
		return;
	}
	
	// does this call to resume, compliment all the calls to pause
	if (0 == --atm644pi_pause_count)
	{
		sei();
	}
}
