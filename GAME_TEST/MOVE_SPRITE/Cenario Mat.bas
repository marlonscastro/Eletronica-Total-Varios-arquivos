const BYTE cenario[8][128] = 
{
0x00,0x00,0x80,0xC0,0x40,0x70,0x0C,0x04,
0x04,0x04,0x04,0x0C,0x18,0x38,0x0C,0x04,
0x04,0x04,0x04,0x0C,0x18,0x18,0x0C,0x04,
0x04,0x04,0x0C,0x08,0x08,0x18,0xF0,0xE0,
0x00,0x00,0x00,0x00,0x00,0x78,0xCC,0x8C,
0x84,0x84,0x04,0x0C,0x18,0x0C,0x84,0x84,
0xC4,0x44,0x74,0x18,0x00,0x00,0x00,0x00,
0x00,0x00,0x10,0x28,0x24,0x24,0x18,0x00,
0x00,0x00,0x00,0x00,0x20,0xFC,0x84,0x04,
0x06,0x0E,0x12,0x02,0x02,0x02,0x04,0x08,
0x08,0x08,0x88,0xCC,0x64,0x44,0xC4,0x84,
0x84,0x84,0x8C,0x82,0x82,0x82,0x82,0x42,
0x42,0x66,0x3C,0x00,0x00,0x00,0x00,0x00,
0x00,0x38,0xEC,0x84,0x02,0x02,0x01,0x01,
0x01,0x02,0x04,0x04,0x04,0x08,0x98,0x10,
0x08,0x08,0x84,0x84,0xC4,0x44,0x6C,0x30,
0x00,0x00,0x07,0x0E,0x18,0x18,0x18,0x1C,
0x1C,0x0F,0x08,0x18,0x10,0x10,0x10,0x10,
0x10,0x18,0x0F,0x03,0x0C,0x08,0x08,0x0C,
0x0C,0x0C,0x0C,0x0C,0x06,0x07,0x07,0x03,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
0x03,0x02,0x06,0x04,0x04,0x04,0x04,0x06,
0x02,0x03,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0x03,0x02,0x02,0x06,
0x04,0x04,0x04,0x02,0x03,0x01,0x01,0x03,
0x06,0x04,0x08,0x08,0x05,0x03,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x10,0x10,0x10,0xF0,0x90,0x10,
0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,
0xFF,0xFF,0x01,0x01,0x19,0x01,0x01,0x01,
0x01,0x01,0x01,0x39,0x01,0x01,0x01,0xFF,
0x00,0x00,0x10,0x10,0xF8,0x10,0x10,0x10,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFF,0x01,0x01,0x19,0x19,0x01,0x01,0x01,
0x01,0x19,0x01,0xFF,0x00,0x00,0x00,0x00,
0xE0,0x20,0x3F,0x21,0x21,0x21,0x21,0x3F,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xE0,0xE2,0x22,0x3E,0xA3,0xE2,
0x22,0x20,0x24,0xFC,0x24,0x64,0x60,0xE0,
0xE0,0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xB8,
0xAC,0xA6,0xEB,0xB5,0x9C,0x87,0x80,0x80,
0xFF,0xFF,0x00,0x00,0x18,0x00,0x00,0x00,
0x00,0x00,0x04,0x3C,0x00,0x00,0x00,0xFF,
0xFF,0x01,0x19,0x19,0x01,0x01,0x01,0x01,
0x01,0x01,0x19,0x19,0x01,0x01,0x01,0xFF,
0x00,0x00,0x20,0x30,0x70,0xF0,0x18,0x08,
0x00,0x01,0x03,0x0E,0x7E,0xCC,0x00,0x00,
0xFF,0x00,0x00,0xC3,0xC3,0x00,0x00,0x00,
0x00,0xC3,0x00,0xFF,0xFC,0x04,0x04,0x04,
0x87,0x84,0x04,0x1C,0x04,0x04,0x84,0x84,
0x07,0x04,0x04,0x1C,0x04,0x84,0x04,0x04,
0x04,0x04,0xFF,0xFF,0x00,0xF0,0x1F,0x00,
0x00,0xFC,0x03,0x01,0x00,0x00,0x00,0x00,
0x01,0x0F,0xFF,0x00,0x00,0x80,0x80,0xC0,
0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFF,0x00,0x00,0x0C,0x0C,0x00,0x00,0x08,
0x08,0x08,0x00,0x00,0x1C,0x00,0x00,0x00,
0xFF,0xFF,0x00,0x00,0x0C,0x0C,0x00,0x00,
0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0xFF,
0xFF,0x00,0x86,0x86,0x00,0x00,0x00,0x00,
0x00,0x00,0x83,0x83,0x00,0x00,0x00,0xFF,
0xFF,0x01,0x01,0x11,0x11,0x01,0x01,0x01,
0x01,0x01,0x11,0x11,0x01,0x01,0x01,0xFF,
0xFF,0x00,0x00,0x30,0x30,0x00,0x00,0x00,
0x00,0x30,0x00,0xFF,0xFF,0x00,0x00,0x00,
0x31,0x31,0x00,0x00,0x00,0x00,0x31,0x31,
0x00,0x00,0x00,0x00,0x00,0x71,0x00,0x00,
0x00,0x00,0xFF,0xFF,0x00,0x00,0x0F,0x30,
0xE0,0x00,0x03,0x0C,0x30,0x60,0x80,0x00,
0x00,0x00,0xFF,0xF0,0x13,0x11,0x91,0x97,
0x1C,0x10,0x10,0x13,0x9C,0x14,0x10,0xF0,
0xFF,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00,
0x04,0x04,0x00,0x00,0x0F,0x00,0x00,0x00,
0xFF,0xFF,0x00,0x00,0xC7,0xC7,0x00,0x00,
0x00,0x00,0x00,0x43,0xC0,0x00,0x00,0xFF,
0xFF,0x00,0x61,0x61,0x00,0x00,0x00,0x00,
0x00,0x00,0x61,0x61,0x00,0x00,0x00,0xFF,
0xFF,0x00,0x00,0x04,0x04,0x00,0x00,0x00,
0x00,0x00,0x04,0x04,0x00,0x00,0x00,0xFF,
0xFF,0x00,0x00,0x0C,0x0C,0x00,0x00,0x00,
0x00,0x0C,0x00,0xFF,0xFF,0x00,0x00,0x00,
0x1C,0x1C,0x00,0x00,0x00,0x00,0x1C,0x1C,
0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,
0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,
0xE1,0x1F,0x00,0x00,0x00,0x00,0x01,0x0F,
0xF8,0x00,0xFF,0xFF,0x00,0x00,0xE3,0xE3,
0x00,0x00,0x00,0x00,0xE3,0x00,0x00,0xFF,
0xFF,0x00,0x00,0x8F,0x8F,0x00,0x00,0x04,
0x04,0x04,0x00,0x00,0x1F,0x00,0x00,0x00,
0xFF,0xFF,0x00,0x00,0x30,0x30,0x00,0x00,
0x00,0x00,0x00,0x00,0x73,0x00,0x00,0xFF,
0xFF,0x80,0x8C,0x8C,0x80,0x80,0xC0,0xC0,
0xC0,0x80,0x8C,0x8C,0x80,0x80,0x80,0xFF,
0xFF,0x80,0x80,0x82,0x82,0x80,0xC0,0xC0,
0xC0,0xC0,0x82,0x82,0x80,0x80,0x80,0xFF,
0xFF,0x80,0x80,0x83,0x83,0x80,0x80,0x80,
0x80,0x83,0x80,0xFF,0xFF,0x80,0x80,0x80,
0x8E,0xCE,0xC0,0xC0,0xC0,0xC0,0xCE,0xCE,
0xC0,0xC0,0xC0,0xC0,0xC0,0x8E,0x80,0x80,
0x80,0x80,0xFF,0xFF,0x80,0x80,0x80,0xC0,
0xBF,0x80,0x80,0x80,0x80,0xA0,0xB0,0x9C,
0x87,0x80,0xFF,0xFF,0x80,0x80,0x98,0x98,
0x80,0x80,0x80,0x80,0x98,0x80,0x80,0xFF,
0xFF,0x80,0x80,0x87,0x87,0x80,0x80,0x82,
0x82,0x82,0x80,0x80,0x87,0x80,0x80,0x80,
0xFF,0xFF,0x80,0x80,0x86,0x86,0x80,0x80,
0x80,0x80,0x80,0x80,0x86,0x80,0x80,0xFF};

