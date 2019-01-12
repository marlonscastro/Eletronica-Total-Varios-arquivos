//#include <18F4550.h>
#include <16F877A.h>
#use delay(clock=4000000)

#FUSES NOWDT, NOBROWNOUT, PUT, XT   

#use rs232(baud=19200, parity=N, xmit=PIN_D4, rcv=PIN_D5, stream = gprs)   // GPs
#use rs232(baud=19200, parity=N, xmit=PIN_D6, rcv=PIN_D7, stream = serial)   // Ecoar na Serial

void main(){
   /*char chr[40];   
   int i = 0;
   while(true){
       chr[i] = fgetc(gprs);
       if(chr[i] == '\r'){
         fprintf(serial, "%s", chr);               
         i = 0;
       }
       i++;
   }*/
   int i = 0;
   char k;  
   while(true){  
      fprintf(serial, "\"inicio da com serial\"\r\n");
      delay_ms(1000);
   }
   while(true){   
      k = fgetc(gprs);
      fputc(k, serial); 
      if (i == 10){
            fprintf(serial, "Beleza Doido: \"teste serial\"\r\n"); 
            i=0;
      }
      i++;
   }

}
  /* int tempo;
   tempo = 1000;
   while (true){
      output_high(pin_D2);
      delay_ms(tempo);
      output_low(pin_D2);
      delay_ms(tempo);

      delay_ms(tempo);
      fprintf(serial, "Beleza Doido: \"teste serial\"\r\n"); 
   }*/


