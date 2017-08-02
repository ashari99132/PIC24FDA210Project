/*
EventScheduler.c
*/

//local include

#include "ApplicationDrivers.h"
#include "EventScheduler.h"

WORD OMB_Software_Ver=20;     //OMB Software ver 1.0
EVENT MainEvent[TOTAL_EVENT]=
		{
			{TEMP_PI_ID,EVENT_DIS,PERIODIC,5000,INIT_RUNTIME, EventUpdateTempPIControl},
                        {CO2_PI_ID,EVENT_DIS,PERIODIC,10000,INIT_RUNTIME, EventUpdateCO2PIControl},
                        {RH_PI_ID,EVENT_DIS,PERIODIC,5000,INIT_RUNTIME, EventUpdateRHPIControl},
			{O2_PI_ID,EVENT_DIS,PERIODIC,5000,INIT_RUNTIME, EventUpdateO2PIControl},
			{AIN_ID,EVENT_EN,ONCE,2,INIT_RUNTIME, EventSelfCalibLTC2439AIN},
			{PT100_ID,EVENT_DIS,PERIODIC,300,INIT_RUNTIME, EventUpdate_PT100channel},
			{NTC_ID,EVENT_DIS,PERIODIC,300,INIT_RUNTIME, EventUpdate_NTCchannel},
			{RH_ID,EVENT_DIS,PERIODIC,300,INIT_RUNTIME, EventUpdate_RHchannel},
			{O2_RS485_ID,EVENT_DIS,PERIODIC,500,INIT_RUNTIME, EventUpdateRS485O2Sensor},
			{BUZZER_ID,EVENT_DIS,PERIODIC,500,INIT_RUNTIME,  EventUpdateBuzzer},
			{CO2_RS485_ID,EVENT_DIS,PERIODIC,500,INIT_RUNTIME, EventUpdateRS485CO2Sensor},
			{RH_CTL_ENABLE_ID,EVENT_DIS,ONCE,0,INIT_RUNTIME,Event_RH_Control_Enabled},
			{RH_CTL_DISABLE_ID,EVENT_DIS,ONCE,0,INIT_RUNTIME,Event_RH_Control_Disabled},
			{HEATERS_OFF_ID,EVENT_DIS,ONCE,0,INIT_RUNTIME,Stop_PID_Heater},
			{DOOR_HEATER_OFF_ID,EVENT_DIS,ONCE,0,INIT_RUNTIME,Stop_Door_Heater},
			{PAN_HEATER_OFF_ID,EVENT_DIS,ONCE,0,INIT_RUNTIME,Event_RH_Control_Off},
			{SOL_RH_CONTROL_OFF_ID,EVENT_DIS,ONCE,0,INIT_RUNTIME,EventSolenoidRHControlOff},
			{MAIN_CO2SOL_ID,EVENT_DIS,ONCE,0,INIT_RUNTIME, Event_CO2_MainSol_Off},
                        {BACK_CO2SOL_ID,EVENT_DIS,ONCE,0,INIT_RUNTIME, Event_CO2_BackSol_Off},
			{MAIN_O2SOL_ID,EVENT_DIS,ONCE,0,INIT_RUNTIME, Event_O2_MainSol_Off},
			{BACK_O2SOL_ID,EVENT_DIS,ONCE,0,INIT_RUNTIME, Event_O2_BackSol_Off},
			
			
			
		};
EVENT_INT IntDrivenEvent[MAX_INT_ID]={
			{INT_ALARMCONTACT,EVENT_EN,SET,EventUpdateAlarmContactRelay},
			{INT_UTI,EVENT_EN,SET,EventUpdateUTI_Communication},
			{INT_DIN,EVENT_EN,SET, EventUpdateDigitalSensors},
			{INT_TCPIP,EVENT_EN,SET,EventTCPIP},			
			{INT_DOOR, EVENT_DIS,SET, EventDoor},
			{INT_THERMOSTAT,EVENT_DIS,SET,EventThermostat},
			{INT_WATERLEVEL,EVENT_DIS,SET,EventWaterLevel},
			{INT_RTC,EVENT_EN,SET,EventRTC},
			{INT_CO2RS485,EVENT_DIS,SET,EventRS485CO2Sensor_RxUpdate},
			{INT_O2RS485,EVENT_DIS,SET,EventUpdateRS485O2Sensor_RxUpdate},
			{INT_UTI_WRITE,EVENT_EN,CLEAR,Event_Int_I2C_Write_Reg}
		};
WORD Flag[MAX_FLAG_ID]={
		DFLT_SENSOR_STATUS_FLAG,	
		DFLT_ALARM_STATUS_FLAG,		
		DFLT_COMPRESSOR_CONTROL_FLAG,
		DFLT_SYSTEM_MODE_FLAG,	
		DFLT_MODEL_FLAG,		
		DFLT_OMB_SHAKER_OPT_FLAG,
		DFLT_OMB_OUTPUTS_FLAG,		
		DFLT_OMB_SWITCHES_STATUS_FLAG,
};			
		


