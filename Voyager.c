/**
Voyager.c
**/
#include "ApplicationDrivers.h"
#include "Voyager.h"

BYTE Voyager_PollCnt=0;
BYTE VoyagerRxData[MAX_VOYAGER_RXDATA];
BYTE VoyagerTxData[MAX_VOYAGER_TXDATA];
void EventVoyager (void)
{
		
		if(Return_U1RxBufferCounter()<MIN_VOYAGER_RXDATA)
			{
				if(Voyager_PollCnt<MAX_VOYAGER_POLL)Voyager_PollCnt++;
				else {
						Voyager_PollCnt=0;
						Flush_U1RxBuffer();
					}	
			}
		else Process_RxVoyager_Data();
	
}
	



void Process_RxVoyager_Data(void)
{
  //just try to echo for testing
  
  BYTE *pU1RxBuffer;
  BYTE c;
  BYTE datalength=Return_U1RxBufferCounter();
  pU1RxBuffer=Return_U1RxBuffer();
  for(c=0;c<datalength;c++)
  {
  	VoyagerRxData[c]=*(pU1RxBuffer+c);
  }
  Flush_U1RxBuffer();
  UART1_TxData(&VoyagerRxData[0],datalength);
  UART1_TxString("Voyager sending data bytes");
   
}
