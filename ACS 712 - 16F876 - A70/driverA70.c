#include <string.h>

#define sce       PIN_c0 //
#define rst       PIN_c1 // 
#define dc        PIN_a5 // 
#define sclk      PIN_c3 // 
#define sda       PIN_c5 //

BYTE const font8x12[128][12] = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,        // sp        0x20 1
  0x00,0x30,0x78,0x78,0x78,0x30,0x30,0x00,0x30,0x30,0x00,0x00,        // !         0x21 2
  0x00,0x66,0x66,0x66,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,        // "         0x22 3
  0x00,0x6C,0x6C,0xFE,0x6C,0x6C,0x6C,0xFE,0x6C,0x6C,0x00,0x00,        // #         0x23 4
  0x30,0x30,0x7C,0xC0,0xC0,0x78,0x0C,0x0C,0xF8,0x30,0x30,0x00,        // $         0x24 5
  0x00,0x00,0x00,0xC4,0xCC,0x18,0x30,0x60,0xCC,0x8C,0x00,0x00,        // %         0x25 6
  0x00,0x70,0xD8,0xD8,0x70,0xFA,0xDE,0xCC,0xDC,0x76,0x00,0x00,        // &         0x26 7
  0x00,0x30,0x30,0x30,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,        // Grad      0x27 
  0x00,0x0C,0x18,0x30,0x60,0x60,0x60,0x30,0x18,0x0C,0x00,0x00,        // (         0x28
  0x00,0x60,0x30,0x18,0x0C,0x0C,0x0C,0x18,0x30,0x60,0x00,0x00,        // )         0x29
  0x00,0x00,0x00,0x66,0x3C,0xFF,0x3C,0x66,0x00,0x00,0x00,0x00,        // *         0x2A
  0x00,0x00,0x00,0x18,0x18,0x7E,0x18,0x18,0x00,0x00,0x00,0x00,        // +         0x2B
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x38,0x60,0x00,        // ,         0x2C
  0x00,0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,        // -         0x2D
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x38,0x00,0x00,        // .         0x2E
  0x00,0x00,0x02,0x06,0x0C,0x18,0x30,0x60,0xC0,0x80,0x00,0x00,        // /         0x2F 
  0x00,0x7C,0xC6,0xCE,0xDE,0xD6,0xF6,0xE6,0xC6,0x7C,0x00,0x00,        // 0         0x30
  0x00,0x10,0x30,0xF0,0x30,0x30,0x30,0x30,0x30,0xFC,0x00,0x00,        // 1         0x31
  0x00,0x78,0xCC,0xCC,0x0C,0x18,0x30,0x60,0xCC,0xFC,0x00,0x00,        // 2         0x32
  0x00,0x78,0xCC,0x0C,0x0C,0x38,0x0C,0x0C,0xCC,0x78,0x00,0x00,        // 3         0x33
  0x00,0x0C,0x1C,0x3C,0x6C,0xCC,0xFE,0x0C,0x0C,0x1E,0x00,0x00,        // 4         0x34
  0x00,0xFC,0xC0,0xC0,0xC0,0xF8,0x0C,0x0C,0xCC,0x78,0x00,0x00,        // 5         0x35
  0x00,0x38,0x60,0xC0,0xC0,0xF8,0xCC,0xCC,0xCC,0x78,0x00,0x00,        // 6         0x36
  0x00,0xFE,0xC6,0xC6,0x06,0x0C,0x18,0x30,0x30,0x30,0x00,0x00,        // 7         0x37
  0x00,0x78,0xCC,0xCC,0xCC,0x78,0xCC,0xCC,0xCC,0x78,0x00,0x00,        // 8         0x38
  0x00,0x78,0xCC,0xCC,0xCC,0x7C,0x18,0x18,0x30,0x70,0x00,0x00,        // 9         0x39
  0x00,0x00,0x00,0x38,0x38,0x00,0x00,0x38,0x38,0x00,0x00,0x00,        // :         0x3A
  0x00,0x00,0x00,0x38,0x38,0x00,0x00,0x38,0x38,0x18,0x30,0x00,        // ;         0x3B
  0x00,0x0C,0x18,0x30,0x60,0xC0,0x60,0x30,0x18,0x0C,0x00,0x00,        // <         0x3C
  0x00,0x00,0x00,0x00,0x7E,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,        // =         0x3D
  0x00,0x60,0x30,0x18,0x0C,0x06,0x0C,0x18,0x30,0x60,0x00,0x00,        // >         0x3E
  0x00,0x78,0xCC,0x0C,0x18,0x30,0x30,0x00,0x30,0x30,0x00,0x00,        // ?         0x3F
  0x00,0x7C,0xC6,0xC6,0xDE,0xDE,0xDE,0xC0,0xC0,0x7C,0x00,0x00,        // @         0x40
  0x00,0x30,0x78,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0x00,0x00,        // A         0x41
  0x00,0xFC,0x66,0x66,0x66,0x7C,0x66,0x66,0x66,0xFC,0x00,0x00,        // B         0x42
  0x00,0x3C,0x66,0xC6,0xC0,0xC0,0xC0,0xC6,0x66,0x3C,0x00,0x00,        // C         0x43
  0x00,0xF8,0x6C,0x66,0x66,0x66,0x66,0x66,0x6C,0xF8,0x00,0x00,        // D         0x44
  0x00,0xFE,0x62,0x60,0x64,0x7C,0x64,0x60,0x62,0xFE,0x00,0x00,        // E         0x45
  0x00,0xFE,0x66,0x62,0x64,0x7C,0x64,0x60,0x60,0xF0,0x00,0x00,        // F         0x46
  0x00,0x3C,0x66,0xC6,0xC0,0xC0,0xCE,0xC6,0x66,0x3E,0x00,0x00,        // G         0x47
  0x00,0xCC,0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0xCC,0x00,0x00,        // H         0x48
  0x00,0x78,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x78,0x00,0x00,        // I         0x49
  0x00,0x1E,0x0C,0x0C,0x0C,0x0C,0xCC,0xCC,0xCC,0x78,0x00,0x00,        // J         0x4A
  0x00,0xE6,0x66,0x6C,0x6C,0x78,0x6C,0x6C,0x66,0xE6,0x00,0x00,        // K         0x4B
  0x00,0xF0,0x60,0x60,0x60,0x60,0x62,0x66,0x66,0xFE,0x00,0x00,        // L         0x4C
  0x00,0xC6,0xEE,0xFE,0xFE,0xD6,0xC6,0xC6,0xC6,0xC6,0x00,0x00,        // M         0x4D
  0x00,0xC6,0xC6,0xE6,0xF6,0xFE,0xDE,0xCE,0xC6,0xC6,0x00,0x00,        // N         0x4E
  0x00,0x38,0x6C,0xC6,0xC6,0xC6,0xC6,0xC6,0x6C,0x38,0x00,0x00,        // O         0x4F
  0x00,0xFC,0x66,0x66,0x66,0x7C,0x60,0x60,0x60,0xF0,0x00,0x00,        // P         0x50
  0x00,0x38,0x6C,0xC6,0xC6,0xC6,0xCE,0xDE,0x7C,0x0C,0x1E,0x00,        // Q         0x51
  0x00,0xFC,0x66,0x66,0x66,0x7C,0x6C,0x66,0x66,0xE6,0x00,0x00,        // R         0x52
  0x00,0x78,0xCC,0xCC,0xC0,0x70,0x18,0xCC,0xCC,0x78,0x00,0x00,        // S         0x53
  0x00,0xFC,0xB4,0x30,0x30,0x30,0x30,0x30,0x30,0x78,0x00,0x00,        // T         0x54
  0x00,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0x78,0x00,0x00,        // U         0x55
  0x00,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0x78,0x30,0x00,0x00,        // V         0x56
  0x00,0xC6,0xC6,0xC6,0xC6,0xD6,0xD6,0x6C,0x6C,0x6C,0x00,0x00,        // W         0x57
  0x00,0xCC,0xCC,0xCC,0x78,0x30,0x78,0xCC,0xCC,0xCC,0x00,0x00,        // X         0x58
  0x00,0xCC,0xCC,0xCC,0xCC,0x78,0x30,0x30,0x30,0x78,0x00,0x00,        // Y         0x59
  0x00,0xFE,0xCE,0x98,0x18,0x30,0x60,0x62,0xC6,0xFE,0x00,0x00,        // Z         0x5A
  0x00,0x3C,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x3C,0x00,0x00,        // [ -       0x5B
  0x00,0x00,0x80,0xC0,0x60,0x30,0x18,0x0C,0x06,0x02,0x00,0x00,        // backslash 0x5C
  0x00,0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C,0x00,0x00,        // ]         0x5D
  0x10,0x38,0x6C,0xC6,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,        // ^         0x5E
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,        // _         0x5F
  0x30,0x30,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,        // '         0x60
  0x00,0x00,0x00,0x00,0x78,0x0C,0x7C,0xCC,0xCC,0x76,0x00,0x00,        // a         0x61
  0x00,0xE0,0x60,0x60,0x7C,0x66,0x66,0x66,0x66,0xDC,0x00,0x00,        // b         0x62
  0x00,0x00,0x00,0x00,0x78,0xCC,0xC0,0xC0,0xCC,0x78,0x00,0x00,        // c         0x63
  0x00,0x1C,0x0C,0x0C,0x7C,0xCC,0xCC,0xCC,0xCC,0x76,0x00,0x00,        // d         0x64
  0x00,0x00,0x00,0x00,0x78,0xCC,0xFC,0xC0,0xCC,0x78,0x00,0x00,        // e         0x65
  0x00,0x38,0x6C,0x60,0x60,0xF8,0x60,0x60,0x60,0xF0,0x00,0x00,        // f         0x66
  0x00,0x00,0x00,0x00,0x76,0xCC,0xCC,0xCC,0x7C,0x0C,0xCC,0x78,        // g         0x67
  0x00,0xE0,0x60,0x60,0x6C,0x76,0x66,0x66,0x66,0xE6,0x00,0x00,        // h         0x68
  0x00,0x18,0x18,0x00,0x78,0x18,0x18,0x18,0x18,0x7E,0x00,0x00,        // i         0x69
  0x00,0x0C,0x0C,0x00,0x3C,0x0C,0x0C,0x0C,0x0C,0xCC,0xCC,0x78,        // j         0x6A
  0x00,0xE0,0x60,0x60,0x66,0x6C,0x78,0x6C,0x66,0xE6,0x00,0x00,        // k         0x6B
  0x00,0x78,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x7E,0x00,0x00,        // l         0x6C
  0x00,0x00,0x00,0x00,0xFC,0xD6,0xD6,0xD6,0xD6,0xC6,0x00,0x00,        // m         0x6D
  0x00,0x00,0x00,0x00,0xF8,0xCC,0xCC,0xCC,0xCC,0xCC,0x00,0x00,        // n         0x6E
  0x00,0x00,0x00,0x00,0x78,0xCC,0xCC,0xCC,0xCC,0x78,0x00,0x00,        // o         0x6F
  0x00,0x00,0x00,0x00,0xDC,0x66,0x66,0x66,0x66,0x7C,0x60,0xF0,        // p         0x70
  0x00,0x00,0x00,0x00,0x76,0xCC,0xCC,0xCC,0xCC,0x7C,0x0C,0x1E,        // q         0x71
  0x00,0x00,0x00,0x00,0xEC,0x6E,0x76,0x60,0x60,0xF0,0x00,0x00,        // r         0x72
  0x00,0x00,0x00,0x00,0x78,0xCC,0x60,0x18,0xCC,0x78,0x00,0x00,        // s         0x73
  0x00,0x00,0x20,0x60,0xFC,0x60,0x60,0x60,0x6C,0x38,0x00,0x00,        // t         0x74
  0x00,0x00,0x00,0x00,0xCC,0xCC,0xCC,0xCC,0xCC,0x76,0x00,0x00,        // u         0x75
  0x00,0x00,0x00,0x00,0xCC,0xCC,0xCC,0xCC,0x78,0x30,0x00,0x00,        // v         0x76
  0x00,0x00,0x00,0x00,0xC6,0xC6,0xD6,0xD6,0x6C,0x6C,0x00,0x00,        // w         0x77
  0x00,0x00,0x00,0x00,0xC6,0x6C,0x38,0x38,0x6C,0xC6,0x00,0x00,        // x         0x78
  0x00,0x00,0x00,0x00,0x66,0x66,0x66,0x66,0x3C,0x0C,0x18,0xF0,        // y         0x79
  0x00,0x00,0x00,0x00,0xFC,0x8C,0x18,0x60,0xC4,0xFC,0x00,0x00,        // z         0x7A
  0x00,0x1C,0x30,0x30,0x60,0xC0,0x60,0x30,0x30,0x1C,0x00,0x00,        // {         0x7B
  0x00,0x18,0x18,0x18,0x18,0x00,0x18,0x18,0x18,0x18,0x00,0x00,        // |         0x7C
  0x00,0xE0,0x30,0x30,0x18,0x0C,0x18,0x30,0x30,0xE0,0x00,0x00,        // }         0x7D
  0x00,0x73,0xDA,0xCE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,        // ->        0x7E
  0x00,0x00,0x00,0x10,0x38,0x6C,0xC6,0xC6,0xFE,0x00,0x00,0x00,        // <-        0x7F
};

