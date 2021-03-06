//-���������� ������� Siemens �31, C72, ��72, ��75, �76-
//           ������� ��������� LPH9135
//              128�128 ��������
//                    v 1.0
//              ==== ����� ����� ====
//------------------------------------------------------


#include <delay.h>
#include "Symbols.h"

//#define _8_BIT_COLOR  //���� ���������������� - 16-�� ������ ����
#define _GEOMETRICAL  //������������� ������� ������ �������������� �����

//===============================================================
//                  ���������� ������� ����� 
//===============================================================
#define LCD_CS       PORTA.0 //����� ����
#define LCD_RESET    PORTA.1 //�����
#define LCD_RS       PORTA.2   //CD - ��� ������������ ������
#define LCD_CLK    PORTA.3 //�������������
#define LCD_DATA    PORTA.4 //������

//*************************************************************
//�������/������
#define CMD 0
#define DAT 1
char RS_old;
  
//===============================================================
//                  ����������� ������
//===============================================================
#ifdef _8_BIT_COLOR
//8-�� ������� �������� ������� (256 ������)
#define GREEN       0x1C
#define DARK_GREEN  0x15
#define RED         0xE0
#define BLUE        0x1F    
#define DARK_BLUE   0x03
#define YELLOW      0xFC
#define ORANGE      0xEC
#define VIOLET      0xE3
#define WHITE       0xFF
#define BLACK       0x00
#define GREY        0x6D

#else
//16-�� ������� �������� ������� (65536 ������)
#define    BLACK                0x0000 
#define    WHITE                0xFFFF 
#define    GRAY                 0xE79C
#define    GREEN                0x07E0 
#define    BLUE                 0x001F 
#define    RED                  0xF800 
#define    SKY                  0x5d1c 
#define    YELLOW               0xffe0 
#define    MAGENTA              0xf81f
#define    CYAN                 0x07ff
#define    ORANGE               0xfca0 
#define    PINK                 0xF97F
#define    BROWN                0x8200
#define    VIOLET               0x9199
#define    SILVER               0xa510
#define    GOLD                 0xa508
#define    BEGH                 0xf77b
#define    NAVY                 0x000F      
#define    DARK_GREEN           0x03E0      
#define    DARK_CYAN            0x03EF      
#define    MAROON               0x7800      
#define    PURPLE               0x780F      
#define    OLIVE                0x7BE0      
#define    LIGHT_GREY           0xC618      
#define    DARK_GREY            0x7BEF
#endif

//*************************************************************
//��������� �������
void LCD_init (void);
void Send_to_lcd (unsigned char RS, unsigned char data);
void SetArea (char x1, char x2, char y1, char y2);
void Put_Pixel (char x, char y, unsigned int color);
void Send_Symbol (unsigned char symbol, char x, char y, int t_color, int b_color, char zoom_width, char zoom_height);  
void LCD_Putchar (char symbol, char x, char y, int t_color, int b_color, char zoom_width, char zoom_height, int rot);    
void LCD_Puts(char *str, int x, int y,  int t_color, int b_color, char zoom_width, char zoom_height, int rot);
void LCD_Putsf(flash char *str, int x, int y,  int t_color, int b_color, char zoom_width, char zoom_height, int rot);
void Send_Symbol_Shadow (unsigned char symbol, char x, char y, int t_color, char zoom_width, char zoom_height);
void LCD_Putchar_Shadow (char symbol, char x, char y, int t_color, char zoom_width, char zoom_height, int rot);
void LCD_Puts_Shadow (char *str, int x, int y,  int t_color, char zoom_width, char zoom_height, int rot);
void LCD_Putsf_Shadow (flash char *str, int x, int y,  int t_color, char zoom_width, char zoom_height, int rot);
void LCD_FillScreen (unsigned int color);
void LCD_Output_image (char x, char y, char width, char height, flash char *img, int rot);
void Send_Image (char x, char y, char width, char height, flash char *img);
#ifdef _GEOMETRICAL
void LCD_DrawLine (char x1, char y1, char x2, char y2, int color);
void LCD_DrawRect (char x1, char y1, char width, char height, char size, int color);
void LCD_FillRect (char x1, char y1, char width, char height, int color);
void LCD_DrawCircle (char xcenter, char ycenter, char rad, int color);
void LCD_FillCircle (char xcenter, char ycenter, char rad, int color);
void LCD_DrawTriangle (char x1, char y1, char x2, char y2, char x3, char y3, int color);
void LCD_FillTriangle (char x1, char y1, char x2, char y2, char x3, char y3, int color);
void LCD_FillTriangleA (char x1, char y1, char x2, char y2, char x3, char y3, int color);
#endif 

