/**
EventBuzzer.c
**/
#include "ApplicationDrivers.h"
#include "EventBuzzer.h"

BYTE BuzFlag=0;
void EventUpdateBuzzer (void)
{
  BuzFlag^=1;
//  if (BuzFlag)SetOutPut(BUZZER,ON);
//  else SetOutPut(BUZZER,OFF);
//  UART1_TxString("Event buzzer is on off on off");
}
