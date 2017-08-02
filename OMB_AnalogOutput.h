#ifndef __OMB_ANALOGOUTPUT_H
#define __OMB_ANALOGOUTPUT_H


typedef struct tagAD5644R{
		 BYTE CMD;
		 BYTE DAC_ADDRES;         
		 WORD Data;
		 BYTE DB_01;
} FRAMEAD5644R;




//----AD5644R Command definition----
#define WR_INPUT_REGn  				0b000
#define UPDATE_DAC_REGn 			0b001
#define WR_INPUT_REGn_UPDATE_ALL	0b010
#define WR_UPDATE_DAC				0b011
#define PWR_DOWN_DAC				0b100
#define RST_DAC						0b101
#define LDAC_REG_SETUP				0b110
#define INTERNAL_SETUP_ON			0b111

//----ADDRESS_CMMD------
#define DAC_A			0b000
#define DAC_B			0b001
#define DAC_C			0b010
#define DAC_D			0b011
#define ALL_DAC			0b111

extern FRAMEAD5644R Data_DAC;
void CalibrateAnalogOut (void);
void InitializeAnalogOut(void);
void CompileDAC_Data(BYTE channel, BYTE cmmd, WORD Data);
void UpdateDAC(BYTE channel, float voltage);
void TxSPIData_DAC(void);
BYTE LsbToMsb(BYTE Data);
void Update_RawDAC(BYTE channel, WORD DAC_data);





#endif

