//// Nokia 6100 LCD with Epson S1D15G10 Controller
////  sample initialization program for PIC18F458 in CCS C 
////  Modify code by ETT
////  WATCHARIN KAOROP
//// START OF HEADER FILE ////

#include <p18cxxx.h>

typedef signed char int8;
typedef unsigned char uint8;
typedef int int16;
typedef unsigned int uint16;
typedef short long int24;
typedef unsigned short long uint24;
typedef long int32;
typedef unsigned long uint32;

//#define LCD_RESET   PORTDbits.RD1 // Digital Output 9  --> Digital Output 3
//#define LCD_CS      PORTDbits.RD0 // Digital Output 8  --> Digital Output 2
//#define SPI_CLK     PORTBbits.RB1 // Analogue Input 10 --> Digital Output 0
//#define SPI_DO      PORTCbits.RC7 // Digital Output 7  --> Digital Output 1

#define LCD_RESET   PORTDbits.RD7 // Digital Output 15
#define LCD_CS      PORTDbits.RD6 // Digital Output 14
#define SPI_CLK     PORTDbits.RD4 // Digital Output 12
#define SPI_DO      PORTDbits.RD5 // Digital Output 13

//#bit SSPEN = 0x14.5   // bit to turn on/off hardware SPI
//#bit SSPEN = 0xFC6.5
// Epson S1D15G10 Command Set

// #include "bmp.h"
#include <delays.h>
// #include "font.h"

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void delay_ms(int);
//void output_low(int);
//void output_high(int);


/** G L O B A L  D E F I N I T I O N S  ***************************************/
#define DISON       0xaf
#define DISOFF      0xae
#define DISNOR      0xa6
#define DISINV      0xa7
#define SLPIN       0x95
#define SLPOUT      0x94
#define COMSCN      0xbb
#define DISCTL      0xca
#define PASET       0x75   // 00,131
#define CASET       0x15   // 00,131
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


//a few basic colors
#define RED         0xE0                           // Color Code
#define GREEN       0x1C
#define BLUE        0x03
#define YELLOW      0xFC
#define MAGENTA     0xE3
#define CYAN        0x1F
#define BLACK       0x00
#define WHITE       0xFF




////  START OF MAIN .C SOURCE FILE ////

//#include "<path to .h file cut from above>"
//#use fast_io(C)



