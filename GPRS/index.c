#include <18F4550.h>
#use delay(clock=48000000)
#fuses HSPLL, PLL4, CPUDIV1, PUT, NOWDT, NOBROWNOUT, NOLVP
#use rs232(baud=19200, parity=N, xmit=PIN_B6, rcv=PIN_B7)
#include "HMF6598SYH-PY.c"
#include "gprs-lib.c"

Enviar_SMS(char *Num, char *Msg){
   printf("AT+CMGF=1\r\n");
   printf("AT+CMGS=\""+*Num+"\"");   
   printf(*Msg);
   printf("CTRL + Z");
   return 1;
}

void main(void){
   while(true){}
}
