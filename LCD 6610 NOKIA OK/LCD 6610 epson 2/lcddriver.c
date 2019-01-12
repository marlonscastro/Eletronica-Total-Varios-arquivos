#include "18F2620.h"
#fuses NOWDT,INTRC_IO,NOLVP,NOMCLR,NOIESO,NOSTVREN,NOWRTD,NOEBTR,NOEBTRB,NOWRTC,NOWRTB,NOFCMEN
#fuses NOPUT,NOPROTECT,NODEBUG,NOBROWNOUT,NOLVP,NOCPD,NOWRT,NOXINST,NOPBADEN,NOLPT1OSC                 
#use delay(clock=4000000)
#use fast_io(c) 

#include "imagedata.c"
#include "bham.c"
#include "fruit.c"

#define LCD_RESET PIN_C0 //spi pins
#define LCD_CS PIN_C1
#define SPI_CLK PIN_C3
#define SPI_DO PIN_C5

#define DOWN PIN_B0 //input control pins
#define RIGHT PIN_B1
#define LEFT PIN_B2
#define UP PIN_B3

#define ACNE PIN_B4
#define SKIN PIN_B5
#define NOSE PIN_B6
#define BUZZ PIN_B7

// Epson S1D15G10 Command Set

#define DISON       0xaf
#define DISOFF      0xae
#define DISNOR      0xa6
#define DISINV      0xa7
#define SLPIN       0x95
#define SLPOUT      0x94
#define COMSCN      0xbb
#define DISCTL      0xca
#define PASET       0x75
#define CASET       0x15
#define DATCTL      0xbc
#define RGBSET8     0xce
#define RAMWR       0x5c
#define RAMRD       0x5d
#define PTLIN       0xa8
#define PTLOUT      0xa9
#define RMWIN       0xe0
#define RMWOUT      0xee
#define ASCSET      0xaa
#define SCSTART     0xab
#define OSCON       0xd1
#define OSCOFF      0xd2
#define PWRCTR      0x20
#define VOLCTR      0x81
#define VOLUP       0xd6
#define VOLDOWN     0xd7
#define TMPGRD      0x82
#define EPCTIN      0xcd
#define EPCOUT      0xcc
#define EPMWR       0xfc
#define EPMRD       0xfd
#define EPSRRD1     0x7c
#define EPSRRD2     0x7d
#define NOP         0x25

#define ENDPAGE     131
#define ENDCOL      131

// Booleans
#define NOFILL 0
#define FILL 1

// 12-bit color definitions
#define WHITE 0xFFF
#define BLACK 0x000
#define RED 0xF00
#define GREEN 0x0F0
#define BLUE 0x00F
#define CYAN 0x0FF
#define MAGENTA 0xF0F
#define YELLOW 0xFF0
#define BROWN 0xB22
#define ORANGE 0xFA0
#define PINK 0xF6A

void pulse(void)// send clock pulse
{
 //   delay_us(1);         
	output_high (SPI_CLK);
//   	delay_us(1);        
   	output_low (SPI_CLK);
}

void spi_command(int SPIData)
{
   	output_low(LCD_CS);      // enable chip

   	output_low (SPI_DO);     // output low on data out (9th bit low = command)
	pulse();

	// clock out the 8 data bits
	//
	output_low (SPI_DO);
	if (SPIData & 0x80) output_high (SPI_DO);
	pulse();

	output_low (SPI_DO);
	if (SPIData & 0x40) output_high (SPI_DO);
	pulse();

	output_low (SPI_DO);
	if (SPIData & 0x20) output_high (SPI_DO);
	pulse();

	output_low (SPI_DO);
	if (SPIData & 0x10) output_high (SPI_DO);
	pulse();

	output_low (SPI_DO);
	if (SPIData & 0x08) output_high (SPI_DO);
	pulse();

	output_low (SPI_DO);
	if (SPIData & 0x04) output_high (SPI_DO);
	pulse();

	output_low (SPI_DO);
	if (SPIData & 0x02) output_high (SPI_DO);
	pulse();

	output_low (SPI_DO);
	if (SPIData & 0x01) output_high (SPI_DO);
	pulse();

//   	delay_us(1);      
   	output_high(LCD_CS);     // disable
}

