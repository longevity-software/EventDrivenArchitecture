/*
 * HardwareGpio.h
 *
 * Created: 27/12/2021 12:01:33
 *  Author: Graham
 */ 


#ifndef HARDWAREGPIO_H_
#define HARDWAREGPIO_H_


#include "GlobalDefinitions.h"

//
//	Public types
//
typedef enum _GPIO_STATE{Inactive, Active}eGpioState;
	
//
//	Public functions
//
extern void HALG_Init(void);
extern eGpioState HALG_GetButtonOneState(void);

#endif /* HARDWAREGPIO_H_ */