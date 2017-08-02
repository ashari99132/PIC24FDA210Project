/**
TempControl.c
**/

#include "ApplicationDrivers.h"
#include "TempControl.h"


float T_Itemp=0.0;	//Temperature sum of integral error
WORD  Tr=TR_DEFAULT; 	//2.75 deg C
const SHORT Tcv_Offset;
const WORD  Tsp;	  	//Temperature set point
      WORD  Tsp_old=3700;  //Temperature set point old
const WORD  Tsp_ha;		//Temperature set point high alarm
const WORD  Tsp_la;		//Temperature set point low alarm
const WORD  Tsp_da; 		//Temperature set point deviation alarm
const WORD  T_pnum;		//Temperature P numerator
const WORD  T_pdnum;		//Temperature P denumerator
const WORD  T_inum;		//Temperature i numerator
const WORD  T_idnum;		//Temperature i denumerator
WORD  Ktn=K_DEFAULT;		//Temperature normalizing constant
const WORD  Pan_Heater_Ratio;
WORD  PWM_MainHeater=0;
WORD  prevTsp;
const WORD  Base_Htr_PR;
const WORD  Door_Htr_PR;
const WORD  Decon_Htr_PR;
float CObias=0.0;
float SigmaT_SP=0.0;
float SigmaT=0.0;
float Delta_Sigma=0.0;  




void EventUpdateTempPIControl (void)
{
 WORD DoorClose=ReturnFlag(OMB_SWITCHES_STATUS_FLAG)&DOOR_SW_CLOSE;
 WORD PT100_error=ReturnFlag(OMB_SENSOR_STATUS_FLAG)&FLAG_PT100_ERROR;
 WORD ThermostatClose=ReturnFlag(OMB_SWITCHES_STATUS_FLAG)&THERSMOSTAT_SW_CLOSE;
 /*WORD AlarmStatus=ReturnFlag(OMB_ALARM_STATUS_FLAG);
 
 WORDTOBYTE tempWord;
 WORD *pWord;
 //reset the intergral error if new set point coming in 

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

   AlarmStatus&=~TSP_REACH;
   SetFlag(OMB_ALARM_STATUS_FLAG,AlarmStatus);
   prevTsp=Tsp;
   T_Itemp=0;
 }
*/
 
   
 //monitor alarm for temp control
   if(!PT100_error && ThermostatClose )TempAlarm_Update();
   else ClearTempALarm();

//calculate the PID and initiate the heater
	if(DoorClose && ThermostatClose && !PT100_error)Run_PID_Heater();	
	else Stop_PID_Heater();
}

float DutyCycle=0.0;
void Run_PID_Heater(void)
{
 WORD OutputsFlag=ReturnFlag(OMB_OUTPUTS_FLAG);
 WORD Mode=ReturnFlag(SYSTEM_MODE_FLAG);
 OutputsFlag&=~(MAIN_HEATER_FLAG|BASE_HEATER_FLAG|DOOR_HEATER_FLAG|DECON_HEATER_FLAG);
 float Pwr_Ratio;
 if(Ret_T_PIDcalculation())
 	{

 		Update_Zone1_OC3_PWM(DutyCycle);
 		if(DutyCycle>0.0)OutputsFlag|=MAIN_HEATER_FLAG;
		if (Mode==DECON_MODE)
 		{
 			Update_Zone2_OC4_PWM(0.75*DutyCycle);
			Update_Zone4_OC6_PWM(100.0);
                        //for door heater only
                        //Update_Zone3_OC5_PWM(DutyCycle);
                        if((0.75*DutyCycle)>0.0)OutputsFlag|=BASE_HEATER_FLAG;
		}
		else 
 		{
  			//Pwr_Ratio=Base_Htr_PR/100.0;
		 	//Update_Zone2_OC4_PWM  ( DutyCycle*Pwr_Ratio);
			Pwr_Ratio=Decon_Htr_PR/100.0;
			Update_Zone4_OC6_PWM(DutyCycle*Pwr_Ratio);
                        //for door heater only
                	//Pwr_Ratio=Door_Htr_PR/100.0;
                        //Update_Zone3_OC5_PWM(DutyCycle*Pwr_Ratio);
                        //if((DutyCycle*Pwr_Ratio)>0.0)OutputsFlag|=BASE_HEATER_FLAG;

 		}
 	}

  //for door  and  base heater heater only
 if (Mode==DECON_MODE) Update_Zone3_OC5_PWM(DutyCycle);

 else
 	{
	 Pwr_Ratio=Door_Htr_PR/100.0;
	 
  	 if(ReturnFlag(OMB_CELSAFE_OPT_FLAG)&O2_OPT)Update_Zone3_OC5_PWM(DutyCycle*Pwr_Ratio+80);
         else Update_Zone3_OC5_PWM(DutyCycle*Pwr_Ratio);
         
         Pwr_Ratio=Base_Htr_PR/100.0;
	 Update_Zone2_OC4_PWM  ( DutyCycle*Pwr_Ratio);
    }

 SetFlag(OMB_OUTPUTS_FLAG,OutputsFlag); 
}

