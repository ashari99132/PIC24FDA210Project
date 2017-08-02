#ifndef __OMBLTC2439_INPUTS_H
#define __OMBLTC2439_INPUTS_H


#define MAX_ADC_BUFF  				3
//---sensor error flag ----
#define FLAG_PT100_ERROR			0x0001
#define FLAG_NTC_ERROR				0x0002
#define FLAG_IRCO2_ERROR			0x0004
#define FLAG_TCCO2_ERROR			0x0008
#define FLAG_OPT2_CHANNEL_ERROR		0x0010						//OPT2 used for RH
#define FLAG_OPT1_CHANNEL_ERROR		0x0020						//OPT1 used for O2
#define FLAG_OPT3_CHANNEL_ERROR		0x0040
#define FLAG_BATT_CHANNEL_ERROR		0x0080
#define FLAG_O2RS485_PUMP_ERROR			 0x0100
#define FLAG_O2RS485_HEATER_VOLT_ERROR	 0x0200
#define FLAG_O2RS485_ASSYMETRY_WARNING	 0x0400
#define FLAG_O2_BELOW_PT1_WARNING 	 0x0800
#define FLAG_O2RS485_SELF_SHUTDOWN 	 0x1000
#define FLAG_O2RS485_ERROR               0x2000



//----ADC sensor error limit---------
#define ADC_LOW_LIMIT				10

//---Default values ----------------
#define PT100_DEFAULT_SLOPE			38.5	    // ohm/oC x100	
#define PT100_DEFAULT_OFFSET		10000	// ohm  x 100
#define PT100_DEFAULT_RMIN			113		//ohm
#define PT100_DEFAULT_ADCMIN		15846
#define PT100_DEFAULT_RNOM			115		//ohm	
#define PT100_DEFAULT_ADCNOM		16305

#define NTC_DEFAULT_RMIN		3892//5000		//ohm
#define NTC_DEFAULT_ADCMIN		18289//21845
#define NTC_DEFAULT_RNOM		10000		//ohm	
#define NTC_DEFAULT_ADCNOM		32767

#define DEFAULT_IRCO2_SLOPE     250			//0-5000mV ~  0-20% CO2
#define DEFAULT_IRCO2_OFFSET	0        


#define DEFAULT_RH_SLOPE		50			//0-5000mV ~  0-100% RH
#define DEFAULT_RH_OFFSET		0


#define DEFAULT_O2_SLOPE			250			//0-5000mV ~  0-20% O2
#define DEFAULT_O2_OFFSET		0

#define DEFAULT_TC0				2000
#define DEFAULT_TC5				2200
#define DEFAULT_TC15			2800	

#define DEFAULT_DAC_SLOPE		1			//0-5000mV ~ 0-5000mV
#define DEFAULT_DAC_OFFSET		0	

#define LOW_VOLT_CALIB            500		//0.5V
#define NOM_VOLT_CALIB            5000		//5V	
//-----moving average window----
#define MOVING_AVERAGE_DEFAULT		5		

//----extern variables-------------
extern WORD LOW_VOLT_CAL; 
extern WORD HIGH_VOLT_CAL;  	

extern WORD Moving_Avg_Window; //Moving average window value;
extern WORD Tcv; 	//temperature current value from PT100
extern WORD Tamb;	//ambient temperature valuer from NTC
extern WORD CO2cv;  //CO2 current value
extern WORD IRCO2cv;
extern WORD O2cv;   //O2 current value
extern WORD RHcv;	//RH current value

extern WORD Vpt100; //Voltage from PT100 channel
extern WORD Vpt100_ADCmin;	//ADC min value for analog channel calibration of Pt100
extern WORD Vpt100_ADCnom;	//ADC nom value for analog channel calibration of Pt100
extern WORD ADCpt100; 

extern WORD Vntc;   //Voltage from ntc channel
extern WORD Vntc_ADCmin;	//ADC min value for analog channel calibration of Pt100
extern WORD Vntc_ADCnom;	//ADC nom value for analog channel calibration of Pt100
extern WORD ADCntc;

extern WORD Vtc;	//Voltage from TCCO2 sensor channel
extern WORD Vtc_ADCmin;	//ADC min value for analog channel calibration of Pt100
extern WORD Vtc_ADCnom;	//ADC nom value for analog channel calibration of Pt100
extern WORD ADCtc;

extern WORD Vvsl;   //Voltage from CO2 vaisala
extern WORD Vvsl_ADCmin;	//ADC min value for analog channel calibration of Pt100
extern WORD Vvsl_ADCnom;	//ADC nom value for analog channel calibration of Pt100
extern WORD ADCvsl;

extern WORD Vbat;	//Voltage battery value
extern WORD Vbat_ADCmin;	//ADC min value for analog channel calibration of Pt100
extern WORD Vbat_ADCnom;	//ADC nom value for analog channel calibration of Pt100

