// Display Sete Segmentos 

#include <16F84A.h>
#use delay(clock=3000000)
//#use rs232(baud=19200, xmit=PIN_B2, rcv=PIN_B1)
#FUSES XT                   

   byte const tabela[] = { 
         0b10111111, // 0  
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
   int16 atraso = 300;
   while(true){
      for (valor = 0; valor < 10; valor++){
         output_b(tabela[valor]);
         delay_us(atraso);            
      }
      /*if (atraso > 25)
         atraso = atraso/2;
      else
         atraso = 800;*/
   }
}

