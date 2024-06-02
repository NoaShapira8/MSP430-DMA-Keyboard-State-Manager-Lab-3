#include  "../header/halGPIO.h"     // private library - HAL layer

//--------------------------------------------------------------------
//             System Configuration  
//--------------------------------------------------------------------
void sysConfig(void){ 
	GPIOconfig();

}
//--------------------------------------------------------------------
// 				Print Byte to 8-bit LEDs array 
//--------------------------------------------------------------------
void print2LEDs(unsigned char ch){
	LEDsArrPort = ch;
}
//--------------------------------------------------------------------
//				Clear 8-bit LEDs array 
//--------------------------------------------------------------------
void clrLEDs(void){
	LEDsArrPort = 0x000;
}  
//--------------------------------------------------------------------
//				Toggle 8-bit LEDs array 
//--------------------------------------------------------------------
void toggleLEDs(char ch){
	LEDsArrPort ^= ch;
}
//--------------------------------------------------------------------
//				Set 8-bit LEDs array 
//--------------------------------------------------------------------
void setLEDs(char ch){
	LEDsArrPort |= ch;
}
//--------------------------------------------------------------------
//				Read value of 4-bit SWs array 
//--------------------------------------------------------------------
unsigned char readSWs(void){
	unsigned char ch;
	
	ch = PBsArrPort;
	ch &= SWmask;     // mask the least 4-bit
	return ch;
}
//---------------------------------------------------------------------
//             Increment / decrement LEDs shown value 
//---------------------------------------------------------------------
void incLEDs(char val){
	LEDsArrPort += val;
}
//---------------------------------------------------------------------
//            Polling based Delay function
//---------------------------------------------------------------------
void delay(unsigned int t){  // t[msec]
	volatile unsigned int i;
	
	for(i=t; i>0; i--);
}
//---------------------------------------------------------------------
//            Enter from LPM0 mode
//---------------------------------------------------------------------
void enterLPM(unsigned char LPM_level){
	if (LPM_level == 0x00) 
	  _BIS_SR(LPM0_bits);     /* Enter Low Power Mode 0 */
        else if(LPM_level == 0x01) 
	  _BIS_SR(LPM1_bits);     /* Enter Low Power Mode 1 */
        else if(LPM_level == 0x02) 
	  _BIS_SR(LPM2_bits);     /* Enter Low Power Mode 2 */
	else if(LPM_level == 0x03) 
	  _BIS_SR(LPM3_bits);     /* Enter Low Power Mode 3 */
        else if(LPM_level == 0x04) 
	  _BIS_SR(LPM4_bits);     /* Enter Low Power Mode 4 */
}
//---------------------------------------------------------------------
//            Enable interrupts
//---------------------------------------------------------------------
void enable_interrupts(){
  _BIS_SR(GIE);
}
//---------------------------------------------------------------------
//            Disable interrupts
//---------------------------------------------------------------------
void disable_interrupts(){
  _BIC_SR(GIE);
}
//*********************************************************************
//            PB's Interrupt Service Rotine
//*********************************************************************
#pragma vector=PORT1_VECTOR
  __interrupt void PBs_handler(void){
   
	delay(debounceVal);
//---------------------------------------------------------------------
//            selector of transition between states
//---------------------------------------------------------------------
	if(PBsArrIntPend & PB0){
	  state = state1;
	  lcd_clear() ;
	  DMA_Off() ;
	  Timer_A0_Off();
	  LEDsArrPort= 0x00 ;
	  PBsArrIntPend &= ~PB0;
        }
        else if(PBsArrIntPend & PB1){
	  state = state2;
	  lcd_clear() ;
	  DMA_Off() ;
	  Timer_A0_Off();
	  LEDsArrPort= 0x00 ;
	  PBsArrIntPend &= ~PB1; 
        }
	else if(PBsArrIntPend & PB2){ 
	  state = state3;
	  lcd_clear() ;
	  Timer_A0_Off();
	  DMA_Off() ;
	  PBsArrIntPend &= ~PB2;
        }
//---------------------------------------------------------------------
//            Exit from a given LPM 
//---------------------------------------------------------------------	
        switch(lpm_mode){
		case mode0:
		 LPM0_EXIT; // must be called from ISR only
		 break;
		 
		case mode1:
		 LPM1_EXIT; // must be called from ISR only
		 break;
		 
		case mode2:
		 LPM2_EXIT; // must be called from ISR only
		 break;
                 
                case mode3:
		 LPM3_EXIT; // must be called from ISR only
		 break;
                 
                case mode4:
		 LPM4_EXIT; // must be called from ISR only
		 break;
	}
        
}
 //--------------------------------------------------------------------
 //              KeyPad Interrupt Service Routine (P2.1)
 //--------------------------------------------------------------------
