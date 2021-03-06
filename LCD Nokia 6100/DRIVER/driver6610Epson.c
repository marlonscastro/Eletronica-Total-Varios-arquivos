#include "nokialcd_io.h"
#include "nokialcd_driver.h"
#include "nokialcd_controlcodes.h"

static const char font5x8[] = {
// taken from KS0108 library, http://en.radzio.dxp.pl
// (c) Rados�aw Kwiecie�, radek@dxp.pl
   0x00, 0x00, 0x00, 0x00, 0x00, // (spacja)
   0x00, 0x00, 0x5F, 0x00, 0x00, // !
   0x00, 0x07, 0x00, 0x07, 0x00, // "
   0x14, 0x7F, 0x14, 0x7F, 0x14, // #
   0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
   0x23, 0x13, 0x08, 0x64, 0x62, // %
   0x36, 0x49, 0x55, 0x22, 0x50, // &
   0x00, 0x05, 0x03, 0x00, 0x00, // '
   0x00, 0x1C, 0x22, 0x41, 0x00, // (
   0x00, 0x41, 0x22, 0x1C, 0x00, // )
   0x08, 0x2A, 0x1C, 0x2A, 0x08, // *
   0x08, 0x08, 0x3E, 0x08, 0x08, // +
   0x00, 0x50, 0x30, 0x00, 0x00, // ,
   0x08, 0x08, 0x08, 0x08, 0x08, // -
   0x00, 0x30, 0x30, 0x00, 0x00, // .
   0x20, 0x10, 0x08, 0x04, 0x02, // /
   0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
   0x00, 0x42, 0x7F, 0x40, 0x00, // 1
   0x42, 0x61, 0x51, 0x49, 0x46, // 2
   0x21, 0x41, 0x45, 0x4B, 0x31, // 3
   0x18, 0x14, 0x12, 0x7F, 0x10, // 4
   0x27, 0x45, 0x45, 0x45, 0x39, // 5
   0x3C, 0x4A, 0x49, 0x49, 0x30, // 6
   0x01, 0x71, 0x09, 0x05, 0x03, // 7
   0x36, 0x49, 0x49, 0x49, 0x36, // 8
   0x06, 0x49, 0x49, 0x29, 0x1E, // 9
   0x00, 0x36, 0x36, 0x00, 0x00, // :
   0x00, 0x56, 0x36, 0x00, 0x00, // ;
   0x00, 0x08, 0x14, 0x22, 0x41, // <
   0x14, 0x14, 0x14, 0x14, 0x14, // =
   0x41, 0x22, 0x14, 0x08, 0x00, // >
   0x02, 0x01, 0x51, 0x09, 0x06, // ?
   0x32, 0x49, 0x79, 0x41, 0x3E, // @
   0x7E, 0x11, 0x11, 0x11, 0x7E, // A
   0x7F, 0x49, 0x49, 0x49, 0x36, // B
   0x3E, 0x41, 0x41, 0x41, 0x22, // C
   0x7F, 0x41, 0x41, 0x22, 0x1C, // D
   0x7F, 0x49, 0x49, 0x49, 0x41, // E
   0x7F, 0x09, 0x09, 0x01, 0x01, // F
   0x3E, 0x41, 0x41, 0x51, 0x32, // G
   0x7F, 0x08, 0x08, 0x08, 0x7F, // H
   0x00, 0x41, 0x7F, 0x41, 0x00, // I
   0x20, 0x40, 0x41, 0x3F, 0x01, // J
   0x7F, 0x08, 0x14, 0x22, 0x41, // K
   0x7F, 0x40, 0x40, 0x40, 0x40, // L
   0x7F, 0x02, 0x04, 0x02, 0x7F, // M
   0x7F, 0x04, 0x08, 0x10, 0x7F, // N
   0x3E, 0x41, 0x41, 0x41, 0x3E, // O
   0x7F, 0x09, 0x09, 0x09, 0x06, // P
   0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
   0x7F, 0x09, 0x19, 0x29, 0x46, // R
   0x46, 0x49, 0x49, 0x49, 0x31, // S
   0x01, 0x01, 0x7F, 0x01, 0x01, // T
   0x3F, 0x40, 0x40, 0x40, 0x3F, // U
   0x1F, 0x20, 0x40, 0x20, 0x1F, // V
   0x7F, 0x20, 0x18, 0x20, 0x7F, // W
   0x63, 0x14, 0x08, 0x14, 0x63, // X
   0x03, 0x04, 0x78, 0x04, 0x03, // Y
   0x61, 0x51, 0x49, 0x45, 0x43, // Z
   0x00, 0x00, 0x7F, 0x41, 0x41, // [
   0x02, 0x04, 0x08, 0x10, 0x20, // "\"
   0x41, 0x41, 0x7F, 0x00, 0x00, // ]
   0x04, 0x02, 0x01, 0x02, 0x04, // ^
   0x40, 0x40, 0x40, 0x40, 0x40, // _
   0x00, 0x01, 0x02, 0x04, 0x00, // `
   0x20, 0x54, 0x54, 0x54, 0x78, // a
   0x7F, 0x48, 0x44, 0x44, 0x38, // b
   0x38, 0x44, 0x44, 0x44, 0x20, // c
   0x38, 0x44, 0x44, 0x48, 0x7F, // d
   0x38, 0x54, 0x54, 0x54, 0x18, // e
   0x08, 0x7E, 0x09, 0x01, 0x02, // f
   0x08, 0x14, 0x54, 0x54, 0x3C, // g
   0x7F, 0x08, 0x04, 0x04, 0x78, // h
   0x00, 0x44, 0x7D, 0x40, 0x00, // i
   0x20, 0x40, 0x44, 0x3D, 0x00, // j
   0x00, 0x7F, 0x10, 0x28, 0x44, // k
   0x00, 0x41, 0x7F, 0x40, 0x00, // l
   0x7C, 0x04, 0x18, 0x04, 0x78, // m
   0x7C, 0x08, 0x04, 0x04, 0x78, // n
   0x38, 0x44, 0x44, 0x44, 0x38, // o
   0x7C, 0x14, 0x14, 0x14, 0x08, // p
   0x08, 0x14, 0x14, 0x18, 0x7C, // q
   0x7C, 0x08, 0x04, 0x04, 0x08, // r
   0x48, 0x54, 0x54, 0x54, 0x20, // s
   0x04, 0x3F, 0x44, 0x40, 0x20, // t
   0x3C, 0x40, 0x40, 0x20, 0x7C, // u
   0x1C, 0x20, 0x40, 0x20, 0x1C, // v
   0x3C, 0x40, 0x30, 0x40, 0x3C, // w
   0x44, 0x28, 0x10, 0x28, 0x44, // x
   0x0C, 0x50, 0x50, 0x50, 0x3C, // y
   0x44, 0x64, 0x54, 0x4C, 0x44, // z
   0x00, 0x08, 0x36, 0x41, 0x00, // {
   0x00, 0x00, 0x7F, 0x00, 0x00, // |
   0x00, 0x41, 0x36, 0x08, 0x00, // }
   0x08, 0x08, 0x2A, 0x1C, 0x08, // ->
   0x08, 0x1C, 0x2A, 0x08, 0x08  // <-
};


