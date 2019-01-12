// ## Exemplo - Apresenta��o de dados em displays de 7 Seg // 
// --------------------   By Marlon   ---------------------

#include <16F877A.h>
#use delay(clock=4000000)

#FUSES NOWDT, NOBROWNOUT, PUT, XT   

#define     K1  pin_a0   // Catodo 1 - Dezenas
#define     K2  pin_a1   // Catodo 2 - Unidades

   byte const nums[] = {    
         0b10111111, // 0  dp-gfedcba
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
   int i = 0;

#INT_TIMER0
void trata_t0(){
   output_b(nums[i/10]);   //  Digito do Primeiro Display // Parte inteira da divis�o de i/10
   output_high(K1);   
   output_low(K2);   
   output_b(nums[i%10]);   //  Digito do Segundo Display //  Resto da Divis�o
   output_high(K2);
   output_low(K1);
}

void main(){
   enable_interrupts(GLOBAL);
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_128);  // 32,7 mS   @   ~30/s
   enable_interrupts(INT_TIMER0);
   while(true){
      delay_ms(1000);
      i++;
      if(i > 99)
         i = 0;
   }
}




