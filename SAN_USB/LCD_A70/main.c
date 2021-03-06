#include <SanUSB.h>
#USE SPI (MASTER, CLK=PIN_B1, DI=PIN_C7, DO=PIN_B0, BAUD = 2000000, MODE=0, BITS=8, STREAM=SPI_1, MSB_FIRST)
#include "driverA70.c"

#define LED_STATUS   pin_b7

int tempo;

#int_TIMER0
void  TIMER0_isr(void){
   tempo++;
   if(tempo == 45){   //  46 * 21,8ms =~ 1002,8ms ou 1,002 segundos 
      tempo=0;
      output_toggle(LED_STATUS);
   }
}
void main(){
   double amp;
   int i;  
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256|RTCC_8_bit);      //21.8 ms overflow
   //setup_adc_ports(AN0_VREF_VREF);
   setup_adc(ADC_CLOCK_DIV_32);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   set_adc_channel(0);   
   delay_ms(500);
   Init_LCD();
   ClearDisplay();
   GotoXRow(0,0);
   printf(printChar8x12, "   TESTE   ");
   GotoXRow(0,2);
   printf(printChar8x12, "   DO LCD     ");
   GotoXRow(0,4);
   printf(printChar8x12, " SIEMENS A70 ");
   GotoXRow(0,6);
   printf(printChar5x8, "  By Marlon ! ");
   while(true){
      /*delay_ms(100);
      GotoXRow(0,4);
      printf(lcd_printChar, "    ADC: %Lu  ", read_adc());
      amp = read_adc()*0.0341;
      GotoXRow(0,5);
      printf(lcd_printChar, "  I: %1.4f   ", amp);*/
   }
}

//---------------------------------------------------------------------------------
