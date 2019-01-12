#include <16F876.h>
#FUSES NOWDT, HS, NOPUT, NOBROWNOUT, NOLVP, NOCPD, NOWRT, NODEBUG, NOPROTECT
#use delay(clock=16000000)
//#USE SPI (MASTER, CLK=PIN_B1, DI=PIN_C7, DO=PIN_B0, BAUD = 1000000, MODE=0, BITS=8, STREAM=SPI_1, MSB_FIRST)

#define LED_STATUS   pin_b7

/*
#define STB_6        pin_b2
#define LATCH        pin_b3
#define CLK          pin_b1
#define DATA         pin_b0*/

#define MTA          pin_b3
#define MTB          pin_b2
#define MT_B         pin_b1
#define MT_A         pin_b0

int tempo = 0;

#int_TIMER0
void  TIMER0_isr(){
   tempo++;
   if(tempo == 70){   //  46 * 21,8ms =~ 1002,8ms ou 1,002 segundos 
      tempo=0;
      output_toggle(LED_STATUS);
   }
   //output_toggle(pin_c4);   
}
   char HalfStep6845[] = {8, 0b0111, 0b0110, 0b1111, 0b1001, 0b1011, 0b0010, 0b0011, 0b0001};  
   unsigned int delay = 0;
   char *type;
   #define LEFT 0
   #define RIGHT 1   
   void Stepper_setSequence(char *type_){
      type = type_;
   }
void main(void){
   int i;
   int32 dado = 0x0000000f;
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_32|RTCC_8_bit);  //RTCC_DIV_256    //21.8 ms overflow
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);   

   delay_ms(2000);
  /* for(i=0;i<8;i++){
   // INICIALIZAÇÃO 
   output_high(LATCH);    
   output_low(STB_6);      

 //  spi_xfer(SPI_1, 0xf1);
 
   for (i=32; i>0; i--) {
    output_low(CLK);
    if ((dado&0x80)==0)
      output_low(DATA);
    else
      output_high(DATA);
    output_high(CLK);
    dado<<=0x01;
   }
   output_high(STB_6); 
   output_low(LATCH);
   delay_ms(1);
   output_high(LATCH);    
   output_low(STB_6);     
   
   //for(i=0;i<20;i++)
      oneStep();
      dado <<= 0x01;
      delay_ms(100);
      }*/
      
   //Stepper_setSequence(HalfStep6845);
   while(true){
      //Stepper_Step(RIGHT);
   }
}

//---------------------------------------------------------------------------------

