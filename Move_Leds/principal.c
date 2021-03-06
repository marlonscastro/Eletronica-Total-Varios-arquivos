#include <16F628A.h>
#use delay(clock=4000000)
#FUSES XT                   

   byte mat[] = { 
         0b01000000, // 0000 0010  0
         0b00100100, // 0010 0100  1
         0b00010000  // 0000 1000  2
         //    321       123
   };

void mover(int comando){
   /* ---- COMANDOS ----
      1: Direita
      2: Esquerda
      3: Cima
      4: Baixo
   */
   int i, x;
   boolean flag = false;
   for(i = 0; i <= 2; i++)
      for(x = 1; x <= 3; x++)
      if(!flag){
         if(bit_test(mat[i], x)){
            bit_clear(mat[i], x);
            flag = true;            
            if(comando == 1){
               if(x == 3)
                  bit_set(mat[i], 1);
               else
                  bit_set(mat[i], x+1);
            }
            if(comando == 2){
               if(x == 1)
                  bit_set(mat[i], 3);
               else
                  bit_set(mat[i], x-1);
            }            
            if(comando == 3){
               if(i == 0)
                  bit_set(mat[2], x);
               else
                  bit_set(mat[i-1], x);
            } 
            if(comando == 4){
               if(i == 2)
                  bit_set(mat[0], x);
               else
                  bit_set(mat[i+1], x);
            } 
         }
      }         
   delay_ms(120);      
}

void main()
{  
   int var;
   while(true){
      for(var = 0; var < 3; var++){
         output_b(mat[var]);
         delay_ms(8);
      }
      if(!input(pin_A0)){
         mover(2);
      }
      if(!input(pin_A1)){
         mover(1);
      }      
      if(!input(pin_A2)){
         mover(3);
      }      
      if(!input(pin_A3)){
         mover(4);
      }            
   }
}
