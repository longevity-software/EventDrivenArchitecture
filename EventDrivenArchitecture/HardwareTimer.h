/*
 * HardwareTimer.h
 *
 * Created: 27/12/2021 16:52:33
 *  Author: Graham
 */ 


#ifndef HARDWARETIMER_H_
#define HARDWARETIMER_H_


#include "GlobalDefinitions.h"
#include "EventQueue.h"

//
//	Public functions
//
extern void HALT_Init(void);
extern void HALT_EventProcessor(sEvent event);

#endif /* HARDWARETIMER_H_ */