/*********************************************************************
 *
 *	Hardware specific definitions
 *
 *********************************************************************
 * FileName:        HardwareProfile.h
 * Dependencies:    None
 * Processor:       PIC24F, PIC32
 * Compiler:        Microchip C32 v1.00 or higher
 *					Microchip C30 v3.01 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2008 Microchip Technology Inc.  All rights 
 * reserved.
 *
 * You should refer to the license agreement accompanying this 
 * Software for additional information regarding your rights and 
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL 
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR 
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF 
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS 
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE 
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER 
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT 
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *
 * Author               Date		Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Darren Wenn  		09/10/08	Original
 * Darren Wenn			06/01/09    Upgraded to Graphics V1.65 and 
 *									TCPIP V5.00
 * Darren Wenn          09/03/09    Upgraded to Graphics V1.75, MiWi P2P 2.1
 *                                  and TCPIP V5.10
 ********************************************************************/
#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H


#include "p24FJ256DA210.h"
#include "General.h"
#include "GenericTypeDefs.h"

#include "Compiler.h"

// Define a macro describing this hardware set up (used in other files)
#define PIC24FJ256DA210_DEV_BOARD
// This value is used to calculate Tick Counter value
	// PIC24F processor
#define GetSystemClock()		(32000000ul)			// Hz
#define GetInstructionClock()	(GetSystemClock()/2)	// Normally GetSystemClock()/4 for PIC18, GetSystemClock()/2 for PIC24/dsPIC, and GetSystemClock()/1 for PIC32.  Might need changing if using Doze modes.
#define GetPeripheralClock()	(GetSystemClock()/2)	// Normally GetSystemClock()/4 for PIC18, GetSystemClock()/2 for PIC24/dsPIC, and GetSystemClock()/1 for PIC32.  Divisor may be different if using a PIC32 since it's configurable.
	#define CLOCK_FREQ              (32000000ul)


#define  O_MCB_I2C_ADDRES 0x0B;
enum OnOffType{
	OFF=0,
	ON
	};

//pin bits
#define PIN_0 		0x0001
#define PIN_1 		0x0002
#define PIN_2 		0x0004
#define PIN_3 		0x0008
#define PIN_4 		0x0010
#define PIN_5 		0x0020
#define PIN_6 		0x0040
#define PIN_7 		0x0080
#define PIN_8 		0x0100
#define PIN_9 		0x0200
#define PIN_10 		0x0400
#define PIN_11 		0x0800
#define PIN_12 		0x1000
#define PIN_13 		0x2000
#define PIN_14 		0x4000
#define PIN_15 		0x8000



//O Series Main Board Outputs
#define BUZZER_IO			LATEbits.LATE4
#define O2_SENSOR_POWER		LATAbits.LATA0
#define TC_SENSOR_POWER		LATCbits.LATC14
#define DIG_OUT1			LATBbits.LATB13
#define DIG_OUT2			LATBbits.LATB12
#define DIG_OUT3			LATBbits.LATB11
#define DIG_OUT4			LATBbits.LATB10
#define DIG_OUT5			LATBbits.LATB3
#define DIG_OUT6			LATBbits.LATB9
#define DIG_OUT7			LATBbits.LATB2
#define DIG_OUT8			LATBbits.LATB8
#define DIG_OUT9			LATBbits.LATB4
#define DIG_OUT10			LATGbits.LATG7
#define DIG_OUT11			LATGbits.LATG15
#define DIG_OUT12			LATDbits.LATD14
#define AC_CUTOFF_RELAY1_J41	LATAbits.LATA10
#define UV_BALLAST_RELAY_J33	LATAbits.LATA9
#define AC_CUTOFF_RELAY2	LATGbits.LATG14
#define ANALOGBRD_MUX_A0	LATDbits.LATD12
#define ANALOGBRD_MUX_A1	LATDbits.LATD13
#define ANALOGBRD_MUX_EN	LATDbits.LATD7
#define TRIAC_MAINHEATER_J35	LATEbits.LATE0
#define TRIAC_PANHEATER_J34		LATEbits.LATE1
#define NONC_CONTACT_J7		LATEbits.LATE5
#define BATT_CUTOFF			LATGbits.LATG12
#define BATT_MEASURE		LATGbits.LATG13
#define EXPANSION_RELAY_PORT		LATGbits.LATG14

//Shaker outputs
#define ILLUMINATION_J14	DIG_OUT6
#define COMPRESSOR_J20		DIG_OUT1
#define CO2_SOLENOID_J22	DIG_OUT2
#define GROW_LAMP_J15		DIG_OUT3
#define SPARE1_J23			DIG_OUT5
#define SPARE2_J19			DIG_OUT4	
#define SPARE3_J16			DIG_OUT7
#define SPARE4_J18			DIG_OUT8
#define SPARE5_J17			DIG_OUT9
#define SPARE6_J24			DIG_OUT10
#define SPARE7_J28			DIG_OUT11
#define SPARE8_J30			DIG_OUT12

