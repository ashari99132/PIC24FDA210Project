#ifndef __VOYAGER_H
#define __VOYAGER_H


#define MIN_VOYAGER_RXDATA	5
#define MAX_VOYAGER_POLL	3
#define MAX_VOYAGER_TXDATA    20
#define MAX_VOYAGER_RXDATA    10

void EventVoyager (void);
void Process_RxVoyager_Data(void);
#endif
