/************************************************************************
**
**  Driver para S65 (L2F50126) 176x132 - 16bit 565 color RGB
**  Marlon - marlonsolucoes@hotmail.com 
**  CCS Compiler 4.114 - Abril de 2014
**  Baseado no driver de Christian Kranz
**
*************************************************************************/
// Interessante usar a interface SPI atravez de setup_spi();

#include <string.h>
#include <lcd.h>

int16 backcolor=0xFFFF;    // cor do fundo
int16 textcolor=0x0000;    // cor do texto

void port_init(){
  output_low(LCD_RESET); 
  output_high(LCD_DATA); 
  output_low(LCD_CS);   
  output_low(LCD_SCK);   
  output_high(LCD_RS);   
}

void lcd_write(char dados){
  spi_write(dados);
}

void lcd_wrcmd(int output_data){ 
  output_low(LCD_RS);
  lcd_write(output_data);
  lcd_write(0x00);
  output_high(LCD_RS);  
}

void lcd_wrdata(int output_data){
  lcd_write(output_data);
  lcd_write(0x00);  
}

void lcd_wrcmd16(int16 dat){
  lcd_wrcmd((dat>>8));
  lcd_wrcmd(dat);
}

void lcd_wrdat16(int16 dat){
  lcd_write(dat>>8);
  lcd_write(dat);
}

void fill_screen(int16 color){
  int16 i;
  output_low(LCD_CS);  // Seleciona o Display
  
  lcd_wrcmd(SD_CSET);
  lcd_wrdata(0x08);  // o inicio � 8 e n�o 0
  lcd_wrdata(0x01);
  lcd_wrdata(0x8B);  // o final � 00x8B = 0x83+8
  lcd_wrdata(0x01);

  lcd_wrcmd(SD_PSET);
  lcd_wrdata(0x00);
  lcd_wrdata(0xAF);
  
  lcd_wrcmd(RAMWR);  // Escrever na RAM do display 

  for (i=0; i<DISP_W*DISP_H; i++)
    lcd_wrdat16(color);     //   Plotagem do pixel com a cor especificada

  output_high(LCD_CS);  
}


void drawBox(int x, int y, long width, long height, int16 Color, int orientacao){
  long i;
  output_low(LCD_CS); 
   
  if (orientacao == PAISAGEM){   
     lcd_wrcmd(SD_CSET);
     lcd_wrdata(0x08+132-y-height);        // O Inicio � 8 e n�o 0 
     lcd_wrdata(0x01);          
     lcd_wrdata(0x08+132-y-1);  // o final � 00x8B = 0x83+8
     lcd_wrdata(0x01);
     
     lcd_wrcmd(SD_PSET);
     lcd_wrdata(x);
     lcd_wrdata(x+width-1);
  }
  else if (orientacao == RETRATO){
     lcd_wrcmd(SD_CSET);
     lcd_wrdata(0x08+x);        // O Inicio � 8 e n�o 0 
     lcd_wrdata(0x01);          
     lcd_wrdata(0x08+x+width-1);  // o final � 00x8B = 0x83+8
     lcd_wrdata(0x01);
     
     lcd_wrcmd(SD_PSET);
     lcd_wrdata(y);
     lcd_wrdata(y+height-1);
  }
  lcd_wrcmd(RAMWR);   // Inicia a grava��o de dados na RAM do display
  for (i=0;i<(width*height);i++){
   lcd_wrdat16(Color);  // com a cor especificada 
  }
  output_high(LCD_CS); 
}

void Putpixel(int x, int y, int16 Color, int orientacao){
  output_low(LCD_CS); 
  
  if (orientacao == PAISAGEM){   
     lcd_wrcmd(SD_CSET);
     lcd_wrdata(0x08+132-y);  // O Inicio � 8 e n�o 0 
     lcd_wrdata(0x01);
     lcd_wrdata(0x08+132-y);  // o final � 00x8B = 0x83+8
     lcd_wrdata(0x01);
     
     lcd_wrcmd(SD_PSET);
     lcd_wrdata(x);
     lcd_wrdata(x);
  }
  else if (orientacao == RETRATO){  
     lcd_wrcmd(SD_CSET);
     lcd_wrdata(0x08+x);  // O Inicio � 8 e n�o 0 
     lcd_wrdata(0x01);
     lcd_wrdata(0x08+x);  // o final � 00x8B = 0x83+8
     lcd_wrdata(0x01);
     
     lcd_wrcmd(SD_PSET);
     lcd_wrdata(y);
     lcd_wrdata(y);  
  }
  lcd_wrcmd(RAMWR);    // Inicia a grava��o de dados na RAM do display
  lcd_wrdat16(Color);  // com a cor especificada 

  output_high(LCD_CS); 
}

