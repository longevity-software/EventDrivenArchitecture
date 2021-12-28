/*
 * main.c
 *
 * Created: 12/26/2021 7:24:45 PM
 *  Author: Graham
 */ 

#include "HardwareGpio.h"
#include "HardwareTimer.h"
#include "HardwareInterrupt.h"

#include "EventQueue.h"
#include "button.h"
#include "Indicators.h"

#define EVER ;;

int main(void)
{
	// Initialise the hardware 
	HALG_Init();
	HALT_Init();
	
	// and application modules.
	EVTQ_Init();
	BTN_Init();
	INDC_Init();
	
	// all Initialisation is done, so enable interrupts
	HALI_EnableInterrupts();
	
	// loop forever
    for(EVER)
    {
		const sEventRequestResult EVENT = EVTQ_GetEvent();
		
		if (True == EVENT.eventPresent)
		{
			// event is present, so propagate it to all event processors.	
			BTN_EventProcessor(EVENT.event);
			INDC_EventProcessor(EVENT.event);
			HALT_EventProcessor(EVENT.event);
		}
    }
}