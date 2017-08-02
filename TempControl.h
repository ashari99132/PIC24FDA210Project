#ifndef __TEMP_CONTROL_H
#define __TEMP_CONTROL_H

#define T_CTL_LIMIT 	300 //3oC
#define PWM_PERIOD		5000 //5secs
#define HEATER_PWM_PERIOD 1000 //1SECS
#define PUMP_DCY_PERIOD   60.0 // minutes
#define Kp				150		//0.2oC/%
#define MAX_DATA_SAMPLES 60
//--------default values----------------//
#define K_DEFAULT				100
#define T_PNUM_DEFAULT			1327
#define T_PDNUM_DEFAULT			1000
#define T_INUM_DEFAULT			919
#define T_IDNUM_DEFAULT			1000
#define TR_DEFAULT				275
#define PAN_HEAT_RATIO_DEFAULT	80	
#define POWER_RATIO_DFLT		100

#define DT_PER_DCY                  0.003
#define DT_PER_DCY_100      75.0

//--------compressor control flag----------//
#define FLAG_COMP_OFF			0x0001
#define FLAG_COMP_IDLE_TIMER	0x0002

extern float T_pgain;
extern float T_igain;
extern const  WORD  Tsp;	  	//Temperature set point
extern const  WORD  Tsp_ha;		//Temperature set point high alarm
extern const  WORD  Tsp_la;		//Temperature set point low alarm
extern const  WORD  Tsp_da; 		//Temperature set point deviation alarm
extern WORD  Ktn;		//Temperature normalizing constant
extern const  WORD  T_pnum;		//Temperature P numerator
extern const  WORD  T_pdnum;		//Temperature P denumerator
extern const  WORD  T_inum;		//Temperature i numerator
extern const  WORD  T_idnum;		//Temperature i denumerator
extern const  WORD  Pan_Heater_Ratio;
extern const SHORT  Tcv_Offset;
extern const  WORD  Base_Htr_PR;
extern const  WORD  Door_Htr_PR;
extern const  WORD  Decon_Htr_PR;
extern WORD  prevTsp;
extern float T_Itemp;

void EventUpdateTempPIControl (void);
void Run_PID_Heater(void);
void Stop_PID_Heater(void);
void SetCOBias(float value);
BYTE Ret_T_PIDcalculation(void);
void TempAlarm_Update (void);
void ClearTempALarm(void);
void EventFanDeconOn(void);
void EventFanDeconOff(void);
void EventPumpChamberOn(void);
void EventPumpChamberOff(void);
void Send_DataToPC (void);
void Event_Control_Enabled(void);
void Event_Control_Disabled(void);
void Stop_Door_Heater(void);
void EventColdStartUp(void);

void RTCEventPumpChamberOn(void);
void RTCEventPumpChamberOff(void);
void Event_Temp_Supervisory(void);

#endif