void Stop_PID_Heater(void)
{
 WORD OutputsFlag=ReturnFlag(OMB_OUTPUTS_FLAG);
 OutputsFlag&=~(MAIN_HEATER_FLAG|BASE_HEATER_FLAG|DECON_HEATER_FLAG);//|DOOR_HEATER_FLAG);

 Update_Zone1_OC3_PWM  (0);
 Update_Zone2_OC4_PWM  (0);
 Update_Zone4_OC6_PWM  (0);
 //Update_Zone3_OC5_PWM  (0);
 //Update_Zone5_OC7_PWM(0);
 SetFlag(OMB_OUTPUTS_FLAG,OutputsFlag); 
}
void Stop_Door_Heater(void)
{
 WORD OutputsFlag=ReturnFlag(OMB_OUTPUTS_FLAG);
 OutputsFlag&=~(DOOR_HEATER_FLAG);
 Update_Zone3_OC5_PWM  (0);
 //Update_Zone5_OC7_PWM(0);
 SetFlag(OMB_OUTPUTS_FLAG,OutputsFlag); 
}

void SetCOBias(float value)
{
  CObias=value;
}

BYTE HeatAction=0; //---1 is heating, 0 is observing
float PrevError=0.0;
float TargetError;
BYTE Ret_T_PIDcalculation(void)
	{

		float Error;
		float returnDCY;
		float Kc= T_pnum/((float)T_pdnum);//1.3274;//0.9190; //0.0582  //0.0294
		float Ti= (float)T_inum/(float)T_idnum;//60.0;//2400.0; // in secs //40.0; in  minutes
		WORD Mode=ReturnFlag(SYSTEM_MODE_FLAG);
		BYTE UpdateDCY=0;


                Error=(Tsp/100.0)-(ActualTcv+(Tcv_Offset/100.0));
    
//		if(Mode==DECON_MODE)
//                {
//
//
//                    if(Tsp<=3800)
//                    {
//                        DutyCycle=0.0;
//                        return 1;
//                    }
//                }


		if(Tsp>6000)CObias=95;
		else if(Tsp<=6000 && Tsp>=5500)
			{
				Kc*=2.0;
				StartONCEMainEvent(1000,HEATERS_OFF_ID);
			}
		else {
			CObias=0;
			StartONCEMainEvent(1000,HEATERS_OFF_ID);
			//StartONCEMainEvent(4000,DOOR_HEATER_OFF_ID);
			}
		
		if(PrevError<=Error && Error>0.0)T_Itemp+=Error;
		else T_Itemp=0;
		
		if (Error>0.0)DutyCycle=(100.0*((Kc*Error)+(Kc*T_Itemp/Ti)))+CObias;
		else DutyCycle=0.0;


		if( Error > PrevError && Error>0)
 		 {
   			SigmaT_SP=Error;
  			SigmaT=0.0;
                        UpdateDCY=1;
                 }
                else if(Error<=PrevError && Error>0)
   		{
     		Delta_Sigma=0.0;
     		if(DutyCycle>100.0)SigmaT+=DT_PER_DCY_100;
     		else SigmaT+=DT_PER_DCY*DutyCycle*100;
    		Delta_Sigma=SigmaT-SigmaT_SP;
     		if(Delta_Sigma>0.0 && Mode!=DECON_MODE)UpdateDCY=0; 
     		else UpdateDCY=1; 
     		if(Delta_Sigma>=SigmaT_SP)
     		{
       			SigmaT_SP=Error;
       			SigmaT=0.0;
                }
     
   		}
  		else UpdateDCY=0;

		
 

//			switch(HeatAction)
//			{
//				case 0:
//				if(Error>PrevError)
//				{
//
//					TargetError=Error*0.8;
//					HeatAction=1;
//					if((Kc*Error)>1.0)
//						{
//						 T_Itemp=0.0;
//						 returnDCY=100.0;						 
//						}
//					else 
//						{
//							T_Itemp+=Error;
//							if (Error>0.0)returnDCY=(100.0*((Kc*Error)+(Kc*T_Itemp/Ti)))+CObias;
//							else returnDCY=0.0;
//			
//						}
//					 
//				}
//				else returnDCY=0.0;
//				break;
//				case 1:
//				if(Error>TargetError)
//					{
//						if((Kc*Error)>1.0)
//						{
//						 T_Itemp=0.0;
//						 returnDCY=100.0;						 
//						}
//						else 
//						{
//							T_Itemp+=Error;
//							if (Error>0.0)returnDCY=(100.0*((Kc*Error)+(Kc*T_Itemp/Ti)))+CObias;
//							else returnDCY=0.0;			
//						}
//						
//					}	
//				else {
//					HeatAction=0;
//					returnDCY=0.0;
//				}
//				break;
//
//
//			}
		if(T_Itemp>99.99)T_Itemp=99.99;
		else if(T_Itemp<-99.99)T_Itemp=-99.99;
		
		PrevError=Error;
		//limit the return from -100 to 100
		if(DutyCycle>100.0)DutyCycle=100.0;
		else if (DutyCycle<=0.0)DutyCycle=0.0;
		return UpdateDCY;
	}

