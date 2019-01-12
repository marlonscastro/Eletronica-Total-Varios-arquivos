#include <18F4550.h>
#use delay(clock=48000000)
//#use rs232(baud=19200, parity=N, xmit=PIN_D6, rcv=PIN_D7, stream = canal1)
#use rs232(baud=4800, parity=N, xmit=PIN_D6, rcv=PIN_D7, stream = gps)   // Modulo GPS
#use rs232(baud=19200, parity=N, xmit=PIN_D2, rcv=PIN_D3, stream = gprs)  // GPRS
#use rs232(baud=19200, parity=N, xmit=PIN_D4, rcv=PIN_D5, stream = serial)   // Ecoar na Serial
#fuses HSPLL, PLL4, CPUDIV1, PUT, NOWDT, NOBROWNOUT, NOLVP
#include <string.h>
#include "DriverPE12864LRF.c"

#define     CMD_SET_TEXT_MODE      "AT+CMGF=1"
#define     CMD_CHECK_OK           "AT"

int1 checkStatus(char* str1, char* cmpstr){
   int i=0 , j=0, cont=0, tam1, tam2;
   int1 ok = 0;
   tam1 = strlen(str1);
   tam2 = strlen(cmpstr);
   while(j<tam1){
      if(str1[j] == cmpstr[i]){
         cont++;
         i++;
      }
      if(cont == tam2){
         ok = 1;
         break;
      }
      j++;
   }
   RETURN ok;
}
int1 sendCMD(char* cmd, char* cmpstr){
   char chr[10];
   int i = 0;
   fprintf(gprs, "%s\r\n", cmd);
   fprintf(serial, "%s\r\n", cmd);
   PE12864_Gotoxy(0,0);
   printf(PE12864_Printchar, "%s", cmd);   
   PE12864_Gotoxy(0,1);
   while (true){         
       chr[i] = fgetc(gprs);
       fputc(chr[i], serial);
       PE12864_Printchar(chr[i]);          
       if(chr[i] == '\n')
         break;
       i++;
   }
   RETURN checkStatus(chr, cmpstr);
}

