/**
LTC2439.c
**/
// local includes
#include "HardwareProfile.h"
#include "ApplicationDrivers.h"
#include "LTC2439.h"


//WORD LTC2439RxBuff[MAX_LTC2439_BUFF];
WORD LTC2439RxBuff;

LINT TotalData_LTC2439;

WORD Read_SingleEndedLTC2439(BYTE channel)
{
BYTE Command[5]={0x00,0x00,0x00,0x00,0x00},c;
WORD ADC_Val;
Flush_SPI1_RxBuffer();

Restart_SPI1();
//fisrt new channel
Command[0]=0x80|EN|SGL|channel;

while(!Test_EOC());
Delay_uS(10);
Reset_CS_LTC2439();
Delay_uS(10);
SPI1_TxByte(&Command[0],5);//while(Return_SPI1_RxBuffer_Cnt()<LTC2439_RESP_BYTES)SPI1_TxByte(Command);
Delay_uS(10);
Set_CS_LTC2439();
Delay_uS(10);
//get average value of the channel
 
Command[0]=0;
Command[0]=0x80|SGL|channel;
//for(c=0;c<MAX_LTC2439_BUFF;c++)
//{
	Flush_SPI1_RxBuffer();
	while(!Test_EOC());
	Delay_uS(100);
	Reset_CS_LTC2439();
	Delay_uS(10); 
	SPI1_TxByte(&Command[0],5);
	Delay_uS(10);
	Set_CS_LTC2439();
	Delay_uS(10);
	//LTC2439RxBuff[c]=Parse_LTC2439Data(); 
	LTC2439RxBuff=Parse_LTC2439Data(); 
//}
	Set_CS_LTC2439();
	//ADC_Val=LTC2439RxBuff[2]-COM_PIN;
	ADC_Val=LTC2439RxBuff-COM_PIN;
	return ADC_Val;
}

WORD  Parse_LTC2439Data (void)
{
 FLOATTOBYTE tempFloat;
 
 WORDTOBYTE tempWord;
 BYTE *pSPI1data,c;
 pSPI1data=Return_SPI1_RxBuffer();
 tempFloat.bytes[3]=0;
 tempFloat.bytes[2]=*(pSPI1data);
 tempFloat.bytes[1]=*(pSPI1data+1);
 tempFloat.bytes[0]=*(pSPI1data+2);
 c=tempFloat.bytes[0];
 tempWord.bytes[0]= c>>5;
 c=tempFloat.bytes[1];
 c<<=3;
 tempWord.bytes[0]|=c;
 c=tempFloat.bytes[1];
 c>>=5;
 tempWord.bytes[1]=c;
 c=tempFloat.bytes[2];
c<<=3;
 tempWord.bytes[1]|=c;

return tempWord.word;
  	
}
BYTE Test_EOC(void)
{
 
 BYTE EOC_Stat=0;
 WORD PortFStat=0;
 
 Reset_CS_LTC2439();
 Delay_uS(10);
 
 PortFStat=PORTF;
 if(PortFStat & 0x0004)EOC_Stat=0;
 else EOC_Stat=1;
 

 Set_CS_LTC2439();
 Delay_uS(10);
 return EOC_Stat;
 
}