void char8x12(int x, int y, char c, int16 BColor, int16 FColor){
  int h,ch,p,mask;
  output_low(LCD_CS);

  lcd_wrcmd(SD_CSET);
  lcd_wrdata(0x08+x);    // start is 8, not 0
  lcd_wrdata(0x01);
  lcd_wrdata(0x08+x+7);  // end is 00x8B = 0x83+8
  lcd_wrdata(0x01);
  
  lcd_wrcmd(SD_PSET);
  lcd_wrdata(y);
  lcd_wrdata(y+12);  

  lcd_wrcmd(RAMWR);
  
  for (h=0; h<12; h++){        
     ch=font8x12[c-32][h];
     mask=0x80;
     for (p=0; p<8; p++){  // write the pixels
        if (ch&mask)
           lcd_wrdat16(FColor);                
        else
           lcd_wrdat16(BColor);
        mask=mask/2;
     } 
  }
  output_high(LCD_CS);  
}

void char8x12_90(int x, int y, char c, int16 BColor, int16 FColor){
  int h,ch,p,mask,pos, i, j, inc = 0, k, a=0, b=0;
  char new_char[16] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };  
  output_low(LCD_CS);
  Byte bitTest = 0x80, bitset = 0x01;

  lcd_wrcmd(SD_CSET);
  lcd_wrdata(0x08+132-y-12);    // start is 8, not 0
  lcd_wrdata(0x01);
  lcd_wrdata(0x08+132-y-1);  // end is 00x8B = 0x83+8
  lcd_wrdata(0x01);
  
  lcd_wrcmd(SD_PSET);
  lcd_wrdata(x);
  lcd_wrdata(x+9);  
  
 /* 
  lcd_wrcmd(SD_CSET);
  lcd_wrdata(0x08+132-y-8);    // start is 8, not 0
  lcd_wrdata(0x01);
  lcd_wrdata(0x08+132-y-1);  // end is 00x8B = 0x83+8
  lcd_wrdata(0x01);
  
  lcd_wrcmd(SD_PSET);
  lcd_wrdata(x);
  lcd_wrdata(x+6);  */  

  // ----------------------- TESTE fun��o inverte bits -------------
   if ((c<0x20) || (c>0x7F)) return;
   pos = c-0x20;
   for(i=0;i<12;i++){
      for(j=0;j<8;j++){      
        if((font8x12[pos][i]&bitTest) != 0)
            new_char[j+inc] |= bitset;
        bitTest>>=1;
      }
      bitTest = 0x80;
      bitset<<=1;
      if(i==7){
         bitset = 0x10; // Bug Consertei << 4 bits
         inc=8;
      }
   }
  // ---------------------------------------------------------------
  lcd_wrcmd(RAMWR);
 // new_char[8] = 0x1f;
  for (h=0; h<16; h++){
     if((h%2)!=0){  
        ch=new_char[a];
        k=8;
        a++;
     }
     else{
        ch=new_char[b+8];     
        k=4;
        b++;
     }
     //ch=0xc0;
     mask=0x80;
     for (p=0; p<k; p++){  // write the pixels
        if (ch&mask)
           lcd_wrdat16(FColor);                
        else
           lcd_wrdat16(BColor);
        mask=mask/2;
     } 
  }
  output_high(LCD_CS);  
}

