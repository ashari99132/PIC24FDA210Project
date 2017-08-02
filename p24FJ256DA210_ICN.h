#ifndef __P24FJ256DA210_ICN_H
#define __P24FJ256DA210_ICN_H

extern BYTE RTC_Flag;
//extern AC_Detect_Flag;

void Initialize_ICN_Module (void);
void __attribute__((interrupt,no_auto_psv)) _CNInterrupt(void);
void __Enable_CN_Interrupt(void);
void __Disable_CN_Interrupt(void);
#endif

