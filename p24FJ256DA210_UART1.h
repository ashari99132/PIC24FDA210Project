#ifndef __P24FJ256DA210_UART1_H
#define __P24FJ256DA210_UART1_H

//used when BRGH = 1 
#define BAUD_HISPEED_4800	833
#define BAUD_HISPEED_9600	416
#define BAUD_HISPEED_19200	207
#define BAUD_HISPEED_38400	103
#define BAUD_HISPEED_115200	34
//used when BRGH = 0 
#define BAUD_LOSPEED_2400	416
#define BAUD_LOSPEED_4800	207
#define BAUD_LOSPEED_9600	103
#define BAUD_LOSPEED_19200	52
#define BAUD_LOSPEED_38400	25
#define BAUD_LOSPEED_115200 8

#define MAX_U1RXBUFFER		20

void Initialize_UART1_Module (void);
void U4_Chip_TxEnable (void);
void U4_Chip_RxEnable (void);
void UART1_TxByte(char Data);
void UART1_TxString(char *String);
void UART1_TxData(BYTE *Data, BYTE dataLength);
void __attribute__ ((interrupt,no_auto_psv)) _U1RXInterrupt  (void);
void Flush_U1RxBuffer(void);
BYTE *Return_U1RxBuffer (void);
BYTE Return_U1RxBufferCounter (void);
void Delay_UART1 (LONG Delay);
#endif

