
/////////////////////////RBJ_Electronics and MarlonRubik Drive PE12864///////////////////////////

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
                        // 0x20, 0x54, 0x54, 0x54, 0x78, // a
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







#define ST7565S_PIN_RD   pin_D7
#define ST7565S_PIN_WR   pin_D6
#define ST7565S_PIN_A0   pin_D5 // RS = A0
#define ST7565S_PIN_CS1  pin_D4
#define ST7565S_PIN_RES  pin_D3

#define ON   1
#define OFF  0

int8 CurrentLine = 0;
int8 QuantChrLine = 0;
int8 OffsetX = 0;

void    ST7565S_InitLcd(void);
void    ST7565S_Write_command(char byte_command);
void    ST7565S_Write_data(char byte_data);
int8    ST7565S_Read_data();
void    ST7565S_Gotoxy(int8 x, int y);
void    ST7565S_Printchar(char cvar);
void    ST7565S_PutPixel(int8 x,int8 y, int1 COLOR);
void    ST7565S_OutPort(char byteDC);
void    ST7565S_clear_screen(void);
void    ST7565S_newLine(void);
void    ST7565S_circle(int x, int y, int radius, int1 fill, int1 COLOR);
void    ST7565S_rect(int x1, int y1, int x2, int y2, int1 fill, int1 COLOR);
void    ST7565S_line(int x1, int y1, int x2, int y2, int1 COLOR);

/////////////////////////////////////////////////////////////


void    ST7565S_InitLcd(void)
{
                                
   output_low(ST7565S_PIN_CS1); // PIN_CS1"LOW" chip Select1 Enabled
   output_low(ST7565S_PIN_RES); // PIN_RES"LOW" //
   delay_us(5);                 // 2uS          //Reset by 10uS
   output_high(ST7565S_PIN_RES);// PIN_RES"HIGH"//
   delay_us(5);    
                                // Initialization Command
                                //------------------------------            (DATASHEET)
   ST7565S_Write_command(0xaf); // Display ON/OFF:(ON)                      (PAG.42/1º)
   ST7565S_Write_command(0x40); // Display Start Line Set addres:(0)        (PAG.42/2º)
   ST7565S_Write_command(0xb0); // Page Address Set:(0)                     (PAG.42/3º)
   
                                // Column address set                       (PAG.43/1º)
   ST7565S_Write_command(0x10); // column address high                   
   ST7565S_Write_command(0x00); // column address low 
   
   ST7565S_Write_command(0xc8); // Common Output Mode Select                (PAG.46/3º)          
   ST7565S_Write_command(0xa0); // ADC Select Select (0:normal)  1: Reverse (PAG.44/2º)
   ST7565S_Write_command(0xa6); // Display Normal/Reverse:(normal)          (PAG.44/3º)
   ST7565S_Write_command(0xa4); // Display All Points ON/OFF:(normal)       (PAG.44/4º)
   ST7565S_Write_command(0xa2); // LCD Bias Set  0: (1/9)                   (PAG.45/1º)
     
      
                                // Power Control Set                        (PAG.47/1º)
                                //-------------------------------       
   ST7565S_Write_command(0x2c); //Booster circuit ON  
   ST7565S_Write_command(0x2e); //Voltage regulator circuit ON
   ST7565S_Write_command(0x2f); //Voltage follower circuit ON
   ST7565S_Write_command(0x26); //Voltage Regulator Internal Resistor Ratio Set:V5
     
                                // Set Brightness
                                //-----------------------------
   ST7565S_Write_command(0x81); // The Electronic Volume (Double Byte Command)
   ST7565S_Write_command(0x17); // The Electronic Volume Mode Set            (PAG.47/3º)
   
   ST7565S_clear_screen ();     //clear screen
   delay_ms(1);
}

///////////////////////////////////////////////////////////////////


void ST7565S_OutPort(char byteDC)// Data or Command
{
  output_low (ST7565S_PIN_CS1); //PIN_CS1"0"  Enabled I/O
  output_high(ST7565S_PIN_RD);  //PIN_RD "0"
  output_low (ST7565S_PIN_WR);  //PIN_WR "0"
  output_b(byteDC);
  output_high(ST7565S_PIN_CS1); //PIN_CS1"1" Disabled I/O 
}

///////////////////////////////////////////////////////////////////

void    ST7565S_Write_command(char byte_command)
{
  output_low (ST7565S_PIN_A0); //PIN_A0"0" Write Command Enabled
  output_high(ST7565S_PIN_RD); //PIN_RD"1" RD Enabled
  output_low (ST7565S_PIN_WR); //PIN_WR"0" Mode Write  
  
  ST7565S_OutPort(byte_command);
}

/////////////////////////////////////////////////////////////////


void    ST7565S_Write_data(char byte_data)
{
  output_high(ST7565S_PIN_A0); //PIN_A0"1" Write data Enabled
  output_high(ST7565S_PIN_RD); //PIN_RD"1" RD Enabled
  output_low (ST7565S_PIN_WR); //PIN_WR"0" Mode Write 
  
  ST7565S_OutPort(byte_data);
  OffsetX++;
  ST7565S_Gotoxy(OffsetX,CurrentLine);
}


////////////////////////////////////////////////////////////////

