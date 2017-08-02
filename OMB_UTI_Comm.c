/**
OMB_UTI_Comm.c

Read frame command will be[03h][RegAdd High][RegAdd low][Number of Regsiters] [CRC16 high][CRC16 low]
Write frame command will be[06h][RegAdd High][RegAdd Low][Val High] [Val Low] [CRC16 high][CRC16 low] for word write


**/
#include "ApplicationDrivers.h"
#include "OMB_UTI_Comm.h"

WORD RegAddres_Write;
WORD Reg_Write_Val;

RXFRAME I2C1_DataFrame;
const REGISTER CLSRegister[MAX_NUMBER_OF_CLSREGISTER]={
							{&OMB_Software_Ver,WORD_RAM,R_REG,NO_EEPROM_ADDR},	//0--
							{&Tcv,WORD_RAM,R_REG,NO_EEPROM_ADDR},				//1--chamber temperature current value (x100) read from PT100
							{&Rpt100,WORD_RAM,R_REG,NO_EEPROM_ADDR},			//2--PT 100 resistance in ohm
							{&ADCpt100,WORD_RAM,R_REG,NO_EEPROM_ADDR},			//3--ADC value of PT100 in current R		
							{&Tamb,WORD_RAM,R_REG,NO_EEPROM_ADDR},				//4--temperature current value (x100) read from NTC for reservoir heater
							{&Rntc, WORD_RAM,R_REG,NO_EEPROM_ADDR}, 			//5--Resistance from ntc channel in ohm
							{&ADCntc,WORD_RAM,R_REG,NO_EEPROM_ADDR},			//6--Raw ADC value of this channel
							{&CO2cv,WORD_RAM,R_REG,NO_EEPROM_ADDR},				//7--TCCO2 current value
							{&Vtc,WORD_RAM,R_REG,NO_EEPROM_ADDR},			//8--Voltage from TCCO2 sensor channel in mV
							{&ADCtc ,WORD_RAM,R_REG,NO_EEPROM_ADDR},			//9--Raw ADC value of this channel
							{&RHcv,WORD_RAM,R_REG,NO_EEPROM_ADDR},				//10--RH current value
							{&Vopt2,WORD_RAM,R_REG,NO_EEPROM_ADDR},				//11--Voltage from optional channel 2 in mV
							{&ADCopt2,WORD_RAM,R_REG,NO_EEPROM_ADDR},			//12--Raw ADC value of this channel
							{&O2cv,WORD_RAM,R_REG,NO_EEPROM_ADDR},				//13--02 current value
							{&Vopt1,WORD_RAM,R_REG,NO_EEPROM_ADDR},				//14--Voltage from optional channel 1 in mV
							{&ADCopt1,WORD_RAM,R_REG,NO_EEPROM_ADDR},			//15--Raw ADC value of this channel
							{&Flag[OMB_OUTPUTS_FLAG],WORD_RAM,RW_REG,NO_EEPROM_ADDR},		//16--on and off the shaker output on OMB board.
							{&Flag[OMB_SWITCHES_STATUS_FLAG],WORD_RAM,R_REG,NO_EEPROM_ADDR},//17--Switches_Status on OMB
							{&Flag[OMB_ALARM_STATUS_FLAG],WORD_RAM,R_REG,NO_EEPROM_ADDR},	//18--Alarm status for all controls  on OMB
							{&Flag[OMB_SENSOR_STATUS_FLAG],WORD_RAM,R_REG,NO_EEPROM_ADDR},	//19--Sensor statuses on OMB
							{&Tsp,WORD_EEPROM,RW_REG,0x0000},					//20--temperature set point 	(x100)
							{(WORD*)&Tcv_Offset,WORD_EEPROM,RW_REG,0x0024},		//21--Offset reading for temperature current value
							{&Tsp_ha,WORD_EEPROM,RW_REG,0x0002},				//22--temperature high alarm set point (x100)
							{&Tsp_la,WORD_EEPROM,RW_REG,0x0004},				//23--temperature low alarm set point (x100)							 
							{&Tsp_da,WORD_EEPROM,RW_REG,0x0006},				//24--temperature deviation alarm set point (x100)
							{&T_pnum,WORD_EEPROM,RW_REG,0x0008},				//25--temp control: p gain numerator
							{&T_pdnum,WORD_EEPROM,RW_REG,0x000A},				//26--temp control: p gain denumerator
							{&T_inum,WORD_EEPROM,RW_REG,0x000C},				//27--temp control: i gain numerator
							{&T_idnum,WORD_EEPROM,RW_REG,0x000E},				//28--temp control: i gain denumerator
							{&Rpt100_Rmin,WORD_EEPROM,RW_REG,0x0014},			//29--PT100 Rmin value for calibration
							{&Rpt100_Rnom,WORD_EEPROM,RW_REG,0x0016},   		//30--PT100 Rnom value for calibration 
							{&Rpt100_ADCmin,WORD_EEPROM,RW_REG,0x0018},  		//31--ADC value of PT100 in Rmin for calibration
							{&Rpt100_ADCnom,WORD_EEPROM,RW_REG,0x001A}, 		//32--ADC value of PT100 in Rnom for calibration
							{(WORD*)&CO2cv_Offset,WORD_EEPROM,RW_REG,0x0048},	//33--Offset reading for CO2 level current value 
							{&IRCO2_Slope,WORD_EEPROM,RW_REG,0x002A},			//34--slope for IRCO2 in mv/%CO2
							{&IRCO2_Offset,WORD_EEPROM,RW_REG,0x002C},			//35--offset for IRCO2 in mV
							{&CO2sp,WORD_EEPROM,RW_REG,0x002E},					//36--CO2 set point
							{&CO2_ha,WORD_EEPROM,RW_REG,0x0030},				//37--CO2 high alarm
							{&CO2_la,WORD_EEPROM,RW_REG,0x0032},				//38--CO2 low alarm 
							{&CO2_pnum,WORD_EEPROM,RW_REG,0x0034},				//39--CO2 level P numerator
							{&CO2_pdnum,WORD_EEPROM,RW_REG,0x0036},				//40--CO2 level P denumerator
							{&CO2_inum,WORD_EEPROM,RW_REG,0x0038},				//41--CO2 level I numerator
							{&CO2_idnum,WORD_EEPROM,RW_REG,0x003A},				//42--CO2 level I denumerator
							{&Rntc_Rmin,WORD_EEPROM,RW_REG,0x001C}, 			//43--Resistance min from ntc channel for calibration
							{&Rntc_Rnom,WORD_EEPROM,RW_REG,0x001E}, 			//44--Resistance rnom from ntc channel for calibration
							{&Rntc_ADCmin,WORD_EEPROM,RW_REG,0x0020},			//45--ADC min value for analog channel calibration of NTC
							{&Rntc_ADCnom,WORD_EEPROM,RW_REG,0x0022},			//46--ADC nom value for analog channel calibration of NTC
							{&NTCsp,WORD_EEPROM,RW_REG,0x0042},					//47--NTC Set point for RH Control using NTC
							{(WORD*)&RHcv_Offset,WORD_EEPROM,RW_REG,0x003C},	//48--Offset reading for RH level current value 
							{&RHsp,WORD_EEPROM,RW_REG,0x004A},					//49--RH high alarm set point
							{&RH_ha,WORD_EEPROM,RW_REG,0x004C},					//50--RH low alarm set point
							{&RH_la,WORD_EEPROM,RW_REG,0x004E},					//51--RH low alarm set point
							{&RH_pnum,WORD_EEPROM,RW_REG,0x0050},				//52--RH level P numerator
							{&RH_pdnum,WORD_EEPROM,RW_REG,0x0052},				//53--RH level P denumerator
							{&RH_inum,WORD_EEPROM,RW_REG,0x0054},				//54--RH level I numerator
							{&RH_idnum,WORD_EEPROM,RW_REG,0x0056},				//55--RH level I denumerator
							{&Vopt2_ADCmin,WORD_EEPROM,RW_REG,0x0058},			//56--ADC min value for analog channel calibration of optional channel 2
							{&Vopt2_ADCnom,WORD_EEPROM,RW_REG,0x005A},			//57--ADC nom value for analog channel calibration of optional channel 2
							{&RH_Slope,WORD_EEPROM,RW_REG,0x005C},				//58--slope for RH sensor   in mV/%RH
							{&RH_Offset,WORD_EEPROM,RW_REG,0x005E},				//59--slope for RH offset   in mV
							{&O2cv_Offset,WORD_EEPROM,RW_REG,0x0040},	//60--Offset reading for 02 level current value
							{&O2sp,WORD_EEPROM,RW_REG,0x0060},					//61--02 high alarm set point
							{&O2_ha,WORD_EEPROM,RW_REG,0x0062},					//62--02 low alarm set point
							{&O2_la,WORD_EEPROM,RW_REG,0x0064},					//63--02 low alarm set point
							{&O2_pnum,WORD_EEPROM,RW_REG,0x0066},				//64--02 level P numerator
							{&O2_pdnum,WORD_EEPROM,RW_REG,0x0068},				//65--02 level P denumerator
							{&O2_inum,WORD_EEPROM,RW_REG,0x006A},				//66--02 level I numerator
							{&O2_idnum,WORD_EEPROM,RW_REG,0x006C},				//67--02 level I denumerator
							{&Vopt1_ADCmin,WORD_EEPROM,RW_REG,0x006E},			//68--ADC min value for analog channel calibration of optional channel 1
							{&Vopt1_ADCnom,WORD_EEPROM,RW_REG,0x0070},			//69--ADC nom value for analog channel calibration of optional channel 1
							{&O2_Slope,WORD_EEPROM,RW_REG,0x0072},				//70--slope for 02 sensor   in mV/%RH
							{&O2_Offset,WORD_EEPROM,RW_REG,0x0074},				//71--slope for 02 offset   in mV
							{&UV_RunTimer,WORD_EEPROM,RW_REG,UVRUNTIME_EEPROM},	//72--UV lamp on running timer
							{&Flag[ALRELAY_FLAG],WORD_EEPROM,RW_REG,0x007C},	//73--Alarm relay flag logic configuration on CelSafe
							{&Flag[SYSTEM_MODE_FLAG],WORD_EEPROM,RW_REG,0x007E},//74--Run mode selection of the OMB
							{&CelSafeOptions,WORD_EEPROM,RW_REG,0x0080},//75--yes and no options for CelSafe model
							//{&Flag[OMB_CELSAFE_OPT_FLAG],WORD_EEPROM,RW_REG,0x0080},//75--yes and no options for CelSafe model
							{&Base_Htr_PR,WORD_EEPROM,RW_REG,0x0086},			//76--
							{&Door_Htr_PR,WORD_EEPROM,RW_REG,0x0088},			//77--
							{&Decon_Htr_PR,WORD_EEPROM,RW_REG,0x008A},			//78--
							{&AppConfig.MyIPAddr.w[0],WORD_RAM,R_REG,NO_EEPROM_ADDR}, //79 IP.Address low word
							{&AppConfig.MyIPAddr.w[1],WORD_RAM,R_REG,NO_EEPROM_ADDR}, //80 IP.Address hi word							//{&Grow_Light_RunTimer,WORD_EEPROM,RW_REG,GROWLIGHTRUNTIME_EEPROM},//Grow light on running timer							//{&IRCO2cv,WORD_RAM,R_REG,NO_EEPROM_ADDR},			//4--IRCO2 current value
							//{&Vvsl,WORD_RAM,R_REG,NO_EEPROM_ADDR},				//5--Voltage from CO2 vaisala in mV
							//{&ADCvsl,WORD_RAM,R_REG,NO_EEPROM_ADDR},			//6--Raw ADC value of this channel
							//{&Ktn,WORD_EEPROM,RW_REG,0x0010},			//11--temp control: normalization constant
							//{&Pan_Heater_Ratio,WORD_EEPROM,RW_REG,0x0012},	//12--temp control: pan heater power ratio constant
							//{&Vvsl_ADCmin,WORD_EEPROM,RW_REG,0x0026},//28--ADC min value for analog channel calibration of Vaisala IR CO2
							//{&Vvsl_ADCnom,WORD_EEPROM,RW_REG,0x0028},//29--ADC nom value for analog channel calibration of Vaisala IR CO2
							//{&PT100_Tmin,WORD_EEPROM,RW_REG,0x0082}, //87--PT100 Tmin in oCx100 for calibration purpose
							//{&PT100_Tnom,WORD_EEPROM,RW_REG,0x0084},//88--PT100 Tnom in oCx100 for calibration purpose
							//{&Vtc_ADCmin,WORD_EEPROM,RW_REG,0x003E},			//43--ADC min value for analog channel calibration of TCCO2
							//{&Vtc_ADCnom,WORD_EEPROM,RW_REG,0x0040},			//44--ADC nom value for analog channel calibration of TCCO2
							//{&TC_0,WORD_EEPROM,RW_REG,0x0042},					//45--constant 0% for TCCO2 in mV;
							//{&TC_5,WORD_EEPROM,RW_REG,0x0044},					//46--constant 5% for TCCO2 in mV;
							//{&TC_15,WORD_EEPROM,RW_REG,0x0046},					//47--constant 15% for TCCO2 in mV;

						};


