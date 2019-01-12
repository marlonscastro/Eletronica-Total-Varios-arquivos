#include <12F675.h>
#device adc=10
#FUSES NOWDT, INTRC_IO, PUT, NOMCLR, NOBROWNOUT, NOPROTECT, NOCPD
#use delay(clock=4000000)
#use rs232(baud=9600, parity=N, xmit=PIN_A5, rcv=PIN_A2, bits=8, stream=PORT1)

#include "driver3310.c"

float valor;

void main(){
   //nokia_init();
   setup_adc_ports(AN0_ANALOG);     // Quais portas analogicas serão utilizadas
   setup_adc(ADC_CLOCK_DIV_64);     // Clock interno dividido por 64 
  // setup_counters(RTCC_INTERNAL,RTCC_DIV_2); // Configuração dos Timers
   setup_timer_1(T1_DISABLED);      // Timer 1 desativado
   setup_comparator(NC_NC_NC_NC);   // Comparador não utilizado
   setup_vref(FALSE);
   while(true){
      set_adc_channel(0);
      delay_ms( 600 );
      valor = (5.0/1024) * read_adc();
      printf("Valor = %f\n\r",valor);
      //valor = (4.2/1024) * read_adc() * 100;
      //printf("Valor = %ld\n\r", read_adc());      
      //printf(nokia_printchar, "MARLON TESTE");
   }
}

