//MIT License
//
//Copyright (c) 2010 Falko Thomale
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//THE SOFTWARE.

#include "lcd.h"
#include "defines.h"
#include "main.h"
#include "font_4x6.h"
#include "lcd_init_sequence.h"
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>

unsigned int fgColor = 0x000F;

void initLCD() {
	unsigned int i;

	PORTC &= ~(1 << P_LCD_RESET); // perform an LCD reset
	_delay_ms(10);
	PORTC |= (1 << P_LCD_RESET);
	_delay_ms(10);

	PORTC |= (1 << P_LCD_CD); // set LCD to command mode
	PORTC &= ~(1 << P_LCD_CS); // activate LCD CS

	for (i = 0; i < sizeof(initData); i++) {
		spi(pgm_read_byte(&initData[i])); // send initialization data
	}
	_delay_ms(1);
	PORTC |= (1 << P_LCD_CS); // deactivate LCD CS

	_delay_ms(1);
	PORTC &= ~(1 << P_LCD_CS); // activate LCD CS

	spi(0xF0);
	spi(0x81);
	spi(0xF4);
	spi(0xB3);
	spi(0xA0);

	spi(0xF0);
	spi(0x06);
	spi(0x10);
	spi(0x20);
	spi(0x30);
	spi(0xF5);
	spi(0x0F);
	spi(0x1C);
	spi(0x2F);
	spi(0x34);
	PORTC |= (1 << P_LCD_CS); // deactivate LCD CS
	PORTC &= ~(1 << P_LCD_CD); // set LCD to data mode
}

void setWindow(unsigned char xstart, unsigned char ystart, unsigned char xend,
		unsigned char yend) {
	xstart <<= 1;
	xstart += 6;
	xend <<= 1;
	xend += 7;

	PORTC |= (1 << P_LCD_CD);
	PORTC &= ~(1 << P_LCD_CS);

	spi(0xF0);
	spi(0x00 | (xstart & 0x0F));
	spi(0x10 | (xstart >> 4));
	spi(0x20 | (ystart & 0x0F));
	spi(0x30 | (ystart >> 4));
	spi(0xF5);
	spi(0x00 | (xend & 0x0F));
	spi(0x10 | (xend >> 4));
	spi(0x20 | (yend & 0x0F));
	spi(0x30 | (yend >> 4));

	PORTC |= (1 << P_LCD_CS);
	PORTC &= ~(1 << P_LCD_CD);
}

void setContrast(unsigned char contrast) {
	PORTC |= (1 << P_LCD_CD);
	PORTC &= ~(1 << P_LCD_CS);

	spi(0xF4);
	spi(0xB0 | (contrast >> 4));
	spi(0xA0 | (contrast & 0x0F));

	PORTC |= (1 << P_LCD_CS);
}

void clearLCD() {
	unsigned int i;
	setWindow(0, 0, 100, 79);
	PORTC &= ~((1 << P_LCD_CS) | (1 << P_LCD_CD));
	for (i = 0; i < 8080; i++) {
		spi(0xFF);
		spi(0xFF);
	}
	PORTC |= (1 << P_LCD_CS);
}

void setColor(unsigned int fc) {
	fgColor = fc;
}

void fillRect(unsigned char xstart, unsigned char ystart, unsigned char width,
		unsigned char height) {
	unsigned char i, j;
	setWindow(xstart, ystart, xstart + width - 1, ystart + height - 1);
	PORTC &= ~((1 << P_LCD_CS) | (1 << P_LCD_CD));
	for (i = 0; i < height; ++i) {
		for (j = 0; j < width; ++j) {
			spi(fgColor >> 8);
			spi(fgColor & 0xFF);
		}
	}
	PORTC |= (1 << P_LCD_CS);
}

void drawRect(unsigned char xstart, unsigned char ystart, unsigned char width,
		unsigned char height) {
	unsigned char i;

	//horizontal Lines
	setWindow(xstart, ystart, xstart + width - 1, ystart);
	PORTC &= ~((1 << P_LCD_CS) | (1 << P_LCD_CD));
	for (i = 0; i < width; ++i) {
		spi(fgColor >> 8);
		spi(fgColor & 0xFF);
	}
	setWindow(xstart, ystart + height - 1, xstart + width - 1, ystart + height
			- 1);
	PORTC &= ~((1 << P_LCD_CS) | (1 << P_LCD_CD));
	for (i = 0; i < width; ++i) {
		spi(fgColor >> 8);
		spi(fgColor & 0xFF);
	}
	//vertical Lines
	setWindow(xstart, ystart, xstart, ystart + height - 1);
	PORTC &= ~((1 << P_LCD_CS) | (1 << P_LCD_CD));
	for (i = 0; i < height; ++i) {
		spi(fgColor >> 8);
		spi(fgColor & 0xFF);
	}
	setWindow(xstart + width - 1, ystart, xstart + width - 1, ystart + height
			- 1);
	PORTC &= ~((1 << P_LCD_CS) | (1 << P_LCD_CD));
	for (i = 0; i < height; ++i) {
		spi(fgColor >> 8);
		spi(fgColor & 0xFF);
	}
	PORTC |= (1 << P_LCD_CS);
}

void setPixel(unsigned char x, unsigned char y) {
	setWindow(x, y, x, y);
	PORTC &= ~((1 << P_LCD_CS) | (1 << P_LCD_CD));
	spi(fgColor >> 8);
	spi(fgColor & 0xFF);
	PORTC |= (1 << P_LCD_CS);
}

void drawChar(unsigned char x, unsigned char y, unsigned char c) {
	unsigned char i, j, w;
	if (0x20 < c && c < 0x80)
		for (i = 0; i < 3; i++) {
			w = pgm_read_byte(&font[c - 0x21][i]);
			for (j = 0; j < 4; j++) {
				if (w & 1)
					setPixel(x + 3 - j, y + i * 2 + 1);
				w = w >> 1;
			}
			for (j = 0; j < 4; j++) {
				if (w & 1)
					setPixel(x + 3 - j, y + i * 2);
				w = w >> 1;
			}
		}
}

void drawString(unsigned char x, unsigned char y, char* c) {
	unsigned char i;
	i = 0;
	while (*(c + i) != '\0') {
		drawChar(x + i * 4, y, *(c + i));
		++i;
	}
}
