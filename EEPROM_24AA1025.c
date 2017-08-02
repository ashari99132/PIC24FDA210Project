/**
EEPROM_24AA1025.c
**/

// local includes
#include "ApplicationDrivers.h"
#include "p24FJ256DA210_I2C3.h"
#include "EEPROM_24AA1025.h"


//global
BYTE ByteCheck=0;
void EEPROM_Read(WORD StartAddress, BYTE *DataBuffer, BYTE dataLength)
{
 WORDTOBYTE command;
 command.bytes[0]=EEPROM_ADDRESS;	
 I2C3_Open();
 

 I2C3_startBit();
 I2C3_Idle_Bus(); 
 I2C3_Send_Byte(command.bytes[0]); //send eeprom address;
 Delay_uS(20);	
 command.word=StartAddress;
 
 I2C3_Send_Byte(command.bytes[1]); //send memory address high
 Delay_uS(20);
 I2C3_Send_Byte(command.bytes[0]); //send memory address low
 Delay_uS(20);
 
 command.bytes[0]=EEPROM_ADDRESS|0x01;	
 I2C3_REstartBit();
 I2C3_Idle_Bus(); 
 I2C3_Send_Byte(command.bytes[0]); //send eeprom address;
 Delay_uS(20);	
 I2C3_Idle_Bus();
  while(dataLength>1)//get data
 {
  I2C3_MasterReceive_Enable();	 
  *DataBuffer=I2C3_Receive_Byte();
  I2C3_Idle_Bus();
  I2C3_Send_Ack();
  I2C3_Idle_Bus();
  DataBuffer++;
  dataLength--;
 }
 I2C3_MasterReceive_Enable();	 
 *DataBuffer=I2C3_Receive_Byte();
 I2C3_Idle_Bus();
 I2C3_Send_NAck();
 I2C3_Idle_Bus();
 Delay_uS(20);	
 I2C3_stopBit();
 I2C3_Close();
}


void EEPROM_SingleWrite(WORD StartAddress, BYTE Data)
{
 WORDTOBYTE command;
 command.bytes[0]|=EEPROM_ADDRESS;	
 I2C3_Open();
 I2C3_startBit();
 I2C3_Idle_Bus(); 
 I2C3_Send_Byte(command.bytes[0]); //send eeprom address;
 Delay_uS(20);	
 command.word=StartAddress;
 
 I2C3_Send_Byte(command.bytes[1]); //send memory address high
 Delay_uS(20);
 I2C3_Send_Byte(command.bytes[0]); //send memory address low
 Delay_uS(20);
 
 I2C3_Send_Byte(Data); //send data
 Delay_uS(20);
 I2C3_Idle_Bus();
 I2C3_stopBit();
 I2C3_Close();
}

void EEPROM_MultiWrite (WORD StartAddress, BYTE *DataBuffer, BYTE DataLength)
{
 
  while(DataLength--)
  	{
		do
		{
			EEPROM_SingleWrite(StartAddress,*DataBuffer);
			Delay_uS(1000);	
			EEPROM_Read(StartAddress, &ByteCheck,1);
			Delay_uS(100);	

		}while (ByteCheck!=*DataBuffer);
		StartAddress++;
		DataBuffer++;
  	}
   
}
//{
//   WORDBYTE command;
// command.byte[0]|=EEPROM_ADDRESS;	

// I2C3_startBit();
// I2C3_Idle_Bus(); 
// I2C3_Send_Byte(command.byte[0]); //send eeprom address;
// Delay_uS(20);	
// command.word=StartAddress;
 
// I2C3_Send_Byte(command.byte[1]); //send memory address high
// Delay_uS(20);
// I2C3_Send_Byte(command.byte[0]); //send memory address low
// Delay_uS(20);
// while(DataLength)
// {
// 	I2C3_Send_Byte(*DataBuffer); //send data
// 	Delay_uS(20);
//DataBuffer++;
//DataLength--;
////if(!I2C3_Is_AckBit())
// 	//break;
// }
// I2C3_Idle_Bus();
// I2C3_stopBit();
// I2C3_Idle_Bus();
// Delay_uS(20);
// //while (!EEPROM_AckPoll());
//}

BYTE EEPROM_AckPoll(void)
{
 BYTE address=EEPROM_ADDRESS;	

 I2C3_startBit();
 I2C3_Idle_Bus(); 
 I2C3_Send_Byte(address); //send eeprom address;
 Delay_uS(20);	
 return I2C3_Is_AckBit();
 
}


