#ifndef __GENERAL_H
#define __GENERAL_H

#define POLY_CRC16 0xA001

void  stringCopy (char *buffer, char *string);
void stringCat(char *string1, char *string2);
char *WordToString(unsigned int Number);
char *FloatToString_4Pt2Dec(float Number);
void Delay_uS(unsigned int Delay ); 
unsigned int CalcCRC16(unsigned char *chpData, char chDataLength);
unsigned int StringToWord(char *String);
unsigned long StringToLONG(char *String);
void SortWordBufferAsc(unsigned int *BuffData, unsigned int nData);


#endif