void spi_data(int SPIData)
{
   	output_low(LCD_CS);      // enable chip

   	output_high (SPI_DO);    // output high on data out (9th bit high = data)
    pulse();

	// clock out the 8 data bits
	//	
	output_low (SPI_DO);
	if (SPIData & 0x80) output_high (SPI_DO);
	pulse();

	output_low (SPI_DO);
	if (SPIData & 0x40) output_high (SPI_DO);
	pulse();

	output_low (SPI_DO);
	if (SPIData & 0x20) output_high (SPI_DO);
	pulse();

	output_low (SPI_DO);
	if (SPIData & 0x10) output_high (SPI_DO);
	pulse();

	output_low (SPI_DO);
	if (SPIData & 0x08) output_high (SPI_DO);
	pulse();

	output_low (SPI_DO);
	if (SPIData & 0x04) output_high (SPI_DO);
	pulse();

	output_low (SPI_DO);
	if (SPIData & 0x02) output_high (SPI_DO);
	pulse();

	output_low (SPI_DO);
	if (SPIData & 0x01) output_high (SPI_DO);
	pulse();

//   	delay_us(1);      
   	output_high(LCD_CS);     // disable
}

void LCDClearScreen(void) 
{
	long z; // loop counter
	// Row address set (command 0x2B)
	spi_command(PASET);
	spi_data(0);
	spi_data(131);
	// Column address set (command 0x2A)
	spi_command(CASET);
	spi_data(0);
	spi_data(131);
	// set the display memory color
	spi_command(RAMWR);
	for(z = 0; z < ((131 * 131) / 2); z++) 
		{
		spi_data((GREEN >> 4) & 0xFF);
		spi_data(((GREEN & 0xF) << 4) | ((GREEN >> 8) & 0xF));
		spi_data(GREEN & 0xFF);
		}
}

void LCDWrite130x130bmp(void) 
{
	long j; // loop counter
	// Data control (need to set "normal" page address for Olimex photograph)
  	spi_command(DATCTL);
    spi_data(0x00); // P1: 0x00 = page address normal, column address normal, address scan in column direction
    spi_data(0x00); // P2: 0x00 = RGB sequence (default value)
    spi_data(0x02); // P3: 0x02 = Grayscale -> 16
	// Display OFF
  	spi_command(DISOFF);
	// Column address set (command 0x2A)
  	spi_command(CASET);
    spi_data(0);
    spi_data(131);
	// Page address set (command 0x2B)
  	spi_command(PASET);
    spi_data(0);
    spi_data(131);
	// WRITE MEMORY
  	spi_command(RAMWR);

	for(j = 0; j < 25740; j++) 
		{
    	spi_data(bham[j]); 
		}
	// Data control (return to "inverted" page address)
  	spi_command(DATCTL);
    spi_data(0x01); // P1: 0x01 = page address inverted, column address normal, address scan in column direction
    spi_data(0x00); // P2: 0x00 = RGB sequence (default value)
    spi_data(0x02); // P3: 0x02 = Grayscale -> 16
	// Display On
	spi_command(DISON);
}
void displayfruit(void) 
{
	long j; // loop counter
	// Data control (need to set "normal" page address for Olimex photograph)
  	spi_command(DATCTL);
    spi_data(0x00); // P1: 0x00 = page address normal, column address normal, address scan in column direction
    spi_data(0x00); // P2: 0x00 = RGB sequence (default value)
    spi_data(0x02); // P3: 0x02 = Grayscale -> 16
	// Display OFF
  	spi_command(DISOFF);
	// Column address set (command 0x2A)
  	spi_command(CASET);
    spi_data(0);
    spi_data(131);
	// Page address set (command 0x2B)
  	spi_command(PASET);
    spi_data(0);
    spi_data(131);
	// WRITE MEMORY
  	spi_command(RAMWR);

	for(j = 0; j < 25740; j++) 
		{
    	spi_data(fruit[j]); 
		}
	// Data control (return to "inverted" page address)
  	spi_command(DATCTL);
    spi_data(0x01); // P1: 0x01 = page address inverted, column address normal, address scan in column direction
    spi_data(0x00); // P2: 0x00 = RGB sequence (default value)
    spi_data(0x02); // P3: 0x02 = Grayscale -> 16
	// Display On
	spi_command(DISON);
}

