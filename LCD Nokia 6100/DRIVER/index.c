#include <18F4550.h>
#use delay(clock=48000000)
#fuses HSPLL, PLL4, CPUDIV1, PUT, NOWDT, NOBROWNOUT, NOLVP
#include "driver6610Epson.c"


void main(void){
   Epson_InitLcd();
   LCDClearScreen(124);
   LCDWriteWindow(10, 10, 60, 60);   
   LCDSetPixel(50, 60,60);
   //printf(Epson_Printchar, "128x64 ST7565SG");
   while(true){}
}
