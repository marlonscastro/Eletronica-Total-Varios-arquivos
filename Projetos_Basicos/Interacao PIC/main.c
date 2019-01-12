#include <16F84A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES XT                       //Crystal osc <= 4mhz for PCM/PCH , 3mhz to 10 mhz for PCD
#FUSES PUT                      //Power Up Timer
//#FUSES PROTECT                  //Code protected from reads

#use delay(clock=3000000)
//#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

void main()
{
   int tempo;
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
    
   tempo = 500;
   while (true){
   if (input(pin_B1)){
         output_low(pin_B7);
         delay_us(tempo);  
         } 
   else{
         output_high(pin_B7);
         delay_us(tempo);    
      }
   }

}
