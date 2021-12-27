/*
 * Atmega644PInterrupt.h
 *
 * Created: 27/12/2021 21:52:59
 *  Author: Graham
 */ 


#ifndef ATMEGA644PINTERRUPT_H_
#define ATMEGA644PINTERRUPT_H_

//
//	Public functions
//
extern void ATM644PI_EnableInterrupts(void);
extern void ATM644PI_DisableInterrupts(void);
extern void ATM644PI_PauseInterrupts(void);
extern void ATM644PI_ResumeInterrupts(void);

#endif /* ATMEGA644PINTERRUPT_H_ */