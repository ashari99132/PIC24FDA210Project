/**
CO2_Control.c
**/
#include "ApplicationDrivers.h"
#include "CO2_Control.h"

DWORD CO2_Itemp;	//sum of integral error
const SHORT CO2cv_Offset;
const WORD  CO2sp;	  	//set point
const WORD  CO2_ha;		//set point high alarm
const WORD  CO2_la;		//set point low alarm
const WORD  CO2_pnum;		//P numerator
const WORD  CO2_pdnum;		//P denumerator
const WORD  CO2_inum;		//i numerator
const WORD  CO2_idnum;		//i denumerator
WORD  prevCO2sp=0;
BYTE CO2injectAction=0;
float PrevCO2Error=0.0;
WORD TargetCO2Error=0;

void EventUpdateCO2PIControl (void)
{
  WORD DoorClose=ReturnFlag(OMB_SWITCHES_STATUS_FLAG)&DOOR_SW_CLOSE;
  WORD IRCO2SensorError=ReturnFlag(OMB_SENSOR_STATUS_FLAG)&FLAG_IRCO2_ERROR;
  //monitor alarm for CO2 control
  if(!IRCO2SensorError && CO2sp>0 )CO2Alarm_Update();
  else ClearCO2ALarm();
  
  if(DoorClose && !IRCO2SensorError && CO2sp>0 )Run_PID_CO2Injection();
  else {
				CO2_Itemp=0;
				Stop_PID_CO2Injection();
  	   }
  		
}

void Run_PID_CO2Injection(void)
{
 Update_CO2Injection_PWM(Ret_CO2_PIDcalculation());
	
}
void Stop_PID_CO2Injection(void)
{
 Update_CO2Injection_PWM(0);
}



int Ret_CO2_PIDcalculation(void)
{
	float Error;
	float returnDCY;
	float CO2_pgain=(float)(CO2_pnum/(float)CO2_pdnum);  //Temperature P gain constant
	float CO2_igain=(float)(CO2_inum/(float)CO2_idnum); 	//Temperature I gain constant

	Error = (float)CO2sp - ((float)CO2cv+(float)CO2cv_Offset);

	if((Error*CO2_pgain)<100)CO2_Itemp+=Error;
        else CO2_Itemp=0;


		if(Error>6.0 )returnDCY=(CO2_pgain*Error)+(CO2_igain*CO2_Itemp);
                else returnDCY=0;


	if(CO2_Itemp>9999.0)CO2_Itemp=9999.0;
	else if(CO2_Itemp<-9999.0)CO2_Itemp=-9999.0;
			 
	
	

	//limit the return from -100 to 100
	if(returnDCY>100.0)returnDCY=100.0;
	else if (returnDCY<0.0)returnDCY=0.0;



      //  if(PrevCO2Error-Error>1.0)
      //  {
      //      returnDCY=0.0;
      //  }

     //   PrevCO2Error=Error;
        return (int)(returnDCY*1);
}