//===============================================================
//                        �������������
//===============================================================
void LCD_init(void)
{
 LCD_CS=0;
 LCD_DATA=0;
 LCD_CLK=1;
 LCD_RESET = 1;
 LCD_RESET = 0;
 LCD_RESET = 1;
 LCD_CLK=1;
 LCD_DATA=1;
 LCD_CLK=1;
 delay_ms(10);
 Send_to_lcd(CMD, 0x01); //����������� �����
 Send_to_lcd(CMD, 0x25); //Wtite Contrast
 Send_to_lcd(DAT, 0x40);    
 Send_to_lcd(CMD, 0x11); //����� �� ������� ������
 //sendCMD(0x03); // Booster on
 delay_ms(10);
 Send_to_lcd(CMD, 0x20); //Display Inversion Off
 Send_to_lcd(CMD, 0xB9);
 Send_to_lcd(CMD, 0x38); //Idle Mod Off
 Send_to_lcd(CMD, 0x29); //��������� �������
 Send_to_lcd(CMD, 0x13); //Normal Mod On
 Send_to_lcd(CMD, 0x36); //Memory Access Control
 Send_to_lcd(DAT, 0x00);
 Send_to_lcd(CMD, 0x3a); //��������� �������� �������
 #ifdef _8_BIT_COLOR
 Send_to_lcd(DAT, 0x02); //���� �� ������� 256 ������
 #else
 Send_to_lcd(DAT, 0x05); //��� ����� �� ������� 65536 ������
 #endif
 Send_to_lcd(CMD, 0x2A); //X_Adress Area
 Send_to_lcd(DAT, 0x00);
 Send_to_lcd(DAT, 0x7F);
 Send_to_lcd(CMD, 0xB4); //Frame Frequency Select
 Send_to_lcd(DAT, 0x03);
 Send_to_lcd(DAT, 0x08);
 Send_to_lcd(DAT, 0x0B);
 Send_to_lcd(DAT, 0x0E);
 Send_to_lcd(CMD, 0xBA); //Display Control
 Send_to_lcd(DAT, 0x07);
 Send_to_lcd(DAT, 0x0D);
 Send_to_lcd(CMD, 0x2B); //Page Adress Set
 Send_to_lcd(DAT, 0x00);
 Send_to_lcd(DAT, 0x7F);    
}

