/**
Main.c
*/
 
// Standard includes

#define THIS_IS_STACK_APPLICATION
#include <stdio.h>


// local includes
#include "HardwareProfile.h"
#include "ApplicationDrivers.h"



//global variables.
char Dummy;

// Declare AppConfig structure and some other supporting stack variables
APP_CONFIG AppConfig;

// Use UART2 instead of UART1 for stdout (printf functions).  Explorer 16 
// serial port hardware is on PIC UART2 module.
#if defined(EXPLORER_16) || defined(PIC24FJ256DA210_DEV_BOARD)
    int __C30_UART = 2;
#endif

// Forward references in this module
static void InitializeBoard(void);


//configuration bits
_CONFIG1( WDTPS_PS32768 & FWPSA_PR128 & ALTVREF_ALTVREDIS & WINDIS_OFF & FWDTEN_OFF & ICS_PGx2 & GWRP_OFF & GCP_OFF & JTAGEN_OFF) 
//use primary oscillator in XT mode no PLL. Since oscillator is 8 MHz. Secondary oscillator is off.
_CONFIG2( POSCMOD_XT & IOL1WAY_OFF & OSCIOFNC_OFF & OSCIOFNC_OFF & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_OFF)
_CONFIG3( WPFP_WPFP255 & SOSCSEL_EC & WUTSEL_LEG & ALTPMP_ALTPMPEN & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM) 
  

/*********************************************************************
 * Function:        int main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *                  
 * Output:          Does not return
 *
 * Side Effects:    None
 *
 * Overview:        Application main entry point
 *
 * Note:            
 ********************************************************************/
 
int main(void)
{
	//local variables
	
	//BYTE Test[2]={0xfd,0xae};
	RCON=0x0000; // reset all reset flags
	// configure the hardware resources on the board
	DelayMs(10000); //give delay to wiait for stable supply
	InitializeBoard();	
	Initialize_UART1_Module();
	Initialize_UART2_Module();
	Initialize_Timer1_Module();
	Initialize_Timer3_Module();
 	Initialize_Timer4_Module();
	Initialize_SPI1_Module();
	Initialize_I2C1_Module();
	Initialize_ICN_Module();
	Initialize_I2C3_Module();
	Initialize_OC_Module ();
	InitializeAnalogOut();
	
	//EEPROM_Read(0x0058,&Test[0],2);
	//EEPROM_MultiWrite (0x0026, &Test[0],2);   //manual input eeprom register 
    
	ReadShakerRegisterFromEEPROM();
	CalibrateAnalogOut();
	// Initialize stack-related hardware components that may be 
    // required by the UART configuration routines
    TickInit();
    

    // Initialize Stack and application related NV variables into AppConfig.
    InitAppConfig();

    // Initialize core stack layers (MAC, ARP, TCP, UDP) and
    // application modules (HTTP, SNMP, etc.)
    StackInit();


	Flag[SYSTEM_MODE_FLAG]=NORMAL_MODE;
	UpdateSystemSensor();
	EventUpdateAlarmContactRelay();
        RTCEventPumpChamberOn();
 //       StartTimerRTC(COLD_CTL_ENABLE_ID,ONCE,2*MINUTE);
//    Exp_FailSafe_Relay_On();
//	FailSafe_Relay_On();

	while (1)
	{	
	  RunBackGroundEvents();	
	}
	// but in case it does
	return 1;	
}

/*********************************************************************
 * Function:        void InitializeBoard(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *                  
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Board configuration functions, some functions
 *					are performed in separate tasks (i.e. UART)
 *
 * Note:            
 ********************************************************************/
