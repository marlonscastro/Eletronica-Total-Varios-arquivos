#include <18F4550.h>
#use delay(clock=48000000)
#fuses HSPLL, PLL4, CPUDIV1, PUT, NOWDT, NOBROWNOUT, NOLVP

/* 
12Mhz input
HSPLL PLL3 CPUDIV2 
Total = 48Mhz 
------------------------------
16Mhz input 
HSPLL PLL4 CPUDIV2
------------------------
20Mhz 
HSPLL PLL5 CPUDIV2
-------------------------
4mHZ INPUT 
HSPLL PLL1 CPUDIV2

*/

//#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

#include <Extended_GLCD.c>

void main(){  
   int i;
   glcd_init(ON);
   KS0108_Gotoxy(0 0);  
   printf(KS0108_Printchar, "Linha 1");
   KS0108_Gotoxy(0 1);    
   printf(KS0108_Printchar, "Linha 2");   
   KS0108_Gotoxy(0 2); 
   printf(KS0108_Printchar, "Linha 3");
   KS0108_Gotoxy(0 3);   
   printf(KS0108_Printchar, "Linha 4");
   KS0108_Gotoxy(0 4);     
   printf(KS0108_Printchar, "Linha 5");
   KS0108_Gotoxy(0 5);   
   printf(KS0108_Printchar, "Linha 6");   
   KS0108_Gotoxy(0 6);   
   printf(KS0108_Printchar, "Linha 7");   
   KS0108_Gotoxy(0 7);    
   printf(KS0108_Printchar, "Linha 8");      
}