void EventUpdateUTI_Communication(void)
{
 
  if( Is_I2C1_FrameData_Valid()) 	//if receive frame is valid
     		 Process_I2C1_FrameData();	//then process the receive frame data
//  SetIntDrivenEventFlag(0,INT_UTI);
  
}

BYTE Is_I2C1_FrameData_Valid(void)
{
	
	WORDTOBYTE tempData;
	BYTE *pI2C1_RxDataBuff;
	pI2C1_RxDataBuff=ReturnI2C1_RxDataBuffer();
	
	CompileRxBufferToFrame();
	
	tempData.bytes[0]=I2C1_DataFrame.Crc[0];
	tempData.bytes[1]=I2C1_DataFrame.Crc[1];
	if(tempData.word == CalcCRC16((pI2C1_RxDataBuff+1), I2C1_DataFrame.dataLength)) 
			return 1;
	return 0;
}
void Process_I2C1_FrameData(void)
{
	switch(I2C1_DataFrame.Command)
	{
		case READ_FUNC:
			 Process_I2C1_ReadFunction();
			 break;		
		case WRITE_FUNC:
			Process_I2C1_WriteFunction();
			break;
	}
}

void Process_I2C1_ReadFunction(void)
{	
	WORDTOBYTE tempWord;
	BYTE c,d;
	WORD RegAddress=I2C1_DataFrame.RegAddress;
	BYTE NumOfReg=I2C1_DataFrame.Data[0];
	BYTE *pTxData;
	pTxData=ReturnI2C1_TxBuffer();
	//if the register address, and number of register is correct then process the read function 
	if( (RegAddress + NumOfReg) <=MAX_NUMBER_OF_CLSREGISTER)
		 {
			c=0;
		   *(pTxData+c)=OMB_ADDR_BRD;c++;   //board address
		   *(pTxData+c)=READ_FUNC;c++;		//function
		    tempWord.word=RegAddress;
		    *(pTxData+c)=tempWord.bytes[1];c++;		//RegAddress high
			*(pTxData+c)=tempWord.bytes[0];c++;		//RegAddress Low
		   *(pTxData+c)=(NumOfReg*2);c++;   //byte count
		   
		   
		   for(d=RegAddress;d<RegAddress+NumOfReg;d++)
		   {
		     	     
		     	tempWord.word=*CLSRegister[d].RegData;
		     	*(pTxData+c)=tempWord.bytes[1];c++;
		     	*(pTxData+c)=tempWord.bytes[0];c++;	
		     	
		   }  
		     
		     tempWord.word=CalcCRC16(pTxData+1,c-1);
		     *(pTxData+c)=tempWord.bytes[1];c++;
		     *(pTxData+c)=tempWord.bytes[0];c++;		     
		    		 
		 }
	else SendException_ReadFunction();
	Flush_I2C1RxBuffer(); 
	Flush_I2C1FrameBuff();

}
void Process_I2C1_WriteFunction(void)
{
	WORDTOBYTE tempWord;
	BYTE d;
	BYTE *pTxData,*pRxData;
	RegAddres_Write=I2C1_DataFrame.RegAddress;
	pTxData=ReturnI2C1_TxBuffer();
	pRxData=ReturnI2C1_RxDataBuffer();
	tempWord.bytes[0]=I2C1_DataFrame.Data[0];
	tempWord.bytes[1]=I2C1_DataFrame.Data[1];
	Reg_Write_Val=tempWord.word;
	//if the register address and the  WR flag is match then  
	if( CLSRegister[RegAddres_Write].RegRW==RW_REG)
		 {
		    *(CLSRegister[RegAddres_Write].RegData)=tempWord.word;
		    for(d=0;d<MAX_I2C1_RXBUFF;d++)*(pTxData+d)=*(pRxData+d);
		  	SetIntDrivenEventFlag(SET,INT_UTI_WRITE);
				   
		  }
	else SendException_WriteFunction();
	Flush_I2C1RxBuffer();
	Flush_I2C1FrameBuff();
}

