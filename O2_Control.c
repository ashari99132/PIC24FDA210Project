/**
O2_Control.c
**/
#include "ApplicationDrivers.h"
#include "O2_Control.h"

const WORD O2cv_Offset;
DWORD O2_Itemp;	
const WORD  O2sp;
const WORD  O2_ha;
const WORD  O2_la;
const WORD  O2_pnum;
const WORD  O2_pdnum;
const WORD  O2_inum;
const WORD  O2_idnum;
WORD  prevO2sp=0;


void EventUpdateO2PIControl (void)
{
  WORD DoorClose=ReturnFlag(OMB_SWITCHES_STATUS_FLAG)&DOOR_SW_CLOSE	;	
  WORD O2SensorError=ReturnFlag(OMB_SENSOR_STATUS_FLAG)&(FLAG_O2RS485_PUMP_ERROR|FLAG_O2RS485_HEATER_VOLT_ERROR|FLAG_O2RS485_ASSYMETRY_WARNING|FLAG_O2_BELOW_PT1_WARNING);
  /*WORD AlarmStatus=ReturnFlag(OMB_ALARM_STATUS_FLAG);
  WORDTOBYTE tempWord;
  WORD *pWord;
  //reset set point reach
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
	 AlarmStatus&=~O2SP_REACH;
	 SetFlag(OMB_ALARM_STATUS_FLAG,AlarmStatus);
  }
  */
  //monitor alarm for O2 control
 if(!O2SensorError && O2sp>0 )O2Alarm_Update();
 else ClearO2Alarm();
  //Update Injection
  if(DoorClose && !O2SensorError && O2sp>0 )Run_PID_O2Injection();
  else {
  O2_Itemp=0;
  Stop_PID_O2Injection();

  }
}

void Run_PID_O2Injection(void)
{
 Update_O2Injection_PWM(Ret_O2_PIDcalculation());
	
}
void Stop_PID_O2Injection(void)
{
 Update_O2Injection_PWM(0);
}



int Ret_O2_PIDcalculation(void)
{
	int Error;
	int returnDCY;
	int O2_Ptemp;
	float O2_pgain=(float)(O2_pnum/(float)O2_pdnum);  //Temperature P gain constant
	float O2_igain=(float)(O2_inum/(float)O2_idnum); 	//Temperature I gain constant
	Error = (O2cv+(SHORT)O2cv_Offset)-O2sp;

			if((O2_pgain*Error)>100)	
				{
					O2_Itemp=0;
					returnDCY=105;
				}
				else if((O2_pgain*Error)<=100 && Error>=-5)
					{ 
						O2_Itemp+=Error;
						returnDCY=(O2_pgain*Error)+(O2_igain*O2_Itemp);
					}
				else if(Error <(-5) )
					{
						O2_Itemp+=Error;	
						returnDCY=0;		
					}

	if(O2_Itemp>9999)O2_Itemp=9999;
	else if (O2_Itemp<-9999)O2_Itemp=-9999;
	
	//limit the return from -100 to 100
	if(returnDCY>100)returnDCY=105;
	else if (returnDCY<0)returnDCY=0;
	return returnDCY;
}

