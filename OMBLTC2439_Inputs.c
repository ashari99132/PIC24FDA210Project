/**
OMBLTC2439_Inputs.c
**/
#include "ApplicationDrivers.h"
#include "OMBLTC2439_Inputs.h"

WORD Moving_Avg_Window=MOVING_AVERAGE_DEFAULT; //Moving average window value;

WORD Rpt100; //Resistance from PT100 channel in ohm
const WORD Rpt100_Rmin;//Min Resistance for calibration;
const WORD Rpt100_Rnom;//Nom Resistance for calibration
const WORD Rpt100_ADCmin;	//ADC min value for analog channel calibration of Pt100
const WORD Rpt100_ADCnom;	//ADC nom value for analog channel calibration of Pt100
WORD ADCpt100; 		//Raw ADC value of this channel
WORD Tcv=3700; 	//temperature current value from PT100
BYTE n_Tcv=0;	//counter for averaging
double Tcv_total; //total temperature


WORD Rntc;   //Resistance from ntc channel in ohm
WORD Rntc_Rmin=NTC_DEFAULT_RMIN; //Resistance min from ntc channel for calibration
WORD Rntc_Rnom=NTC_DEFAULT_RNOM;	//Resistance rnom from ntc channel for calibration
WORD Rntc_ADCmin=NTC_DEFAULT_ADCMIN;	//ADC min value for analog channel calibration of NTC
WORD Rntc_ADCnom=NTC_DEFAULT_ADCNOM;	//ADC nom value for analog channel calibration of NTC
WORD ADCntc; 		//Raw ADC value of this channel
WORD Tamb=2400;	//ambient temperature valuer from NTC
BYTE n_Tamb=0;	//counter for averaging
double Tamb_total; //total temperature
float Tamb_avg; //average Tamb in float

WORD Vtc;	//Voltage from TCCO2 sensor channel in mV
WORD Vtc_ADCmin=0;	//ADC min value for analog channel calibration of TCCO2
WORD Vtc_ADCnom=0;	//ADC nom value for analog channel calibration of TCCO2
WORD ADCtc; 		//Raw ADC value of this channel
WORD CO2cv;  //TCCO2 current value
BYTE n_CO2cv=0;	//counter for averaging
double CO2cv_total; //total temperature
float CO2cv_avg; //average CO2cv in float

WORD Vvsl;   //Voltage from CO2 vaisala in mV
WORD Vvsl_ADCmin=0;	//ADC min value for analog channel calibration of Vaisala IR CO2
WORD Vvsl_ADCnom=0;	//ADC nom value for analog channel calibration of Vaisala IR CO2
WORD ADCvsl; 		//Raw ADC value of this channel
WORD IRCO2cv;  //IRCO2 current value
BYTE n_IRCO2cv=0;	//counter for averaging
double IRCO2cv_total; //total temperature
float IRCO2cv_avg; //average CO2cv in float


WORD Vbat;	//Voltage battery value in mV
WORD Vbat_ADCmin=0;	//ADC min value for analog channel calibration of battery
WORD Vbat_ADCnom=0;	//ADC nom value for analog channel calibration of battery
WORD ADCbat; 		//Raw ADC value of this channel
BYTE n_batt=0;	//counter for averaging
double batt_total; //total temperature
float batt_avg; //average CO2cv in float

WORD Vopt1;	//Voltage from optional channel 1 in mV
WORD Vopt1_ADCmin=0;	//ADC min value for analog channel calibration of optional channel 1
WORD Vopt1_ADCnom=0;	//ADC nom value for analog channel calibration of optional channel 1
WORD ADCopt1; 		//Raw ADC value of this channel
WORD O2cv;   //O2 current value
BYTE n_O2cv=0;	//counter for averaging
double O2cv_total; //total temperature
float O2cv_avg; //average O2cv in float

WORD Vopt2;  //Voltage from optional channel 2 in mV
WORD Vopt2_ADCmin=0;	//ADC min value for analog channel calibration of optional channel 2
WORD Vopt2_ADCnom=0;	//ADC nom value for analog channel calibration of optional channel 2
WORD ADCopt2; 		//Raw ADC value of this channel
WORD RHcv;	//RH current value
BYTE n_RHcv=0;	//counter for averaging
double RHcv_total; //total temperature
float RHcv_avg; //average RHcv in float


