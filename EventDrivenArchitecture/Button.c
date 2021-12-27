/*
 * Button.c
 *
 * Created: 27/12/2021 11:46:11
 *  Author: Graham
 */ 

#include "Button.h"
#include "HardwareGpio.h"

//
//	Local #defines
//
#define DEBOUNCE_COUNT		5	// 50mS

//
//	Local functions
//
static void DebounceButtonOne(void);

//
//	Local variables
//
static eBoolean btn_button_is_pressed;
static tu8 btn_debounce_counter;

//
//	Initialises the module.
//
void BTN_Init(void)
{
	btn_button_is_pressed = False;
	btn_debounce_counter = DEBOUNCE_COUNT;
}

//
//	Processes events.
//
void BTN_EventProcessor(sEvent event)
{
	switch(event.id)
	{
		case Timer10MilliSecondsEvent:
			DebounceButtonOne();
			break;
		default:
			// no other events are processed by this module
			break;
	}
}

//
//	Process the button debouncing
//
static void DebounceButtonOne(void)
{
	const eGpioState NEW_STATE = HALG_GetButtonOneState();
	
	const eBoolean BUTTON_BEING_PRESSED = (((False == btn_button_is_pressed) && (Active == NEW_STATE)) ? True : False);
	const eBoolean BUTTON_BEING_RELEASED = (((True == btn_button_is_pressed) && (Inactive == NEW_STATE)) ? True : False);
	const eBoolean STATE_IS_CHANGING = (((True == BUTTON_BEING_PRESSED) || (True == BUTTON_BEING_RELEASED)) ? True : False);
	
	// is the state is the same then no need to do anything except reset the debounce counter
	if (False == STATE_IS_CHANGING)
	{
		btn_debounce_counter = DEBOUNCE_COUNT;
		return;
	}
	
	// state is different so debounce it
	if (0 == --btn_debounce_counter)
	{
		// debounce counter elapsed, so set the new state 
		btn_button_is_pressed = BUTTON_BEING_PRESSED;
		
		sEvent event;
		
		// set the event id
		event.id = (True == btn_button_is_pressed) ? ButtonPressedEvent : ButtonReleasedEvent;
		
		// post the event 
		EVTQ_PostEvent(event);
		
		// and reset the counter 
		btn_debounce_counter = DEBOUNCE_COUNT;
	}
}
