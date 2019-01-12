#include <12F683.h>
#FUSES NOWDT, INTRC_IO, NOPUT, NOMCLR, NOPROTECT, NOCPD, NOBROWNOUT, IESO, FCMEN
#use delay(clock=4000000)
#use rs232(baud=9600,parity=N,xmit=PIN_A2,rcv=PIN_A3,bits=8,stream=PORT1)

#include "2408.c"

void main(){
   char chr;
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_vref(FALSE);
   setup_comparator(NC_NC);
   init_ext_eeprom();
   printf("teste");

   write_ext_eeprom(0x001, 'A');   
   chr = read_ext_eeprom(0x0001);
   
   printf("\n\r%c", chr);
   
}
