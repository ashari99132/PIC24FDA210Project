#ifndef __APPLICATION_DRIVERS_H
#define __APPLICATION_DRIVERS_H

//general include
#include "General.h"
#include "GenericTypeDefs.h"
#include "TCPIP Stack/TCPIP.h"
//drivers include
#include "p24FJ256DA210_Timer3.h"
//#include "p24FJ256DA210_Timer2.h"
#include "p24FJ256DA210_Timer1.h"
#include "p24FJ256DA210_UART1.h"
#include "p24FJ256DA210_SPI1.h"
#include "LTC2439.h"
#include "Flash.h"
#include "p24FJ256DA210_I2C1.h"
#include "p24FJ256DA210_ICN.h"
#include "p24FJ256DA210_UART2.h"
#include "p24FJ256DA210_I2C3.h"
#include "p24FJ256DA210_OCX.h"

//application include
#include "Flag_id.h"
#include "AC_Hz.h"
#include "AlarmContactRelay.h"
#include "CO2_Control.h"
#include "CO2_RS485.h"
#include "EEPROM_24AA1025.h"
#include "RTC_S35390.h"
#include "EventBuzzer.h"
#include "EventRTC.h"
#include "EventScheduler.h"
#include "EventTCPIP.h"
#include "Event_UV.h"
#include "FailSafeRelay.h"
#include "O2_Control.h"
#include "O2_RS485.h"
#include "OMB_AnalogOutput.h"
#include "OMB_DigitalInputs.h"
#include "OMB_Mode.h"
#include "OMB_Output.h"
#include "OMB_UTI_Comm.h"
#include "OMBLTC2439_Inputs.h"
#include "RH_Control.h"
//#include "RTC_S35390.h"
#include "TempControl.h"
#include "USB.h"

#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
	void SaveAppConfig(const APP_CONFIG *AppConfig);
#else
	#define SaveAppConfig(a)
#endif

// Define a header structure for validating the AppConfig data structure in EEPROM/Flash
typedef struct
{
	unsigned short wConfigurationLength;	// Number of bytes saved in EEPROM/Flash (sizeof(APP_CONFIG))
	unsigned short wOriginalChecksum;		// Checksum of the original AppConfig defaults as loaded from ROM (to detect when to wipe the EEPROM/Flash record of AppConfig due to a stack change, such as when switching from Ethernet to Wi-Fi)
	unsigned short wCurrentChecksum;		// Checksum of the current EEPROM/Flash data.  This protects against using corrupt values if power failure occurs while writing them and helps detect coding errors in which some other task writes to the EEPROM in the AppConfig area.
} NVM_VALIDATION_STRUCT;

//Split NVM_VALIDATION_STRUCT structure into its respective bytes
typedef union __NVM_VALIDATION_PagestructToByte__
{
  BYTE bytes[ sizeof( NVM_VALIDATION_STRUCT )];
  NVM_VALIDATION_STRUCT Page_Instance;
}NVM_VALIDATION_PAGESTRUCTTOBYTE, *pNVM_VALIDATION_PAGESTRUCTTOBYTE;

pNVM_VALIDATION_PAGESTRUCTTOBYTE Return_NVMPage_Pointer(void);



#endif
