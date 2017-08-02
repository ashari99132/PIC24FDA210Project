#ifndef __OMB_MODE_H
#define __OMB_MODE_H
void UpdateSystemSensor (void);
void UpdateSystemMode(void);
void Set_FactoryMode(void);
void Set_NormalMode(void);
void Set_DeconMode (void);
void Set_DeconStopMode(	void );
void UpdateOutput(void);
void Output_Manual_Control(void);
void EventEMLock (void);
extern WORD CelSafeOptions;

#endif
