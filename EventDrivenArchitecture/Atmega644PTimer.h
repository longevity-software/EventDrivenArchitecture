/*
 * Atmega644PTimer.h
 *
 * Created: 27/12/2021 20:49:40
 *  Author: Graham
 */ 


#ifndef ATMEGA644PTIMER_H_
#define ATMEGA644PTIMER_H_

//
//	Public functions
//
extern void ATM644PT_InitTimerFor10mS(void);
extern void ATM644PT_SetfunctionToCallAt10MillisecondInterval(void (*function_ptr)(void));


#endif /* ATMEGA644PTIMER_H_ */