WORD Vopt3;  //Voltage from optional channel 3 in mV
WORD Vopt3_ADCmin=0;	//ADC min value for analog channel calibration of optional channel 3
WORD Vopt3_ADCnom=0;	//ADC nom value for analog channel calibration of optional channel 3
WORD ADCopt3; 		//Raw ADC value of this channel
BYTE n_Vopt3=0;	//counter for averaging
double Vopt3_total; //total temperature
float Vopt3_avg; //average CO2cv in float

WORD Vxtr;	//Voltage from XTR calib channel
WORD ADCxtr; 		//Raw ADC value of this channel

WORD Vdac;	//voltage from DAC calib channel
WORD ADCdac; 		//Raw ADC value of this channel

WORD LOW_VOLT_CAL=100;  //100 mv	
WORD HIGH_VOLT_CAL=2500;  //2500 mv	
WORD ADC2500vref; 		//Raw ADC value of this channel
WORD ADC0vref; 		//voltage from 0V reference channel;

WORD PT100_Tmin=PT100_DEFAULT_SLOPE; 	//slope for PT100 sensor  in ohm/oC
WORD PT100_Tnom=PT100_DEFAULT_OFFSET;	//offset for PT100 sensor in ohm

WORD O2_Slope=DEFAULT_O2_SLOPE;		//slope for O2 sensor   in mV/%O2
WORD O2_Offset=DEFAULT_O2_OFFSET;		//offset for O2 sensor  in mV
WORD RH_Slope=DEFAULT_RH_SLOPE;		//slope for RH sensor   in mV/%RH

WORD RH_Offset=DEFAULT_RH_OFFSET;		//slope for RH offset   in mV

WORD TC_0=DEFAULT_TC0;			//constant 0% for TCCO2 in mV;
WORD TC_5=DEFAULT_TC5;			//constant 5% for TCCO2 in mV;
WORD TC_15=DEFAULT_TC15;			//constant 15% for TCCO2 in mV;

WORD IRCO2_Slope=DEFAULT_IRCO2_SLOPE;	//slope for IRCO2 in mv/%CO2
WORD IRCO2_Offset=DEFAULT_IRCO2_OFFSET;	//offset for IRCO2 in mV
WORD Analog_Slope=DEFAULT_DAC_SLOPE; 	//slope for multichannel analog self calibration
WORD Analog_Offset=DEFAULT_DAC_OFFSET;	//offset for multichannel analog self calibration 
float ActualTcv;
float ActualTcvNTC;
void EventSelfCalibLTC2439AIN(void)	
{

BYTE c;	
 //read the ADC values from SPI channel 15 for 5VREF 
 for (c=0;c<10;c++)
 	{
 		ADC2500vref=Read_SingleEndedLTC2439(CH15);
		 Delay_uS(1000);
 	}

 //read the ADC values from SPI channel 14 for 0VREF 
 
 for (c=0;c<10;c++)
 	{
		 ADC0vref=Read_SingleEndedLTC2439(CH14);
		 Delay_uS(1000);
 	} 
 LOW_VOLT_CAL=0;
 HIGH_VOLT_CAL=2500;  //2500 mV
 Vtc_ADCmin=ADC0vref;
Vtc_ADCnom=ADC2500vref;
// Vvsl_ADCmin=ADC0vref;
// Vvsl_ADCnom=ADC2500vref;
 Vbat_ADCmin=ADC0vref;
 Vbat_ADCnom=ADC2500vref;
 Vopt1_ADCmin=ADC0vref;
 Vopt1_ADCnom=ADC2500vref;
// Vopt2_ADCmin=ADC0vref;
// Vopt2_ADCnom=ADC2500vref;
 Vopt3_ADCmin=ADC0vref;
 Vopt3_ADCnom=ADC2500vref;
}
void EventUpdate_PT100channel(void)
{
 BYTE c;
 WORD SensorStatus=ReturnFlag(OMB_SENSOR_STATUS_FLAG);
 SensorStatus&=~FLAG_PT100_ERROR;
 //read the ADC values from SPI channel 0
 
 
 ADCpt100=Read_SingleEndedLTC2439(CH0);

 //check the error values of this channel
 if(ADCpt100<ADC_LOW_LIMIT)
  SensorStatus|=FLAG_PT100_ERROR;
 SetFlag(OMB_SENSOR_STATUS_FLAG,SensorStatus);
 
  //moving average of the value get 
 if(n_Tcv>=Moving_Avg_Window)
 {
  n_Tcv=Moving_Avg_Window;
  Tcv_total-=ActualTcv;
 }
 Tcv_total+=GetPT100temp(ADCpt100);
 ActualTcv=Tcv_total/(float)Moving_Avg_Window;
 if(ActualTcv<=0.0)
 {
  SensorStatus|=FLAG_PT100_ERROR;
  SetFlag(OMB_SENSOR_STATUS_FLAG,SensorStatus);
  ActualTcv=0.0;
 }
 Tcv=(WORD)(ActualTcv* 100);
 n_Tcv++; 
 
  UpdateDAC(DAC_A,(ActualTcv/20.0));
 }