BYTE const font8x8[128][8] = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // Leerzeichen 0x20 32 0
  0x00,0x00,0x00,0xF2,0xF2,0x00,0x00,0x00,  // ! 33 1
  0x00,0xE0,0xE0,0x00,0x00,0xE0,0xE0,0x00,  // " 34 2
  0x28,0xFE,0xFE,0x28,0x28,0xFE,0xFE,0x28,  // # 35 3
  0x00,0x48,0x5C,0xD6,0xD6,0x74,0x24,0x00,  // $ 36 4 
  0x00,0xC6,0x66,0x30,0x18,0xCC,0xC6,0x00,  // % 37 5
  0x0A,0x4E,0xEE,0xB2,0xB2,0xFE,0x4C,0x00,  // & 38 6
  0x00,0x80,0xC0,0x60,0x20,0x00,0x00,0x00,  // ' 39 7
  0x00,0x00,0x82,0xC6,0x7C,0x38,0x00,0x00,  // ( 40 8
  0x00,0x00,0x38,0x7C,0xC6,0x82,0x00,0x00,  // ) 41 9
  0x10,0x54,0x7C,0x38,0x38,0x7C,0x54,0x10,  // * 42 10
  0x00,0x10,0x10,0x7C,0x7C,0x10,0x10,0x00,  // + 43 11
  0x00,0x00,0x00,0x06,0x07,0x01,0x00,0x00,  // , 44 12
  0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x00,  // - 45 13
  0x00,0x00,0x00,0x06,0x06,0x00,0x00,0x00,  // . 46 14 
  0x40,0x60,0x30,0x18,0x0C,0x06,0x02,0x00,  // / 47 15
  0x00,0x7C,0xFE,0xA2,0x92,0xFE,0x7C,0x00,  // 0  0x30 48 16
  0x00,0x02,0x02,0xFE,0xFE,0x22,0x02,0x00,  // 1 49
  0x00,0x62,0xF2,0x92,0x8A,0xCE,0x46,0x00,  // 2 50
  0x00,0x6C,0xFE,0x92,0x92,0xC6,0x44,0x00,  // 3 51
  0x08,0xFE,0xFE,0x68,0x28,0x18,0x18,0x00,  // 4 52
  0x00,0x9C,0xBE,0xA2,0xA2,0xE6,0xE4,0x00,  // 5 53
  0x00,0x4C,0xDE,0x92,0x92,0xFE,0x7C,0x00,  // 6 54
  0x00,0xC0,0xE0,0xBE,0x9E,0xC0,0xC0,0x00,  // 7 55
  0x00,0x6C,0xFE,0x92,0x92,0xFE,0x6C,0x00,  // 8 56
  0x00,0x7C,0xFE,0x92,0x92,0xF6,0x64,0x00,  // 9 57
  0x00,0x00,0x00,0x24,0x24,0x00,0x00,0x00,  // : 58
  0x00,0x00,0x00,0x26,0x27,0x01,0x00,0x00,  // ; 59
  0x00,0x82,0x82,0xC6,0x6C,0x38,0x10,0x00,  // < 60
  0x00,0x28,0x28,0x28,0x28,0x28,0x28,0x00,  // = 61
  0x00,0x10,0x38,0x6C,0xC6,0x82,0x82,0x00,  // > 62
  0x00,0x60,0xF0,0x9A,0x8A,0xC0,0x40,0x00,  // ? 63 at� aqui subtrai 0x20 
  0x00,0x74,0xF2,0xB2,0x82,0xFE,0x7C,0x00,  // @ 64
  0x00,0x3E,0x7E,0xD0,0xD0,0x7E,0x3E,0x00,  // A  0x41 65
  0x00,0x6C,0xFE,0x92,0x92,0xFE,0xFE,0x00,  // B 66
  0x00,0x44,0xC6,0x82,0x82,0xFE,0x7C,0x00,  // C 67
  0x00,0x38,0x7C,0xC6,0x82,0xFE,0xFE,0x00,  // D 68
  0x00,0x82,0x82,0x92,0x92,0xFE,0xFE,0x00,  // E 69
  0x00,0x80,0x80,0x90,0x90,0xFE,0xFE,0x00,  // F 70
  0x00,0x5C,0xDE,0x92,0x82,0xFE,0x7C,0x00,  // G 71
  0x00,0xFE,0xFE,0x10,0x10,0xFE,0xFE,0x00,  // H 72
  0x00,0x00,0x82,0xFE,0xFE,0x82,0x00,0x00,  // I 73
  0x00,0x80,0xFC,0xFE,0x82,0x06,0x04,0x00,  // J 74
  0x00,0x82,0xC6,0x6C,0x38,0xFE,0xFE,0x00,  // K 75
  0x00,0x02,0x02,0x02,0x02,0xFE,0xFE,0x00,  // L 76
  0xFE,0xFE,0x60,0x30,0x60,0xFE,0xFE,0x00,  // M 77
  0x00,0xFE,0xFE,0x38,0x70,0xFE,0xFE,0x00,  // N 78
  0x00,0x7C,0xFE,0x82,0x82,0xFE,0x7C,0x00,   // O 79

  0x00,0x60,0xF0,0x90,0x90,0xFE,0xFE,0x00,  // P 80
  0x00,0x7A,0xFE,0x86,0x84,0xFC,0x78,0x00,  // Q 81
  0x00,0x62,0xF6,0x9C,0x98,0xFE,0xFE,0x00,  // R 82
  0x00,0x4C,0xDE,0x92,0x92,0xF6,0x64,0x00,  // S 83
  0x00,0x80,0x80,0xFE,0xFE,0x80,0x80,0x00,  // T 84
  0x00,0xFC,0xFE,0x02,0x02,0xFE,0xFC,0x00,  // U 85
  0x00,0xF8,0xFC,0x06,0x06,0xFC,0xF8,0x00,  // V 86
  0xFE,0xFE,0x0C,0x18,0x0C,0xFE,0xFE,0x00,  // W 87
  0x00,0xC6,0xEE,0x38,0x38,0xEE,0xC6,0x00,  // X 88
  0x00,0xE0,0xF0,0x1E,0x1E,0xF0,0xE0,0x00,  // Y 89
  0x00,0xC2,0xE2,0xB2,0x9A,0x8E,0x86,0x00,  // Z 90
  0x00,0x00,0x82,0x82,0xFE,0xFE,0x00,0x00,  // [ 91
  0x40,0x60,0x30,0x18,0x0C,0x06,0x02,0x00,  // backslash 92
  0x00,0x00,0xFE,0xFE,0x82,0x82,0x00,0x00,  // ] 93
  0x00,0x80,0xC0,0x60,0x20,0x00,0x00,0x00,  // ^ 94
  0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,  // _ 95
  0x00,0x80,0xC0,0x60,0x20,0x00,0x00,0x00,  // ` 96
  0x00,0x1E,0x3E,0x2A,0x2A,0x2E,0x04,0x00,  // a 97
  0x00,0x0C,0x1E,0x12,0x12,0x7E,0x7E,0x00,  // b 98
  0x00,0x00,0x22,0x22,0x22,0x3E,0x1C,0x00,  // c 99
  0x00,0x7E,0x7E,0x12,0x12,0x1E,0x0C,0x00,  // d 100
  0x00,0x18,0x3A,0x2A,0x2A,0x3E,0x1C,0x00,  // e 101
  0x00,0x50,0x50,0x7E,0x3E,0x10,0x00,0x00,  // f 102
  0x00,0x3E,0x3F,0x25,0x25,0x3D,0x19,0x00,  // g 103
  0x00,0x0E,0x1E,0x10,0x10,0x7E,0x7E,0x00,  // h 104
  0x00,0x00,0x02,0x5E,0x5E,0x12,0x00,0x00,  // i 105
  0x00,0x5E,0x5F,0x01,0x01,0x01,0x00,0x00,  // j 106
  0x00,0x02,0x16,0x1C,0x08,0x7E,0x7E,0x00,  // k 107
  0x00,0x00,0x02,0x7E,0x7E,0x42,0x00,0x00,  // l 108
  0x1E,0x3E,0x38,0x1C,0x18,0x3E,0x3E,0x00,  // m 109 
  0x00,0x1E,0x3E,0x20,0x20,0x3E,0x3E,0x00,  // n 110
  0x00,0x1C,0x3E,0x22,0x22,0x3E,0x1C,0x00,  // o 111
  0x00,0x18,0x3C,0x24,0x24,0x3F,0x3F,0x00,  // p 112
  0x00,0x3F,0x3F,0x24,0x24,0x3C,0x18,0x00,  // q 113
  0x00,0x10,0x30,0x20,0x20,0x3E,0x3E,0x00,  // r 114
  0x00,0x24,0x2E,0x2A,0x2A,0x3A,0x12,0x00,  // s 115
  0x00,0x22,0x22,0x7E,0x7C,0x20,0x20,0x00,  // t 116
  0x00,0x3E,0x3E,0x02,0x02,0x3E,0x3C,0x00,  // u 117
  0x00,0x38,0x3C,0x06,0x06,0x3C,0x38,0x00,  // v 118
  0x38,0x3E,0x0E,0x1C,0x0E,0x3E,0x38,0x00,  // w 119
  0x00,0x22,0x36,0x1C,0x1C,0x36,0x22,0x00,  // x 120
  0x00,0x3C,0x3E,0x07,0x05,0x3D,0x39,0x00,  // y 121
  0x00,0x22,0x32,0x3A,0x2E,0x26,0x22,0x00,  // z 122
  0x00,0x00,0x82,0x82,0xFE,0xFE,0x00,0x00,  // ] 123
  0x00,0x44,0x92,0x92,0x7A,0x3E,0x16,0x02,  // Pfund 124
  0x00,0x00,0xFE,0xFE,0x82,0x82,0x00,0x00,  // [ 125
  0x00,0x10,0x30,0x7F,0x7F,0x30,0x10,0x00,  // Pfeil hoch 126
  0x18,0x18,0x18,0x18,0x7E,0x3C,0x18,0x00,  // Pfeil links 127
};