void TempAlarm_Update (void)
{
	WORD Status=ReturnFlag(OMB_ALARM_STATUS_FLAG);
        WORD Mode=ReturnFlag(SYSTEM_MODE_FLAG);
	Status&=~(T_HIGH_ALARM|T_LOW_ALARM);

	//failsafe
        if((Tcv+Tcv_Offset)>=Tsp+500 /*&& !(Status&T_DEV_ALARM) */ && Mode==NORMAL_MODE)
        {
            FailSafe_Relay_Off();
            Status|=T_DEV_ALARM;
        }
        else if ((Tcv+Tcv_Offset)<=Tsp /*&& (Status&T_DEV_ALARM)*/&& Mode==NORMAL_MODE)
        {
            FailSafe_Relay_On();
            Status&=~T_DEV_ALARM;
        }

	//set point reach
	if((Tcv+Tcv_Offset)>=Tsp)
		Status|=TSP_REACH;
	//temperature high alarm 
	if((Tcv+Tcv_Offset)>=Tsp_ha)
		Status|=T_HIGH_ALARM;
	
	//temperature low alarm 
	else if((Tcv+Tcv_Offset)<=Tsp_la)
		Status|=T_LOW_ALARM;
	
	//temperature deviation alarm
	//if((Tcv+Tcv_Offset)<=(Tsp-Tsp_da)&& (Tcv+Tcv_Offset)>=(Tsp+Tsp_da) && (Status&TSP_REACH) )
	  // Status|=T_DEV_ALARM;


	SetFlag(OMB_ALARM_STATUS_FLAG,Status);

}
void ClearTempALarm(void)
{
	WORD Status=ReturnFlag(OMB_ALARM_STATUS_FLAG);
    Status&=~(T_HIGH_ALARM|T_LOW_ALARM|T_DEV_ALARM);
	SetFlag(OMB_ALARM_STATUS_FLAG,Status);
}

