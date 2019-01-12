#include <16F628A.h>
#use delay(clock=4000000)
#FUSES HS, NOWDT, NOLVP

void main(){
   int x, i = 0, tempo = 100;
   byte mat[] = {
         0b00101001,
         0b00011001,
         0b00011010,  
         0b00110010,
         0b00110100,
         0b00101100

        /* 0b00101001,
         0b00011010,         
         0b00110100*/
   };
   /*byte mat[] = {
         0b00001110,
         0b00000111,
         0b00100011,  
         0b00101001,
         0b00011001,
         0b00011010         
   };*/
   while(true){
      for (x = 0; x < 6; x++){
         output_b(mat[x]);
         delay_ms(tempo);
      }
      i++;
      if(i > 4){
         i = 0;
         if(tempo > 6)
            tempo = tempo - 4;
         
      }
   }
}
