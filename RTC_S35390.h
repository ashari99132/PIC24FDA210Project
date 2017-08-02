#ifndef __RTC_S35390A_H
#define __RTC_S35390A_H
//
//extern WORD YearBuffer;
//extern BYTE MonthBuffer;
//extern BYTE DayBuffer;
//extern BYTE HourBuffer;
//extern BYTE MinuteBuffer;
//extern BYTE SecondsBuffer;
//
#define RTC_ADDRESS  0x60
#define MAX_RTC_BUFF 7
#define TO_S35390    0x01
#define FROM_S35390  0x02  

////---RTC CMD---
#define STAT1_REG	 0x00
#define STAT2_REG    0x02
#define RT1_REG	   	 0x04
#define RT2_REG      0x06
#define INT1_REG	 0x08
#define INT2_REG	 0x0A
#define CORR_REG	 0x0B
#define FREE_REG	 0x0E

//---DATA VALUE FOR STAT1_REG---
#define STAT1_POC 		0x01
#define STAT1_BLD			0x02
#define STAT1_INT2		0x04
#define STAT1_INT1 		0x08
#define STAT1_SC1			0x10
#define STAT1_SC0			0x20
#define STAT1_HRS_24		0x40	
#define STAT1_RESET		0x80

//---DATA VALUE FOR STAT2_REG---
#define PER_MINUTE_EDGE_INT2    0x04
#define MINUTE_PERIODIC_INT2    0x0C
#define ALARM2_INT2             0x02
#define OUTPUT_USER_FREQ_INT2   0x08
#define PER_MINUTE_EDGE_INT1    0x40
#define MINUTE_PERIODIC_INT1    0xC0
#define ALARM1_INT1             0x20  
#define Hz_32K_OUTPUT           0x10
#define OUTPUT_USER_FREQ_INT1   0x80

//---INTERRUPT FREQUENCY---
#define Hz_16		0x08
#define Hz_8		0x10
#define Hz_4		0x20
#define Hz_2		0x40
#define Hz_1		0x80


void s35390_Read(BYTE command, BYTE dataLength);
void s35390_Write(BYTE command,BYTE dataLength);

char S35390_ConvertRTData(char dataBuffer, char Direction);
char CompileStringTo_S35390_RT1Data(char *String);

void s35390_Initialize(void);
void s35390_GetDate_And_Time(void);
void s35390_SetTime(BYTE Hour, BYTE Minutes, BYTE Seconds);
void s35390_SetDate(WORD Year, BYTE Months, BYTE Days);
void s35390_FlushBuffer(void);
#endif

