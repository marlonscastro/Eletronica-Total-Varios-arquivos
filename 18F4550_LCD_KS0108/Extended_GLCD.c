
#define GLCD_CS1 PIN_B3    // Chip Selection 1
#define GLCD_CS2 PIN_B4    // Chip Selection 2
#define GLCD_DI  PIN_B0    // Data or Instruction input
#define GLCD_RW  PIN_B1    // Read/Write
#define GLCD_E   PIN_B2    // Enable
#define GLCD_RST PIN_C0    // Reset
#define DATAIN   INPUT_D   // Data input port  (Should be same port as DATAOUT)
#define DATAOUT  OUTPUT_D  // Data output port (Should be same port as DATAIN)

#define GLCD_WIDTH 128     // Used for text wrapping by glcd_text57 function

#define ON  1
#define OFF 0

#define YES 1
#define NO  0

BYTE glcd_readByte(BYTE chip);
void glcd_writeByte(BYTE chip, BYTE data);
void glcd_fillScreen(int1 color);

void    KS0108_Gotoxy(int x, int y);

const BYTE TEXT[51][5] ={0x00, 0x00, 0x00, 0x00, 0x00, // SPACE
                         0x00, 0x00, 0x5F, 0x00, 0x00, // !
                         0x00, 0x03, 0x00, 0x03, 0x00, // "
                         0x14, 0x3E, 0x14, 0x3E, 0x14, // #
                         0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
                         0x43, 0x33, 0x08, 0x66, 0x61, // %
                         0x36, 0x49, 0x55, 0x22, 0x50, // &
                         0x00, 0x05, 0x03, 0x00, 0x00, // '
                         0x00, 0x1C, 0x22, 0x41, 0x00, // (
                         0x00, 0x41, 0x22, 0x1C, 0x00, // )
                         0x14, 0x08, 0x3E, 0x08, 0x14, // *
                         0x08, 0x08, 0x3E, 0x08, 0x08, // +
                         0x00, 0x50, 0x30, 0x00, 0x00, // ,
                         0x08, 0x08, 0x08, 0x08, 0x08, // -
                         0x00, 0x60, 0x60, 0x00, 0x00, // .
                         0x20, 0x10, 0x08, 0x04, 0x02, // /
                         0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
                         0x04, 0x02, 0x7F, 0x00, 0x00, // 1
                         0x42, 0x61, 0x51, 0x49, 0x46, // 2
                         0x22, 0x41, 0x49, 0x49, 0x36, // 3
                         0x18, 0x14, 0x12, 0x7F, 0x10, // 4
                         0x27, 0x45, 0x45, 0x45, 0x39, // 5
                         0x3E, 0x49, 0x49, 0x49, 0x32, // 6
                         0x01, 0x01, 0x71, 0x09, 0x07, // 7
                         0x36, 0x49, 0x49, 0x49, 0x36, // 8
                         0x26, 0x49, 0x49, 0x49, 0x3E, // 9
                         0x00, 0x36, 0x36, 0x00, 0x00, // :
                         0x00, 0x56, 0x36, 0x00, 0x00, // ;
                         0x08, 0x14, 0x22, 0x41, 0x00, // <
                         0x14, 0x14, 0x14, 0x14, 0x14, // =
                         0x00, 0x41, 0x22, 0x14, 0x08, // >
                         0x02, 0x01, 0x51, 0x09, 0x06, // ?
                         0x3E, 0x41, 0x59, 0x55, 0x5E, // @
                         0x7E, 0x09, 0x09, 0x09, 0x7E, // A
                         0x7F, 0x49, 0x49, 0x49, 0x36, // B
                         0x3E, 0x41, 0x41, 0x41, 0x22, // C
                         0x7F, 0x41, 0x41, 0x41, 0x3E, // D
                         0x7F, 0x49, 0x49, 0x49, 0x41, // E
                         0x7F, 0x09, 0x09, 0x09, 0x01, // F
                         0x3E, 0x41, 0x41, 0x49, 0x3A, // G
                         0x7F, 0x08, 0x08, 0x08, 0x7F, // H
                         0x00, 0x41, 0x7F, 0x41, 0x00, // I
                         0x30, 0x40, 0x40, 0x40, 0x3F, // J
                         0x7F, 0x08, 0x14, 0x22, 0x41, // K
                         0x7F, 0x40, 0x40, 0x40, 0x40, // L
                         0x7F, 0x02, 0x0C, 0x02, 0x7F, // M
                         0x7F, 0x02, 0x04, 0x08, 0x7F, // N
                         0x3E, 0x41, 0x41, 0x41, 0x3E, // O
                         0x7F, 0x09, 0x09, 0x09, 0x06, // P
                         0x1E, 0x21, 0x21, 0x21, 0x5E, // Q
                         0x7F, 0x09, 0x09, 0x09, 0x76};// R

