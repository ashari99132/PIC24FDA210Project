/**
p24FJ256DA210_Timer1.c


**/
// local includes
#include "HardwareProfile.h"
#include "p24FJ256DA210_Timer1.h"
#include "ApplicationDrivers.h"

//global variable

void Timer1_Start( void )
{
  	 T1CONbits.TON = 1; //Start Timer1 
  	 
}
 


void Timer1_Stop( void )
{
    T1CONbits.TON = 0; //Stop Timer1 
    
}




void Initialize_Timer1_Module( void )
{
	T1CON = 0x00; //Stops the Timer1 and reset control reg.
	T1CONbits.TCKPS =0b00; // no prescale.  
	T1CONbits.TCS=0;	// using FOSC/2 --	means 16 MHz since crystal is 8MHZ + PLL 
	PR1 = MIN_TIMER_1_RESOL; //Load the time period
	TMR1 = 0x0000; //Clear contents of the timer register
	IEC0bits.T1IE = 1; //Enable Timer1 interrupts
	IPC0bits.T1IP = 1; //Setup Timer1 interrupt for desired priority level 1
	IFS0bits.T1IF = 0; //Clear the Timer1 interrupt status flag
	T1CONbits.TON = 1; //Atart Timer1
}

WORD Counter1=0;
void __attribute__ ((interrupt,no_auto_psv)) _T1Interrupt (void)
{
  TMR1=0x0000;  //clear the contents of the timer register.
  if (Counter1++>60000)Counter1=0;	
  RunForeGroundEvents();
  TriacDebounceCntDown();
  IFS0bits.T1IF = 0;         //clear the interrupt status of Timer 1
}

void __Enable_Timer1_Interrupt(void)
{
 IEC0bits.T1IE = 1; //Enable Timer1 interrupts
}
void __Disable_Timer1_Interrupt(void)
{
 IEC0bits.T1IE = 0; //Disable Timer1 interrupts
}
WORD retCounter1(void)
{
	return Counter1;
}

