 #include  "../header/bsp.h"    // private library - BSP layer

//-----------------------------------------------------------------------------  
//           GPIO configuration
//-----------------------------------------------------------------------------
void GPIOconfig(void){
  
  WDTCTL = WDTHOLD | WDTPW;		// Stop WDT
   
  // LEDs 8-bit Array Port configuration
  LEDsArrPortSel &= ~0xFF;            // GPIO capability
  LEDsArrPortDir |= 0xFF;             // output dir
  LEDsArrPort = 0x00;				  // clear all LEDs
  
  // Switches Setup
  //SWsArrPortSel &= ~0x0F;
  //SWsArrPortDir &= ~0x0F;
  
  // PushButtons Setup
  PBsArrPortSel &= ~0x07;
  PBsArrPortDir &= ~0x07;
  PBsArrIntEdgeSel |= 0x03;  	     // pull-up mode
  PBsArrIntEdgeSel &= ~0x0C;         // pull-down mode
  PBsArrIntEn |= 0x07;
  PBsArrIntPend &= ~0xFF;            // clear pending interrupts
  



  //-------------------------------------------------------------
  //            LCD setup
  //-------------------------------------------------------------
    LCD_Data_Sel &= ~0xF0 ;             // makes P1.4 - P1.7 IO mode
    LCD_Data_Dir |= 0xF0 ;              // makes P1.4 - P1.7 Output mode
    LCD_Data_Write &= ~0xF0 ;           // CLR P1.4 - P1.7

    LCD_CTL_Sel &= ~0xE0 ;             // makes P2.5 - P2.7 IO mode
    LCD_CTL_Dir |= 0xE0 ;              // makes P2.5 - P2.7 Output mode
    LCd_CTL_Write &= ~0xE0 ;           // CLR P2.5 - P2.7

 //-------------------------------------------------------------------------------------
 //            KeyPad configuration
 //-------------------------------------------------------------------------------------
    KeyPadPortDir |= ( BIT0 + BIT1 + BIT2 + BIT3) ;
    KeypadPortOUT = 0x00 ;
    
    KeyPad_IRQ_Sel &= ~(BIT1) ; // makes P2.1 IO mode
    KeyPad_IRQ_Pend = 0x00 ; // Clear interrupts for P2.1
    KeyPad_IRQ_En |= (BIT1) ; // enable P2.1 for interrupts
    KeyPad_IRQ_Dir &= ~(BIT1) ;// makes P2.1 Input mode
    KeyPad_IRQ_EdgeSel |= (BIT1) ; // P2.1 falling Edge

    _BIS_SR(GIE);                     // enable interrupts globally

}        
//------------------------------------------------------------------------------------- 
//            Timers configuration
//-------------------------------------------------------------------------------------
void TimerA0Func0_Config(void) {
    TA0CTL = 0x0004 ;
    TA0CCR0 = 0xFFFF ;
    TACTL = 0x02E2 ;
    TA0CCTL0 = 0x0010 ;

}

//------------------------------------------------------------------------------------- 
//            DMA configuration
//-------------------------------------------------------------------------------------
void DMA_Config_Func2(void){
    DMA0CTL = DMAEN + DMASRCINCR_3 + DMASWDW + DMAIE; //repeated-single, source inc, word-word trans, Interupt enable
    DMACTL0 = DMA0TSEL_1; //TACCR2_IFG trigger
}

             
             
            
  