void char5x8(int x, int y, char c, int16 BColor, int16 FColor){
  int h,ch,p,mask,pos, i, j;
  char new_char[8] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };  
  Byte bitTest = 0x01, bitset = 0x80;  
  output_low(LCD_CS);

  lcd_wrcmd(SD_CSET);
  lcd_wrdata(0x08+x);    // start is 8, not 0
  lcd_wrdata(0x01);
  lcd_wrdata(0x08+x+6-1);  // end is 00x8B = 0x83+8
  lcd_wrdata(0x01);
  
  lcd_wrcmd(SD_PSET);
  lcd_wrdata(y);
  lcd_wrdata(y+8);  

  lcd_wrcmd(RAMWR);
  // ----------------------- TESTE fun��o inverte bits -------------
   if ((c<0x20) || (c>0x7F)) return;
   pos = c-0x20;
   for(i=0;i<5;i++){
      for(j=0;j<8;j++){      
        if((font5x8[pos][i]&bitTest) != 0)
          new_char[j] |= bitset;
        bitTest<<=1;
      }
      bitTest = 0x01;
      bitset>>=1;
      if(i==4)
         bitset = 0x80;         
    
   }
  // ---------------------------------------------------------------
  for (h=0; h<8; h++){        
     ch=new_char[h];
     mask=0x80;
     for (p=0; p<6; p++){  // write the pixels
        if (ch&mask)
           lcd_wrdat16(FColor);                
        else
           lcd_wrdat16(BColor);
        mask=mask/2;
     } 
  }
  output_high(LCD_CS);  
}

void char5x8_90(int x, int y, char c, int16 BColor, int16 FColor){
  int h,ch,p,mask;
  output_low(LCD_CS);

  lcd_wrcmd(SD_CSET);
  lcd_wrdata(0x08+132-y-8);    // start is 8, not 0
  lcd_wrdata(0x01);
  lcd_wrdata(0x08+132-y-1);  // end is 00x8B = 0x83+8
  lcd_wrdata(0x01);
  
  lcd_wrcmd(SD_PSET);
  lcd_wrdata(x);
  lcd_wrdata(x+6);  

  lcd_wrcmd(RAMWR);

  for (h=0; h<6; h++){
     if (h<5)
       ch=font5x8[c-32][h];
     else
       ch=0x00;
     mask=0x80;
     for (p=0; p<8; p++){  // write the pixels
        if (ch&mask)
           lcd_wrdat16(FColor);                
        else
           lcd_wrdat16(BColor);
        mask=mask/2;
     } 
  }
  output_high(LCD_CS);  
}

void char8x8_90(int x, int y, char c, int16 BColor, int16 FColor){
  int h,ch,p,mask;
  output_low(LCD_CS);

  lcd_wrcmd(SD_CSET);
  lcd_wrdata(0x08+132-y-8);    // start is 8, not 0
  lcd_wrdata(0x01);
  lcd_wrdata(0x08+132-y-1);  // end is 00x8B = 0x83+8
  lcd_wrdata(0x01);
  
  lcd_wrcmd(SD_PSET);
  lcd_wrdata(x);
  lcd_wrdata(x+8);  

  lcd_wrcmd(RAMWR);
  
  for (h=0; h<8; h++){        
     ch=invByte(font8x8[c-32][7-h]);
     mask=0x80;
     for (p=0; p<8; p++){  // write the pixels
        if (ch&mask)
           lcd_wrdat16(FColor);                
        else
           lcd_wrdat16(BColor);
        mask=mask/2;
     } 
  }
  output_high(LCD_CS);  
}

char invByte(char bt){    // Essa fun��o � necess�ria para inverter os bits da maneira correta ex: 1100 0000 = 0000 0011
   char btInvert = 0x00;
   Byte bitTest = 0x80, bitset = 0x01;
   int i;
   for(i=0;i<8;i++){
      if((bt&bitTest) != 0)
         btInvert |= bitset; 
      bitTest>>=1;
      bitset<<=1;
   }
   return btInvert;   
}

