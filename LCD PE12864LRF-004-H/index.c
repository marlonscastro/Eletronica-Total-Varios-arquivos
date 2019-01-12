#include <16f628A.h>
#use delay(clock=4000000)
#FUSES NOWDT, NOBROWNOUT, PUT, XT  
#include "DriverPE12864LRF.c"

void main(void){
   PE12864_InitLcd();
   printf(PE12864_Printchar, "Teste LCD 128x64");
   while(true){}
}
