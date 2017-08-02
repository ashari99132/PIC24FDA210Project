/**
OMB_DigitalInputs.c
**/
#include "ApplicationDrivers.h"
#include "OMB_DigitalInputs.h"
#include "HardwareProfile.h"

BYTE ReturnRefrigerant_PSW(void)
{
	return PORTEbits.RE8;
}

BYTE ReturnO2N2Tank_1_PSW(void)	
{
	return PORTGbits.RG15;
}

BYTE ReturnO2N2Tank_2_PSW(void)	
{
	return PORTDbits.RD14;
}

BYTE ReturnDoor_SW(void)		
{
	return PORTFbits.RF13;
}

BYTE ReturnThermostat_SW(void)		
{
	return PORTDbits.RD3;
}

BYTE ReturnSMPSFailure_Detection(void)		
{
	return PORTDbits.RD0;
}

BYTE ReturnCO2Tank_1_PSW(void)		
{
	return PORTDbits.RD9;
}

BYTE ReturnCO2Tank_2_PSW(void)			
{
	return PORTDbits.RD1;
}

BYTE ReturnWaterLevelSensor (void)
{
	return PORTAbits.RA4;
}

void EventUpdateDigitalSensors (void)
{

WORD SwitchStatus= ReturnFlag(OMB_SWITCHES_STATUS_FLAG);

//----CO2 Tank 1 Pressure Switch-----
if(ReturnCO2Tank_1_PSW()&& !(SwitchStatus&CO2TANK_1_PSW_CLOSE))
SwitchStatus|=CO2TANK_1_PSW_CLOSE;   
else if (!ReturnCO2Tank_1_PSW()&& (SwitchStatus&CO2TANK_1_PSW_CLOSE))
SwitchStatus&=~CO2TANK_1_PSW_CLOSE;	 

//----CO2 Tank 2 Pressure Switch-----
if(ReturnCO2Tank_2_PSW()&& !(SwitchStatus&CO2TANK_2_PSW_CLOSE))
SwitchStatus|=CO2TANK_2_PSW_CLOSE;   
else if (!ReturnCO2Tank_2_PSW()&& (SwitchStatus&CO2TANK_2_PSW_CLOSE))
SwitchStatus&=~CO2TANK_2_PSW_CLOSE;	 

//----O2 Tank 1 Pressure Switch-----
if(ReturnO2N2Tank_1_PSW()&& !(SwitchStatus&O2TANK_1_PSW_CLOSE))
SwitchStatus|=O2TANK_1_PSW_CLOSE;   
else if (!ReturnO2N2Tank_1_PSW()&& (SwitchStatus&O2TANK_1_PSW_CLOSE))
SwitchStatus&=~O2TANK_1_PSW_CLOSE;	 

//----O2 Tank 2 Pressure Switch-----
if(ReturnO2N2Tank_2_PSW()&& !(SwitchStatus&O2TANK_2_PSW_CLOSE))
SwitchStatus|=O2TANK_2_PSW_CLOSE;   
else if (!ReturnO2N2Tank_2_PSW()&& (SwitchStatus&O2TANK_2_PSW_CLOSE))
SwitchStatus&=~O2TANK_2_PSW_CLOSE;	 

//----Door Switch-----
if(ReturnDoor_SW() && !(SwitchStatus&DOOR_SW_CLOSE))
{
 SwitchStatus|=DOOR_SW_CLOSE;	
 SetIntDrivenEventFlag(SET,INT_DOOR);
}
else if (!ReturnDoor_SW() && (SwitchStatus&DOOR_SW_CLOSE))
{
	SwitchStatus&=~DOOR_SW_CLOSE;   
	SetIntDrivenEventFlag(SET,INT_DOOR);
}

//----Thermostat  Switch-----	
if(ReturnThermostat_SW() && !(SwitchStatus&THERSMOSTAT_SW_CLOSE))	
{
 SwitchStatus|=THERSMOSTAT_SW_CLOSE;	
 SetIntDrivenEventFlag(SET,INT_THERMOSTAT);
}
else if (!ReturnThermostat_SW() && (SwitchStatus&THERSMOSTAT_SW_CLOSE))
{
 SwitchStatus&=~THERSMOSTAT_SW_CLOSE;	
 SetIntDrivenEventFlag(SET,INT_THERMOSTAT);
}


//----SMPS Failure Detection-----

if(ReturnSMPSFailure_Detection() && !(SwitchStatus&SMPS_LIVE) )
{
 SwitchStatus|=SMPS_LIVE;	
}
else if (!ReturnSMPSFailure_Detection() && (SwitchStatus&SMPS_LIVE) )
{
 SwitchStatus&=~SMPS_LIVE;   
}
//----Water Level Sensor-----

if(ReturnWaterLevelSensor() && !(SwitchStatus&WATER_LEVEL_SW_CLOSE) )
 {
  SwitchStatus|=WATER_LEVEL_SW_CLOSE;
  SetIntDrivenEventFlag(SET,INT_WATERLEVEL);
 }
else if (!ReturnWaterLevelSensor() && (SwitchStatus&WATER_LEVEL_SW_CLOSE) )
 {
  SwitchStatus&=~WATER_LEVEL_SW_CLOSE;	
  SetIntDrivenEventFlag(SET,INT_WATERLEVEL);
 }

SetFlag(OMB_SWITCHES_STATUS_FLAG,SwitchStatus);

}

