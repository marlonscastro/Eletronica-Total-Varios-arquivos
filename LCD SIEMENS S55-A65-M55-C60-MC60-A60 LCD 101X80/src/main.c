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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "defines.h"
#include "lcd.h"

/* define CPU frequency in MHz here if not defined in Makefile */
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

volatile unsigned char centiSecond;
volatile unsigned char second;
volatile unsigned char minute;
volatile unsigned char hour;

void init() {
	DDRB = (1 << P_DATA) | (1 << P_CLK); //P_DATA, P_CLK as output
	DDRC = (1 << P_LCD_CS) | (1 << P_LCD_RESET) | (1 << P_LCD_CD); //P_LCD_CS, P_LCD_RESET, P_LCD_CD as output
	PORTC = (1 << P_LCD_CS);

	//initSPI
	DDRB = (1 << P_DATA) | (1 << P_CLK); //P_DATA, P_CLK (SCK,MOSI) as output
	PORTB = (1 << P_CLK); // SCK und PB0 high (ist mit SS am Slave verbunden)
	SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR0); //Aktivierung des SPI, Master, Taktrate fck/16
	sei();

	// Timer 1 konfigurieren
	TCCR1B = (1 << WGM12) && (1 << CS11) && (1 << CS10); // Prescaler 64
	// Compare Interrupt erlauben
	TIMSK |= (1 << OCIE1A);
	OCR1A = 1250;

	// Global Interrupts aktivieren
	sei();
}

void spi(unsigned char data) {
	PORTB &= ~_BV(PB0); //SS am Slave Low --> Beginn der Übertragung
	SPDR = data; //Schreiben der Daten
	while (!(SPSR & (1 << SPIF)))
		;
	PORTB |= _BV(PB0); //SS High --> Ende der Übertragung
}

ISR (TIMER1_COMPA_vect)
{
	if (++centiSecond == 100) {
		centiSecond = 0;
		if (++second == 60) {
			if (++minute == 60) {
				hour++;
				second = 0;
			}
			second = 0;
		}
	}
}

#define fieldWidth 30
#define fieldHeight 19
#define fieldLength 72
unsigned char golField[fieldLength];
unsigned char golField2[fieldLength];
const signed char neighbours[8] = { -fieldWidth - 1, -fieldWidth, -fieldWidth
		+ 1, -1, 1, fieldWidth - 1, fieldWidth, fieldWidth + 1 };

int main() {
	unsigned long iterationCnt;
	unsigned int cell, neighbourCell;
	unsigned char i, x, y, neighbourCnt;
	signed char dx, dy;

	init();
	initLCD();

	setContrast(43);

	clearLCD();

	//headline
	setColor(0x0F00); // red
	drawString(4, 2, "Conway's Game of Life");
	setColor(0x00F0); // green
	fillRect(3, 8, 88, 2);

	//field
	setColor(0x0000); // black
	drawRect(4, 13, 92, 59);

	iterationCnt = 0;

	//initialising field
	//draws a glider - use converter.php to create other pictures
	golField[36] = 1;
	golField[39] = 128;
	golField[43] = 56;

	setColor(0x0FFF); // white
	fillRect(5, 14, 90, 57);
	setColor(0x00FF); // blue
	for (x = 0; x < fieldWidth; x++)
		for (y = 0; y < fieldHeight; y++) {
			cell = y * fieldWidth + x;
			if ((golField[cell >> 3] & 1 << (cell & 0b00000111)))
				fillRect(5 + x * 3, 14 + y * 3, 3, 3);
		}

	while (1) {
		//clock
		setColor(0x0FFF); // white
		fillRect(2, 73, 32, 6);
		setColor(0x0000); // black
		drawChar(2, 73, 48 + (hour / 10) % 100);
		drawChar(6, 73, 48 + hour % 10);
		drawChar(10, 73, ':');
		drawChar(14, 73, 48 + (minute / 10) % 100);
		drawChar(18, 73, 48 + minute % 10);
		drawChar(22, 73, ':');
		drawChar(26, 73, 48 + (second / 10) % 100);
		drawChar(30, 73, 48 + second % 10);

		//iteration-counter
		for (i = 0; i < 19; i++) {
			if ((iterationCnt >> i) & 1)
				setColor(0x000F); // blue
			else
				setColor(0x0FFF); // white
			fillRect(97 - i * 3, 76, 3, 3);
			if (i % 4 == 3) {
				if ((iterationCnt >> i) & 1)
					setColor(0x0B9F); // light-blue
				else
					setColor(0x0FDD); // pink
				fillRect(97 - i * 3, 76, 3, 3);
			}
		}

		//next Generation
		for (x = 0; x < fieldWidth; x++)
			for (y = 0; y < fieldHeight; y++) {
				cell = y * fieldWidth + x;
				neighbourCnt = 0;
				for (dx = -1; dx < 2; ++dx)
					for (dy = -1; dy < 2; ++dy)
						if (dx != 0 || dy != 0) {
							neighbourCell = ((y + dy + fieldHeight)
									% fieldHeight) * fieldWidth + (x + dx
									+ fieldWidth) % fieldWidth;
							if (golField[neighbourCell >> 3] & 1
									<< (neighbourCell & 0b00000111))
								++neighbourCnt;
						}
				if ((golField[cell >> 3] & 1 << (cell & 0b00000111))) { //Zelle lebt
					if (neighbourCnt == 2 || neighbourCnt == 3)
						golField2[cell >> 3] |= 1 << (cell & 0b00000111); //Zelle bleibt leben
					else {
						golField2[cell >> 3] &= ~(1 << (cell & 0b00000111)); //Zelle stirbt
						setColor(0x0FFF); // white
						fillRect(5 + x * 3, 14 + y * 3, 3, 3);
					}
				} else { //Zelle ist tot
					if (neighbourCnt == 3) {
						golField2[cell >> 3] |= 1 << (cell & 0b00000111); //Zelle wird belebt
						setColor(0x00FF); // blue
						fillRect(5 + x * 3, 14 + y * 3, 3, 3);
					} else
						golField2[cell >> 3] &= ~(1 << (cell & 0b00000111)); //Zelle bleibt tot
				}
			}

		//neues Muster erstellen
		if (PIND & (1 << P_TASTER_1))
			for (i = 0; i < fieldLength; ++i)
				golField2[i] = rand();
		for (i = 0; i < fieldLength; ++i)
			golField[i] = golField2[i];

		iterationCnt++;
	}

	return 0;
}
