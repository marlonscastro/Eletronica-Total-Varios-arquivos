#include <16F628A.h>
#use delay(clock=4000000)
#FUSES NOWDT, NOBROWNOUT, PUT, XT   

#use rs232(baud=9600, parity=N, xmit=PIN_A2, rcv=PIN_A3, STREAM=gprs)   // GPRS
#use rs232(baud=9600, parity=N, xmit=PIN_A0, rcv=PIN_A1, STREAM=serial)   // Ecoar na Serial

#include <string.h>

char *retNum(char *str, char* strret){
   int i = 0, j = 0, cont = 0;
   if (strlen(str) > 20){
      while(i < strlen(str)){
         if(cont == 1){
            strret[j] = str[i];
            j++;
         }
         if (str[i] == '\"' ){
            cont++;
            if(cont == 2){
               fputs("ATH\r", gprs);            
               strret[j-1] = '\0';
               break;
            }
         }
         i++;
      }
      return strret;
   }
}

void main(){
   char temp[12];
   char chr[35];
   //char vet[] = "\r\nRING\r\n+CLIP: \"85851611\",161,\"\",,\"\",0\r\n";
   char vet[35];   
   while(true){
      /*
      delay_ms(2000);
      fprintf(serial, "%s", vet);
      fprintf(serial, "Numero: %s ", retNum(vet, temp));
      */
      /*fgets(vet,gprs);
      if ((strlen(vet) > 30)){
         fputs(retNum(vet, temp), serial);
         break;
      }*/ 
      fputs("ATH\r", gprs);        
   }
   //sprintf(chr, "AT+CMGS=\"%s\"\r", retNum(vet, temp));      
   sprintf(chr, "AT+CMGS=\"%s\"\r", temp);                  
       fputs("AT+CMGF=1\r", gprs);
         fputs(chr, gprs);
         sprintf(chr, "Teste de mensagem%c", 0x1a);
         fputs(chr, gprs);
         

  // fputs(temp, serial);
   /*char chr[35];
 
   delay_ms(3000);
   fputs("AT+CMGF=1\r", gprs);
   delay_ms(1000);
   fputs("AT+CMGS=\"8185851611\"\r", gprs);
   delay_ms(2000);
   sprintf(chr, "Lt:08 00.8226S\r\nLg:034 54.5643W%c", 0x1a);
   fputs(chr, gprs);   
   
   while(true){
      fgets(chr,gprs);
      fputs(chr, serial);
   }*/
}

/*


#fuses HS,NOWDT,NOPROTECT
#include <16f628A.H>
#include <string.h>
#use delay(clock=4000000)
#use rs232(baud=9600, xmit=PIN_B2, rcv=PIN_B1)

#int_rda
trata(void){
   output_low(pin_b0);
}

void main(){
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   printf("Isso funciona\n\r");
   output_high(pin_b0);
   while(True){
      output_high(pin_b5);
      delay_ms(500);
      output_low(pin_b5);
      delay_ms(500);
   }
} */
