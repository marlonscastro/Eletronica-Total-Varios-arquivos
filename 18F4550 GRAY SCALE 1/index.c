#include <18F4550.h>
#use delay(clock=48000000)
#fuses HSPLL, PLL4, CPUDIV1, PUT, NOWDT, NOBROWNOUT, NOLVP
#include "HMF6598SYH-PY.c"
#include <string.h>


void main(void){
   int i, j, t;
   HMF6598_InitLcd();
   t = 0;
   while(true){
      HMF6598_Gotoxy(0,0);
      for(i=0;i<8;i++)
         HMF6598_Write_data(0xff);
      HMF6598_Gotoxy(0,1);
      if (t<3)
         for(i=0;i<8;i++){
            HMF6598_Write_data(0xff);
         }
      else
         for(i=0;i<8;i++){
            HMF6598_Write_data(0x00);
         }
      HMF6598_Gotoxy(0,2);
      if (t<1)
         for(i=0;i<8;i++){
            HMF6598_Write_data(0xff);
         }
      else
         for(i=0;i<8;i++){
            HMF6598_Write_data(0x00);
         }         
      t++;
      if (t > 9)
         t = 0;
   }
 
   
}
