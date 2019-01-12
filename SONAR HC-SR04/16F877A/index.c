/************************************************************************************************ 
/ Thank to:
/
/  Used sonar - HC-SR04  & DYP c
/  If you are using DYP ME 007 or any other 5 pin sonar, Please note that not to take the 
/  pin named 'out'. Take echo instead. 
/  Pin configuration (5 pin)- VCC(+5) TRIG(Trigger pin) ECHO(Output pin) OUT(Not needed) GND (Ground) 
/  Pin configuration (4 pin)- VCC(+5) TRIG(Trigger pin) ECHO(Output pin) GND (Ground) 
/ 
/  Code by Bhanu Watawana 
/  0778111887 
/  Uva Wellassa University - Sri Lanka 
/  Mechatronics 
*///////////////////////////////////////////////////////////////////////////////////////////////// 
#include <16F887.h>
#device adc=8
#FUSES NOWDT, HS, NOPUT, PROTECT, NOBROWNOUT, NOLVP, NOCPD, NOWRT, NODEBUG 
#use delay(clock=20000000) 
#define LCD_DATA_PORT getenv("SFR:PORTB")   // declaro usar el portb para el control del lcd
#define LCD_ENABLE_PIN  PIN_B2                                    ////
#define LCD_RS_PIN      PIN_B0                                    ////
#define LCD_RW_PIN      PIN_B1                                    ////
#include <lcd.c>
int16 distance, time;          // Defining variables
// Defining the pins 
   #define trig pin_D1     // Change as you wish, can use any pin in the MCU 
   #define echo pin_D0     // Change as you wish, can use any pin in the MCU 
   #USE standard_io(d)
void main() { 
   lcd_init();                               // initiating the LCD 
   printf(LCD_PUTC, "\f Iniciando...");// for LCD & MCU restart troubleshooting
   delay_ms(1000);
   printf(LCD_PUTC, "\fProbando Sensor\nUltrasonico");// for LCD & MCU restart troubleshooting 
   delay_ms(1000);                              // Boot-up delay, for troubleshooting 
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);     // initiating timer 

   while(true){ 
      output_high(trig);                         // ping the sonar 
      delay_us(20);                            // sending 20us pulse 
      output_low(trig); 
      while(!input(ECHO)){}                       // wait for high state of echo pin 

      set_timer1(0);                           // setting timer zero 
      while(input(ECHO)){}                       // Wait for high state of echo pin 
       
      time=get_timer1();                       // Getting the time 
      distance=time*0.028 + 1.093 ;            // Calculating the distance                         
      printf(LCD_PUTC, "\fTiempo :%Lu \nDistancia = %Lu",time,distance); // Putting the time and distance to the LCD 
      delay_ms(1000); 
   } 
} 
