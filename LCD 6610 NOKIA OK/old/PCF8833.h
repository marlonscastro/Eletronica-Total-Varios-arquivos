#ifndef  PCF8833_H
#define  PCF8833_H
///////////////////////////////////////////////////////////////////////////////
#include <string.h>
///////////////////////////////////////////////////////////////////////////////
// Philips PCF8833 LCD controller command codes
#define P_NOP 0x00 // nop
#define P_SWRESET 0x01 // software reset
#define P_BSTROFF 0x02 // booster voltage OFF
#define P_BSTRON 0x03 // booster voltage ON
#define P_RDDIDIF 0x04 // read display identification
#define P_RDDST 0x09 // read display status
#define P_SLEEPIN 0x10 // sleep in
#define P_SLEEPOUT 0x11 // sleep out
#define P_PTLON 0x12 // partial display mode
#define P_NORON 0x13 // display normal mode
#define P_INVOFF 0x20 // inversion OFF
#define P_INVON 0x21 // inversion ON
#define P_DALO 0x22 // all pixel OFF
#define P_DAL 0x23 // all pixel ON
#define P_SETCON 0x25 // write contrast
#define P_DISPOFF 0x28 // display OFF
#define P_DISPON 0x29 // display ON
#define P_CASET 0x2A // column address set
#define P_PASET 0x2B // page address set
#define P_RAMWR 0x2C // memory write
#define P_RGBSET 0x2D // colour set
#define P_PTLAR 0x30 // partial area
#define P_VSCRDEF 0x33 // vertical scrolling definition
#define P_TEOFF 0x34 // test mode
#define P_TEON 0x35 // test mode
#define P_MADCTL 0x36 // memory access control
#define P_SEP 0x37 // vertical scrolling start address
#define P_IDMOFF 0x38 // idle mode OFF
#define P_IDMON 0x39 // idle mode ON
#define P_COLMOD 0x3A // interface pixel format
#define P_SETVOP 0xB0 // set Vop
#define P_BRS 0xB4 // bottom row swap
#define P_TRS 0xB6 // top row swap
#define P_DISCTR 0xB9 // display control
#define P_DOR 0xBA // data order
#define P_TCDFE 0xBD // enable/disable DF temperature compensation
#define P_TCVOPE 0xBF // enable/disable Vop temp comp
#define P_EC 0xC0 // internal or external oscillator
#define P_SETMUL 0xC2 // set multiplication factor
#define P_TCVOPAB 0xC3 // set TCVOP slopes A and B
#define P_TCVOPCD 0xC4 // set TCVOP slopes c and d
#define P_TCDF 0xC5 // set divider frequency
#define P_DF8COLOR 0xC6 // set divider frequency 8-color mode
#define P_SETBS 0xC7 // set bias system
#define P_RDTEMP 0xC8 // temperature read back
#define P_NLI 0xC9 // n-line inversion
#define P_RDID1 0xDA // read ID1
#define P_RDID2 0xDB // read ID2
#define P_RDID3 0xDC // read ID3
///////////////////////////////////////////////////////////////////////////////
void PCF8833_write_data(int8 data)
{
   NLCD_CS = 0;
   
   //Disable SPI:
   SSPEN = 0;
   SSP2STAT = 0x00;
   
   //Tx first data bit:
   NLCD_SDO = 1;  //set data bit
   NLCD_SCLK= 1;  //1 clock pulse
   delay_cycles(4);
   NLCD_SCLK= 0;  //clk low
   NLCD_SDO = 0;  //data low
   
   //re-enable SPI:
   SSPEN = 1;
   SSP2STAT = 0x40;
   spi_write2(data);
   
   NLCD_CS = 1;
}
///////////////////////////////////////////////////////////////////////////////
void PCF8833_write_command(int8 command)
{
   NLCD_CS = 0;
   
   //Disable SPI:
   SSPEN = 0;
   SSP2STAT = 0x00;
   
   //Tx first data bit:
   NLCD_SDO = 0;  //clear data bit
   NLCD_SCLK= 1;  //1 clock pulse
   delay_cycles(4);
   NLCD_SCLK= 0;  //clk low
   NLCD_SDO = 0;  //data low
   
   //re-enable SPI:
   SSPEN = 1;
   SSP2STAT = 0x40;
   spi_write2(command);
   
   NLCD_CS = 1;
}
///////////////////////////////////////////////////////////////////////////////
void PCF8833_init()
{
   NLCD_CS = 1;
   
   // Hardware reset
   NLCD_RESET = 0;
   delay_ms(50);
   NLCD_RESET = 1;
   delay_ms(50);
   // Sleep out (command 0x11)
   PCF8833_write_command(P_SLEEPOUT);
   // Inversion on (command 0x21)
   PCF8833_write_command(P_INVOFF); // seems to be required for this controller
   // Color Interface Pixel Format (command 0x3A)
   PCF8833_write_command(P_COLMOD);
   PCF8833_write_data(0x03); // 0x03 = 12 bits-per-pixel
   // Memory access controler (command 0x36)
   PCF8833_write_command(P_MADCTL);
   PCF8833_write_data(0x00); // 0xC0 = mirror x and y, reverse rgb
   // Write contrast (command 0x25)
   PCF8833_write_command(P_SETCON);
   PCF8833_write_data(0x30); // contrast 0x30
   delay_ms(50);
   // Display On (command 0x29)
   PCF8833_write_command(P_DISPON);
   
}
///////////////////////////////////////////////////////////////////////////////
void PCF8833_LCDClearScreen(void) {
   int16 i; // loop counter
   // Row address set (command 0x2B)
   PCF8833_write_command(P_PASET);
   PCF8833_write_data(0);
   PCF8833_write_data(131);
   // Column address set (command 0x2A)
   PCF8833_write_command(P_CASET);
   PCF8833_write_data(0);
   PCF8833_write_data(131);
   // set the display memory to BLACK
   PCF8833_write_command(P_RAMWR);
   For (i = 0; i < ((131 * 131) / 2); i++)
   {
      PCF8833_write_data((BLACK >> 4) & 0xFF);
      PCF8833_write_data(((BLACK & 0xF) << 4) | ((BLACK >> 8) & 0xF));
      PCF8833_write_data(BLACK & 0xFF);
   }
}
///////////////////////////////////////////////////////////////////////////////
void PCF8833_LCDSetPixel(int x, int y, int16 color)
{
   // Row address set (command 0x2B)
   PCF8833_write_command(P_PASET);
   PCF8833_write_data(y);
   PCF8833_write_data(y);
   // Column address set (command 0x2A)
   PCF8833_write_command(P_CASET);
   PCF8833_write_data(x);
   PCF8833_write_data(x);
   
   PCF8833_write_command(P_RAMWR);
   PCF8833_write_data((unsigned char)((color >> 4) & 0xFFFF));
   PCF8833_write_data((unsigned char)(((color & 0x0F) << 4) | 0x00));
   PCF8833_write_command(P_NOP);
   }
