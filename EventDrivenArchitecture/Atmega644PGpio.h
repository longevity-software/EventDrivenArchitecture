/*
 * Atmega644PGpio.h
 *
 * Created: 28/12/2021 09:59:11
 *  Author: Graham
 */ 

#ifndef ATMEGA644PGPIO_H_
#define ATMEGA644PGPIO_H_

//
//	Public types
//
typedef enum _PIN_LEVEL
{
	LOW, 
	HIGH
}ePinLevel;

typedef enum _SET_DIRECTION_RESULT
{
	DIRECTION_OK,
	DIRECTION_INVALID_PIN,
	DIRECTION_PIN_IS_NOT_USABLE_AS_GPIO
}eSetPinDirectionResult;

typedef enum _SET_LEVEL_RESULT
{
	SET_LEVEL_OK, 
	SET_LEVEL_INVALID_PIN,
	SET_LEVEL_PIN_IS_NOT_OUTPUT
}eSetPinLevelResult;

typedef enum _GET_LEVEL_RESULT
{
	GET_LEVEL_OK,
	GET_LEVEL_INVALID_PIN,
	GET_LEVEL_PIN_IS_NOT_INPUT		
}eGetPinLevelResult;

typedef struct _GET_LEVEL_STRUCT
{
	eGetPinLevelResult result;
	ePinLevel level;
}eGetPinLevelStruct;
//
//	Public functions
//
extern eSetPinDirectionResult ATM644PG_SetPinAsOutput(unsigned char pinNumber);
extern eSetPinDirectionResult ATM644PG_SetPinAsInput(unsigned char pinNumber);
extern eSetPinLevelResult ATM644PG_SetPinLevel(unsigned char pinNumber, ePinLevel level);
extern eGetPinLevelStruct ATM644PG_GetPinLevel(unsigned char pinNumber);

#endif /* ATMEGA644PGPIO_H_ */