// 12-Bit Color Definitions
#define WHITE   0xFFF
#define BLACK   0x000
#define RED     0xF00
#define GREEN   0x0F0
#define BLUE    0x00F
#define CYAN    0x0FF
#define MAGENTA 0xF0F
#define YELLOW  0xFF0
#define BROWN   0xB22
#define ORANGE  0xFA0
#define PINK    0xF6A

#define FONT_WIDTH 6
#define FONT_HEIGHT 8

#define LCD_PORT   PORTD
#define LCD_PIN    PIND
#define LCD_DDR    DDRD

#define LCDRST     pin_A1//(1 << 4)
#define LCDCS      pin_A0
#define SPICLK     pin_B0//(1 << 1)
#define SPIDATA    pin_B1//(1 << 2)
//#define SPIMISO    pin_b3;//(1 << 3)

#define ON   1
#define OFF  0

// FIXME - these depend upon the vendor
// correction factor that modifies operation of LCDSetWindow
#define LCD_Y_OFFSET 2
// number of visible pixels
#define LCD_WIDTH 130
#define LCD_HEIGHT 130

void LCDInitController();
void LCDWriteWindow(int x1, int y1, int x2, int y2);
void LCDWritePair(int c1, int c2);
void LCDSetPixel(int color, int x, int y);
void LCDFillBox(int color, int x1, int y1, int x2, int y2);
void LCDClearScreen(int color);
void drawChar(char c, int fg, int bg, int x, int y);
void drawString(char *s, int fg, int bg, int x, int y);
void LCDCommand(int data);
void LCDData(int data);
void Epson_InitLcd(void);

