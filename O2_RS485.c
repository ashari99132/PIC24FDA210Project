/**
O2_RS485.c
**/
#include "ApplicationDrivers.h"
#include "O2_RS485.h"

WORD O2RS485Register[MAX_O2RS485_REG];
WORD O2RS485RxCnt=10;
BYTE O2SendCnt=0;
void Initialize_O2RS485 (void)
{
	//clear the error flag on the sensor
  EventWriteRS485O2Sensor(O2_CLEAR_ERR_FLAG,O2_CLEAR);	
  //RS485O2SensorCmd(WRITE_HOLDING_REGISTER,O2_CLEAR_ERR_FLAG,O2_CLEAR);
  // Delay_uS(50000); 
  //Delay_uS(50000); 	
  //Delay_uS(50000); 
  //turn on the oxygen sensor 
  EventWriteRS485O2Sensor(O2RS485_SENSOR_POWER,SENSOR_ON);	
  //RS485O2SensorCmd(WRITE_HOLDING_REGISTER,O2RS485_SENSOR_POWER,SENSOR_ON);  
  //Delay_uS(50000); 
  //Delay_uS(50000); 
  //Delay_uS(50000); 
}

void Stop_O2RS485 (void)
{
  EventWriteRS485O2Sensor(O2RS485_SENSOR_POWER,SENSOR_OFF);	
  //RS485O2SensorCmd(WRITE_HOLDING_REGISTER,O2RS485_SENSOR_POWER,SENSOR_OFF);
  //Delay_uS(50000);
  //Delay_uS(50000);
  //Delay_uS(50000);

}
void Calibrate_O2RS485 (WORD Value)
{
  EventWriteRS485O2Sensor(O2_CALIB_CONTROL, DFLT_COND);
  EventWriteRS485O2Sensor(O2_CALIB_VALUE,Value);
  EventWriteRS485O2Sensor(O2_CALIB_CONTROL,ACTIVE_COND);

//  RS485O2SensorCmd(WRITE_HOLDING_REGISTER,O2_CALIB_CONTROL,DFLT_COND);
//  Delay_uS(50000);
//  Delay_uS(50000);
//  Delay_uS(50000);
//  RS485O2SensorCmd(WRITE_HOLDING_REGISTER,O2_CALIB_VALUE,Value);
//  Delay_uS(50000);
//  Delay_uS(50000);
//  Delay_uS(50000);
//  RS485O2SensorCmd(WRITE_HOLDING_REGISTER,O2_CALIB_CONTROL,ACTIVE_COND);
//  Delay_uS(50000);
//  Delay_uS(50000);
//  Delay_uS(50000);
}

void EventUpdateRS485O2Sensor (void)
{
 WORD SensorStatus=ReturnFlag(OMB_SENSOR_STATUS_FLAG);
 if(O2RS485RxCnt>=15)
 	{
 		Flush_U2RxBuffer();
 		RS485O2SensorCmd(READ_INPUT_REGISTER,O2_AVERAGE,5); 
		O2RS485RxCnt=0;
                O2SendCnt++;
                if(O2SendCnt>=10)
                {
                 O2SendCnt=10;
                 SensorStatus|=FLAG_O2RS485_ERROR;
                 O2cv=0;
                }
 	}
 
}

void EventUpdateRS485O2Sensor_RxUpdate(void)
{
	 WORD O2RS485_Err_Flag=0;
	 BYTE RxBuffCnt=0;
	 WORD SensorStatus=ReturnFlag(OMB_SENSOR_STATUS_FLAG);
	 ;	
     RxBuffCnt=Return_U2RxBufferCounter();
	 O2RS485RxCnt++;
	 if(RxBuffCnt>=8)
	 {
	      
	   if(RS485_ProcessFrame(READ_INPUT_REGISTER,O2_AVERAGE,5)==1)
		{
                   O2SendCnt=0;
		   O2cv=O2RS485Register[0];

                   O2RS485_Err_Flag=O2RS485Register[4]<<6;
		   SensorStatus&=~(FLAG_O2RS485_PUMP_ERROR|FLAG_O2RS485_HEATER_VOLT_ERROR|FLAG_O2RS485_ASSYMETRY_WARNING|FLAG_O2_BELOW_PT1_WARNING|FLAG_O2RS485_ERROR);
                   SensorStatus|=O2RS485_Err_Flag;
                   if(SensorStatus&(FLAG_O2RS485_PUMP_ERROR|FLAG_O2RS485_HEATER_VOLT_ERROR|FLAG_O2RS485_SELF_SHUTDOWN))
                         SensorStatus|=FLAG_O2RS485_ERROR;
		   SetFlag(OMB_SENSOR_STATUS_FLAG,SensorStatus);
		   Flush_U2RxBuffer();
		   O2RS485RxCnt=15;
		}
  
 }
 
}
//Using PollRX or without receive interrupt. 

