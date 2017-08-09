/**
OMB_Output.c

Driver for O series main board outputs.c
**/

#include "OMB_Output.h"
#include "ApplicationDrivers.h"
#include "HardwareProfile.h"





void Exp_FailSafe_Relay_On (void)

{
	LATA|=PIN_10;
	//AC_CUTOFF_RELAY1_J41=ON;	
	Delay_uS(10);
}
void Exp_FailSafe_Relay_Off (void)
{
	LATA&=~PIN_10;
	//AC_CUTOFF_RELAY1_J41=OFF;	
	Delay_uS(10);
}

void FailSafe_Relay_On(void)
{
	LATG|=PIN_14;
	//AC_CUTOFF_RELAY2=ON;
	Delay_uS(10);
}
void FailSafe_Relay_Off(void)
{
	LATG&=~PIN_14;
	//AC_CUTOFF_RELAY2=OFF;
	Delay_uS(10);
}
void Set_Analog_Mux (char Address)
{
	switch(Address)
	{
		case 0:
			LATD&=~(PIN_12|PIN_13);
			//ANALOGBRD_MUX_A0=0;	
			//ANALOGBRD_MUX_A1=0;		
			break;
			
		case 1:
			LATD&=~(PIN_12|PIN_13);
			LATD|=PIN_12;
			//ANALOGBRD_MUX_A0=0;		
			//ANALOGBRD_MUX_A1=1;		
			break;
		case 2:
			LATD&=~(PIN_12|PIN_13);
			LATD|=PIN_13;
			//ANALOGBRD_MUX_A0=1;		
			//ANALOGBRD_MUX_A1=0;		
			break;
		case 3:
		    LATD|=(PIN_12|PIN_13);
			//ANALOGBRD_MUX_A0=1;		
			//ANALOGBRD_MUX_A1=1;		
		
			break;
	}
		Delay_uS(10);
}
void Enable_AnalogMux(void)
{
	LATD|=PIN_6;
	//ANALOGBRD_MUX_EN=ON;
	Delay_uS(10);	
}
void Disable_AnalogMux(void)
{
	LATD&=~PIN_6;
	//ANALOGBRD_MUX_EN=OFF;	
	Delay_uS(10);
}


void TurnOffAllOutputs (void)
{
SetFlag(OMB_OUTPUTS_FLAG,0);
SetOutPut(J7_ALARM_RELAY,OFF);
//SetOutPut(J57_WATER_VALVE,OFF);
SetOutPut(J53_DECON_FAN,OFF);
SetOutPut(J22_MAIN_SOL_CO2,OFF);
SetOutPut(J20_COMPRESSOR,OFF);
SetOutPut(J14_MAIN_SOL_O2N2,OFF);
SetOutPut(J15_BACK_SOL_CO2,OFF);
SetOutPut(J33_UVBALLAST,OFF);
SetOutPut(J37_LEDDRIVER	,OFF);
SetOutPut(J35_MAINHEATER,OFF);
SetOutPut(J34_PANHEATER	,OFF);
SetOutPut(J13_ZONE6_HTR,OFF);
SetOutPut(J14_ZONE5_HTR	,OFF);
SetOutPut(J10_ZONE4_HTR	,OFF);
SetOutPut(J9_ZONE3_HTR,OFF);
SetOutPut(J5_ZONE2_HTR,OFF);
SetOutPut(J4_ZONE1_HTR,OFF);
SetOutPut(BUZZER,OFF);
SetOutPut(J4_ZONE1_HTR,OFF);
SetOutPut(J23_SOL_RH_CNTRL,OFF);


}



void SetOutPut (char Output, char OnOff)
{
	switch (Output)
		{
			case J7_ALARM_RELAY :
				LATEbits.LATE5=OnOff;
				break;
			case J57_WATER_VALVE :	
				LATGbits.LATG6=OnOff;
				break;
			case J53_DECON_FAN :	 	
				LATAbits.LATA3=OnOff;
				break;
			case J22_MAIN_SOL_CO2 :	
				LATBbits.LATB12=OnOff;
				break;
			case J20_COMPRESSOR :		
				LATBbits.LATB13=OnOff;
				break;
			case J14_MAIN_SOL_O2N2 :	
				LATBbits.LATB9=OnOff;
				break;
			case J15_BACK_SOL_CO2:
				LATBbits.LATB11=OnOff;
				break;
			case J33_UVBALLAST	:
				LATAbits.LATA9=OnOff;
				break;
			case J37_LEDDRIVER	:	
				LATDbits.LATD7=OnOff;
				break;
			case J35_MAINHEATER	:	
				if(OnOff)Update_OC1_PWM(100.0);
				else Update_OC1_PWM(0.0);
				break;
			case J34_PANHEATER	:	
				if(OnOff)Update_OC2_PWM(100.0);
				else Update_OC2_PWM (0.0);
				break;
			case J13_ZONE6_HTR	:	
				if(OnOff)Update_Zone6_OC8_PWM (100.0);
				else Update_Zone6_OC8_PWM (0.0);
				break;
			case J14_ZONE5_HTR	:	
				if(OnOff)Update_Zone5_OC7_PWM (100.0);
				else Update_Zone5_OC7_PWM(0.0);
				break;
			case J10_ZONE4_HTR	:	
				if(OnOff)Update_Zone4_OC6_PWM (100.0);
				else Update_Zone4_OC6_PWM(0.0);
				break;
			case J9_ZONE3_HTR	:
				if(OnOff)Update_Zone3_OC5_PWM(100.0);
				else Update_Zone3_OC5_PWM(0.0);
				break;
			case J5_ZONE2_HTR	:	
				if(OnOff)Update_Zone2_OC4_PWM(100.0);
				else Update_Zone2_OC4_PWM(0.0);
				break;
			case J4_ZONE1_HTR	:	
				if(OnOff)Update_Zone1_OC3_PWM (100.0);
				else Update_Zone1_OC3_PWM (0.0);
				break;		
			case BUZZER	:
				LATEbits.LATE4=OnOff;
				break;
			case VAISALA_PWR	:
				LATAbits.LATA7=OnOff;
				break;
			case J19_DOOR_LOCK:
				LATBbits.LATB10=OnOff;
				break;
			case J56_BACK_SOL_O2 :
				LATEbits.LATE1=OnOff;
				break;
			case DAC_CS:
				LATAbits.LATA1=OnOff;
				break;
			case J23_SOL_RH_CNTRL:
				SPARE1_J23=OnOff;
				break;
			default:
			 	break;
	}
	Delay_uS(10);
}