/*void LCDCommand(int data){
   unsigned char dbyte, i, mask = 0x80;

   data&=0xff;
   output_low(LCDCS);  //LCDCS
   if(data & 0x100) {
      output_high(SPIDATA); //SPIMOSI
   } else {
      output_low(SPIDATA);  //SPIMOSI
   }
   output_low(SPICLK);  //SPICLK
   dbyte = data;
   //bitsleep();
   output_high(SPICLK); //SPICLK
 
   for (i=8; i>0; i--) {
    output_low(SPICLK);
    if (dbyte&mask)
      output_high(SPIDATA);
    else
      output_low(SPIDATA);
      output_low(SPICLK);         //SPICLK      
      mask>>=0x01;
      output_high(SPICLK);      //SPICLK    
   }   
   output_high(LCDCS);
   //bitsleep();
}
void LCDData(int data){
   unsigned char dbyte, i, mask = 0x80;
   data = 0x100 + ((data) & 0xff);
   output_low(LCDCS);  //LCDCS
   if(data & 0x100) {
      output_high(SPIDATA); //SPIMOSI
   } else {
      output_low(SPIDATA);  //SPIMOSI
   }
   output_low(SPICLK);  //SPICLK
   dbyte = data;
   //bitsleep();
   output_high(SPICLK); //SPICLK
 
   for (i=8; i>0; i--) {
    output_low(SPICLK);
    if (dbyte&mask)
      output_high(SPIDATA);
    else
      output_low(SPIDATA);
      output_low(SPICLK);         //SPICLK      
      mask>>=0x01;
      output_high(SPICLK);      //SPICLK    
   }   
   output_high(LCDCS);
   //bitsleep();
}*/
void LCDData(int data) {
   int j;
   output_low(LCDCS);
   //data = 0x100 + ((data) & 0xff);
   
   output_low(SPICLK);
   output_high(SPIDATA);   
   output_high(SPICLK);   
   for (j=8; j; j--) {
    output_low(SPICLK);
    if (data&0x80)
      output_high(SPIDATA);
    else
      output_low(SPIDATA);
      data<<=0x01;
      output_high(SPICLK);      //SPICLK    
   }       
   output_high(LCDCS);
}
void LCDCommand(int data) {
   int j;
   output_low(LCDCS);
   //data&=0xff;
  
   output_low(SPICLK);
   output_low(SPIDATA);   
   output_high(SPICLK);   
   for (j=8; j; j--) {
    output_low(SPICLK);
    if (data&0x80)
      output_high(SPIDATA);
    else
      output_low(SPIDATA);
      data<<=0x01;
      output_high(SPICLK);      //SPICLK    
   }       
   output_high(LCDCS);
}

