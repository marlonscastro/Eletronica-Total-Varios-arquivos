/*#include <16f876.h>
#use delay(clock=16000000)
#FUSES NOWDT, NOBROWNOUT, PUT, XT  */

#include <16F876.h>
#FUSES NOWDT, HS, NOPUT, NOBROWNOUT, NOLVP, NOCPD, NOWRT, NODEBUG, NOPROTECT
#use delay(clock=16000000)
//#USE SPI (MASTER, CLK=PIN_B2, DI=PIN_C5, DO=PIN_B1, BAUD = 100000, MODE=0, BITS=8, STREAM=SPI_1, MSB_FIRST)


#include "EDG128BK3WXMGA.c"

void main(void){
   PE12864_InitLcd();
   printf(PE12864_Printchar, "Teste LCD 128x64");
   while(true){}
}
