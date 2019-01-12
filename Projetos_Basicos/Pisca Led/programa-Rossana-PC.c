// primeiro exemplo

#include <16F877a.h>
#use delay(clock=4000000)

//#use rs232(baud=19200, xmit=PIN_B2, rcv=PIN_B1)
#FUSES NOWDT, PUT, XT                   

void main()
{
   int tempo;
   tempo = 500;
   while (true){
      output_high(pin_D2);
      delay_ms(tempo);
      output_
      low(pin_D2);
      delay_ms(tempo);
   }
}