void init(void)// send clock pulse
{
	setup_adc_ports(NO_ANALOGS);
   	setup_adc(ADC_OFF);
	setup_comparator(NC_NC_NC_NC);
   	setup_timer_0(RTCC_INTERNAL|RTCC_DIV_4);
   	setup_timer_1(T1_DISABLED);
   	setup_timer_2(T2_DISABLED, 0, 1);
   	set_tris_b(0b00001111);   // set button input rb0,1,2,3, output rb4,5,6,7
   	set_tris_c(0b00010000);   // all outputs less spi SDI

   // reset display
	delay_ms(1);
   	output_low (SPI_CLK);
   	output_low (SPI_DO);
   	output_high (LCD_CS);
   	output_low (LCD_RESET);
//	delay_ms(100);
   	output_high (LCD_RESET);
	delay_ms(100);
   //init'd, now drop CS to send commands/data and raise when finished

    spi_command(DISCTL);  // display control
    spi_data(0x00);      // 
    spi_data(0x20);      // 32 = (128/4)-1 (round up) number of display lines for scanning
    spi_data(0x00);      // 


    spi_command(COMSCN);  // common scanning direction
    spi_data(0x01);

    spi_command(OSCON);  // internal oscialltor ON

    spi_command(SLPOUT);  // sleep out
	delay_ms(2);

    spi_command(PWRCTR);  // power ctrl
    spi_data(0x0F);      //everything on, no external reference resistors

    spi_command(DISINV);  // invert display mode

    spi_command(DATCTL);  // data control
    spi_data(0x01);   // page scan direction
    spi_data(0x00);   // normal RGB arrangement
    spi_data(0x02);   // 8-bit 16-grayscale

    spi_command(VOLCTR);  // electronic volume, this is the contrast/brightness
    spi_data(0x23);   // volume (contrast) setting - fine tuning
    spi_data(0x03);   // internal resistor ratio - coarse adjustment

	LCDWrite130x130bmp(); 
	delay_ms(2000);

  	spi_command(DISON);   // display on

}

void LCDSetPixel(int x, int y, int16 color) 
{
	// Row address set (command 0x2B)
	spi_command(PASET);
	spi_data(x);
	spi_data(x);
	// Column address set (command 0x2A)
	spi_command(CASET);
	spi_data(y);
	spi_data(y);
	// Now illuminate the pixel (2nd pixel will be ignored)
	spi_command(RAMWR);
	spi_data((color >> 4) & 0xFF);
	spi_data(((color & 0xF) << 4) | ((color >> 8) & 0xF));
	spi_data(color & 0xFF);
}

void LCDSetLine(int x0, int y0, int x1, int y1, int16 color) 
{
	signed int16 dy, dx, fraction;
	int stepx, stepy;

	 dy = y1 - y0;
	 dx = x1 - x0;
//	 stepx, stepy;

	if (dy < 0) 
	{
		dy = -dy; stepy = -1; 
	} 
	else 
	{ 
		stepy = 1; 
	}
	if (dx < 0) 
	{
		dx = -dx; stepx = -1; 
	} 
	else 
	{ 
		stepx = 1; 
	}
	dy <<= 1; // dy is now 2*dy
	dx <<= 1; // dx is now 2*dx
	LCDSetPixel(x0, y0, color);
	if (dx > dy) 
	{
		fraction = dy - (dx >> 1); // same as 2*dy - dx
		while (x0 != x1) 
		{
			if (fraction >= 0) 
			{
				y0 += stepy;
				fraction -= dx; // same as fraction -= 2*dx
			}
			x0 += stepx;
			fraction += dy; // same as fraction -= 2*dy
			LCDSetPixel(x0, y0, color);
		}
	} 
	else 
	{
		fraction = dx - (dy >> 1);
		while (y0 != y1) 
		{
			if (fraction >= 0) 
			{
				x0 += stepx;
				fraction -= dy;
			}
			y0 += stepy;
			fraction += dx;
			LCDSetPixel(x0, y0, color);
		}
	}
}


