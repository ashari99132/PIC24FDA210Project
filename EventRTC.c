/**
EventRTC.c
**/
#include "ApplicationDrivers.h"
#include "EventRTC.h"

EVENT RTC_Event[TOTAL_EVENT_RTC]=
		{
		//	{IDLE_COMPRESSOR_RTC_ID,EVENT_DIS,ONCE,2*MINUTE,INIT_RUNTIME, EventCompressorIdle},
			{UV_RUNTIME_RTC_ID,EVENT_DIS,ONCE,1*HOUR,INIT_RUNTIME, EventUVRunTime},
			{NORMAL_MODE_ID,EVENT_EN,ONCE,2*MINUTE,INIT_RUNTIME,Set_NormalMode},
			{CTL_ENABLE_ID,EVENT_DIS,ONCE,2*MINUTE,INIT_RUNTIME,Event_Control_Enabled},
                //        {COLD_CTL_ENABLE_ID,EVENT_DIS,ONCE,1*MINUTE,INIT_RUNTIME,EventColdStartUp},
 
		};	
void EventRTC (void)
{
	BYTE c;
//run the timer for all the event that is enabled and not interrupt driven
	 for(c=0;c<TOTAL_EVENT_RTC;c++)
 		{
	 		if( RTC_Event[c].ENDIS==EVENT_RUN)
 	 	 	   {
 	 	 	    	RTC_Event[c].RunFunction();	
 	 	 	   		 if(RTC_Event[c].Type!=ONCE)RTC_Event[c].RunningTimer=0; // only periodic type is resetted.
 	 	 	   		 else RTC_Event[c].ENDIS=EVENT_RUN_ONCED;
 	 	 	   	}
 	 	 	   		  
 	 	 	   
 	   }
	
}

void EventIntRTC (void)
{
		BYTE c;
	//run the timer for all the event that is enabled and not interrupt driven
		 for(c=0;c<TOTAL_EVENT_RTC;c++)
			{
				if( RTC_Event[c].ENDIS==EVENT_EN  )
				   {
					RTC_Event[c].RunningTimer++;
					if( RTC_Event[c].RunningTimer==RTC_Event[c].Period)RTC_Event[c].ENDIS=EVENT_RUN;
				   }
		   }

}
void StartTimerRTC(BYTE rtc_id, BYTE type, WORD period)
{
 BYTE c;
  for(c=0;c<TOTAL_EVENT_RTC;c++)
  {
   if ( (RTC_Event[c].ID==rtc_id) )
   {
    RTC_Event[c].ENDIS=EVENT_EN;
    RTC_Event[c].Type=type;
    RTC_Event[c].Period=period;
    RTC_Event[c].RunningTimer=0;
   }
  }

}
void StopTimerRTC(BYTE rtc_id)
{
 BYTE c;
  for(c=0;c<TOTAL_EVENT_RTC;c++)
  {
   if ( (RTC_Event[c].ID==rtc_id) )
   {
    RTC_Event[c].ENDIS=EVENT_DIS;
    }
  }
}

BYTE ReturnTimerRTCENDIS(BYTE rtc_id)
{

BYTE c;
  for(c=0;c<TOTAL_EVENT_RTC;c++)
  {
   if ( (RTC_Event[c].ID==rtc_id) )
   {
    return RTC_Event[c].ENDIS;
    }
  }
 return 0;
}
