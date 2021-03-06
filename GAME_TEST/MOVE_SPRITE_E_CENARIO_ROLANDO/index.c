#include <18F4550.h>
#use delay(clock=48000000)
#fuses HSPLL, PLL4, CPUDIV1, PUT, NOWDT, NOBROWNOUT, NOLVP
#include "HMF6598SYH-PY.c"
#include <string.h>

int x_ext, y_ext;
int t = 0, i, j;

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
      if (x_ext + t > 127){
         Sp1 |= cenario[y_ext/8][x_ext+t-128];
         Sp2 |= cenario[(y_ext/8)+1][x_ext+t-128];         
      }
      else{
         Sp1 |= cenario[y_ext/8][x_ext+t];      
         Sp2 |= cenario[(y_ext/8)+1][x_ext+t];
      }
      HMF6598_Gotoxy(x_ext,(y_ext/8));
      HMF6598_Write_data(Sp1);
      HMF6598_Gotoxy(x_ext,(y_ext/8)+1); 
      HMF6598_Write_data(Sp2);
      x_ext++;
   }
   x_ext -= 8;
}

#INT_TIMER0
void RTTC_isr(void){
   //output_toggle(pin_d0); 
   if(!input(pin_D7)){  // Direita
      if(x_ext < 120)
         x_ext = x_ext + 1;
   }
   if(!input(pin_D6)){  // Cima
      if(y_ext > 0)
         y_ext = y_ext - 1;     
   }
   if(!input(pin_D5)){  // Baixo
      if(y_ext < 55)
         y_ext = y_ext + 1;      
   }
   if(!input(pin_D4)){  // Esquerda
      if(x_ext > 0)
         x_ext = x_ext - 1;      
   }
   disable_interrupts (INT_TIMER0); 
   disable_interrupts(GLOBAL);    
}

void main(void){
   int i, j;
   HMF6598_InitLcd();
   setup_timer_0 (RTCC_DIV_4);
   // ------ SPRITE DE FUNDO rolando -------
   x_ext = 3;
   y_ext = 3;
   while(true){
      for(i=0;i<8;i++){
         HMF6598_Gotoxy(0,i);
         for(j=t;j<128;j++)
            HMF6598_Write_data(cenario[i][j]);           
         for(j=0;j<t;j++)   
            HMF6598_Write_data(cenario[i][j]);
      }
      putSprite(x_ext, y_ext);
      set_timer0(0);
      enable_interrupts (INT_TIMER0); 
      enable_interrupts(GLOBAL);       
      delay_ms(40);
      t++;
      if(t>127)
         t = 0;
   }
   // --------------------------------------
}