void RunForeGroundEvents(void)
{
BYTE c;
	 for(c=0;c<TOTAL_EVENT;c++)
		{
			if(MainEvent[c].ENDIS==EVENT_EN) 
				{
					MainEvent[c].RunningTimer++;
					if(MainEvent[c].RunningTimer==MainEvent[c].Period)
					{
					   MainEvent[c].ENDIS=EVENT_RUN;
					   MainEvent[c].RunningTimer=0;					  	
					}

                        }
					
				
	}
}


void RunBackGroundEvents(void)
{
 BYTE c;
 //BYTE 	d;
 
// WORD funcTime;
// char Msg[20];
 //run background function to check the ID
 	 
	 for(c=0;c<TOTAL_EVENT;c++)
 		{
	 		if(MainEvent[c].ENDIS==EVENT_RUN)
 	 	 	       {
					 MainEvent[c].RunFunction();	
					 MainEvent[c].ENDIS=EVENT_EN; 
					 if(MainEvent[c].Type==ONCE)MainEvent[c].ENDIS=EVENT_RUN_ONCED;  	 	 	   			
					} 	 		 	 	   
 	 	}
  //run all the functions that is interrupt driven
  for(c=0;c<MAX_INT_ID;c++)
  	{
  	 if(IntDrivenEvent[c].Flag==SET && IntDrivenEvent[c].ENDIS==EVENT_EN)
  	 		{
  	 		
			//for(d=0;d<20;d++)Msg[d]=0;
			//funcTime=retCounter1();
  	 	  	 IntDrivenEvent[c].RunFunction();
			 
			 //funcTime=retCounter1()-funcTime;
			 //stringCopy(Msg,WordToString(IntDrivenEvent[c].ID));
			 //stringCat(Msg,":");
			 //stringCat(Msg,WordToString(funcTime)); 				 
			 //stringCat(Msg,"\r\n");
			 //UART1_TxString(Msg);
  	 	  	 }
  	}	
 
}



void SetMainEventPeriod(WORD NewPeriod, BYTE id)
{
	BYTE c;
	for(c=0;c<TOTAL_EVENT;c++)
	 {
		 if(MainEvent[c].ID==id)
		 	{
		 		MainEvent[c].Period=NewPeriod;
		 		break;	
		 	}		 		
	 } 
}

void SetMainEventRunningTimer(WORD NewValue, BYTE id)
{
	BYTE c;
	for(c=0;c<TOTAL_EVENT;c++)
	 {
		 if(MainEvent[c].ID==id)
		 	{
		 		MainEvent[c].RunningTimer=NewValue;
		 		break;	
		 	}		 		
	 } 
}
void SetMainEventENDIS(BYTE id, BYTE NewValue )
{
	BYTE c;
	for(c=0;c<TOTAL_EVENT;c++)
	 {
		 if(MainEvent[c].ID==id)
		 	{
		 		MainEvent[c].ENDIS=NewValue;
		 		break;	
		 	}		 		
	 } 
}

void SetMainEventType(BYTE NewValue, BYTE id)
{
	BYTE c;
	for(c=0;c<TOTAL_EVENT;c++)
	 {
		 if(MainEvent[c].ID==id)
		 	{
		 		MainEvent[c].Type=NewValue;
		 		break;	
		 	}		 		
	 } 
}

BYTE RetMainEventType(BYTE id)
{
 BYTE retVal,c;
	for(c=0;c<TOTAL_EVENT;c++)
	 {
		 if(MainEvent[c].ID==id)
		 	{
		 		retVal=MainEvent[c].Type;
		 		break;	
		 	}		 		
	 } 
  return retVal;
}
BYTE RetMainEventENDIS(BYTE id)
{
 BYTE retVal,c;
	for(c=0;c<TOTAL_EVENT;c++)
	 {
		 if(MainEvent[c].ID==id)
		 	{
		 		retVal=MainEvent[c].ENDIS;
		 		break;
		 	}
	 }
  return retVal;

}
void StartONCEMainEvent(WORD NewPeriod, BYTE id)
{
	BYTE c;
	for(c=0;c<TOTAL_EVENT;c++)
	 {
		 if(MainEvent[c].ID==id)
		 	{
		 		MainEvent[c].Period=NewPeriod;
		 		MainEvent[c].ENDIS=EVENT_EN;
		 		MainEvent[c].RunningTimer=0;
		 		break;	
		 	}		 		
	 } 
}

void SetIntDrivenEventENDIS(BYTE NewValue, BYTE id)
{
	BYTE c;
	for(c=0;c<MAX_INT_ID;c++)
	 {
		 if(IntDrivenEvent[c].ID==id)
		 	{
		 		IntDrivenEvent[c].ENDIS=NewValue;
		 		break;	
		 	}
		 
	 } 
}


void SetIntDrivenEventFlag(BYTE NewValue, BYTE id)
{
  BYTE c;
	for(c=0;c<MAX_INT_ID;c++)
	 {
		 if(IntDrivenEvent[c].ID==id)
		 	{
		 		IntDrivenEvent[c].Flag=NewValue;
		 		break;	
		 	}
		 
	 } 
}


WORD ReturnFlag(WORD FlagID)
{
 
 return  Flag[FlagID];
}

void SetFlag(BYTE FlagID, WORD Value)
{
  Flag[FlagID]=Value;	
}

