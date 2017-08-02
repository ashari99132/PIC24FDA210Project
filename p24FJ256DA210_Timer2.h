#ifndef __P24FJ256DA210_TIMER2_H
#define __P24FJ256DA210_TIMER2_H



#define MIN_TIMER_2_RESOL  62500 //to get 1 second timer

void Timer2_Start( void );
void Timer2_Stop( void );
void Initialize_Timer2_Module( void );
void __attribute__ ((interrupt,no_auto_psv)) _T2Interrupt (void);


#endif
