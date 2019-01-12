//////////////////////
///    lcd1100.c
///
///    by Fatih GENC
///    fatihgenc81@hotmail.com
///    5/5/2011
//////////////////////

#define sclk   PIN_B3
#define sda    PIN_B2
#define cs     PIN_B1
#define rst    PIN_B0

#define CMD      0
#define DATA     1

#define lcd_WIDTH   96

#ifndef ON
#define ON           1
#endif

#ifndef OFF
#define OFF          0
#endif

void Lcd_Clear(void);
void Lcd_Init(void);
void Lcd_Write(int1 cd,unsigned char c);
void Gotoxy(char x,char y);
void lcd_pixel(unsigned char x,unsigned char y, int1 color);
void lcd_line(int8 x1, int8 y1, int8 x2, int8 y2, int1 color);
void lcd_circle(int8 x, int8 y, int8 radius, int1 fill, int1 color);
void lcd_text57(int8 x, int8 y, char* textptr, int8 size, int1 color);
void lcd_rect(int8 x1, int8 y1, int8 x2, int8 y2, int1 fill, int1 color);


static int8 memory[96][8]; //LCD memory data
static int8 XX,YY;


// lookup table, here you can modify the font
const int8 FONT[51][5] ={0x00, 0x00, 0x00, 0x00, 0x00, // SPACE
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
                         0x08, 0x08, 0x08, 0x08, 0x08, // -
                         0x00, 0x60, 0x60, 0x00, 0x00, // .
                         0x20, 0x10, 0x08, 0x04, 0x02, // /
                         0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
                         0x00, 0x04, 0x02, 0x7F, 0x00, // 1
                         0x42, 0x61, 0x51, 0x49, 0x46, // 2
                         0x22, 0x41, 0x49, 0x49, 0x36, // 3
                         0x18, 0x14, 0x12, 0x7F, 0x10, // 4
                         0x27, 0x45, 0x45, 0x45, 0x39, // 5
                         0x3E, 0x49, 0x49, 0x49, 0x32, // 6
                         0x01, 0x01, 0x71, 0x09, 0x07, // 7
                         0x36, 0x49, 0x49, 0x49, 0x36, // 8
                         0x26, 0x49, 0x49, 0x49, 0x3E, // 9
                         0x00, 0x36, 0x36, 0x00, 0x00, // :
                         0x00, 0x56, 0x36, 0x00, 0x00, // ;
                         0x08, 0x14, 0x22, 0x41, 0x00, // <
                         0x14, 0x14, 0x14, 0x14, 0x14, // =
                         0x00, 0x41, 0x22, 0x14, 0x08, // >
                         0x02, 0x01, 0x51, 0x09, 0x06, // ?
                         0x3E, 0x41, 0x59, 0x55, 0x5E, // @
                         0x7E, 0x09, 0x09, 0x09, 0x7E, // A
                         0x7F, 0x49, 0x49, 0x49, 0x36, // B
                         0x3E, 0x41, 0x41, 0x41, 0x22, // C
                         0x7F, 0x41, 0x41, 0x41, 0x3E, // D
                         0x7F, 0x49, 0x49, 0x49, 0x41, // E
                         0x7F, 0x09, 0x09, 0x09, 0x01, // F
                         0x3E, 0x41, 0x41, 0x49, 0x3A, // G
                         0x7F, 0x08, 0x08, 0x08, 0x7F, // H
                         0x00, 0x41, 0x7F, 0x41, 0x00, // I
                         0x30, 0x40, 0x40, 0x40, 0x3F, // J
                         0x7F, 0x08, 0x14, 0x22, 0x41, // K
                         0x7F, 0x40, 0x40, 0x40, 0x40, // L
                         0x7F, 0x02, 0x0C, 0x02, 0x7F, // M
                         0x7F, 0x02, 0x04, 0x08, 0x7F, // N
                         0x3E, 0x41, 0x41, 0x41, 0x3E, // O
                         0x7F, 0x09, 0x09, 0x09, 0x06, // P
                         0x1E, 0x21, 0x21, 0x21, 0x5E, // Q
                         0x7F, 0x09, 0x09, 0x09, 0x76};// R

