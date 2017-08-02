/**
AlarmContactRelay.c
**/
#include "ApplicationDrivers.h"
#include "AlarmContactRelay.h"

void EventUpdateAlarmContactRelay (void)
{
  WORD Alrly_config=ReturnFlag(ALRELAY_FLAG);
  WORD Alrly_Pwr=Alrly_config&ALRELAY_PWR_CYCLE;
  WORD Alrly_T=Alrly_config&ALRELAY_T;
  WORD Alrly_CO2=Alrly_config&ALRELAY_CO2;
  WORD Alrly_O2=Alrly_config&ALRELAY_O2;
  WORD Alrly_RH=Alrly_config&ALRELAY_RH;
	
  WORD AlarmStatus=ReturnFlag(OMB_ALARM_STATUS_FLAG);
  BYTE T_Alarm;
  BYTE CO2_Alarm;
  BYTE O2_Alarm;
  BYTE RH_Alarm;

  if((AlarmStatus&T_HIGH_ALARM) || (AlarmStatus&T_LOW_ALARM))T_Alarm=1;
  else T_Alarm=0;

  if((AlarmStatus&CO2_HIGH_ALARM) || (AlarmStatus&CO2_HIGH_ALARM))CO2_Alarm=1;
   else CO2_Alarm=0;

  if((AlarmStatus&O2_HIGH_ALARM) || (AlarmStatus&O2_LOW_ALARM))O2_Alarm=1;
   else O2_Alarm=0;

  if((AlarmStatus&RH_HIGH_ALARM) || (AlarmStatus&RH_LOW_ALARM))RH_Alarm=1;
   else RH_Alarm=0;
  
  if(Alrly_config&ALRELAY_PWR_CYCLE)SetOutPut(J7_ALARM_RELAY,ON);
  else{

		if((T_Alarm*Alrly_T!=0)|| (CO2_Alarm*Alrly_CO2!=0)||(O2_Alarm*Alrly_O2!=0)||(RH_Alarm*Alrly_RH!=0) )SetOutPut(J7_ALARM_RELAY,ON);
		else SetOutPut(J7_ALARM_RELAY,OFF);
  	  }

  
}

