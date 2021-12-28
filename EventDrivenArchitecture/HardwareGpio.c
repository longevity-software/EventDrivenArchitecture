/*
 * HardwareGpio.c
 *
 * Created: 27/12/2021 12:01:49
 *  Author: Graham
 */ 

#include "HardwareGpio.h"
#include "Atmega644PGpio.h"

//
//	Local definitions
//
#define LED_PIN			1
#define BUTTON_PIN		2

//
//	Initialises the GPIOs 
//
void HALG_Init(void)
{
	// Set the appropriate pin directions
	ATM644PG_SetPinAsOutput(LED_PIN);
	ATM644PG_SetPinAsInput(BUTTON_PIN);	
}

//
//	Gets the current state of button one
//
eGpioState HALG_GetButtonOneState(void)
{
	eGetPinLevelStruct pinState = ATM644PG_GetPinLevel(BUTTON_PIN);
	
	// button 1 is active low
	return (pinState.level == LOW) ? Active : Inactive;
}
