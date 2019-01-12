#include <16F876.h>
#device adc=10
#FUSES NOWDT, HS, NOPUT, NOBROWNOUT, NOLVP, NOCPD, NOWRT, NODEBUG, NOPROTECT
#use delay(clock=16000000)

#define LED_STATUS   pin_a1
#define DATA         pin_c4   
#define SCK          pin_c3

int tempo;

#int_TIMER0
void  TIMER0_isr(void){
   tempo++;
   if(tempo == 45){   //  46 * 21,8ms =~ 1002,8ms ou 1,002 segundos 
      tempo=0;
      output_toggle(LED_STATUS);
   }
}
void Write_led_panel(int16 chr){
   int i;
   for(i=0;i<16;i++){
      output_low(SCK);
      if((chr&0x01) == 0) output_low(DATA);
      else output_high(DATA);
      output_high(SCK);
      chr=chr>>1;
   }
   output_high(DATA);
}

void main(){
   double amp;
   long i; 
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256|RTCC_8_bit);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   while(true){
      Write_led_panel(0xea);         
      delay_ms(100);
   }
}

