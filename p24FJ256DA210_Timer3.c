/**
p24FJ256DA210_Timer3.c


**/
// local includes
#include "HardwareProfile.h"
#include "ApplicationDrivers.h"
#include "p24FJ256DA210_Timer3.h"



void Timer3_Start( void )
{
  	 T3CONbits.TON = 1; //Start Timer3 
}
 


void Timer3_Stop( void )
{
    T3CONbits.TON = 0; //Stop Timer3 
}




void Initialize_Timer3_Module( void )
{
	T3CON = 0x00; //Stops the Timer2 and reset control reg.
	T3CONbits.TCKPS =0b11; // 1:256 
	T3CONbits.TCS=0;	// using FOSC/2 --	means 16 MHz since crystal is 8MHZ+PLL. 
	PR3 = (WORD)MIN_TIMER_3_RESOL; 		//lsw of time period
	TMR3 = 0x0000; //Clear contents of the timer register
	IEC0bits.T3IE = 1; //Enable Timer3 interrupts
	IPC2bits.T3IP = 0b001; //Setup Timer3 interrupt for desired priority level 
	IFS0bits.T3IF = 0; //Clear the Timer3 interrupt status flag
	T3CONbits.TON = 1; //Start Timer3 
}


void __attribute__ ((interrupt,no_auto_psv)) _T3Interrupt (void)
{
  TMR3=0x0000;  //clear the contents of the timer register.
  EventIntRTC();
  IFS0bits.T3IF = 0;         //clear the interrupt status of Timer 1  
}

void Initialize_Timer4_Module( void )
{
	T4CON = 0x00; //Stops the Timer2 and reset control reg.
	T4CONbits.TCKPS =0b01; // 1:8 
	PR4=0x9C3F;
	T4CONbits.TCS=0;	// using FOSC/2 --	means 16 MHz since crystal is 8MHZ+PLL. 
	TMR4 = 0x0000; //Clear contents of the timer register
	T4CONbits.TON = 1; //Start Timer2
	 
}