void EventUpdate_NTCchannel(void)
{
 WORD SensorStatus=ReturnFlag(OMB_SENSOR_STATUS_FLAG);
 SensorStatus&=~FLAG_NTC_ERROR;	
 //read the ADC values from SPI channel 1
 ADCntc=Read_SingleEndedLTC2439(CH1);
 
 //check the error values of this channel
 if(ADCntc<ADC_LOW_LIMIT)
  SensorStatus|=FLAG_NTC_ERROR;
 SetFlag(OMB_SENSOR_STATUS_FLAG,SensorStatus);
 
 //moving average of the value get 
  if(n_Tamb>=Moving_Avg_Window)
 {
  n_Tamb=Moving_Avg_Window;
  Tamb_total-=Tamb_avg;
 }
 ActualTcvNTC=GetNTCtemp(ADCntc);
 Tamb_total+=ActualTcvNTC;
 Tamb_avg=Tamb_total/(float)Moving_Avg_Window;
 Tamb=(WORD)(Tamb_avg * 100);
 n_Tamb++; 
}
void EventUpdate_TCCO2channel(void)
{
 WORD SensorStatus=ReturnFlag(OMB_SENSOR_STATUS_FLAG);
 SensorStatus&=~FLAG_TCCO2_ERROR; 	
 //read the ADC values from SPI channel
 ADCtc=Read_SingleEndedLTC2439(CH2);
 
 //check the error values of this channel
 if(ADCtc<ADC_LOW_LIMIT)
  SensorStatus|=FLAG_TCCO2_ERROR;
 SetFlag(OMB_SENSOR_STATUS_FLAG,SensorStatus);
 
 //moving average of the value get 
  if(n_CO2cv>=Moving_Avg_Window)
 {
  n_CO2cv=Moving_Avg_Window;
  CO2cv_total-=CO2cv_avg;
 }
 CO2cv_total+=GetTCCO2(ADCtc);
 CO2cv_avg=CO2cv_total/(float)Moving_Avg_Window;
 CO2cv=(WORD)(CO2cv_avg * 100);
 n_CO2cv++; 
}
void EventUpdate_IRCO2channel(void)
{
 WORD SensorStatus=ReturnFlag(OMB_SENSOR_STATUS_FLAG);
 SensorStatus&=~FLAG_IRCO2_ERROR;	
 //read the ADC values from SPI channel
 ADCvsl=Read_SingleEndedLTC2439(CH3);
 
 //check the error values of this channel
 if(ADCvsl<ADC_LOW_LIMIT)
  SensorStatus|=FLAG_IRCO2_ERROR;
 SetFlag(OMB_SENSOR_STATUS_FLAG,SensorStatus);
  
 //moving average of the value get 
  if(n_IRCO2cv>=Moving_Avg_Window)
 {
  n_IRCO2cv=Moving_Avg_Window;
  IRCO2cv_total-=IRCO2cv_avg;
 }
 IRCO2cv_total+=GetIRCO2(ADCvsl);
 IRCO2cv_avg=IRCO2cv_total/(float)Moving_Avg_Window;
 IRCO2cv=(WORD)(IRCO2cv_avg * 100);
 n_IRCO2cv++;  	
 UpdateDAC(DAC_B,((IRCO2cv/2000.0)*5.0));
}
void EventUpdate_Battchannel(void)
{
 WORD SensorStatus=ReturnFlag(OMB_SENSOR_STATUS_FLAG);
 SensorStatus&=~FLAG_BATT_CHANNEL_ERROR;	
 //read the ADC values from SPI channel
 ADCbat=Read_SingleEndedLTC2439(CH4);
 
 //check the error values of this channel
 if(ADCbat<ADC_LOW_LIMIT)
  SensorStatus|=FLAG_BATT_CHANNEL_ERROR;
 SetFlag(OMB_SENSOR_STATUS_FLAG,SensorStatus);
 
 //moving average of the value get 
  if(n_batt>=Moving_Avg_Window)
 {
  n_batt=Moving_Avg_Window;
  batt_total-=batt_avg;
 }
 batt_total+=GetValue_2points(Vbat_ADCmin,Vbat_ADCnom,LOW_VOLT_CAL, HIGH_VOLT_CAL,ADCbat);
 batt_avg=batt_total/(float)Moving_Avg_Window;
 Vbat=(WORD)(batt_avg * 100);
 n_batt++;  	
}
void EventUpdate_Opt2channel(void)
{
 WORD SensorStatus=ReturnFlag(OMB_SENSOR_STATUS_FLAG);
 SensorStatus&=~FLAG_OPT1_CHANNEL_ERROR;	
 //read the ADC values from SPI channel
 ADCopt1=Read_SingleEndedLTC2439(CH6);
 
 //check the error values of this channel
 if(ADCopt1<ADC_LOW_LIMIT)
 
 SensorStatus|=FLAG_OPT1_CHANNEL_ERROR;
 SetFlag(OMB_SENSOR_STATUS_FLAG,SensorStatus);
 
 //moving average of the value get 
  if(n_O2cv>=Moving_Avg_Window)
 {
  n_O2cv=Moving_Avg_Window;
  O2cv_total-=O2cv_avg;
 }
 O2cv_total+=GetO2(ADCopt1);
 O2cv_avg=O2cv_total/(float)Moving_Avg_Window;
 O2cv=(WORD)(O2cv_avg * 100);
 n_O2cv++;
 }