static void InitializeBoard(void)
{
	//---------------microcontroller setup-----------------------
	//OSCCONbits.COSC=0b010; //use primary oscillator w/o PLL which using crystal 8MHZ and Fosc is 8MHZ.
	//OSCCONbits.NOSC=0b010; //use primary oscillator w/o PLL which using crystal 8MHZ and Fosc is 8MHZ.
	//INTCON1bits.NSTDIS=1; //no need for nested interrupt.
	//INTCON2bits.DISI=1; 	//enable DISI instruction;
		    #if defined(__PIC24FJ256DA210__) || defined(__PIC24FJ256GB210__)
        // Disable analog on all pins
        ANSA = 0x0000;
        ANSB = 0x0000;
        ANSC = 0x0000;
        ANSD = 0x0000;
        ANSE = 0x0000;
        ANSF = 0x0000;
        ANSG = 0x0000;
    #endif
	//----------------remapping the pins------------------------- 
	__builtin_write_OSCCONL(OSCCON & 0xbf);  //unlock registers
	
	// remapping the SPI1 pins
	RPOR8bits.RP16R =	0b01000; 	// pin 51 (RP16) as SCLK out								
	RPOR9bits.RP19R =	0b00111;	// pin 12 (RP19) as SIMO (SDO1)
	RPINR20bits.SDI1R =	0b11110;	// pin 52 (RP30) as SOMI (SDI1)	

	// remapping the SPI2 pins	
	RPOR0bits.RP0R =	0b01011; 	// pin 25 (RP0) as SCLK out								
	RPOR0bits.RP1R =	0b01010;	// pin 24 (RP1) as ETH_SPI_DATAOUT (SDO2)
	RPINR22bits.SDI2R =	0b00010;	// pin 68 (RP2) as ETH_SPI_DATAIN (SDI2)	
	
		//remapping the UART2 pins to use for O2 sensor RS-485
     RPOR14bits.RP29R = 0b00101;		//pin 44 (RP29) as O2SENSOR_TX (U2TX)
	 RPINR19bits.U2RXR 	 = 0b001110;		//pin 43 (RP14) as O2SENSOR_RX (U2RX)
			
	//remapping the UART1 pins to use for voyager
     RPOR1bits.RP3R = 0b00011;		//pin 70 (RP3) as RS485_TX (U1TX)
	RPINR18bits.U1RXR 	=0b001100;		//pin 71 (RP12) as RS485_RX (U1RX)
	
	//remapping the UART3 pins to use for O2 sensor RS-485
//	RPOR14bits.RP29R = 0b11100;		//pin 44 (RP29) as O2SENSOR_TX (U3TX)
//	RPINR17bits.U3RXR 	 = 0b001110;		//pin 43 (RP14) as O2SENSOR_RX (U3RX)

	//remapping the UART4 pins to use for O2 sensor RS-485
//	RPOR14bits.RP29R = 0b11110;		//pin 44 (RP29) as O2SENSOR_TX (U4TX)
//	RPINR27bits.U4RXR 	 = 0b001110;		//pin 43 (RP14) as O2SENSOR_RX (U4RX)

	
	// remapping the RD4/RP25 pin as the PWM out OC1 for main heater
	RPOR12bits.RP25R = 0b010010;
	//remapping the RD5/RP20  pin as the PWM out OC2 for water pan heater
	RPOR10bits.RP20R = 0b010011;

	
	//remapping the RP13/RB2 pin as the PWM out OC3 for zone1 heater
	RPOR6bits.RP13R =0b010100;
	//remapping the RP8/RB8 pin as the PWM out OC4 for zone2 heater
	RPOR4bits.RP8R =0b010101;
	//remapping the RP28/RB4 pin as the PWM out OC5 for zone 3 heater
	RPOR14bits.RP28R =0b010110;
	//remapping the RP26/RG7 pin as the PWM out OC6 for zone 4 heater. 
      RPOR13bits.RP26R =0b010111;
     	//remapping the RP17/RF5 pin as the PWM out OC7 for zone 5 heater. 
      RPOR8bits.RP17R =0b011000;
         //remappng the RP10/RF4 pin as the  PWM out OC8 for zone 6 heater. 
      RPOR5bits.RP10R =0b011001;   
	__builtin_write_OSCCONL(OSCCON | 0x40); //unlock registers
	//----------------end of remapping the pins--------------------
		
	

	
	

	// configure the SPI2 for master mode 8MHz operation
    // SPI2 is used by the ENC 
 //   SPI2CON1bits.PPRE = 0b11;
//    SPI2CON1bits.SPRE = 0b110;
//    SPI2CON1bits.MSTEN = 1;
//    SPI2CON1bits.CKE = 1;
//    SPI2STAT = 0x8000;
	TRISDbits.TRISD15=0;			//pin 48 (RD15/CN21) as ETHERNET_CS drive
//	CNPU2bits.CN21PUE=0;
//	TRISCbits.TRISC3=0;				//pin 8 (RC3/CN47)as ETHERNET_RESET drive
//	CNPU3bits.CN47PUE=0;
//	CNEN3bits.CN45IE=1;				//pin 6 (CN45) as LAN_INT interrupt
	


	
	
	//configure the output ports
	TRISAbits.TRISA10=0;//pin 29 (RA10/CN42) as AC_CUTOFF_RELAY1
	CNPU3bits.CN42PUE=0;
	TRISAbits.TRISA9=0;	//pin 28 (RA9/CN41) as UV_BALLAST_RELAY
	CNPU3bits.CN41PUE=0;
	TRISGbits.TRISG14=0;	//pin 95 (RG14/CN81) as AC_CUTOFF_RELAY2
	CNPU6bits.CN81PUE=0;
	TRISDbits.TRISD12=0;	//pin 79 (RD12/CN57) as ANALOGBRD_MUX_A0
	CNPU4bits.CN57PUE=0;
	TRISDbits.TRISD13=0;	//pin 80 (RD13/CN19) as ANALOGBRD_MUX_A1
	CNPU2bits.CN19PUE=0;
	TRISDbits.TRISD6=0;	//pin 83 (RD6/CN15) as ANALOGBRD_MUX_EN
	CNPU1bits.CN15PUE=0;
	TRISEbits.TRISE0=0;	//pin 93 (RE0/CN58)	as TRIACMAIN_HEATER
	CNPU4bits.CN58PUE=0;
	TRISEbits.TRISE1=0;	//pin 94 (RE1/CN59) as TIRACPAN_HEATER
	CNPU4bits.CN59PUE=0;
	TRISEbits.TRISE4=0;	//pin 100 (RE4/CN62) as BUZZER
	CNPU4bits.CN62PUE=0;
	TRISEbits.TRISE5=0;	//pin 3   (RE5/CN63) as NONC_CONTACT
	CNPU4bits.CN63PUE=0;
	TRISGbits.TRISG7=0;	//pin 11 (RG7/CN9) as DIGOUT_10
	CNPU1bits.CN9PUE=0;
	TRISBbits.TRISB4=0;	//pin 21 (RB4/CN6) as DIGOUT_9
	CNPU1bits.CN6PUE=0;
	TRISBbits.TRISB8=0;	//pin 32 (RB8/CN26) as DIGOUT_8
	CNPU2bits.CN26PUE=0;
	TRISBbits.TRISB2=0;	//pin 23 (RB2/CN4) as DIGOUT_7
	CNPU1bits.CN4PUE=0;
	TRISBbits.TRISB9=0;	//pin 33 (RB9/CN27) as DIGOUT_6
	CNPU2bits.CN27PUE=0;
	TRISBbits.TRISB3=0;	//pin 22 (RB3/CN5) as DIGOUT_5
	CNPU1bits.CN5PUE=0;
	TRISBbits.TRISB10=0;	//pin 34 (RB10/CN28) as DIGOUT_4
	CNPU2bits.CN28PUE=0;
	TRISBbits.TRISB11=0;	//pin 35 (RB11/CN29) as DIGOUT_3
	CNPU2bits.CN29PUE=0;
	TRISBbits.TRISB12=0;	//pin 41 (RB12/CN30) as DIGOUT_2
	CNPU2bits.CN30PUE=0;
	TRISBbits.TRISB13=0;	//pin 42 (RB13/CN31) as DIGOUT_1
	CNPU2bits.CN31PUE=0;
	TRISBbits.TRISB15=0;	//pin 1  (RG15/CN82) as DIGOUT_11
	CNPU6bits.CN82PUE=0;
	TRISDbits.TRISD14=0;	//pin 47 (RD14/CN20) as DIGOUT_12
	CNPU2bits.CN20PUE=0;
	TRISGbits.TRISG12=0;	//pin 96 (RG12/CN79) as BAT_CUT_OFF
	CNPU5bits.CN79PUE=0;
	TRISAbits.TRISA2=0;	//pin 58 (RA2/CN35) as TRIAC_DRIVE
	CNPU3bits.CN35PUE=0;
	TRISGbits.TRISG13=0;	//pin 97 (RG13) Battery measure
	TRISDbits.TRISD7=0;  //pin 84 (D7 )J37 LED Driver
	TRISAbits.TRISA3=0;	//pin 59 (A3) J53 DCON FAN
	TRISGbits.TRISG6=0;	//pin 10 (G6) J57 WATER VALVE
	TRISAbits.TRISA7=0; //pin 92 (A7) VAISALA_PWR

}
void __UserGIE(void)
{
	__Enable_I2C1Slave_Interrupt();
	__Enable_SPI1Master_Interrupt();
	__Enable_Timer1_Interrupt();
	
	
}
void __UserGDE(void)
{
	__Disable_I2C1Slave_Interrupt();
	__Disable_SPI1Master_Interrupt();
	__Disable_Timer1_Interrupt();
}

