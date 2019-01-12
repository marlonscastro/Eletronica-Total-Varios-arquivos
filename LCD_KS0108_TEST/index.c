#include <16f628A.h>
#use delay(clock=4000000)
#FUSES NOWDT, NOBROWNOUT, PUT, XT  
#include "Extended_GLCD.c"

void main(void){
   char inverse_test_txt[]  = "TESTE LCD KS0108";
 
   glcd_init(ON);
  
   glcd_image(NO);
   delay_ms(4000);
   glcd_text57(10,30,inverse_test_txt,1,ON);
   while(true){}
}