void CO2Alarm_Update (void)
{
	WORD Status=ReturnFlag(OMB_ALARM_STATUS_FLAG);
	Status&=~(CO2_HIGH_ALARM|CO2_LOW_ALARM);
	//CO2 set point reach
	if(((int)CO2cv+(int)CO2cv_Offset)>=(int)CO2sp)
		Status|=CO2SP_REACH;
	
	//CO2 high alarm 
	if(((int)CO2cv+(int)CO2cv_Offset)>=(int)CO2_ha )
		Status|=CO2_HIGH_ALARM;
	
	//CO2 low alarm 
	else if(((int)CO2cv+(int)CO2cv_Offset)<=(int)CO2_la )
		Status|=CO2_LOW_ALARM;
	
		
	SetFlag(OMB_ALARM_STATUS_FLAG,Status);

}
void ClearCO2ALarm(void)
{
 WORD Status=ReturnFlag(OMB_ALARM_STATUS_FLAG);
 Status&=~(CO2_HIGH_ALARM|CO2_LOW_ALARM);
 SetFlag(OMB_ALARM_STATUS_FLAG,Status);
}
void  Update_CO2Injection_PWM (int DCY)
{
	
	float k;
	//set the respective PWM
	if(DCY<0)DCY=0;
	k=DCY/100.0;
	WORD PWM_Value=k*CO2_PWM_PERIOD;

	if(!PWM_Value){
		Event_CO2_MainSol_Off();
		Event_CO2_BackSol_Off();
		}
		else{
				if(CO2_SolenoidSystem()==MAIN_SOL)
					{
						StartONCEMainEvent(PWM_Value,MAIN_CO2SOL_ID);
						Event_CO2_MainSol_On(); 	
				
					}
				else 
					{
						StartONCEMainEvent(PWM_Value,BACK_CO2SOL_ID);
						Event_CO2_BackSol_On(); 
			
					}
		
		}	
}
BYTE CO2_SolenoidSystem(void)
{
 //BYTE CO2BackupIsInstalled=ReturnFlag(OMB_CELSAFE_OPT_FLAG)&CO2_BACKUP_OPT;
 BYTE CO2Tank_1_IsLow=ReturnFlag(OMB_SWITCHES_STATUS_FLAG)&CO2TANK_1_PSW_CLOSE;
 BYTE CO2Tank_2_IsLow=ReturnFlag(OMB_SWITCHES_STATUS_FLAG)&CO2TANK_2_PSW_CLOSE;
 BYTE NowUseTank_2_CO2=ReturnFlag(OMB_SWITCHES_STATUS_FLAG)&NOW_USE_CO2TANK_2;
 BYTE Temp=ReturnFlag(OMB_SWITCHES_STATUS_FLAG);
 BYTE SolenoidNo=0;

// if(CO2BackupIsInstalled)
// {
    if (!CO2Tank_2_IsLow && (CO2Tank_1_IsLow || (NowUseTank_2_CO2 && !CO2Tank_1_IsLow)))
    {
	Temp|=NOW_USE_CO2TANK_2;   
      Temp&=~NOW_USE_CO2TANK_1;
      SetFlag(Temp,OMB_SWITCHES_STATUS_FLAG);
      SolenoidNo=BACKUP_SOL;
    }
    else
    {
	Temp|=NOW_USE_CO2TANK_1;   
      Temp&=~NOW_USE_CO2TANK_2;   
      SetFlag(Temp,OMB_SWITCHES_STATUS_FLAG);    
      SolenoidNo=MAIN_SOL;
    }



 return SolenoidNo;
}
void Event_CO2_MainSol_On(void)
{
	WORD OutputsFlag=ReturnFlag(OMB_OUTPUTS_FLAG);
	OutputsFlag|=CO2_SOL_MAIN_FLAG;
	SetFlag(OMB_OUTPUTS_FLAG,OutputsFlag);
	SetOutPut(J22_MAIN_SOL_CO2,ON);
}

void Event_CO2_MainSol_Off(void)
{
	WORD OutputsFlag=ReturnFlag(OMB_OUTPUTS_FLAG);
	OutputsFlag&=~(CO2_SOL_MAIN_FLAG);
	SetFlag(OMB_OUTPUTS_FLAG,OutputsFlag);
	SetOutPut(J22_MAIN_SOL_CO2,OFF);
}
void Event_CO2_BackSol_On(void)
{
	WORD OutputsFlag=ReturnFlag(OMB_OUTPUTS_FLAG);
	OutputsFlag|=CO2_SOL_BACK_FLAG;
	SetFlag(OMB_OUTPUTS_FLAG,OutputsFlag);
	SetOutPut(J15_BACK_SOL_CO2,ON);
}

void Event_CO2_BackSol_Off(void)
{
	WORD OutputsFlag=ReturnFlag(OMB_OUTPUTS_FLAG);
	OutputsFlag&=~(CO2_SOL_BACK_FLAG);
	SetFlag(OMB_OUTPUTS_FLAG,OutputsFlag);
	SetOutPut(J15_BACK_SOL_CO2,OFF);
}



