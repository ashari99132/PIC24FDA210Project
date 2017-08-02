#ifndef __OMB_UTI_COMM_H
#define __OMB_UTI_COMM_H

#define OMB_ADDR_BRD		OMB_I2C1_ADD<<1
#define READ_CMD_BYTELENGTH	7
#define WORD_WRITE_CMD_BYTELENGTH	8
#define MAX_NUMBER_OF_CLSREGISTER  81
enum Cls_RegAddress{
	OMB_SOFTWARE_VER,		   //  0
	TCV,		  //  1
	RPT100, 		 //  2
	ADCPT100,		   //  3
	TNTC,		  //  4
	RNTC,		   //  5
	ADCNTC, 		 //  6
	CO2CV,			//	7
	VTC,		  //  8
	ADCTC , 		 //  9
	RHCV,		   //  10
	VOPT2,			//	11
	ADCOPT2,		  //  12
	O2CV,		   //  13
	VOPT1,			//	14
	ADCOPT1,		  //  15
	OMB_OUTPUTS,		  //  16
	OMB_SWITCHES_STATUS,		  //  17
	OMB_ALARM_STATUS,		   //  18
	OMB_SENSOR_STATUS,			//	19
	TSP,		  //  20
	TCV_OFFSET, 		 //  21
	TSP_HA, 		 //  22
	TSP_LA, 		 //  23
	TSP_DA, 		 //  24
	T_PNUM, 		 //  25
	T_PDNUM,		  //  26
	T_INUM, 		 //  27
	T_IDNUM,		  //  28
	RPT100_RMIN,		  //  29
	RPT100_RNOM,		  //  30
	RPT100_ADCMIN,			//	31
	RPT100_ADCNOM,			//	32
	CO2CV_OFFSET,		   //  33
	IRCO2_SLOPE,		  //  34
	IRCO2_OFFSET,		   //  35
	CO2SP,			//	36
	CO2_HA, 		 //  37
	CO2_LA, 		 //  38
	CO2_PNUM,		   //  39
	CO2_PDNUM,			//	40
	CO2_INUM,		   //  41
	CO2_IDNUM,			//	42
	NTC_RMIN, 		 //  43
	NTC_RNOM, 		 //  44
	NTC_ADCMIN,		   //  45
	NTC_ADCNOM,		   //  46
	NTC_SP,			//	47
	RHCV_OFFSET,		  //  48
	RHSP,		   //  49
	RH_HA,			//	50
	RH_LA,			//	51
	RH_PNUM,		  //  52
	RH_PDNUM,		   //  53
	RH_INUM,		  //  54
	RH_IDNUM,		   //  55
	VOPT2_ADCMIN,		   //  56
	VOPT2_ADCNOM,		   //  57
	RH_SLOPE,		   //  58
	RH_OFFSET,			//	59
	O2CV_OFFSET,		  //  60
	O2SP,		   //  61
	O2_HA,			//	62
	O2_LA,			//	63
	O2_PNUM,		  //  64
	O2_PDNUM,		   //  65
	O2_INUM,		  //  66
	O2_IDNUM,		   //  67
	VOPT1_ADCMIN,		   //  68
	VOPT1_ADCNOM,		   //  69
	O2_SLOPE,		   //  70
	O2_OFFSET,			//	71
	UV_RUNTIMER,		  //  72
	OMB_ALRELAY,		  //  73
	OMB_MODE,		   //  74
	OMB_OPT,		  //  75
	BASE_HTR_PR,		  //  76
	DOOR_HTR_PR,		  //  77
	DECON_HTR_PR,		   //  78
	IP_ADDR_LO_W,		//79	
	IP_ADDR_HI_W		//80
};


#define WORD_RAM	   0x01
#define WORD_EEPROM	   0x02


#define R_REG	   0x01
#define RW_REG	   0x02

#define READ_FUNC  0x03
#define WRITE_FUNC 0x06
#define NO_EEPROM_ADDR	0xFFFF		

typedef struct ModBusRegisters{
	WORD *RegData;
	BYTE RegType;
	BYTE RegRW;
	WORD EEPROM_Address; 
}REGISTER,*pREGISTER;


typedef struct DataFrame{
	
	BYTE Command;
	WORD RegAddress; 				//is board address
	BYTE dataLength;			//data length of frame received
	BYTE Data[4];   // is the data value or number of register. 
	BYTE Crc[2];	//crc for the data
}RXFRAME,*pRXFRAME;
extern const REGISTER CLSRegister[MAX_NUMBER_OF_CLSREGISTER];

BYTE Is_I2C1_FrameData_Valid(void);
void EventUpdateUTI_Communication(void);
void Process_I2C1_FrameData(void);
void Process_I2C1_ReadFunction(void);
void Process_I2C1_WriteFunction(void);
void SendException_ReadFunction(void);
void SendException_WriteFunction(void);
void CompileRxBufferToFrame(void);
void ReadShakerRegisterFromEEPROM(void);
void Flush_I2C1FrameBuff(void);
void Event_Int_I2C_Write_Reg(void);

#endif
