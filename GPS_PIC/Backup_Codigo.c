#include <16f877A.h>
#use delay(clock=4000000)
#fuses HS,NOWDT,PUT
#use rs232(baud=4800, xmit=PIN_C6,rcv=PIN_C7)
#include <lcd.c>

void main(){
   char vet[40];
   char arg[7] = {'$', 'G', 'P', 'R', 'M', 'C'};
   int y = 0, i = 0, var = 0;
   char k;
   lcd_init();
   while(true){
      k=getc();
      if(k == arg[i])
         i++;
      if(i > 5){
         vet[y] = k;
         y++;
         if(y > 39){
            lcd_gotoxy(1,1);
            printf(lcd_putc,"LT:  ");
            for(var = 14; var < 23; var++)
               lcd_putc(vet[var]);
            lcd_putc(vet[24]);
            lcd_gotoxy(1,2);
            printf(lcd_putc,"LG: ");
            for(var = 26; var < 36; var++)
               lcd_putc(vet[var]);
            lcd_putc(vet[37]);
            y = 0;
            i = 0;
         }
      }
   }
}
/*
            lcd_escreve('\f');
            lcd_pos_xy(1,1);
            printf(lcd_escreve,"LT: ");
            for(var = 14; var < 23; var++)
               lcd_escreve(vet[var]);
            lcd_escreve(" ");
            lcd_escreve(vet[24]);
            
            lcd_pos_xy(1,2);
            printf(lcd_escreve,"LG: ");
            for(var = 26; var < 36; var++)
               lcd_escreve(vet[var]);
            lcd_escreve(" ");
            lcd_escreve(vet[37]);*/
           
            /*for(var = 14, x = 0; var < 23, x < 9; var++, x++)
               imp[x] = vet[var];
            imp[9] = ' ';               
            imp[10] = vet[24];                           
            imp[11] = ' ';
            imp[12] = NULL;
            printf(lcd_escreve,"LT: %s", imp);
            
            for(var = 26, x = 0; var < 36, x < 10; var++, x++)
               imp[x] = vet[var];
            imp[10] = ' ';               
            imp[11] = vet[37];                           
            imp[12] = NULL;
            printf(lcd_escreve,"\r\nLG: %s", imp);*/           
