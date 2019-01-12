#include <12F683.h>
#device adc=10

#FUSES NOWDT, INTRC_IO, NOPUT, NOMCLR, NOPROTECT, NOCPD, NOBROWNOUT, IESO, FCMEN
#use delay(clock=8000000)
#include "driver3310.c"

long x;
int s, m;
char c;
double W_100ms_preco = 0.00000000912, valor_total = 0.0, WtMedido = 0.0;

#int_TIMER0
void TIMER0_isr(void){
   x++;
   if(x>999){
      x=0;
      s+=1;
      c = ' ';      
      if(s>59){
         s=0;
         m+=1;
      }
   }
   if(x==500)
      c = '>';
   if(x % 100 == 0){
      WtMedido = 0.0048828125*read_adc()*215; 
      valor_total = valor_total + (W_100ms_preco * WtMedido);
   }
}

#int_RA
void isr_ra(){
   if(!input(pin_a3))
      disable_interrupts(INT_TIMER0);
}

void main(){
   x=s=m=0;
   nokia_init();
   setup_adc(ADC_CLOCK_DIV_64);
   setup_adc_ports(sAN0);
   set_adc_channel(0);
  
   setup_comparator(NC_NC_NC_NC);                           // Comparador não utilizado
   setup_vref(FALSE);                                       // VREF não configurado    
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_8|RTCC_8_bit);      //1.0 ms overflow
   setup_comparator(NC_NC);
    
   enable_interrupts(INT_TIMER0);
   enable_interrupts(INT_RA);
   enable_interrupts(GLOBAL);


  
   while(true){
      delay_ms(20);
      nokia_gotoxy(0,2);      
      printf(nokia_printchar, "%02d:%02d %fW ", m, s, WtMedido);       
      nokia_gotoxy(0,5);      
      printf(nokia_printchar, "R$ %1.9f", valor_total);
   }
}
