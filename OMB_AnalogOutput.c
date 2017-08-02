/**
OMB_AnalogOutput.c
**/
#include "ApplicationDrivers.h"
#include "OMB_AnalogOutput.h"

FRAMEAD5644R Data_DAC;
float V1_DAC_CH[4]={0.0,0.0,0.0,0.0};
float V2_DAC_CH[4]={0.0,0.0,0.0,0.0};
BYTE Data_DACtoTx[3];

void CalibrateAnalogOut (void)
	{ 
	  char Tolerance_Cnt = 0,Cnt=0;
	  char Exit = 0;
	  float Voltage_DAC_500, Voltage_DAC_10k;
	//	char *Converted_String = NULL;
	  WORD DAC_data = 500;
	  WORD DAC_Calib_Channel_Data=0;
	  unsigned long Previous_Average = 0;
	  unsigned long Current_Average=0;
	  unsigned long Total;
	  char Channel = 0;
	  float Temp_1;
	
      Enable_AnalogMux();		  

	  CompileDAC_Data(DAC_A,WR_INPUT_REGn,DAC_data);
	  TxSPIData_DAC();
	  
	  CompileDAC_Data(DAC_B,WR_INPUT_REGn,DAC_data);
	  TxSPIData_DAC();

	  CompileDAC_Data(DAC_C,WR_INPUT_REGn,DAC_data);
	  TxSPIData_DAC();
	  
	  CompileDAC_Data(DAC_D,WR_INPUT_REGn_UPDATE_ALL,DAC_data);
	  TxSPIData_DAC();
	 
	  while(Channel < 4) {
		Set_Analog_Mux(Channel);
		DAC_data =500;

		CompileDAC_Data(Channel,WR_INPUT_REGn,DAC_data);
		TxSPIData_DAC();
		
		CompileDAC_Data(Channel,UPDATE_DAC_REGn,0);
		TxSPIData_DAC();
	
		DAC_Calib_Channel_Data=Read_SingleEndedLTC2439(CH12);

		
		
		Cnt=0;
		Total=0;
		do{
		  
	
		  DAC_Calib_Channel_Data=Read_SingleEndedLTC2439(CH12);
		  Delay_uS(1000);
		  if(DAC_Calib_Channel_Data>2100 || DAC_Calib_Channel_Data<2900 )return;
	 // 	MainBrd_ComputeMovingAvg(CH7_DATA); 					   //Compute the Moving Average

		  


			if(Cnt>=2)//Moving_Average_Factor_Global)
		  {
			Total-=Previous_Average;
			Cnt=2;//Moving_Average_Factor_Global;
		  }
		  
		  Total+=DAC_Calib_Channel_Data; 
		  Current_Average=Total/2;//Moving_Average_Factor_Global;
		  Cnt++;
	
		  if(Current_Average!=Previous_Average)
			Previous_Average = Current_Average;
		  else{
			Tolerance_Cnt++;
			if(Tolerance_Cnt >= 5){
			  Tolerance_Cnt = 0;
			  Exit	= 1;
			}
		  }
		}while(!Exit);
		
		Temp_1 = (float)Previous_Average;
		
		Voltage_DAC_500 = Temp_1*5.0/65535;//(Temp_1*CalibData_Gain)+CalibData_Offset;
		Total=0;
		Previous_Average = 0;
		Exit = 0;
		DAC_data = 10000;
		
		CompileDAC_Data(Channel,WR_INPUT_REGn,DAC_data);
		TxSPIData_DAC();
		
		CompileDAC_Data(Channel,UPDATE_DAC_REGn,0);
		TxSPIData_DAC();
	
		DAC_Calib_Channel_Data=Read_SingleEndedLTC2439(CH12);
		
		Cnt=0;
		do{
		  DAC_Calib_Channel_Data=Read_SingleEndedLTC2439(CH12);
		  Delay_uS(1000);
		 // MainBrd_ComputeMovingAvg(CH7_DATA); 					   //Compute the Moving Average
		  if(Cnt>=2)//Moving_Average_Factor_Global)
		  {
			Total-=Previous_Average;
			Cnt=2;//Moving_Average_Factor_Global;
		  }
		  
		  Total+=DAC_Calib_Channel_Data; 
		  Current_Average=Total/2;//Moving_Average_Factor_Global;
		  Cnt++;
	
		  if(Current_Average!=Previous_Average)
			Previous_Average = Current_Average;
		  else{
			Tolerance_Cnt++;
			if(Tolerance_Cnt >= 5){
			  Tolerance_Cnt = 0;
			  Exit	= 1;
			}
		  }
		}while(!Exit);
		
		Temp_1 = (float)Previous_Average;	   
		Voltage_DAC_10k = Temp_1*5.0/65535;//(Temp_1*CalibData_Gain)+CalibData_Offset;
		Previous_Average = 0;
		Exit = 0;
		
		switch(Channel)
		{	   
		case 0:
		  //---------------------------Channel 1------------------------------------//	
		  V1_DAC_CH[0]=Voltage_DAC_500;
		  V2_DAC_CH[0]=Voltage_DAC_10k;
		  break;
		  
		case 1:
		  //---------------------------Channel 2------------------------------------//	
		  V1_DAC_CH[1]=Voltage_DAC_500;
		  V2_DAC_CH[1]=Voltage_DAC_10k;
		  break;
		  
		case 2:
		  //---------------------------Channel 3------------------------------------//	
		  V1_DAC_CH[2]=Voltage_DAC_500;
		  V2_DAC_CH[2]=Voltage_DAC_10k;
		  
		  break;
		  
		case 3:
		  //---------------------------Channel 4------------------------------------//	
		  V1_DAC_CH[3]=Voltage_DAC_500;
		  V2_DAC_CH[3]=Voltage_DAC_10k;
		  break;
		}
		Channel++;
	  }

	   Disable_AnalogMux();
	}