/*****************************/
/* Table Font Size 5x7 Pixel */
/*****************************/
// #pragma udata gpr1
rom const unsigned char font[475] =
{
   0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,                  // Sp
   0x00 , 0x06 , 0x5F , 0x06 , 0x00 ,                      // !
   0x07 , 0x03 , 0x00 , 0x07 , 0x03 ,                      // ,
   0x24 , 0x7E , 0x24 , 0x7E , 0x24 ,                      // #
   0x24 , 0x2B , 0x6A , 0x12 , 0x00 ,                      // $
   0x63 , 0x13 , 0x08 , 0x64 , 0x63 ,                      // %
   0x36 , 0x49 , 0x56 , 0x20 , 0x50 ,                      // &
   0x00 , 0x07 , 0x03 , 0x00 , 0x00 ,                      // //
   0x00 , 0x3E , 0x41 , 0x00 , 0x00 ,                      // (
   0x00 , 0x41 , 0x3E , 0x00 , 0x00 ,                      // )
   0x08 , 0x3E , 0x1C , 0x3E , 0x08 ,                      // *
   0x08 , 0x08 , 0x3E , 0x08 , 0x08 ,                      // +
   0x00 , 0xE0 , 0x60 , 0x00 , 0x00 ,                      // ,
   0x08 , 0x08 , 0x08 , 0x08 , 0x08 ,                      // -
   0x00 , 0x60 , 0x60 , 0x00 , 0x00 ,                      // .
   0x20 , 0x10 , 0x08 , 0x04 , 0x02 ,                      // /
   0x3E , 0x51 , 0x49 , 0x45 , 0x3E ,                      // 0
   0x00 , 0x42 , 0x7F , 0x40 , 0x00 ,                      // 1
   0x62 , 0x51 , 0x49 , 0x49 , 0x46 ,                      // 2
   0x22 , 0x49 , 0x49 , 0x49 , 0x36 ,                      // 3
   0x18 , 0x14 , 0x12 , 0x7F , 0x10 ,                      // 4
   0x2F , 0x49 , 0x49 , 0x49 , 0x31 ,                      // 5
   0x3C , 0x4A , 0x49 , 0x49 , 0x30 ,                      // 6
   0x01 , 0x71 , 0x09 , 0x05 , 0x03 ,                      // 7
   0x36 , 0x49 , 0x49 , 0x49 , 0x36 ,                      // 8
   0x06 , 0x49 , 0x49 , 0x29 , 0x1E ,                      // 9
   0x00 , 0x6C , 0x6C , 0x00 , 0x00 ,                      // :
   0x00 , 0xEC , 0x6C , 0x00 , 0x00 ,                      // ;
   0x08 , 0x14 , 0x22 , 0x41 , 0x00 ,                      // <
   0x24 , 0x24 , 0x24 , 0x24 , 0x24 ,                      // =
   0x00 , 0x41 , 0x22 , 0x14 , 0x08 ,                      // >
   0x02 , 0x01 , 0x59 , 0x09 , 0x06 ,                      // ?
   0x3E , 0x41 , 0x5D , 0x55 , 0x1E ,                      // @
   0x7E , 0x09 , 0x09 , 0x09 , 0x7E ,                      // A
   0x7F , 0x49 , 0x49 , 0x49 , 0x36 ,                      // B
   0x3E , 0x41 , 0x41 , 0x41 , 0x22 ,                      // C
   0x7F , 0x41 , 0x41 , 0x41 , 0x3E ,                      // D
   0x7F , 0x49 , 0x49 , 0x49 , 0x41 ,                      // E
   0x7F , 0x09 , 0x09 , 0x09 , 0x01 ,                      // F
   0x3E , 0x41 , 0x49 , 0x49 , 0x7A ,                      // G
   0x7F , 0x08 , 0x08 , 0x08 , 0x7F ,                      // H
   0x00 , 0x41 , 0x7F , 0x41 , 0x00 ,                      // I
   0x30 , 0x40 , 0x40 , 0x40 , 0x3F ,                      // J
   0x7F , 0x08 , 0x14 , 0x22 , 0x41 ,                      // K
   0x7F , 0x40 , 0x40 , 0x40 , 0x40 ,                      // L
   0x7F , 0x02 , 0x04 , 0x02 , 0x7F ,                      // M
   0x7F , 0x02 , 0x04 , 0x08 , 0x7F ,                      // N
   0x3E , 0x41 , 0x41 , 0x41 , 0x3E ,                      // O
   0x7F , 0x09 , 0x09 , 0x09 , 0x06 ,                      // P
   0x3E , 0x41 , 0x51 , 0x21 , 0x5E ,                      // Q
   0x7F , 0x09 , 0x09 , 0x19 , 0x66 ,                      // R
   0x26 , 0x49 , 0x49 , 0x49 , 0x32 ,                      // S
   0x01 , 0x01 , 0x7F , 0x01 , 0x01 ,                      // T
   0x3F , 0x40 , 0x40 , 0x40 , 0x3F ,                      // U
   0x1F , 0x20 , 0x40 , 0x20 , 0x1F ,                      // V
   0x3F , 0x40 , 0x3C , 0x40 , 0x3F ,                      // W
   0x63 , 0x14 , 0x08 , 0x14 , 0x63 ,                      // X
   0x07 , 0x08 , 0x70 , 0x08 , 0x07 ,                      // Y
   0x71 , 0x49 , 0x45 , 0x43 , 0x00 ,                      // Z
   0x00 , 0x7F , 0x41 , 0x41 , 0x00 ,                      // [
   0x02 , 0x04 , 0x08 , 0x10 , 0x20 ,                      // Back slash
   0x00 , 0x41 , 0x41 , 0x7F , 0x00 ,                      // ]
   0x04 , 0x02 , 0x01 , 0x02 , 0x04 ,                      // ^
   0x80 , 0x80 , 0x80 , 0x80 , 0x80 ,                      // _
   0x00 , 0x03 , 0x07 , 0x00 , 0x00 ,                      // `
   0x20 , 0x54 , 0x54 , 0x54 , 0x78 ,                      // a
   0x7F , 0x44 , 0x44 , 0x44 , 0x38 ,                      // b
   0x38 , 0x44 , 0x44 , 0x44 , 0x28 ,                      // c
   0x38 , 0x44 , 0x44 , 0x44 , 0x7F ,                      // d
   0x38 , 0x54 , 0x54 , 0x54 , 0x18 ,                      // e
   0x08 , 0x7E , 0x09 , 0x09 , 0x00 ,                      // f
   0x18 , 0xA4 , 0xA4 , 0xA4 , 0x7C ,                      // g
   0x7F , 0x04 , 0x04 , 0x78 , 0x00 ,                      // h
   0x00 , 0x00 , 0x7D , 0x00 , 0x00 ,                      // i
   0x40 , 0x80 , 0x84 , 0x7D , 0x00 ,                      // j
   0x7F , 0x10 , 0x28 , 0x44 , 0x00 ,                      // k
   0x00 , 0x00 , 0x7F , 0x40 , 0x00 ,                      // l
   0x7C , 0x04 , 0x18 , 0x04 , 0x78 ,                      // m
   0x7C , 0x04 , 0x04 , 0x78 , 0x00 ,                      // n
   0x38 , 0x44 , 0x44 , 0x44 , 0x38 ,                      // o
   0xFC , 0x44 , 0x44 , 0x44 , 0x38 ,                      // p
   0x38 , 0x44 , 0x44 , 0x44 , 0xFC ,                      // q
   0x44 , 0x78 , 0x44 , 0x04 , 0x08 ,                      // r
   0x08 , 0x54 , 0x54 , 0x54 , 0x20 ,                      // s
   0x04 , 0x3E , 0x44 , 0x24 , 0x00 ,                      // t
   0x3C , 0x40 , 0x20 , 0x7C , 0x00 ,                      // u
   0x1C , 0x20 , 0x40 , 0x20 , 0x1C ,                      // v
   0x3C , 0x60 , 0x30 , 0x60 , 0x3C ,                      // w
   0x6C , 0x10 , 0x10 , 0x6C , 0x00 ,                      // x
   0x9C , 0xA0 , 0x60 , 0x3C , 0x00 ,                      // y
   0x64 , 0x54 , 0x54 , 0x4C , 0x00 ,                      // z
   0x08 , 0x3E , 0x41 , 0x41 , 0x00 ,                      // {
   0x00 , 0x00 , 0x7F , 0x00 , 0x00 ,                      // |
   0x00 , 0x41 , 0x41 , 0x3E , 0x08 ,                      // }
   0x02 , 0x01 , 0x02 , 0x01 , 0x00 ,                      // ~
};

