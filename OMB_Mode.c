/**
OMB_Mode.c
**/
#include "ApplicationDrivers.h"
#include "OMB_Mode.h"

WORD CelSafeOptions;
void UpdateSystemSensor (void)
{
	
	//WORD Options=ReturnFlag(OMB_CELSAFE_OPT_FLAG);	
	
	SetMainEventENDIS(PT100_ID,EVENT_EN);
	SetMainEventENDIS(NTC_ID,EVENT_EN);
	SetMainEventENDIS(CO2_RS485_ID,EVENT_EN);
	SetIntDrivenEventENDIS(EVENT_EN,INT_CO2RS485);
	SetOutPut(VAISALA_PWR,ON);
	
	if(CelSafeOptions&RH_OPT)SetMainEventENDIS(RH_ID,EVENT_EN);
	else SetMainEventENDIS(RH_ID,EVENT_DIS);

	if(CelSafeOptions&O2_OPT)
	{
		SetMainEventENDIS(O2_RS485_ID,EVENT_EN);
		Initialize_O2RS485();
		SetIntDrivenEventENDIS(EVENT_EN,INT_O2RS485);
	}
	else
	{
		SetMainEventENDIS(O2_RS485_ID,EVENT_DIS);
		Stop_O2RS485();
		SetIntDrivenEventENDIS(EVENT_DIS,INT_O2RS485);
	}
	Stop_PID_Heater();
	EventFanDeconOff();
	SetCOBias(0.0);

}

void UpdateSystemMode(void)
{
 WORD Mode=ReturnFlag(SYSTEM_MODE_FLAG);
 switch (Mode)
 {
	case TEST_MODE: 
	case FACTORY_MODE:
 	 	Set_FactoryMode();
 	 	break;
  	case NORMAL_MODE:
		UpdateSystemSensor(); 
 		Set_NormalMode();
		break;
	case DECON_MODE:
		Set_DeconMode(); 
		break;
	case DECONSTOP_MODE:
	 	Set_DeconStopMode();
		break;
 	default:
 		break;
 	
 }
}

void Set_FactoryMode(void)
{

TurnOffAllOutputs ();
SetMainEventENDIS(TEMP_PI_ID,EVENT_DIS);
SetMainEventENDIS(CO2_PI_ID,EVENT_DIS);
SetMainEventENDIS(RH_PI_ID,EVENT_DIS);
SetMainEventENDIS(O2_PI_ID,EVENT_DIS);

}
void Set_NormalMode(void)
{
    WORD *pTsp;
    SHORT *pTcv_Offset;
    pTsp=&Tsp;
    pTcv_Offset=&Tcv_Offset;
WORDTOBYTE tempValue;
//WORD Options=ReturnFlag(OMB_CELSAFE_OPT_FLAG);

EEPROM_Read(0x0000, &tempValue.bytes[0], 2);
Delay_uS(5000);
*pTsp=tempValue.word;
EEPROM_Read(0x0024, &tempValue.bytes[0], 2);
Delay_uS(5000);
*pTcv_Offset=tempValue.word;

SetOutPut(VAISALA_PWR,ON);

 //if(ReturnTimerRTCENDIS(COLD_CTL_ENABLE_ID)!=EVENT_EN)
     SetMainEventENDIS(TEMP_PI_ID,EVENT_EN);
SetMainEventENDIS(CO2_PI_ID,EVENT_EN);
SetIntDrivenEventENDIS(EVENT_EN,INT_THERMOSTAT);
SetIntDrivenEventENDIS(EVENT_EN,INT_DOOR);
SetIntDrivenEventENDIS(EVENT_EN,INT_WATERLEVEL);

if(CelSafeOptions&O2_OPT)
    SetMainEventENDIS(O2_PI_ID,EVENT_EN);
else
    SetMainEventENDIS(O2_PI_ID,EVENT_DIS);

Exp_FailSafe_Relay_On();
FailSafe_Relay_On();
   
//Stop_PID_Heater();
EventFanDeconOff();
SetCOBias(0.0);
//EventPumpChamberOn();
RTCEventPumpChamberOn();
}

