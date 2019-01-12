// ********************************************************************************
// File: nokia6100.xc
//
// Platform specific implementation of the Nokia 6100 driver.
// Targeted at the XMOS event driven processor (www.xmos.com)
//
// Contains functions for SPI transfer, hardware resetting the LCD controller
// and delays
//
// Author: Bianco Zandbergen, 28 November 2009
// ********************************************************************************
#include <xs1.h>
#include <xclib.h>
#include <platform.h>
#include "nokia6100.h"

out port lcd_reset = 	N6100_LCD_RESET;	// Hardware reset
out port lcd_sel = 		N6100_LCD_SEL;		// SSEL
out port lcd_clk =		N6100_LCD_CLK;		// SCLK
out port lcd_dat = 		N6100_LCD_DAT;		// MOSI

timer t1; // generic timer shared by XC functions

// *************************************************************************************************
// n6100_lcd_spi_transmit(int type, unsigned char indata)
//
// Transfer 9 bits to the LCD controller using SPI.
// We do not receive anything as the MISO pin of the LCD controller
// is not brought out in the Nokia 6100 LCD.
// Transfer is MSB first, the first bit transferred indicates if the succeeding byte
// is a command or data byte.
//
// SPI settings: 9 bits
//               CPOL=1 (clk idle high)
//               CPHA=1 (data captured at rising edge)
//
// Wave form:
//     ___                                                                          __
//        \                                                                        / 
// ssel    \______________________________________________________________________/ idle high
//    ___       __      __      __      __      __      __      __      __      ______ 
//       \     /  \    /  \    /  \    /  \    /  \    /  \    /  \    /  \    /         
// clk    \___/    \__/    \__/    \__/    \__/    \__/    \__/    \__/    \__/     idle high
//          ______  ______  ______  ______  ______  ______  ______  ______  ______
//         / D/C  \/  7   \/  6   \/  5   \/  4   \/  3   \/  2   \/  1   \/  0   \
// data    \______/\______/\______/\______/\______/\______/\______/\______/\______/ idle dont't care
//
//
// Inputs: 	type = command or data byte (N6100_LCD_CMD or N6100_LCD_DATA)
//          indata = byte to transfer
// 			 
// Returns: nothing
//
// Author: Bianco Zandbergen November 28, 2009
// *************************************************************************************************
#if USE_EXP_SPI == 0
void n6100_lcd_spi_transmit(int type, unsigned int indata)
{
	
	unsigned time;
	int i;
	unsigned int data;
		
	// select lcd
	// clock must be low before selecting lcd
	lcd_clk <: 0;
	lcd_sel <: 0;
	
	// change bit endianes because we have to transfer MSB first.
	// incoming data:
	// xxxxxxxx xxxxxxxx xxxxxxxx 76543210
	// after byterev:
	// 76543210 xxxxxxxx xxxxxxxx xxxxxxxx
	// after bitrev:
	// xxxxxxxx xxxxxxxx xxxxxxxx 01234567
	// after that we shift it 1 bit to the left
	// and push the bit indicating a command or data byte
	// to the front
	data = bitrev(byterev(indata));     
	data <<= 1;
	data |= type;
	
	/* safe current time */
	t1 :> time;
	
	#pragma loop unroll
	for (i = 0; i < 9; i++) {
		lcd_dat <: >> data;					// put data bit on line, shift data 1 to the right
		lcd_clk <: 0;						// clock low
		
		time += N6100_LCD_SPI_HALF_PERIOD;	// wait half period
		t1 when timerafter(time) :> void;
		
		lcd_clk <: 1;						// clock high, data will be read by lcd controller
		
		time += N6100_LCD_SPI_HALF_PERIOD;	// wait half period
		t1 when timerafter(time) :> void;
	}
	
	lcd_clk <: 1;
	lcd_sel <: 1;

	asm("nop;nop;"); // just to make sure ssel is at least 40ns high, in practice this might be removed
}

#else

void n6100_lcd_spi_transmit(int type, unsigned int data)
{
	
	int i;
		
	lcd_clk <: 0;
	lcd_sel <: 0;
	
	data = bitrev(byterev(data));     
	data <<= 1;
	data |= type;
		
	#pragma loop unroll
	for (i = 0; i < 9; i++) {
		
		lcd_dat <: >> data;
		lcd_clk <: 0;	
		lcd_clk <: 1;	
	}
	
	lcd_clk <: 1;
	lcd_sel <: 1;
}
#endif

// *************************************************************************************************
// n6100_lcd_reset(void)
//
// Reset the LCD controller using the reset line.
//
// Inputs: 	none
// 			 
// Returns: nothing
//
// Author: Bianco Zandbergen November 28, 2009
// *************************************************************************************************
void n6100_lcd_reset(void)
{
	lcd_sel <: 1; 		// slave select high
	lcd_clk <: 1; 		// clk high
	
	// Hardware reset
	lcd_reset <: 0;
	n6100_lcd_delayus(1000);
	
	lcd_reset <: 1;
	n6100_lcd_delayus(1000);
}

// *************************************************************************************************
// n6100_lcd_delayus(unsigned int us)
//
// Delay for a given number of microseconds.
//
// Inputs: 	us = number of microseconds to delay
// 			 
// Returns: nothing
//
// Author: Bianco Zandbergen November 28, 2009
// *************************************************************************************************
#define TIME_US 100 // 10ns resolution
void n6100_lcd_delayus(unsigned int us)
{
	unsigned time, i;
	t1 :> time; /* save current time */
	
	for (i=0;i<us;i++) {
		time += TIME_US;
		t1 when timerafter(time) :> void;
	}
}
