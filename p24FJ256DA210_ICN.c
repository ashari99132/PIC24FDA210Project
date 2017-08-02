/**
p24FJ256DA210_ICN.c

**/
// local includes
#include "HardwareProfile.h"
#include "p24FJ256DA210_ICN.h"
#include "General.h"
BYTE RTC_Flag;
//BYTE AC_Detect_Flag;
void Initialize_ICN_Module (void)
{
	/* RF12/CN75 is RTC_INT */
	TRISFbits.TRISF12 = 1;	// make the port as input
	CNEN5bits.CN75IE=1;				//pin 40 (CN75/RF12) as RTC_INT
	
	/*RD2/CN77 is AC_DETECT_INT*/
	//TRISDbits.TRISD2 = 1;	// make the port as input
	//CNEN5bits.CN77IE=1;				//pin 77 (CN51/RD2) as AC_DETECT_INT
	
	IFS1bits.CNIF = 0;		// clear IF
	IPC4bits.CNIP = 4;		// set IP as 7
	IEC1bits.CNIE = 1;		// enable CN
}

void __attribute__((interrupt,no_auto_psv)) _CNInterrupt(void)
{
	if(PORTFbits.RF12)
		{
		 RTC_Flag=1;
		}
		
	
	IFS1bits.CNIF = 0;		// clear IF
}

void __Enable_CN_Interrupt(void)
{
	IEC1bits.CNIE = 1;		
	
}
void __Disable_CN_Interrupt(void)
{
   IEC1bits.CNIE = 0;		
}
