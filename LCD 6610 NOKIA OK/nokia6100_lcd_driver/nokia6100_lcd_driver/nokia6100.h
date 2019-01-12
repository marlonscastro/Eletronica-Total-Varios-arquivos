// *****************************************************************************
// File: nokia6100.h
//
// Main header file for Nokia 6100 display with NXP PCF8833 LCD controller
// for use with XMOS processors (www.xmos.com).
//
// Note: Nokia 6100 LCD screens can be equipped with two different controllers
//       (NXP PCF8833 and Epson S1D15G10) which are not fully compatible with
//       each other. A possible way to distinguish them is to look at the color
//       of the flexible PCB. Displays with the NXP controller likely have a
//       brown PCB and displays with an Epson controller a green PCB.
//
// API Functions:
//       n6100_lcd_setpixel(int x, int y, int color)
//       n6100_lcd_setline(int x0, int y0, int x1, int y1, int color)
//       n6100_lcd_setrect(int x0, int y0, int x1, int y1, unsigned char fill, int color)
//       n6100_lcd_setcircle(int x0, int y0, int radius, int color)
//       n6100_lcd_putchar(char c, int x, int y, int size, int fColor, int bColor)
//       n6100_lcd_putstr(char *pString, int x, int y, int Size, int fColor, int bColor)
//       n6100_lcd_drawbitmap(int x, int y, int w, int h, unsigned char *p)
//      
//       For more detailed information see the comments above each
//       function in pcf8833.c. The last two functions cannot be called
//       from XC because they use pointers and at the moment XC does not
//       support pointers.
//
// Author: Bianco Zandbergen, 28 November 2009
// *****************************************************************************
#ifndef NOKIA6100_H_
#define NOKIA6100_H_

// *****************************************************************************
// Connector pinout
//                      ____
//               pin 1 |    | pin 10
//               pin 5 |    | pin 6
//   __________________|    |__               
//  |                          |    pin 1: VCC (3.3V)
//  |                          |    pin 2: #RESET      <--- Port N6100_LCD_RESET
//  |                          |    pin 3: DATA        <--- Port N6100_LCD_DAT
//  |                          |    pin 4: CLK         <--- Port N6100_LCD_CLK
//  |                          |    pin 5: #CS         <--- Port N6100_LCD_SEL
//  |                          |    pin 6: VCC (3.3V)
//  |                          |    pin 7: N.C.
//  |                          |    pin 8: GND
//  |                          |    pin 9: Backlight -
//  |                          |    pin 10: Backlight + (7-8V)
//  |__________________________|
//
// *****************************************************************************

// *****************************************************************************
// Configuration
// *****************************************************************************

// Ports connected to the LCD (all 1-bit ports)
#define N6100_LCD_RESET		XS1_PORT_1A // LCD reset line
#define N6100_LCD_SEL		XS1_PORT_1B // LCD chip select
#define N6100_LCD_CLK		XS1_PORT_1C // sclk
#define N6100_LCD_DAT		XS1_PORT_1D // mosi

// SPI settings
#define N6100_LCD_SPI_SPEED			1000000	// SPI speed in Hertz
#define N6100_LCD_SPI_PERIOD 		(100000000/N6100_LCD_SPI_SPEED) // period in 10ns granularity		
#define N6100_LCD_SPI_HALF_PERIOD 	(N6100_LCD_SPI_PERIOD/2) // half of a period in 10ns granularity			
#define USE_EXP_SPI					0 // a faster SPI routine which exceeds PCF8833 specs

// Memory data access control
// 0 = false/disable 1 = true/enable
#define N6100_LCD_INVERT_RGB	0	// invert RGB -> BGR
#define N6100_LCD_LINE_BOTTOP	0	// Lines from bottom to top
#define N6100_LCD_RAM_WR_VER	0	// Write RAM in vertical (y) direction
#define N6100_LCD_MIRROR_X		0	// Mirror X axis
#define N6100_LCD_MIRROR_Y		1	// Mirror Y axis

// Disable parts of the driver to decrease the firmware size
// Please note that functions might be dependable of eachother and
// disabling one function might result in the malfunction of an other function
// 1 = enable 0 = disable
#define N6100_LCD_USE_SETPIXEL			1 // include n6100_lcd_setpixel(int x, int y, int color) function
#define N6100_LCD_USE_SETXY				1 // include n6100_lcd_setxy(int x, int y) function
#define N6100_LCD_USE_SETLINE			1 // include n6100_lcd_setline(int x0, int y0, int x1, int y1, int color) function
#define N6100_LCD_USE_SETRECT			1 // include n6100_lcd_setrect(int x0, int y0, int x1, int y1, unsigned char fill, int color) function
#define N6100_LCD_USE_SETCIRCLE			1 // include n6100_lcd_setcircle(int x0, int y0, int radius, int color) function
#define N6100_LCD_USE_FONTS				1 // use putchar or putstr, setting this to 0 will exclude all font related parts and overrule the individual options
#define N6100_LCD_USE_PUTCHAR			1 // include 6100_lcd_putchar(char c, int x, int y, int size, int fColor, int bColor) function
#define N6100_LCD_USE_PUTSTR			1 // include n6100_lcd_putstr(char *pString, int x, int y, int Size, int fColor, int bColor) function
#define N6100_LCD_USE_FONT_SMALL		1 // include SMALL font table
#define N6100_LCD_USE_FONT_MEDIUM		1 // include MEDIUM font table
#define N6100_LCD_USE_FONT_LARGE		1 // include LARGE font table
#define N6100_LCD_USE_DRAWBITMAP		1 // include n6100_lcd_drawbitmap(int x, int y, int w, int h, unsigned char *p) function