//===============================================================
//������� ������ �������/������ � LCD (RS==0 - �������, RS==1 - ������)
//===============================================================
void Send_to_lcd (unsigned char RS, unsigned char data){
 //unsigned char count;  
 LCD_CLK = 0;
 LCD_DATA = 0;
 if ((RS_old != RS) || (!RS_old && !RS)) //��������� ������ �������� RS (���� ��������� ���� ������� �� ������� CS)
 { 
  LCD_CS=1;   // ��������� CS 
  LCD_RS=RS;   
  LCD_CS=0;   // ����� CS 
 }
 //******************************************************************************
 //����� ���� ������������ ����� ���������� ��� ��� ������ ����� � ������� 
 //******************************************************************************
 /*
 for (count = 0; count < 8; count++) { 
  if(data&0x80)      LCD_DATA=1;
  else             LCD_DATA=0;
  LCD_CLK=1;  
  data <<= 1;
  LCD_CLK=0;    
 } 
 */
 //******************************************************************************
 //����� ������ ��� (��� �����) ������������ ����� ������� ������ ����� � ������� 
 //******************************************************************************
 LCD_DATA = 0;
 if ((data & 128) == 128)  LCD_DATA = 1; 
 LCD_CLK=1;
 LCD_CLK=0;
 LCD_DATA = 0;
 if ((data & 64) == 64)  LCD_DATA = 1; 
 LCD_CLK=1;
 LCD_CLK=0;
 LCD_DATA = 0;
 if ((data & 32) == 32)  LCD_DATA = 1; 
 LCD_CLK=1;
 LCD_CLK=0;
 LCD_DATA = 0;
 if ((data & 16) ==16)  LCD_DATA = 1; 
 LCD_CLK=1;
 LCD_CLK=0;
 LCD_DATA = 0;
 if ((data & 8) == 8)  LCD_DATA = 1; 
 LCD_CLK=1;
 LCD_CLK=0;
 LCD_DATA = 0;
 if ((data & 4) == 4)  LCD_DATA = 1; 
 LCD_CLK=1;
 LCD_CLK=0;
 LCD_DATA = 0;
 if ((data & 2) == 2)  LCD_DATA = 1; 
 LCD_CLK=1;
 LCD_CLK=0;
 LCD_DATA = 0;
 if ((data & 1) == 1)  LCD_DATA = 1; 
 LCD_CLK=1;
 LCD_CLK=0;
 
 RS_old=RS;  //��������� �������� RS   
 LCD_DATA = 0;
}

//===============================================================
//              ������� ������������� ������� ������
//===============================================================
void SetArea(char x1, char x2, char y1, char y2)
{
 Send_to_lcd( CMD, 0x2A );  //������ ������� �� X
 Send_to_lcd( DAT, x1 );    //���������
 Send_to_lcd( DAT, x2 );    //��������

 Send_to_lcd( CMD, 0x2B );  //������ ������� �� Y
 Send_to_lcd( DAT, y1 );    //��������� 
 Send_to_lcd( DAT, y2 );    //��������

 Send_to_lcd( CMD, 0x2C );  //���������� ������� �� ������ ������ � ������ � �������� �������� ������
}                 

//===============================================================
//                          ������ ����� 
//=============================================================== 
void Put_Pixel (char x, char y, unsigned int color) 
{
 signed char i;
 SetArea( x, x, y, y ); 
 LCD_RS = 1;    
 
 #ifdef _8_BIT_COLOR   //(8-�� ������� �������� ������� (256 ������))
 Send_to_lcd( DAT, color ); //������ - ����� ���� ������� 
 #else                 //(16-�� ������� �������� ������� (65536 ������))
 Send_to_lcd( DAT, (color >> 8) ); 
 Send_to_lcd( DAT, color );
 #endif
}  
                   
//===============================================================
//           ������� ���������� ������� �� �������
//===============================================================
void Send_Symbol (unsigned char symbol, char x, char y, int t_color, int b_color, char zoom_width, char zoom_height) 
{
 unsigned char temp_symbol, a, b, zw, zh, mask; 
  
 if (symbol>127) symbol-=64;    //������� ������������� ����� ������� ASCII
 for ( a = 0; a < 5; a++) //��������� 5 ����, ������������ ������
 {
    temp_symbol = font_5x8[symbol-32][a];
    zw = 0; 
    while(zw != zoom_width) //����� ����� ����������� zw ��� 
    {    
        mask=0x01;  
       
        SetArea( x+zw, x+zw, y, y+(zoom_height*8)-1 );                        
        
        LCD_RS = 1; //���������� ������          
        for ( b = 0; b < 8; b++ ) //���� ����������� 8 ��� �����
        {         
            zh = zoom_height; //� zoom_height ��� ���������� ������ �������
            while(zh != 0) //����� ������� ����������� zh ���
            {
                if (temp_symbol&mask) 
                {
                    #ifdef _8_BIT_COLOR   //(8-�� ������� �������� ������� (256 ������))
                    Send_to_lcd( DAT, t_color ); //������ - ����� ���� ������� 
                    #else                 //(16-�� ������� �������� ������� (65536 ������))
                    Send_to_lcd( DAT, (t_color >> 8) ); Send_to_lcd( DAT, t_color );
                    #endif
                }
                else 
               {
                    #ifdef _8_BIT_COLOR   //(8-�� ������� �������� ������� (256 ������))
                    Send_to_lcd( DAT, b_color ); //������ - ����� ���� ������� 
                    #else                 //(16-�� ������� �������� ������� (65536 ������))
                    Send_to_lcd( DAT, (b_color >> 8) ); Send_to_lcd( DAT, b_color );
                    #endif
                }
                zh--;
            }
            mask<<=1; //������ ���������� mask �� 1 ��� �����;    
        }
        zw++;
    }
 
   x=x+zoom_width; //�������� ����� ���������� ������� �� ��� x ��� ������ ���������� �����             
 }
}  

