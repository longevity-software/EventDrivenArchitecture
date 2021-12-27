/*
 * button.h
 *
 * Created: 27/12/2021 11:42:45
 *  Author: Graham
 */ 

#ifndef BUTTON_H_
#define BUTTON_H_

#include "GlobalDefinitions.h"
#include "EventQueue.h"

//
//	Public functions
//
extern void BTN_Init(void);
extern void BTN_EventProcessor(sEvent event);

#endif /* BUTTON_H_ */