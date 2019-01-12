//////////////////////////////////////////////////////////////////////////
//	List of driver commands
//////////////////////////////////////////////////////////////////////////
//	spi_command(data);					//where data is 8 bits i.e. 0x00
// 	spi_data(data);
//  LCDClearScreen();					//Fill whole screen with a color
// 	LCDSetPixel(x, y, color);			//set a pixel to selected color
//	LCDSetLine(x0, y0, x1, y1, color);	//0=start pixel	1=end pixel
//	LCDPutChar('E', 60, 60, WHITE, BLACK);		//display single character
//
//	strcpy(display,"Hello World!");				//display string
//	LCDPutStr(display, 20, 20, WHITE, BLACK);	//display string(cont)
//////////////////////////////////////////////////////////////////////////

#include <lcddriver.c>

void main_menu(void)
{
	char display[];

	LCDClearScreen();

	LCDSetRect(110, 0, 130, 130, YELLOW);	//bottom rect
	LCDSetRect(110, 64, 130, 66, GREEN);		//center line
	LCDSetRect(0, 0, 30, 130, YELLOW);		//top rect	

	strcpy(display,"WELCOME TO LIGHT");				//display header
	LCDPutStr(display, 8, 10, BROWN, YELLOW);		//x,y,fontcolor,background
	strcpy(display,"THERAPY TREATMENT");
	LCDPutStr(display, 20, 10, BROWN, YELLOW);	//x,y,fontcolor,background

	strcpy(display,"MENU");
	LCDPutStr(display, 35, 10, BLACK, GREEN);	//x,y,fontcolor,background
	LCDSetLine(44, 10, 44, 33, BLACK);		//underline header


	strcpy(display,"1) Acne treatment");
	LCDPutStr(display, 55, 10, WHITE, BLUE);	//x,y,fontcolor,background
	strcpy(display,"2) Skin Renewal  ");
	LCDPutStr(display, 75, 10, WHITE, GREEN);	//x,y,fontcolor,background
	strcpy(display,"SELECT");
	LCDPutStr(display, 115, 15, BLACK, YELLOW);	//x,y,fontcolor,background
	strcpy(display,"OPTIONS");
	LCDPutStr(display, 115, 80, BLACK, YELLOW);	//x,y,fontcolor,background

}

void menu_acne(void)
{
	char display[];

	strcpy(display,"1) Acne treatment");
	LCDPutStr(display, 55, 10, WHITE, BLUE);	//x,y,fontcolor,background
	strcpy(display,"2) Skin Renewal  ");
	LCDPutStr(display, 75, 10, WHITE, GREEN);	//x,y,fontcolor,background

}
void menu_skin(void)
{
	char display[];

	strcpy(display,"1) Acne treatment");
	LCDPutStr(display, 55, 10, WHITE, GREEN);	//x,y,fontcolor,background
	strcpy(display,"2) Skin Renewal  ");
	LCDPutStr(display, 75, 10, WHITE, BLUE);	//x,y,fontcolor,background
}

void menu_nose(void)
{
	char display[];

	strcpy(display,"1) ALLERGY RELIEVER");
	LCDPutStr(display, 55, 10, WHITE, BLUE);	//x,y,fontcolor,background
	strcpy(display,"                   ");
	LCDPutStr(display, 75, 10, WHITE, GREEN);	//x,y,fontcolor,background
	strcpy(display," BACK  ");
	LCDPutStr(display, 115, 80, BLACK, YELLOW);	//x,y,fontcolor,background
}

void acne_treatment(void)
{
	int a,b;
	char display[];

	LCDClearScreen();
	LCDSetRect(0, 0, 30, 130, YELLOW);		//top rect	

	strcpy(display,"ACNE THERAPY");
	LCDPutStr(display, 20, 30, BROWN, YELLOW);	//x,y,fontcolor,background

	strcpy(display,"SIT BACK AND RELAX");
	LCDPutStr(display, 45, 10, BLACK, GREEN);	//x,y,fontcolor,background

	strcpy(display,"FOR 15 MINUTES");
	LCDPutStr(display, 65, 10, BLACK, GREEN);	//x,y,fontcolor,background

	delay_ms(3000);

	displayfruit();

	OUTPUT_HIGH(ACNE);

	for (a=0;a<8;a++) //countdown 15 mins
		{
		delay_ms(1000);
		}
	OUTPUT_LOW(ACNE);

	for (b=0;b<2;b++) //activate buzzer
		{
		for (a=0;a<200;a++)
			{
			OUTPUT_HIGH(BUZZ);
			delay_ms(1);
			OUTPUT_LOW(BUZZ);
			delay_ms(1);
			}
		}

	LCDClearScreen();
	strcpy(display,"THERAPY COMPLETED");
	LCDPutStr(display, 45, 10, BLACK, GREEN);	//x,y,fontcolor,background
	strcpy(display,"HAVE A NICE DAY");
	LCDPutStr(display, 65, 10, BLACK, GREEN);	//x,y,fontcolor,background
	delay_ms(1000);
}

