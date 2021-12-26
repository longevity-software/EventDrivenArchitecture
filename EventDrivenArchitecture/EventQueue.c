/*
 * EventQueue.c
 *
 * Created: 26/12/2021 19:55:17
 *  Author: Graham
 */ 

#include "EventQueue.h"

//
//	Local #defines
//
#define MAX_EVENTS		10

//
//	Static variables
//
static sEvent evtq_events[MAX_EVENTS];

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
}

//
//	Gets the event which is at the top of the queue.
//
sEventRequestResult EVTQ_GetEvent(void)
{
	sEventRequestResult result;
	
	result.eventPresent = False;
	
	return result;
}

//
//	Posts and event to the bottom of the queue.
//
void EVTQ_PostEvent(eEventId id)
{
	
}