BYTE const font5x8[128][5] =  {
  0x00,0x00,0x00,0x00,0x00,   // 20 space 
  0x00,0x00,0x5f,0x00,0x00,   // 21 !
  0x00,0x07,0x00,0x07,0x00,   // 22 "
  0x14,0x7f,0x14,0x7f,0x14,   // 23 #
  0x24,0x2a,0x7f,0x2a,0x12,   // 24 $
  0x23,0x13,0x08,0x64,0x62,   // 25 %
  0x36,0x49,0x55,0x22,0x50,   // 26 &
  0x00,0x05,0x03,0x00,0x00,   // 27 '
  0x00,0x1c,0x22,0x41,0x00,   // 28 (
  0x00,0x41,0x22,0x1c,0x00,   // 29 )
  0x14,0x08,0x3e,0x08,0x14,   // 2a *
  0x08,0x08,0x3e,0x08,0x08,   // 2b +
  0x00,0x50,0x30,0x00,0x00,   // 2c ,
  0x08,0x08,0x08,0x08,0x08,   // 2d -
  0x00,0x60,0x60,0x00,0x00,   // 2e .
  0x20,0x10,0x08,0x04,0x02,   // 2f /
  0x3e,0x51,0x49,0x45,0x3e,   // 30 0
  0x00,0x42,0x7f,0x40,0x00,   // 31 1
  0x42,0x61,0x51,0x49,0x46,   // 32 2
  0x21,0x41,0x45,0x4b,0x31,   // 33 3
  0x18,0x14,0x12,0x7f,0x10,   // 34 4
  0x27,0x45,0x45,0x45,0x39,   // 35 5
  0x3c,0x4a,0x49,0x49,0x30,   // 36 6
  0x01,0x71,0x09,0x05,0x03,   // 37 7
  0x36,0x49,0x49,0x49,0x36,   // 38 8
  0x06,0x49,0x49,0x29,0x1e,   // 39 9
  0x00,0x36,0x36,0x00,0x00,   // 3a :
  0x00,0x56,0x36,0x00,0x00,   // 3b ;
  0x08,0x14,0x22,0x41,0x00,   // 3c <
  0x14,0x14,0x14,0x14,0x14,   // 3d =
  0x00,0x41,0x22,0x14,0x08,   // 3e >
  0x02,0x01,0x51,0x09,0x06,   // 3f ?
  0x32,0x49,0x79,0x41,0x3e,   // 40 @
  0x7e,0x11,0x11,0x11,0x7e,   // 41 A
  0x7f,0x49,0x49,0x49,0x36,   // 42 B
  0x3e,0x41,0x41,0x41,0x22,   // 43 C
  0x7f,0x41,0x41,0x22,0x1c,   // 44 D
  0x7f,0x49,0x49,0x49,0x41,   // 45 E
  0x7f,0x09,0x09,0x09,0x01,   // 46 F
  0x3e,0x41,0x49,0x49,0x7a,   // 47 G
  0x7f,0x08,0x08,0x08,0x7f,   // 48 H
  0x00,0x41,0x7f,0x41,0x00,   // 49 I
  0x20,0x40,0x41,0x3f,0x01,   // 4a J
  0x7f,0x08,0x14,0x22,0x41,   // 4b K
  0x7f,0x40,0x40,0x40,0x40,   // 4c L
  0x7f,0x02,0x0c,0x02,0x7f,   // 4d M
  0x7f,0x04,0x08,0x10,0x7f,   // 4e N
  0x3e,0x41,0x41,0x41,0x3e,    // 4f O

  0x7f,0x09,0x09,0x09,0x06,   // 50 P
  0x3e,0x41,0x51,0x21,0x5e,   // 51 Q
  0x7f,0x09,0x19,0x29,0x46,   // 52 R
  0x46,0x49,0x49,0x49,0x31,   // 53 S
  0x01,0x01,0x7f,0x01,0x01,   // 54 T
  0x3f,0x40,0x40,0x40,0x3f,   // 55 U
  0x1f,0x20,0x40,0x20,0x1f,   // 56 V
  0x3f,0x40,0x38,0x40,0x3f,   // 57 W
  0x63,0x14,0x08,0x14,0x63,   // 58 X
  0x07,0x08,0x70,0x08,0x07,   // 59 Y
  0x61,0x51,0x49,0x45,0x43,   // 5a Z
  0x00,0x7f,0x41,0x41,0x00,   // 5b [
  0x02,0x04,0x08,0x10,0x20,   // 5c
  0x00,0x41,0x41,0x7f,0x00,   // 5d
  0x04,0x02,0x01,0x02,0x04,   // 5e
  0x40,0x40,0x40,0x40,0x40,   // 5f
  0x00,0x01,0x02,0x04,0x00,   // 60
  0x20,0x54,0x54,0x54,0x78,   // 61 a
  0x7f,0x48,0x44,0x44,0x38,   // 62 b
  0x38,0x44,0x44,0x44,0x20,   // 63 c
  0x38,0x44,0x44,0x48,0x7f,   // 64 d
  0x38,0x54,0x54,0x54,0x18,   // 65 e
  0x08,0x7e,0x09,0x01,0x02,   // 66 f
  0x0c,0x52,0x52,0x52,0x3e,   // 67 g
  0x7f,0x08,0x04,0x04,0x78,   // 68 h
  0x00,0x44,0x7d,0x40,0x00,   // 69 i
  0x20,0x40,0x44,0x3d,0x00,   // 6a j
  0x7f,0x10,0x28,0x44,0x00,   // 6b k
  0x00,0x41,0x7f,0x40,0x00,   // 6c l
  0x7c,0x04,0x18,0x04,0x78,   // 6d m
  0x7c,0x08,0x04,0x04,0x78,   // 6e n
  0x38,0x44,0x44,0x44,0x38,   // 6f o
  0x7c,0x14,0x14,0x14,0x08,   // 70 p
  0x08,0x14,0x14,0x18,0x7c,   // 71 q
  0x7c,0x08,0x04,0x04,0x08,   // 72 r
  0x48,0x54,0x54,0x54,0x20,   // 73 s
  0x04,0x3f,0x44,0x40,0x20,   // 74 t
  0x3c,0x40,0x40,0x20,0x7c,   // 75 u
  0x1c,0x20,0x40,0x20,0x1c,   // 76 v
  0x3c,0x40,0x30,0x40,0x3c,   // 77 w
  0x44,0x28,0x10,0x28,0x44,   // 78 x
  0x0c,0x50,0x50,0x50,0x3c,   // 79 y
  0x44,0x64,0x54,0x4c,0x44,   // 7a z
  0x00,0x08,0x36,0x41,0x00,   // 7b
  0x00,0x00,0x7f,0x00,0x00,   // 7c
  0x00,0x41,0x36,0x08,0x00,   // 7d
  0x10,0x08,0x08,0x10,0x08,   // 7e
  0x78,0x46,0x41,0x46,0x78    // 7f
};


