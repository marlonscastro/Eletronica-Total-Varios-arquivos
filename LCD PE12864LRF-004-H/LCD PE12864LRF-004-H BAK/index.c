#include <18F4550.h>
#use delay(clock=48000000)
#fuses HSPLL, PLL4, CPUDIV1, PUT, NOWDT, NOBROWNOUT, NOLVP
#include "DriverPE12864LRF.c"
#include <math.h>
#include <string.h>
#include <stdlib.h>


void PE12864_TextXy(int x, int y, char* cvar);
void circulo(float aC, float bC, float r);
void circuloMenor(float aC, float bC, float r);
void circuloPonteiro(float aC, float bC, float r);
void circuloNumerico(float aC, float bC, float r);


void circulo(float aC, float bC, float r){
   int16 i = 0;
   float y, x;
   while(i <= 360){
      y = (sin(i*pi/180)*r)+bC;
      x = (cos(i*pi/180)*r)+aC;      
      PE12864_Putpixel(floor(x), floor(64-y), ON);
      i++;
   }
}
void circuloMenor(float aC, float bC, float r){
   int16 i = 0;
   float y, x;
   while(i <= 360){
      y = (sin(i*pi/180)*r)+bC;
      x = (cos(i*pi/180)*r)+aC;      
      PE12864_Putpixel(floor(x), floor(64-y), ON);
      i+=6;
   }
}
void circuloPonteiro(float aC, float bC, float r){
   int16 i = 0, mS = 0;
  // char chr[14];
   int H = 15, M = 41, S = 15, test = 0;
   float y, x;
   while(i <= 360){
      y = (sin(i*pi/180)*r)+bC;
      x = (cos(i*pi/180)*r)+aC;
      circuloNumerico(62, 29, 26);
      PE12864_line(aC, bC, (cos(0*pi/180)*(r-11))+aC, (sin(0*pi/180)*(r-11))+bC, ON);  // hora
      PE12864_line(aC, bC, (cos((156+test)*pi/180)*(r-7))+aC, (sin((156+test)*pi/180)*(r-7))+bC, ON); // minuto     
      PE12864_line(aC, bC, x, y, ON);
      mS = 0;
      while(mS < 1000){
         /*sprintf(chr,"%u:%u:%u %lu", H, M, S, mS);
         PE12864_TextXy(3,5,chr);  */ 
         PE12864_Gotoxy(0,0);
         /*if(S > 9)
            printf(PE12864_Printchar,"%u:%u:%u", H, M, S);
         else
            printf(PE12864_Printchar,"%u:%u:0%u", H, M, S);*/
         mS+=1;
         delay_ms(1);
      }
      S++;
      if(S>59){
         S=0;
         M++;
         PE12864_line(aC, bC, (cos((156+test)*pi/180)*(r-7))+aC, (sin((156+test)*pi/180)*(r-7))+bC, OFF); // minuto              
         test+=6;
      }
      //delay_ms(1000);
      PE12864_line(aC, bC, x, y, OFF);
      i+=6;
   }   
}
void circuloNumerico(float aC, float bC, float r){
   int16 i = 0, val = 3;
   char chr[5];
   float y, x;
   while(i <= 360){
      y = (sin(i*pi/180)*r)+bC;
      x = (cos(i*pi/180)*r)+aC;       
      //PE12864_Putpixel(x, y, ON);      
      if(!(i%30)){
         sprintf(chr,"%lu", val);
         // -- Resolver Bugs :   Inicio 
         if(val == 9)
            y+=1;
         if(val == 10){
            y+=2;
            x-=1;
         }
         if(val == 11){
            y+=1;
            x-=3;
         }
         if(val == 12)
            x-=3;            
         // -- Resolver Bugs :   Fim            
         PE12864_TextXy(x,y,chr);
         val++;
         if(val > 12)    // 9: 1B 0T || 10: 2B 1T || 11: 1B 1T || 12: 0B 3T
            val = 1;
      }
      i+=30;
   }
}
void PE12864_TextXy(int x, int y, char* cvar){
   int i, loop = 0;
   char c1, c2, chr;
   while(loop < strlen(cvar)){ 
      chr = cvar[loop];
      for(i=0;i<5;i++){
         if (chr < 0x53){
            c1 = TEXT[chr-0x20][i] <<(y%8);
            c2 = TEXT[chr-0x20][i] >>(8-(y%8));               
         }
         else {
            c1 = TEXT2[chr-0x53][i] <<(y%8);
            c2 = TEXT2[chr-0x53][i] >>(8-(y%8));
         }
         PE12864_Gotoxy(x,(y/8));      
         c1 |= buffer[x][y/8];         
         PE12864_Write_data(c1);               
         PE12864_Gotoxy(x,(y/8)+1);      
         c2 |= buffer[x][(y/8)+1];
         PE12864_Write_data(c2);
         x++;
      }
      x++;
      loop++;
   }
}
void circuloFechado(float aC, float bC, float r){
   int16 i = 0;
   float y, x;
   while(i <= 360){
      y = (sin(i*pi/180)*r)+bC;
      x = (cos(i*pi/180)*r)+aC;
      PE12864_line(aC, bC, x, y, ON);      
      i++;
   }   
}
void relogioAnalogico(){
   /*circulo(96, 32, 32);
   circuloMenor(96, 32, 30);
   circuloNumerico(94, 29, 26); 
   circuloPonteiro(96, 32, 28);*/
   circulo(64, 32, 32);
   circuloMenor(64, 32, 30);
   circuloNumerico(62, 29, 26); 
   circuloPonteiro(64, 32, 28);
}
void main(void){
   PE12864_InitLcd();
   relogioAnalogico();
   while(true){}
}
