#include <16F84A.h>
#use delay(clock=4000000)

#use rs232(baud=9600, parity=N, xmit=PIN_B6, rcv=PIN_B7)
#FUSES NOWDT, XT, NOPROTECT                   

void main()
{
   int tempo;
   tempo = 800;
   while (true){
      printf("Ol� mundo");
      delay_ms(tempo);
   }
}