char    ST7565S_Read_data()
{
  ST7565S_Write_command(0xe0);   // Set Modify Read  (0xee to cancel)(PAG.45/2º) 
  set_tris_b(0xff);              // Port_Output
  
  //-----------DUMMY READ----------------------//                               
  output_low  (ST7565S_PIN_CS1); //  Enable Bus I/O
  output_high (ST7565S_PIN_A0);  // 
  output_low  (ST7565S_PIN_RD);  // 
  output_high (ST7565S_PIN_WR);  //  Mode Read
  output_high (ST7565S_PIN_CS1); //  Disabled Bus I/O
  delay_us(1);
  //------------DATA READ---------------------//
  output_low  (ST7565S_PIN_CS1); //  Enable Bus I/O
  output_high (ST7565S_PIN_A0);  // 
  output_low  (ST7565S_PIN_RD);  //
  output_high (ST7565S_PIN_WR);  //  Mode Read
  return input_b();              
  output_high (ST7565S_PIN_CS1); //  Disabled Bus I/O   
}

/////////////////////////////////////////////////////////////////


void    ST7565S_newLine(void)

{
  if(CurrentLine < 7)  // New Line Command
  {  
      ST7565S_Write_command((CurrentLine+1)|0xb0);  // Set Page Address to 0 (0 a 7)
      ST7565S_Write_command(0x00);  // Set LSB for index Column
      ST7565S_Write_command(0x10);  // Set MSB for index Column   
      CurrentLine+=1;
  }
  QuantChrLine = 1;
  OffsetX = 0;
}


///////////////////////////////////////////////////////////////////



void  ST7565S_clear_screen(void) 

{
   int p, c;
   for(p = 0; p < 8; p++)
   {
      for(c = 0; c < 128; c++) 
      {
         ST7565S_Gotoxy(c,p);
         ST7565S_Write_data(0x00);
         }
   }
   ST7565S_Gotoxy(0,0);   
}


///////////////////////////////////////////////////////////////////

void    ST7565S_Gotoxy(int x, int y)


{
   int8 OffsetChr = 0;
   
   ST7565S_Write_command(0xb0 | y);
   ST7565S_Write_command((0x00 | x) & 0x0f);
   ST7565S_Write_command(0x10|(x>>4));
   
   OffsetChr = (x+1)/6;
   if((x+1)%6)
      OffsetChr++;   
   CurrentLine = y;
   QuantChrLine = OffsetChr;
   OffsetX = x;
}


//////////////////////////////////////////////////////////////


void    ST7565S_Printchar(char cvar)

{
   int i;
   if (QuantChrLine > 21)  
      ST7565S_newLine(); 
   else
       QuantChrLine++;    
   if(cvar == 0x20)
      for(i=0;i<2;i++)
         ST7565S_Write_data(0x00);
   else{
      for(i=0;i<5;i++){
         if (cvar < 0x53){
            if(TEXT[cvar-0x20][i])         
               ST7565S_Write_data(TEXT[cvar-0x20][i]);      
         }
         else {
            if(TEXT2[cvar-0x53][i])               
               ST7565S_Write_data(TEXT2[cvar-0x53][i]);               
         }
      }
   }
   ST7565S_Write_data(0x00);
}

////////////////////////////////////////////////////////////////


void ST7565S_PutPixel(int x, int y, int1 COLOR)
{
   char BytePlot = 0 , tempByte ;
   if((x > 127)||(y > 63))
    return;
   BytePlot |= 1;
   BytePlot<<=(y%8);
   tempByte = BytePlot;
   ST7565S_Gotoxy( x,(y/8));
   BytePlot|= ST7565S_Read_data();
   if(COLOR == OFF)
      BytePlot-=tempByte;
   ST7565S_Write_data(BytePlot);
   
}


////////////////////////////////////////////////////////////////////////


void ST7565S_circle(int x, int y, int radius, int1 fill, int1 COLOR)

{
   signed int a, b, P;
   a = 0;
   b = radius;
   P = 1 - radius;
   do{
      if(fill)
      {
         ST7565S_line(x-a, y+b, x+a, y+b, color);
         ST7565S_line(x-a, y-b, x+a, y-b, color);
         ST7565S_line(x-b, y+a, x+b, y+a, color);
         ST7565S_line(x-b, y-a, x+b, y-a, color);
      }
      else
      {
         ST7565S_PutPixel(a+x, b+y, color);
         ST7565S_PutPixel(b+x, a+y, color);
         ST7565S_PutPixel(x-a, b+y, color);
         ST7565S_PutPixel(x-b, a+y, color);
         ST7565S_PutPixel(b+x, y-a, color);
         ST7565S_PutPixel(a+x, y-b, color);
         ST7565S_PutPixel(x-a, y-b, color);
         ST7565S_PutPixel(x-b, y-a, color);
      }
      if(P < 0)
         P+= 3 + 2*a++;
      else
         P+= 5 + 2*(a++ - b--);
    } while(a <= b);
}


//////////////////////////////////////////////////////////////////////////////

void ST7565S_rect(int x1, int y1, int x2, int y2, int1 fill, int1 color)
{
   if(fill)
   {
      int y, ymax;                               // Find the y min and max
      if(y1 < y2)
      {
         y = y1;
         ymax = y2;
      }
      else
      {
         y = y2;
         ymax = y1;
      }

      for(; y<=ymax; ++y)                       // Draw lines to fill the rectangle
         ST7565S_line(x1, y, x2, y, color);
   }
   else
   {
      ST7565S_line(x1, y1, x2, y1, color);      // Draw the 4 sides
      ST7565S_line(x1, y2, x2, y2, color);
      ST7565S_line(x1, y1, x1, y2, color);
      ST7565S_line(x2, y1, x2, y2, color);
   }
}


//////////////////////////////////////////////////////////////////////////////

void ST7565S_line(int x1, int y1, int x2, int y2, int1 COLOR)

{
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
         ST7565S_PutPixel(x, y, COLOR);
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
         ST7565S_PutPixel(x, y, COLOR);

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

