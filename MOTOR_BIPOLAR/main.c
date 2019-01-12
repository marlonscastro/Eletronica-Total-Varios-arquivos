#include <16F876.h>
#FUSES NOWDT, HS, NOPUT, NOBROWNOUT, NOLVP, NOCPD, NOWRT, NODEBUG, NOPROTECT
#use delay(clock=16000000)
//#USE SPI (MASTER, CLK=PIN_B1, DI=PIN_C7, DO=PIN_B0, BAUD = 1000000, MODE=0, BITS=8, STREAM=SPI_1, MSB_FIRST)

#define LED_STATUS   pin_b7

#define MTA          pin_b3
#define MTB          pin_b2
#define MT_B         pin_b1
#define MT_A         pin_b0

int tempo;

#int_TIMER0
void  TIMER0_isr(void){
   tempo++;
   if(tempo == 70){   //  46 * 21,8ms =~ 1002,8ms ou 1,002 segundos 
      tempo=0;
      output_toggle(LED_STATUS);
   }
   output_toggle(pin_c4);   
}

// ----------------------- Função teste Motor de Passo -----------------------------

   //char WaveStep[] = {4, 0b0001, 0b0010, 0b0100, 0b1000};
   char WaveStep[] = {4, 0b0001, 0b0010, 0b0100, 0b1000};
   char FullStep[] = {4, 0b0011, 0b0110, 0b1100, 0b1001};
   char HalfStep[] = {8, 0b0001, 0b0011, 0b0010, 0b0110, 0b0100, 0b1100, 0b1000, 0b1001};
   //                       A,B,_B,_A 
   char HalfStep6845[] = {8, 0b0111, 0b0110, 0b1111, 0b1001, 0b1011, 0b0010, 0b0011, 0b0001};  
                        
   unsigned int delay = 0;
   char *type;
   #define LEFT 0
   #define RIGHT 1
   
   void Stepper_setSequence(char *type_){
    type = type_;
   }
   
   void Stepper_Speed(unsigned nSteps, char rpm){
      delay = 60000 / (nSteps * rpm);
   }
   
   void Stepper_Step(char direcao){
      static unsigned stepCount = 0;
      char len = type[0];
      char val = type[(stepCount % len) + 1];
      
      if(direcao == 0)
         stepCount++;
      else
         stepCount--;
      
      if(bit_test(val, 0))
         output_high(MT_A);
      else
         output_low(MT_A);  
      
      if(bit_test(val, 1))
         output_high(MT_B);
      else
         output_low(MT_B);  
      
      if(bit_test(val, 2))
         output_high(MTB);
      else
         output_low(MTB);  
      
      if(bit_test(val, 3))
         output_high(MTA);
      else
         output_low(MTA);           
      delay_ms(10);
   }
void main(void){
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_32|RTCC_8_bit);  //RTCC_DIV_256    //21.8 ms overflow
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);   

   delay_ms(2000);
      
   Stepper_Speed(72,2);
   Stepper_setSequence(HalfStep6845);

   while(true){
      Stepper_Step(LEFT);
   }
}

//---------------------------------------------------------------------------------

