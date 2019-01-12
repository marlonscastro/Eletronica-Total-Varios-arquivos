#include <18F4550.h>
#use delay(clock=48000000)
#fuses HSPLL, PLL4, CPUDIV1, PUT, NOWDT, NOBROWNOUT, NOLVP              

   byte const tabela[] = { 
         0b10111111, // 0   dp-gfedcba
         0b10000110, // 1  
         0b11011011, // 2  
         0b11001111, // 3  
         0b11100110, // 4  
         0b11101101, // 5  
         0b11111101, // 6  
         0b10000111, // 7  
         0b11111111, // 8  
         0b11100111, // 9           
   };

void main()
{
   int valor;
   int16 atraso = 600;
   while(true){
     /* for (valor = 0; valor < 10; valor++){
         output_b(tabela[valor]);
         delay_us(atraso);            
      }*/
      output_high(pin_D0);
      delay_ms(600);
      output_low(pin_D0);
      delay_ms(600);      
   }
}

