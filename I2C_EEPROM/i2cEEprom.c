void SerialWrite(int byte_data);
void Write_i2cEeprom(int16 Addr, char data);
int8 SerialRead(int16 Addr);
int8 Read_i2cEeprom(int16 Addr);
void Communication(int1 Condition);

#define SDA    pin_D0
#define SCL    pin_D1

#define START  1
#define STOP   0

void Communication(int1 Condition){
   output_high(SCL);
   if(Condition == START){
      output_high(SDA);
      delay_us(5);
      output_low(SDA);
      delay_us(5);      
   }
   else{
      output_low(SDA);
      delay_us(5);;      
      output_high(SDA);      
      delay_us(5);      
   }
   output_low(SCL);   
}
int8 Read_i2cEeprom(int16 Addr){
   Communication(START);
   SerialWrite(0xA0|(Addr<<9));   // 1010-0000 |   Write
   SerialWrite(0x00|Addr);
   SerialWrite(0xA1|(Addr<<9));   // 1010-0001 |   Read 
   return SerialRead(Addr);
   Communication(STOP);   
   delay_ms(5);   
}
void Write_i2cEeprom(int16 Addr, char data){
   Communication(START);
   SerialWrite(0xA0|(Addr<<9));   // 1010-0000 | 
   SerialWrite(0x00|Addr);
   SerialWrite(data); 
   Communication(STOP);
   delay_ms(8);
}
int8 SerialRead(int16 Addr){
   int i = 9;
   BYTE byte_lido = 0x00;
   while(i>0){
      output_low(SCL);
      delay_us(4);      
      if((i==1) && (input(SDA))){
      }
        // i = 9;
      else{
         if(!input(SDA))
            byte_lido<<=1;
         else{
            byte_lido<<=1;
            byte_lido|=0x01;
         }
      }
      output_high(SCL);      
      delay_us(5);      
      i--;      
   }
   return byte_lido;
}
void SerialWrite(int byte_data){
   int i = 9;
   while(i>0){
      output_low(SCL);
      delay_us(5);
      if((i==1) && (input(SDA))){
         //i = 9;
         HMF6598_Gotoxy(0,5);
         printf(HMF6598_Printchar, "Write error!");
      }
      else{
         if((byte_data&0x80)==0)
            output_low(SDA);
         else
            output_high(SDA);
      }  
      output_high(SCL);      
      delay_us(5);      
      i--;
   }
}