const BYTE TEXT2[44][5]={0x26, 0x49, 0x49, 0x49, 0x32, // S
                         0x01, 0x01, 0x7F, 0x01, 0x01, // T
                         0x3F, 0x40, 0x40, 0x40, 0x3F, // U
                         0x1F, 0x20, 0x40, 0x20, 0x1F, // V
                         0x7F, 0x20, 0x10, 0x20, 0x7F, // W
                         0x41, 0x22, 0x1C, 0x22, 0x41, // X
                         0x07, 0x08, 0x70, 0x08, 0x07, // Y
                         0x61, 0x51, 0x49, 0x45, 0x43, // Z
                         0x00, 0x7F, 0x41, 0x00, 0x00, // [
                         0x02, 0x04, 0x08, 0x10, 0x20, // \
                         0x00, 0x00, 0x41, 0x7F, 0x00, // ]
                         0x04, 0x02, 0x01, 0x02, 0x04, // ^
                         0x40, 0x40, 0x40, 0x40, 0x40, // _
                         0x00, 0x01, 0x02, 0x04, 0x00, // `
                         0x20, 0x54, 0x54, 0x54, 0x78, // a
                         0x7F, 0x44, 0x44, 0x44, 0x38, // b
                         0x38, 0x44, 0x44, 0x44, 0x44, // c
                         0x38, 0x44, 0x44, 0x44, 0x7F, // d
                         0x38, 0x54, 0x54, 0x54, 0x18, // e
                         0x04, 0x04, 0x7E, 0x05, 0x05, // f
                         0x08, 0x54, 0x54, 0x54, 0x3C, // g
                         0x7F, 0x08, 0x04, 0x04, 0x78, // h
                         0x00, 0x44, 0x7D, 0x40, 0x00, // i
                         0x20, 0x40, 0x44, 0x3D, 0x00, // j
                         0x7F, 0x10, 0x28, 0x44, 0x00, // k
                         0x00, 0x41, 0x7F, 0x40, 0x00, // l
                         0x7C, 0x04, 0x78, 0x04, 0x78, // m
                         0x7C, 0x08, 0x04, 0x04, 0x78, // n
                         0x38, 0x44, 0x44, 0x44, 0x38, // o
                         0x7C, 0x14, 0x14, 0x14, 0x08, // p
                         0x08, 0x14, 0x14, 0x14, 0x7C, // q
                         0x00, 0x7C, 0x08, 0x04, 0x04, // r
                         0x48, 0x54, 0x54, 0x54, 0x20, // s
                         0x04, 0x04, 0x3F, 0x44, 0x44, // t
                         0x3C, 0x40, 0x40, 0x20, 0x7C, // u
                         0x1C, 0x20, 0x40, 0x20, 0x1C, // v
                         0x3C, 0x40, 0x30, 0x40, 0x3C, // w
                         0x44, 0x28, 0x10, 0x28, 0x44, // x
                         0x0C, 0x50, 0x50, 0x50, 0x3C, // y
                         0x44, 0x64, 0x54, 0x4C, 0x44, // z
                         0x00, 0x08, 0x36, 0x41, 0x41, // {
                         0x00, 0x00, 0x7F, 0x00, 0x00, // |
                         0x41, 0x41, 0x36, 0x08, 0x00, // }
                         0x02, 0x01, 0x02, 0x04, 0x02};// ~