// End of configuration

// *****************************************************************************
// Function prototypes
// *****************************************************************************
void n6100_lcd_spi_transmit(int type, unsigned int indata);
void n6100_lcd_init(void);
void n6100_lcd_reset(void);
void n6100_lcd_delayus(unsigned int us);

#if N6100_LCD_USE_SETPIXEL == 1
void n6100_lcd_setpixel(int x, int y, int color);
#endif

#if N6100_LCD_USE_SETXY == 1
void n6100_lcd_setxy(int x, int y);
#endif 

#if N6100_LCD_USE_SETLINE == 1
void n6100_lcd_setline(int x0, int y0, int x1, int y1, int color);
#endif

#if N6100_LCD_USE_SETRECT == 1
void n6100_lcd_setrect(int x0, int y0, int x1, int y1, unsigned char fill, int color);
#endif

#if N6100_LCD_USE_SETCIRCLE == 1
void n6100_lcd_setcircle(int x0, int y0, int radius, int color);
#endif

#if N6100_LCD_USE_PUTCHAR == 1 && N6100_LCD_USE_FONTS == 1
void n6100_lcd_putchar(char c, int x, int y, int size, int fColor, int bColor);
#endif

// XC can't handle pointers at the moment (november 2009)
// these functions cannot be called from XC!
#if __XC__ != 1

#if N6100_LCD_USE_PUTSTR == 1 && N6100_LCD_USE_FONTS == 1
void n6100_lcd_putstr(char *pString, int x, int y, int Size, int fColor, int bColor);
#endif

#if N6100_LCD_USE_DRAWBITMAP == 1
void n6100_lcd_drawbitmap(int x, int y, int w, int h, unsigned char *p);
#endif

#endif

// *****************************************************************************
// Send command and send data macro's
// *****************************************************************************
#define N6100_LCD_CMD				0
#define N6100_LCD_DATA				1
#define n6100_lcd_write_cmd(arg)	n6100_lcd_spi_transmit(N6100_LCD_CMD, arg)
#define n6100_lcd_write_data(arg)	n6100_lcd_spi_transmit(N6100_LCD_DATA, arg)

// *****************************************************************************
// NXP PCF8833 LCD Controller command codes and register options
// *****************************************************************************

// command codes
#define NOP 0x00 // nop
#define SWRESET 0x01 // software reset
#define BSTROFF 0x02 // booster voltage OFF
#define BSTRON 0x03 // booster voltage ON
#define RDDIDIF 0x04 // read display identification
#define RDDST 0x09 // read display status
#define SLEEPIN 0x10 // sleep in
#define SLEEPOUT 0x11 // sleep out
#define PTLON 0x12 // partial display mode
#define NORON 0x13 // display normal mode
#define INVOFF 0x20 // inversion OFF
#define INVON 0x21 // inversion ON
#define DALO 0x22 // all pixel OFF
#define DAL 0x23 // all pixel ON
#define SETCON 0x25 // write contrast
#define DISPOFF 0x28 // display OFF
#define DISPON 0x29 // display ON
#define CASET 0x2A // column address set
#define PASET 0x2B // page address set
#define RAMWR 0x2C // memory write
#define RGBSET 0x2D // colour set
#define PTLAR 0x30 // partial area
#define VSCRDEF 0x33 // vertical scrolling definition
#define TEOFF 0x34 // test mode
#define TEON 0x35 // test mode
#define MADCTL 0x36 // memory access control
#define SEP 0x37 // vertical scrolling start address
#define IDMOFF 0x38 // idle mode OFF
#define IDMON 0x39 // idle mode ON
#define COLMOD 0x3A // interface pixel format
#define SETVOP 0xB0 // set Vop
#define BRS 0xB4 // bottom row swap
#define TRS 0xB6 // top row swap
#define DISCTR 0xB9 // display control
#define DOR 0xBA // data order
#define TCDFE 0xBD // enable/disable DF temperature compensation
#define TCVOPE 0xBF // enable/disable Vop temp comp
#define EC 0xC0 // internal or external oscillator
#define SETMUL 0xC2 // set multiplication factor
#define TCVOPAB 0xC3 // set TCVOP slopes A and B
#define TCVOPCD 0xC4 // set TCVOP slopes c and d
#define TCDF 0xC5 // set divider frequency
#define DF8COLOR 0xC6 // set divider frequency 8-color mode
#define SETBS 0xC7 // set bias system
#define RDTEMP 0xC8 // temperature read back
#define NLI 0xC9 // n-line inversion
#define RDID1 0xDA // read ID1
#define RDID2 0xDB // read ID2
#define RDID3 0xDC // read ID3

// Memory data access control (MADCTL) register options
#define RGB_BIT				(1<<3)
#define LINE_ADDR_ORDER_BIT	(1<<4)
#define RAM_WR_V_BIT		(1<<5)
#define MIRROR_X_BIT		(1<<6)
#define MIRROR_Y_BIT		(1<<7)

// pixel interface formats (COLMOD)
#define PIXEL_8BIT			((1<<1))
#define PIXEL_12BIT			((1<<0)|(1<<1))
#define PIXEL_16BIT			((1<<0)|(1<<2))

// contrast
#define MAXCONTRAST			63

// *****************************************************************************
// Macro's used in function arguments
// *****************************************************************************

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

// Font sizes
#define SMALL 0
#define MEDIUM 1
#define LARGE 2

#endif /*NOKIA6100_H_*/