//===============================================================
// ������� ������ ������ ������� ASCII-���� (�� ����� Symbols.h)
//===============================================================
void LCD_Putchar(char symbol, char x, char y, int t_color, int b_color, char zoom_width, char zoom_height, int rot)
{
    unsigned char m;
    if(zoom_width == 0)   zoom_width = 1;
    if(zoom_height == 0)  zoom_height = 1;
    switch (rot)
    {
        case 0:  //��������� ����� ���� � � � - ����� ������� ���� �������   
        Send_Symbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height);
        break;
        //================================
        case 90:        
        Send_to_lcd(CMD, 0x36); 
        Send_to_lcd(DAT, 0x60); //��������� ����� ���� � � � - ������ ������� ���� ������� 
        Send_Symbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height);
        Send_to_lcd(CMD, 0x36); 
        Send_to_lcd(DAT, 0x00);
        break;
        //================================
        case 180:       
        Send_to_lcd(CMD, 0x36); 
        Send_to_lcd(DAT, 0xC0); //��������� ����� ���� � � � - ������ ������ ���� ������� 
        Send_Symbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height);
        Send_to_lcd(CMD, 0x36); 
        Send_to_lcd(DAT, 0x00);
        break;
        //================================
        case 270:       
        Send_to_lcd(CMD, 0x36); 
        Send_to_lcd(DAT, 0xA0); //��������� ����� ���� � � � - ����� ������ ���� �������  
        Send_Symbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height);
        Send_to_lcd(CMD, 0x36); 
        Send_to_lcd(DAT, 0x00);
        break;
        //================================
        default:
        Send_to_lcd(CMD, 0x36); 
        Send_to_lcd(DAT, 0x00); //��������� ����� ���� � � � - ����� ������� ���� �������  
        Send_Symbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height);
        Send_to_lcd(CMD, 0x36); 
        Send_to_lcd(DAT, 0x00);
        //=================================    
    };  
}

//===============================================================
//          ������� ������ ������, ������������� � ram 
//===============================================================
void LCD_Puts(char *str, int x, int y,  int t_color, int b_color, char zoom_width, char zoom_height, int rot)
{
 unsigned char i=0;
              
 if(zoom_width == 0)   zoom_width = 1;
 if(zoom_height == 0)  zoom_height = 1;
   
 while (str[i]) //x � y - ����� ������� ��������� �������; � ����������� ���������� i ����� ������ ���������� ������� ��������� �� i*6 (��� ������������ ������� �������)  
 {      
  LCD_Putchar(str[i], x+(i*6*zoom_width), y, t_color, b_color, zoom_width, zoom_height, rot);
  i++;
 }  
}

//===============================================================
//          ������� ������ ������, ������������� �� flash
//===============================================================
void LCD_Putsf(flash char *str, int x, int y,  int t_color, int b_color, char zoom_width, char zoom_height, int rot)
{
 unsigned char i=0;
        
 if(zoom_width == 0)   zoom_width = 1;
 if(zoom_height == 0)  zoom_height = 1;
   
 while (str[i]) //x � y - ����� ������� ��������� �������; � ����������� ���������� i ����� ������ ���������� ������� ��������� �� i*6 (��� ������������ ������� �������)  
 {      
  LCD_Putchar(str[i], x+(i*6*zoom_width), y, t_color, b_color, zoom_width, zoom_height, rot);
  i++;
 }  
}    

