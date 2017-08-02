#ifndef __CO2_CONTROL_H
#define __CO2_CONTROL_H

#define CO2_PWM_PERIOD		5000 //
#define MAIN_SOL					1
#define BACKUP_SOL				2




extern const SHORT CO2cv_Offset;
extern const WORD  CO2sp;	  	//Temperature set point
extern const WORD  CO2_ha;		//Temperature set point high alarm
extern const WORD  CO2_la;		//Temperature set point low alarm
extern const WORD  CO2_pnum;		//Temperature P numerator
extern const WORD  CO2_pdnum;		//Temperature P denumerator
extern const WORD  CO2_inum;		//Temperature i numerator
extern const WORD  CO2_idnum;		//Temperature i denumerator
extern WORD  prevCO2sp;
extern DWORD CO2_Itemp;	//sum of integral error
void EventUpdateCO2PIControl (void);
void Run_PID_CO2Injection(void);
void Stop_PID_CO2Injection(void);
int Ret_CO2_PIDcalculation(void);
void CO2Alarm_Update (void);
void ClearCO2ALarm(void);
void Update_CO2Injection_PWM (int DCY);
BYTE CO2_SolenoidSystem(void);
void Event_CO2_MainSol_On(void);
void Event_CO2_MainSol_Off(void);
void Event_CO2_BackSol_On(void);
void Event_CO2_BackSol_Off(void);



#endif