void pset(unsigned char color, unsigned char x, unsigned char y);
void spi_command(int8);
void spi_data(int8);
void spi_do(int8);

void LCD_Set_Box(unsigned char x1,
                 unsigned char y1,
             unsigned char x2,
             unsigned char y2);
             
void LCD_Fill_Screen(unsigned char color,
                     unsigned char x1,
                  unsigned char y1,
                  unsigned char x2,
                  unsigned char y2);
                 
void LCD_Initial(void);                 
void Draw_Color_Bar(void);                 
void LCDWrite130x130bmp(void); 

void LCD_Print_Char(unsigned char fcolor,
               unsigned char bcolor,
               unsigned char x,
               unsigned char y,char c);

void LCD_Print_String(unsigned char fcolor,
                  unsigned char bcolor,
                  unsigned char x,
                  unsigned char y,char *text);



void LCDmain()
{

   int i,index;
   char String_Buff[30];                           // String Array Buffer
   
   
   //setup_adc_ports(NO_ANALOGS);
   //setup_adc(ADC_OFF);
   //setup_comparator(NC_NC_NC_NC);
   
   //setup_spi(SPI_MASTER|SPI_L_TO_H|SPI_XMIT_L_TO_H|SPI_CLK_DIV_4);
   // Already Commented Out   // setup_spi(SPI_MASTER|SPI_L_TO_H|SPI_XMIT_L_TO_H);
   //setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   //setup_timer_1(T1_DISABLED);
   //setup_timer_2(T2_DISABLED, 0, 1);
   //set_tris_c(0x00);   // all outputs, can change to mask only hardware SPI bits if needed

   LCD_Initial(); 
   
   while(1)
   {
   Draw_Color_Bar();       
   delay_ms(2000);
   
   LCD_Fill_Screen(RED,0,0,131,131);     

   delay_ms(1000);
   
   LCD_Fill_Screen(GREEN,0,0,131,131);
   
   delay_ms(1000);
   
   LCD_Fill_Screen(BLUE,0,0,131,131);   
   
   delay_ms(1000);
   
   LCD_Fill_Screen(YELLOW,0,0,131,131);
   
   delay_ms(1000);
   
   LCD_Fill_Screen(MAGENTA,0,0,131,131);   
     
   delay_ms(1000);
   
   LCD_Fill_Screen(CYAN,0,0,131,131);
   
   delay_ms(1000);
   
   LCD_Fill_Screen(BLACK,0,0,131,131);     
   
   delay_ms(1000);
   
   // LCDWrite130x130bmp();
     
   delay_ms(2000);   
     
   spi_command(DATCTL);                                // datctl
   spi_data(0x00);
   spi_data(0);
   spi_data(0x01);
   spi_data(0);

   LCD_Fill_Screen(BLACK,0,0,131,131);                 // Fill Screen with Black Color
   sprintf(String_Buff," TEST ET-LCD6610 ");
   LCD_Print_String(YELLOW, BLACK, 7, 5,String_Buff);             
   sprintf(String_Buff," WWW.ETTEAM.COM ");
   LCD_Print_String(CYAN, BLACK, 7, 15,String_Buff);
   sprintf(String_Buff," TEST RED COLOR ");
   LCD_Print_String(RED, BLACK, 7, 30,String_Buff);
   sprintf(String_Buff," TEST GREEN COLOR ");
   LCD_Print_String(GREEN, BLACK, 7, 45,String_Buff);
   sprintf(String_Buff," TEST BLUE COLOR ");
   LCD_Print_String(BLUE, BLACK, 7, 60,String_Buff);
   sprintf(String_Buff," TEST WHITE COLOR ");
   LCD_Print_String(WHITE, BLACK, 7, 75,String_Buff);
   sprintf(String_Buff," TEST MAGENTA COLOR ");
   LCD_Print_String(MAGENTA, BLACK, 7, 90,String_Buff);
   sprintf(String_Buff," TEST CYAN COLOR ");
   LCD_Print_String(CYAN, BLACK, 7, 105,String_Buff);
   sprintf(String_Buff," TEST YELLOW COLOR ");
   LCD_Print_String(YELLOW, BLACK, 7, 120,String_Buff);     
         
   delay_ms(5000);   
     
   }

}

