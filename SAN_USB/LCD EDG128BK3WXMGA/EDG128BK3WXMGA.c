// Driver teste para o LCD 128x64 (PowerTip PE12864LRF-004-H/*
const BYTE TEXT[51][5] ={0x00, 0x00, 0x00, 0x00, 0x00, // SPACE  01
                         0x00, 0x00, 0x5F, 0x00, 0x00, // !
                         0x00, 0x03, 0x00, 0x03, 0x00, // "
                         0x14, 0x3E, 0x14, 0x3E, 0x14, // #
                         0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
                         0x43, 0x33, 0x08, 0x66, 0x61, // %
                         0x36, 0x49, 0x55, 0x22, 0x50, // &
                         0x00, 0x05, 0x03, 0x00, 0x00, // '
                         0x00, 0x1C, 0x22, 0x41, 0x00, // (
                         0x00, 0x41, 0x22, 0x1C, 0x00, // )
                         0x14, 0x08, 0x3E, 0x08, 0x14, // *
                         0x08, 0x08, 0x3E, 0x08, 0x08, // +
                         0x00, 0x50, 0x30, 0x00, 0x00, // ,
                         0x08, 0x08, 0x08, 0x08, 0x00, // -
                         0x00, 0x60, 0x60, 0x00, 0x00, // .
                         0x20, 0x10, 0x08, 0x04, 0x00, // /
                         0x3E, 0x51, 0x49, 0x3e, 0x00, // 0      17
                         0x04, 0x02, 0x7F, 0x00, 0x00, // 1
                         0x00, 0x61, 0x51, 0x49, 0x46, // 2
                         0x00, 0x41, 0x49, 0x49, 0x36, // 3      20
                         0x18, 0x14, 0x12, 0x7F, 0x00, // 4
                         0x00, 0x27, 0x45, 0x45, 0x39, // 5
                         0x3E, 0x49, 0x49, 0x32, 0x00, // 6      23
                         0x00, 0x01, 0x71, 0x09, 0x07, // 7
                         0x36, 0x49, 0x49, 0x36, 0x00, // 8
                         0x26, 0x49, 0x49, 0x3e, 0x00, // 9      26
                         0x00, 0x36, 0x36, 0x00, 0x00, // :
                         0x00, 0x56, 0x36, 0x00, 0x00, // ;
                         0x08, 0x14, 0x22, 0x41, 0x00, // <
                         0x14, 0x14, 0x14, 0x14, 0x00, // =
                         0x00, 0x41, 0x22, 0x14, 0x08, // >
                         0x02, 0x01, 0x51, 0x09, 0x06, // ?
                         0x3E, 0x41, 0x59, 0x55, 0x5E, // @
                         0x7E, 0x09, 0x09, 0x7e, 0x00, // A      34
                         0x7F, 0x49, 0x49, 0x36, 0x00, // B
                         0x3E, 0x41, 0x41, 0x22, 0x00, // C
                         0x7F, 0x41, 0x41, 0x3e, 0x00, // D      37
                         0x7F, 0x49, 0x49, 0x41, 0x00, // E
                         0x7F, 0x09, 0x09, 0x01, 0x00, // F
                         0x3E, 0x41, 0x49, 0x3a, 0x00, // G      40
                         0x7F, 0x08, 0x08, 0x7f, 0x00, // H
                         0x00, 0x41, 0x7F, 0x41, 0x00, // I
                         0x30, 0x40, 0x40, 0x3f, 0x00, // J      43
                         0x7F, 0x08, 0x14, 0x63, 0x00, // K
                         0x7F, 0x40, 0x40, 0x00, 0x00, // L
                         0x7F, 0x02, 0x0C, 0x02, 0x7F, // M      46
                         0x7F, 0x02, 0x04, 0x08, 0x7F, // N
                         0x3E, 0x41, 0x41, 0x3e, 0x00, // O
                         0x7F, 0x09, 0x09, 0x06, 0x00, // P      49
                         0x1E, 0x21, 0x21, 0x5e, 0x00, // Q
                         0x7F, 0x09, 0x09, 0x76, 0x00};// R      51

