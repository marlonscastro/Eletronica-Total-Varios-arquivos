#include <18F4520.h>
#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES H4                       //High speed osc with HW enabled 4X PLL
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOBROWNOUT               //No brownout reset
#FUSES BORV20                   //Brownout reset at 2.0V
#FUSES PUT                      //Power Up Timer
#FUSES NOCPD                    //No EE protection
#FUSES STVREN                   //Stack full/underflow will cause reset
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOWRT                    //Program memory not write protected
#FUSES NOWRTD                   //Data EEPROM not write protected
#FUSES IESO                     //Internal External Switch Over mode enabled
#FUSES FCMEN                    //Fail-safe clock monitor enabled
#FUSES PBADEN                   //PORTB pins are configured as analog input channels on RESET
#FUSES NOWRTC                   //configuration not registers write protected
#FUSES NOWRTB                   //Boot block not write protected
#FUSES NOEBTR                   //Memory not protected from table reads
#FUSES NOEBTRB                  //Boot block not protected from table reads
#FUSES NOCPB                    //No Boot Block code protection
#FUSES LPT1OSC                  //Timer1 configured for low-power operation
#FUSES MCLR                     //Master Clear pin enabled
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)

#use delay(clock=40000000)
//#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

#include <Extended_GLCD.c>

char inverse_test_txt[]  = "INVERSE IMAGE TEST";
char image_txt[]         = "IMAGE";
char box_3D_txt[]        = "3D BOX";
char cir_seg_txt[]       = "SEGMENT OF A CIRCLE";
char on_xy_txt[]         = "ON 'XY' COORDINATE";
char depth2_txt[]        = "DEPTH VALUE=2";
char depth3_txt[]        = "DEPTH VALUE=3";

void main()
{  
   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_OFF|ADC_TAD_MUL_0);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

   glcd_init(ON);
   
   glcd_image(NO);
   delay_ms(4000);

   while (true)
   {
      int i;
      
      // FULL SCREEN INVERSE IMAGE TEST
      glcd_fillscreen(OFF);
      glcd_text57(10,30,inverse_test_txt,1,ON);
      delay_ms(3000);
      glcd_fillscreen(OFF);      
      
      for (i=0;i<=1;++i)
      {
         glcd_image(NO);
         delay_ms(1500);
         glcd_image(YES);
         delay_ms(1500);
      }      
      
      // IMAGE ON "XY" COORDINATE TEST
      glcd_fillscreen(OFF);
      glcd_text57(48,22,image_txt,1,ON);
      glcd_text57(10,37,on_xy_txt,1,ON);
      delay_ms(3000);
      glcd_fillscreen(OFF);
      glcd_image_xy(0,0,NO);
      delay_ms(1500);
      glcd_image_xy(64,0,NO);
      delay_ms(1500);      
      glcd_image_xy(0,32,NO);
      delay_ms(1500);
      glcd_image_xy(64,32,NO);
      delay_ms(1500);
      glcd_image_xy(32,16,NO);
      delay_ms(3000);
      

      // 3D-BOX TEST
      glcd_fillscreen(OFF);
      glcd_text57(45,22,box_3D_txt,1,ON);
      glcd_text57(10,37,on_xy_txt,1,ON);
      delay_ms(3000);
      glcd_fillscreen(OFF);
      glcd_text57(25,30,depth2_txt,1,ON);
      delay_ms(2000);
      glcd_fillscreen(OFF);
      glcd_3Dbox(32,16,64,32,2,ON);
      delay_ms(3000);
      glcd_fillscreen(OFF);
      glcd_text57(25,30,depth3_txt,1,ON);
      delay_ms(2000);
      glcd_fillscreen(OFF);
      glcd_3Dbox(32,16,64,32,3,ON);
      delay_ms(3000);
      
      
      // SEGMENT OF A CIRCLE TEST
      glcd_fillscreen(OFF);
      glcd_text57(7,22,cir_seg_txt,1,ON);
      glcd_text57(10,37,on_xy_txt,1,ON);
      delay_ms(3000);
      glcd_fillscreen(OFF);
      glcd_circle_seg(64,32,25,0,90,ON);
      delay_ms(2000);
      glcd_fillscreen(OFF);
      glcd_circle_seg(64,32,25,90,180,ON);
      delay_ms(2000);
      glcd_fillscreen(OFF);
      glcd_circle_seg(64,32,25,180,270,ON);
      delay_ms(2000);
      glcd_fillscreen(OFF);
      glcd_circle_seg(64,32,25,270,360,ON);
      delay_ms(2000);
      
      glcd_fillscreen(OFF);
      glcd_circle_seg(64,32,25,0,135,ON);
      delay_ms(2000);
      glcd_fillscreen(OFF);
      glcd_circle_seg(64,32,25,90,315,ON);
      delay_ms(2000);
      glcd_fillscreen(OFF);
      glcd_circle_seg(64,32,25,0,360,ON);
      delay_ms(2000);
   }
}