void EventUpdate_RHchannel(void)
{
BYTE c;
 WORD SensorStatus=ReturnFlag(OMB_SENSOR_STATUS_FLAG);
 SensorStatus&=~FLAG_OPT2_CHANNEL_ERROR;	
 //read the ADC values from SPI channel
 
 
  ADCopt2=Read_SingleEndedLTC2439(CH5);
 //check the error values of this channel
 if(ADCopt2<ADC_LOW_LIMIT)
  SensorStatus|=FLAG_OPT2_CHANNEL_ERROR;
 SetFlag(OMB_SENSOR_STATUS_FLAG,SensorStatus);
 
  if(n_RHcv>=Moving_Avg_Window)
 {
  n_RHcv=Moving_Avg_Window;
  RHcv_total-=RHcv_avg;
 }
 RHcv_total+=GetRH(ADCopt2);
 RHcv_avg=RHcv_total/(float)Moving_Avg_Window;
 RHcv=(WORD)(RHcv_avg * 100);
 n_RHcv++;
 UpdateDAC(DAC_C,(RHcv/2000.0));
 }
void EventUpdate_Opt3channel(void)
{
 WORD SensorStatus=ReturnFlag(OMB_SENSOR_STATUS_FLAG);
 SensorStatus&=~FLAG_OPT3_CHANNEL_ERROR;	
//read the ADC values from SPI channel
 ADCopt3=Read_SingleEndedLTC2439(CH7);
 
 //check the error values of this channel
 if(ADCopt3<ADC_LOW_LIMIT)
 
 SensorStatus|=FLAG_OPT3_CHANNEL_ERROR;
 SetFlag(OMB_SENSOR_STATUS_FLAG,SensorStatus);
 
 //moving average of the value get 
  if(n_Vopt3>=Moving_Avg_Window)
 {
  n_Vopt3=Moving_Avg_Window;
  Vopt3_total-=Vopt3_avg;
 }
 Vopt3_total+=GetValue_2points(Vopt3_ADCmin,Vopt3_ADCnom,LOW_VOLT_CAL, HIGH_VOLT_CAL, ADCopt3);
 Vopt3_avg=Vopt3_total/(float)Moving_Avg_Window;
 Vopt3=(WORD)(Vopt3_avg * 100);
 n_Vopt3++;
}
float GetValue_Slope(WORD slope, WORD offset, WORD ADC)
{
 float value;
 value=(float)(ADC-offset)/(float)slope;
 return value;
}
float GetValue_2points(WORD y1, WORD y2, WORD x1, WORD x2, WORD ADC)
{
 float m,b,x;
 m=(float)(y2-y1)/(float)(x2-x1);
 b=(float)y1-(m*x1);
 x=((float)ADC-b)/m;
 return x;
}
float GetTCCO2(WORD ADC)
{
 float TCCO2val;	
 Vtc=(WORD)GetValue_2points(Vtc_ADCmin,Vtc_ADCnom,LOW_VOLT_CAL, HIGH_VOLT_CAL,ADC);
 if(Vtc<=TC_5)
 	TCCO2val=(float)GetValue_2points(TC_0,TC_5,0,5,Vtc);
 else 
 	TCCO2val=(float)GetValue_2points(TC_5,TC_15,0,5,Vtc)+5.0;
 	
 return TCCO2val;	
}