void    Epson_InitLcd(void){
   //LCD_DDR |= (SPICLK | SPIMOSI | LCDCS | LCDRST);
  // LCD_DDR &= ~SPIMISO;
   
   output_low(SPICLK);   //SPICLK
   output_low(SPIDATA);  //SPIMOSI
   output_high(LCDCS);   //LCDCS
   output_low(LCDRST);   //LCDRST

   delay_ms(5);
   output_high(LCDRST);
   output_high(SPICLK);
   output_high(SPIDATA);   

   delay_ms(5);  

   LCDCommand(EP_DISCTL);     // display control(EPSON)
   LCDData(0x0C);         // 12 = 1100 - CL dividing ratio [don't divide] switching period 8H (default)
   LCDData(0x20);         // 130 line display
   LCDData(0x00);         // no inversely highlighted lines
   LCDData(0x01);         // dispersion
   
   LCDCommand(EP_COMSCN);     // common scanning direction(EPSON)
   LCDData(0x01);
    
   LCDCommand(EP_OSCON);     // internal oscillator ON(EPSON)
   
   LCDCommand(EP_SLPOUT);     // sleep out(EPSON)

   LCDCommand(EP_PWRCTR);    // power ctrl(EPSON)
   LCDData(0x0F);          //everything on, no external reference resistors
   LCDCommand(EP_DISINV);     // invert display mode(EPSON)

   LCDCommand(EP_DATCTL);     // data control(EPSON)
   LCDData(0x00);         // normal column addressing
   LCDData(0x00);         // normal RGB arrangement
   LCDData(0x02);         // 16-bit Grayscale Type A
   
   LCDCommand(EP_VOLCTR);     // electronic volume, this is the contrast/brightness(EPSON)
   LCDData(0x28);         // volume (contrast) setting - fine tuning, original
   LCDData(0x03);         // internal resistor ratio - coarse adjustment

   LCDCommand(EP_NOP);     // nop(EPSON)

   //for(j=0; j<30000; j++) {}
   delay_ms(1);

   LCDCommand(EP_DISON);      // display on(EPSON)
   
}

/*void drawChar(char c, int fg, int bg, int x, int y) {
   int idx = c-' ';
   if(idx < 0 || idx >= 96) idx = 0;
   const char *p = font5x8 + idx*5;

   LCDWriteWindow(x, y, x+5, y+8);
   for(int j=0; j<8; j++) {
      char mask = (1<<j);
      for(int i=0; i<3; i++) {
//#if FONT_AVR_PGMSPACE
//         char b1 = pgm_read_byte(p + i*2) & mask;
 //        char b2 = (i==2) ? 0 : pgm_read_byte(p + i*2+1) & mask;
//#else
         char b1 = p[i*2] & mask;
         char b2 = (i==2) ? 0 : p[i*2+1] & mask;
//#endif
         LCDWritePair(b1?fg:bg, b2?fg:bg);
      }
   }
}
void drawString(char *s, int fg, int bg, int x, int y) {
   while(*s) {
      drawChar(*s, fg, bg, x, y);
      x += 6;
      s++;
   }
}
*/

static inline void LCDSetWindow(int x1, int y1, int x2, int y2) {
   LCDCommand(LCD_PASET);   // page start/end ram
   LCDData(y1 + LCD_Y_OFFSET);
   LCDData(y2 + LCD_Y_OFFSET);

   LCDCommand(LCD_CASET);   // column start/end ram
   LCDData(x1);
   LCDData(x2);
}

static inline void LCDBeginWrite() {
   LCDCommand(LCD_RAMWR);
}

void LCDWriteWindow(int x1, int y1, int x2, int y2) {
   LCDSetWindow(x1, y1, x2, y2);
   LCDBeginWrite();
}

void LCDWritePair(int c1, int c2) {
   LCDData(c1 >> 4);
   LCDData((c1<<4) | ((c2>>8) & 0x0f));
   LCDData(c2);
}

void LCDSetPixel(int color, int x, int y) {
   LCDWriteWindow(x, y, x, y);
   LCDWritePair(0, color);
}

void LCDFillBox(int color, int x1, int y1, int x2, int y2) {
   int c1 = color >> 4;
   int c2 = (color<<4) | ((color>>8) & 0x0f);
   int c3 = color;
   int i;
   int num_words = ((x2-x1+1) * (y2-y1+1) + 1) / 2;

   LCDWriteWindow(x1, y1, x2, y2);
   for(i=0; i<num_words; i++) {
      LCDData(c1);
      LCDData(c2);
      LCDData(c3);
   }
}

void LCDClearScreen(int color) {
   LCDFillBox(color, 0, 0, LCD_WIDTH-1, LCD_HEIGHT-1);
}