//===============================================================
//     ������� ���������� ������� �� ������� ��� ����� ����
//===============================================================
void Send_Symbol_Shadow (unsigned char symbol, char x, char y, int t_color, char zoom_width, char zoom_height) 
{
 unsigned char temp_symbol, a, b, zw, zh, mask; 
 char m, n;
 m=x; 
 n=y;
 if (symbol>127) symbol-=64;    //������� ������������� ����� ������� ASCII
 for ( a = 0; a < 5; a++) //��������� 5 ����, ������������ ������
 {  
  temp_symbol = font_5x8[symbol-32][a];
  zw = 0; 
  while(zw != zoom_width) //����� ����� ����������� zw ��� 
  {    
   n=y;      
   
   mask=0x01;     
   for ( b = 0; b < 8; b++ ) //���� ����������� 8 ��� �����
   {         
    zh = 0; //� zoom_height ��� ���������� ������ �������
    while(zh != zoom_height) //����� ������� ����������� zh ���
    {
    
      if (temp_symbol&mask) 
      {
       Put_Pixel (m+zw, n+zh, t_color);
      }
     
     zh++;
    }
    mask<<=1; //������ ���������� mask �� 1 ��� �����;
    n=n+zoom_height;                   
   }
   zw++;   
  }
   m=m+zoom_width;           
 }
} 

//===============================================================
// ������� ������ ������ ������� ASCII-���� ��� ����� ����
//===============================================================
void LCD_Putchar_Shadow (char symbol, char x, char y, int t_color, char zoom_width, char zoom_height, int rot)
{
 unsigned char m;
 if(zoom_width == 0)   zoom_width = 1;
 if(zoom_height == 0)  zoom_height = 1;
 switch (rot)
 {
  case 0:  //��������� ����� ���� � � � - ����� ������� ���� �������   
  Send_Symbol_Shadow( symbol, x, y, t_color, zoom_width, zoom_height);
  break;
  //================================
  case 90:  
  Send_to_lcd(CMD, 0x36); 
  Send_to_lcd(DAT, 0x60); //��������� ����� ���� � � � - ������ ������� ���� ������� 
  Send_Symbol_Shadow( symbol, x, y, t_color, zoom_width, zoom_height);
  Send_to_lcd(CMD, 0x36); 
  Send_to_lcd(DAT, 0x00);
  break;
  //================================
  case 180:       
  Send_to_lcd(CMD, 0x36); 
  Send_to_lcd(DAT, 0xC0); //��������� ����� ���� � � � - ������ ������ ���� ������� 
  Send_Symbol_Shadow( symbol, x, y, t_color, zoom_width, zoom_height);
  Send_to_lcd(CMD, 0x36); 
  Send_to_lcd(DAT, 0x00);
  break;
  //================================
  case 270: 
  Send_to_lcd(CMD, 0x36); 
  Send_to_lcd(DAT, 0xA0); //��������� ����� ���� � � � - ����� ������ ���� �������  
  Send_Symbol_Shadow( symbol, x, y, t_color, zoom_width, zoom_height);
  Send_to_lcd(CMD, 0x36); 
  Send_to_lcd(DAT, 0x00);
  break;
  //================================
  default:
  Send_to_lcd(CMD, 0x36); 
  Send_to_lcd(DAT, 0x00); //��������� ����� ���� � � � - ����� ������� ���� �������  
  Send_Symbol_Shadow( symbol, x, y, t_color, zoom_width, zoom_height);
  Send_to_lcd(CMD, 0x36); 
  Send_to_lcd(DAT, 0x00);
  //=================================    
 };  
}

//===============================================================
//   ������� ������ ������, ������������� � ram ��� ����� ���� 
//===============================================================
void LCD_Puts_Shadow(char *str, int x, int y,  int t_color, char zoom_width, char zoom_height, int rot)
{
 unsigned char i=0;
                    
 if(zoom_width == 0)   zoom_width = 1;
 if(zoom_height == 0)  zoom_height = 1;
   
 while (str[i]) //x � y - ����� ������� ��������� �������; � ����������� ���������� i ����� ������ ���������� ������� ��������� �� i*6 (��� ������������ ������� �������)  
 {      
  LCD_Putchar_Shadow(str[i], x+(i*6*zoom_width), y, t_color, zoom_width, zoom_height, rot);
  i++;
 }  
}

