#ifndef _api_H_
#define _api_H_

#include  "../header/halGPIO.h"     // private library - HAL layer


extern void printSWs2LEDs(void);
extern void printArr2SWs(char Arr[], int size, unsigned int rate);
extern void Timer_A0_On(void);
extern void Timer_A0_Off(void);
extern void KeyPadReady(void);
extern void Swap(int i , int j) ;
extern void func3(void) ;
extern void Print_Mat(void) ;





#endif







