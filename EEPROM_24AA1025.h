#ifndef _EEPROM_24AA1025_h
#define _EEPROM_24AA1025_h

#define EEPROM_ADDRESS  0xAA
#define BLOCK_2			0x08



void EEPROM_Read(WORD StartAddress, BYTE *DataBuffer, BYTE dataLength);
void EEPROM_SingleWrite(WORD StartAddress, BYTE Data);
void EEPROM_MultiWrite (WORD StartAddress, BYTE *DataBuffer, BYTE DataLength);
BYTE EEPROM_AckPoll(void);
#endif