//===============================================================
// ������� ������ ������, ������������� �� flash ��� ����� ����
//===============================================================
void LCD_Putsf_Shadow(flash char *str, int x, int y,  int t_color, char zoom_width, char zoom_height, int rot)
{
 unsigned char i=0;
           
 if(zoom_width == 0)   zoom_width = 1;
 if(zoom_height == 0)  zoom_height = 1;
   
 while (str[i])   
 {      
  LCD_Putchar_Shadow(str[i], x+(i*6*zoom_width), y, t_color, zoom_width, zoom_height, rot);
  i++;
 }  
} 
   
//===============================================================
//                  ������� ������ ������ 
//===============================================================
void LCD_FillScreen (unsigned int color)
{ 
 unsigned int x; 
 signed char i;
 SetArea( 0, 127, 0, 127 );   //������� ����� ������ 
 LCD_RS = 1;    
 
 //������ - ����� ���� �������
 for (x = 0; x < 16384; x++)  // 16384 - ��� 128 * 128
 {   
  #ifdef _8_BIT_COLOR   //(8-�� ������� �������� ������� (256 ������))
  Send_to_lcd( DAT, color ); //������ - ����� ���� ������� 
  #else         //(16-�� ������� �������� ������� (65536 ������))
  Send_to_lcd( DAT, (color >> 8) ); Send_to_lcd( DAT, color );
  #endif
 }                 
} 

//===============================================================
//                 ������� ������ �����������
//===============================================================
void LCD_Output_image (char x, char y, char width, char height, flash char *img, int rot)
{ 
 unsigned char m;
 switch (rot)
 {
  case 0:  //��������� ����� ���� � � � - ����� ������� ���� �������    
  Send_Image (x, y, width, height, img);
  break;
  //================================
  case 90:   
  Send_to_lcd(CMD, 0x36); 
  Send_to_lcd(DAT, 0x60); //��������� ����� ���� � � � - ������ ������� ���� ������� 
  Send_Image (x, y, width, height, img);
  Send_to_lcd(CMD, 0x36); 
  Send_to_lcd(DAT, 0x00);
  break;
  //================================
  case 180:       
  Send_to_lcd(CMD, 0x36); 
  Send_to_lcd(DAT, 0xC0); //��������� ����� ���� � � � - ������ ������ ���� ������� 
  Send_Image (x, y, width, height, img);
  Send_to_lcd(CMD, 0x36); 
  Send_to_lcd(DAT, 0x00);
  break;
  //================================
  case 270:      
  Send_to_lcd(CMD, 0x36); 
  Send_to_lcd(DAT, 0xA0); //��������� ����� ���� � � � - ����� ������ ���� �������  
  Send_Image (x, y, width, height, img);
  Send_to_lcd(CMD, 0x36); 
  Send_to_lcd(DAT, 0x00);
  break;
  //================================
  default:
  Send_to_lcd(CMD, 0x36); 
  Send_to_lcd(DAT, 0x00); //��������� ����� ���� � � � - ����� ������� ���� �������  
  Send_Image (x, y, width, height, img);
  Send_to_lcd(CMD, 0x36); 
  Send_to_lcd(DAT, 0x00);
  //=================================    
 };
}   

