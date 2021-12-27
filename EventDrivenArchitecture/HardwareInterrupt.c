/*
 * HardwareInterrupt.c
 *
 * Created: 27/12/2021 21:14:03
 *  Author: Graham
 */ 

#include "HardwareInterrupt.h"
#include "Atmega644PInterrupt.h"

//
//	Calls the device specific function to enable interrupts
//
void HALI_EnableInterrupts(void)
{
	ATM644PI_EnableInterrupts();
}

//
//	Calls the device specific function to disable interrupts
//
void HALI_DisableInterrupts(void)
{
	ATM644PI_DisableInterrupts();
}

//
//	Calls the device specific function to pause interrupts
//
void HALI_PauseInterrupts(void)
{
	ATM644PI_PauseInterrupts();
}

//
//	Calls the device specific function to resume interrupts
//
void HALI_ResumeInterrupts(void)
{
	ATM644PI_ResumeInterrupts();
}
