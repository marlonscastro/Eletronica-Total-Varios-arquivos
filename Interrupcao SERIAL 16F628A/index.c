#include <16f628a.h>
#FUSES NOWDT, NOBROWNOUT, PUT, XT   
#use delay(clock=4000000)

#use rs232(baud=9600, parity=N, xmit=PIN_B2, rcv=PIN_B1, STREAM=gprs)       // GPRS

//#use rs232(baud=9600, parity=N, xmit=PIN_B2, rcv=PIN_B1, STREAM=serial)     // Ecoar na Serial
//#use rs232(baud=9600, parity=N, xmit=PIN_A2, rcv=PIN_A3, STREAM=gprs)       // GPRS
#use rs232(baud=9600, parity=N, xmit=PIN_A0, rcv=PIN_A1, STREAM=serial)   // Ecoar na Serial

char chr[40];
int cont = 0;
int i = 0;
Boolean OK = false, timeOut = false;

#INT_TIMER0
void TimeOut_Timer(){

   static boolean led;
   static int16 conta;

   /*
   4Mhz / 4       = 1Mhz   
   1Mhz / 64      = 15625 Hz (15,6 Khz)
   Periodo        = 0,000064 (64uS)
   0,000064 x 256 = 0,016384 (16,38ms)
   0,016384 x 20  = 0,327 s
   */

   conta++;
   if (conta == 20){
      timeOut = true;
      conta=0;
      led = !led;  // inverte o led
      output_bit (pin_b0,led);
   }   
}

#INT_RDA
void serial_isr(){ 
   //disable_interrupts(INT_RDA);
   
   set_timer0(0);
   clear_interrupt(int_timer0);
   enable_interrupts(INT_TIMER0);  
   
   if(timeOut){
      fputs("Sem Recepção", serial);
      timeOut = false;
   }
   
   while(kbhit(gprs)){
      chr[i] = fgetc(gprs);
      if (chr[i] == '\n'){
         cont++;
         if(cont == 3){
            cont = 0;
            chr[i+1] = '\0';
            i = 0;
            OK = true;
            fputs(chr, serial);            
            break;
         }
      } else i++;
   }
   disable_interrupts(INT_TIMER0);   
   // output_high(pin_b0);   
}

void main(){
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_RDA); 
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_64);
   //enable_interrupts(INT_TIMER0);
   //while(true){}
   /*while(true){
      if (!OK)
         fputs("AT\r", gprs);
      while(true){
         if(OK){
            OK = false;
            break; 
         }
      }
      delay_ms(1000);
   }*/
      delay_ms(2000);
      fputs("AT\r", gprs);      
      delay_ms(5000);      
} 



/*


#int_timer0
void timer0isr(){                                                                       
   if (waitfor) 
      --waitfor;
   else 
      RC_timeout=true;
}

void ftget_string(char *s, int max, int ticks){
   int len;
   char c;
   waitfor=ticks;
   RC_timeout=false;                                             

   set_timer0(0);
   clear_interrupt(int_timer0);
   enable_interrupts(INT_TIMER0);
   --max;
   len=0;
   do{
      while(!kbhit(GSM)){
         if(RC_timeout){
            c=10;
            break;
         }
      }
      if (kbhit(GSM))
      c=fgetc(GSM);
      if ((c>=' ')&&(c<='~'))
         if(len<=max){
            s[len++]=c;
         }
   }while(c!=10);
   s[len]=0;
   disable_interrupts(INT_TIMER0);
} 
*/
