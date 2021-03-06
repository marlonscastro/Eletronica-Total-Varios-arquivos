/* ***********************************************************************
**
**  Copyright (C) 2005 Christian Kranz
**
** Siemens S65 Display Control
*********************************************************************** */

#ifndef _LCD_H
#define _LCD_H


#define LCD_CS	   PB0
#define LCD_RESET  PB6
#define LCD_RS	   PB7
#define LCD_MOSI   PB2
#define LCD_MISO   PB3
#define LCD_SCK    PB1



#ifndef LCD_ASM

 void mswait(uint16_t ms);

 void lcd_init(void);			// LCD initialise
 void lcd_clrscr(void);		// LCD power down

 void lcd_wrdata(uint8_t);
 void lcd_wrcmd(uint8_t);

#endif

#endif // ifndef LCD_H

