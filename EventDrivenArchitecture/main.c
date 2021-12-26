/*
 * main.c
 *
 * Created: 12/26/2021 7:24:45 PM
 *  Author: Graham
 */ 

#include "EventQueue.h"

#include <xc.h>

#define EVER ;;

int main(void)
{
	// Initialise the hardware 
	
	// and application modules.
	EVTQ_Init();
	
	// loop forever
    for(EVER)
    {
        //TODO:: Please write your application code 
    }
}