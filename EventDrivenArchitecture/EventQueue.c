/*
 * EventQueue.c
 *
 * Created: 26/12/2021 19:55:17
 *  Author: Graham
 */ 

#include "EventQueue.h"

#include "HardwareInterrupt.h"

//
//	Local #defines
//
#ifdef TEST		// for unit testing, ensure that the MAX EVENTS is fixed.
#define MAX_EVENTS		10
#else
#define MAX_EVENTS		20
#endif

//
//	Static variables
//
static volatile sEvent evtq_events[MAX_EVENTS];
static volatile tu8 evtq_event_ip;
static tu8 evtq_event_op;
static volatile tu8 evtq_event_count;
static volatile tu8 evtq_event_highwater;

//
//	Initialises the event queue
//
void EVTQ_Init(void)
{
	int i;
	
	// Initialise all events to NoEvent
	for (i = 0; i < MAX_EVENTS; ++i)
	{
		evtq_events[i].id = NoEvent;
	}
	
	evtq_event_ip = 0;
	evtq_event_op = 0;
	evtq_event_count = 0;
	evtq_event_highwater = 0;
}

//
//	Gets the event which is at the top of the queue.
//
sEventRequestResult EVTQ_GetEvent(void)
{	
	// event queue can be modified under interrupt, so pause interrupts while checking it.
	HALI_PauseInterrupts();
	
	sEventRequestResult result;		
	
	if (0 == evtq_event_count)
	{
		result.eventPresent = False;
		result.event.id = NoEvent;
	
		// be sure to resume the paused interrupts
		HALI_ResumeInterrupts();
	
		return result;
	}
	
	result.eventPresent = True;
	result.event = evtq_events[evtq_event_op++];
	
	// wrap back to 0
	if (MAX_EVENTS == evtq_event_op)
	{
		evtq_event_op = 0;
	}
	
	// update count for this event
	evtq_event_count--;
	
	// be sure to resume the paused interrupts
	HALI_ResumeInterrupts();
	
	return result;
}

//
//	Posts and event to the bottom of the queue.
//
eBoolean EVTQ_PostEvent(sEvent event)
{
	// pause interrupts, as events can be posted under interrupt
	HALI_PauseInterrupts();
	
	if (evtq_event_count == MAX_EVENTS)
	{
		// be sure to resume the paused interrupts
		HALI_ResumeInterrupts();
		
		// no space so return false
		return False;	
	}
	
	evtq_events[evtq_event_ip++] = event;
	
	// wrap back to 0
	if (MAX_EVENTS == evtq_event_ip)
	{
		evtq_event_ip = 0;
	}
	
	// update count for this event
	evtq_event_count++;
	
	// check if the high water level needs adjusting.
	if (evtq_event_count > evtq_event_highwater)
	{
		evtq_event_highwater = evtq_event_count;
	}
	
	// be sure to resume the paused interrupts
	HALI_ResumeInterrupts();
	
	return True;
}

//
//	returns the current high water level.
//
tu8 EVTQ_GetHighWaterLevel(void)
{
	// High Water level can be modified under interrupt, so pause interrupts while getting the value
	HALI_PauseInterrupts();
	
	const tu8 LEVEL = evtq_event_highwater;
	
	// be sure to resume the paused interrupts
	HALI_ResumeInterrupts();
	
	return LEVEL;
}