void SendException_ReadFunction(void)
{
	WORDTOBYTE tempWord;
	BYTE c=0;
	BYTE *pTxData;
	pTxData=ReturnI2C1_TxBuffer();
	*(pTxData+c)=OMB_ADDR_BRD;c++;
	*(pTxData+c)=READ_FUNC;c++;
	*(pTxData+c)=0x03;c++;
	tempWord.word=CalcCRC16(pTxData+1,c-1);
	*(pTxData+c)=tempWord.bytes[1];c++;
	*(pTxData+c)=tempWord.bytes[0];c++; 	
}
void SendException_WriteFunction(void)
{
	WORDTOBYTE tempWord;
	BYTE c=0;
	BYTE *pTxData;
	pTxData=ReturnI2C1_TxBuffer();
	*(pTxData+c)=OMB_ADDR_BRD;c++;
	*(pTxData+c)=WRITE_FUNC;c++;
	*(pTxData+c)=0x03;c++;
	tempWord.word=CalcCRC16(pTxData+1,c-1);
	*(pTxData+c)=tempWord.bytes[1];c++;
	*(pTxData+c)=tempWord.bytes[0];c++; 	
}

void CompileRxBufferToFrame(void)
{
 	BYTE *pI2C1_RxDataBuff;
//	BYTE  I2C1_RxDataCnt=ReturnCounter_I2C1RxBuffer();
	WORDTOBYTE regAddr;
	pI2C1_RxDataBuff=ReturnI2C1_RxDataBuffer();
	I2C1_DataFrame.Command=*(pI2C1_RxDataBuff+1);
	regAddr.bytes[0]=*(pI2C1_RxDataBuff+3);
	regAddr.bytes[1]=*(pI2C1_RxDataBuff+2);
	I2C1_DataFrame.RegAddress=regAddr.word; 	
	if(I2C1_DataFrame.Command==READ_FUNC)
	{
	I2C1_DataFrame.Data[0]=*(pI2C1_RxDataBuff+4); 
	I2C1_DataFrame.Data[1]=0; 
	I2C1_DataFrame.Data[2]=0; 
	I2C1_DataFrame.Data[3]=0; 
	I2C1_DataFrame.Crc[0]=*(pI2C1_RxDataBuff+6);
	I2C1_DataFrame.Crc[1]=*(pI2C1_RxDataBuff+5);
	I2C1_DataFrame.dataLength=READ_CMD_BYTELENGTH-3;			
	}
	else if(I2C1_DataFrame.Command==WRITE_FUNC)
	{
	I2C1_DataFrame.dataLength=WORD_WRITE_CMD_BYTELENGTH-3;			
	I2C1_DataFrame.Data[0]=*(pI2C1_RxDataBuff+5); 
	I2C1_DataFrame.Data[1]=*(pI2C1_RxDataBuff+4);  
	I2C1_DataFrame.Data[2]=0; 
	I2C1_DataFrame.Data[3]=0; 
	I2C1_DataFrame.Crc[0]=*(pI2C1_RxDataBuff+7);
	I2C1_DataFrame.Crc[1]=*(pI2C1_RxDataBuff+6);
	}
		
	
	
}
	

