/**
p24FJ256DA210_SPI1.c
**/
// local includes
#include "HardwareProfile.h"
#include "p24FJ256DA210_SPI1.h"

BYTE SPI1_RxBuffer[MAX_SPI1_RXBUFF];
BYTE SPI1_RxBuff_Cnt=0;
void Initialize_SPI1_Module (void)
{
	// SPI1 is used by FLASH SST25VF016B, external ADC LTC2439 DAC board
	// configure the SPI1 for master mode 8MHz operation
  	TRISFbits.TRISF3 = 0;  // Set SCK pin as an output
    TRISFbits.TRISF2 = 1;  // Make sure SDI pin is an input
    TRISGbits.TRISG8 = 0;  // Set SDO pin as an output
	
	SPI1CON1 = 0x0339;  // 500 Khz SPI clk frequency;Input data sampled at end of data output time ,	
						  // Serial output data changes on transition from active clock state to Idle clock state,
						  // Master mode is enabled.
	SPI1CON2 = 0x0000;
    SPI1STAT = 0;    // clear SPI

	TRISGbits.TRISG1=0; 		// pin 89 (RG1/CN78) as FLASH_CS drive
	CNPU5bits.CN78PUE=0;
	TRISGbits.TRISG0=0;			// pin 90 (RG0/CN77) as ADC_CS drive
	CNPU5bits.CN77PUE=0;
	TRISAbits.TRISA1=0;			// pin 38 (RA1/CN34)	as DAC_CS drive
	CNPU3bits.CN34PUE=0;
	
	SPI1STAT |= 0x8000 ;		//Start the SPI1 module
	IFS0bits.SPI1IF=0;			//clear interrupt flag
    //IEC0bits.SPI1IE=1;			//enable interrupt
    ///IPC2bits.SPI1IP=4;		//interrupt priority level 
    
	IFS0bits.SPI1IF=0;			//clear interrupt flag
	
}

void SPI1_TxByte(BYTE *Data, BYTE dataLength)
{

	while(dataLength>0)
	{
		while(SPI1STATbits.SPITBF);
		SPI1BUF=*Data;
		Data++;
		dataLength--;
		SPI1_RxByte();
	}

}

void SPI1_Tx_Only(BYTE *Data, BYTE dataLength)
{
	while(dataLength>0)
	{
		SPI1STATbits.SPIROV=0;
		while(SPI1STATbits.SPITBF);
			SPI1BUF=*Data;
		Data++;
		dataLength--;
	}

}
void SPI1_RxByte(void)
{
	
	while(!SPI1STATbits.SPIRBF ); //wait for receiving data
	if(SPI1_RxBuff_Cnt<MAX_SPI1_RXBUFF)
	{
	 SPI1_RxBuffer[SPI1_RxBuff_Cnt]=SPI1BUF;
	 SPI1_RxBuff_Cnt++;	
	}  	
}


void __attribute__((interrupt,no_auto_psv)) _SPI1Interrupt(void)
{
	//__builtin_disi(0x3FFF);
	IFS0bits.SPI1IF=0;			//clear interrupt flag
	//__UserGDE();
	IEC0bits.SPI1IE=0;			//disable interrupt
	while(!SPI1STATbits.SPIRBF); //wait for receiving data
	if(SPI1_RxBuff_Cnt<MAX_SPI1_RXBUFF)
	{
	 SPI1_RxBuffer[SPI1_RxBuff_Cnt]=SPI1BUF;
	 SPI1_RxBuff_Cnt++;	
	}  	
	
	//__UserGIE();
	IEC0bits.SPI1IE=1;			//enable interrupt
	//__builtin_disi(0x0000);
}

BYTE *Return_SPI1_RxBuffer(void)
{
	return &SPI1_RxBuffer[0];
}
BYTE Return_SPI1_RxBuffer_Cnt (void)
{
	return SPI1_RxBuff_Cnt;
}

void Flush_SPI1_RxBuffer(void)
{
 BYTE c;
 for(c=0;c<MAX_SPI1_RXBUFF;c++)
 	SPI1_RxBuffer[c]=0;
 SPI1_RxBuff_Cnt=0;
}
void __Enable_SPI1Master_Interrupt(void)
{
	IEC0bits.SPI1IE=1;			//enable interrupt
}
void __Disable_SPI1Master_Interrupt(void)
{
	IEC0bits.SPI1IE=0;			//enable interrupt
}

void Set_CS_LTC2439 (void)
{
   LATG|=0x0001;
}

void Reset_CS_LTC2439 (void)
{
  LATG&=~(0x0001);
}

void Restart_SPI1(void)
{
 WORD Dummy;
 SPI1STAT = 0;    // clear SPI
 Dummy=SPI1BUF; 
 SPI1STAT |= 0x8000 ;

}

void SetEdgeActiveToIdle(void)
{
 SPI1STAT = 0;    // clear SPI
 Delay_uS(10);
 SPI1CON1|=0x0100;
 SPI1STAT |= 0x8000 ;
 
}

void SetEdgeIdleToActive(void)
{
SPI1STAT = 0;    // clear SPI 
Delay_uS(10);

SPI1CON1&=~(0x0100);
SPI1STAT |= 0x8000 ;
}


