#ifndef __OMB_OUTPUT_H
#define __OMB_OUTPUT_H

#define J7_ALARM_RELAY 		0
#define J57_WATER_VALVE		1
#define J53_DECON_FAN		2
#define J22_MAIN_SOL_CO2	3
#define J20_COMPRESSOR		4
#define J14_MAIN_SOL_O2N2	5
#define J15_BACK_SOL_CO2	6
#define J33_UVBALLAST		7
#define J37_LEDDRIVER		8
#define J35_MAINHEATER		9
#define J34_PANHEATER		10
#define J13_ZONE6_HTR		11
#define J14_ZONE5_HTR		12
#define J10_ZONE4_HTR		13
#define J9_ZONE3_HTR		14
#define J5_ZONE2_HTR		15
#define J4_ZONE1_HTR		16
#define BUZZER				17
#define VAISALA_PWR			18
#define J19_DOOR_LOCK		19
#define J56_BACK_SOL_O2		20
#define DAC_CS				21
#define J23_SOL_RH_CNTRL	22

void Exp_FailSafe_Relay_On (void);
void Exp_FailSafe_Relay_Off (void);
void FailSafe_Relay_On(void);
void FailSafe_Relay_Off(void);
void Set_Analog_Mux (char Address);
void Enable_AnalogMux(void);
void Disable_AnalogMux(void);
void TurnOffAllOutputs (void);
void SetOutPut(char Output, char OnOff);


#endif
