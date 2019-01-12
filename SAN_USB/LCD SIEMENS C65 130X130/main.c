#include <16F876.h>
#FUSES NOWDT, HS, NOPUT, NOBROWNOUT, NOLVP, NOCPD, NOWRT, NODEBUG, NOPROTECT
#use delay(clock=16000000)
#USE SPI (MASTER, CLK=PIN_B3, DI=PIN_C7, DO=PIN_B2, BAUD = 2000000, MODE=0, BITS=8, STREAM=SPI_1, MSB_FIRST)

#include "c65_S6B33B2.c"
#define LED_STATUS   pin_b7

int tempo;
char text[30];

#int_TIMER0
void  TIMER0_isr(void){
   tempo++;
   if(tempo == 70){   //  46 * 21,8ms =~ 1002,8ms ou 1,002 segundos 
      tempo=0;
      output_toggle(LED_STATUS);
   }
   output_toggle(pin_c4);   
}
void main(void){
   int i;
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_32|RTCC_8_bit);  //RTCC_DIV_256    //21.8 ms overflow
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);   
   
   delay_ms(200);
   initlcd();
   lcdfill(0b11100000);   // 0bRRRGGGBB
   delay_ms(300);
   lcdfill(0b00011100);   // 0bRRRGGGBB
   delay_ms(300);
   lcdfill(0b00000011);   // 0bRRRGGGBB
   delay_ms(300);   
   lcdfill(0b00000000);   // 0bRRRGGGBB
   delay_ms(500);
   
   drawBox(WHITE, 0, 0, 10, 130);
   drawBox(BLACK, 10, 0, 10, 130);
   drawBox(RED,   20, 0, 10, 130);
   drawBox(GREEN, 30, 0, 10, 130);
   drawBox(BLUE,  40, 0, 10, 130);
   drawBox(PINK,  50, 0, 10, 130);
   drawBox(BLUE, 60, 0, 10, 130);
   drawBox(YELLOW,70, 0, 10, 130);
   drawBox(ORANGE,80, 0, 10, 130); 
   drawBox(WHITE, 90, 0, 10, 130);
   drawBox(BLACK, 100, 0, 10, 130);
   drawBox(RED,   110, 0, 10, 130);
   drawBox(GREEN, 120, 0, 10, 130);
   delay_ms(2000);

   lcdfill(BLACK);

   /*putChar(BLACK, WHITE, 'a', 0, 0);*/
 
   sprintf(text, "Teste Siemens C65");
   putText(BLACK, WHITE, text, 17, 0, 0);  
   delay_ms(300);
   drawBox(BLUE, 0, 94, 130, 10);
   delay_ms(300);   
   sprintf(text, "RBJ.NET Electronics");
   putText(BLUE, WHITE, text, 19, 10, 96);  
   delay_ms(300);
   sprintf(text, "-- Driver By Marlon --");
   putText(BLACK, WHITE, text, 22, 0, 110);  
   drawBox(GREEN, 20, 20, 30, 30);
   delay_ms(300);
   drawBox(BLUE, 50, 20, 30, 30);    
   delay_ms(300);
   drawBox(RED, 80, 20, 30, 30);
   delay_ms(300);
   
   drawBox(PINK, 20, 52, 30, 30);
   delay_ms(300);
   drawBox(ORANGE, 50, 53, 30, 30);    
   delay_ms(300);
   drawBox(YELLOW, 80, 52, 30, 30);
   delay_ms(300);

   while(true){}
}

//---------------------------------------------------------------------------------