const BYTE TEXT2[44][5]={0x26, 0x49, 0x49, 0x32, 0x00, // S
                         0x00, 0x01, 0x7F, 0x01, 0x00, // T
                         0x3F, 0x40, 0x40, 0x3f, 0x00, // U
                         0x1F, 0x20, 0x40, 0x20, 0x1F, // V
                         0x7F, 0x20, 0x10, 0x20, 0x7F, // W
                         0x41, 0x22, 0x1C, 0x22, 0x41, // X
                         0x07, 0x08, 0x70, 0x08, 0x07, // Y
                         0x61, 0x51, 0x49, 0x47, 0x00, // Z
                         0x00, 0x7F, 0x41, 0x00, 0x00, // [
                         0x02, 0x04, 0x08, 0x10, 0x20, // \
                         0x00, 0x00, 0x41, 0x7F, 0x00, // ]
                         0x04, 0x02, 0x01, 0x02, 0x04, // ^
                         0x40, 0x40, 0x40, 0x40, 0x00, // _
                         0x00, 0x01, 0x02, 0x04, 0x00, // `
                         //0x20, 0x54, 0x54, 0x54, 0x78, // a
                         0x38, 0x44, 0x44, 0x7c, 0x00,  // a 
                         0x7F, 0x44, 0x44, 0x38, 0x00, // b
                         0x38, 0x44, 0x44, 0x44, 0x00, // c
                         0x38, 0x44, 0x44, 0x7f, 0x00, // d
                         0x38, 0x54, 0x54, 0x18, 0x00, // e
                         0x00, 0x04, 0x7E, 0x05, 0x00, // f
                         0x08, 0x54, 0x54, 0x3c, 0x00, // g
                         0x7F, 0x08, 0x04, 0x78, 0x00, // h
                         0x00, 0x00, 0x7a, 0x00, 0x00, // i
                         0x20, 0x00, 0x44, 0x3D, 0x00, // j
                         0x7e, 0x10, 0x28, 0x44, 0x00, // k
                         0x00, 0x41, 0x7F, 0x40, 0x00, // l
                         0x7C, 0x04, 0x78, 0x04, 0x78, // m
                         0x7C, 0x04, 0x04, 0x78, 0x00, // n
                         0x38, 0x44, 0x44, 0x38, 0x00, // o
                         0x7C, 0x14, 0x14, 0x08, 0x00, // p
                         0x08, 0x14, 0x14, 0x7c, 0x00, // q
                         0x00, 0x7C, 0x08, 0x04, 0x00, // r
                         0x08, 0x54, 0x54, 0x20, 0x00, // s
                         0x00, 0x04, 0x3F, 0x44, 0x00, // t
                         0x00, 0x3c, 0x40, 0x20, 0x7C, // u
                         0x1C, 0x20, 0x40, 0x20, 0x1C, // v
                         0x3C, 0x40, 0x30, 0x40, 0x3C, // w
                         0x44, 0x28, 0x10, 0x28, 0x44, // x
                         0x0C, 0x50, 0x50, 0x3c, 0x00, // y
                         0x00, 0x64, 0x54, 0x4C, 0x00, // z
                         0x00, 0x08, 0x36, 0x41, 0x41, // {
                         0x00, 0x00, 0x7F, 0x00, 0x00, // |
                         0x41, 0x41, 0x36, 0x08, 0x00, // }
                         0x02, 0x01, 0x02, 0x04, 0x02};// ~


#define PE12864_RES   pin_B4
#define PE12864_CS1   pin_B3
#define PE12864_A0    pin_B2
#define PE12864_CLK   pin_B1
#define PE12864_DATA  pin_B0

#define ON   1
#define OFF  0

int8 CurrentLine = 0;
int8 QuantChrLine = 0;
int8 OffsetX = 0;

void    PE12864_InitLcd(void);
void    PE12864_Write_command(char byte_command);
void    PE12864_Write_data(char byte_data);
void    PE12864_Gotoxy(int8 x, int y);
void    PE12864_Printchar(char cvar);
void    PE12864_PutPixel(int8 x,int8 y, int1 COLOR);
void    PE12864_SerialOut(char byteDC);
void    clear_screen(void);
void    newLine(void);
void    PE12864_circle(int x, int y, int radius, int1 fill, int1 COLOR);
void    PE12864_line(int x1, int y1, int x2, int y2, int1 COLOR);
//void    linexy(int8 x1,int8 y1,int8 x2,int8 y2, int1 COLOR);

