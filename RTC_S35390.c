/**
RTC_S35390.c
**/

// local includes
//#include "HardwareProfile.h"
#include "ApplicationDrivers.h"
#include "p24FJ256DA210_I2C3.h"
#include "RTC_S35390.h"


//global

BYTE S35390_DataBuffer[MAX_RTC_BUFF];
WORD YearBuffer;
BYTE MonthBuffer;
BYTE DayBuffer;
BYTE HourBuffer;
BYTE MinuteBuffer;
BYTE SecondsBuffer;


void s35390_Read(BYTE command, BYTE dataLength)
{
 command|=RTC_ADDRESS;	
 command|=0x01;	

 I2C3_startBit();
 I2C3_Idle_Bus(); 
 I2C3_Send_Byte(command); //send address;
 Delay_uS(20);	
  while(dataLength>1)//get data
 {
  I2C3_MasterReceive_Enable();	 
  S35390_DataBuffer[MAX_RTC_BUFF-dataLength]=I2C3_Receive_Byte();
  I2C3_Idle_Bus();
  I2C3_Send_Ack();
  I2C3_Idle_Bus();
  dataLength--;
 }
I2C3_MasterReceive_Enable();	 
S35390_DataBuffer[MAX_RTC_BUFF-dataLength]=I2C3_Receive_Byte();
 I2C3_Idle_Bus();
 I2C3_Send_NAck();
 I2C3_Idle_Bus();
 Delay_uS(20);	
 I2C3_stopBit();
 I2C3_Idle_Bus();
 Delay_uS(20);	
 I2C3_stopBit(); 
}


void s35390_Write(BYTE command, BYTE dataLength)
{
 command|=RTC_ADDRESS;		
 command&=~(0x01);
I2C3_startBit();
 I2C3_Idle_Bus(); 
 I2C3_Send_Byte(command); //send address;
 Delay_uS(20);	
 while(dataLength>0)//get data
 {
  I2C3_Send_Byte(S35390_DataBuffer[MAX_RTC_BUFF-dataLength]);
  //I2C3_Idle_Bus();
  Delay_uS(20);
  if(!I2C3_Is_AckBit())
   	break;	 
 dataLength--;
 }
I2C3_Idle_Bus();
 I2C3_Send_NAck();
 I2C3_Idle_Bus();
 Delay_uS(20);	
 I2C3_stopBit();
 I2C3_Idle_Bus();
 Delay_uS(20);	
 I2C3_stopBit(); 
}


void s35390_Initialize(void)
{
  //reset RTC
  S35390_DataBuffer[0]=STAT1_RESET;
  s35390_Write(STAT1_REG,1);
  
  //configure to 24Hours mode
  S35390_DataBuffer[0]=STAT1_HRS_24;
  s35390_Write(STAT1_REG,1);
  
  //clear real time register 1
  s35390_FlushBuffer();
  s35390_Write(RT1_REG,7);
  
  //use interrupt 1
  S35390_DataBuffer[0]=OUTPUT_USER_FREQ_INT1;
  s35390_Write(RT2_REG,1);
  
  //set interrupt 1 to 1Hz
  S35390_DataBuffer[0]=Hz_1;
  s35390_Write(INT1_REG,1);
  
  //flush buffer for preparation
  s35390_FlushBuffer();
}

char S35390_ConvertRTData(char dataBuffer, char Direction)
{
	char Add[8]={1,2,4,8,10,20,40,80};
	char Bit[8]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
	signed char c=0;
	char result=0;
	int temp;
	switch(Direction)
	{
          case(TO_S35390):
		for(c=7;c>(-1);c--)
		      {
			temp=dataBuffer-Add[c];
			if(temp>=0)
                        {
                          result|=Bit[c];
			  dataBuffer=temp;
                        }
		      }
		break;
	 case(FROM_S35390):
               for(c=7;c>(-1);c--)
		{
		  if(dataBuffer&0x01)result+=Add[c];
		  dataBuffer>>=1;	
		}			
		break;
	}
	
	return result;
}


char CompileStringTo_S35390_RT1Data(char *String)
{
  char Temp = 0x00;
  
  Temp=*(String);
  Temp-='0';
  Temp*=10;
  Temp+=*(String+1);
  Temp-='0';
   
  Temp=S35390_ConvertRTData(Temp,TO_S35390); 
  return Temp;
}
void s35390_GetDate_And_Time(void)
{
 //read time and date from RT1 reg	
 s35390_FlushBuffer();	
 s35390_Read(RT1_REG,7);
 
 //compile the time and date to readable format
 YearBuffer =S35390_ConvertRTData(S35390_DataBuffer[0],FROM_S35390) ;
 YearBuffer +=2000; 
 MonthBuffer=S35390_ConvertRTData(S35390_DataBuffer[1],FROM_S35390) ;
 DayBuffer=S35390_ConvertRTData(S35390_DataBuffer[2],FROM_S35390) ;
 HourBuffer=S35390_ConvertRTData(S35390_DataBuffer[4],FROM_S35390) ;
 if(HourBuffer>40)HourBuffer-=40;
 MinuteBuffer=S35390_ConvertRTData(S35390_DataBuffer[5],FROM_S35390);
 SecondsBuffer=S35390_ConvertRTData(S35390_DataBuffer[6],FROM_S35390);
}

void s35390_SetTime(BYTE Hour, BYTE Minutes, BYTE Seconds)
{
 //read time and date from RT1 reg	
 s35390_FlushBuffer();	
 s35390_Read(RT1_REG,7);
 
 //compile the time to S35390 format
 S35390_DataBuffer[4]=S35390_ConvertRTData(Hour,TO_S35390);
 S35390_DataBuffer[5]=S35390_ConvertRTData(Minutes,TO_S35390);
 S35390_DataBuffer[6]=	S35390_ConvertRTData(Seconds,TO_S35390);
 
 //write the time to S35390
 s35390_Write(RT1_REG,7);

}
void s35390_SetDate(WORD Year, BYTE Month, BYTE Day)
{
//read time and date from RT1 reg	
 s35390_FlushBuffer();	
 s35390_Read(RT1_REG,7);
 
 //compile the date to S35390 format
 Year-=2000;
 S35390_DataBuffer[0]=S35390_ConvertRTData((char)Year,TO_S35390);
 S35390_DataBuffer[1]=S35390_ConvertRTData(Month,TO_S35390);
 S35390_DataBuffer[2]=S35390_ConvertRTData(Day,TO_S35390);
 
 //write the date to S35390
 s35390_Write(RT1_REG,7);
}
void s35390_FlushBuffer(void)
{
BYTE c;
for(c=0;c<MAX_RTC_BUFF;c++)
  S35390_DataBuffer[c]=0;
}
