#ifndef __O2_CONTROL_H
#define __O2_CONTROL_H

#define O2_HIGH_ALARM	0x0020
#define O2_LOW_ALARM	0x0040

extern const WORD O2cv_Offset;
extern const WORD  O2sp;	  	//Temperature set point
extern const WORD  O2_ha;		//Temperature set point high alarm
extern const WORD  O2_la;		//Temperature set point low alarm
extern const WORD  O2_pnum;		//Temperature P numerator
extern const WORD  O2_pdnum;		//Temperature P denumerator
extern const WORD  O2_inum;		//Temperature i numerator
extern const WORD  O2_idnum;		//Temperature i denumerator
extern WORD  prevO2sp;
extern DWORD O2_Itemp;


void EventUpdateO2PIControl (void);
void Run_PID_O2Injection(void);
void Stop_PID_O2Injection(void);
int Ret_O2_PIDcalculation(void);
void O2Alarm_Update (void);
void ClearO2Alarm (void);
void Update_O2Injection_PWM (int DCY);
BYTE O2_SolenoidSystem(void);
void Event_O2_MainSol_On(void);
void Event_O2_MainSol_Off(void);
void Event_O2_BackSol_On(void);
void Event_O2_BackSol_Off(void);


#endif