void pset(unsigned char color, unsigned char x, unsigned char y){
//  sets the starting page(row) and column (x & y) coordinates in ram,
//  then writes the colour to display memory.  The ending x & y are left
//  maxed out so one can continue sending colour data bytes to the 'open'
//  RAMWR command to fill further memory.  issuing any other command
//  finishes RAMWR.

  x += 2;                  // for some reason starts at 2

  spi_command(PASET);   // page start/end ram
  spi_data(x);
  spi_data(ENDPAGE);

  spi_command(CASET);   // column start/end ram
  spi_data(y);
  spi_data(ENDCOL);

  spi_command(RAMWR);    // write
  spi_data(color);
}

void spi_command(int8 dat)
{
      LCD_CS = 0;      // enable chip
   
   /* SPI DATA BIT 9 */
   SPI_DO = 0;     // output low on data out (9th bit low = command)
   SPI_CLK = 0;
   Delay1TCY();        // send clock pulse
   SPI_CLK = 1;
   Delay1TCY();        // send clock pulse

   spi_do(dat);

   //SSPEN=1;                 // turn hardware SPI back on
   //spi_write(dat);          // make PIC do the work for the command byte
   LCD_CS = 1;     // disable
}

void spi_data(int8 dat)
{
   LCD_CS = 0;      // enable chip
   
   /* SPI DATA BIT 9 */
   SPI_DO = 1;    // output high on data out (9th bit high = data)
   SPI_CLK = 0;
   Delay1TCY();         // send clock pulse
   SPI_CLK = 1;
   Delay1TCY();        // send clock pulse
   
   spi_do(dat);
   
   //SSPEN=1;                 // turn hardware SPI back on
   //spi_write(dat);          // make PIC do the work for the data byte
   LCD_CS = 1;     // disable
}