void    PE12864_InitLcd(void){
   
   output_low(PE12864_CS1); // Chip Enabled
   output_low(PE12864_RES);
   delay_ms(5);
   output_high(PE12864_RES);   

   // LCD BIAS SET
   //- PAG 45 - 1010001-BIT    0: 1/9 ou 1: 1/7 ST7565S
   PE12864_Write_command(0xa2);
   //1010011-BIT  Display Fill  0: Normal  1: Reverse
   PE12864_Write_command(0xa6); // Normal
   // Commom Output mode Select
   //- PAG 46 -  1100-BIT      0: Normal Direction    1: Reverse Direction    (Ex: 11000*** - Normal Direction)
   PE12864_Write_command(0xc8);
   // LCD ADC Select 0:normal  1: Reverse
   PE12864_Write_command(0xa0);   
   // CMD Set Start Line 
   PE12864_Write_command(0x40);   
   
   PE12864_Write_command(0x28 | 0x4); 
   PE12864_Write_command(0x28 | 0x6);    
   PE12864_Write_command(0x28 | 0x7);    
   delay_us(5);   
   PE12864_Write_command(0x20 | 0x6);  // resistor Ratio
   clear_screen();
   PE12864_Write_command(0xaf); // Display ON
   PE12864_Write_command(0xa4); // all points Normal

   //Set Brightness  
   PE12864_Write_command(0x81); 
   PE12864_Write_command(0x1a);
}

void PE12864_SerialOut(char byteDC){
  //int i;
  output_low(PE12864_CS1);  
  /*for (i=8; i>0; i--) {
    output_low(PE12864_CLK);
    if ((byteDC&0x80)==0)
      output_low(PE12864_DATA);
    else
      output_high(PE12864_DATA);
    output_high(PE12864_CLK);
    byteDC<<=0x01;
  }*/
  spi_xfer(SPI_1, byteDC);  
  output_high(PE12864_CS1);
}
void    PE12864_Write_command(char byte_command){
  output_low(PE12864_A0);          // Write Command Enabled
  PE12864_SerialOut(byte_command);
}
void    PE12864_Write_data(char byte_data){
  output_high(PE12864_A0);         // Write data Enabled
  PE12864_SerialOut(byte_data);
  //Buffer[OffsetX][CurrentLine] = byte_data;  
  OffsetX++;
  PE12864_Gotoxy(OffsetX,CurrentLine);
}
void newLine(){
  if(CurrentLine < 7){  // New Line Command
      PE12864_Write_command((CurrentLine+1)|0xb0);  // Set Page Address to 0 (0 a 7)
      PE12864_Write_command(0x00);  // Set LSB for index Column
      PE12864_Write_command(0x10);  // Set MSB for index Column   
      CurrentLine+=1;
  }
  QuantChrLine = 1;
  OffsetX = 0;
}
void clear_screen(void) {
   int p, c;
   for(p = 0; p < 8; p++) {
      for(c = 0; c < 128; c++) {
         PE12864_Gotoxy(c,p);
         PE12864_Write_data(0x00);
         //Buffer[c][p] = 0x00;        
      }
   }
   PE12864_Gotoxy(0,0);   
}
void    PE12864_Gotoxy(int x, int y){
   int8 OffsetChr = 0;
   
   PE12864_Write_command(0xb0 | y);
   PE12864_Write_command((0x00 | x) & 0x0f);
   PE12864_Write_command(0x10|(x>>4));
   
   OffsetChr = (x+1)/6;
   if((x+1)%6)
      OffsetChr++;   
   CurrentLine = y;
   QuantChrLine = OffsetChr;
   OffsetX = x;
}
void    PE12864_Printchar(char cvar){
   int i;
   if (QuantChrLine > 21)  
       newLine(); 
   else
       QuantChrLine++;    
   if(cvar == 0x20)
      for(i=0;i<2;i++)
         PE12864_Write_data(0x00);
   else{
      for(i=0;i<5;i++){
         if (cvar < 0x53){
            if(TEXT[cvar-0x20][i])         
               PE12864_Write_data(TEXT[cvar-0x20][i]);      
         }
         else {
            if(TEXT2[cvar-0x53][i])               
               PE12864_Write_data(TEXT2[cvar-0x53][i]);               
         }
      }
   }
   PE12864_Write_data(0x00);
}


