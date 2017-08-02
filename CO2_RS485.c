/**
CO2_RS485.c
**/
#include "ApplicationDrivers.h"
#include "CO2_RS485.h"

char CO2RS485_FinalBuffer[MAX_CO2RS485_BUFF];
WORD CO2RS485_RxReadCnt=0;
BYTE SendCount=0;
void EventUpdateRS485CO2Sensor (void)
{
 BYTE c;
 WORD SensorStatus=ReturnFlag(OMB_SENSOR_STATUS_FLAG);
 if(CO2RS485_RxReadCnt>=10)
 {
 	UART1_TxString("\rsend\r");
 	for(c=0;c<MAX_CO2RS485_BUFF;c++) CO2RS485_FinalBuffer[c]=0;
	Flush_U1RxBuffer(); 
	CO2RS485_RxReadCnt=0;
        SendCount++;
        if(SendCount>=10)
        {
         CO2cv=0;
         SensorStatus|=FLAG_IRCO2_ERROR;
         SendCount=10;
         SetFlag(OMB_SENSOR_STATUS_FLAG,SensorStatus);
        }
 }
}
void EventRS485CO2Sensor_RxUpdate (void)
{
	BYTE DataLenRx,c,d=0;
	LONG CO2ppm;
	BYTE *pU1RxBuffer;
	WORD SensorStatus=ReturnFlag(OMB_SENSOR_STATUS_FLAG);
	CO2RS485_RxReadCnt++;
	pU1RxBuffer=Return_U1RxBuffer();
	DataLenRx=Return_U1RxBufferCounter();
	for (c=0;c<DataLenRx;c++)
	{
		if(*(pU1RxBuffer+c)==0x0d)
			{
				d=1;
				break;
			}
		else d=0;
	}
		
	if(d)
	{
				c=0;d=0;
				while(*(pU1RxBuffer+c)!='=')c++; //new format GMP reading by factory default is 'CO2=123456 ppm\r'. 
				while(*(pU1RxBuffer+c)!=0x0d)
					{
					if (*(pU1RxBuffer+c)>='0' && *(pU1RxBuffer+c)<='9')
						{
							CO2RS485_FinalBuffer[d]=*(pU1RxBuffer+c);
							d++;	
						}
					else if (*(pU1RxBuffer+c)=='*') 
						{
                                                        CO2cv=0;
							SensorStatus|=FLAG_IRCO2_ERROR;
							break;
						}						
					c++; 
					}
				if (d>0)
					{
						SensorStatus&=~FLAG_IRCO2_ERROR;
						CO2ppm=StringToLONG(&CO2RS485_FinalBuffer[0]);
						CO2cv=CO2ppm/100;
						Flush_U1RxBuffer();
						CO2RS485_RxReadCnt=10;
                                                SendCount=0;
					}
			
				   
		 }
	SetFlag(OMB_SENSOR_STATUS_FLAG,SensorStatus);
}


//void EventRS485CO2Sensor_RxUpdate (void)
//{
//	BYTE DataLenRx,c,d=0;
//	LONG CO2ppm;
//	BYTE *pU1RxBuffer;
//	WORD SensorStatus=ReturnFlag(OMB_SENSOR_STATUS_FLAG);
//	CO2RS485_RxReadCnt++;
//	SensorStatus&=~FLAG_IRCO2_ERROR;
//	pU1RxBuffer=Return_U1RxBuffer();
//	DataLenRx=Return_U1RxBufferCounter();
//	for (c=0;c<DataLenRx;c++)
//	{
//		if(*(pU1RxBuffer+c)==0x0d)
//			{
//				d=1;
//				break;
//			}
//		else d=0;
//	}
//		
//	if(d)
//	{
//				c=0;d=0;
//				while(*(pU1RxBuffer+c)!=0x0d)
//					{
//					if (*(pU1RxBuffer+c)>='0' && *(pU1RxBuffer+c)<='9')
//						{
//							CO2RS485_FinalBuffer[d]=*(pU1RxBuffer+c);
//							d++;	
//						}
//					else if (*(pU1RxBuffer+c)=='*') 
//						{
//							SensorStatus|=FLAG_IRCO2_ERROR;
//							break;
//						}						
//					c++; 
//					}
//				if (d>0)
//					{
//						SensorStatus&=~FLAG_IRCO2_ERROR;
//						CO2ppm=StringToLONG(&CO2RS485_FinalBuffer[0]);
//						CO2cv=CO2ppm/100;
//						Flush_U1RxBuffer();
//						CO2RS485_RxReadCnt=10;
//					}
//			
//				   
//		 }
//	SetFlag(OMB_SENSOR_STATUS_FLAG,SensorStatus);
//}