void InitializeAnalogOut(void)
{
CompileDAC_Data(0,RST_DAC, 0);
TxSPIData_DAC();

}

void UpdateDAC(BYTE channel, float voltage)
{

 WORD DAC_data=0;
 float m,b,x;
 m=(V2_DAC_CH[channel]-V1_DAC_CH[channel])/9500.0;
 b=V1_DAC_CH[channel]-(m*500.0);
 x=(voltage-b)/m;
 DAC_data= (WORD)x;
 if(DAC_data>16383)DAC_data=16383;
CompileDAC_Data(channel,WR_INPUT_REGn, DAC_data);
TxSPIData_DAC();

CompileDAC_Data(channel,UPDATE_DAC_REGn, 0);
TxSPIData_DAC();
  
}
void CompileDAC_Data(BYTE channel, BYTE cmmd, WORD Data)
{
   WORDTOBYTE Temp;
    
	Data_DAC.DAC_ADDRES=channel;
	Data_DAC.CMD=cmmd;
	Data_DAC.Data=Data;
  
   	switch(Data_DAC.CMD)
			{
			case WR_INPUT_REGn:
			case WR_INPUT_REGn_UPDATE_ALL:				
				Data_DAC.DB_01=0;
				break;
			case UPDATE_DAC_REGn:
				Data_DAC.Data=0;
				Data_DAC.DB_01=0;
				break;					
			
			case RST_DAC:
				Data_DAC.Data=0;
				if(channel==ALL_DAC)Data_DAC.DB_01=1;
				else Data_DAC.DB_01=0;
				break;
			case INTERNAL_SETUP_ON:
				Data_DAC.Data=0;
				Data_DAC.DB_01=1;
				break;
	}

	
Temp.word=(Data_DAC.Data<<2)|Data_DAC.DB_01;

Data_DACtoTx[0]=(Data_DAC.CMD<<3)|Data_DAC.DAC_ADDRES;
Data_DACtoTx[1]=Temp.bytes[1];
Data_DACtoTx[2]=Temp.bytes[0];
}

void TxSPIData_DAC(void)
{

 SetEdgeIdleToActive();
 Delay_uS(10);
 SetOutPut(DAC_CS,0);
 Delay_uS(10);
 SPI1_Tx_Only(&Data_DACtoTx[0],3);
 Delay_uS(50);
 SetOutPut(DAC_CS,1);
 Delay_uS(10);
 SetEdgeActiveToIdle();
}

void Update_RawDAC(BYTE channel, WORD DAC_data)
{
	CompileDAC_Data(channel,WR_INPUT_REGn, DAC_data);
	TxSPIData_DAC();
	
	CompileDAC_Data(channel,UPDATE_DAC_REGn, DAC_data);
	TxSPIData_DAC();


}

	