const int8 FONT2[44][5]={0x26, 0x49, 0x49, 0x49, 0x32, // S
                         0x01, 0x01, 0x7F, 0x01, 0x01, // T
                         0x3F, 0x40, 0x40, 0x40, 0x3F, // U
                         0x1F, 0x20, 0x40, 0x20, 0x1F, // V
                         0x7F, 0x20, 0x10, 0x20, 0x7F, // W
                         0x41, 0x22, 0x1C, 0x22, 0x41, // X
                         0x07, 0x08, 0x70, 0x08, 0x07, // Y
                         0x61, 0x51, 0x49, 0x45, 0x43, // Z
                         0x00, 0x7F, 0x41, 0x00, 0x00, // [
                         0x02, 0x04, 0x08, 0x10, 0x20, // \
                         0x00, 0x00, 0x41, 0x7F, 0x00, // ]
                         0x00, 0x07, 0x05, 0x07, 0x00, // ° (degree)
                         0x40, 0x40, 0x40, 0x40, 0x40, // _
                         0x00, 0x01, 0x02, 0x04, 0x00, // `
                         0x20, 0x54, 0x54, 0x54, 0x78, // a
                         0x7F, 0x44, 0x44, 0x44, 0x38, // b
                         0x38, 0x44, 0x44, 0x44, 0x44, // c
                         0x38, 0x44, 0x44, 0x44, 0x7F, // d
                         0x38, 0x54, 0x54, 0x54, 0x18, // e
                         0x04, 0x04, 0x7E, 0x05, 0x05, // f
                         0x08, 0x54, 0x54, 0x54, 0x3C, // g
                         0x7F, 0x08, 0x04, 0x04, 0x78, // h
                         0x00, 0x44, 0x7D, 0x40, 0x00, // i
                         0x20, 0x40, 0x44, 0x3D, 0x00, // j
                         0x7F, 0x10, 0x28, 0x44, 0x00, // k
                         0x00, 0x41, 0x7F, 0x40, 0x00, // l
                         0x7C, 0x04, 0x78, 0x04, 0x78, // m
                         0x7C, 0x08, 0x04, 0x04, 0x78, // n
                         0x38, 0x44, 0x44, 0x44, 0x38, // o
                         0x7C, 0x14, 0x14, 0x14, 0x08, // p
                         0x08, 0x14, 0x14, 0x14, 0x7C, // q
                         0x00, 0x7C, 0x08, 0x04, 0x04, // r
                         0x48, 0x54, 0x54, 0x54, 0x20, // s
                         0x04, 0x04, 0x3F, 0x44, 0x44, // t
                         0x3C, 0x40, 0x40, 0x20, 0x7C, // u
                         0x1C, 0x20, 0x40, 0x20, 0x1C, // v
                         0x3C, 0x40, 0x30, 0x40, 0x3C, // w
                         0x44, 0x28, 0x10, 0x28, 0x44, // x
                         0x0C, 0x50, 0x50, 0x50, 0x3C, // y
                         0x44, 0x64, 0x54, 0x4C, 0x44, // z
                         0x00, 0x08, 0x36, 0x41, 0x41, // {
                         0x00, 0x00, 0x7F, 0x00, 0x00, // |
                         0x41, 0x41, 0x36, 0x08, 0x00, // }
                         0x02, 0x01, 0x02, 0x04, 0x02};// ~
/////////////////////////////////////////////////////////////////////////


// clear LCD
void Lcd_Clear(void){
   unsigned int i;
   Lcd_Write(CMD,0x40); // Y = 0
   Lcd_Write(CMD,0xb0);
   Lcd_Write(CMD,0x10); // X = 0
   Lcd_Write(CMD,0x0);
   Lcd_Write(CMD,0xae); // disable display;
   for(i=0;i<255;i++)
   Lcd_Write(DATA,0x00);
   for(i=0;i<255;i++)
   Lcd_Write(DATA,0x00);
   for(i=0;i<255;i++)
   Lcd_Write(DATA,0x00);
   for(i=0;i<99;i++)
   Lcd_Write(DATA,0x00);
   Lcd_Write(CMD,0xaf); // enable display;
   }

