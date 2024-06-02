#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer

//-------------------------------------------------------------
//            Print SWs value onto LEDs
//-------------------------------------------------------------
void printSWs2LEDs(void){
	unsigned char ch;
	
	ch = readSWs();
	print2LEDs(ch);
}
//--------------------------------------------------------------------
//            Print array to LEDs array with rate of LEDs_SHOW_RATE
//--------------------------------------------------------------------            
void printArr2SWs(char Arr[], int size, unsigned int rate){
	unsigned int i;
	
	for(i=0; i<size; i++){
		print2LEDs(Arr[i]);
		delay(rate);
	}
}

void Timer_A0_On (void) {
  //TA0CTL |= MC_2 + TAIE ;
  //TA0CCTL0 |=CCIE ;
}

void Timer_A0_Off (void) {
  TA0CTL = 0x0000 ;
  TA0CCTL0 = 0x0000 ;
  TACCR0 = 0x0000;
  TACCTL1 = 0x0000 ;
  TACCTL2 = 0x0000 ;
}

void KeyPadReady (void) {
    KeypadPortIN = 0xF0 ;
    KeypadPortOUT= 0x00 ;
}

void Swap(int i , int j)  {
    int k=0 ;
    DMA1CTL = DMADT_1 + DMASRCINCR_3 + DMADSTINCR_3 + DMASBDB ;
    DMACTL0 = DMA1TSEL_0 ;
    DMA1SZ = 36 ;
    for ( k=0 ; k<10 ; k++){
        if (k==i){
            DMA1SA= (int)data_matrix_in[i] ;
            DMA1DA = (int)data_matrix_out[j] ;
        }
        else if (k==j){
          DMA1SA= (int)data_matrix_in[j] ;
          DMA1DA = (int)data_matrix_out[i] ;
        }
        else {
          DMA1SA= (int)data_matrix_in[k] ;
          DMA1DA = (int)data_matrix_out[k] ;
        }
        DMA1CTL |= DMAEN +DMAREQ ;
    }

}

void func3(void) {
  DMACTL0 = DMA0TSEL_1;                     // CCR2 trigger
  DMA0SA = (int)LEDS_Arr ;
  DMA0DA = (int)&LEDsArrPort ;
  DMA0SZ = 0x08 ;
  DMA0CTL = DMADT_4 + DMASRCINCR_3 + DMASBDB + DMAEN; // Rpt, inc src
  TACTL = TASSEL_2 + MC_2 + ID_3 ;                  // SMCLK/4, contmode
  __bis_SR_register(LPM0_bits + GIE);
}

void Print_Mat (void ) {
    lcd_home() ;
    //state = state2 ;
    for ( k=0 ; k<=14 ; k++) {
        lcd_data(data_matrix_out[scroll][k]) ;
    }
    lcd_new_line ;
    for (k=15 ; k<=30 ; k++){
        lcd_data(data_matrix_out[scroll][k]) ;
    }
}