int1 sendSMS(char* NUM, char* MSG){
   char cmd[] = "AT+CMGF=1";
   char chr[22];
   char cmpstr[] = "OK";
   int i = 0, cont = 0;
   
   if (sendCMD(cmd, cmpstr)) {
      fprintf(gprs, "AT+CMGS=\"%s\"\r\n", NUM);
      fprintf(serial, "AT+CMGS=\"%s\"\r\n", NUM);      
      
      fgetc(gprs);
      fputc(serial);
//      fputc(0x3e, gprs);
      if(fgetc(gprs) == 0x20){
         //fputc(0x20, gprs);
         fputc(0x20, serial);         
         fprintf(gprs, "%s%c", MSG, 0x1a);
         fprintf(serial, "%s%c", MSG, 0x1a);         
         while(true){
            chr[i] = fgetc(gprs);
            fputc(chr[i], serial);            
            if(chr[i] == '\r')
               cont++;
            if (cont == 4)
               break;
            i++;
         }
         return checkStatus(chr, cmpstr);
      }
      else return 0;
   }
   else return 0;
   
   /*if (sendCMD(cmd, cmpstr)) {   
      //strcpy(cmpstr, ">");
      sprintf(cmpstr, "%c", 0x3e);   //  '>'
      //strcpy(cmd, "AT+CMGS=\"8185851611\"\r\n");
      sprintf(cmd, "AT+CMGS=\"%s\"\r\n", NUM);
      if (sendCMD(cmd, cmpstr)){
         strcpy(cmpstr, "+CMGS:40");         
         //strcpy(cmd, "Mensagem SMS");  
         sprintf(cmd, "%s%c", MSG, 0x1a);
         if (sendCMD(cmd, cmpstr)){
            printf(PE12864_Printchar, "SMS Enviado com Sucesso!");
         }
      }
   }
   RETURN checkStatus(chr, cmpstr);  */ 
}
int1 iniGPRS(){
   //char cmd[] = "AT+CFUN=1";
   //char cmpstr[] = "OK";
   char cmd[] = "AT";
   char cmpstr[] = "OK";
   delay_ms(2000);
   if (sendCMD(cmd, cmpstr))
      return 1;
   else
      return 0;
}
void waitCMD(){
   int i = 0, j = 0, cont = 0, ok = 0;
   char chr[30];
   char NUMERO[12];
   char CallVal[] = "RING";
   char cmd[] = "ATH";
   char strcomp[] = "OK";
   char MENSAGEM[] = "TESTE de SMS SIM300D!!!";
   /*
   \r\nRING\r\n
   +CLIP: "85851611",161,"",,"",0\r\n      
   */
   while(true){
     i=j=cont=ok=0;
     delay_ms(2000);
     PE12864_Gotoxy(0,1);
     printf(PE12864_Printchar, "INICIO                        ");   
      /*chr[i] = fgetc(canal1);
      if(chr[i] == )
         i++;
   }
   if(ok){*/
      while(true){
         chr[i] = fgetc(gprs);
         fputc(chr[i], serial);      
         if(chr[i] == '\n')
            cont++;
         if (cont == 4){
            cont = 0;
            break;
         }
         i++;
      }
      if (sendCMD(cmd, strcomp)){  // Desconecta a ligação com 'ATH'
         for(i=0; i<strlen(chr); i++){
            if((cont == 1) && (chr[i] != '\"')){
               NUMERO[j] = chr[i];
            j++;
            }
            if(chr[i] == '\"')
               cont++;
            if(cont == 2){
               NUMERO[j] = '\0';
               break;
            }
            }
         /* PE12864_Gotoxy(0,0);   
            printf(PE12864_Printchar, "%u", j);
            PE12864_Gotoxy(0,1);   
            printf(PE12864_Printchar, "%s", NUMERO);
            PE12864_Gotoxy(0,2);   
            printf(PE12864_Printchar, "%s", MENSAGEM);*/ 
   
         if (j>0){  // Se o Numero não é CONFIDENCIAL, envia a Mensagem
            if (sendSMS(NUMERO, MENSAGEM)){
               PE12864_Gotoxy(0,1);
               printf(PE12864_Printchar, "Mensagem Enviada");
            }
            else{
               PE12864_Gotoxy(0,1);
               printf(PE12864_Printchar, "Erro");
            }   
         } 
         else{
            PE12864_Gotoxy(0,1);
            printf(PE12864_Printchar, "DESCONHECIDO");
         }
         
      }
   }
}
void main(void){
   int i, cont=0, j = 0; 
   char k = 'M';
   PE12864_InitLcd();
   /*if (iniGPRS()){
      delay_ms(8000);
      waitCMD();
   }*/
   /*if(iniGPRS())
      printf(PE12864_Printchar, "Inicializado");
   else
      printf(PE12864_Printchar, "Erro na Inicializacao!");*/
      PE12864_Gotoxy(0,0);
      printf(PE12864_Printchar, "Inicializado");
      while(true){
         k = fgetc(gprs);
         fputc(k, serial);         
         PE12864_Printchar(k);   
      }
      printf(PE12864_Printchar, "                       ");
      PE12864_Gotoxy(0,0);
      printf(PE12864_Printchar, "Fim");      
   
   // iniGPRS();
   /*char NUM[] = "85851611";
   char MSG[] = "TESTE de SMS !!!";
   char str[] = "\r\nRING\r\n+CLIP: \"85851611\",161,\"\",,\"\",0\r\n";
   char strmod[10];
   for(i=0; i<strlen(str); i++){
       if ((str[i] != '\"') && (cont == 1)){
         strmod[j] = str[i];
         j++;
       }
       if (str[i] == '\"')
          cont++;
       if(cont == 2)
          break;          
   }
   printf(PE12864_Printchar, "%s", strmod);  */ 
   /*if (sendSMS(NUM, MSG)){
      PE12864_Gotoxy(0,1);
      printf(PE12864_Printchar, "Mensagem Enviada");
   }
   else{
      PE12864_Gotoxy(0,1);
      printf(PE12864_Printchar, "Erro");
   }*/
   
   /*while(TRUE){
      fprintf(canal1, "AT+CMGF=1\r\n");
      fprintf(canal1, "AT+CMGS=\"8185851611\"\r\n");
      fprintf(canal1, "Ola Mundo, aqui eh o SIM300S da SIMCom!%c\r\n", 0x1a);      
      delay_ms(1000);
   }*/
}