//****************************************************************************//
// Purpose:       Initialize a graphic LCD. This must be called before any    //
//                other glcd function is used.                                //
// Inputs:        The initialization mode                                     //
//                OFF - Turns the LCD off                                     //
//                ON  - Turns the LCD on                                      //
//****************************************************************************//
void glcd_init(int1 mode){
   // Initialze some pins
   output_high(GLCD_RST);
   output_low(GLCD_E);
   output_low(GLCD_CS1);
   output_low(GLCD_CS2);
   
   output_low(GLCD_DI);                // Set for instruction
   glcd_writeByte(GLCD_CS1, 0xF8);     // Specify first RAM line at the top
   glcd_writeByte(GLCD_CS2, 0xF8);     //  of the screen
   
   if(mode == ON)
   {
      glcd_writeByte(GLCD_CS1, 0x3F);  // Turn the display on
      glcd_writeByte(GLCD_CS2, 0x3F);
   }
   else
   {
      glcd_writeByte(GLCD_CS1, 0x3E);  // Turn the display off
      glcd_writeByte(GLCD_CS2, 0x3E);
   }   
   glcd_writeByte(GLCD_CS1, 0x40);     // Set the column address to 0
   glcd_writeByte(GLCD_CS2, 0x40);
   glcd_writeByte(GLCD_CS1, 0xB7);     // Set the page address to 0
   glcd_writeByte(GLCD_CS2, 0xB7);
   output_high(GLCD_DI);   
   glcd_fillScreen(OFF);               // Clear the display
}
//****************************************************************************//
// Purpose:       Write a byte of data to the specified chip                  //
// Inputs:        chipSelect - which chip to write the data to                //
//                data - the byte of data to write                            //
//****************************************************************************//

void glcd_writeByte(char chip, BYTE data){
   if(chip == GLCD_CS1)       // Choose which chip to write to
      output_high(GLCD_CS1);
   else
      output_high(GLCD_CS2);
   
   output_low(GLCD_E);
   output_low(GLCD_RW);   
   delay_us(1);
   output_high(GLCD_E);
   DATAOUT(data);       
   output_low(GLCD_E);

   output_low(GLCD_CS1);      
   output_low(GLCD_CS2);   
}

//****************************************************************************//
// Purpose:       Reads a byte of data from the specified chip                //
// Ouputs:        A byte of data read from the chip                           //
//****************************************************************************//
BYTE glcd_readByte(BYTE chip){
   BYTE data;                 // Stores the data read from the LCD
   if(chip == GLCD_CS1)       // Choose which chip to read from
      output_high(GLCD_CS1);
   else
      output_high(GLCD_CS2);

   DATAIN();                  // Set port d to input
   output_high(GLCD_RW);      // Set for reading
   output_high(GLCD_E);       // Pulse the enable pin
   delay_us(2);
   output_low(GLCD_E);
   delay_us(2);
   output_high(GLCD_E);       // Pulse the enable pin
   delay_us(2);
   data = DATAIN();          // Get the data from the display's output register
   output_low(GLCD_E);

   output_low(GLCD_CS1);      // Reset the chip select lines
   output_low(GLCD_CS2);
   return data;               // Return the read data
}

//****************************************************************************//
// Purpose:       Turns ON-OFF graphic LCD. Good solution on system standby   //
//                GLCD does not clear its memory map on OFF command. So last  //
//                screen shows up when ON command send to GLCD                //
// Inputs:        OFF - Turns the LCD off                                     //
//                ON  - Turns the LCD on                                      //
//****************************************************************************//
void glcd_standby(int1 command){  
   output_low(GLCD_E);
   output_low(GLCD_CS1);
   output_low(GLCD_CS2);
   output_low(GLCD_DI);
   if (command)
   {   
      glcd_writeByte(GLCD_CS1,0x3F);
      glcd_writeByte(GLCD_CS2,0x3F);
   }
   else
   {
      glcd_writeByte(GLCD_CS1,0x3E);
      glcd_writeByte(GLCD_CS2,0x3E);   
   }
}