float GetIRCO2(WORD ADC)
{
float IRCO2val;
Vvsl=(WORD)GetValue_2points(Vvsl_ADCmin,Vvsl_ADCnom,LOW_VOLT_CALIB, NOM_VOLT_CALIB,ADC);
//IRCO2val=GetValue_Slope(IRCO2_Slope,IRCO2_Offset,Vvsl);
IRCO2val=GetValue_2points(Vvsl_ADCmin,Vvsl_ADCnom,IRCO2_Slope, IRCO2_Offset,ADC);
return IRCO2val;

}

float GetNTCtemp(WORD ADC)
{
float Tval;
Rntc=(WORD)GetValue_2points(Rntc_ADCmin,Rntc_ADCnom,Rntc_Rmin, Rntc_Rnom,ADC);   
//Rntc=(WORD)GetValue_2points(NTC_DEFAULT_ADCMIN,NTC_DEFAULT_ADCNOM,NTC_DEFAULT_RMIN,NTC_DEFAULT_RNOM,ADC);		
Tval=NTCLookUpTable(Rntc);
return Tval;
}

float GetPT100temp(WORD ADC)
{
float Tval;
Rpt100=GetValue_2points(Rpt100_ADCmin,Rpt100_ADCnom,Rpt100_Rmin, Rpt100_Rnom,ADC);   
//Tval=GetValue_2points(Rpt100_Rmin*100, Rpt100_Rnom*100,PT100_Tmin,PT100_Tnom,Rpt100);
Tval=PT100LookUpTable(Rpt100);
return Tval;
}
float GetO2(WORD ADC)
{
float O2val;
Vopt1=(WORD)GetValue_2points(Vopt1_ADCmin,Vopt1_ADCnom,LOW_VOLT_CALIB, NOM_VOLT_CALIB,ADC);
//O2val=GetValue_Slope(O2_Slope,O2_Offset,Vopt1);
O2val=(WORD)GetValue_2points(Vopt1_ADCmin,Vopt1_ADCnom,O2_Slope,O2_Offset,ADC);
return O2val;
}
float GetRH(WORD ADC)
{
float RHval;
Vopt2=(WORD)GetValue_2points(Vopt2_ADCmin,Vopt2_ADCnom,LOW_VOLT_CALIB, NOM_VOLT_CALIB,ADC);
//RHval=GetValue_Slope(RH_Slope,RH_Offset,Vopt2);
RHval=GetValue_2points(Vopt2_ADCmin,Vopt2_ADCnom,RH_Slope, RH_Offset,ADC);
return RHval;
}

