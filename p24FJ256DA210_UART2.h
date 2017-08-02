#ifndef __P24FJ256DA210_UART2_H
#define __P24FJ256DA210_UART2_H

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
#define BAUD_LOSPEED_38400	25
#define BAUD_LOSPEED_115200 8
#define MAX_U2RXBUFFER		30



void Initialize_UART2_Module (void);
void U5_Chip_TxEnable (void);
void U5_Chip_RxEnable (void);
void UART2_TxByte(char Data);
BYTE UART2_PollByte(void);
void UART2_TxString(char *String);
void __attribute__ ((interrupt,no_auto_psv)) _U2RXInterrupt  (void);
void Delay_UART2(LONG Delay);
void UART2_TxData(BYTE *Data, BYTE dataLength);
void Flush_U2RxBuffer(void);
BYTE *Return_U2RxBuffer (void);
void OpenUART2 (void);
void CloseUART2(void);

BYTE Return_U2RxBufferCounter (void);
#endif

