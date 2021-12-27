/*
 * EventQueue.h
 *
 * Created: 26/12/2021 19:53:09
 *  Author: Graham
 */ 


#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_

#include "GlobalDefinitions.h"

// List of all possible events
typedef enum _EVENT_ID
{
	NoEvent,
	TestEvent,
	Timer10MilliSecondsEvent,
	ButtonPressedEvent,
	ButtonReleasedEvent
}eEventId;

// Made this a structure so that it can be easily expanded to add values or priority etc.
typedef struct _EVENT
{
	eEventId id;
}sEvent;

// structure returned from the EVTQ_GetEvent function
typedef struct  
{
	eBoolean eventPresent;
	sEvent event;
}sEventRequestResult;

//
//	Public functions
//
extern void EVTQ_Init(void);
extern sEventRequestResult EVTQ_GetEvent(void);
extern eBoolean EVTQ_PostEvent(sEvent event);
extern tu8 EVTQ_GetHighWaterLevel(void);



#endif /* EVENTQUEUE_H_ */