void SendCommand(BYTE Command);
void WriteDisplay(BYTE Value);
void Reset_LCD(void);
void ClearDisplay(void);
void Init_LCD(void);
void GotoXRow(BYTE x, BYTE Row);
char invByte(char bt);
void printChar5x8(char cvar);
void printChar8x8(char cvar);
void printChar8x12(char cvar);

long i;
int XX = 0, YY = 0;

void lcd_write(char dados){
   spi_write(dados);
}

void Reset_LCD(void){
  delay_us(10);
  output_bit(sda, 0);
  output_bit(sclk, 0);
  output_bit(dc, 0);
  delay_us(10);
  output_bit(rst, 1);
  delay_us(10);
  output_bit(sce, 0);
  delay_us(10);
  output_bit(rst, 0);
  delay_us(10);  
  output_bit(rst, 1);
  output_bit(sce, 1);
}

void Init_LCD(void){
  Reset_LCD();
  SendCommand(0x21);  // Function set: extended instruction set
  SendCommand(0x14);  // Bias System
  SendCommand(0x0A);  // HV-gen stages
  SendCommand(0x05);  // Temperature Control
  SendCommand(0xCC);  // Contrast: 204
  SendCommand(0x20);  // Function set: standard instruction set
  SendCommand(0x11);  // VLCD programming range: high
  SendCommand(0x0C);  // Display control: normal (inverted = 0x0D)
  
}   

