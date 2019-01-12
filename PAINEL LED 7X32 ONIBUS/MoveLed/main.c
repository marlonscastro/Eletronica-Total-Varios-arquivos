#include <16F876.h>
#device adc=10
#FUSES NOWDT, HS, NOPUT, NOBROWNOUT, NOLVP, NOCPD, NOWRT, NODEBUG, NOPROTECT
#use delay(clock=16000000)
#define LED_STATUS   pin_a1
#include "driverLD7x32.c"

int tempo;
int x_obj = 3, y_obj = 3;

#int_TIMER0
void  TIMER0_isr(void){
   tempo++;
   if(tempo == 20){
      tempo=0;
      output_toggle(LED_STATUS);
   }
   varre_coluna();    
}

void main(){
   int i;
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_64|RTCC_8_bit);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);

   /* INICIO DO GAME R-TYPE Led */
   bit_set(MAT[x_obj], y_obj);      
   bit_set(MAT[x_obj-1], y_obj);   
   while(true){
      for(i=x_obj+1;i<32;i++){
         put_led(i, y_obj, ON);
         if(i>(x_obj+1))
            put_led((i-1), y_obj, OFF);               
         delay_us(400);
         // Piscar Cauda : Chamas da nave
         if((i%3) == 0){
            bit_clear(MAT[x_obj-1], y_obj);            
         }
         else                 
            bit_set(MAT[x_obj-1], y_obj);
      }
   }
}
