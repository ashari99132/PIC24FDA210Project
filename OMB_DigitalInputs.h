#ifndef __OMB_DIGITALINPUTS_H
#define __OMB_DIGITALINPUTS_H

#define DOOR_SW_CLOSE				0x0001
#define REFRIGERANT_PSW_CLOSE		0x0002
#define THERSMOSTAT_SW_CLOSE		0x0004
#define CO2TANK_1_PSW_CLOSE			0x0008
#define CO2TANK_2_PSW_CLOSE			0x0010
#define O2TANK_1_PSW_CLOSE			0x0020
#define O2TANK_2_PSW_CLOSE			0x0040
#define SMPS_LIVE					0x0080
#define NOW_USE_CO2TANK_1			0x0100
#define NOW_USE_CO2TANK_2			0x0200
#define NOW_USE_O2TANK_1			0x0400
#define NOW_USE_O2TANK_2			0x0800
#define WATER_LEVEL_SW_CLOSE		0x1000
#define SPARE_IO_5_TRIAC_STAT           0x2000

#define TRIAC_FAIL_DEBOUNCE_TIME        1570 //ms

BYTE ReturnRefrigerant_PSW(void);
BYTE ReturnO2N2Tank_1_PSW(void)	;
BYTE ReturnO2N2Tank_2_PSW(void)	;
BYTE ReturnDoor_SW(void);
BYTE ReturnThermostat_SW(void);
BYTE ReturnSMPSFailure_Detection(void);
BYTE ReturnCO2Tank_1_PSW(void);
BYTE ReturnCO2Tank_2_PSW(void);
BYTE ReturnWaterLevelSensor (void);
BYTE ReturnSpareIO5Port(void);
void EventUpdateDigitalSensors (void);
void EventDoor (void);
void EventThermostat(void);
void EventWaterLevel (void);
void EventTriacFailDetection(void);
void TriacDebounceCntDown(void);


#endif
