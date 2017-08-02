#ifndef __P24FJ256DA210_OCX_H
#define __P24FJ256DA210_OCX_H
	
	/*  
	The following configuration for OC1, OC2, OC3 and OC4 will set the 
	Output Compare modules for PWM mode w/o FAULT pin enabled, 
	a 50%/75% duty cycle and PWM frequency of 1 kHz at Fosc = 32 MHz. 
	System clock is selected as the clock for the PWM time base 
	and no interrupt is enabled. The four PWM channels are synchronised
	by OC1, therefore OC1 should be initialized at last. OC2 and OC4 are
	complementary to OC1 and OC3 respectively. 
	
	Find the Period register value for a desired PWM frequency of 400 Hz, 
	where Fosc = 8 MHz with PLL (32 MHz device clock rate). 
	Tcy = 2/Fosc = 62.5 ns
	PWM Period   =  1/PWM Frequency = 1/50 Hz = 20 ms
	PWM Period   = (OC1RS + 1) * Tcy
	20ms = (OC1RS + 1) * 62.5 ns * 1 
	OC1RS = 39999 (0x9C3F)
	*/
#define OC_PWM_PERIOD 	0x9C3F
void Initialize_OC_Module (void);
void Update_OC1_PWM  ( float fDcy); //Main Heater
void Update_OC2_PWM  ( float fDcy);//Pan Heater
void Update_Zone1_OC3_PWM  ( float fDcy);
void Update_Zone2_OC4_PWM  ( float fDcy);
void Update_Zone3_OC5_PWM  ( float fDcy);
void Update_Zone4_OC6_PWM  ( float fDcy);
void Update_Zone5_OC7_PWM  ( float fDcy);
void Update_Zone6_OC8_PWM ( float fDcy);


#endif




