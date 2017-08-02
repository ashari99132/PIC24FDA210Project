#ifndef __Event_GrowLight_H
#define __Event_GrowLight_H

#define GROWLIGHTRUNTIME_EEPROM  0x007A
extern WORD Grow_Light_RunTimer;
void EventGrowLightRunTime (void);
void EventGrowLight (void); 
void EventLight (void);
#endif
