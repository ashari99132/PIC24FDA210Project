/**
p24FJ256DA210_Timer2.c


**/
// local includes
#include "HardwareProfile.h"
#include "ApplicationDrivers.h"
#include "p24FJ256DA210_Timer2.h"



void Timer2_Start( void )
{
  	 T2CONbits.TON = 1; //Start Timer2 
}
 


void Timer2_Stop( void )
{
    T2CONbits.TON = 0; //Stop Timer2 
}




void Initialize_Timer2_Module( void )
{
	T2CON = 0x00; //Stops the Timer2 and reset control reg.
	T2CONbits.T32=0;		// use 16bit timer
	T2CONbits.TCKPS =0b11; // 1:256 
	T2CONbits.TCS=0;	// using FOSC/2 --	means 16 MHz since crystal is 8MHZ+PLL. 
	PR2 = (WORD)MIN_TIMER_2_RESOL; 		//lsw of time period
	//PR3 = (WORD)(MIN_TIMER_2_RESOL>>16);    //mws of time period
	TMR2 = 0x0000; //Clear contents of the timer register
	IEC0bits.T2IE = 1; //Enable Timer2 interrupts
	IPC1bits.T2IP = 0b001; //Setup Timer2 interrupt for desired priority level 
	IFS0bits.T2IF = 0; //Clear the Timer2 interrupt status flag
	T2CONbits.TON = 1; //Start Timer2 
}


void __attribute__ ((interrupt,no_auto_psv)) _T2Interrupt (void)
{
  TMR2=0x0000;  //clear the contents of the timer register.
  EventIntRTC();
  IFS0bits.T2IF = 0;         //clear the interrupt status of Timer 1  
}
