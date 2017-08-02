#ifndef __FLAG_ID_H
#define __FLAG_ID_H

#define MAX_FLAG_ID						8

 enum _Flag_Id_  {
OMB_SENSOR_STATUS_FLAG=0,
OMB_ALARM_STATUS_FLAG,
COMPRESSOR_CONTROL_FLAG,					
SYSTEM_MODE_FLAG,				
ALRELAY_FLAG,
OMB_CELSAFE_OPT_FLAG,
OMB_OUTPUTS_FLAG,				
OMB_SWITCHES_STATUS_FLAG,
};

#define DFLT_SENSOR_STATUS_FLAG			0x0000
#define DFLT_ALARM_STATUS_FLAG			0x0000
#define DFLT_COMPRESSOR_CONTROL_FLAG	FLAG_COMP_OFF
#define DFLT_SYSTEM_MODE_FLAG			NORMAL_MODE 
#define DFLT_MODEL_FLAG					0x00
#define DFLT_OMB_SHAKER_OPT_FLAG		FREEZER_OPT|LAMP_OPT|GROWLAMP_OPT|UV_OPT
#define DFLT_OMB_OUTPUTS_FLAG				0x0000
#define DFLT_OMB_SWITCHES_STATUS_FLAG		0x0000

//--------OMB_O2RS485_CTL flags ------------
#define O2_RS485_CALIBRATE         1
//OMB_ALARM_STATUS_FLAG
#define T_HIGH_ALARM			0x0001
#define T_LOW_ALARM				0x0002
#define T_DEV_ALARM				0x0004
#define CO2_HIGH_ALARM			0x0008
#define CO2_LOW_ALARM			0x0010
#define O2_HIGH_ALARM			0x0020
#define O2_LOW_ALARM			0x0040 
#define RH_LOW_ALARM			0x0080
#define RH_HIGH_ALARM			0x0100
#define TSP_REACH				0x0200
#define CO2SP_REACH				0x0400
#define O2SP_REACH				0x0800
#define RHSP_REACH				0x1000

//------Celsafe system mode flag------
#define FACTORY_MODE 0x0004
#define TEST_MODE 0x0002
#define NORMAL_MODE 0x0001
#define DECON_MODE  0x0008
#define DECONSTOP_MODE	0x0010


//------Celsafe Option Flag---------
#define FREEZER_OPT				0x0001
#define CO2_OPT					0x0002
#define RH_OPT					0x0004
#define O2_OPT					0x0008
#define LAMP_OPT		      	0x0010
#define GROWLAMP_OPT			0x0020
#define UV_OPT					0x0040
#define CO2_TANK_ALARM_OPT		0x0080
#define O2_TANK_ALARM_OPT		0x0100
#define CO2_BACKUP_OPT			0x0200
#define O2_BACKUP_OPT			0x0400


//------Celsafe Alarm Relay Flag----
#define ALRELAY_PWR_CYCLE		0x0001
#define ALRELAY_T				0x0002
#define ALRELAY_CO2				0x0004
#define ALRELAY_O2				0x0008
#define ALRELAY_RH				0x0010



//------Output Flag---------

#define MAIN_HEATER_FLAG				0x0001  //Zone 1 heater
#define BASE_HEATER_FLAG				0x0002	//Zone 2 heater
#define DOOR_HEATER_FLAG				0x0004	//Zone 3 heater
#define DECON_HEATER_FLAG				0x0008	//Zone 4 heater
#define TUBE_HEATER_FLAG				0x0010  //Zone 5 heater
#define PUMP_FLAG						0x0020  //Zone 6 heater
#define DECON_FAN_FLAG					0x0040  
#define CO2_SOL_MAIN_FLAG				0x0080
#define O2_SOL_MAIN_FLAG				0x0100	
#define CO2_SOL_BACK_FLAG				0x0200
#define O2_SOL_BACK_FLAG				0x0400
#define EM_LOCK_FLAG					0x0800
#define UV_LAMP_FLAG					0x1000
#define WATER_HEATER_FLAG				0x2000
#define WATER_VALVE_RELAY_FLAG			0x4000
#define ALARM_CONTACT_RELAY_FLAG		0x8000


#define TURN_OFF_ALL_OUTPUT_FLAG	0x0000
#endif