//===============================================================
//          ������� ��� ����������� ������ �����������   
//===============================================================
//����� �������� � Image2Lcd � NokiaImageCreator ������ ����������� �����-������� ������-����.
//x, y - ������ ������� ������ �����������; width � height - ������ � ������ �����������   
void Send_Image (char x, char y, char width, char height, flash char *img)  
{  
 unsigned int idx=0, size_array;  //������ ������� img � �������� ������� �������
 
 Send_to_lcd( CMD, 0x2A );          //������ ������� �� X
 Send_to_lcd( DAT, x );             //���������
 Send_to_lcd( DAT, x+(width-1) );   //��������

 Send_to_lcd( CMD, 0x2B );          //������ ������� �� Y
 Send_to_lcd( DAT, y );             //��������� 
 Send_to_lcd( DAT, y+(height-1) );  //��������

 Send_to_lcd( CMD, 0x2C );  //���������� ������� �� ������ ������ � ������ � �������� �������� ������
 
 size_array= width * height;  //���������� ������ �������
 for (idx = 0; idx < size_array; idx++)  //��������� ������ �������
 { 
  #ifdef _8_BIT_COLOR        
  Send_to_lcd( DAT, *img++ );   //��������������� ������ ������� �� ������� img
  #else                      
  Send_to_lcd( DAT, *img++ ); Send_to_lcd( DAT, *img++ );
  #endif 
 }
} 

#ifdef _GEOMETRICAL
//===============================================================
//                      ���������� �����
//===============================================================
void LCD_DrawLine (char x1, char y1, char x2, char y2, int color)
{ 
 short  x, y, d, dx, dy, i, i1, i2, kx, ky;
 signed char flag;

 dx = x2 - x1;
 dy = y2 - y1;
 if (dx == 0 && dy == 0) Put_Pixel(x1, y1, color);  //�����
 else      //�����
 {
  kx = 1;
  ky = 1;
  if( dx < 0 )
  { 
   dx = -dx; 
   kx = -1; 
  }
  else
  if(dx == 0) kx = 0;
  if(dy < 0)
  { 
   dy = -dy; 
   ky = -1; 
  }
  if(dx < dy)
  { 
   flag = 0; 
   d = dx; 
   dx = dy; 
   dy = d; 
  }
  else flag = 1;
  i1 = dy + dy; 
  d = i1 - dx; 
  i2 = d - dx;
  x = x1; 
  y = y1;

  for(i=0; i < dx; i++)
  {
   Put_Pixel(x, y, color);
   if(flag) x += kx;
   else y += ky;
   if( d < 0 ) d += i1;
   else
   {
    d += i2;
    if(flag) y += ky;
    else x += kx;
   }
  }
  Put_Pixel(x, y, color);
 }
}   
  
//===============================================================
//                     ���������� �����                
//===============================================================
void LCD_DrawRect (char x1, char y1, char width, char height, char size, int color)
{
 unsigned int i;
 char x2=x1+(width-1), y2=y1+(height-1); //�������� ������� ����� �� ���� � � �
 for( i=1; i<=size; i++)   // size - ������� �����
 {
  LCD_DrawLine(x1, y1, x1, y2, color);
  LCD_DrawLine(x2, y1, x2, y2, color);
  LCD_DrawLine(x1, y1, x2, y1, color);
  LCD_DrawLine(x1, y2, x2, y2, color);
  x1++; // ���������� ������� �����, ���� ��� ������
  y1++;
  x2--;
  y2--;
 }
}

//===============================================================
//              ��������� ������������� ������ COLOR
//===============================================================
void LCD_FillRect (char x1, char y1, char width, char height, int color)
{
 unsigned int x, y;
       
 SetArea( x1, x1+(width-1), y1, y1+(height-1) );
 LCD_RS = 1;
 
 y = width * height;           //���������� �������� � ��������������
 for (x = 0; x < y; x++) 
 {   
  #ifdef _8_BIT_COLOR   //(8-�� ������� �������� ������� (256 ������))
  Send_to_lcd( DAT, color ); //������ - ����� ���� ������� 
  #else         //(16-�� ������� �������� ������� (65536 ������))
  Send_to_lcd( DAT, (color >> 8) ); Send_to_lcd( DAT, color );
  #endif
 }   
}  
 
