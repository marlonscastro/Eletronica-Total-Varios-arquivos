// ********************************************************************************
// File: main.c
//
// A simple demo for the Nokia 6100 Display.
// 
// Demo 1: draws a simple figure.
// Demo 2: draws a bitmap image saved in bitmap.c
// 
// To use demo 2 set 'int demo' to 2.
//
// Author: Bianco Zandbergen December 5, 2009
// ********************************************************************************
#include "nokia6100.h"

// bitmap is saved in bitmap.c
extern unsigned char bitmap[];

int main(void) {

	int demo = 1;
	
	// initialize PCF8833 controller
	n6100_lcd_init();

	if (demo == 1) {
		
		// white background
		n6100_lcd_setrect(0, 0, 132, 132, FILL, WHITE);
		
		// head
		n6100_lcd_setcircle(100, 65, 20, BLACK);
		
		// eyes
		n6100_lcd_setcircle(110, 59, 5, BLACK);
		n6100_lcd_setcircle(110, 71, 5, BLACK);
		
		// mouth
		n6100_lcd_setline(90, 60, 90, 70, RED);
		
		// torso
		n6100_lcd_setrect(50, 50, 79, 80, FILL, GREEN);
		
		// arms
		n6100_lcd_setrect(70, 30, 79, 49, FILL, RED);
		n6100_lcd_setrect(70, 80, 79, 101, FILL, RED);
		
		// legs
		n6100_lcd_setrect(20, 50, 50, 60, FILL, BLUE);
		n6100_lcd_setrect(20, 70, 50, 80, FILL, PINK);
		
		n6100_lcd_putstr("Hello!", 110, 90, SMALL, BLACK, WHITE);	
		
	} else if (demo == 2) {
		
		// draw XMOS logo
		n6100_lcd_drawbitmap(1, 1, 130, 130, bitmap);
	}
		
	while(1);
	return 0;
}