void ClearDisplay(void){
  GotoXRow(0,7);
  for (i=0; i<815; i++){ // eigentlich 101*64/8 aber Display-SOC 
     WriteDisplay(0x00);                                  // unterst�tzt 0..101, also 102 Spalten pro Zeile 
  }                  // es sind aber nur 101 Spalten vorhanden!
}

void GotoXRow(BYTE x, BYTE Row){ // x: 0..101, Row 0..7;
  SendCommand( 0b00101000);
  SendCommand((0b01000000 + 7 - Row));
  SendCommand((0b10000000 + x ));
  XX = x;
  YY = Row;
  /*YY = 7 - Row;
  XX = x;*/
}

void SendCommand(BYTE Command){
  output_bit(sda, 0);
  output_bit(sclk, 0);
  output_bit(dc, 0);
  output_bit(sce, 0);
  
  lcd_write(Command);
  
  output_bit(sce, 1);
}
void WriteDisplay(BYTE Value){          
  output_bit(sda, 0);
  output_bit(sclk, 0);
  output_bit(dc, 1);
  output_bit(sce, 0);

  lcd_write(Value);
  output_bit(sce, 1);
  /*XX++;
  if(XX > 101){
      XX = 0;
      YY++;
      if(YY > 7)
         YY = 0;
  }*/
}

