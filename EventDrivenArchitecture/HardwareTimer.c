/*
 * HardwareTimer.c
 *
 * Created: 27/12/2021 16:53:32
 *  Author: Graham
 */ 

#include "HardwareTimer.h"
#include "HardwareInterrupt.h"

#include "Atmega644PTimer.h"

//
//	Local Functions
//
static void TimerInterruptServiceRoutine(void);

//
//	Local Variables
//
static volatile eBoolean halt_timer_event_unprocessed;

//
//	Initialises the Timers
//
void HALT_Init(void)
{
	// Initialise the underlying device specific driver
	ATM644PT_InitTimerFor10mS();
	
	// set the function to service the timer interrupt.
	ATM644PT_SetfunctionToCallAt10MillisecondInterval(TimerInterruptServiceRoutine);
	
	// no timer events have been posted so events can't be unprocessed.
	halt_timer_event_unprocessed = False;
}

//
//	Event Processing function, confirms that each timer event is processed before the next is posted.
//
void HALT_EventProcessor(sEvent event)
{
	switch(event.id)
	{
		case Timer10MilliSecondsEvent:
			HALI_PauseInterrupts();
			// this event is being processed so clear the unprocessed flag with interrupts paused.
			halt_timer_event_unprocessed = False;
			HALI_ResumeInterrupts();
			break;
		default:
			// no other events are processed by this module
			break;
	}	
}

//
// function to be called under timer interrupt.
//
static void TimerInterruptServiceRoutine(void)
{
	if (True == halt_timer_event_unprocessed)
	{
		// TODO - timer overrun so raise error.
		return;
	}
	
	sEvent event;
	event.id = Timer10MilliSecondsEvent;
	
	EVTQ_PostEvent(event);
	
	// timer event has been posted so set flag to indicate that it is yet to be processed.
	halt_timer_event_unprocessed = True;
}
