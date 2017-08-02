/**
p24FJ256DA210_OC1.c

Configured as PWM output 16 bit.
**/
// local includes
#include "HardwareProfile.h"
#include "p24FJ256DA210_OCX.h"
#include "General.h"
#include "ApplicationDrivers.h"

void Initialize_OC_Module (void)
{
	OC8CON1 			= 0;		// It is a good practice to clear off the control bits initially
	OC8CON2 			= 0;
	OC8R				= 0;	// Initialize Compare Register1 with 0% duty cycle
	OC8CON2bits.SYNCSEL = 0b01110;//0x1;		// synchronized by timer4
	OC8CON1bits.OCTSEL	= 0x2;//0x7;	//use timer4	// System Clock (Tcy) is the clock source for output Compare
	OC8CON1bits.OCFLT	= 0;		// No PWM Fault condition has occurred (this bit is only used when OCM<2:0> = 111)
	OC8CON2bits.OCINV	= 0;		// OCx output is inverted
	OC8CON1bits.OCM 	= 0x6;		// Edge-aligned PWM mode on OC



	OC7CON1				= 0; 		// It is a good practice to clear off the control bits initially
	OC7CON2				= 0;
	OC7R				= 0;	// Initialize Compare Register1 with 0% duty cycle
	OC7CON2bits.SYNCSEL	= 0b01110;//0x1;		// synchronized by timer4
	OC7CON1bits.OCTSEL	= 0x2;//0x7;	//use timer4	// System Clock (Tcy) is the clock source for output Compare
	OC7CON1bits.OCFLT	= 0;		// No PWM Fault condition has occurred (this bit is only used when OCM<2:0> = 111)
	OC7CON2bits.OCINV	= 0;		// OCx output is inverted
	OC7CON1bits.OCM		= 0x6;		// Edge-aligned PWM mode on OC
	
	OC6CON1				= 0; 		// It is a good practice to clear off the control bits initially
	OC6CON2				= 0;
	OC6R				= 0;	// Initialize Compare Register1 with 0% duty cycle
	OC6CON2bits.SYNCSEL	= 0b01110;//0x1;		// synchronized by timer4
	OC6CON1bits.OCTSEL	=0x2;//0x7;	//use timer4	// System Clock (Tcy) is the clock source for output Compare
	OC6CON1bits.OCFLT	= 0;		// No PWM Fault condition has occurred (this bit is only used when OCM<2:0> = 111)
	OC6CON2bits.OCINV	= 0;		// OCx output is inverted
	OC6CON1bits.OCM		= 0x6;		// Edge-aligned PWM mode on OC


	OC5CON1				= 0; 		// It is a good practice to clear off the control bits initially
	OC5CON2				= 0;
	OC5R				= 0;	// Initialize Compare Register1 with 0% duty cycle
	OC5CON2bits.SYNCSEL	= 0b01110;//0x1;		// synchronized by timer4
	OC5CON1bits.OCTSEL	= 0x2;//0x7;	//use timer4	// System Clock (Tcy) is the clock source for output Compare
	OC5CON1bits.OCFLT	= 0;		// No PWM Fault condition has occurred (this bit is only used when OCM<2:0> = 111)
	OC5CON2bits.OCINV	= 0;		// OCx output is inverted
	OC5CON1bits.OCM		= 0x6;		// Edge-aligned PWM mode on OC


	OC4CON1				= 0; 		// It is a good practice to clear off the control bits initially
	OC4CON2				= 0;
	OC4R				= 0;	// Initialize Compare Register1 with 0% duty cycle
	OC4CON2bits.SYNCSEL	= 0b01110;//0x1;		// synchronized by timer4
	OC4CON1bits.OCTSEL	=0x2;//0x7;	//use timer4	// System Clock (Tcy) is the clock source for output Compare
	OC4CON1bits.OCFLT	= 0;		// No PWM Fault condition has occurred (this bit is only used when OCM<2:0> = 111)
	OC4CON2bits.OCINV	= 0;		// OCx output is inverted
	OC4CON1bits.OCM		= 0x6;		// Edge-aligned PWM mode on OC

	OC3CON1				= 0; 		// It is a good practice to clear off the control bits initially
	OC3CON2				= 0;
	OC3R				= 0;	// Initialize Compare Register1 with 0% duty cycle
	OC3CON2bits.SYNCSEL	= 0b01110;//0x1;		// synchronized by timer4
	OC3CON1bits.OCTSEL	= 0x2;//0x7;	//use timer4	// System Clock (Tcy) is the clock source for output Compare
	OC3CON1bits.OCFLT	= 0;		// No PWM Fault condition has occurred (this bit is only used when OCM<2:0> = 111)
	OC3CON2bits.OCINV	= 0;		// OCx output is inverted
	OC3CON1bits.OCM		= 0x6;		// Edge-aligned PWM mode on OC
	
	OC2CON1				= 0; 		// It is a good practice to clear off the control bits initially
	OC2CON2				= 0;
	OC2R				= 0;	// Initialize Compare Register1 with 0% duty cycle
	OC2CON2bits.SYNCSEL	= 0b01110;//0x1;		// synchronized by timer4
	OC2CON1bits.OCTSEL	= 0x2;//0x7;	//use timer4	// System Clock (Tcy) is the clock source for output Compare
	OC2CON1bits.OCFLT	= 0;		// No PWM Fault condition has occurred (this bit is only used when OCM<2:0> = 111)
	OC2CON2bits.OCINV	= 0;		// OCx output is inverted
	OC2CON1bits.OCM		= 0x6;		// Edge-aligned PWM mode on OC
	
	OC1CON1				= 0; 		// It is a good practice to clear off the control bits initially
	OC1CON2				= 0;
	OC1R				= 0;		// Initialize Compare Register1 with 0% duty cycle
	OC1RS				= 10;//OC_PWM_PERIOD ;	// Calculate the desired period for OC1, OC2, OC3 and OC4.
	OC1CON2bits.SYNCSEL	= 0b01110;//0x1;		// synchronized by timer4
	OC1CON1bits.OCTSEL	= 0x2;//0x7;	//use timer4	// System Clock (Tcy) is the clock source for output Compare
	OC1CON1bits.OCFLT	= 0;		// No PWM Fault condition has occurred (this bit is only used when OCM<2:0> = 111)
	OC1CON2bits.OCINV	= 0;		// OCx output is not inverted
	OC1CON1bits.OCM		= 0x6;		// Edge-aligned PWM mode on OC	
}
void Update_OC1_PWM ( float fDcy)
{
 OC1R = fDcy* 0.01*OC_PWM_PERIOD;
}

void Update_OC2_PWM ( float fDcy)
{
 OC2R = fDcy* 0.01*OC_PWM_PERIOD;
}

void Update_Zone1_OC3_PWM ( float fDcy)
{
 OC3R = fDcy* 0.01*OC_PWM_PERIOD;
}
void Update_Zone2_OC4_PWM ( float fDcy)
{
 OC4R = fDcy* 0.01*OC_PWM_PERIOD;
}
void Update_Zone3_OC5_PWM ( float fDcy)
{
 OC5R = fDcy* 0.01*OC_PWM_PERIOD;
}
void Update_Zone4_OC6_PWM ( float fDcy)
{
 OC6R = fDcy* 0.01*OC_PWM_PERIOD;
}
void Update_Zone5_OC7_PWM ( float fDcy)
{
 OC7R = fDcy* 0.01*OC_PWM_PERIOD;
}
void Update_Zone6_OC8_PWM ( float fDcy)
{
 OC8R = fDcy* 0.01*OC_PWM_PERIOD;
}