float NTCLookUpTable(WORD Resistance)
{
  WORD cnt=0;
  float T=0.0;
//  float a,b;
  /*
WORD NTC[81]={ 13290,
	12740,12220,11730,11250,10800,10370,9960,9569,9196,8840,
	8496,8167,7853,7553,7267,6993,6731,6481,6242,6013,
	5793,5581,5379,5185,5000,4821,4650,4487,4329,4179,
	4033,3894,3760,3631,3508,3390,3276,3167,3062,2961,
	2864,2770,2679,2593,2509,2429,2352,2277,2206,2137,
	2070,2006,1943,1884,1826,1770,1717,1665,1615,1567,
	1521,1476,1433,1391,1350,1311,1274,1237,1202,1168,
	1135,1104,1073,1043,1014,9861,9592,9331,9079,8835

};*/

WORD NTC[96]=
{27284,
26131,	25034,	23990,	22998,	22053,	21153,	20296,	19479,	18701,	17959,
17240,	16556,	15903,	15280,	14685,	14118,	13576,	13058,	12564,	12091,
11635,	11198,	10781,	10382,	10000,	9632,	9281,	8944,	8622,	8313,
8014,	7728,	7454,	7192,	6940,	6699,	6467,	6245,	6032,	5827,	
5717,	5526,	5342,	5165,	4995,	4832,	4674,	4523,	4378,	4239,
4103,	3972,	3846,	3725,	3608,	3496,	3388,	3284,	3183,	3086,
2992,	2902,	2815,	2730,	2649,	2571,	2495,	2422,	2352,	2284,
2181,	2154,	2092,	2032,	1975,	1919,	1865,	1813,	1763,	1715,
1667,	1622,	1577,	1535,	1493,	1453,	1414,	1377,	1340,	1305,
1230,	1200,	1160,	1130,	1100,
};

  //check resistance domain on look up table
while(NTC[++cnt]>Resistance && cnt <96);
if(cnt<96 && cnt>0)T=GetValue_2points(NTC[cnt-1],NTC[cnt],cnt-1,cnt,Resistance);
else if(cnt>=96)T=GetValue_2points(NTC[cnt-2],NTC[cnt-1],cnt-2,cnt-1,Resistance);
else if(cnt<=0)T=GetValue_2points(NTC[cnt],NTC[cnt+1],cnt,cnt+1,Resistance);
  
return T;
}

