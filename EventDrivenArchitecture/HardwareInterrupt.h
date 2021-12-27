/*
 * HardwareInterrupt.h
 *
 * Created: 27/12/2021 21:14:21
 *  Author: Graham
 */ 


#ifndef HARDWAREINTERRUPT_H_
#define HARDWAREINTERRUPT_H_

//
//	Public functions
//
extern void HALI_EnableInterrupts(void);
extern void HALI_DisableInterrupts(void);
extern void HALI_PauseInterrupts(void);
extern void HALI_ResumeInterrupts(void);

#endif /* HARDWAREINTERRUPT_H_ */