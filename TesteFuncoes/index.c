#include <16f877A.h>
#use delay(clock=4000000)
#fuses HS,NOWDT,PUT
#use rs232(baud=4800, xmit=PIN_C6,rcv=PIN_C7)
#include <lcd.c>
#include <string.h>
//#include <usart.c>
   char k;
   long int i = 0;
   char arg[7] = {'$', 'G', 'P', 'R', 'M', 'C'};     
void split(char caracter, int ind, char *retorno, char *str){
   int tam, i, x, cont, p;
   tam = strlen(str);
   x = cont = 0;
   for (i = 0; i < tam; i++){
      if(ind == 0){
         if(caracter != str[i]){
            retorno[x] = str[i];
            x++;
         }
         else break;
      }
      else{
         if (caracter == str[i]){
            cont++;
            if(cont == ind){
               p = i + 1;
               while(true){
                  if(str[p] != caracter){
                     retorno[x] = str[p];
                     p++;
                     x++;
                  }
                  else
                     break;
               }
            }
            if(cont > ind)
               break;
         }
      }
   }
}

void recebe_rs232(char *mat){
   int x = 0;
   while(x < 70){
      k = getc();
      if(k == arg[i])
         i++;
      if(i > 5){
         i = 0;
         mat[i] = k;
         
      }
      x++;
   }
}

void pressRb(){
   printf(lcd_putc, "funcao executada");
   delay_ms(1000);
   lcd_putc('\f');   
}

void main(){
   char vet[10] = {'9', '9', '9', '9', '.', '9', '9', '2', '6', '\0'};
   int x, valor;
   lcd_init();
   while(true){
      lcd_gotoxy(1,1);
      printf(lcd_putc, "%lu", i);
      if(!input(pin_B5))
         pressRb();
      delay_ms(30);
      i++;
   }
   
}

/*
#use rs232(baud=9600, xmit = PIN_C6, rcv = PIN_C7, parity = N, bits = 8, errors)

Int pacote[10];

void main()
{
enable_interrupts(global);
enable_interrupts(int_rda);
While(1)
{
Escreve seu c�digo��.....
Escreve seu c�digo��.....
}
}


#INT_RDA
void Void Receber_RS232()
{
pacote[i++]=getc();
printf (lcd_escreve,"%c",pacote[i]); //escreve no lcd o que recebeu
//� depende da sua configura��o de lcd
} 
*/



/*
void main(){
   char mat[80];
   char ret[10];

   lcd_init();

   while(true){
      k=getc();
      if(k == arg[i])
         i++;
      else
         if (i > 0)
            i--;
      if(i > 5){
         i = 0;
         lcd_putc('\f');
         recebe_rs232(mat);
         split(',', 4, ret, mat);
         k = ret[0];      
         split(',', 3, ret, mat);      
         printf(lcd_putc,"LT: %s  %c",ret, k);
         
         split(',', 6, ret, mat);
         k = ret[0];
         split(',', 5, ret, mat);
         printf(lcd_putc,"\r\nLG: %s %c",ret, k);
      }
   } 
}
*/
