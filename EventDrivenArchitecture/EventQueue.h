/*
 * EventQueue.h
 *
 * Created: 26/12/2021 19:53:09
 *  Author: Graham
 */ 


#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_

#include "GlobalDefinitions.h"

typedef enum _EVENT_ID
{
	NoEvent,
	TestEvent
}eEventId;

typedef struct _EVENT
{
	eEventId id;
}sEvent;

typedef struct  
{
	eBoolean eventPresent;
	sEvent event;
}sEventRequestResult;

extern void EVTQ_Init(void);
extern sEventRequestResult EVTQ_GetEvent(void);
extern void EVTQ_PostEvent(eEventId id);



#endif /* EVENTQUEUE_H_ */