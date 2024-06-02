#ifndef _app_H_
#define _app_H_


enum FSMstate{state0,state1,state2,state3,state4}; // global variable
enum SYSmode{mode0,mode1,mode2,mode3,mode4}; // global variable
extern int KeyCount,Func1FirstFlag,OneSecFlag,k ;
extern char CurrentKey,PastKey ;
extern char KB,Idiom_recorder[MAX_IDIOM_LENGTH] ;
extern char data_matrix_in[Row][Col] ,data_matrix_out[Row][Col];
extern char LEDS_Arr[8] ;
extern int scroll,idiom_count,k ;


#endif







