#ifndef __RH_CONTROL_H
#define __RH_CONTROL_H


#define NTC_SP_FOR_RH 		40000  //--40 C temp set point
#define MAX_RH_SOL_PERIOD	5000

extern const SHORT RHcv_Offset;
extern const WORD  RHsp;	  	//Temperature set point
extern const WORD  RH_ha;		//Temperature set point high alarm
extern const WORD  RH_la;		//Temperature set point low alarm
extern const WORD  RH_pnum;		//Temperature P numerator
extern const WORD  RH_pdnum;		//Temperature P denumerator
extern const WORD  RH_inum;		//Temperature i numerator
extern const WORD  RH_idnum;		//Temperature i denumerator
extern const WORD  NTCsp;
extern WORD  prevRHsp;
extern FLOAT RH_Itemp;	//Temperature sum of integral error



void EventUpdateRHPIControl (void);
float Ret_RH_PIDcalculation(void);
void RHAlarm_Update (void);
void ClearRHALarm(void);
void Event_RH_Control(void);
void Event_RH_Control_Off(void);
void Event_RH_Control_Enabled(void);
void Event_RH_Control_Disabled(void);	
void RH_ControlWithRHSensor(void);
void RH_ControlWithNTC(void);
float Ret_RH_PIDcalculationWithNTC(void);
void EventSolenoidRHControlOff(void);
void EventSolenoidRHControlOn(float PWM);





#endif
