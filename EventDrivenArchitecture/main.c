/*
 * main.c
 *
 * Created: 12/26/2021 7:24:45 PM
 *  Author: Graham
 */ 

#include "HardwareGpio.h"

#include "EventQueue.h"
#include "button.h"

#include <xc.h>

#define EVER ;;

int main(void)
{
	// Initialise the hardware 
	HALG_Init();
	
	// and application modules.
	EVTQ_Init();
	BTN_Init();
	
	// loop forever
    for(EVER)
    {
		const sEventRequestResult EVENT = EVTQ_GetEvent();
		
		if (True == EVENT.eventPresent)
		{
			// event is present, so propogate it to all event processors.	
			BTN_EventProcessor(EVENT.event);
		}
    }
}