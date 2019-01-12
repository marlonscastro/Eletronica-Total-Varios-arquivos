#include <16F628A.h>

#use delay(clock=4000000)
#FUSES NOWDT, NOBROWNOUT, PUT, XT   

#use rs232(baud=9600, parity=N, xmit=PIN_B2, rcv=PIN_B1, STREAM=gprs)       // GPRS
#use rs232(baud=9600, parity=N, xmit=PIN_A0, rcv=PIN_A1, STREAM=serial)   // Ecoar na Serial

#include <string.h>

   boolean podeEntrar = false;   

   //char chr[35];
   //char vet[] = "\r\nRING\r\n+CLIP: \"85851611\",161,\"\",,\"\",0\r\n";
   char arg[6] = {'+', 'C', 'L', 'I', 'P', ':'};
   char k;
   int i = 0,cont = 0, y = 0, limpar = 0;   

char* retNum(char *str, char* strret){  //   "85851611","",161,
   int i = 0, j = 0, cont = 0;
   //if (strlen(str) > 11){
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
   //}
   return(strret);   
}
#INT_RDA
void serial_isr(){
   k=fgetc(gprs);
   if(k == arg[i])
      i++;
   if(i > 5){
      vet[y] = k;
      y++;
      if(y > 12){
         vet[y] = '\0';
        // fputs(retNum(vet, temp), serial);     
         podeEntrar = true;
         i = 0;
         y = 0;
      }
   }   
}

void main(){
   char vet[40];// = "\"85851611\",\"\",161,"; 
   char temp[20];
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_RDA);   
   while(true){
      /*vet[i] = fgetc(gprs); 
      if(vet[i] == '\r'){
         cont++;
         if (cont == 4){
            fputs(retNum(vet, temp), serial);         
            i=0;
            cont = 0;
            //break;
            sprintf(chr, "AT+CMGS=\"%s\"\r", temp);                  
            fputs("AT+CMGF=1\r", gprs);
            fputs(chr, gprs);
            sprintf(chr, "Lt:   08 01.8650S\r\nLg:034 56.3050W%c", 0x1a);
            fputs(chr, gprs);
            delay_ms(2000);            
         }
      } else i++;*/

      /*
      \r\n
      RING\r\n
      \r\n
      +CLIP: "85851611",161,"",,"",0\r\n
      ATH\r\n
      OK\r\n
      */
      
      //k = fgetc(gprs);
      //fputc(k, serial);
      output_high(pin_B0);
      delay_ms(300);
      output_low(pin_B0);
      delay_ms(300);      
      
      if(podeEntrar){
         podeEntrar = false;
        
         fputs(retNum(vet, temp), serial);
         delay_ms(1000);
         
         /*sprintf(chr, "AT+CMGS=\"%s\"\r", temp);                  
         fputs("AT+CMGF=1\r", gprs);
         fputs(chr, gprs);
         sprintf(chr, "Lt:   08 01.8650S\r\nLg:034 56.3050W%c", 0x1a);
         fputs(chr, gprs);
         delay_ms(2000);  */          
         /*for(limpar = 0; limpar < 50;limpar++)
            vet[limpar] = '\0';*/
      }
      
      
     /* vet[i] = fgetc(gprs); 
      if(i == 43){
            fputs(retNum(vet, temp), serial);         
            i = 0;
            //break;
            sprintf(chr, "AT+CMGS=\"%s\"\r", temp);                  
            fputs("AT+CMGF=1\r", gprs);
            fputs(chr, gprs);
            sprintf(chr, "Lt:   08 00.8226S\r\nLg:034 54.5643W%c", 0x1a);
            fputs(chr, gprs);
            delay_ms(5000);            
      } else i++; */

     /* vet[i] = fgetc(gprs); 
      if(vet[i] == '\r'){
         cont++;
         if (cont == 4){
            fputs(retNum(vet, temp), serial);         
            i=0;
            cont = 0;
            //break;
            sprintf(chr, "AT+CMGS=\"%s\"\r", temp);                  
            fputs("AT+CMGF=1\r", gprs);
            fputs(chr, gprs);
            sprintf(chr, "Lt:   08 00.8226S\r\nLg:034 54.5643W%c", 0x1a);
            fputs(chr, gprs);
            delay_ms(5000);            
         }
      } else i++;  */  
      //fputs("Mensagem SERIAL\r\n", serial);      
   }
   //sprintf(chr, "AT+CMGS=\"%s\"\r", retNum(vet, temp));   
}