extern WORD Vopt1;	//Voltage from optional channel 1
extern WORD Vopt1_ADCmin;	//ADC min value for analog channel calibration of Pt100
extern WORD Vopt1_ADCnom;	//ADC nom value for analog channel calibration of Pt100
extern WORD ADCopt1;

extern WORD Vopt2;  //Voltage from optional channel 2
extern WORD Vopt2_ADCmin;	//ADC min value for analog channel calibration of Pt100
extern WORD Vopt2_ADCnom;	//ADC nom value for analog channel calibration of Pt100
extern WORD ADCopt2;

extern WORD Vopt3;  //Voltage from optional channel 3
extern WORD Vopt3_ADCmin;	//ADC min value for analog channel calibration of Pt100
extern WORD Vopt3_ADCnom;	//ADC nom value for analog channel calibration of Pt100

extern WORD Vxtr;	//Voltage from XTR calib channel
extern WORD Vdac;	//voltage from DAC calib channel
extern WORD V2500vref; //voltage from 5 v reference channel

extern WORD PT100_Slope; 	//slope for PT100
extern WORD PT100_Offset;	//offset for PT100
extern WORD TC_0;			//constant 0% for TCCO2;
extern WORD TC_5;			//constant 5% for TCCO2;
extern WORD TC_15;			//constant 15% for TCCO2;
extern WORD IRCO2_Slope;	//slope for IRCO2
extern WORD IRCO2_Offset;	//offset for IRCO2
extern WORD IRCO2_Min;	//slope for IRCO2
extern WORD IRCO2_Nom;	//offset for IRCO2

extern WORD Analog_Slope; 	//slope for multichannel analog self calibration
extern WORD Analog_Offset;	//offset for multichannel analog self calibration 

extern WORD Rpt100; //Resistance from PT100 channel in ohm
extern const WORD Rpt100_Rmin;//Min Resistance for calibration;
extern const WORD Rpt100_Rnom;//Nom Resistance for calibration
extern const WORD Rpt100_ADCmin;	//ADC min value for analog channel calibration of Pt100
extern const WORD Rpt100_ADCnom;	//ADC nom value for analog channel calibration of Pt100
extern WORD ADCpt100; 		//Raw ADC value of this channel

extern WORD Rntc;   //Resistance from ntc channel in ohm
extern WORD Rntc_Rmin; //Resistance min from ntc channel for calibration
extern WORD Rntc_Rnom;	//Resistance rnom from ntc channel for calibration
extern WORD Rntc_ADCmin;	//ADC min value for analog channel calibration of NTC
extern WORD Rntc_ADCnom;	//ADC nom value for analog channel calibration of NTC
extern WORD ADCntc; 		//Raw ADC value of this channel

extern WORD PT100_Tmin; 	//slope for PT100 sensor  in ohm/oC
extern WORD PT100_Tnom;	//offset for PT100 sensor in ohm

extern WORD O2_Slope;		//slope for O2 sensor   in mV/%O2
extern WORD O2_Offset;		//offset for O2 sensor  in mV
extern WORD RH_Slope;		//slope for RH sensor   in mV/%RH
extern WORD RH_Offset;		//slope for RH offset   in mV
extern WORD O2_Min;
extern WORD O2_Nom;
extern WORD RH_Min;	
extern WORD RH_Nom;	
extern float ActualTcv;
extern float ActualTcvNTC;
//---------function declarations------------
void EventSelfCalibLTC2439AIN(void);	//self calibration, ONCE
void EventUpdate_PT100channel(void);	//PERIODIC
void EventUpdate_NTCchannel(void);		//PERIODIC
void EventUpdate_TCCO2channel(void);	//PERIODIC
void EventUpdate_IRCO2channel(void);	//PERIODIC
void EventUpdate_Battchannel(void);		//PERIODIC
void EventUpdate_RHchannel(void);		//PERIODIC
void EventUpdate_Opt2channel(void);		//PERIODIC
void EventUpdate_Opt3channel(void);		//PERIODIC
float GetValue_Slope(WORD slope, WORD offset, WORD ADC);	// getting the value from the known slope and offset
float GetValue_2points(WORD y1, WORD y2, WORD x1, WORD x2, WORD ADC);			// getting the value from the known 2 points.	
float GetTCCO2(WORD ADC);						// getting the TC value from CO2 parameters
float GetIRCO2(WORD ADC);						// getting the IRCO2 value from the CO2 parameters.
float GetNTCtemp(WORD ADC);							// getting the Temperature from resistance value of NTC
float GetPT100temp(WORD ADC);						// getting the Temperature from resistance value of PT100 
float GetO2(WORD ADC);
float GetRH(WORD ADC);	
float NTCLookUpTable(WORD Resistance);
float PT100LookUpTable(WORD Resistance);
#endif