//****************************************************************************//
// Purpose:       Turn a pixel on a graphic LCD on or off                     //
// Inputs:        x - the x coordinate of the pixel                           //
//                y - the y coordinate of the pixel                           //
//                color - ON or OFF                                           //
// Output:        1 if coordinate out of range, 0 if in range                 //
//****************************************************************************//
void glcd_pixel(int x, int y, int1 color){
   BYTE data;
   BYTE chip = GLCD_CS1;  // Stores which chip to use on the LCD

   if(x > 63){     // Check for first or second display area
      x -= 64;
      chip = GLCD_CS2;
   }
   output_low(GLCD_DI);                                     // Set for instruction
   bit_clear(x,7);                                          // Clear the MSB. Part of an instruction code
   bit_set(x,6);                                            // Set bit 6. Also part of an instruction code
   glcd_writeByte(chip, x);                                 // Set the horizontal address
   glcd_writeByte(chip, (y/8 & 0b10111111) | 0b10111000);   // Set the vertical page address
   output_high(GLCD_DI);                                    // Set for data
   data = glcd_readByte(chip);

   if(color == ON)
      bit_set(data, y%8);        // Turn the pixel on
   else                          // or
      bit_clear(data, y%8);      // turn the pixel off
   output_low(GLCD_DI);          // Set for instruction
   glcd_writeByte(chip, x);      // Set the horizontal address
   output_high(GLCD_DI);         // Set for data
   glcd_writeByte(chip, data);   // Write the pixel data
}

//****************************************************************************//
// Purpose:       Fill the LCD screen with the passed in color                //
// Inputs:        ON - turn all the pixels on                                 //
//                OFF - turn all the pixels off                               //
// Dependencies:  glcd_writeByte()                                            //
//****************************************************************************//
void glcd_fillScreen(int1 color){
   int i, j;

   // Loop through the vertical pages
   for(i = 0; i < 8; ++i)
   {
      output_low(GLCD_DI);                      // Set for instruction
      glcd_writeByte(GLCD_CS1, 0b01000000);     // Set horizontal address to 0
      glcd_writeByte(GLCD_CS2, 0b01000000);
      glcd_writeByte(GLCD_CS1, i | 0b10111000); // Set page address
      glcd_writeByte(GLCD_CS2, i | 0b10111000);
      output_high(GLCD_DI);                     // Set for data

      // Loop through the horizontal sections
      for(j = 0; j < 64; ++j)
      {
         glcd_writeByte(GLCD_CS1, 0xFF*color);  // Turn pixels on or off
         glcd_writeByte(GLCD_CS2, 0xFF*color);  // Turn pixels on or off
      }
   }
}

// =========================================================== //
void    KS0108_Printchar(char cvar){
   int i;
   if(cvar == 0x20)
      for(i=0;i<2;i++){
         glcd_writeByte(GLCD_CS1, 0x00);
         glcd_writeByte(GLCD_CS2, 0x00);         
      }
   else{
      for(i=0;i<5;i++){
         if (cvar < 0x53){
            if(TEXT[cvar-0x20][i]){        
               glcd_writeByte(GLCD_CS1, TEXT[cvar-0x20][i]);         
               glcd_writeByte(GLCD_CS2, TEXT[cvar-0x20][i]);                        
            }
         }
         else {
            if(TEXT2[cvar-0x53][i]){               
               glcd_writeByte(GLCD_CS1, TEXT2[cvar-0x53][i]);            
               glcd_writeByte(GLCD_CS2, TEXT2[cvar-0x53][i]);            
            }
         }
      }
   }
   glcd_writeByte(GLCD_CS1, 0x00);               
   glcd_writeByte(GLCD_CS2, 0x00); 
}

void KS0108_PutPixel(int x, int y, int1 COLOR){
   char BytePlot = 0, tempByte;
   if((x > 127)||(y > 63))
      return;
   BytePlot |= 1;
   BytePlot<<=(y%8);
   tempByte = BytePlot;
   KS0108_Gotoxy(x,(y/8));
   BytePlot|=glcd_readByte(GLCD_CS1);
   if(COLOR == OFF)
      BytePlot-=tempByte;
   glcd_writeByte(GLCD_CS1, BytePlot);
}

void KS0108_Gotoxy(int x, int y){
   output_low(GLCD_DI);
   glcd_writeByte(GLCD_CS1, 0x40 + x);
   glcd_writeByte(GLCD_CS2, 0x40 + x);
   glcd_writeByte(GLCD_CS1, 0xB7 + y);
   glcd_writeByte(GLCD_CS2, 0xB7 + y);   
   output_high(GLCD_DI);   
}


