#ifndef  S1D15G00_H
#define  S1D15G00_H
///////////////////////////////////////////////////////////////////////////////
#include <string.h>
///////////////////////////////////////////////////////////////////////////////
#define S_DISON  0xAF // Display on
#define S_DISOFF 0xAE // Display off
#define S_DISNOR 0xA6 // Normal display
#define S_DISINV 0xA7 // Inverse display
#define S_COMSCN 0xBB // Common scan direction
#define S_DISCTL 0xCA // Display control
#define S_SLPIN  0x95 // Sleep in
#define S_SLPOUT 0x94 // Sleep out
#define S_PASET  0x75 // Page address set
#define S_CASET  0x15 // Column address set
#define S_DATCTL 0xBC // Data scan direction, etc.
#define S_RGBSET8 0xCE // 256-color position set
#define S_RAMWR  0x5C // Writing to memory
#define S_RAMRD  0x5D // Reading from memory
#define S_PTLIN  0xA8 // Partial display in
#define S_PTLOUT 0xA9 // Partial display out
#define S_RMWIN  0xE0 // Read and modify write
#define S_RMWOUT 0xEE // End
#define S_ASCSET 0xAA // Area scroll set
#define S_SCSTART 0xAB // Scroll start set
#define S_OSCON  0xD1 // Internal oscillation on
#define S_OSCOFF 0xD2 // Internal oscillation off
#define S_PWRCTR 0x20 // Power control
#define S_VOLCTR 0x81 // Electronic volume control
#define S_VOLUP  0xD6 // Increment electronic control by 1
#define S_VOLDOWN 0xD7 // Decrement electronic control by 1
#define S_TMPGRD 0x82 // Temperature gradient set
#define S_EPCTIN 0xCD // Control EEPROM
#define S_EPCOUT 0xCC // Cancel EEPROM control
#define S_EPMWR 0xFC // Write into EEPROM
#define S_EPMRD 0xFD // Read from EEPROM
#define S_EPSRRD1 0x7C // Read register 1
#define S_EPSRRD2 0x7D // Read register 2
#define S_NOP 0x25 // NOP instruction
///////////////////////////////////////////////////////////////////////////////
void S1D15G00_write_data(int8 data)
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
void S1D15G00_write_command(int8 command)
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
void S1D15G00_LCDClearScreen()
{
   long i; // loop counter
   // Row address set (command 0x2B)
   S1D15G00_write_command(S_PASET);
   S1D15G00_write_data(0);
   S1D15G00_write_data(131);
   // Column address set (command 0x2A)
   S1D15G00_write_command(S_CASET);
   S1D15G00_write_data(0);
   S1D15G00_write_data(131);
   // set the display memory to BLACK
   S1D15G00_write_command(S_RAMWR);
   for(i = 0; i < ((131 * 131) / 2); i++)
   {
      S1D15G00_write_data(0x00);
      S1D15G00_write_data(0x00);
      S1D15G00_write_data(0x00);
   }
}
///////////////////////////////////////////////////////////////////////////////
void S1D15G00_LCDWhiteScreen()
{
   long i; // loop counter
   // Row address set (command 0x2B)
   S1D15G00_write_command(S_PASET);
   S1D15G00_write_data(0);
   S1D15G00_write_data(131);
   // Column address set (command 0x2A)
   S1D15G00_write_command(S_CASET);
   S1D15G00_write_data(0);
   S1D15G00_write_data(131);
   // set the display memory to BLACK
   S1D15G00_write_command(S_RAMWR);
   for(i = 0; i < ((131 * 131) / 2); i++)
   {
      S1D15G00_write_data(0xFF);
      S1D15G00_write_data(0xFF);
      S1D15G00_write_data(0xFF);
   }
}
///////////////////////////////////////////////////////////////////////////////
void S1D15G00_init()
{
   NLCD_CS = 1;
   
   // Hardware reset
   NLCD_RESET = 0;
   delay_ms(10);
   NLCD_RESET = 1;
   delay_ms(10);
   // Display control
   S1D15G00_write_command(S_DISCTL);
   S1D15G00_write_data(0x00); // P1: 0x00 = 2 divisions, switching period=8 (default)
   S1D15G00_write_data(0x20); // P2: 0x20 = nlines/4 - 1 = 132/4 - 1 = 32)
   S1D15G00_write_data(0x00); // P3: 0x00 = no inversely highlighted lines
   // COM scan
   S1D15G00_write_command(S_COMSCN);
   S1D15G00_write_data(1); // P1: 0x01 = Scan 1->80, 160<-81
   // Internal oscilator ON
   S1D15G00_write_command(S_OSCON);
   // Sleep out
   S1D15G00_write_command(S_SLPOUT);
   // Power control
   S1D15G00_write_command(S_PWRCTR);
   S1D15G00_write_data(0x0f); // reference voltage regulator on, circuit voltage follower on, BOOST ON
   // Inverse display
   S1D15G00_write_command(S_DISINV);
   // Data control
   S1D15G00_write_command(S_DATCTL);
   S1D15G00_write_data(0x01); // P1: 0x01 = page address inverted, column address normal, address scan in column direction
   S1D15G00_write_data(0x00); // P2: 0x00 = RGB sequence (default value)
   S1D15G00_write_data(0x02); // P3: 0x02 = Grayscale -> 16 (selects 12-bit color, type A)
   // Voltage control (contrast setting)
   S1D15G00_write_command(S_VOLCTR);
   S1D15G00_write_data(38); // P1 = 40 volume value (experiment with this value to get the best contrast)
   S1D15G00_write_data(3); // P2 = 3 resistance ratio (only value that works)
   // allow power supply to stabilize
   delay_ms(50);
   // turn on the display
   S1D15G00_write_command(S_DISON);
   
}
///////////////////////////////////////////////////////////////////////////////
void S1D15G00_LCDSetPixel(int x, int y, int16 color)
{
   int16 temp_color=0;
   // Row address set (command 0x2B)
   S1D15G00_write_command(S_PASET);
   S1D15G00_write_data(y);
   S1D15G00_write_data(y);
   // Column address set (command 0x2A)
   S1D15G00_write_command(S_CASET);
   S1D15G00_write_data(x);
   S1D15G00_write_data(x);
   // Now illuminate the pixel (2nd pixel will be ignored)
   temp_color = color << 4;
   S1D15G00_write_command(S_RAMWR);
   S1D15G00_write_data(make8(temp_color,1));
   S1D15G00_write_data(make8(color,1) | make8(temp_color,0));
   S1D15G00_write_data(make8(color,0));
}
///////////////////////////////////////////////////////////////////////////////
void S1D15G00_LCDPutChar(char c, int x, int y, int8 size, int16 fColor, int16 bColor)
{
   int8 i,j;
   unsigned int8 nCols;
   unsigned int8 nRows;
   unsigned int8 nBytes;
   unsigned char PixelRow;
   unsigned char Mask;
   unsigned int16 Word0;
   unsigned int16 Word1;
   //unsigned char *pFont;
   unsigned char pChar[16];
   //unsigned char *FontTable[] = {(unsigned char *)FONT6x8, (unsigned char *)FONT8x8,
   //(unsigned char *)FONT8x16};
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
   S1D15G00_write_command(S_PASET);
   S1D15G00_write_data(y);
   S1D15G00_write_data(y + nRows - 1);
   // Column address set (command 0x2A)
   S1D15G00_write_command(S_CASET);
   S1D15G00_write_data(x);
   S1D15G00_write_data(x + nCols - 1);
   // WRITE MEMORY
   S1D15G00_write_command(S_RAMWR);
   // loop on each row, working backwards from the bottom to the top
   for (i = nRows - 1; i != 255; i--)
   {
      // copy pixel row from font table and then decrement row
      PixelRow = pChar[i];
      // loop on each pixel in the row (left to right)
      // Note: we do two pixels each loop
      Mask = 0x80;
      for (j = 0; j < nCols; j += 2) {
      // if pixel bit set, use foreground color; else use the background color
      // now get the pixel color for two successive pixels
      if ((PixelRow & Mask) == 0)
         Word0 = bColor;
      else
         Word0 = fColor;
      Mask >>= 1;
      if ((PixelRow & Mask) == 0)
         Word1 = bColor;
      else
         Word1 = fColor;
      Mask >>= 1;
      // use this information to output three data bytes
      S1D15G00_write_data((Word0 >> 4) & 0xFF);
      S1D15G00_write_data(((Word0 & 0xF) << 4) | ((Word1 >> 8) & 0xF));
      S1D15G00_write_data(Word1 & 0xFF);
      }
   }
   // terminate the Write Memory command
   S1D15G00_write_command(S_NOP);
}
///////////////////////////////////////////////////////////////////////////////
void S1D15G00_LCDPutStr(char *pString, int x, int y, int Size, int16 fColor, int16 bColor)
{
   // loop until null-terminator is seen
   while (*pString != '\0')
   {
      // draw the character
      S1D15G00_LCDPutChar(*pString++, x, y, Size, fColor, bColor);
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
void S1D15G00_LCDWrite132x132bmp(int8 bmp)
{
   long j; // loop counter
   // Data control (need to set "normal" page address for Olimex photograph)
   S1D15G00_write_command(S_DATCTL);
   S1D15G00_write_data(0x00); // P1: 0x00 = page address normal, column address normal, address scan in column direction
   S1D15G00_write_data(0x00); // P2: 0x00 = RGB sequence (default value)
   S1D15G00_write_data(0x02); // P3: 0x02 = Grayscale -> 16
   // Display OFF
   S1D15G00_write_command(S_DISOFF);
   // Column address set (command 0x2A)
   S1D15G00_write_command(S_CASET);
   S1D15G00_write_data(0);
   S1D15G00_write_data(131);
   // Page address set (command 0x2B)
   S1D15G00_write_command(S_PASET);
   S1D15G00_write_data(0);
   S1D15G00_write_data(131);
   // WRITE MEMORY
   S1D15G00_write_command(S_RAMWR);
   for(j = 0; j < 25740; j++)
   {
      switch (bmp)
      {
         case 0:
            S1D15G00_write_data(bmp0[j]);
         break;
         
         case 1:
            S1D15G00_write_data(bmp1[j]);
         break;
         
         case 2:
            S1D15G00_write_data(bmp2[j]);
         break;
         
         case 3:
            //S1D15G00_write_data(bmp3[j]);
         break;
      }
   }
   // Data control (return to "inverted" page address)
   S1D15G00_write_command(S_DATCTL);
   S1D15G00_write_data(0x01); // P1: 0x01 = page address inverted, column address normal, address scan in column direction
   S1D15G00_write_data(0x00); // P2: 0x00 = RGB sequence (default value)
   S1D15G00_write_data(0x02); // P3: 0x02 = Grayscale -> 16
   // Display On
   S1D15G00_write_command(S_DISON);
}
///////////////////////////////////////////////////////////////////////////////
void S1D15G00_LCDWriteIcon(int8 icon, int16 color)
{
   int16 i;
   
   switch (icon)
   {
      case 0:
         for (i=0; i<548; i++)
            S1D15G00_LCDSetPixel(PixelSet0[i][0], PixelSet0[i][1], color);
      break;
     
      case 1:
         for (i=0; i<688; i++)
            S1D15G00_LCDSetPixel(PixelSet1[i][0], PixelSet1[i][1], color);
      break;
     
      case 2:
         for (i=0; i<303; i++)
            S1D15G00_LCDSetPixel(PixelSet2[i][0], PixelSet2[i][1], color);
      break;
     
      case 3:
         for (i=0; i<630; i++)
            S1D15G00_LCDSetPixel(PixelSet3[i][0], PixelSet3[i][1], color);
      break;
   }
}
///////////////////////////////////////////////////////////////////////////////
#endif 