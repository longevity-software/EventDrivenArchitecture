/*
 * Indicators.c
 *
 * Created: 28/12/2021 19:13:32
 *  Author: Graham
 */ 

#include "Indicators.h"

#include "HardwareGpio.h"

//
//	Private defines
//
#define LED_FLASH_OFF_THRESHOLD		20	//	200mS
#define LED_FLASH_ON_THRESHOLD		100	//	1000mS

//
//	Private functions
//
static void StateIndicatorOffEventProcessor(sEvent event);
static void StateIndicatorOnEventProcessor(sEvent event);

//
//	Private variables
//
static void (*indc_state_machine_function_ptr)(sEvent);
static tu8 indc_led_flash_counter;

//
//	Module Initialisation function
//
void INDC_Init(void)
{
	// set the initial state to off
	indc_state_machine_function_ptr = StateIndicatorOffEventProcessor;
	
	// Ensure the LED is off 
	HALG_SetLedOneState(Inactive);
	
	// and the counter is cleared.
	indc_led_flash_counter = 0;
}

//
//	Event processor
//
void INDC_EventProcessor(sEvent event)
{
	// call the current state function to process the event
	indc_state_machine_function_ptr(event);
}

//
//	Off state, event processor
//
static void StateIndicatorOffEventProcessor(sEvent event)
{
	// in the off state, we need to look for a transition to the on state.
	switch(event.id)
	{
		case ButtonPressedEvent:
			// button has been pressed, so change state to on.
			indc_state_machine_function_ptr = StateIndicatorOnEventProcessor;
			// Clear the counter which times the flash rate
			indc_led_flash_counter = 0;
			// and set the LED on 
			HALG_SetLedOneState(Active);
			break;
		default:
			// no other events need to be processed.
			break;
	}
}

//
//	On state, event processor
//
static void StateIndicatorOnEventProcessor(sEvent event)
{
	// in the off state, we need to look for a transition to the on state.
	switch(event.id)
	{
		case ButtonReleasedEvent:
			// button has been released, so change state to off.
			indc_state_machine_function_ptr = StateIndicatorOffEventProcessor;
			// Ensure the LED is off
			HALG_SetLedOneState(Inactive);
			break;
		case Timer10MilliSecondsEvent:
			// timer has elapsed so update flash counter
			indc_led_flash_counter++;
			// and check if the led state should be changed
			if (LED_FLASH_OFF_THRESHOLD == indc_led_flash_counter)
			{
				HALG_SetLedOneState(Inactive);
			}
			else if (LED_FLASH_ON_THRESHOLD == indc_led_flash_counter) 
			{
				HALG_SetLedOneState(Active);
				indc_led_flash_counter = 0;
			}
			break;
		default:
			// no other events need to be processed.
			break;
	}	
}
