#include <16F688.h>
#device adc=10
#FUSES NOWDT, INTRC_IO, NOPUT, MCLR, NOPROTECT, NOCPD, NOBROWNOUT, NOIESO, NOFCMEN
#use delay(clock=4000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C4,rcv=PIN_C5,bits=8,stream=PORT1)

#include "PCF8833.c"

void main(){
   char Texto[] = "!!!!!!";
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_timer_1(T1_DISABLED);      // Timer 1 desativado
   setup_comparator(NC_NC_NC_NC);   // Comparador não utilizado
   setup_vref(FALSE); 
   glcd_init(100);
   delay_ms(1000);
   glcd_cls(BLACK);   
   while(TRUE){
        delay_ms(1000);  
        glcd_circle(50,50,20,YES,BLUE);
        glcd_text57(10,10, texto, 1, WHITE, BLACK);
   }
}