// Purpose:       Initialize the LCD.
//                Call before using any other LCD function.
void Lcd_Init(void){
   output_low(cs);
   output_low(rst);
   delay_ms(5);         // 5mS so says the stop watch(less than 5ms will not work)
   output_high(rst);
   Lcd_Write(CMD,0x20); // write VOP register
   Lcd_Write(CMD,0x90);
   Lcd_Write(CMD,0xA4); // all on/normal display
   Lcd_Write(CMD,0x2F); // Power control set(charge pump on/off)
   Lcd_Write(CMD,0x40); // set start row address = 0
   Lcd_Write(CMD,0xb0); // set Y-address = 0
   Lcd_Write(CMD,0x10); // set X-address, upper 3 bits
   Lcd_Write(CMD,0x0);  // set X-address, lower 4 bits
   Lcd_Write(CMD,0xC8); // mirror Y axis (about X axis)
   Lcd_Write(CMD,0xa1); // Invert screen in horizontal axis
   Lcd_Write(CMD,0xac); // set initial row (R0) of the display
   Lcd_Write(CMD,0x07);
   //Lcd_Write(CMD,0xF9); //
   Lcd_Write(CMD,0xaf); // display ON/OFF
   
   Lcd_Clear(); // clear LCD
   Lcd_Write(CMD,0xa7); // invert display
   delay_ms(100);       
   Lcd_Write(CMD,0xa6); // normal display (non inverted)
   delay_ms(100);           
   }

// Purpose:    Write a byte of data to lcd
// Inputs:     c - the byte of data to write
void Lcd_Write(int1 cd,unsigned char c){
int i;
   output_low(cs);
   output_low(sclk);
   output_bit(sda,cd);
   output_high(sclk);

if(cd==DATA)
   {
   memory[XX][YY]= c; //write data to memory
   XX++;
   }

   for(i=0;i<8;i++){
      output_low(sclk);
      if((c & 0x80))
         output_high(sda);
      else
         output_low(sda);
      output_high(sclk);
      c <<= 1;
      delay_us(10);
   }
   output_high(cs);
        

 }

void Gotoxy(char x,char y){
      Lcd_Write(CMD,(0xB0|(y&0x0F)));       // Y axis initialisation: 0100 yyyy         
      Lcd_Write(CMD,(0x00|(x&0x0F)));       // X axis initialisation: 0000 xxxx ( x3 x2 x1 x0)
      Lcd_Write(CMD,(0x10|((x>>4)&0x07))); // X axis initialisation: 0010 0xxx  ( x6 x5 x4)

}

// Purpose:    Turn a pixel on a graphic LCD on or off
// Inputs:     1) x - the x coordinate of the pixel
//             2) y - the y coordinate of the pixel
//             3) color - ON or OFF
void lcd_pixel(unsigned char x,unsigned char y, int1 color){
   char aux[8];
   char i,o;
   char c=1;
   char index;
   int8 temp;
   
   XX=x;
   YY=y/8;

      Gotoxy(x,YY);           
      temp=memory[x][YY];
     
      if(color == ON)
         bit_set(temp, y%8);        // Turn the pixel on
         else                          // or
         bit_clear(temp, y%8);      // turn the pixel off
     
      Lcd_Write(DATA,temp);   
}

/////////////////////////////////////////////////////////////////////////
// Purpose:       Draw a line on a nokia 1100 LCD
//                line drawing algorithm
// Inputs:        (x1, y1) - the start coordinate
//                (x2, y2) - the end coordinate
//                color - ON or OFF
// Dependencies:  glcd_pixel()
/////////////////////////////////////////////////////////////////////////
void lcd_line(int8 x1, int8 y1, int8 x2, int8 y2, int1 color)
{
   int16        dy, dx;
   signed int8  addx=1, addy=1;
   signed int16 P, diff;

   int8 i=0;
   dx = abs((signed int8)(x2 - x1));
   dy = abs((signed int8)(y2 - y1));


   if(x1 > x2)
      addx = -1;
   if(y1 > y2)
      addy = -1;

   if(dx >= dy)
   {
      dy *= 2;
      P = dy - dx;
      diff = P - dx;

      for(; i<=dx; ++i)
      {
         lcd_pixel(x1, y1, color);

         if(P < 0)
         {
            P  += dy;
            x1 += addx;
         }
         else
         {
            P  += diff;
            x1 += addx;
            y1 += addy;
         }
      }
   }
   else
   {
      dx *= 2;
      P = dx - dy;
      diff = P - dy;

      for(; i<=dy; ++i)
      {
         lcd_pixel(x1, y1, color);

         if(P < 0)
         {
            P  += dx;
            y1 += addy;
         }
         else
         {
            P  += diff;
            x1 += addx;
            y1 += addy;
         }
      }
   }
}

