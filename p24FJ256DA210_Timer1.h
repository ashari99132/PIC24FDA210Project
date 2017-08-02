#ifndef __P24FJ256DA210_TIMER1_H
#define __P24FJ256DA210_TIMER1_H

#define MIN_TIMER_1_RESOL  16000//4000   // to get 5ms timer. 

extern BYTE T1_Flag;
void Timer1_Start( void );
void Timer1_Stop( void );
void Initialize_Timer1_Module( void );
void __attribute__ ((interrupt,no_auto_psv)) _T1Interrupt (void);
void __Enable_Timer1_Interrupt(void);
void __Disable_Timer1_Interrupt(void);
WORD retCounter1(void);


#endif
