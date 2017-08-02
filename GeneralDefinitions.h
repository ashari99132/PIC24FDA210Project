#ifndef __GENERAL_DEFINITIONS_H
#define __GENERAL_DEFINITIONS_H

typedef unsigned char BYTE;
typedef signed char	  SCHAR;

typedef unsigned int  WORD;
typedef signed int	  SHORT;

typedef unsigned long DWORD;
typedef unsigned long LONG;
typedef union  wordbyte {
 WORD word;
 BYTE byte[2]; 

}WORDBYTE;
typedef union  floatbyte {
 float floatval;
 BYTE byte[4]; 

}FLOATBYTE;

typedef union  longbyte {
 LONG longval;
 BYTE byte[4];

}LONGBYTE;
#endif
