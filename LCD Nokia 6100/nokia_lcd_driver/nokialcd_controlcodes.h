#ifndef EPSON
#ifndef PHILLIPS
#error You must define either EPSON or PHILLIPS
#endif
#endif

#ifdef EPSON
#ifdef PHILLIPS
#error You must define only one of EPSON or PHILLIPS
#endif
#endif

//********************************************************************
//
//               EPSON Controller Definitions
//
//********************************************************************
#define EP_DISON       0xAF
#define EP_DISOFF      0xAE
#define EP_DISNOR      0xA6
#define EP_DISINV      0xA7
#define EP_SLPIN       0x95
#define EP_SLPOUT      0x94
#define EP_COMSCN      0xBB
#define EP_DISCTL      0xCA
#define EP_PASET       0x75
#define EP_CASET       0x15
#define EP_DATCTL      0xBC
#define EP_RGBSET8     0xCE
#define EP_RAMWR       0x5C
#define EP_RAMRD       0x5D
#define EP_PTLIN       0xA8
#define EP_PTLOUT      0xA9
#define EP_RMWIN       0xE0
#define EP_RMWOUT      0xEE
#define EP_ASCSET      0xAA
#define EP_SCSTART     0xAB
#define EP_OSCON       0xD1
#define EP_OSCOFF      0xD2
#define EP_PWRCTR      0x20
#define EP_VOLCTR      0x81
#define EP_VOLUP       0xD6
#define EP_VOLDOWN     0xD7
#define EP_TMPGRD      0x82
#define EP_EPCTIN      0xCD
#define EP_EPCOUT      0xCC
#define EP_EPMWR       0xFC
#define EP_EPMRD       0xFD
#define EP_EPSRRD1     0x7C
#define EP_EPSRRD2     0x7D
#define EP_NOP         0x25


//*******************************************************
//            Generic LCD commands
//*******************************************************
   #define LCD_RAMWR 0x5C
   #define LCD_PASET 0x75
   #define LCD_CASET 0x15
   #define LCD_NOP   0x25