//CelSafe Outputs	
#define O2_MAINSOL_J14		DIG_OUT6
#define O2_BACKSOL_J20		DIG_OUT1
#define CO2_MAINSOL_J22		DIG_OUT2
#define CO2_BACKSOL_J15		DIG_OUT3
#define SPARE1_J23			DIG_OUT5
#define EM_DOORLOCK_J19		DIG_OUT4	
#define ZONE2_HEATER_J16	DIG_OUT7
#define ZONE3_HEATER_J18	DIG_OUT8
#define ZONE4_HEATER_J17	DIG_OUT9
#define ZONE5_HEATER_J24	DIG_OUT10
#define ZONE6_HEATER_J28	DIG_OUT11
#define ZONE7_HEATER_J30	DIG_OUT12		
	
	// ENC28J60 I/O pins
	#define ENC_CS_TRIS			(TRISDbits.TRISD15)
	#define ENC_CS_IO			(LATDbits.LATD15)   // (LATGbits.LATG6)   // (LATDbits.LATD15) --O series board
	// SPI SCK, SDI, SDO pins are automatically controlled by the 
	// PIC24/PIC32 SPI module 

		#define ENC_SPI_IF			(IFS2bits.SPI2IF)
		#define ENC_SSPBUF			(SPI2BUF)
		#define ENC_SPISTAT			(SPI2STAT)
		#define ENC_SPISTATbits		(SPI2STATbits)
		#define ENC_SPICON1			(SPI2CON1)
		#define ENC_SPICON1bits		(SPI2CON1bits)
		#define ENC_SPICON2			(SPI2CON2)



//I2CxCON bits
#define BIT_SEN 	0x0001
#define BIT_RSEN 	0x0002
#define BIT_PEN 	0x0004
#define BIT_RCEN 	0x0008
#define BIT_ACKEN 	0x0010
#define BIT_ACKDT 	0x0020
#define BIT_STREN 	0x0040
#define BIT_GCEN 	0x0080
#define BIT_SMEN 	0x0100
#define BIT_DISSLW 	0x0200
#define BIT_A10M 	0x0400
#define BIT_IPMIEN 	0x0800
#define BIT_SCLREL 	0x1000
#define BIT_I2CSIDL 0x2000
#define BIT_I2CEN 	0x8000

//I2CxSTAT bits

#define BIT_TBF 	0x0001
#define BIT_RBF 	0x0002
#define BIT_R_NOTW 	0x0004
#define BIT_S	 	0x0008
#define BIT_P	 	0x0010
#define BIT_D_NOTA 	0x0020
#define BIT_I2COV 	0x0040
#define BIT_IWCOL 	0x0080
#define BIT_ADD10 	0x0100
#define BIT_GCSTAT 	0x0200
#define BIT_BCL 	0x0400
#define BIT_TRSTAT 	0x4000
#define BIT_ACKSTAT 0x8000

// SST SST25VF016B (16Mbit/2Mbyte) I/O pins
// Jumper JP23 must have a shunt shorting pins 2-3 (not the default).
#define SPIFLASH_CS_TRIS		BRDFLASH_CS_TRIS     // (TRISAbits.TRISA14)  // (TRISGbits.TRISG1) --O series board 
#define SPIFLASH_CS_IO			BRDFLASH_CS_IO       // (LATAbits.LATA14)    // (LATGbits.LATG1) --O series board 
#define SPIFLASH_SCK_TRIS		(TRISFbits.TRISF3)   // (TRISDbits.TRISD8)   // (TRISFbits.TRISF3) --O series board  
#define SPIFLASH_SDI_TRIS		(TRISFbits.TRISF2)   // (TRISBbits.TRISB0)   // (TRISFbits.TRISF2) --O series board  
#define SPIFLASH_SDI_IO			(PORTFbits.RFF2)	 // (PORTBbits.RB0)      // (PORTFbits.RF2) --O series board 
#define SPIFLASH_SDO_TRIS		(TRISFbits.TRISF2)	 // (TRISBbits.TRISB1)   // (TRISGbits.TRISG8) --O series board  
#define SPIFLASH_SPI_IF			(IFS0bits.SPI1IF)
#define SPIFLASH_SSPBUF			(SPI1BUF)
#define SPIFLASH_SPICON1		(SPI1CON1)
#define SPIFLASH_SPICON1bits	(SPI1CON1bits)
#define SPIFLASH_SPICON2		(SPI1CON2)
#define SPIFLASH_SPISTAT		(SPI1STAT)
#define SPIFLASH_SPISTATbits	(SPI1STATbits)


#define SPIADC_CS_TRIS			(TRISGbits.TRISG0) //--O series board 
#define SPIADC_CS_IO			(LATGbits.LATG0) //--O series board 

#define SPIDAC_CS_TRIS			(TRISAbits.TRISA1)// --O series board 
#define SPIDAC_CS_IO			(LATAbits.LATA1) //--O series board 

#define BRDFLASH_CS_TRIS		(TRISGbits.TRISG1) //--O series board 
#define BRDFLASH_CS_IO			(LATGbits.LATG1) //--O series board 





void __UserGIE(void);
void __UserGDE(void);

#endif