void EventFanDeconOn(void)
{
 WORD OutputsFlag=ReturnFlag(OMB_OUTPUTS_FLAG);
 BYTE c;
 SetOutPut(J53_DECON_FAN,ON);
 for(c=0;c<100;c++)Delay_uS(50000);
 OutputsFlag|=DECON_FAN_FLAG;
 SetFlag(OMB_OUTPUTS_FLAG,OutputsFlag);
}	
void EventFanDeconOff(void)
{
 WORD OutputsFlag=ReturnFlag(OMB_OUTPUTS_FLAG);
 BYTE c;
 SetOutPut(J53_DECON_FAN,OFF);
 for(c=0;c<100;c++)Delay_uS(50000);
 OutputsFlag&=~DECON_FAN_FLAG;
 SetFlag(OMB_OUTPUTS_FLAG,OutputsFlag);
}
void EventPumpChamberOn(void)
{
 WORD OutputsFlag=ReturnFlag(OMB_OUTPUTS_FLAG);
 BYTE c;
 SetOutPut(J13_ZONE6_HTR,ON);
 for(c=0;c<100;c++)Delay_uS(50000);
 OutputsFlag|=PUMP_FLAG;
 SetFlag(OMB_OUTPUTS_FLAG,OutputsFlag);
}
void EventPumpChamberOff(void)
{
 WORD OutputsFlag=ReturnFlag(OMB_OUTPUTS_FLAG);
 BYTE c;
 SetOutPut(J13_ZONE6_HTR,OFF);
 for(c=0;c<100;c++)Delay_uS(50000);
 OutputsFlag&=~PUMP_FLAG;
 SetFlag(OMB_OUTPUTS_FLAG,OutputsFlag);
}

void Send_DataToPC (void)
{
	UART1_TxString(FloatToString_4Pt2Dec((ActualTcv+(Tcv_Offset/100.0))));
	UART1_TxString(", ");
	UART1_TxString(FloatToString_4Pt2Dec(DutyCycle));
	UART1_TxString(" \r");
}

void Event_Control_Enabled(void)
{
	  SetMainEventENDIS(TEMP_PI_ID,EVENT_EN);
	  //SetMainEventENDIS(CO2_PI_ID,EVENT_EN);
	  SetMainEventENDIS(RH_PI_ID,EVENT_EN);
	  if(CelSafeOptions&O2_OPT)SetMainEventENDIS(O2_PI_ID,EVENT_EN);
	  
	  
	  
}

void Event_Control_Disabled(void)	
{
	SetMainEventENDIS(TEMP_PI_ID,EVENT_DIS);
	SetMainEventENDIS(CO2_PI_ID,EVENT_DIS);
	SetMainEventENDIS(O2_PI_ID,EVENT_DIS);
	SetMainEventENDIS(RH_PI_ID,EVENT_DIS);
	Stop_PID_Heater();
	Stop_PID_CO2Injection();
	Stop_PID_O2Injection();	
	Event_RH_Control_Off();
	
	
}



void EventColdStartUp(void)
{
 SetMainEventENDIS(CO2_PI_ID,EVENT_EN);
 if((Tsp/100.0)-(ActualTcv+(Tcv_Offset/100.0))>=7.0)
 {
      Update_Zone1_OC3_PWM  (50);
      Update_Zone2_OC4_PWM  (80);
      Update_Zone4_OC6_PWM  (80);
      Update_Zone3_OC5_PWM  (80);

     StartTimerRTC(CTL_ENABLE_ID,ONCE,5*MINUTE);
 }
 else Event_Control_Enabled();

}