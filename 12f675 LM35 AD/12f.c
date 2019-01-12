#include <12f675.h>
#device adc=8
#use delay(clock=4000000)
#fuses  INTRC_IO,NOWDT, noprotect
#use rs232(baud=9600, xmit=PIN_A2,rcv=PIN_A3)

int valor;

void main(){
   setup_adc_ports(AN0_ANALOG|AN1_ANALOG);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_counters(RTCC_INTERNAL,RTCC_DIV_2);
   setup_timer_1(T1_DISABLED);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   while(1){
      set_adc_channel(0);
      delay_ms( 300 );
      valor = (4.2/1024) * read_adc() * 100;
      printf("Valor = %d\n\r",valor);
   }
}