///////////////////////////////////////////////////////////////////////////////
void PCF8833_LCDPutChar(char c, int x, int y, int8 size, int16 fColor, int16 bColor)
{
   int8 i,j;
   unsigned int8 nCols;
   unsigned int8 nRows;
   unsigned int8 nBytes;
   unsigned char PixelRow;
   unsigned char Mask;
   unsigned int16 Word0;
   unsigned int16 Word1;
   unsigned char pChar[16];
   // get pointer to the beginning of the selected font table
   // &
   // get the nColumns, nRows and nBytes
   switch(size)
   {
      case 0:
         nCols = FONT6x8[0][0];
         nRows = FONT6x8[0][1];
         nBytes= FONT6x8[0][2];
         memcpy(pChar, FONT6x8[c - 0x1F], nBytes);
      break;
     
      case 1:
         nCols = FONT8x8[0][0];
         nRows = FONT8x8[0][1];
         nBytes= FONT8x8[0][2];
         memcpy(pChar, FONT8x8[c - 0x1F], nBytes);
      break;
     
      case 2:
         nCols = FONT8x16[0][0];
         nRows = FONT8x16[0][1];
         nBytes= FONT8x16[0][2];
         memcpy(pChar, FONT8x16[c - 0x1F], nBytes);
      break;
   }
   // Row address set (command 0x2B)
   PCF8833_write_command(P_PASET);
   PCF8833_write_data(y);
   PCF8833_write_data(y + nRows - 1);
   // Column address set (command 0x2A)
   PCF8833_write_command(P_CASET);
   PCF8833_write_data(x);
   PCF8833_write_data(x + nCols - 1);
   // WRITE MEMORY
   PCF8833_write_command(P_RAMWR);
   // loop on each row, working backwards from the bottom to the top
   for (i=0; i < nRows; i++) //for (i = nRows - 1; i != 255; i--)
   {
      // copy pixel row from font table and then decrement row
      PixelRow = pChar[i]; //PixelRow = *pChar--;
      // loop on each pixel in the row (left to right)
      // Note: we do two pixels each loop
      Mask = 0x80;
      for (j = 0; j < nCols; j += 2)
      {
         // if pixel bit set, use foreground color; else use the background color
         // now get the pixel color for two successive pixels
         if ((PixelRow & Mask) == 0)
            Word0 = bColor;
         else
            Word0 = fColor;
         Mask = Mask >> 1;
         if ((PixelRow & Mask) == 0)
            Word1 = bColor;
         else
            Word1 = fColor;
         Mask = Mask >> 1;
         // use this information to output three data bytes
         PCF8833_write_data((Word0 >> 4) & 0xFF);
         PCF8833_write_data(((Word0 & 0xF) << 4) | ((Word1 >> 8) & 0xF));
         PCF8833_write_data(Word1 & 0xFF);
      }
   }
   // terminate the Write Memory command
   PCF8833_write_command(P_NOP);
}
///////////////////////////////////////////////////////////////////////////////
void PCF8833_LCDPutStr(char *pString, int x, int y, int Size, int16 fColor, int16 bColor)
{
   // loop until null-terminator is seen
   while (*pString != '\0')
   {
      // draw the character
      PCF8833_LCDPutChar(*pString++, x, y, Size, fColor, bColor);
      // advance the y position
      if (Size == SMALL)
         x = x + 6;
      else
         x = x + 8;
      // bail out if y exceeds 131
      if (y > 131) break;
   }
}
///////////////////////////////////////////////////////////////////////////////
void PCF8833_LCDWrite132x132bmp(int8 bmp)
{
   long j; // loop counter
   // Memory access controler (command 0x36)
   //PCF8833_write_command(MADCTL);
   //PCF8833_write_data(0x48); // no mirror Y (temporary to satisfy Olimex bmptoarray utility)
   // Display OFF
   PCF8833_write_command(P_DISPOFF);
   // Column address set (command 0x2A)
   PCF8833_write_command(P_CASET);
   PCF8833_write_data(0);
   PCF8833_write_data(131);
   // Page address set (command 0x2B)
   PCF8833_write_command(P_PASET);
   PCF8833_write_data(0);
   PCF8833_write_data(131);

   // WRITE MEMORY
   PCF8833_write_command(P_RAMWR);
   for(j = 0; j < 25740; j++)
   {
      switch (bmp)
      {
         case 0:
            PCF8833_write_data(bmp0[j]);
         break;
         
         case 1:
            PCF8833_write_data(bmp1[j]);
         break;
         
         case 2:
            PCF8833_write_data(bmp2[j]);
         break;
         
         case 3:
            //PCF8833_write_data(bmp3[j]);
         break;
      }
   }
   
   // Memory access controler (command 0x36)
   //PCF8833_write_command(MADCTL);
   //PCF8833_write_data(0xC8); // restore to (mirror x and y, reverse rgb)
   // Display On
   PCF8833_write_command(P_DISPON);
}
///////////////////////////////////////////////////////////////////////////////
void PCF8833_LCDWriteIcon(int8 icon, int16 color)
{
   int16 i;
   
   switch (icon)
   {
      case 0:
         for (i=0; i<548; i++)
            PCF8833_LCDSetPixel(PixelSet0[i][0], PixelSet0[i][1], color);
      break;
     
      case 1:
         for (i=0; i<688; i++)
            PCF8833_LCDSetPixel(PixelSet1[i][0], PixelSet1[i][1], color);
      break;
     
      case 2:
         for (i=0; i<303; i++)
            PCF8833_LCDSetPixel(PixelSet2[i][0], PixelSet2[i][1], color);
      break;
     
      case 3:
         for (i=0; i<630; i++)
            PCF8833_LCDSetPixel(PixelSet3[i][0], PixelSet3[i][1], color);
      break;
   }
}
///////////////////////////////////////////////////////////////////////////////
#endif 
