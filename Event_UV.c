/**
Event_UV.c
**/
#include "ApplicationDrivers.h"
#include "Event_UV.h"
WORD UV_RunTimer=0x0000;
void EventUVRunTime (void)
{
	
 	UV_RunTimer++;
 	
}

void EventUVLamp (void)
{
	WORD Output=ReturnFlag(OMB_OUTPUTS_FLAG);
	WORDTOBYTE tempValue;
	
 	
 	
	if((Output&UV_LAMP_FLAG))
		{
			SetOutPut(J33_UVBALLAST,ON);
			StartTimerRTC(UV_RUNTIME_RTC_ID,PERIODIC,10*MINUTE);
		}
	else if (!(Output&UV_LAMP_FLAG))
		{
			SetOutPut(J33_UVBALLAST,OFF);
			StopTimerRTC(UV_RUNTIME_RTC_ID);
			//save to EEPROM the UV_RunTimer 
			tempValue.word=UV_RunTimer;	
 			EEPROM_MultiWrite (UVRUNTIME_EEPROM, &tempValue.bytes[0],2);
 			Delay_uS(20);
		}
}
