/**
p24FJ256DA210_I2C1.c

Configured as slave I2C
**/
// local includes
#include "HardwareProfile.h"
#include "p24FJ256DA210_I2C1.h"
#include "General.h"
#include "ApplicationDrivers.h"

BYTE I2C1_RxdataBuffer[MAX_I2C1_RXBUFF];
BYTE I2C1_RxBuff_Cnt=0;
BYTE I2C1_TxdataBuffer[MAX_I2C1_TXBUFF];
BYTE I2C1_TxBuff_Cnt=0;


void Initialize_I2C1_Module (void)
{
//	I2C1CON=0x0000;
//	//configure the I2C1 to communicate to UTI as slave
	I2C1CONbits.I2CEN=1;			//enable pin 66 (SCL1) and pin 67(SDA1) as I2C pin
//	I2C1CONbits.A10M =0;			//7 bit addressing
	I2C1ADD=OMB_I2C1_ADD;
	I2C1CONbits.DISSLW=1;			//disable slew rate control since using <400KHz
	I2C1CONbits.STREN=1;			//enable clock stretch
//	I2C1BRG=0;					//BRG is not used for slave
	
	__Clear_I2C1Slave_Interrupt();		//clear i2c slave interrupt;	
	__Enable_I2C1Slave_Interrupt();		//enable slave I2c interrupt.			
	
	IPC4bits.SI2C1IP=7;		//set interrupt level 
	
//	I2C1STATbits.S=0;				//clearable bit.
//	I2C1STATbits.P=0;
//	I2C1STATbits.BCL=0;
//	I2C1STATbits.I2COV=0;
//	I2C1STATbits.IWCOL=0;
	    	
	I2C1_RxdataBuffer[0]=I2C1RCV;					//clear the receive buffer
//	I2C1TRN=I2C1_TxdataBuffer[0];					//clear the transmit buffer
	
}

void __Disable_I2C1Slave_Interrupt(void)
{
IEC1bits.SI2C1IE=0;
}
void __Enable_I2C1Slave_Interrupt(void)
{
IEC1bits.SI2C1IE=1;
}
void __Set_I2C1Slave_Interrupt(void)
{
	IFS1bits.SI2C1IF=1;
}
void __Clear_I2C1Slave_Interrupt(void)
{
	IFS1bits.SI2C1IF=0;
}

void Tx_I2C1SlaveData(void)
{
	I2C1_TxBuff_Cnt=0;
	while(!I2C1STATbits.ACKSTAT)
		{
		 I2C1CONbits.SCLREL=0;	 
		 I2C1RCV=I2C1_TxdataBuffer[I2C1_TxBuff_Cnt];
		 I2C1_TxBuff_Cnt++;
		 I2C1CONbits.SCLREL=1;
		 while(I2C1STATbits.TBF);
		 Delay_uS(100);
		} 

}


void __attribute__((interrupt,no_auto_psv)) _SI2C1Interrupt (void)
{
 //__builtin_disi(0x3FFF);	
 WORD I2C1status=I2C1STAT;
 if(I2C1status & BIT_R_NOTW)  //if read
 {
  I2C1CON&=~BIT_SCLREL;	 
  if((I2C1status & BIT_D_NOTA) == 0x0000) //Address byte received
  {
  	I2C1_RxBuff_Cnt=0;
  	I2C1_TxBuff_Cnt=0;
  	I2C1_RxdataBuffer[I2C1_RxBuff_Cnt] = I2C1RCV;
  	I2C1_RxBuff_Cnt++;
  }
  I2C1TRN=I2C1_TxdataBuffer[I2C1_TxBuff_Cnt];
  I2C1_TxBuff_Cnt++;

 }
 else  //if write
 {
 
  if((I2C1status & BIT_D_NOTA) == 0x0000) //Address byte received
  {
  	I2C1_RxBuff_Cnt=0;
  	I2C1_TxBuff_Cnt=0;
  }
  I2C1_RxdataBuffer[I2C1_RxBuff_Cnt] = I2C1RCV;
  I2C1_RxBuff_Cnt++;
   SetIntDrivenEventFlag(1,INT_UTI);
 
 }

  I2C1CON|=BIT_SCLREL;
  
 __Clear_I2C1Slave_Interrupt();
//__builtin_disi(0x0000);
}

BYTE *ReturnI2C1_RxDataBuffer(void)
{
 return &I2C1_RxdataBuffer[0];
}

 
BYTE *ReturnI2C1_TxBuffer(void)
{
 return &I2C1_TxdataBuffer[0];
}
BYTE ReturnCounter_I2C1RxBuffer(void)
{
 return I2C1_RxBuff_Cnt;
}
BYTE ReturnCounter_I21TxBuffer(void)
{
return I2C1_TxBuff_Cnt;
}
void Flush_I2C1RxBuffer (void)
{
 BYTE c;
 for (c=0;c<MAX_I2C1_RXBUFF;c++)I2C1_RxdataBuffer[c]=0;
 I2C1_RxBuff_Cnt=0; 
}
