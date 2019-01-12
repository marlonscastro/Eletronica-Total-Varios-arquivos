#include <16f877a.h>
#use     delay(clock=10245000)
#fuses   HS, PUT, NOWDT, NOBROWNOUT, NOLVP
#include "DRIVE_GLCD_ST7565_S.c"
#include <math.h>
#include <string.h>
#include <stdlib.h>


void main(void)
{
   
   int i ;
   output_high(pin_d2);//led pówer
   
   ST7565S_InitLcd();
   
   ST7565S_gotoxy(10,4);
   printf(ST7565S_printchar,"RBJ_ELECTRONICS");
     
   for(i=0;i<128;i++)
   {
      ST7565S_PutPixel(i,35,ON);
      delay_ms(20);
   }
   
   ST7565S_gotoxy(10,5);
   
   printf(ST7565S_printchar,"VANIZE MARIA DE JESUS");
   
   ST7565S_rect(10, 2, 118, 60, OFF,ON);
   delay_ms(20);
   ST7565S_circle(64, 20, 15, ON, ON); 
   delay_ms(20);
   ST7565S_circle(64, 32, 25, OFF, ON); 
   delay_ms(20);
   ST7565S_rect(60, 20, 100, 45, OFF,ON);
}

    
   