void LCDSetRect(int x00, int y00, int x11, int y11, int16 color)
{
	int16 i,xmin,xmax,ymin,ymax;

	// specify the controller drawing box according to those limits
	xmin = (x00 <= x11) ? x00 : x11;
	xmax = (x00 > x11) ? x00 : x11;
	ymin = (y00 <= y11) ? y00 : y11;
	ymax = (y00 > y11) ? y00 : y11;

	// Row address set (command 0x2B)
	spi_command(PASET);
	spi_data(xmin);
	spi_data(xmax);
	// Column address set (command 0x2A)
	spi_command(CASET);
	spi_data(ymin);
	spi_data(ymax);
	// WRITE MEMORY
	spi_command(RAMWR);
	// loop on total number of pixels / 2
	for (i = 0; i < ((((xmax - xmin + 1) * (ymax - ymin + 1))/2 ) +130 ); i++) 
	{
		// use the color value to output three data bytes covering two pixels
		spi_data((color >> 4) & 0xFF);
		spi_data(((color & 0xF) << 4) | ((color >> 8) & 0xF));
		spi_data(color & 0xFF);
	}
}

void LCDPutChar(char c, int x, int y, int16 fColor, int16 bColor) 
{
	signed int i,j;
	int32 nBytes;
	int PixelRow;
	int Mask;
	int16 Word0;
	int16 Word1;
	int32 char_row;

	nBytes = 0x08; //8 bytes per character
	// get pointer to the last byte of the desired character
	char_row = ((nBytes * (c - 0x1F)) + nBytes - 1)/8;
	// Row address set (command 0x2B)
	spi_command(PASET);
	spi_data(x);
	spi_data(x + 7);
	// Column address set (command 0x2A)
	spi_command(CASET);
	spi_data(y);
	spi_data(y + 5);
	// WRITE MEMORY
	spi_command(RAMWR);
	// loop on each row, working backwards from the bottom to the top
	for (i = 7; i >= 0; i--) 
	{
		// copy pixel row from font table and then decrement row
		PixelRow = Font[char_row][i];
		// loop on each pixel in the row (left to right)
		// Note: we do two pixels each loop
		Mask = 0x80;
		for (j = 0; j < 6; j += 2) 
		{
			// if pixel bit set, use foreground color; else use the background color
			// now get the pixel color for two successive pixels
			if ((PixelRow & Mask) == 0)
				Word0 = bColor;
			else
				Word0 = fColor;

			Mask = Mask >> 1;	//shift bit right

			if ((PixelRow & Mask) == 0)
				Word1 = bColor;
			else
				Word1 = fColor;

			Mask = Mask >> 1;	//shift bit right

			// use this information to output three data bytes
			spi_data((Word0 >> 4) & 0xFF);
			spi_data(((Word0 & 0xF) << 4) | ((Word1 >> 8) & 0xF));
			spi_data(Word1 & 0xFF);
		}
	}
	// terminate the Write Memory command
	spi_command(NOP);
}

void LCDPutStr(char *pstring, int x, int y, int16 fColor, int16 bColor) 
{
	char letter;
	// loop until null-terminator is seen
	while (*pstring != 0) //check for null terminator
	{
		letter=*pstring;
		// draw the character
		LCDPutChar(letter, x, y, fColor, bColor);
		// advance the y position
		y = y + 6;
		// bail out if y exceeds 131
		if (y > 131) break;
		*pstring++;
	}
}

