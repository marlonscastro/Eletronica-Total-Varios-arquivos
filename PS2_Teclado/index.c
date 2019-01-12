#include <18F4550.h>
#use delay(clock=48000000)
#fuses HSPLL, PLL4, CPUDIV1, PUT, NOWDT, NOBROWNOUT, NOLVP
#use rs232(baud=9600, xmit=PIN_C4, rcv=PIN_C5, FORCE_SW, BITS=8, STOP=1, PARITY=N, INVERT)

#include "HMF6598SYH-PY.c"
#include "ps2lib.c"

#define SCL     pin_b0
#define SDA     pin_b1


Enviar_SMS(char *Num, char *Msg){
   printf("AT+CMGF=1\r\n");
   printf("AT+CMGS=\""+*Num+"\"");   
   printf(*Msg);
   printf("CTRL + Z");
   return 1;
}

char Read_Ps2Key(){
   return getc();
}

void main(void){
   while(true){}
}

