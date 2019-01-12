#include <18F4550.h>
#device adc=8
#use delay(clock=48000000)
#fuses HSPLL, PLL4, CPUDIV1, PUT, NOWDT, NOBROWNOUT, NOLVP
#include "HMF6598SYH-PY.c"
float distancia, tempo;
   #define TRIG pin_D7 
   #define ECHO pin_D5 

void main() { 
   HMF6598_InitLcd();
   delay_ms(1000);                              // Boot-up delay, for troubleshooting 
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);     // initiating timer 

   while(true){ 
      output_high(trig);                         // ping the sonar 
      delay_us(20);                            // sending 20us pulse 
      output_low(trig); 

      while(!input(ECHO)){}                       // wait for high state of echo pin 
      set_timer1(0);                           // setting timer zero 
      
      while(input(ECHO)){}                       // Wait for high state of echo pin
       
      tempo=get_timer1();                       // Getting the time 
      distancia=tempo*0.0149 + 1.093 ;            // Calculating the distance                         
      
      delay_ms(100); 
      
      HMF6598_Gotoxy(0,0);
      printf(HMF6598_Printchar, "Tempo :%f      ",tempo);      
      
      HMF6598_Gotoxy(0,1);
      printf(HMF6598_Printchar, "Distancia = %2.2f cm       ",distancia);      
   } 
} 