void Set_DeconMode (void)
{
//	WORD Options=ReturnFlag(OMB_CELSAFE_OPT_FLAG);
    SHORT *pTcv_Offset;
    WORD *pTsp;
    //WORD EMLockON=ReturnFlag(OMB_OUTPUTS_FLAG);
        pTsp=&Tsp;
        *pTsp=20000;
        pTcv_Offset=&Tcv_Offset;
	*pTcv_Offset+=1500;

        //EMLockON|=EM_LOCK_FLAG;
        //SetFlag(OMB_OUTPUTS_FLAG,EMLockON);
        //EventEMLock();

	SetMainEventENDIS(CO2_PI_ID,EVENT_DIS);
	SetMainEventENDIS(CO2_RS485_ID,EVENT_DIS);	
	Event_CO2_MainSol_Off();
	Event_CO2_BackSol_Off();
	if(CelSafeOptions&O2_OPT)
	{
	SetMainEventENDIS(O2_PI_ID,EVENT_DIS);
	SetMainEventENDIS(O2_RS485_ID,EVENT_DIS);
    Stop_O2RS485();	
	Event_O2_MainSol_Off();
	Event_O2_BackSol_Off();
	}
        FailSafe_Relay_On();
        DelayMs(5000);
	SetOutPut(VAISALA_PWR,OFF);
	EventPumpChamberOff();
        StopTimerRTC(PUMP_ON_ID);
        StopTimerRTC(PUMP_OFF_ID);
	EventFanDeconOn();
	SetOutPut(J14_ZONE5_HTR,OFF);
	SetCOBias(90.0);
}

void Set_DeconStopMode(	void )
{
    WORD *pTsp;
        pTsp=&Tsp;
        *pTsp=3700;
	SetCOBias(0.0);
	Stop_PID_Heater();
}
void UpdateOutput(void)
{
	WORD Mode=ReturnFlag(SYSTEM_MODE_FLAG);
	
	switch (Mode)
	{
	   case TEST_MODE: 
	   case FACTORY_MODE:
		   Output_Manual_Control();
		   break;
	   case NORMAL_MODE:
		  	EventUVLamp();
			EventEMLock();
			break;
	   default:
		   break;	   
	}
}

void Output_Manual_Control(void)
{
	WORD OutputsFlag=ReturnFlag(OMB_OUTPUTS_FLAG);
 
if (OutputsFlag&MAIN_HEATER_FLAG)SetOutPut(J4_ZONE1_HTR,ON);
else SetOutPut(J4_ZONE1_HTR,OFF);

if (OutputsFlag&BASE_HEATER_FLAG)SetOutPut(J5_ZONE2_HTR,ON);
else SetOutPut(J5_ZONE2_HTR,OFF);

if (OutputsFlag&DOOR_HEATER_FLAG)SetOutPut(J9_ZONE3_HTR,ON);
else SetOutPut(J9_ZONE3_HTR,OFF);

if (OutputsFlag&DECON_HEATER_FLAG)SetOutPut(J10_ZONE4_HTR,ON);
else SetOutPut(J10_ZONE4_HTR,OFF);

if (OutputsFlag&TUBE_HEATER_FLAG)SetOutPut(J14_ZONE5_HTR,ON);				
else SetOutPut(J14_ZONE5_HTR,OFF);				
 
if (OutputsFlag&PUMP_FLAG)SetOutPut(J13_ZONE6_HTR,ON);
else SetOutPut(J13_ZONE6_HTR,OFF); 

if (OutputsFlag&DECON_FAN_FLAG)SetOutPut(J53_DECON_FAN,ON);
else SetOutPut(J53_DECON_FAN,OFF);

if (OutputsFlag&CO2_SOL_MAIN_FLAG)SetOutPut(J22_MAIN_SOL_CO2,ON);
else SetOutPut(J22_MAIN_SOL_CO2,OFF);

if (OutputsFlag&O2_SOL_MAIN_FLAG)SetOutPut(J14_MAIN_SOL_O2N2,ON);
else SetOutPut(J14_MAIN_SOL_O2N2,OFF);


if (OutputsFlag&CO2_SOL_BACK_FLAG)SetOutPut(J15_BACK_SOL_CO2,ON);
else SetOutPut(J15_BACK_SOL_CO2,OFF);			


if (OutputsFlag&O2_SOL_BACK_FLAG)SetOutPut(J56_BACK_SOL_O2,ON);
else SetOutPut(J56_BACK_SOL_O2,OFF);

if (OutputsFlag&EM_LOCK_FLAG)SetOutPut(J19_DOOR_LOCK,ON);
else SetOutPut(J19_DOOR_LOCK,OFF);

if (OutputsFlag&UV_LAMP_FLAG)SetOutPut(J33_UVBALLAST,ON);
else SetOutPut(J33_UVBALLAST,OFF); 				

if (OutputsFlag&WATER_HEATER_FLAG)SetOutPut(J34_PANHEATER,ON);				
else SetOutPut(J34_PANHEATER,OFF); 			

if (OutputsFlag&WATER_VALVE_RELAY_FLAG)SetOutPut(J57_WATER_VALVE,ON);				
else SetOutPut(J57_WATER_VALVE,OFF); 			

}

void EventEMLock (void)
{
  WORD EMLockON=ReturnFlag(OMB_OUTPUTS_FLAG)&EM_LOCK_FLAG;
 if (EMLockON)SetOutPut(J19_DOOR_LOCK,ON);
 else SetOutPut(J19_DOOR_LOCK,OFF);

}

