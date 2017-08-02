void AdaptControlHeater (void)
{
	BYTE HeatState=INITIATE_STATE;
	WORD HEATER_PULSE=ONE_SECOND;
	WORD cnt_HeatPulse;
	WORD T_peak=0;
	float T_0;
	WORD dtime_HeatingDelay=0;
	WORD dtime_HeatingPeak=0;
	float heat_error=0;
	float heat_capacity;    // celcius/100% dutycycle 1 second pulse heat
	WORD HeatUp_Time=0;
	WORD HeatObserv_Time=0;
    float NextDutyCycle;
	heat_error=Tsp-(Tcv+Tcv_Offset);
	switch(HeatState)
		{
		case INITIATE_STATE:
			NextDutyCycle=100;
			HEATER_PULSE=ONE_SECOND;			
		case PULSE_SET_STATE:
			DutyCycle=NextDutyCycle;
			T_0=Tcv+Tcv_Offset;
			UpdateHeaterDCY();
			cnt_HeatPulse=0;
			dtime_HeatingPeak=0;
			dtime_HeatingDelay=0;
			HeatState=PULSE_OBSERVE_STATE;
			break;
		case PULSE_OBSERVE_STATE:
			if(cnt_HeatPulse++>HEATER_PULSE)
			{
			HeatState=AFTER_PULSE_OBSERVE_STATE;
			DutyCycle=0;
			UpdateHeaterDCY();
			}
			if(heat_error<-50)		
			{
			HeatState=STOP_HEATING;
			if(HEATER_PULSE>ONE_SECOND)HEATER_PULSE-=TEN_MS;
			else{ 
					if(NextDutyCycle>0)NextDutyCycle-=5;
				}		
			}dtime_HeatingPeak++;			
			if(Tcv+Tcv_Offset-T_0<10)dtime_HeatingDelay++;
			else dtime_HeatingPeak++;
			break;
		case AFTER_PULSE_OBSERVE_STATE:
			if(Tcv+Tcv_Offset-T_0<10)dtime_HeatingDelay++;
			else 
				{
				if(Tcv+Tcv_Offset>=prevTcv)
					{
						dtime_HeatingPeak++;
						T_peak=Tcv+Tcv_Offset;
					}
				else HeatState=HEATUP_SET_STATE;					
				}			
			break;
		case HEATUP_SET_STATE:
			cnt_HeatPulse=0;
			heat_capacity=(T_peak-T_0)/(HEATER_PULSE/ONE_SECOND);
			HeatUp_Time=(heat_error/heat_capacity)*ONE_SECOND;
			HeatObserv_Time=(heat_error/heat_capacity)*(dtime_HeatingDelay+dtime_HeatingPeak);
			HeatState=HEATUP_OBSERVATION_STATE;
			T_0=Tcv+Tcv_Offset;
			DutyCycle=NextDutyCycle;
			UpdateHeaterDCY();
		case HEATUP_OBSERVATION_STATE:
			if(cnt_HeatPulse>=HeatUp_Time)
			{
				DutyCycle=0;
				UpdateHeaterDCY();			
				HeatState=HEATING_OBSERVATION_STATE;
			}
			else {
			cnt_HeatPulse++;
			if(heat_error<-50)
				{
				DutyCycle=0;
				UpdateHeaterDCY();			
				HeatState=STOP_HEATING;
				}
			}
			break;
		case HEATING_OBSERVATION_STATE:
			if(Tcv+Tcv_Offset>=prevTcv)
				{
					T_peak=Tcv+Tcv_Offset;
				}
			else 
				{
				if(heat_error<=0)HeatState=STOP_HEATING;
				else
					{
					  heat_capacity=(T_peak-T_0)/(HeatUp_Time/ONE_SECOND);
					  HeatUp_Time=(heat_error/heat_capacity)*ONE_SECOND;
					  T_0=Tcv+Tcv_Offset;
					  DutyCycle=NextDutyCycle;
					  UpdateHeaterDCY();
					  HeatState= HEATUP_OBSERVATION_STATE;	
					}
			}			
			break;
		case STOP_HEATING:
			  if(heat_error>=50)HeatState=PULSE_SET_STATE;
			break;				
		}	
}

void UpdateHeaterDCY(void)
{
 WORD OutputsFlag=ReturnFlag(OMB_OUTPUTS_FLAG);
 WORD Mode=ReturnFlag(SYSTEM_MODE_FLAG);
 OutputsFlag&=~(MAIN_HEATER_FLAG|BASE_HEATER_FLAG|DOOR_HEATER_FLAG|DECON_HEATER_FLAG);
 float Pwr_Ratio;
 Update_Zone1_OC3_PWM(DutyCycle);
 if(DutyCycle>0.0)OutputsFlag|=MAIN_HEATER_FLAG;
 
 Pwr_Ratio=Base_Htr_PR/100.0; 
 Update_Zone2_OC4_PWM  ( DutyCycle*Pwr_Ratio);
 if((DutyCycle*Pwr_Ratio)>0.0)OutputsFlag|=BASE_HEATER_FLAG;

 
 Pwr_Ratio=Door_Htr_PR/100.0;
 Update_Zone3_OC5_PWM(DutyCycle*Pwr_Ratio);
 if((DutyCycle*Pwr_Ratio)>0.0)OutputsFlag|=DOOR_HEATER_FLAG;

 if (Mode==DECON_MODE)
 {
	 //Update_Zone4_OC6_PWM(100.0);
	 Update_Zone5_OC7_PWM(100.0);
	 OutputsFlag|=DECON_HEATER_FLAG;
 }
 else 
 {
 Pwr_Ratio=Decon_Htr_PR/100.0;
 //Update_Zone4_OC6_PWM(DutyCycle*Pwr_Ratio);
 Update_Zone5_OC7_PWM(DutyCycle*Pwr_Ratio);
  if((DutyCycle*Pwr_Ratio)>0.0)OutputsFlag|=DECON_HEATER_FLAG;
 }
}

