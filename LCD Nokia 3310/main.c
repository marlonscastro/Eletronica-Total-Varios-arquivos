#include <16F628A.h>
#use delay(clock=4000000)
#fuses XT, PUT, NOWDT, NOBROWNOUT, NOLVP
#include "drive3310.c"
//#include <math.h>

void main(void)
{
   int8 k;
   nokia_init();
   printf(nokia_printchar, "Teste LCD");
   nokia_gotoxy(0, 1);   
   printf(nokia_printchar, "Marlon teste");   
   while(true){};
}