void O2Alarm_Update (void)
{
	WORD Status=ReturnFlag(OMB_ALARM_STATUS_FLAG);
	Status&=~(O2_HIGH_ALARM|O2_LOW_ALARM);
	//O2 set point reach
	if((O2cv+(SHORT)O2cv_Offset)<=O2sp)
		Status|=O2SP_REACH;
	//temperature high alarm 
	if((O2cv+(SHORT)O2cv_Offset)>=O2_ha )
		Status|=O2_HIGH_ALARM;
	
	//temperature low alarm 
	if((O2cv+(SHORT)O2cv_Offset)<=O2_la )
		Status|=O2_LOW_ALARM;
	
		
	SetFlag(OMB_ALARM_STATUS_FLAG,Status);
}
void ClearO2Alarm (void)
{
	WORD Status=ReturnFlag(OMB_ALARM_STATUS_FLAG);
	Status&=~(O2_HIGH_ALARM|O2_LOW_ALARM);
	SetFlag(OMB_ALARM_STATUS_FLAG,Status);
}
void  Update_O2Injection_PWM (int DCY)
{
	
	float k;
	//set the respective PWM
	if(DCY<0)DCY=0;
	k=DCY/100.0;
	WORD PWM_Value=k*PWM_PERIOD;
	if(!PWM_Value)
		{
			Event_O2_MainSol_Off();
			Event_O2_BackSol_Off();
		}
		else{
			if(O2_SolenoidSystem()==MAIN_SOL)
				{
				 StartONCEMainEvent(PWM_Value,MAIN_O2SOL_ID);	
				 Event_O2_MainSol_On();	
				}
			else 
				{
				 StartONCEMainEvent(PWM_Value,BACK_O2SOL_ID);	
				 Event_O2_BackSol_On();	
				}
			}
	
	
	
}
BYTE O2_SolenoidSystem(void)
{
// BYTE O2BackupIsInstalled=ReturnFlag(OMB_CELSAFE_OPT_FLAG)&O2_BACKUP_OPT;
 BYTE O2Tank_1_IsLow=ReturnFlag(OMB_SWITCHES_STATUS_FLAG)&O2TANK_1_PSW_CLOSE;
 BYTE O2Tank_2_IsLow=ReturnFlag(OMB_SWITCHES_STATUS_FLAG)&O2TANK_2_PSW_CLOSE;
 BYTE NowUseTank_2_O2=ReturnFlag(OMB_SWITCHES_STATUS_FLAG)&NOW_USE_O2TANK_2;
 BYTE Temp=ReturnFlag(OMB_SWITCHES_STATUS_FLAG);
 BYTE SolenoidNo=0;

 //if(O2BackupIsInstalled)
// {
    if (!O2Tank_2_IsLow && (O2Tank_1_IsLow || (NowUseTank_2_O2 && !O2Tank_1_IsLow)))
    {
	Temp|=NOW_USE_O2TANK_2;   
      Temp&=~NOW_USE_O2TANK_1;
      SetFlag(Temp,OMB_SWITCHES_STATUS_FLAG);
      SolenoidNo=BACKUP_SOL;
    }
    else
    {
	Temp|=NOW_USE_O2TANK_1;   
      Temp&=~NOW_USE_O2TANK_2;   
      SetFlag(Temp,OMB_SWITCHES_STATUS_FLAG);    
      SolenoidNo=MAIN_SOL;
    }


 // }
 // else 
 //   {
 //     Temp|=NOW_USE_O2TANK_1;   
 //     Temp&=~NOW_USE_O2TANK_2;   
 //     SetFlag(Temp,OMB_SWITCHES_STATUS_FLAG);    
 //     SolenoidNo=MAIN_SOL;
 //   }

 return SolenoidNo;
}
void Event_O2_MainSol_On(void)
{
	WORD OutputsFlag=ReturnFlag(OMB_OUTPUTS_FLAG);
	OutputsFlag|=O2_SOL_MAIN_FLAG;
	SetFlag(OMB_OUTPUTS_FLAG,OutputsFlag);
	SetOutPut(J14_MAIN_SOL_O2N2,ON);
}


void Event_O2_MainSol_Off(void)
{
	WORD OutputsFlag=ReturnFlag(OMB_OUTPUTS_FLAG);
	OutputsFlag&=~(O2_SOL_MAIN_FLAG);
	SetFlag(OMB_OUTPUTS_FLAG,OutputsFlag);
	SetOutPut(J14_MAIN_SOL_O2N2,OFF);
}

void Event_O2_BackSol_On(void)
{
	WORD OutputsFlag=ReturnFlag(OMB_OUTPUTS_FLAG);
	OutputsFlag|=O2_SOL_BACK_FLAG;
	SetFlag(OMB_OUTPUTS_FLAG,OutputsFlag);
	SetOutPut(J56_BACK_SOL_O2,ON);
}


void Event_O2_BackSol_Off(void)
{
	WORD OutputsFlag=ReturnFlag(OMB_OUTPUTS_FLAG);
	OutputsFlag&=~(O2_SOL_BACK_FLAG);
	SetFlag(OMB_OUTPUTS_FLAG,OutputsFlag);
	SetOutPut(J56_BACK_SOL_O2,OFF);
}

