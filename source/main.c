#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer
#include     <string.h>
#include    <stdio.h>

enum FSMstate state;
enum SYSmode lpm_mode;
int KeyCount=0,Func1FirstFlag,OneSecFlag=0 ;
char PastKey,CurrentKey ;
char KB=100  ;
int scroll=0 , idiom_count=0 ,k=0 ;
char LEDS_Arr[8]= {0x01 , 0x02 , 0x04 , 0x08, 0x10 , 0x20 , 0x40 , 0x80} ;
char data_matrix_out[Row][Col] = { };
char Idiom_recorder[MAX_IDIOM_LENGTH]={ } ;
char data_matrix_in[Row][Col] = {
                            "An apple a day keeps the doctor away",
                             "climb on the bandwagon" ,
                             "Dot the i's and cross the t\'s",
                             "He who pays the piper calls the tune",
                             "The pen is mightier than the sword",
                             "The pot calling the kettle black",
                             "shed crocodile tears",
                             "Close but no cigar",
                             "Cut from the same cloth",
                             "Strike while the iron’s hot",
};



void main(void){


  state = state0;  // start in idle state on RESET
  lpm_mode = mode0;     // start in idle state on RESET
  sysConfig();
  lcd_init() ;
  lcd_clear() ;
  lcd_home() ;
  
  while(1){
	switch(state){
	  case state0:
	      enterLPM(lpm_mode);
		break;
		 
	  case state1:
	      //TimerA0Func0_Config() ;
	      Func1FirstFlag=0 ;
	      KeyPadReady() ;
	      enterLPM(lpm_mode);

		break;
		 
	  case state2:
	    lcd_clear() ;
	    Swap(0,1) ;
	    Print_Mat() ;
        KeyPadReady() ;
        enterLPM(lpm_mode);
		break;
		
	  case state3 :
	    lcd_clear() ;
	    func3() ;
	}
  }
}
  
  
  
  
  
  