void spi_do(int8 dat)
{
   int i;
   i = 0;
   /* SPI DATA BITS 1 through 8 */
   for(i = 1; i <= 8; i++) // setup a loop of 8 iterations, one for each bit
   {
      if (dat > (unsigned)127)  // test the most significant bit
      {
         SPI_DO = 1;; // if it is a 1 (ie. B1XXXXXXX), set the master out pin high
      }
      else
      {
         SPI_DO = 0; // if it is not 1 (ie. B0XXXXXXX), set the master out pin low
      }

      dat = dat << 1;
      SPI_CLK = 0;
      Delay1TCY();        // send clock pulse
      SPI_CLK = 1;
      Delay1TCY();        // send clock pulse
   }
}


/*************************/
/* Initial LCD-NOKIA6610 */
/*************************/
void LCD_Initial(void)
{

   // reset display
   SPI_CLK = 0;
   SPI_DO = 0;
   LCD_CS = 1;
   LCD_RESET = 0;
   delay_ms(100);
   LCD_RESET = 1;
   SPI_CLK = 1;


   //init'd, now drop CS to send commands/data and raise when finished
   spi_command(NOP);

    spi_command(DISCTL);  // display control
    spi_data(0x0C);      // 12 = 1100 - CL dividing ratio [don't divide] switching period 8H (default)
    spi_data(0x20);      // 32 = (128/4)-1 (round up) number of display lines for scanning
    spi_data(0x0C);      // 12 = 1100 - number of lines to be inversely highlighted
    spi_data(0x00);

    spi_command(COMSCN);  // common scanning direction
    spi_data(0x01);
    // 0 0 0 =   1 -> 80   81 -> 160
    // 0 0 1 =   1 -> 80   81 <- 160
    // 0 1 0 =   1 <- 80   81 -> 160
    // 0 1 1 =   1 <- 80   81 <- 160

    spi_command(OSCON);  // internal oscialltor ON

    spi_command(SLPOUT);  // sleep out

    spi_command(VOLCTR);  // electronic volume, this is the contrast/brightness
    spi_data(0x23);   // volume (contrast) setting - fine tuning
    spi_data(0x03);   // internal resistor ratio - coarse adjustment

    spi_command(PWRCTR);  // power ctrl
    spi_data(0x0f);      //everything on, no external reference resistors
    delay_ms(100);

    spi_command(DISINV);  // invert display mode

    spi_command(DATCTL);  // data control
    spi_data(0x00);   // normal display of page/column address, page scan direction
    spi_data(0x00);   // normal RGB arrangement
    spi_data(0x01);   // 8-bit grayscale

    spi_command(RGBSET8);   // setup 8-bit color lookup table  [RRRGGGBB]
  //RED
    spi_data(0);
    spi_data(2);
    spi_data(4);
    spi_data(6);
    spi_data(8);
    spi_data(10);
    spi_data(12);
    spi_data(15);
    // GREEN
    spi_data(0);
    spi_data(2);
    spi_data(4);
    spi_data(6);
    spi_data(8);
    spi_data(10);
    spi_data(12);
    spi_data(15);
    //BLUE
    spi_data(0);
    spi_data(4);
    spi_data(9);
    spi_data(15);

    spi_command(NOP);  // nop
   
   LCD_Fill_Screen(WHITE,0,0,131,131);
   spi_command(DISON);                // Display On   
   
}


