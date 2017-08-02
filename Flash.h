#ifndef __FLASH_H
#define __FLASH_H


//============================Defines=============================//

#define MAX_SECTOR_SIZE			0x01000
#define MAX_BLOCK_SIZE				0x010000

#define MAX_FLASH_PAGES			8192
#define MAX_PAGE_PER_SECTOR		256

#define SECTOR_0   0x00000
#define SECTOR_1   0x01000
#define SECTOR_2   0x02000
#define SECTOR_3   0x03000
#define SECTOR_4   0x04000
#define SECTOR_5   0x05000
#define SECTOR_6   0x06000
#define SECTOR_7   0x07000
#define SECTOR_8   0x08000
#define SECTOR_9   0x09000
#define SECTOR_10  0x0A000
#define SECTOR_11  0x0B000
#define SECTOR_12  0x0C000
#define SECTOR_13  0x0D000
#define SECTOR_14  0x0E000
#define SECTOR_15  0x0F000

//====FLASH STATUS CMD=============/
#define FLASH_WRITE_ENABLE    0x06
#define FLASH_ENABLE_WRITESR  0x50
#define FLASH_WRITE_DISABLE   0x04
#define FLASH_BULK_ERASE      0x60 //0xC7
#define FLASH_DEEP_PWRDWN     0xB9
#define FLASH_REL_PWRDWN      0xAB
//=================================/

#define FLASH_READ_STATUSREG1 0x05
#define FLASH_READ_STATUSREG2 0x35
#define FLASH_WRITE_STATUSREG 0x01
#define FLASH_READ            0x03
#define FLASH_SECTOR_ERASE    0x20 //0xD8

#define FLASH_BYTE_PROGRAM    0x02
#define FLASH_READ_IDENT      0x90

#define FLASH_AUTO_ADDRESS    0xAD

//====FLASH STATUS REG=============/
#define FLASH_BUSY  0x01
#define FLASH_WEL    0x02
#define FLASH_BP0     0x04
#define FLASH_BP1     0x08
#define FLASH_BP2     0x10
#define FLASH_BP3     0x20
#define FLASH_AAI      0x40	
#define FLASH_BPL     0x80	



#define FLASH_DATA_READ       	0x00
#define FLASH_DATA_WRITE      	0x01
#define FLASH_ERASE_PROTECTION	0x02
#define FLASH_CS_Low()        mPORTEClearBits(BIT_7); 	// Turn off RE7 on startup.	// CS (on Flash)  
#define FLASH_CS_High()       mPORTESetBits(BIT_7); 	// Turn on RE7 on startup.	// CS (on Flash)

typedef struct FlASH_Data
{
  BYTE *Data;       //Pointer containing data to be written or read from to the FLASH
  BYTE No_of_Bytes; //Number of bytes to be written
  BYTE Cmmd;        //Instruction to be transmitted
  BYTE Address[3];  //Address location in the FLASH to be written or read from
}FLASH_DATA,*pFLASH_DATA;

void FLASH_SendData(BYTE *Data, WORD NoOfBytes);
void FLASH_SendStatusCmmd (BYTE cmmd);
void FLASH_SectorErase (LINT Sector);
void FLASH_ChipErase(void);
void FLASH_WriteStatusReg(BYTE Status);
void FLASH_Read(LINT StartAddress, WORD NoOfBytes, BYTE *DataRx );
void FLASH_ByteProgram(LINT Address, BYTE Data);
void FLASH_MultiByteProgram(LINT Address, BYTE* Data, WORD NoOfBytes);
BYTE  FLASH_ReadStatusReg(void);
#endif