//===============================================================
//                  ���������� ����������
//===============================================================
void LCD_DrawCircle (char xcenter, char ycenter, char rad, int color)
{
 signed char tswitch, x1=0, y1; 
 char d;

 d = ycenter - xcenter;
 y1 = rad;
 tswitch = 3 - 2 * rad;
 while (x1 <= y1) 
 {
  Put_Pixel(xcenter + x1, ycenter + y1, color); 
  Put_Pixel(xcenter + x1, ycenter - y1, color);
  Put_Pixel(xcenter - x1, ycenter + y1, color);   
  Put_Pixel(xcenter - x1, ycenter - y1, color);
  Put_Pixel(ycenter + y1 - d, ycenter + x1, color); 
  Put_Pixel(ycenter + y1 - d, ycenter - x1, color);
  Put_Pixel(ycenter - y1 - d, ycenter + x1, color);
  Put_Pixel(ycenter - y1 - d, ycenter - x1, color);

  if (tswitch < 0) tswitch += (4 * x1 + 6);
  else 
  {
   tswitch += (4 * (x1 - y1) + 10);
   y1--;
  }
  x1++;
 }
}    

//===============================================================
//                 ��������� ���� ������ COLOR
//===============================================================
void LCD_FillCircle (char xcenter, char ycenter, char rad, int color)
{
 signed int x1=0, y1, tswitch; 
 y1 = rad;
 tswitch = 1 - rad;

 do
 {
  LCD_DrawLine(xcenter-x1, ycenter+y1, xcenter+x1, ycenter+y1, color);
  LCD_DrawLine(xcenter-x1, ycenter-y1, xcenter+x1, ycenter-y1, color);
  LCD_DrawLine(xcenter-y1, ycenter+x1, xcenter+y1, ycenter+x1, color);
  LCD_DrawLine(xcenter-y1, ycenter-x1, xcenter+y1, ycenter-x1, color);

  if(tswitch < 0)
  tswitch+= 3 + 2*x1++;
  else
  tswitch+= 5 + 2*(x1++ - y1--);
 } while(x1 <= y1);
}

//===============================================================
//                     ���������� �����������
//===============================================================
void LCD_DrawTriangle(char x1, char y1, char x2, char y2, char x3, char y3, int color)
{
 LCD_DrawLine(x1, y1, x2, y2, color);
 LCD_DrawLine(x3, y3, x1, y1, color);
 LCD_DrawLine(x3, y3, x2, y2, color);  
}

//===============================================================
//              ��������� ����������� ������ COLOR
//===============================================================
void LCD_FillTriangle(char x1, char y1, char x2, char y2, char x3, char y3, int color)
{
 LCD_FillTriangleA(x1, y1, x2, y2, x3, y3, color);
 LCD_FillTriangleA(x3, y3, x1, y1, x2, y2, color);
 LCD_FillTriangleA(x3, y3, x2, y2, x1, y1, color);
}    

//===============================================================
void LCD_FillTriangleA(char x1, char y1, char x2, char y2, char x3, char y3, int color)
{
 signed long x, y, addx, dx, dy;
 signed long P;
 int i;
 long a1,a2,b1,b2;
 if(y1>y2)  {b1=y2; b2=y1; a1=x2; a2=x1;}
 else       {b1=y1; b2=y2; a1=x1; a2=x2;}
 dx = a2 -a1;
 dy = b2 - b1;
 if(dx<0)dx=-dx;
 if(dy<0)dy=-dy;
 x = a1;
 y = b1;
   
 if(a1 > a2)    addx = -1;
 else           addx = 1;
   
 if(dx >= dy)
 {
  P = 2*dy - dx;
  for(i=0; i<=dx; ++i)
  {
   LCD_DrawLine((int)x, (int)y, x3, y3, color);
   if(P < 0)
   {
    P += 2*dy;
    x += addx;
   }
   else
   {
    P += 2*dy - 2*dx;
    x += addx;
    y ++;
   }
  }
 }
 else
 {
  P = 2*dx - dy;
  for(i=0; i<=dy; ++i)
  {
   LCD_DrawLine((int)x, (int)y, x3, y3, color);
   if(P < 0)
   {
    P += 2*dx;
    y ++;
   }
   else
   {
    P += 2*dx - 2*dy;
    x += addx;
    y ++;
   }
  }
 }
}

//===============================================================
#endif


    