float PT100LookUpTable(WORD Resistance)
{
  WORD cnt=0;
  float T=0.0;
 
WORD PT100[81]={ 10000,
	10039,10078,10117,10156,10195,10234,10273,10312,10351,10390,
	10429,10468,10507,10546,10585,10624,10663,10702,10740,10779,
	10818,10857,10896,10935,10973,11012,11051,11090,11129,11167,
	11206,11245,11283,11322,11361,11400,11438,11477,11515,11554,
	11593,11631,11670,11708,11747,11786,11824,11863,11901,11940,
	11978,12017,12055,12094,12132,12171,12209,12247,12286,12324,
	12363,12401,12439,12478,12516,12554,12593,12631,12669,12708,
	12746,12784,12822,12861,12899,12937,12975,13013,13052,13090

};

  //check resistance domain on look up table
while(PT100[++cnt]<Resistance && cnt<81 );
if(cnt<81 && cnt>=0)T=GetValue_2points(PT100[cnt-1],PT100[cnt],(cnt-1),cnt,Resistance);
else  T =  (Resistance-PT100_DEFAULT_OFFSET)/PT100_DEFAULT_SLOPE;

return T;
}
/*const SLINT NTC_Lookup[TEMP_POINT_MAX_1_DEGREE_TABLE][2] = {		//added -41 to -50 degree lookup points
	{-95, 28956400},
+++++++++++++++++++++++
	{-94, 27200700},
	{-93, 25445000},
	{-92, 23689300},
	{-91, 21933600},
	{-90, 20177900},
	{-89, 18937900},
	{-88, 17697900},
	{-87, 16457900},
	{-86, 15217900},
	{-85, 13977900},
	{-84, 13128600},
	{-83, 12279300},
	{-82, 11430000},
	{-81, 10841700},
	{-80, 10256700},
	{-79, 9671700},
	{-78, 9086700},
	{-77, 8501700},
	{-76, 7916700},
	{-75, 7331700},
	{-74, 6746700},
	{-73, 6449000},
	{-72, 6130000},
	{-71, 5811000},
	{-70, 5492000},
	{-69, 5173000},
	{-68, 4854000},
	{-67, 4535000},
	{-66, 4216000},
	{-65, 3897000},
	{-64, 3578000},
	{-63, 3383300},
	{-62, 3188600},
	{-61, 2993900},
	{-60, 2799200},
	{-59, 2604500},
	{-58, 2469800},
	{-57, 2335100},
	{-56, 2200400},
	{-55, 2065700},
	{-54, 1931000},
	{-53, 1834750},
	{-52, 1738500},
	{-51, 1642250},
	{-50, 1546000},
	{-49, 1460000},
	{-48, 1379000},
	{-47, 1303000},
	{-46, 1232000},
	{-45, 1165000},
	{-44, 1103000},
	{-43, 1044000},
	{-42, 989300},
	{-41, 937600},
	{-40, 889100},
	{-39, 842400},
	{-38, 798500},
	{-37, 757200},
	{-36, 718400},
	{-35, 681900},
	{-34, 647500},
	{-33, 615100},
	{-32, 584600},
	{-31, 555800},
	{-30, 528700},
	{-29, 502600},
	{-28, 478000},
	{-27, 454800},
	{-26, 432800},
	{-25, 412100},
	{-24, 392600},
	{-23, 374100},
	{-22, 356600},
	{-21, 340100},
	{-20, 324400},
	{-19, 309300},
	{-18, 295100},
	{-17, 281600},
	{-16, 268800},
	{-15, 256600},
	{-14, 245200},
	{-13, 234300},
	{-12, 223900},
	{-11, 214100},
	{-10, 204800},
	{-9, 195900},
	{-8, 187400},
	{-7, 179300},
	{-6, 171600},
	{-5, 164300},
	{-4, 157400},
	{-3, 150800},
	{-2, 144600},
	{-1, 138600},
	{0, 132900},
	{1, 127400},
	{2, 122200},
	{3, 117300},
	{4, 112500},
	{5, 108000},
	{6, 103700},
	{7, 99600},
	{8, 95690},
	{9, 91960},
	{10, 88400},
	{11, 84960},
	{12, 81670},
	{13, 78530},
	{14, 75530},
	{15, 72670},
	{16, 69930},
	{17, 67310},
	{18, 64810},
	{19, 62420},
	{20, 60130},
	{21, 57930},
	{22, 55810},
	{23, 53790},
	{24, 51850},
	{25, 50000},
	{26, 48210},
	{27, 46500},
	{28, 44870},
	{29, 43290},
	{30, 41790},
	{31, 40330},
	{32, 38940},
	{33, 37600},
	{34, 36310},
	{35, 35080},
	{36, 33900},
	{37, 32760},
	{38, 31670},
	{39, 30620},
	{40, 29610},
	{41, 28640},
	{42, 27700},
	{43, 26790},
	{44, 25930},
	{45, 25090},
	{46, 24290},
	{47, 23520},
	{48, 22770},
	{49, 22060},
	{50, 21370},
	{51, 20700},
	{52, 20060},
	{53, 19430},
	{54, 18840},
	{55, 18260},
	{56, 17700},
	{57, 17170},
	{58, 16650},
	{59, 16150},
	{60, 15670},
	{61, 15210},
	{62, 14760},
	{63, 14330},
	{64, 13910},
	{65, 13500},
	{66, 13110},
	{67, 12740},
	{68, 12370},
	{69, 12020},
	{70, 11680},
	{71, 11350},
	{72, 11040},
	{73, 10730},
	{74, 10430},
	{75, 10140},
	{76, 9861},
	{77, 9592},
	{78, 9331},
	{79, 9079},
	{80, 8835}
};

const SLINT PT100_Lookup_Table[ MAX_POINT_PT100_TABLE ][ 2 ] = {
	{ -100,	602541 },
	{ -99,	606594 },
	{ -98,	610645 },
	{ -97,	614695 },
	{ -96,	618742 },
	{ -95,	622787 },
	{ -94,	626831 },
	{ -93,	630873 },
	{ -92,	634912 },
	{ -91,	638950 },
	{ -90,	642987 },
	{ -89,	647021 },
	{ -88,	651054 },
	{ -87,	655084 },
	{ -86,	659114 },
	{ -85,	663141 },
	{ -84,	667166 },
	{ -83,	671190 },
	{ -82,	675212 },
	{ -81,	679233 },
	{ -80,	683251 },
	{ -79,	687268 },
	{ -78,	691284 },
	{ -77,	695297 },
	{ -76,	699309 },
	{ -75,	703319 },
	{ -74,	707328 },
	{ -73, 	711335 },
	{ -72,	715340 },
	{ -71,	719344 },
	{ -70,	723346 },
	{ -69,	727347 },
	{ -68,	731346 },
	{ -67,	735343 },
	{ -66,	739339 },
	{ -65,	743334 },
	{ -64,	747326 },
	{ -63,	751318 },
	{ -62,	755307 },
	{ -61,	759296 },
	{ -60,	763282 },
	{ -59,	767268 },
	{ -58,	771251 },
	{ -57,	775234 },
	{ -56,	779214 },
	{ -55,	783194 },
	{ -54,	787171 },
	{ -53,	791148 },
	{ -52,	795123 },
	{ -51,	799096 },
	{ -50,	803068 },
	{ -49,	807039 },
	{ -48,	811008 },
	{ -47,	814976 },
	{ -46,	818943 },
	{ -45,	822908 },
	{ -44,	826871 },
	{ -43,	830834 },
	{ -42,	834795 },
	{ -41,	838754 },
	{ -40,	842713 },
	{ -39,	846669 },
	{ -38,	850625 },
	{ -37,	854579 },
	{ -36,	858532 },
	{ -35,	862484 },
	{ -34,	866434 },
	{ -33,	870383 },
	{ -32,	874331 },
	{ -31,	878277 },
	{ -30,	882222 },
	{ -29,	886166 },
	{ -28,	890109 },
	{ -27,	894050 },
	{ -26,	897990 },
	{ -25,	901929 },
	{ -24,	905866 },
	{ -23,	909802 },
	{ -22,	913737 },
	{ -21,	917671 },
	{ -20,	921603 },
	{ -19,	925535 },
	{ -18,	929465 },
	{ -17,	933394 },
	{ -16,	937321 },
	{ -15,	941247 },
	{ -14,	945173 },
	{ -13,	949097 },
	{ -12,	953019 },
	{ -11,	956941 },
	{ -10,	960861 },
	{ -9 ,  964780 },
	{ -8,	968698 },
	{ -7,	972615 },
	{ -6,	976531 },
	{ -5,	980445 },
	{ -4,	984359 },
	{ -3,	988271 },
	{ -2,	992182 },
	{ -1,	996091 },
	{ 0	,   1000000 },
	{ 1, 	1003907 },
	{ 2, 	1007814 },
	{ 3, 	1011719 },
	{ 4,  	1015623 },
	{ 5, 	1019526 },
	{ 6, 	1023427 },
	{ 7, 	1027328 },
	{ 8, 	1031227 },
	{ 9, 	1035125 },
	{ 10,	1039022 },
	{ 11, 	1042918 },
	{ 12,	1046813 },
	{ 13,	1050706 },
	{ 14,	1054599 },
	{ 15,	1058490 },
	{ 16,	1062380 },
	{ 17,	1066269 },
	{ 18,	1070156 },
	{ 19,	1074043 },
	{ 20,	1077928 },
	{ 21, 	1081813 },
	{ 22,	1085696 },
	{ 23,	1089578 },
	{ 24,	1093458 },
	{ 25,	1097338 },
	{ 26,	1101216 },
	{ 27,	1105094 },
	{ 28,	1108970 },
	{ 29,	1112845 },
	{ 30,	1116718 },
	{ 31,	1120591 },
	{ 32,	1124463 },
	{ 33,	1128333 },
	{ 34,	1132202 },
	{ 35,	1136070 },
	{ 36,	1139937 },
	{ 37,	1143802 },
	{ 38,	1147667 },
	{ 39,	1151530 },
	{ 40,	1155392 }
};
*/
