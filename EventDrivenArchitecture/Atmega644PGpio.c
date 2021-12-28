/*
 * Atmega644PGpio.c
 *
 * Created: 28/12/2021 09:59:27
 *  Author: Graham
 */ 

#include "Atmega644PGpio.h"

#include <xc.h>

//
//	Private #defines
//
#define PIN_IS_NOT_GPIO		0x00
#define PIN_IS_GPIO			0x01
#define PIN_CONFIGURED		0x02
#define PIN_IS_OUTPUT		0x04
#define PIN_SET_HIGH		0x08

#define MAX_PINS		40

#define ACCESS_REGISTER(x)		_SFR_IO8(x)

//
//	Private types
//
typedef unsigned char PIN_CONFIG;

typedef struct _PIN_DEFINITIONS
{
	PIN_CONFIG config;
	unsigned char directionRegister;
	unsigned char outputRegister;
	unsigned char inputRegister;
	unsigned char pinMask;
}sPinDefinitions;

//
//	Private variables
//
static sPinDefinitions pinConfigurations[MAX_PINS] = {
	{PIN_IS_GPIO, 0x04, 0x05, 0x03, 0x01},
	{PIN_IS_GPIO, 0x04, 0x05, 0x03, 0x02},
	{PIN_IS_GPIO, 0x04, 0x05, 0x03, 0x04},
	{PIN_IS_GPIO, 0x04, 0x05, 0x03, 0x08},
	{PIN_IS_GPIO, 0x04, 0x05, 0x03, 0x10},
	{PIN_IS_GPIO, 0x04, 0x05, 0x03, 0x20},
	{PIN_IS_GPIO, 0x04, 0x05, 0x03, 0x40},
	{PIN_IS_GPIO, 0x04, 0x05, 0x03, 0x80},
	{PIN_IS_NOT_GPIO, 0x00, 0x00, 0x00, 0x00},
	{PIN_IS_NOT_GPIO, 0x00, 0x00, 0x00, 0x00},
	{PIN_IS_NOT_GPIO, 0x00, 0x00, 0x00, 0x00},
	{PIN_IS_NOT_GPIO, 0x00, 0x00, 0x00, 0x00},
	{PIN_IS_NOT_GPIO, 0x00, 0x00, 0x00, 0x00},
	{PIN_IS_GPIO, 0x0A, 0x0B, 0x09, 0x01},
	{PIN_IS_GPIO, 0x0A, 0x0B, 0x09, 0x02},
	{PIN_IS_GPIO, 0x0A, 0x0B, 0x09, 0x04},
	{PIN_IS_GPIO, 0x0A, 0x0B, 0x09, 0x08},
	{PIN_IS_GPIO, 0x0A, 0x0B, 0x09, 0x10},
	{PIN_IS_GPIO, 0x0A, 0x0B, 0x09, 0x20},
	{PIN_IS_GPIO, 0x0A, 0x0B, 0x09, 0x40},
	{PIN_IS_GPIO, 0x0A, 0x0B, 0x09, 0x80},
	{PIN_IS_GPIO, 0x07, 0x08, 0x06, 0x01},
	{PIN_IS_GPIO, 0x07, 0x08, 0x06, 0x02},
	{PIN_IS_GPIO, 0x07, 0x08, 0x06, 0x04},
	{PIN_IS_GPIO, 0x07, 0x08, 0x06, 0x08},
	{PIN_IS_GPIO, 0x07, 0x08, 0x06, 0x10},
	{PIN_IS_GPIO, 0x07, 0x08, 0x06, 0x20},
	{PIN_IS_GPIO, 0x07, 0x08, 0x06, 0x40},
	{PIN_IS_GPIO, 0x07, 0x08, 0x06, 0x80},
	{PIN_IS_NOT_GPIO, 0x00, 0x00, 0x00, 0x00},
	{PIN_IS_NOT_GPIO, 0x00, 0x00, 0x00, 0x00},
	{PIN_IS_NOT_GPIO, 0x00, 0x00, 0x00, 0x00},
	{PIN_IS_GPIO, 0x01, 0x02, 0x0, 0x01},
	{PIN_IS_GPIO, 0x01, 0x02, 0x00, 0x02},
	{PIN_IS_GPIO, 0x01, 0x02, 0x00, 0x04},
	{PIN_IS_GPIO, 0x01, 0x02, 0x00, 0x08},
	{PIN_IS_GPIO, 0x01, 0x02, 0x00, 0x01},
	{PIN_IS_GPIO, 0x01, 0x02, 0x00, 0x02},
	{PIN_IS_GPIO, 0x01, 0x02, 0x00, 0x04},
	{PIN_IS_GPIO, 0x01, 0x02, 0x00, 0x08}
};

