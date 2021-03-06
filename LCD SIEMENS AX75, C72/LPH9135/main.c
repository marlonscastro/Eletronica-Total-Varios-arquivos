#include <16F876.h>
#FUSES NOWDT, HS, NOPUT, NOBROWNOUT, NOLVP, NOCPD, NOWRT, NODEBUG, NOPROTECT
#use delay(clock=16000000)

#include "LPH9135.h" // Controlador do Siemens Ax75, c72

#define LED_STATUS   pin_a1

#define SPI_MODE_0  (SPI_L_TO_H | SPI_XMIT_L_TO_H)
#define SPI_MODE_1  (SPI_L_TO_H)
#define SPI_MODE_2  (SPI_H_TO_L)
#define SPI_MODE_3  (SPI_H_TO_L | SPI_XMIT_L_TO_H)

int tempo;
char text[30];

#int_TIMER0
void  TIMER0_isr(void){
   tempo++;
   if(tempo == 70){   //  46 * 21,8ms =~ 1002,8ms ou 1,002 segundos 
      tempo=0;
      output_toggle(LED_STATUS);
   }
   output_toggle(pin_c4);   
}
void main(void){
   int i;
   setup_spi(SPI_MASTER | SPI_MODE_0 | SPI_CLK_DIV_4 );   
   //setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_32|RTCC_8_bit);  //RTCC_DIV_256    //21.8 ms overflow
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);   
   
   delay_ms(1000);
   LCD_init();
   LCD_FillScreen(RED);   // 0bRRRGGGBB
   delay_ms(1000);
   LCD_FillScreen(GREEN);   // 0bRRRGGGBB
   delay_ms(1000);
   LCD_FillScreen(BLUE);   // 0bRRRGGGBB
   delay_ms(1000);
   /*LCD_Putchar('M', 30, 30, WHITE, BLUE, 1, 1, 0);
   LCD_Putchar('a', 37, 30, WHITE, RED, 1, 1, 0);
   LCD_Putchar('r', 43, 30, WHITE, BLACK, 1, 1, 0);   
   LCD_Putchar('l', 50, 30, WHITE, BLACK, 1, 1, 0);*/
   /*LCD_FillScreen(WHITE);   // 0bRRRGGGBB
   delay_ms(1000);
   Put_Pixel(10,10, GREEN);
   delay_ms(500);
   LCD_Putchar('M', 30, 30, WHITE, BLACK, 1, 1, 1); */  
   while(true){}
}

//---------------------------------------------------------------------------------