/********************************/
/*  (x1,y1)                  */
/*     ********************      */
/*     *                  *      */
/*     *                  *      */
/*     ********************      */
/*                    (x2,y2)   */
/********************************/

void LCD_Set_Box(unsigned char x1,
                 unsigned char y1,
             unsigned char x2,
             unsigned char y2)
{
   spi_command(CASET);                              // Page Start/Eend ram
   spi_data(x1);     
   spi_data(x2);

   spi_command(PASET);                              // Column Start/End ram
   spi_data(y1);
   spi_data(y2);
}


/**************************/
/* Fill Screen With Color */
/**************************/
void LCD_Fill_Screen(unsigned char color,
                     unsigned char x1,
                  unsigned char y1,
                  unsigned char x2,
                  unsigned char y2)
{
  unsigned int j;
  unsigned int total_bytes1;
  unsigned int total_bytes2;
  unsigned int total_bytes;

  LCD_Set_Box(x1, y1, x2, y2);

  spi_command(RAMWR);
  total_bytes1 = (x2 - x1 + 1);
  total_bytes2 = (y2 - y1 + 1);
  total_bytes = total_bytes1 * total_bytes2;
  for (j = 0; j < total_bytes; j++)
  {
    spi_data(color);
  }
}

/**********************/
/* Create 4-Bar Color */
/**********************/
void Draw_Color_Bar(void)
{
   LCD_Fill_Screen(RED,0,0,131,33);
   LCD_Fill_Screen(GREEN,0,34,131,66);
   LCD_Fill_Screen(BLUE,0,67,131,99);
   LCD_Fill_Screen(WHITE,0,100,131,131);
}

/*
void LCDWrite130x130bmp(void)
{
   unsigned int j; // loop counter

   // Data control (need to set "normal" page address for Olimex photograph)
   spi_command(DATCTL);
   spi_data(0x00); // P1: 0x00 = page address normal, column address normal, address scan in column direction
   spi_data(0x01); // P2: 0x01 = RGB sequence B-> G-> R(Invert Direction)
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
  // for(j = 0; j < 25740; j++)
 
     for (j=0;j<sizeof(picture);j++)
   {
      spi_data(picture[j]);
   }

   // Data control (return to "inverted" page address)
   spi_command(DATCTL);
   spi_data(0x00); // P1: 0x01 = page address inverted, column address normal, address scan in column direction
   spi_data(0x01); // P2: 0x01 = RGB sequence B-> G-> R(Invert Direction)
   spi_data(0x01); // P3: 0x02 = Grayscale -> 16

   // Display On
   spi_command(DISON);
}
*/


/************************/
/* Print Char on Screen */
/************************/
void LCD_Print_Char(unsigned char fcolor,
               unsigned char bcolor,
               unsigned char x,
               unsigned char y,char c)
{
   unsigned int i;
   LCD_Set_Box(x,y,x,y+7);
   spi_command(RAMWR);
   for(i=0;i<8;i++)
   {
     if (1<<i & c)
        spi_data(fcolor);
     else
        spi_data(bcolor);
   }
}

/**************************/
/* Print String on Screen */
/**************************/
void LCD_Print_String(unsigned char fcolor,
                  unsigned char bcolor,
                  unsigned char x,
                  unsigned char y,char *text)
{
   unsigned char c;
   unsigned char t;
   unsigned int i;
   unsigned int j;

   while(*text != 0)
   {
     t = *text;
     i = t - 32;
     i = i * 5;
     for(j = i; j < i+5; j++)
     {
       c = font[j];
       LCD_Print_Char(fcolor, bcolor, x++, y, c);
     }
     LCD_Print_Char(fcolor, bcolor, x++, y, 0);
     text++;
   }
}

void delay_ms(int time)
{
   int time_i;
   for(time_i = 0; time_i < time; time_i++)
   {
      Delay100TCYx (120);
   }
}

/*
void output_low(int PIN)
{
   PIN = 0;
}

void output_high(int PIN)
{
   PIN = 1;
}
*/