#include <16f877A.h>
#use delay(clock=4000000)
#fuses HS,NOWDT,PUT
#use rs232(baud=4800, xmit=PIN_C6,rcv=PIN_C7)
#include <lcd.c>
boolean func = false;

void muda(){
   if(!input(pin_B5)){
      func = !func;
   }
}

void main(){
   char vet[70];
   char arg[7] = {'$', 'G', 'P', 'R', 'M', 'C'};
   int y = 0,i = 0, var = 0, x, valor;
   float valorf;
   char k;
   lcd_init();
   while(true){
      muda();
      k=getc();
      if(k == arg[i])
         i++;
      if(i > 5){
         vet[y] = k;
         y++;
         if(y > 69){
            if(func){
               for(x = 33; x >= 26 ; x--){
                  valor = vet[x];
                  if((valor < 57) && (valor > 47)){
                     valor++;
                     vet[x] = valor;
                     break;
                  }
                  else {
                     if(valor == 57)
                        vet[x] = '0';
                     }
               }         
               lcd_gotoxy(1,1);
               printf(lcd_putc,"LT:  ");
               for(var = 14; var < 23; var++)
                  lcd_putc(vet[var]);
               lcd_putc(' ');
               lcd_putc(vet[24]);
               lcd_gotoxy(1,2);
               printf(lcd_putc,"LG: ");
               for(var = 26; var < 36; var++)
                  lcd_putc(vet[var]);
               lcd_putc(' ');   
               lcd_putc(vet[37]);
            }
            else{

               valor = (vet[40] - 48)*10;
               valor = valor + (vet[41] - 48);
               valorf = valor + (vet[43] - 48)*0.1;
               valorf = valorf*1.852;
               
               lcd_gotoxy(1,1);
               lcd_putc(vet[51]);
               lcd_putc(vet[52]);
               lcd_putc('/');
               lcd_putc(vet[53]);
               lcd_putc(vet[54]);
               lcd_putc('/');
               lcd_putc(vet[55]);
               lcd_putc(vet[56]);
               lcd_putc(' ');
               lcd_putc('-');               
               lcd_putc(' ');
               
               y = valorf;
               printf(lcd_putc,"%d    ",y);
               //lcd_putc('M');               
               
               lcd_gotoxy(1,2);   
               lcd_putc(vet[2]);               
               lcd_putc(vet[3]);
               lcd_putc(':');               
               lcd_putc(vet[4]);
               lcd_putc(vet[5]);               
               lcd_putc(':');
               lcd_putc(vet[6]);               
               lcd_putc(vet[7]);  
               lcd_putc(' ');
               lcd_putc('-');               
               lcd_putc(' ');    
               
               printf(lcd_putc, "Km/h ");                  
            }
            y = 0;
            i = 0;
         }
      }
   }
}


/*
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
            lcd_putc(' ');
            lcd_putc(vet[24]);
            lcd_gotoxy(1,2);
            printf(lcd_putc,"LG: ");
            for(var = 26; var < 36; var++)
               lcd_putc(vet[var]);
            lcd_putc(' ');   
            lcd_putc(vet[37]);
            y = 0;
            i = 0;
         }
      }
   }
}

*/
