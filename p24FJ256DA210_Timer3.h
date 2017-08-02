#ifndef __P24FJ256DA210_TIMER3_H
#define __P24FJ256DA210_TIMER3_H



#define MIN_TIMER_3_RESOL  62500   // to get 1s timer. 

void Timer3_Start( void );
void Timer3_Stop( void );
void Initialize_Timer3_Module( void );
void Initialize_Timer4_Module( void );
void __attribute__ ((interrupt,no_auto_psv)) _T3Interrupt (void);
#endif
