#include <18F4550.h>
#use delay(clock=48000000)
//#fuses HS, PUT, NOWDT, NOBROWNOUT, NOLVP
#fuses HSPLL, PLL4, CPUDIV1, PUT, NOWDT, NOBROWNOUT, NOLVP

#include "HMF6598SYH-PY.c"
#include "i2cEEprom.c"

/*

#ifndef EEPROM_SDA

#define EEPROM_SDA  PIN_C4
#define EEPROM_SCL  PIN_C3

#endif


#use i2c(master, sda=EEPROM_SDA, scl=EEPROM_SCL)

#define EEPROM_ADDRESS long int
#define EEPROM_SIZE    512

void init_ext_eeprom() {
   output_float(EEPROM_SCL);
   output_float(EEPROM_SDA);
}

BOOLEAN ext_eeprom_ready() {
   int1 ack;
   i2c_start();            // If the write command is acknowledged,
   ack = i2c_write(0xa0);  // then the device is ready.
   i2c_stop();
   return !ack;
}

void write_ext_eeprom(long int address, BYTE data) {
   while(!ext_eeprom_ready());
   i2c_start();
   i2c_write((0xa0|(BYTE)(address>>7))&0xfe);
   i2c_write(address);
   i2c_write(data);
   i2c_stop();
}


BYTE read_ext_eeprom(long int address) {
   BYTE data;

   while(!ext_eeprom_ready());
   i2c_start();
   i2c_write((0xa0|(BYTE)(address>>7))&0xfe);
   i2c_write(address);
   i2c_start();
   i2c_write((0xa0|(BYTE)(address>>7))|1);
   data=i2c_read(0);
   i2c_stop();
   return(data);
}

*/
// ===========================================================================

#define I2CWRITE     0b00000000
#define I2CREAD      0b00000001 

int i2c_addr_mask(int device_addr) {
   /* xxxxxIJK --> 00000IJK, then 00000IJK --> 0000IJK0 */
   return((device_addr & 0x07)<<1);
}

// routines for 24cXX eeproms with 16bit address support (e.g. 24C64)

#define EEPROM_24CXX 0b10100000

int i2c_24cXX_eeprom_read(int device_addr, int addrlen, int16 memory_addr) {
   int data;
   int addr_mask;
   addr_mask=i2c_addr_mask(device_addr);
   i2c_start();
   i2c_write(EEPROM_24CXX | addr_mask | I2CWRITE); // mode is write
      if (addrlen==ADDR_LEN_16) {
      i2c_write(make8(memory_addr,1));
      i2c_write(make8(memory_addr,0));
      }
   else
      i2c_write((int)memory_addr);     // address of memory to read from
   i2c_start();                        // repeated start
   i2c_write(EEPROM_24CXX | addr_mask | I2CREAD); // mode is read
   data=i2c_read(0);                   // read the data, No Ack the read
   i2c_stop();
   return(data);
}


int i2c_24cXX_eeprom_write(int device_addr, int addrlen, int16 memory_addr, int memory_val) {
   int data;
   int addr_mask;
   addr_mask=i2c_addr_mask(device_addr);
   i2c_start();
   i2c_write(EEPROM_24CXX | addr_mask | I2CWRITE); // mode is write
   if (addrlen==ADDR_LEN_16) {
      i2c_write(make8(memory_addr,1));
      i2c_write(make8(memory_addr,0));
      }
   else
      i2c_write((int)memory_addr);
   i2c_write(memory_val);
   i2c_stop();
   if (addrlen==ADDR_LEN_16) // only for rev B process parts!  see ST data sheet,
      delay_ms(5);           // http://us.st.com/stonline/books/pdf/docs/4578.pdf
   else
      delay_ms(10);  // enforced delay for writing
   return(i2c_24cXX_eeprom_read(addrlen,device_addr,memory_addr));
}




// ===========================================================================

void main(void){
   HMF6598_InitLcd();
   Write_i2cEeprom(0x00, 0xff);
   while(true){}
   /*int i;

   printf(HMF6598_Printchar, "ABCDEFGHIJKLMNOPQRST;");
   HMF6598_Gotoxy(0,1);
   printf(HMF6598_Printchar, "UVWXYZ:,.'~^1234567"); 
   HMF6598_Gotoxy(0,2);
   printf(HMF6598_Printchar, "890!@#$/\&*()=-+[]{}\"");       
   HMF6598_Gotoxy(0,3);
   printf(HMF6598_Printchar, "abcdefghijklmnopqrst");     
   HMF6598_Gotoxy(0,4);
   printf(HMF6598_Printchar, "uvwxyz_");     
   HMF6598_Gotoxy(0,7);
   printf(HMF6598_Printchar, "Total Electronics!"); 

   for(i=0;i<128;i++){
      HMF6598_PutPixel(i,60,ON);
      delay_ms(50);
   }
   HMF6598_circle(64, 32, 30, OFF, ON);   */
}