/////////////////////////////////////////////////////////////////////////
// Purpose:       Draw a circle on a nokia 1100 LCD
// Inputs:        (x,y) - the center of the circle
//                radius - the radius of the circle
//                fill - YES or NO
//                color - ON or OFF
/////////////////////////////////////////////////////////////////////////
void lcd_circle(int8 x, int8 y, int8 radius, int1 fill, int1 color)
{
signed int8  a, b, P;

   a = 0;
   b = radius;
   P = 1 - radius;

   do
   {
      if(fill)
      {
         lcd_line(x-a, y+b, x+a, y+b, color);
         lcd_line(x-a, y-b, x+a, y-b, color);
         lcd_line(x-b, y+a, x+b, y+a, color);
         lcd_line(x-b, y-a, x+b, y-a, color);
      }
      else
      {
         lcd_pixel(a+x, b+y, color);
         lcd_pixel(b+x, a+y, color);
         lcd_pixel(x-a, b+y, color);
         lcd_pixel(x-b, a+y, color);
         lcd_pixel(b+x, y-a, color);
         lcd_pixel(a+x, y-b, color);
         lcd_pixel(x-a, y-b, color);
         lcd_pixel(x-b, y-a, color);
      }

      if(P < 0)
         P += 3 + 2 * a++;
      else
         P += 5 + 2 * (a++ - b--);
    } while(a <= b);
}

/////////////////////////////////////////////////////////////////////////
// Purpose:       Write text on a nokia 1100 LCD
// Inputs:        (x,y) - The upper left coordinate of the first letter
//                textptr - A pointer to an array of text to display
//                size - The size of the text: 1 = 5x7, 2 = 10x14, ...
//                color - ON or OFF
/////////////////////////////////////////////////////////////////////////
void lcd_text57(int8 x, int8 y, char* textptr, int8 size, int1 color)
{
   int8 j, k, l, m;                       // Loop counters
   int8 pixelData[5];                     // Stores character data

   for(; *textptr != '\0'; ++textptr, ++x)// Loop through the passed string
   {
      if(*textptr < 'S') // Checks if the letter is in the first font array
         memcpy(pixelData, FONT[*textptr - ' '], 5);
      else if(*textptr <= '~') // Check if the letter is in the second font array
         memcpy(pixelData, FONT2[*textptr - 'S'], 5);
      else
         memcpy(pixelData, FONT[0], 5);   // Default to space

      // Handles newline and carriage returns
      switch(*textptr)
      {
         case '\n':
            y += 7*size + 1;
            continue;
         case '\r':
            x = 0;
            continue;
      }

      if(x+5*size >= lcd_WIDTH)          // Performs character wrapping
      {
         x = 0;                           // Set x at far left position
         y += 7*size + 1;                 // Set y at next position down
      }
      for(j=0; j<5; ++j, x+=size)         // Loop through character byte data
      {
         for(k=0; k < 7; ++k)             // Loop through the vertical pixels
         {
            if(bit_test(pixelData[j], k)) // Check if the pixel should be set
            {
               for(l=0; l < size; ++l)    // These two loops change the
               {                          // character's size
                  for(m=0; m < size; ++m)
                  {
                     lcd_pixel(x+m, y+k*size+l, color); // Draws the pixel
                  }
               }
            }
         }
      }
   }
}

/////////////////////////////////////////////////////////////////////////
// Purpose:       Draw a rectangle on a nokia 1100 LCD
// Inputs:        (x1, y1) - the start coordinate
//                (x2, y2) - the end coordinate
//                fill  - YES or NO
//                color - ON or OFF
// Dependencies:  glcd_pixel(), glcd_line()
/////////////////////////////////////////////////////////////////////////
void lcd_rect(int8 x1, int8 y1, int8 x2, int8 y2, int1 fill, int1 color)
{
   if(fill)
   {
     
      int8  i, xmin, xmax, ymin, ymax;

      if(x1 < x2)                            //  Find x min and max
      {
         xmin = x1;
         xmax = x2;
      }
      else
      {
         xmin = x2;
         xmax = x1;
      }

      if(y1 < y2)                            // Find the y min and max
      {
         ymin = y1;
         ymax = y2;
      }
      else
      {
         ymin = y2;
         ymax = y1;
      }

      for(; xmin <= xmax; ++xmin)
      {
         for(i=ymin; i<=ymax; ++i)
         {
            lcd_pixel(xmin, i, color);
         }
      }
   }
   else
   {
      lcd_line(x1, y1, x2, y1, color);      // Draw the 4 sides
      lcd_line(x1, y2, x2, y2, color);
      lcd_line(x1, y1, x1, y2, color);
      lcd_line(x2, y1, x2, y2, color);
   }
} 
