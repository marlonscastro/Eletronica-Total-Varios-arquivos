#define cs        PIN_d2 // 
#define reset     PIN_d3 // 
#define rs        PIN_c4 // 
#define clk       PIN_c5 // 
#define data      PIN_c6 //

void Reset_LCD(void){
  delay_us(10);
  output_low(data);
  output_low(clk);  
  output_low(rs);
  delay_us(10);
  output_high(reset);
  delay_us(10);
  output_low(cs);
  delay_us(10);
  output_low(reset);
  delay_us(10);  
  output_high(reset);
  output_high(cs);
}


// ------------------------------------------------------------------
// command to display
// ------------------------------------------------------------------
void SendCommand(BYTE Command)
{
BYTE i,s;

  s=0x80;

  output_low(data);
  output_low(clk);
  output_low(rs);
  output_low(cs);
  delay_us(10);
  for (i=0; i<8; i++) 
  {
    if (Command & s) { output_high(data); } 
    else             { output_low(data); }
    s = s>>1;
    delay_us(10);
    output_high(clk);
    delay_us(10);
    output_low(clk);;
    delay_us(10);
  }
  output_high(cs);
}


// ------------------------------------------------------------------
//
// ------------------------------------------------------------------
void Init_LCD(void)
{
  /*Reset_LCD();
  SendCommand(0b00100001);    // Function set: chip is active, horizontal addressing, use extended instruction set
  SendCommand(0b11011010);    // 
  SendCommand(0b00010100);    // Display control: ?    
  SendCommand(0b00001011);    // Set voltage multiplier factor -> ok
  SendCommand(0b00000101);    // Temperature controlVLCD temperature coefficient 1
  SendCommand((128+80));      // contrast
  SendCommand(0b00100000);    // Function set
  SendCommand(0b00010001);    // VLCD programming range: high
  SendCommand(0b00001100);    // Display control: normal */
//    SendCommand(0b00001101);    // Display control: inverse -> ok
   SendCommand( 0x21 ); /* LCD Extended Commands. */
   SendCommand( 0xCF ); /* Set LCD Vop (Contrast).*/
   SendCommand( 0x06 ); /* Set Temp coefficent. */
   SendCommand( 0x13 ); /* LCD bias mode 1:48. */
   SendCommand( 0x28 ); /* LCD Standard Commands,Horizontal addressing mode */
   SendCommand( 0x0C ); /* LCD in normal mode. */
}   


// ------------------------------------------------------------------
// Line: 0..7, Row 0..100;
// ------------------------------------------------------------------
void GotoLineRow(BYTE Line, BYTE Row)
{
  SendCommand( 0b00101000);
  SendCommand((0b01000000 + Line));
  SendCommand((0b10000000 + Row ));
}


// ------------------------------------------------------------------
// data to display
// ------------------------------------------------------------------
void SendData(BYTE Value){          
  BYTE i,s;

  s=0x80;
  output_low(data);
  output_low(clk);;
  output_high(rs);
  output_low(cs);

  delay_us(10);
  for (i=0; i<8; i++) 
  {
    if (Value & s) { output_high(data); } 
    else           { output_low(data); }
    s = s>>1;
    delay_us(10);
    output_high(clk);
    delay_us(10);
    output_low(clk);;
    delay_us(10);
  }
  output_high(cs);
}


// ------------------------------------------------------------------