#pragma vector=PORT2_VECTOR
  __interrupt void KeyPad_handler(void){

      delay(debounceVal * 3);

      if (state==state1 || state==state2 ){
          if(KeyPad_IRQ_Pend & BIT1){    // if keypad has been pressed find value
                   KB = 100;
                   KeypadPortOUT = 0x0E;
                   if ( ( KeypadPortIN & 0x10 ) == 0 ){
                       if (Func1FirstFlag ==0) {
                           CurrentKey=PastKey='D' ;
                           KeyCount ++ ;
                           Func1FirstFlag = 1  ;
                       }
                       else if (CurrentKey == PastKey) {
                           KeyCount ++ ;
                       }
                   }


                   else if ( ( KeypadPortIN & 0x20 ) == 0 )  {
                       if (Func1FirstFlag ==0) {
                         CurrentKey=PastKey='#' ;
                           KeyCount ++ ;
                           Func1FirstFlag = 1  ;
                       }
                       else if (CurrentKey == PastKey) {
                           KeyCount ++ ;
                       }
                   }

                   else if ( ( KeypadPortIN & 0x40 ) == 0 )  {
                     if (state == state1) { 
                       if (Func1FirstFlag ==0) {
                         CurrentKey=PastKey='0' ;
                         KeyCount ++ ;
                         Func1FirstFlag = 1  ;
                       }
                       else if (CurrentKey == PastKey) {
                         KeyCount ++ ;
                       }
                     }
                     else if (state == state2 ) { 
                       scroll ++ ; 
                       Print_Mat() ;
                     }
                   }
                   
                   else if ( ( KeypadPortIN & 0x80 ) == 0 )  {
                       if (Func1FirstFlag ==0) {
                         CurrentKey=PastKey='*' ;
                           KeyCount ++ ;
                           Func1FirstFlag = 1  ;
                       }
                       else if (CurrentKey == PastKey) {
                           KeyCount ++ ;
                       }
                   }

                   KeypadPortOUT = 0x0D;
                   if ( ( KeypadPortIN & 0x10 ) == 0 ){
                       if (Func1FirstFlag ==0) {
                           CurrentKey=PastKey='C' ;
                           KeyCount ++ ;
                           Func1FirstFlag = 1  ;
                       }
                       else if (CurrentKey == PastKey) {
                           KeyCount ++ ;
                       }
                   }
                   
                    else if ( ( KeypadPortIN & 0x20 ) == 0 ){
                       if (Func1FirstFlag ==0) {
                           CurrentKey=PastKey='9' ;
                           KeyCount ++ ;
                           Func1FirstFlag = 1  ;
                       }
                       else if (CurrentKey == PastKey) {
                           KeyCount ++ ;
                       }
                   }
                          
                   else if ( ( KeypadPortIN & 0x40 ) == 0 ){
                       if (Func1FirstFlag ==0) {
                           CurrentKey=PastKey='8' ;
                           KeyCount ++ ;
                           Func1FirstFlag = 1  ;
                       }
                       else if (CurrentKey == PastKey) {
                           KeyCount ++ ;
                       }
                   }
                   
                   else if ( ( KeypadPortIN & 0x80 ) == 0 ){
                       if (Func1FirstFlag ==0) {
                           CurrentKey=PastKey='7' ;
                           KeyCount ++ ;
                           Func1FirstFlag = 1  ;
                       }
                       else if (CurrentKey == PastKey) {
                           KeyCount ++ ;
                       }
                   }

                   KeypadPortOUT = 0x0B;
                   if ( ( KeypadPortIN & 0x10 ) == 0 ){
                       if (Func1FirstFlag ==0) {
                           CurrentKey=PastKey='B' ;
                           KeyCount ++ ;
                           Func1FirstFlag = 1  ;
                       }
                       else if (CurrentKey == PastKey) {
                           KeyCount ++ ;
                       }
                   }
                   
                   else if ( ( KeypadPortIN & 0x20 ) == 0 ){
                       if (Func1FirstFlag ==0) {
                           CurrentKey=PastKey='6' ;
                           KeyCount ++ ;
                           Func1FirstFlag = 1  ;
                       }
                       else if (CurrentKey == PastKey) {
                           KeyCount ++ ;
                       }
                   }
                   else if ( ( KeypadPortIN & 0x40 ) == 0 ){
                     if (state == state1 ) { 
                       if (Func1FirstFlag ==0) {
                         CurrentKey=PastKey='5' ;
                         KeyCount ++ ;
                         Func1FirstFlag = 1  ;
                       }
                       else if (CurrentKey == PastKey) {
                         KeyCount ++ ;
                       }
                     }
                     else if (state == state2) { 
                       scroll -- ; 
                       Print_Mat() ;
                     }
                   }
                   
                   else if ( ( KeypadPortIN & 0x80 ) == 0 ){
                       if (Func1FirstFlag ==0) {
                           CurrentKey=PastKey='4' ;
                           KeyCount ++ ;
                           Func1FirstFlag = 1  ;
                       }
                       else if (CurrentKey == PastKey) {
                           KeyCount ++ ;
                       }
                   }

                   KeypadPortOUT = 0x07;
                   if ( ( KeypadPortIN & 0x10 ) == 0 ){
                       if (Func1FirstFlag ==0) {
                           CurrentKey=PastKey='A' ;
                           KeyCount ++ ;
                           Func1FirstFlag = 1  ;
                       }
                       else if (CurrentKey == PastKey) {
                           KeyCount ++ ;
                       }
                   }
                   else if ( ( KeypadPortIN & 0x20 ) == 0 ){
                       if (Func1FirstFlag ==0) {
                           CurrentKey=PastKey='3' ;
                           KeyCount ++ ;
                           Func1FirstFlag = 1  ;
                       }
                       else if (CurrentKey == PastKey) {
                           KeyCount ++ ;
                       }
                   }
                   else if ( ( KeypadPortIN & 0x40 ) == 0 ){
                       if (Func1FirstFlag ==0) {
                           CurrentKey=PastKey='2' ;
                           KeyCount ++ ;
                           Func1FirstFlag = 1  ;
                       }
                       else if (CurrentKey == PastKey) {
                           KeyCount ++ ;
                       }
                   }
                   else if ( ( KeypadPortIN & 0x80 ) == 0 )  {
                       if (Func1FirstFlag ==0) {
                           CurrentKey=PastKey='1' ;
                           KeyCount ++ ;
                           Func1FirstFlag = 1  ;
                       }
                       else if (CurrentKey == PastKey) {
                           KeyCount ++ ;
                       }
                   }
                   KeyPad_IRQ_Pend &= ~BIT1 ;
                   if (state == state2) {
                     KeyPadReady() ;
                   }
                   if (state ==state1) {
                     TimerA0Func0_Config() ;
                   }
          }
      }
}


  //*********************************************************************
  //            TimerA0 Interrupt Service Routine
  //*********************************************************************

  #pragma vector = TIMER0_A0_VECTOR
  __interrupt void Timer_A0_ISR (void){
    LPM0_EXIT ;
    OneSecFlag++ ;
    if (OneSecFlag % 3 ==0) {
        if (CurrentKey == 'D'){
            if (KeyCount == 1 ) {
                KB = 'F' ;
            }
            if (KeyCount == 2 ) {
                KB = 'Y' ;
            }
            if (KeyCount == 3 ) {
                 KB = 'Z' ;
            }
        }
        else if (CurrentKey == '#'){
            if (KeyCount == 1 ) {
                KB = 'B' ;
            }
            if (KeyCount == 2 ) {
                KB = 'W' ;
            }
            if (KeyCount == 3 ) {
                 KB = 'X' ;
            }
        }
        else if (CurrentKey == '0'){
            if (KeyCount == 1 ) {
                KB = '0' ;
            }
            if (KeyCount == 2 ) {
                KB = 'T' ;
            }
        }
        else if (CurrentKey == '*'){
            if (KeyCount == 1 ) {
                KB = 'A' ;
            }
            if (KeyCount == 2 ) {
                KB = 'S' ;
            }
        }
        else if (CurrentKey == 'C'){
            if (KeyCount == 1 ) {
                KB = 'E' ;
            }
            if (KeyCount == 2 ) {
                KB = 'R' ;
            }
        }
        else if (CurrentKey == '9'){
            if (KeyCount == 1 ) {
                KB = '9' ;
            }
            if (KeyCount == 2 ) {
                KB = 'Q' ;
            }
        }
        else if (CurrentKey == '8'){
            if (KeyCount == 1 ) {
                KB = '8' ;
            }
            if (KeyCount == 2 ) {
                KB = '9' ;
            }
        }
        else if (CurrentKey == '7'){
            if (KeyCount == 1 ) {
                KB = '7' ;
            }
            if (KeyCount == 2 ) {
                KB = 'O' ;
            }
        }
        else if (CurrentKey == 'B'){
            if (KeyCount == 1 ) {
                KB = 'D' ;
            }
            if (KeyCount == 2 ) {
                KB = 'N' ;
            }
        }
        else if (CurrentKey == '6'){
            if (KeyCount == 1 ) {
                KB = '6' ;
            }
            if (KeyCount == 2 ) {
                KB = 'M' ;
            }
        }
        else if (CurrentKey == '5'){
            if (KeyCount == 1 ) {
                KB = '5' ;
            }
            if (KeyCount == 2 ) {
              KB = 'L' ;
            }
        }
        else if (CurrentKey == '4'){
            if (KeyCount == 1 ) {
                KB = '4' ;
            }
            if (KeyCount == 2 ) {
                KB = 'K' ;
            }
        }
        else if (CurrentKey == 'A'){
            if (KeyCount == 1 ) {
                KB = 'C' ;
            }
            if (KeyCount == 2 ) {
                KB = 'J' ;
            }
        }
        else if (CurrentKey == '3'){
            if (KeyCount == 1 ) {
                KB = '3' ;
            }
            if (KeyCount == 2 ) {
                KB = 'I' ;
            }
        }
        else if (CurrentKey == '2'){
            if (KeyCount == 1 ) {
                KB = '2' ;
            }
            if (KeyCount == 2 ) {
                KB = 'H' ;
            }
        }
        else if (CurrentKey == '1'){
            if (KeyCount == 1 ) {
                KB = '1' ;
            }
            if (KeyCount == 2 ) {
                KB = 'G' ;
            }
            if (KeyCount ==3 ){
                KB = ' ' ;
            }
        }
        
        if (KB != 100) {

        }
        Timer_A0_Off() ;
        Func1FirstFlag = 0 ;
        KeyCount= 0 ;
        lcd_data(KB) ;
        Idiom_recorder[idiom_count] = KB ;
        idiom_count ++ ;

    }
    else {
        TimerA0Func0_Config() ;
    }



}


  //---------------------------------------------------------------------
  //            LCD
  //---------------------------------------------------------------------
  //******************************************************************
  // send a command to the LCD
  //******************************************************************
  void lcd_cmd(unsigned char c){

      LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

      if (LCD_MODE == FOURBIT_MODE)
      {
          LCD_Data_Write &= ~OUTPUT_DATA;// clear bits before new write
          LCD_Data_Write |= ((c >> 4) & 0x0F) << LCD_DATA_OFFSET;
          lcd_strobe();
          LCD_Data_Write &= ~OUTPUT_DATA;
          LCD_Data_Write |= (c & (0x0F)) << LCD_DATA_OFFSET;
          lcd_strobe();
      }
      else
      {
          LCD_Data_Write = c;
          lcd_strobe();
      }
  }


  //******************************************************************
  // send data to the LCD
  //******************************************************************
  void lcd_data(unsigned char c){

      LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

      LCD_Data_Write &= ~OUTPUT_DATA;
      LCD_RS(1);
      if (LCD_MODE == FOURBIT_MODE)
      {
              LCD_Data_Write &= ~OUTPUT_DATA;
              LCD_Data_Write |= ((c >> 4) & 0x0F) << LCD_DATA_OFFSET;
              lcd_strobe();
              LCD_Data_Write &= (0xF0 << LCD_DATA_OFFSET) | (0xF0 >> 8 - LCD_DATA_OFFSET);
              LCD_Data_Write &= ~OUTPUT_DATA;
              LCD_Data_Write |= (c & 0x0F) << LCD_DATA_OFFSET;
              lcd_strobe();
      }
      else
      {
              LCD_Data_Write = c;
              lcd_strobe();
      }

      LCD_RS(0);
  }

  //******************************************************************
  // write a string of chars to the LCD
  //******************************************************************
  void lcd_puts(const char * s){

      while(*s)
          lcd_data(*s++);
  }

  //******************************************************************
  // initialize the LCD
  //******************************************************************
  void lcd_init(){

      char init_value;

      if (LCD_MODE == FOURBIT_MODE) init_value = 0x3 << LCD_DATA_OFFSET;
      else init_value = 0x3F;

      LCD_RS_DIR(OUTPUT_PIN);
      LCD_EN_DIR(OUTPUT_PIN);
      LCD_RW_DIR(OUTPUT_PIN);
      LCD_Data_Dir |= OUTPUT_DATA;
      LCD_RS(0);
      LCD_EN(0);
      LCD_RW(0);

      DelayMs(15);
      LCD_Data_Write &= ~OUTPUT_DATA;
      LCD_Data_Write |= init_value;
      lcd_strobe();
      DelayMs(5);
      LCD_Data_Write &= ~OUTPUT_DATA;
      LCD_Data_Write |= init_value;
      lcd_strobe();
      DelayUs(200);
      LCD_Data_Write &= ~OUTPUT_DATA;
      LCD_Data_Write |= init_value;
      lcd_strobe();

      if (LCD_MODE == FOURBIT_MODE){
          LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h
          LCD_Data_Write &= ~OUTPUT_DATA;
          LCD_Data_Write |= 0x2 << LCD_DATA_OFFSET; // Set 4-bit mode
          lcd_strobe();
          lcd_cmd(0x28); // Function Set
      }
      else lcd_cmd(0x3C); // 8bit,two lines,5x10 dots

      lcd_cmd(0xF); //Display On, Cursor On, Cursor Blink
      lcd_cmd(0x1); //Display Clear
      lcd_cmd(0x6); //Entry Mode
      lcd_cmd(0x80); //Initialize DDRAM address to zero
  }


  //******************************************************************
  // lcd strobe functions
  //******************************************************************
  void lcd_strobe(){
    LCD_EN(1);
    asm("nOp");
    //asm("NOP");
    LCD_EN(0);
  }

  //******************************************************************
  // Delay usec functions
  //******************************************************************
  void DelayUs(unsigned int cnt){

      unsigned char j;
      for(j=cnt ; j>0 ; j--) asm("n0p"); // tha command asm("nop") takes raphly 1usec

  }
  //******************************************************************
  // Delay msec functions
  //******************************************************************
  void DelayMs(unsigned int cnt){

      unsigned char j;
      for(j=cnt ; j>0 ; j--) DelayUs(1000); // tha command asm("nop") takes raphly 1usec

  }

void DMA_Off(void) {
    DMA0CTL &= ~DMAEN ;
    DMA1CTL &= ~DMAEN ;
}






 
