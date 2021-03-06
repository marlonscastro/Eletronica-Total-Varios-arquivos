#include <16F73.h>
#use delay(clock=16000000)
#FUSES NOWDT, HS, NOPUT, NOPROTECT, NOBROWNOUT 

int contaTempo = 0, i=0, AltOBJ=2;
int contaBotoes = 0, desloc = 3, flag = 0, largOBJ = 2;
int1 bit1, bit2;

byte OBJ[2] = {0b00011000,
               0b00011000};
byte vm[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
byte vd[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  
#INT_TIMER0
void RTTC_isr(void){
   int y, t;
   contaTempo++;
   if (contaTempo==60){ // ~1seg
      if((i == 8-AltOBJ) || (((vm[i+AltOBJ])&(OBJ[AltOBJ-1])) != 0)){
         y = 0;
         for(t=i;t<AltOBJ+i;t++){
            vm[t] |= OBJ[y];
            y++;
         }
         // ------------------ Se completou a completou uma linha
         for(t=0;t<8;t++){
            if(vm[t] == 0xff){
               vm[t] = 0x00;
               for(y=t;y>0;y--){
                  vm[y] = vm[y-1];
               }
            }
         }
         // --------------------------------------
         i = 0;
      }
      else i++;
      contaTempo = 0;
   }
}
void main(){
   int x,y;
   setup_timer_0 (RTCC_DIV_256);
   set_timer0(0);
   enable_interrupts (INT_TIMER0); 
   enable_interrupts(GLOBAL);  
   output_high(pin_a5);
   output_low(pin_a5);   
   output_high(pin_a4);
   while(true){
      y=0;
      for (x = 0; x < 8; x++){
         output_low(pin_a4);
         output_high(pin_a4);
         if((x>=i) && (x < AltOBJ+i)){
            output_c(~(vm[x] | OBJ[y]));
            y++;
         }
         else
            output_c(~vm[x]);
         delay_ms(2);
       
      }
      output_high(pin_a5); 
      output_low(pin_a5);  
      
      contaBotoes++;
      if (contaBotoes > 2){
         if(!input(pin_a3)){ // Direita
            if(desloc < (8-AltOBJ)){
               desloc++;
               for(x=0;x<AltOBJ;x++)
                  OBJ[x] >>= 1;
            }
         }
         if(!input(pin_a1)){ // esq
            if(desloc > 0){
               for(x=0;x<altOBJ;x++){
                  //if((bit_test(OBJ[x],desloc) & bit_test(vm[i+x],desloc-1)) == 0)
                  bit1 = bit_test(OBJ[x],desloc);
                  bit2 = bit_test(vm[i+x],desloc-1);
                  if((bit1 & bit2)!=1){
                     flag = 1;
                  }
               }
               if(flag==1){
                  flag = 0;
                  desloc--;
                  for(x=0;x<AltOBJ;x++)
                     OBJ[x] <<= 1;
               }
            }
         }       
         contaBotoes = 0;
      }
      /*      a0 - baixo  a1 - esq  a2 - cima  a3 - dir      */
   }
}

