/**
RH_Control.c
**/
#include "ApplicationDrivers.h"
#include "RH_Control.h"

FLOAT RH_Itemp;	//Temperature sum of integral error
const SHORT RHcv_Offset;
const WORD  RHsp;	  	//Temperature set point
const WORD  RH_ha;		//Temperature set point high alarm
const WORD  RH_la;		//Temperature set point low alarm
const WORD  RH_pnum;		//Temperature P numerator
const WORD  RH_pdnum;		//Temperature P denumerator
const WORD  RH_inum;		//Temperature i numerator
const WORD  RH_idnum;		//Temperature i denumerator
WORD  prevRHsp=0;
const WORD  NTCsp;

float RH_PIDOut=0;
void EventUpdateRHPIControl (void)
{
 
  WORD AlarmStatus=ReturnFlag(OMB_ALARM_STATUS_FLAG);
  if(AlarmStatus&TSP_REACH)
	{
  		if(CelSafeOptions&RH_OPT)RH_ControlWithRHSensor();
  		else RH_ControlWithNTC();
	}
 }


BYTE RHAction=0; //--- 1 is boiling, 0 is observing
int PrevRHError=0;
int TargetRHError;
float CObias_RH=0.0;
float Ret_RH_PIDcalculation(void)
{
	int Error;
	float returnDCY;
//	int RH_Ptemp;
	float Kc=(float)RH_pnum/(float)RH_pdnum;  //Temperature P gain constant
	float Ti=(float)RH_inum/(float)RH_idnum; 	//Temperature I gain constant
	//WORD Options=ReturnFlag(OMB_CELSAFE_OPT_FLAG);
	if(CelSafeOptions&RH_OPT)Error = RHsp - (RHcv+RHcv_Offset);
	else Error = NTCsp - (Tamb);

	if(Error<(-500) && (CelSafeOptions&RH_OPT) )
		{
			RH_Itemp+=Error;
			returnDCY=(Kc*Error)+(Kc*RH_Itemp/Ti)+CObias_RH;
		}
	else 
		{
			switch(RHAction)
				{
					case 0:
						if (Error>PrevRHError)
						{
						RHAction=1;
						TargetRHError=0.95*Error;
							if((Kc*Error)>=500)
							{
								RH_Itemp=0;
								returnDCY=100.0;
							}		
							else {
									RH_Itemp+=Error;
									if(Error>0)returnDCY=(Kc*Error)+(Kc*RH_Itemp/Ti)+CObias_RH;
									else returnDCY=0.0;
								 }				
							}
							else returnDCY=0;
							break;
					case 1:
						if(Error>TargetRHError)
							{
							if((Kc*Error)>=500)
								{
									RH_Itemp=0;
									returnDCY=100.0;
								}
								else {
										RH_Itemp+=Error;
										if(Error>0)returnDCY=(Kc*Error)+(Kc*RH_Itemp/Ti)+CObias_RH;
										else returnDCY=0.0;
						  			  }
							}
							else{
									RH_Itemp=0;
									RHAction=0;
									returnDCY=0;
								}
							break;
				}
		
		}

					
			
	if(RH_Itemp>9999)RH_Itemp=9999;
	else if (RH_Itemp<-9999)RH_Itemp=-9999;
	PrevRHError=Error;
	if(returnDCY>100.0)returnDCY=100.0;
	else if (returnDCY<-100.0)returnDCY=-100.0;
	return returnDCY;
}

void RHAlarm_Update (void)
{
	WORD Status=ReturnFlag(OMB_ALARM_STATUS_FLAG);
	Status&=~(RH_HIGH_ALARM|RH_LOW_ALARM);
	//RH set point reach
	if((RHcv+RHcv_Offset)>=RHsp)
		Status|=RHSP_REACH;
	//temperature high alarm 
	if((RHcv+RHcv_Offset)>=RH_ha )
		Status|=RH_HIGH_ALARM;
	
	//temperature low alarm 
	if((RHcv+RHcv_Offset)<=RH_la )
		Status|=RH_LOW_ALARM;
	
	SetFlag(OMB_ALARM_STATUS_FLAG,Status);

}