//BYTE CompileRxBufferToFrame(void)
//{
// 	BYTE *pI2C1_RxDataBuff;
//	BYTE  I2C1_RxDataCnt=ReturnCounter_I2C1RxBuffer();
//	WORDBYTE regAddr;
//	pI2C1_RxDataBuff=ReturnI2C1_RxDataBuffer();
//	switch (I2C1_RxDataCnt)
//	{
//		case READ_CMD_BYTELENGTH:	
//			I2C1_DataFrame.Command=*(pI2C1_RxDataBuff+1);
//			if(I2C1_DataFrame.Command!=READ_FUNC)
//				return 0;
//			regAddr.byte[0]=*(pI2C1_RxDataBuff+3);
//			regAddr.byte[1]=*(pI2C1_RxDataBuff+2);
//			I2C1_DataFrame.RegAddress=regAddr.word; 	
//			I2C1_DataFrame.dataLength=READ_CMD_BYTELENGTH-3;			
//			I2C1_DataFrame.Data[0]=*(pI2C1_RxDataBuff+4); 
//			I2C1_DataFrame.Data[1]=0; 
//			I2C1_DataFrame.Data[2]=0; 
//			I2C1_DataFrame.Data[3]=0; 
//			I2C1_DataFrame.Crc[0]=*(pI2C1_RxDataBuff+6);
//			I2C1_DataFrame.Crc[1]=*(pI2C1_RxDataBuff+5);	
//			return 1;
//		case WORD_WRITE_CMD_BYTELENGTH:
//			I2C1_DataFrame.Command=*(pI2C1_RxDataBuff+1);
//			if(I2C1_DataFrame.Command!=WRITE_FUNC)
//				return 0;
//			regAddr.byte[0]=*(pI2C1_RxDataBuff+3);
//			regAddr.byte[1]=*(pI2C1_RxDataBuff+2);
//			I2C1_DataFrame.RegAddress=regAddr.word; 	
//			I2C1_DataFrame.dataLength=WORD_WRITE_CMD_BYTELENGTH-3;			
//			I2C1_DataFrame.Data[0]=*(pI2C1_RxDataBuff+5); 
//			I2C1_DataFrame.Data[1]=*(pI2C1_RxDataBuff+4);  
//			I2C1_DataFrame.Data[2]=0; 
//			I2C1_DataFrame.Data[3]=0; 
//			I2C1_DataFrame.Crc[0]=*(pI2C1_RxDataBuff+7);
//			I2C1_DataFrame.Crc[1]=*(pI2C1_RxDataBuff+6);
//			return 1;
//		default:
//			return 0;
//	}
//	
//}
void ReadShakerRegisterFromEEPROM(void)
{
 BYTE c;
WORDTOBYTE tempValue;
WORD *pShort;
pShort=&RHcv_Offset;
*pShort=0;
pShort=&O2cv_Offset;
*pShort=0;
pShort=&CO2cv_Offset;
*pShort=0;
pShort=&Tcv_Offset;
*pShort=0;
pShort=&Rpt100_Rmin;
*pShort=PT100_DEFAULT_RMIN;//Min Resistance for calibration;
pShort=&Rpt100_Rnom;
*pShort=PT100_DEFAULT_RNOM;//Nom Resistance for calibration
pShort=&Rpt100_ADCmin;
*pShort=PT100_DEFAULT_ADCMIN;	//ADC min value for analog channel calibration of Pt100
pShort=&Rpt100_ADCnom;
*pShort=PT100_DEFAULT_ADCNOM;	//ADC nom value for analog channel calibration of Pt100

pShort=&Tsp;
*pShort=3700;	  	//Temperature set point
pShort=&Tsp_ha;
*pShort=3800;		//Temperature set point high alarm
pShort=&Tsp_la;
*pShort=3600;		//Temperature set point low alarm
pShort=&Tsp_da;
*pShort=500; 		//Temperature set point deviation alarm
pShort=&T_pnum;
*pShort=T_PNUM_DEFAULT;		//Temperature P numerator
pShort=&T_pdnum;
*pShort=T_PDNUM_DEFAULT;		//Temperature P denumerator
pShort=&T_inum;
*pShort=T_INUM_DEFAULT;		//Temperature i numerator
pShort=&T_idnum;
*pShort=T_IDNUM_DEFAULT;		//Temperature i denumerator
pShort=&Pan_Heater_Ratio;
*pShort=PAN_HEAT_RATIO_DEFAULT;
pShort=&Base_Htr_PR;
*pShort=POWER_RATIO_DFLT;
pShort=&Door_Htr_PR;
*pShort=POWER_RATIO_DFLT;
pShort=&Decon_Htr_PR;
*pShort=POWER_RATIO_DFLT;


pShort=&CO2sp;
*pShort=500;	  	//set point
pShort=&CO2_ha;
*pShort=600;		//set point high alarm
pShort=&CO2_la;
*pShort=400;		//set point low alarm
pShort=&CO2_pnum;
*pShort=1;		//P numerator
pShort=&CO2_pdnum;
*pShort=1;		//P denumerator
pShort=&CO2_inum;
*pShort=1;		//i numerator
pShort=&CO2_idnum;
*pShort=360;		//i denumerator

pShort=&O2sp;
*pShort=500;
pShort=&O2_ha;
*pShort=600;
pShort=&O2_la;
*pShort=400;
pShort=&O2_pnum;
*pShort=1;
pShort=&O2_pdnum;
*pShort=1;
pShort=&O2_inum;
*pShort=1;
pShort=&O2_idnum;
*pShort=360;

pShort=&RHsp;
*pShort=8500;	  	//Temperature set point
pShort=&RH_ha;
*pShort=9500;		//Temperature set point high alarm
pShort=&RH_la;
*pShort=6500;		//Temperature set point low alarm
pShort=&RH_pnum;
*pShort=1;		//Temperature P numerator
pShort=&RH_pdnum;
*pShort=1;		//Temperature P denumerator
pShort=&RH_inum;
*pShort=1;		//Temperature i numerator
pShort=&RH_idnum;
*pShort=360;		//Temperature i denumerator
pShort=&NTCsp;
*pShort=NTC_SP_FOR_RH;

 for (c=0;c<MAX_NUMBER_OF_CLSREGISTER;c++)
 {
	
 	if(CLSRegister[c].RegType==WORD_EEPROM)
 	{
	  EEPROM_Read(CLSRegister[c].EEPROM_Address, &tempValue.bytes[0], 2);
	  Delay_uS(5000);
	  if(tempValue.word !=0xffff)	
 	   		*(CLSRegister[c].RegData)=tempValue.word;
 	  else  //write with default value
 	  {
 	  	tempValue.word=*(CLSRegister[c].RegData);
 	  	EEPROM_MultiWrite (CLSRegister[c].EEPROM_Address, &tempValue.bytes[0], 2);
 	  	Delay_uS(5000);
 	  }
 	}
 }
prevTsp=Tsp;
prevRHsp=RHsp;
prevO2sp=O2sp;
prevCO2sp=CO2sp;
}
void Flush_I2C1FrameBuff(void)
{
	I2C1_DataFrame.Command=0;
	I2C1_DataFrame.Crc[0]=0;
	I2C1_DataFrame.Crc[1]=0;
	I2C1_DataFrame.Data[0]=0;
	I2C1_DataFrame.Data[1]=0;
	I2C1_DataFrame.Data[2]=0;
	I2C1_DataFrame.Data[3]=0;
	I2C1_DataFrame.dataLength=0;
	I2C1_DataFrame.RegAddress=0;

}
//SHORT delta;
void Event_Int_I2C_Write_Reg(void)
{
	
	WORDTOBYTE tempWord;
        WORD *pWord;

	tempWord.word=Reg_Write_Val;
	
	if( CLSRegister[RegAddres_Write].RegType==WORD_EEPROM)
	{
	  EEPROM_MultiWrite (CLSRegister[RegAddres_Write].EEPROM_Address, &tempWord.bytes[0],2);
	  Delay_uS(100);
	}
        //delta=0;
	switch(RegAddres_Write)
		{
                                case IRCO2_OFFSET:
                                    if(Reg_Write_Val)SetOutPut(J19_DOOR_LOCK,ON);
                                    else SetOutPut(J19_DOOR_LOCK,OFF);
                                    break;
                                case TSP:

                                   if(prevTsp!=Tsp)
                                       {
					pWord=&Tsp_ha;
                                        *pWord+=Tsp-prevTsp;
					tempWord.word=*pWord;
					EEPROM_MultiWrite (CLSRegister[TSP_HA].EEPROM_Address, &tempWord.bytes[0],2);
					Delay_uS(5000);
                                        pWord=&Tsp_la;
                                        *pWord+=Tsp-prevTsp;
					tempWord.word=*pWord;
					EEPROM_MultiWrite (CLSRegister[TSP_LA].EEPROM_Address, &tempWord.bytes[0],2);
					Delay_uS(5000);
                                        prevTsp=Tsp;
                                        T_Itemp=0;
                                        }
                                        break;
                                case CO2SP:

                                   if(prevCO2sp!=CO2sp)
                                       {
					pWord=&CO2_ha;
                                        *pWord+=CO2sp-prevCO2sp;
					tempWord.word=*pWord;
					EEPROM_MultiWrite (CLSRegister[CO2_HA].EEPROM_Address, &tempWord.bytes[0],2);
					Delay_uS(5000);
                                        pWord=&CO2_la;
                                        *pWord+=CO2sp-prevCO2sp;
					tempWord.word=*pWord;
					EEPROM_MultiWrite (CLSRegister[CO2_LA].EEPROM_Address, &tempWord.bytes[0],2);
					Delay_uS(5000);
                                        prevCO2sp=CO2sp;
                                        CO2_Itemp=0;
                                        }
                                        break;
                                case O2SP:

                                   if(prevO2sp!=O2sp)
                                       {
					pWord=&O2_ha;
                                        *pWord+=O2sp-prevO2sp;
					tempWord.word=*pWord;
					EEPROM_MultiWrite (CLSRegister[O2_HA].EEPROM_Address, &tempWord.bytes[0],2);
					Delay_uS(5000);
                                        pWord=&O2_la;
                                        *pWord+=O2sp-prevO2sp;
					tempWord.word=*pWord;
					EEPROM_MultiWrite (CLSRegister[O2_LA].EEPROM_Address, &tempWord.bytes[0],2);
					Delay_uS(5000);
                                        prevO2sp=O2sp;
                                        O2_Itemp=0;
                                        }
                                        break;
                                case RHSP:

                                   if(prevRHsp!=RHsp)
                                       {
					pWord=&RH_ha;
                                        *pWord+=RHsp-prevRHsp;
					tempWord.word=*pWord;
					EEPROM_MultiWrite (CLSRegister[RH_HA].EEPROM_Address, &tempWord.bytes[0],2);
					Delay_uS(5000);
                                        pWord=&RH_la;
                                        *pWord+=RHsp-prevRHsp;
					tempWord.word=*pWord;
					EEPROM_MultiWrite (CLSRegister[RH_LA].EEPROM_Address, &tempWord.bytes[0],2);
					Delay_uS(5000);
                                        prevRHsp=RHsp;
                                        RH_Itemp=0;
                                        }
                                        break;

				case O2_OFFSET:
					Calibrate_O2RS485(O2_Offset);//Calibrate O2
					break;
				case OMB_MODE:
					UpdateSystemMode(); //SYSTEM MODE flage
					break;
				case OMB_OUTPUTS:
					UpdateOutput();//Output Flag
					break;
				default:
					break;
	
		}
	SetIntDrivenEventFlag(CLEAR,INT_UTI_WRITE);
}

