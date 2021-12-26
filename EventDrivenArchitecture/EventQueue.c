/*
 * EventQueue.c
 *
 * Created: 26/12/2021 19:55:17
 *  Author: Graham
 */ 

#include "EventQueue.h"

//
//	Initialises the event queue
//
void EVTQ_Init(void)
{
	
}

//
//	Gets the event which is at the top of the queue.
//
sEventRequestResult EVTQ_GetEvent(void)
{
	sEventRequestResult result;
	
	result.eventPresent = True;
	
	return result;
}