void putstr(int x, int y, char* text, int16 BC, int16 FC, int fonte, int orientacao){
   int i = 0;

   if (fonte == FONT58){
      if (orientacao == RETRATO)
         while (text[i]!=0){   
            //for(i=0;i<strlen(text);i++)
               char5x8(x+(i*6),y,text[i],BC, FC);            
               i++;               
         }            
      else if (orientacao == PAISAGEM)
         while (text[i]!=0){  
            char5x8_90(x+(i*6),y,text[i],BC, FC);
            i++;
         }
   }
   if (fonte == FONT812){
      if (orientacao == RETRATO)
         while (text[i]!=0){  
            char8x12(x+(i*8),y,text[i],BC, FC);
            i++;
         }
      else if (orientacao == PAISAGEM)
         while (text[i]!=0){  
            char8x12_90(x+(i*8),y,text[i],BC, FC);
            i++;
         }
   }  
   if (fonte == FONT88){
      if (orientacao == RETRATO)
         while (text[i]!=0){  
            //char8x8(x+(i*8),y,text[i],BC, FC);
               char5x8(x+(i*6),y,text[i],BC, FC);            
            i++;
         }
      else if (orientacao == PAISAGEM)
         while (text[i]!=0){  
            char8x8_90(x+(i*8),y,text[i],BC, FC);
            i++;
         }
   }   
}

void lcd_init(void){
  int i;
  BYTE const disctl[9] = {0x4C, 0x01, 0x53, 0x00, 0x02, 0xB4, 0xB0, 0x02, 0x00};
  BYTE const gcp64_0[29] =
                      {0x11,0x27,0x3C,0x4C,0x5D,0x6C,0x78,0x84,0x90,0x99,0xA2,0xAA,0xB2,0xBA,
                       0xC0,0xC7,0xCC,0xD2,0xD7,0xDC,0xE0,0xE4,0xE8,0xED,0xF0,0xF4,0xF7,0xFB,
                       0xFE};
  BYTE const gcp64_1[34] =
                     {0x01,0x03,0x06,0x09,0x0B,0x0E,0x10,0x13,0x15,0x17,0x19,0x1C,0x1E,0x20,
                      0x22,0x24,0x26,0x28,0x2A,0x2C,0x2D,0x2F,0x31,0x33,0x35,0x37,0x39,0x3B,
                      0x3D,0x3F,0x42,0x44,0x47,0x5E};
  BYTE const gcp16[15] =
                      {0x13,0x23,0x2D,0x33,0x38,0x3C,0x40,0x43,0x46,0x48,0x4A,0x4C,0x4E,0x50,0x64};

  port_init();
  // generate clean display reset
  output_low(LCD_RESET);   // CS is high during reset release 
  output_high(LCD_CS);  
  output_high(LCD_RS);  // RS is set to high
  delay_ms(10);

  output_high(LCD_RESET);  // release reset
  delay_ms(35);

  output_low(LCD_CS);  // select display
  
  lcd_wrcmd(_DATCTL);
  lcd_wrdata(0x2A);  // 0x2A=565 mode, 0x0A=666mode, 0x3A=444mode
      
  output_high(LCD_CS);
  //delay_us(1);  // Pulso no pino CS
  output_low(LCD_CS);
  
  lcd_wrcmd(_DISCTL);
  for (i=0; i<9; i++){
    lcd_wrdata(disctl[i]);
  }
  
  lcd_wrcmd(_GCP64);
  for (i=0; i<29; i++){
    lcd_wrdata(gcp64_0[i]);
    lcd_wrdata(0x00);
  }
  for (i=0; i<34; i++){
    lcd_wrdata(gcp64_1[i]);
    lcd_wrdata(0x01);
  }

  lcd_wrcmd(_GCP16);
  for (i=0; i<15; i++){
    lcd_wrdata(gcp16[i]);
  }

  lcd_wrcmd(GSSET);
  lcd_wrdata(0x00);

  lcd_wrcmd(OSSEL);
  lcd_wrdata(0x00);

  lcd_wrcmd(SLPOUT);
  
  //delay_ms(7);

  lcd_wrcmd(SD_CSET);
  lcd_wrdata(0x08);
  lcd_wrdata(0x01);
  lcd_wrdata(0x8B);
  lcd_wrdata(0x01);

  lcd_wrcmd(SD_PSET);
  lcd_wrdata(0x00);
  lcd_wrdata(0x8F);

  lcd_wrcmd(ASCSET);
  lcd_wrdata(0x00);
  lcd_wrdata(0xAF);
  lcd_wrdata(0xAF);
  lcd_wrdata(0x03);
  
  lcd_wrcmd(SCSTART);
  lcd_wrdata(0x00);

  output_low(LCD_RS);    
  lcd_wrdata(DISON);
  
  output_high(LCD_CS);    // deselect display
}