void PE12864_PutPixel(int x, int y, int1 COLOR){
   byte BytePlot, tempByte;
   if((x > 127)||(y > 63))
      return;
   BytePlot = 0;
   BytePlot |= 1;
   PE12864_Gotoxy(x,(y/8));
   BytePlot<<=(y%8);
   tempByte = BytePlot;   
   //BytePlot|=Buffer[x][y/8];      
   if(COLOR == OFF)
      BytePlot-=tempByte;
   PE12864_Write_data(BytePlot);
   
   /*   if(COLOR == ON)
      BytePlot|=Buffer[x][y/8];      
   else{
      tempByte = BytePlot;
      BytePlot|=Buffer[x][y/8];       
      BytePlot-=tempByte;
      //BytePlot = ((BytePlot | Buffer[x][y/8]) - BytePlot); 
   }*/
}

void PE12864_circle(int x, int y, int radius, int1 fill, int1 COLOR){
   signed int a, b, P;
   a = 0;
   b = radius;
   P = 1 - radius;
   do{
      if(fill){
         PE12864_line(x-a, y+b, x+a, y+b, color);
         PE12864_line(x-a, y-b, x+a, y-b, color);
         PE12864_line(x-b, y+a, x+b, y+a, color);
         PE12864_line(x-b, y-a, x+b, y-a, color);
      }
      else{
         PE12864_PutPixel(a+x, b+y, color);
         PE12864_PutPixel(b+x, a+y, color);
         PE12864_PutPixel(x-a, b+y, color);
         PE12864_PutPixel(x-b, a+y, color);
         PE12864_PutPixel(b+x, y-a, color);
         PE12864_PutPixel(a+x, y-b, color);
         PE12864_PutPixel(x-a, y-b, color);
         PE12864_PutPixel(x-b, y-a, color);
      }
      if(P < 0)
         P+= 3 + 2*a++;
      else
         P+= 5 + 2*(a++ - b--);
    } while(a <= b);
}

void PE12864_line(int x1, int y1, int x2, int y2, int1 COLOR){
   signed int  x, y, addx, addy, dx, dy;
   signed long P;
   int i;
   dx = abs((signed int)(x2 - x1));
   dy = abs((signed int)(y2 - y1));
   x = x1;
   y = y1;

   if(x1 > x2)
      addx = -1;
   else
      addx = 1;
   if(y1 > y2)
      addy = -1;
   else
      addy = 1;
   if(dx >= dy){
      P = 2*dy - dx;
      for(i=0; i<=dx; ++i){
         PE12864_PutPixel(x, y, COLOR);
         if(P < 0){
            P += 2*dy;
            x += addx;
         }
         else{
            P += 2*dy - 2*dx;
            x += addx;
            y += addy;
         }
      }
   }
   else{
      P = 2*dx - dy;
      for(i=0; i<=dy; ++i){
         PE12864_PutPixel(x, y, COLOR);

         if(P < 0){
            P += 2*dx;
            y += addy;
         }
         else{
            P += 2*dx - 2*dy;
            x += addx;
            y += addy;
         }
      }
   }
}

/*void linexy(int8 x1,int8 y1,int8 x2,int8 y2, int1 COLOR){
   int length_x, length_y, i;
   float divResult;
   length_x = abs((signed int)(x2 - x1));
   length_y = abs((signed int)(y2 - y1));
   
   if(length_x < length_y){
      divResult = (float)(length_x / length_y);
      for(i = 0; i < length_y+1;i++)
         PE12864_Putpixel(x1+ceil(divResult*i), y1+i, ON);
   }
   else{
      divResult = (float)(length_y / length_x);
      for(i = 0; i < length_x+1;i++)
         PE12864_Putpixel(x1+i, y1+ceil(divResult*i), ON);
   }   
}
*/