void ClearRHALarm(void)
{
 WORD Status=ReturnFlag(OMB_ALARM_STATUS_FLAG);
 Status&=~(RH_HIGH_ALARM|RH_LOW_ALARM);
 SetFlag(OMB_ALARM_STATUS_FLAG,Status);
}



void Event_RH_Control(void)
{
	WORD OutputsFlag=ReturnFlag(OMB_OUTPUTS_FLAG);
	OutputsFlag&=~(WATER_HEATER_FLAG);
    
	if(RH_PIDOut>=0){
		OutputsFlag|=(WATER_HEATER_FLAG);
		Update_OC2_PWM(RH_PIDOut*0.5);   //limit the pan heater power to 0.5
		}
	else EventSolenoidRHControlOn(RH_PIDOut*(-1.0));
	SetFlag(OMB_OUTPUTS_FLAG,OutputsFlag);
}

void Event_RH_Control_Off(void)
{
	WORD OutputsFlag=ReturnFlag(OMB_OUTPUTS_FLAG);
	OutputsFlag&=~(WATER_HEATER_FLAG);
	SetFlag(OMB_OUTPUTS_FLAG,OutputsFlag);
	Update_OC2_PWM(0.0);
}


void Event_RH_Control_Enabled(void)
{
	  SetMainEventENDIS(RH_PI_ID,EVENT_EN);
	  SetOutPut(J57_WATER_VALVE,OFF);
}

void Event_RH_Control_Disabled(void)	
{
	Event_RH_Control_Off();
	SetMainEventENDIS(RH_PI_ID,EVENT_DIS);
	SetOutPut(J57_WATER_VALVE,ON);
}

void RH_ControlWithNTC (void)
{
	 WORD NTCSensorError=ReturnFlag(OMB_SENSOR_STATUS_FLAG)&FLAG_NTC_ERROR;

  if(!NTCSensorError)
  	{
  	RH_PIDOut=Ret_RH_PIDcalculation();
  	Event_RH_Control();	 	
  	}

}

void RH_ControlWithRHSensor(void)
{
 
  WORD DoorClose=ReturnFlag(OMB_SWITCHES_STATUS_FLAG)&DOOR_SW_CLOSE;
  WORD RHSensorError=ReturnFlag(OMB_SENSOR_STATUS_FLAG)&FLAG_OPT2_CHANNEL_ERROR;
 /* WORD AlarmStatus=ReturnFlag(OMB_ALARM_STATUS_FLAG);
 
  WORDTOBYTE tempWord;
  WORD *pWord;
  SHORT Delta=0;
  //reset set point reach
  if(prevRHsp!=RHsp)
  	{
                                        Delta=RHsp-prevRHsp;
                                        pWord=&RH_ha;
					*pWord+=Delta;
					tempWord.word=*pWord;
					EEPROM_MultiWrite (CLSRegister[RH_HA].EEPROM_Address, &tempWord.bytes[0],2);
					Delay_uS(5000);

                                        pWord=&RH_la;
                                        *pWord+=Delta;
					tempWord.word=*pWord;
					EEPROM_MultiWrite (CLSRegister[RH_LA].EEPROM_Address, &tempWord.bytes[0],2);
					Delay_uS(5000);
 	 prevRHsp=RHsp;
	 AlarmStatus&=~RHSP_REACH;
	 SetFlag(OMB_ALARM_STATUS_FLAG,AlarmStatus);
  }
    */
  //monitor alarm for RH control

  if(DoorClose && !RHSensorError)
  	{
  	RHAlarm_Update();
  	RH_PIDOut=Ret_RH_PIDcalculation();
  	Event_RH_Control();
	StartONCEMainEvent(1000,PAN_HEATER_OFF_ID);
  	}
  else {
  	ClearRHALarm();
  	Event_RH_Control_Off();	
  	}
}

void EventSolenoidRHControlOff(void)
{
 SetOutPut(J23_SOL_RH_CNTRL,OFF);
}

void EventSolenoidRHControlOn(float PWM)
{
	WORD NewPeriod=PWM*MAX_RH_SOL_PERIOD*0.01;	
	SetOutPut(J23_SOL_RH_CNTRL,ON);
	StartONCEMainEvent(NewPeriod, SOL_RH_CONTROL_OFF_ID);

}


