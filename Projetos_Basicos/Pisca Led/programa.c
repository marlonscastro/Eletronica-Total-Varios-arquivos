// primeiro exemplo

#include <16F876.h>
#use delay(clock=4000000)

//#use rs232(baud=19200, xmit=PIN_B2, rcv=PIN_B1)
#FUSES NOWDT, PUT, XT                   

void main()
{
   int tempo;
   tempo = 200;
   while (true){
      output_high(pin_B5);
      delay_ms(tempo);
      output_low(pin_B5);
      delay_ms(tempo);
   }
}
