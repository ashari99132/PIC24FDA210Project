#ifndef __EVENT_SCHEDULER_H
#define __EVENT_SCHEDULER_H

typedef struct __eventStruct__
{
  BYTE ID;			//used for event which driven by interrupt
  BYTE ENDIS;
  BYTE Type;
  WORD Period;   //in mS.
  WORD RunningTimer;
  void (*RunFunction)();		
}EVENT, *pEVENT;

typedef struct __eventInterruptStruct__
{
  BYTE ID;			//used for event which driven by interrupt
  BYTE ENDIS;
  BYTE Flag;
  void (*RunFunction)();		
}EVENT_INT, *pEVENT_INT;

#define ONCE		0x00
#define PERIODIC 	0x01
#define INT_DRIVEN 	0x02  //can be from HW Int or from softwareInt. 
#define INIT_RUNTIME 	   0
#define MAX_RUNTIME 	1000 //max run time is 1000ms. 
#define EVENT_EN			1
#define EVENT_DIS			0
#define EVENT_RUN			2
#define EVENT_RUN_ONCED		3	

#define SET 		0x01
#define CLEAR 		0x00

#define CLEAR_FLAG  0x00
//events id
#define TOTAL_EVENT				31
#define TOTAL_SOLENOID_EVENT                    4

#define TEMP_PI_ID 				0
#define CO2_PI_ID 				1
#define RH_PI_ID 				2
#define O2_PI_ID 				3
#define AIN_ID 					4
#define PT100_ID 				5
#define NTC_ID 					6
#define IRCO2_ID 				7
#define BATT_ID					8
#define RH_ID 				9
#define OPT2_ID 				10
#define OPT3_ID 				11
#define O2_RS485_ID				12	
#define BUZZER_ID				13
#define VOYAGER_ID 				14
#define USB_ID 					15
#define AC_FREAD_ID				16
#define MAIN_CO2SOL_ID			17
#define BACK_CO2SOL_ID			18
#define MAIN_O2SOL_ID			19
#define BACK_O2SOL_ID			20
#define MAIN_RHSOL_ID			21
#define CO2_RS485_ID			22
#define RH_CTL_ENABLE_ID		23
#define RH_CTL_DISABLE_ID		24
#define HEATERS_OFF_ID			25
#define DOOR_HEATER_OFF_ID		26
#define PAN_HEATER_OFF_ID		27
#define SOL_RH_CONTROL_OFF_ID	28
#define TRIAC_FAIL_DETECTION_ID	29



//interrupt id
#define MAX_INT_ID					11

#define INT_ALARMCONTACT			0
#define INT_UTI						1
#define INT_TCPIP					2
#define INT_DIN						3
#define INT_DOOR					4
#define INT_THERMOSTAT				5
#define INT_WATERLEVEL				6
#define INT_RTC						7
#define INT_CO2RS485				8
#define INT_O2RS485					9
#define INT_UTI_WRITE				10

extern WORD OMB_Software_Ver;
extern WORD Flag[MAX_FLAG_ID];

void RunForeGroundEvents(void);
void RunBackGroundEvents(void);
void SetMainEventPeriod(WORD NewPeriod, BYTE id);
void SetMainEventRunningTimer(WORD NewValue, BYTE id);
void SetMainEventENDIS(BYTE id, BYTE NewValue);
void SetMainEventType(BYTE NewValue, BYTE id);
BYTE RetMainEventType(BYTE id);
BYTE RetMainEventENDIS(BYTE id);
void StartONCEMainEvent(WORD NewPeriod, BYTE id);

void SetIntDrivenEventENDIS(BYTE NewValue, BYTE id);
void SetIntDrivenEventENDIS(BYTE NewValue, BYTE id);
void SetIntDrivenEventFlag(BYTE NewValue, BYTE id);
WORD ReturnFlag(WORD FlagID);
void SetFlag(BYTE FlagID, WORD Value);

#endif
