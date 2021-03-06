#include <18F4550.h>
#use delay(clock=48000000)
#fuses HSPLL, PLL4, CPUDIV1, PUT, NOWDT, NOBROWNOUT, NOLVP
#include "HMF6598SYH-PY.c"
#include <string.h>

int x_ext, y_ext;
void putSprite(int x, int y){
   const BYTE bloco[8] = {0xFF,0xFF,0x81,0x81,0x81,0x81,0xFF,0xFF};
   int i;
   char Sp1, Sp2;
   if(x < 121)
      x_ext = x;
   if(y < 57)
      y_ext = y;
   for(i=0;i<8;i++){
      Sp1 = bloco[i] <<(y_ext%8);
      Sp2 = bloco[i] >>(8-(y_ext%8));      
      HMF6598_Gotoxy(x_ext,(y_ext/8));
      HMF6598_Write_data(Sp1);
      HMF6598_Gotoxy(x_ext,(y_ext/8)+1);            
      HMF6598_Write_data(Sp2);
      x_ext++;
   }
   x_ext -= 8;
}

void main(void){
   int v;
   HMF6598_InitLcd();
   putSprite(3, 3);
   while(true){
      delay_ms(50);
      if(!input(pin_D7)){   
         putSprite(x_ext+1, y_ext);
         
         HMF6598_Gotoxy(x_ext-1,(y_ext/8));
         HMF6598_Write_data(0x00);
         HMF6598_Gotoxy(x_ext-1,(y_ext/8)+1);
         HMF6598_Write_data(0x00);         
      }
      if(!input(pin_D6)){   
         for(v=0;v<8;v++){
            HMF6598_Gotoxy(x_ext+v,(y_ext/8)+1);            
            HMF6598_Write_data(0x00);         
         }
         putSprite(x_ext, y_ext-1);
      }
      if(!input(pin_D5)){  
         for(v=0;v<8;v++){
            HMF6598_Gotoxy(x_ext+v,(y_ext/8));            
            HMF6598_Write_data(0x00);         
         }      
         putSprite(x_ext, y_ext+1);
      }
      if(!input(pin_D4)){   
         putSprite(x_ext-1, y_ext);
         
         HMF6598_Gotoxy(x_ext+8,(y_ext/8));
         HMF6598_Write_data(0x00);
         HMF6598_Gotoxy(x_ext+8,(y_ext/8)+1);
         HMF6598_Write_data(0x00);           
      }      
   }
   //int i, j;
   /* HMF6598_Gotoxy(0,0);   
   printf(HMF6598_Printchar, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");   
   */
   /*for(i=0;i<8;i++){
      HMF6598_Gotoxy(0,i);
      for(j=0;j<128;j++){
         HMF6598_Write_data(cenario[i][j]);           
         }
   }*/
   
}
