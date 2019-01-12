#include <18F4550.h>
#device adc=8
#use delay(clock=48000000)
#fuses HSPLL, PLL4, CPUDIV1, PUT, NOWDT, NOBROWNOUT, NOLVP

#include "driver1100.c"

int8 i;
char c[]="TEST";

void main (void) {
   Lcd_Init();
   lcd_circle(76, 38, 10, 0, 1);
   lcd_line(95, 0, 0, 64, 1);
   lcd_text57(10, 15, c, 1, 1);
   lcd_text57(10, 25, c, 2, 1);
   lcd_rect(60, 50, 92, 60, 1, 1);
   lcd_text57(65, 52, c, 1, 0);
   while(true){
   };
} 

