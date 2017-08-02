/**
LTC2439.c
**/
// local includes
#include "HardwareProfile.h"
#include "ApplicationDrivers.h"
#include "Flash.h"



void FLASH_SendData(BYTE *Data, WORD NoOfBytes)
{
 SPIFLASH_CS_IO = 0;
 Restart_SPI1();
 Delay_uS(10);
 SPI1_TxByte(Data, NoOfBytes);
 Delay_uS(10);
 SPIFLASH_CS_IO = 1;
}
void FLASH_SendStatusCmmd (BYTE cmmd)
{
 BYTE DataToTx[2];
 DataToTx[0]=cmmd;
 FLASH_SendData(&DataToTx[0],1);
}

void FLASH_SectorErase (LINT Sector)
{
 LONGTOBYTE tempSector;
 tempSector.long_data=Sector;
 BYTE DataToTx[4];
 DataToTx[0]=FLASH_SECTOR_ERASE;
 DataToTx[1]=tempSector.bytes[2];
 DataToTx[2]=tempSector.bytes[1];
 DataToTx[3]=tempSector.bytes[0];
 FLASH_SendStatusCmmd (FLASH_WRITE_ENABLE);
 Delay_uS(10);
 FLASH_SendData(&DataToTx[0],4);
 while(FLASH_ReadStatusReg()&FLASH_BUSY);
 Delay_uS(10);
 Delay_uS(5000);
 Delay_uS(5000);
}

void FLASH_ChipErase(void)
{
 FLASH_SendStatusCmmd (FLASH_WRITE_ENABLE);
 Delay_uS(10);
 FLASH_SendStatusCmmd (FLASH_BULK_ERASE);
 while(FLASH_ReadStatusReg()&FLASH_BUSY);
 Delay_uS(10);
}

BYTE  FLASH_ReadStatusReg(void)
{
BYTE *pSPI1data;	
BYTE DataToTx[2];
pSPI1data=Return_SPI1_RxBuffer();
DataToTx[0]=FLASH_READ_STATUSREG1;
DataToTx[1]=0x00;	
Flush_SPI1_RxBuffer();
FLASH_SendData(&DataToTx[0],2);
DataToTx[0]=*pSPI1data;
DataToTx[1]=*(pSPI1data+1);
return DataToTx[1];
}

void FLASH_WriteStatusReg(BYTE Status)
{
BYTE DataToTx[2];
DataToTx[0]=FLASH_DATA_WRITE;
DataToTx[1]=Status;	
FLASH_SendStatusCmmd (FLASH_ENABLE_WRITESR);
Delay_uS(10);
FLASH_SendData(&DataToTx[0],2); 
Delay_uS(10);
}

void FLASH_Read(LINT StartAddress, WORD NoOfBytes, BYTE *DataRx )
{

	BYTE DataToTx[4];
	BYTE *pSPI1data;
	LONGTOBYTE Address;
	 Address.long_data=StartAddress;
	 pSPI1data=Return_SPI1_RxBuffer();
	
	DataToTx[0]=FLASH_READ;
 	DataToTx[1]=Address.bytes[2];
 	DataToTx[2]=Address.bytes[1];
 	DataToTx[3]=Address.bytes[0];
	
	SPIFLASH_CS_IO = 0;
	Restart_SPI1();
	Delay_uS(10);
	SPI1_TxByte(&DataToTx[0], 4);
	Delay_uS(10);
	Flush_SPI1_RxBuffer();
	while (NoOfBytes--)
	{
	DataToTx[0]=0;
	Delay_uS(10);	
	SPI1_TxByte(&DataToTx[0], 1);
	Delay_uS(10);
	*DataRx=*pSPI1data;
	DataRx++;
	pSPI1data++;
	}
	SPIFLASH_CS_IO = 1;
}

void FLASH_ByteProgram(LINT Address, BYTE Data)
{
BYTE DataToTx[5];
LONGTOBYTE tempAddress;
tempAddress.long_data=Address;
DataToTx[0]=FLASH_BYTE_PROGRAM;
DataToTx[1]=tempAddress.bytes[2];
DataToTx[2]=tempAddress.bytes[1];
DataToTx[3]=tempAddress.bytes[0];
DataToTx[4]=Data;
FLASH_SendStatusCmmd (FLASH_WRITE_ENABLE);
Delay_uS(20);
FLASH_SendData(&DataToTx[0],5);
while(FLASH_ReadStatusReg()&FLASH_BUSY);
 Delay_uS(10);
}

void FLASH_MultiByteProgram(LINT Address, BYTE* Data, WORD NoOfBytes)
{
  while (NoOfBytes--)
  {
    FLASH_ByteProgram(Address, *Data);
    Address++;
    Data++;
  }

}
	
