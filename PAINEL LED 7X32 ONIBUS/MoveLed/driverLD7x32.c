#include "driverLD7x32.h"

void put_led(int x, int y, int COLOR){
   if(COLOR == ON)
      bit_set(MAT[x], y);
   else
      bit_clear(MAT[x], y);      
}

// Faz a varredura das colunas uma a uma da 1a a 32a;
void varre_coluna(){
   int i;
   int32 chr = 1;
   for(i=0;i<32;i++){
      write_col(MAT[i]);
      output_low(SCK_164);
      if((chr&0x01) == 0) output_low(DATA_164);
      else output_high(DATA_164);
      output_high(SCK_164);
      chr=chr>>1;
      delay_us(500);
   }
   output_low(DATA_164);
}

// Função que escreve os dados da Matriz MAT[] na coluna especificada
void write_col(char colData){
   int i;
   for(i=0;i<8;i++){
      output_low(SCK_595);
      if((colData&0x01) == 0) output_low(DATA_595);
      else output_high(DATA_595);
      output_high(SCK_595);
      colData=colData>>1;
   }
   output_low(LATCH_595);  
   output_high(LATCH_595);
}

void clearscreen(){
   int i;
   for(i=0;i<96;i++)
      MAT[i] = 0x00;
}

void put_char(int x, char cvar){
  int i;
  char c;
  if ((cvar<0x20) || (cvar>0x7F)) return;
  for (i=0;i<5;i++){
    c=font5x8[((cvar&0xff)-0x20)][i];
    if((c!=0x00) || (cvar==0x20)){     
       MAT[x]=c;
       x++;
    }
  }
  MAT[x]=0x00;
}

void putstr(int x, char* text){
   int i = 0;
   while (text[i]!=0){   
      put_char(x+(i*6),text[i]);
      i++;               
   }
}

void mydelay(long time_ms){
   delay_ms(time_ms/1000*60);
}