//void EventUpdateRS485O2Sensor (void)
//{
// 
// WORD NumOfRegister=5;
// LONG TimeOut=1000000;
// Flush_U2RxBuffer(); 
// RS485O2SensorCmd(READ_INPUT_REGISTER,O2_AVERAGE,NumOfRegister); 
//
// while(UART2_PollByte()<((NumOfRegister*2)+5)  &&  TimeOut-- )
// {
//    if(RS485_ProcessFrame(READ_INPUT_REGISTER,O2_AVERAGE,NumOfRegister))
//     {
//     	O2cv=O2RS485Register[0];
//     	break;
//     }
//  
// }
// 
//}
void EventWriteRS485O2Sensor(WORD startRegister, WORD Value)
{
 
 LONG TimeOut=500000;
 BYTE Retry=0;
 BYTE RxBuffCnt=0;

 Flush_U2RxBuffer();
 RS485O2SensorCmd(WRITE_HOLDING_REGISTER,startRegister,Value); 
  while(RxBuffCnt<=15 && TimeOut-- && Retry <3)
 {
    RxBuffCnt=Return_U2RxBufferCounter(); 	
	if(RS485_ProcessFrame(WRITE_HOLDING_REGISTER,startRegister,Value))
     	break;
	if (!TimeOut && Retry <3)
		{
			TimeOut=500000;
 			Retry++;
			Flush_U2RxBuffer();
			RS485O2SensorCmd(WRITE_HOLDING_REGISTER,startRegister,Value); 			
		}
  }
}
void RS485O2SensorCmd(BYTE function, WORD startRegister, WORD Parameter)
{
 BYTE TxBuff[8];
 WORDTOBYTE temp;	
   TxBuff[0]=OXYRS485_ADDR;
   TxBuff[1]=function;
   temp.word=startRegister;
   TxBuff[2]=temp.bytes[1];
   TxBuff[3]=temp.bytes[0];
   temp.word=Parameter;
   TxBuff[4]=temp.bytes[1];
   TxBuff[5]=temp.bytes[0];
   temp.word=CalcCRC16(&TxBuff[0],6);
   TxBuff[6]=temp.bytes[0];
   TxBuff[7]=temp.bytes[1];
   UART2_TxData(&TxBuff[0],8);
}

BYTE RS485_ProcessFrame(BYTE function, WORD startRegister, WORD Parameter)
{
 BYTE status=0;
 BYTE RxBuffCnt;
 
 
 RxBuffCnt=Return_U2RxBufferCounter();
  
 switch (function)
  {
   case READ_INPUT_REGISTER:   			
   case READ_HOLDING_REGISTER:
   		if(RxBuffCnt >= ((Parameter*2)+5))
   		  status=RS485O2_ProcessReadFunc(startRegister, Parameter);
		break;
   case WRITE_HOLDING_REGISTER:
   		if(RxBuffCnt>=8)
  		  status=RS485O2_ProcessWriteFunc(startRegister,Parameter);	
		break;
	default:
		break;
  }
 
 return status;
}

BYTE RS485O2_ProcessReadFunc(WORD startRegister, WORD RegLength)
{
	BYTE framelength,c,status=0;
	BYTE *pRxBuffer;
	WORDTOBYTE temp;
	framelength=(RegLength*2)+5;
	pRxBuffer=Return_U2RxBuffer();
	temp.bytes[1]=*(pRxBuffer+(framelength-1));
	temp.bytes[0]=*(pRxBuffer+(framelength-2));
	if(temp.word==CalcCRC16(pRxBuffer,framelength-2))
	{
	 for(c=0;c<RegLength;c++)
	 {
	  temp.bytes[0]=*(pRxBuffer+4+(2*c));
	  temp.bytes[1]=*(pRxBuffer+3+(2*c));
	  O2RS485Register[returnO2RS485RegIndex(startRegister+c)]=temp.word;
	 }	 
	 status=1;	
	}
	
	return status;
}

BYTE RS485O2_ProcessWriteFunc(WORD startRegister, WORD Value)
{
	BYTE *pRxBuffer;
	BYTE RegStatus=0;
	WORDTOBYTE temp;
	WORD StartReg_FromBuffer;
	WORD Value_FromBuffer;
	pRxBuffer=Return_U2RxBuffer();
	temp.bytes[1]=*(pRxBuffer+7);
	temp.bytes[0]=*(pRxBuffer+6);
	if(temp.word==CalcCRC16(pRxBuffer,6))
		{
			temp.bytes[0]=*(pRxBuffer+3);
			temp.bytes[1]=*(pRxBuffer+2);
			StartReg_FromBuffer=temp.word;
			temp.bytes[0]=*(pRxBuffer+5);
			temp.bytes[1]=*(pRxBuffer+4);
			Value_FromBuffer=temp.word;			
			if (StartReg_FromBuffer == startRegister && Value_FromBuffer==Value)
					RegStatus=1;
			
			
		}
	return RegStatus;
}

WORD returnO2RS485RegIndex (WORD RegAddress)
{
  BYTE c,val;
  WORD RS485O2RegAddress[MAX_O2RS485_REG]= {
										O2_AVERAGE,      
										O2_RAW, 
										O2_ASSYMETRY,
										O2_SYTEM_STATUS,
										O2_ERROR_WARNING
 };
  
  for (c=0;c<MAX_O2RS485_REG;c++)
  	{
  		if (RegAddress==RS485O2RegAddress[c])val=c;
  	}
  return val;
}