void EventDoor (void)
{
WORD DoorClose = ReturnFlag(OMB_SWITCHES_STATUS_FLAG)&DOOR_SW_CLOSE;
WORD Mode=ReturnFlag(SYSTEM_MODE_FLAG);
WORD AlarmStatus=ReturnFlag(OMB_ALARM_STATUS_FLAG);
 	switch(Mode)
 		{
			case FACTORY_MODE:
			case NORMAL_MODE:
				if(DoorClose)
					{
                                       // if(ReturnTimerRTCENDIS(COLD_CTL_ENABLE_ID)!=EVENT_EN)
                                        //    {
                                            //EventPumpChamberOn();
                                            RTCEventPumpChamberOn();
                                            StartTimerRTC(CTL_ENABLE_ID,ONCE,1*MINUTE);
                                            SetMainEventENDIS(CO2_PI_ID,EVENT_EN);
                                            Update_Zone2_OC4_PWM(0.0);//fix base
                                         //   }
					}
				else{
					//EventPumpChamberOff();
					StopTimerRTC(PUMP_ON_ID);
                                        StopTimerRTC(PUMP_OFF_ID);
                                        Event_Control_Disabled();
                                        Update_Zone2_OC4_PWM(10.0);//fix base
                                        Update_Zone4_OC6_PWM(5.0);//fix secondary
                                }
				break;
			case DECON_MODE:
				if(DoorClose)EventFanDeconOn();
				else EventFanDeconOff();
				break;
	}
if(!DoorClose && (AlarmStatus&TSP_REACH))
	{
		AlarmStatus&=~TSP_REACH;
   		SetFlag(OMB_ALARM_STATUS_FLAG,AlarmStatus);
	}
SetIntDrivenEventFlag(CLEAR,INT_DOOR);
}

void EventThermostat(void)
{
	WORD ThermostatClose = ReturnFlag(OMB_SWITCHES_STATUS_FLAG)&THERSMOSTAT_SW_CLOSE;
    if(ThermostatClose)UpdateSystemMode();
	else{
	 		SetMainEventENDIS(TEMP_PI_ID,EVENT_DIS);
			SetMainEventENDIS(CO2_PI_ID,EVENT_DIS);
			SetMainEventENDIS(O2_PI_ID,EVENT_DIS);
			//SetMainEventENDIS(RH_PI_ID,EVENT_DIS);
			Stop_PID_Heater();
			Event_CO2_MainSol_Off();
			Event_O2_MainSol_Off();
			Event_CO2_BackSol_Off();
			Event_O2_BackSol_Off();
			//Event_RH_Control_Off();
	}
 	SetIntDrivenEventFlag(CLEAR,INT_THERMOSTAT);			
}
void EventWaterLevel (void)
{
	WORD WaterLevelFull = ReturnFlag(OMB_SWITCHES_STATUS_FLAG)&WATER_LEVEL_SW_CLOSE;
	if (!WaterLevelFull)StartONCEMainEvent(1,RH_CTL_DISABLE_ID);
	else StartONCEMainEvent(3000,RH_CTL_ENABLE_ID);	

	SetIntDrivenEventFlag(CLEAR,INT_WATERLEVEL); 
}