void skin_treatment(void)
{
	int a,b;
	char display[];

	LCDClearScreen();
	LCDSetRect(0, 0, 30, 130, YELLOW);		//top rect	

	strcpy(display,"SKIN RENEWAL");
	LCDPutStr(display, 20, 10, BROWN, YELLOW);	//x,y,fontcolor,background

	strcpy(display,"SIT BACK AND RELAX");
	LCDPutStr(display, 45, 10, BLACK, GREEN);	//x,y,fontcolor,background

	strcpy(display,"FOR 15 MINUTES");
	LCDPutStr(display, 65, 10, BLACK, GREEN);	//x,y,fontcolor,background

	delay_ms(3000);

	strcpy(display,"HEALTH TIPS:      ");
	LCDPutStr(display, 45, 10, BLACK, GREEN);	//x,y,fontcolor,background
	LCDSetLine(54, 10, 54, 80, BLACK);		//underline header

	strcpy(display,"DRINK 1.5 LTR OF");
	LCDPutStr(display, 65, 10, BLACK, GREEN);	//x,y,fontcolor,background
	strcpy(display,"WATER DAILY");
	LCDPutStr(display, 75, 10, BLACK, GREEN);	//x,y,fontcolor,background


	OUTPUT_HIGH(SKIN);

	for (a=0;a<8;a++) //countdown 15 mins
		{
		delay_ms(1000);
		}
	OUTPUT_LOW(SKIN);

	for (b=0;b<2;b++) //activate buzzer
		{
		for (a=0;a<200;a++)
			{
			OUTPUT_HIGH(BUZZ);
			delay_ms(1);
			OUTPUT_LOW(BUZZ);
			delay_ms(1);
			}
		}

	LCDClearScreen();
	strcpy(display,"THERAPY COMPLETED");
	LCDPutStr(display, 45, 10, BLACK, GREEN);	//x,y,fontcolor,background
	strcpy(display,"HAVE A NICE DAY");
	LCDPutStr(display, 65, 10, BLACK, GREEN);	//x,y,fontcolor,background
	delay_ms(1000);
}

void nose_treatment(void)
{
	int a,b;
	char display[];

	LCDClearScreen();
	LCDSetRect(0, 0, 30, 130, YELLOW);		//top rect	

	strcpy(display,"ALLERGY RELIEVER");
	LCDPutStr(display, 20, 10, BROWN, YELLOW);	//x,y,fontcolor,background

	strcpy(display,"SIT BACK AND RELAX");
	LCDPutStr(display, 45, 10, BLACK, GREEN);	//x,y,fontcolor,background

	strcpy(display,"FOR 15 MINUTES");
	LCDPutStr(display, 65, 10, BLACK, GREEN);	//x,y,fontcolor,background

	delay_ms(3000);

	displayfruit();

	OUTPUT_HIGH(NOSE);

	for (a=0;a<8;a++) //countdown 15 mins
		{
		delay_ms(1000);
		}
	OUTPUT_LOW(NOSE);

	for (b=0;b<2;b++) //activate buzzer
		{
		for (a=0;a<200;a++)
			{
			OUTPUT_HIGH(BUZZ);
			delay_ms(1);
			OUTPUT_LOW(BUZZ);
			delay_ms(1);
			}
		}

	LCDClearScreen();
	strcpy(display,"THERAPY COMPLETED");
	LCDPutStr(display, 45, 10, BLACK, GREEN);	//x,y,fontcolor,background
	strcpy(display,"HAVE A NICE DAY");
	LCDPutStr(display, 65, 10, BLACK, GREEN);	//x,y,fontcolor,background
	delay_ms(1000);
}

void main()
{
	int a, b, selected=1, selectacne=1, selectskin=2, optionpage=0;

   	init(); //initialize LCD
	for (b=0;b<2;b++) //activate buzzer
		{
		for (a=0;a<200;a++)
			{
			OUTPUT_HIGH(BUZZ);
			delay_ms(1);
			OUTPUT_LOW(BUZZ);
			delay_ms(1);
			}
		}
	OUTPUT_LOW(ACNE); //disable all lights
	OUTPUT_LOW(SKIN);
	OUTPUT_LOW(NOSE);

	main_menu(); //display main menu

  	while(TRUE)  // main program loop.  
	{ 
		if(INPUT(DOWN)==0)	//select menu2
		{
     		menu_skin();
			selected=selectskin;
			delay_ms(10);
		}
		if(INPUT(UP)==0)	//select menu1
		{
     		menu_acne();
			selected=selectacne;
			delay_ms(10);
		}
		if(INPUT(LEFT)==0)	//select button pressed
		{
     		if(selected==selectskin)
			{		
				skin_treatment();
				main_menu();
				selected=selectacne;
			}
		     if(selected==selectacne)
			{		
				acne_treatment();
				main_menu();
				selected=selectacne;
			}	
		}
		
		if(INPUT(RIGHT)==0)	//option button pressed
		{
			optionpage=1;
			while(optionpage==1)
			{
		    	menu_nose();
				if(INPUT(LEFT)==0)	//select button pressed
				{
					nose_treatment();
					optionpage=0;
					main_menu();
					selected=selectacne;
				}
				if(INPUT(RIGHT)==0)	//back button pressed
				{
					main_menu();
					optionpage=0;
					selected=selectacne;
				}
			}
		}
   	}
}
