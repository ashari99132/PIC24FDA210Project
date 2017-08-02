/**
Event_GrowLight.c
**/
#include "ApplicationDrivers.h"
#include "Event_GrowLight.h"
WORD Grow_Light_RunTimer=0x0000;
void EventGrowLightRunTime (void)
{	
 	Grow_Light_RunTimer++;
}

void EventGrowLight (void) 
{
WORD Output=ReturnFlag(OMB_OUTPUTS_FLAG);
WORDTOBYTE tempValue;	
	if((Output&GROW_LAMP_FLAG))
		{
			SetOutPut(J15_GROW_LIGHT,ON);
			StartTimerRTC(GROWLIGHT_RUNTIME_RTC_ID,PERIODIC,10*MINUTE);
		}
	else if (!(Output&GROW_LAMP_FLAG))
		{
			SetOutPut(J15_GROW_LIGHT,OFF);
			StopTimerRTC(GROWLIGHT_RUNTIME_RTC_ID);
			tempValue.word=Grow_Light_RunTimer;
			EEPROM_MultiWrite (GROWLIGHTRUNTIME_EEPROM, &tempValue.bytes[0],2);
			Delay_uS(20);
		}
}
void EventLight (void)
{
WORD Output=ReturnFlag(OMB_OUTPUTS_FLAG);
	
	if(Output&ILLUMINATION_FLAG)SetOutPut(J37_LEDDRIVER,ON);
	else SetOutPut(J37_LEDDRIVER,OFF);
}