//
//	Sets the passed pin as an output
//
eSetPinDirectionResult ATM644PG_SetPinAsOutput(unsigned char pinNumber)
{
	if (pinNumber > MAX_PINS)
	{
		return DIRECTION_INVALID_PIN;
	}
	
	// subtract 1 as array is 0 indexed.
	pinNumber -= 1;
	
	if (PIN_IS_GPIO != (pinConfigurations[pinNumber].config & PIN_IS_GPIO))
	{
		// pin is not a GPIO 
		return DIRECTION_PIN_IS_NOT_USABLE_AS_GPIO;
	}
	
	// all looks good, so set the direction as output by setting the bit
	ACCESS_REGISTER(pinConfigurations[pinNumber].directionRegister) |= pinConfigurations[pinNumber].pinMask;
	
	// update the pin configuration
	pinConfigurations[pinNumber].config |= (PIN_CONFIGURED | PIN_IS_OUTPUT);
	
	return DIRECTION_OK;
}

//
//	Sets the passed pin as an input
//
eSetPinDirectionResult ATM644PG_SetPinAsInput(unsigned char pinNumber)
{
	if (pinNumber > MAX_PINS)
	{
		return DIRECTION_INVALID_PIN;
	}
		
	// subtract 1 as array is 0 indexed.
	pinNumber -= 1;
		
	if (PIN_IS_GPIO != (pinConfigurations[pinNumber].config & PIN_IS_GPIO))
	{
		// pin is not a GPIO
		return DIRECTION_PIN_IS_NOT_USABLE_AS_GPIO;
	}
		
	// all looks good, so set the direction as input by clearing the bit
	ACCESS_REGISTER(pinConfigurations[pinNumber].directionRegister) &= ~pinConfigurations[pinNumber].pinMask;
	
	// update the pin configuration
	pinConfigurations[pinNumber].config |= (PIN_CONFIGURED);
	
	return DIRECTION_OK;
}

//
//	Sets a pin as long as it is configured as an output
//
eSetPinLevelResult ATM644PG_SetPinLevel(unsigned char pinNumber, ePinLevel level)
{
	if (pinNumber > MAX_PINS)
	{
		return SET_LEVEL_INVALID_PIN;
	}
	
	// subtract 1 as array is 0 indexed.
	pinNumber -= 1;
	
	const PIN_CONFIG REQUIRED_CONFIG = (PIN_IS_GPIO | PIN_CONFIGURED | PIN_IS_OUTPUT);
	
	if (REQUIRED_CONFIG != (pinConfigurations[pinNumber].config & REQUIRED_CONFIG))
	{
		// pin is not configured as an output
		return SET_LEVEL_PIN_IS_NOT_OUTPUT;
	}
	 
	// set the output to the required level.
	if (HIGH == level)
	{
		ACCESS_REGISTER(pinConfigurations[pinNumber].outputRegister) |= pinConfigurations[pinNumber].pinMask;
	}
	else
	{
		ACCESS_REGISTER(pinConfigurations[pinNumber].outputRegister) &= ~pinConfigurations[pinNumber].pinMask;
	}
	
	return SET_LEVEL_OK;
}

//
//	Gets the level of a pin.
//
eGetPinLevelStruct ATM644PG_GetPinLevel(unsigned char pinNumber)
{
	eGetPinLevelStruct result;
	
	if (pinNumber > MAX_PINS)
	{
		result.result = GET_LEVEL_INVALID_PIN;
		result.level = LOW;
		
		return result;
	}

	// subtract 1 as array is 0 indexed.
	pinNumber -= 1;

	const PIN_CONFIG REQUIRED_CONFIG = (PIN_IS_GPIO | PIN_CONFIGURED);
	const PIN_CONFIG EXCLUDED_CONFIG = (PIN_IS_OUTPUT);

	if	(
			(REQUIRED_CONFIG != (pinConfigurations[pinNumber].config & REQUIRED_CONFIG))		// pin is not a configured GPIO
			|| (EXCLUDED_CONFIG == (pinConfigurations[pinNumber].config & EXCLUDED_CONFIG))		// or it is an output.
		)
	{
		// pin does not have the required configuration
		result.result = GET_LEVEL_PIN_IS_NOT_INPUT;
		result.level = LOW;
		
		return result;
	}

	result.result = GET_LEVEL_OK;
	result.level = ((pinConfigurations[pinNumber].pinMask == (ACCESS_REGISTER(pinConfigurations[pinNumber].inputRegister) & pinConfigurations[pinNumber].pinMask))
						? HIGH
						: LOW
					);
					
	return result;
}
