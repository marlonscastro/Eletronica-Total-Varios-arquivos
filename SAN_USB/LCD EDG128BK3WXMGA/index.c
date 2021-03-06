#include <SanUSB.h>
#USE SPI (MASTER, CLK=PIN_B1, DI=PIN_C7, DO=PIN_B0, BAUD = 2000000, MODE=0, BITS=8, STREAM=SPI_1, MSB_FIRST)

#include "EDG128BK3WXMGA.c"
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
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256|RTCC_8_bit);      //21.8 ms overflow
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   PE12864_InitLcd();
   printf(PE12864_Printchar, "Teste LCD 128x64");
   while(true){}
}
