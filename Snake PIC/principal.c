#include <16F628A.h>
#use delay(clock=4000000)
#FUSES XT, NOWDT, NOMCLR, NOLVP
   int comando = 1, tam = 2, sem = 0, tempo = 100;
   int col[24] = {4,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
   int lin[24] = {5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
   int comida[] = {1,1};
byte mat[] = {
         0b00000000,
         0b00000010,
         0b00000000,  
         0b00000000,
         0b00000000,
         0b00011000, 
         0b00000000,
         0b00000000,
   };
void mover_auto(int *col, int *lin){
   /* --- COMANDOS ---  1: Esquerda 2: Direita 3: Cima  4: Baixo  */
   int i, x, tmp;
   for(x=tam; x>0; x--){
      i = x-1;
      if(x == tam){
         tmp = col[i];
         bit_clear(mat[lin[i]], tmp);
      }
      if(i > 0){
         col[i] = col[i-1];      
         lin[i] = lin[i-1];         
      }
      else{
         if(comando == 1){
            if(col[i] == 7)
               col[i] = 0;
            else
               col[i]++;
         }
         if(comando == 2){
            if(col[i] == 0)
               col[i] = 7;
            else
               col[i]--;
         }
         if(comando == 3){
            if(lin[i] == 0)
               lin[i] = 7;
            else
               lin[i]--;
         }
         if(comando == 4){
            if(lin[i] == 7)
               lin[i] = 0;
            else
               lin[i]++;
         }
      }
   }
   for(i = 0; i < tam; i++){
      tmp = col[i];
      bit_set(mat[lin[i]], tmp);
   }
   // Cobra Morreu
   for(i = 0; i < tam-1; i++){
      if((col[0] == col[i+1]) && (lin[0] == lin[i+1])){
         for(x = 0; x < tam; x++){      
            tmp = col[x];
            bit_clear(mat[lin[x]], tmp);
         }
         bit_clear(mat[comida[0]], comida[1]);
         col[0] = 4;
         col[1] = 3;
         lin[0] = 5;
         lin[1] = 5;
         comida[0] = 1;
         comida[1] = 1;
         comando = 1;
         tam = 2;
         tempo = 100;
         break;
      }
   }   
   // Acho a comida
   if((col[0] == comida[1]) && (lin[0] == comida[0])){
      if(sem > 63)
         sem = sem % 64;
      for(i = 0; i < 8; i++){
         for(x = 0; x < 8; x++){
            if(sem > 0){
               sem--;
            }
            if(sem == 0){
               for(tmp = 0; tmp < tam-1; tmp++){
                  if((col[tmp] == x) && (lin[tmp] == i)){
                     if((i == 7) && (x == 7)){
                        i = 0;
                        x = 0;
                     }
                     sem++;
                     break;
                  }
               }
               if(sem == 0){
                  comida[0] = i;
                  comida[1] = x;
                  bit_set(mat[i], x);
                  break;               
               }
            }
         }   
         if(sem == 0)
            break;
      }
      if(tam < 24){
         tam++;
         tempo = tempo - 4;
      }
   }
}
void main(){
   int x;
   long int cont = 0;
   output_high(pin_a1);
   output_low(pin_a1);   
   output_high(pin_a0);   
   while(true){
      for (x = 0; x < 8; x++){
         output_low(pin_a0); 
         output_high(pin_a0);      
         output_b(~mat[x]);
         delay_ms(1);
      }
      output_high(pin_a1);
      output_low(pin_a1);
      if(!input(pin_A2)){
         if(comando != 1)
            comando = 2;
         sem = sem + 4;
      }
      if(!input(pin_A3)){
         if(comando != 3)      
            comando = 4;
         sem = sem + 4;
      }
      if(!input(pin_A4)){
         if(comando != 2)      
            comando = 1;
         sem = sem + 4;
      }
      if(!input(pin_A5)){
         if(comando != 4)    
            comando = 3;
         sem = sem + 4;
      }
      // Pisca Comida
      if((cont % 4) == 0){
         if((cont % 8) > 0)
            bit_clear(mat[comida[0]], comida[1]);      
         else            
            bit_set(mat[comida[0]], comida[1]);                  
      }
      // Movimenta a cobra
      if(cont > tempo){
         cont = 0;
         mover_auto(col, lin);
      }
      else
         cont++;
   }
}

