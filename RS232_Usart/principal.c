// Este programa ecoa o caractere enviado serialmente, al�m de imprimi-lo
// no display
#include <16f877A.h>
#use delay(clock=4000000)
#fuses HS,NOWDT,PUT,NOBROWNOUT,NOLVP
#include <mod_lcd.c>
#include <usart.c>
void main()
{
   char k[];
   lcd_ini();
   setup_adc_ports(no_analogs);
   //usart_inicializa (12,1); // velocidade: 19200
   usart_inicializa (12,0); // velocidade: 4800
   lcd_pos_xy(1,2);
   while(true){
      k=usart_recebe();
      usart_transmite (k);
      printf (lcd_escreve,"%c",k);
   }
}