void printChar5x8(char cvar){
  int i;
  char c;
  if ((cvar<0x20) || (cvar>0x7F)) return;
  for (i=0;i<5;i++){
    c=font5x8[((cvar&0xff)-0x20)][i];
    if((c!=0x00) || (cvar==0x20))     
       WriteDisplay(c);
  }
  WriteDisplay(0x00);
}

void printChar8x8(char cvar){
   BYTE i;
   char c = 0x00;
   long pos = 0;
   if ((cvar<0x20) || (cvar>0x7F)) return;
   pos = cvar-0x20;   
   for (i=0;i<8;i++){
      c=font8x8[pos][(7-i)];
      /*if((c!=0x00) || (cvar==0x20)){      
         WriteDisplay(invByte(c));  
      }*/
      if((c!=0x00) || (cvar==0x20) && (i<3)){      
         WriteDisplay(invByte(c));  
      }      
   }
   WriteDisplay(0x00);  
}

char invByte(char bt){    // Essa fun��o � necess�ria para inverter os bits da maneira correta ex: 1100 0000 = 0000 0011
   char btInvert = 0x00;
   Byte bitTest = 0x80, bitset = 0x01;
   for(i=0;i<8;i++){
      if((bt&bitTest) != 0)
         btInvert |= bitset; 
      bitTest>>=1;
      bitset<<=1;
   }
   return btInvert;   
}

void printChar8x12(char cvar){
   int i, j, inc = 0;
   long pos = 0;
   char c[16] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
  
   Byte bitTest = 0x80, bitset = 0x01;

   if ((cvar<0x20) || (cvar>0x7F)) return;
   pos = cvar-0x20;
   for(i=0;i<12;i++){
      for(j=0;j<8;j++){      
        if((font8x12[pos][i]&bitTest) != 0)
          c[j+inc] |= bitset;
        bitTest>>=1;
      }
      bitTest = 0x80;
      bitset<<=1;
      if(i==7){
         inc=8;
         bitset = 0x01;         
      }      
   }
   for(i=0;i<8;i++){
     // if(((c[i]!=0x00) && (c[i+8]!=0x00)) || (cvar==0x20))
         WriteDisplay(c[i]);
   }
   WriteDisplay(0x00);   
   GotoXRow(XX,YY+1);
   for(i=0;i<8;i++){
      //if(((c[i]!=0x00) && (c[i+8]!=0x00)) || (cvar==0x20)){    
         WriteDisplay(c[i+8]); 
      //}
         XX++; 
   }
   WriteDisplay(0x00);
   GotoXRow(XX,YY-1);   
}