//void Process_I2C1_FrameData(void)
//{
////--testing purpose--
//char Echo0[8]={0x90,'E','C','H','O','-','0','0'};
//char Echo1[8]={0x90,'E','C','H','O','-','0','1'};
//char Echo2[8]={0x90,'E','C','H','O','-','0','2'};
//char Echo3[8]={0x90,'E','C','H','O','-','0','3'};
//
//BYTE *pI2C1TxDataBuff;
//BYTE *pI2C1RxDataFrame;
//BYTE c;
//
//pI2C1TxDataBuff=ReturnI2C1_TxBuffer();
//pI2C1RxDataFrame=ReturnI2C1_RxDataBuffer();
//
//if(*(pI2C1RxDataFrame+7)=='0')
//{
//  for(c=0;c<8;c++)
//  	*(pI2C1TxDataBuff+c)=Echo1[c];
//}
//else if (*(pI2C1RxDataFrame+7)=='1')
//{
//  for(c=0;c<8;c++)
//  	*(pI2C1TxDataBuff+c)=Echo2[c];
//}
//else if (*(pI2C1RxDataFrame+7)=='2')
//{
//  for(c=0;c<8;c++)
//  	*(pI2C1TxDataBuff+c)=Echo3[c];
//}
//else if (*(pI2C1RxDataFrame+7)=='3')
//{
//  for(c=0;c<8;c++)
//  	*(pI2C1TxDataBuff+c)=Echo0[c];
//}
//	
//	
//	BYTE Func =*I2C1_DataFrame.pData;
//	switch(I2C1_DataFrame.Func)
//	{
//		case READ_FUNC:
//			 Process_I2C1_ReadFunction();
//			 break;		
//		case WRITE_FUNC:
//			Process_I2C1_WriteFunction();
//			break;
//	}
//	
//}
