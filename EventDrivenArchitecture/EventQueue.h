/*
 * EventQueue.h
 *
 * Created: 26/12/2021 19:53:09
 *  Author: Graham
 */ 


#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_

#include "GlobalDefinitions.h"

typedef struct  
{
	eBoolean eventPresent;
}sEventRequestResult;

extern void EVTQ_Init(void);
extern sEventRequestResult EVTQ_GetEvent(void);



#endif /* EVENTQUEUE_H_ */