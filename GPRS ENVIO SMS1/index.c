/*
   O Codigo abaixo, recebe uma liga��o qualquer, desconecta-a e envia uma mensagem pro 85851611 Somente
   N�o envia para o numero que ligou.
*/

#include <16F628A.h>
#use delay(clock=4000000)
#FUSES NOWDT, NOBROWNOUT, PUT, XT   

#use rs232(baud=9600, parity=N, xmit=PIN_B2, rcv=PIN_B1, STREAM=gprs)     // GPRS
//#use rs232(baud=9600, parity=N, xmit=PIN_A0, rcv=PIN_A1, STREAM=serial)   // Ecoar na Serial
#use rs232(baud=4800, parity=N, xmit=PIN_A0, rcv=PIN_A1, STREAM=serial)   // GPS


#include <string.h>
   
   int i = 0, y = 0;
   char k;
   char arg[6] = {'+', 'C', 'L', 'I', 'P', ':'};
   boolean podeEntrar = false;   
   char vet[];// = "\"85851611\",\"\",161,"; 
   
char *retNum(char *str, char *strret){  //   "85851611","",161,
   int a = 0, b = 0, cont = 0;
   while(a < 19){
      if(cont == 1){
         strret[b] = str[a];
         b++;
      }
      if (str[a] == '\"' ){
         cont++;
         if(cont == 2){
            fputs("ATH\r", gprs);            
            strret[b-1] = '\0';
            break;
         }
      }
      a++;
   }
return(strret);      
}

char *splitstr(char *str, char* strret, int num, char chr){
   int i = 0, j = 0, cont = 0, index = 0;
   while(i < strlen(str)){
      if (index == num){
         cont++;
         break;
      }
      else 
         if(str[i] == chr)
           index++;
      i++;
   }
   while(i < strlen(str)){
      if((str[i] != chr) && (cont == 1)){
         strret[j] = str[i];
         j++;
      }
      if((str[i] == chr) || (i == strlen(str)-1))
         cont++;
      if(cont == 2){
         strret[j] = '\0';
         break;
      }
      i++;
   }
   return strret;
}


#INT_RDA
void serial_isr(){
   // IMEI:  358948-01-042182-2
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
            break;
         }
      } 
}

void main(){
   char temp[20];
  // char chr[25];
   //char vet[] = "\r\nRING\r\n+CLIP: \"85851611\",161,\"\",,\"\",0\r\n";
// ----- Var GPS -------
   char temp2[20];
   char gps[70];
   char arggps[6] = {'$', 'G', 'P', 'R', 'M', 'C'};
   int a = 0,b = 0;
   char chrgps;

// --------------------

   enable_interrupts(GLOBAL);
   enable_interrupts(INT_RDA);   
   while(true){
      /*output_high(pin_B0);
      delay_ms(300);
      output_low(pin_B0);
      delay_ms(300);*/
      
      if(podeEntrar){
         podeEntrar = false;
         fputs(retNum(*vet, temp), serial);
         fputs(temp, serial);         
         //fputs("ATH\r", gprs);    
         
         /*sprintf(chr, "AT+CMGS=\"85851611\"\r");                  
         fputs("AT+CMGF=1\r", gprs);
         fputs(chr, gprs);
         sprintf(chr, "Lt:   08 01.8650S\r\nLg:034 56.3050W%c", 0x1a);
         fputs(chr, gprs);*/
         
         fprintf(gprs, "AT+CMGF=1\r");
         fprintf(gprs, "AT+CMGS=\"85851611\"\r");
         
        
         fprintf(gprs, "Hora: %s\r\n", splitstr(gps, temp2, 1, ','));
         fprintf(gprs, "Data: %s\r\n", splitstr(gps, temp2, 9, ','));            
         fprintf(gprs, "Lt:  %s", splitstr(gps, temp2, 3, ','));            
         fprintf(gprs, "%s\r\n", splitstr(gps, temp2, 4, ','));            
         fprintf(gprs, "Lg: %s", splitstr(gps, temp2, 5, ','));            
         fprintf(gprs, "%s\r\n", splitstr(gps, temp2, 6, ','));
         fprintf(gprs, "VEL(Mph): %s \r\nBy Marlon", splitstr(gps, temp2, 7, ','));            
         fprintf(gprs, "%c", 0x1a);         
      }
      // -------------- Recep��o GPS --------------------------
      chrgps=fgetc(serial);
      if(chrgps == arggps[i])
         b++;
      if(b > 5){
         gps[a] = chrgps;
         a++;
         if(a > 69){
            a = 0;
            b = 0;
         }
      }      
      // -------------------------------------------------------
   }
}
/* 
1 = 24
2 = 16
3 = 17
4 = 20
$GPRMC,213820.79,A,0800.8226,S,03454.5543,W,000.0,000.8,050410,022.6,W,A*25 

$GPRMC,
213820.79,        Fix taken at 213820 UTC
A,                Status A=active or V=Void.
0800.8226,        Latitude 08 deg 00.8226'
S,                S
03454.5543,       Longitude 034 deg 54.5543'
W,                W
000.0,            Speed over the ground in knots (Milhas N�uticas, 1852 Metros ou 1,852 Km)
000.8,            Track angle in degrees True
050410,           Date -  5 rd of April 2010
022.6,            Magnetic Variation
W,                W
A*25              The checksum data, always begins with *

Da forma que o google Maps traduz:   08 00.8226S 034 54.5643W

*/
