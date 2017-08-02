/**
p24FJ256DA210_I2C3.c

Configured as master I2C
**/
// local includes
#include "HardwareProfile.h"
#include "p24FJ256DA210_I2C3.h"
#include "General.h"


BYTE I2C3_dataBuffer[MAX_I2C3_RXBUFF];
BYTE I2C3_dataBuffer_Cnt;
BYTE I2C3_Flag;
void Initialize_I2C3_Module(void)
{
	I2C3CON=0x0000;
	//configure the I2C3 for RTC and EEPROM as master
	I2C3CONbits.I2CEN=1;			//enable pin 5 (SCL3) and pin 4(SDA3) as I2C pin
	I2C3CONbits.A10M =0;			//7 bit addressing
	I2C3CONbits.DISSLW=1;			//disable slew rate control since using <400KHz
	I2C3BRG=0x9D;					//100kHz Fscl from 16 MHz Fcy
		
	IFS5bits.MI2C3IF=0;				//clear i2c master interrupt;
	//IEC5bits.MI2C3IE=1;				//enable master I2c interrupt.
	//IPC21bits.MI2C3IP=0b100;		//set interrupt level 4
	
	I2C3STATbits.S=0;				//clearable bit.
	I2C3STATbits.P=0;
	I2C3STATbits.BCL=0;
	I2C3STATbits.I2COV=0;
	I2C3STATbits.IWCOL=0;
	    	
	I2C3_dataBuffer[0]=I2C3RCV;					//clear the receive buffer
	I2C3TRN=I2C3_dataBuffer[0];					//clear the transmit buffer	
	
	 I2C3_Idle_Bus(); 
}

void I2C3_startBit(void) //initate start condition
{
 I2C3CONbits.SEN=1;
}
void I2C3_Idle_Bus(void) //Idle bus of I2C
{
 I2C3CON&=0xffe0;
 Delay_uS(20);	
}

void I2C3_REstartBit(void) //initate re start condition
{
 I2C3CON&=0xffe0;	
 I2C3CONbits.RSEN=1;
}
void I2C3_stopBit(void) //initate stop condition
{
  WORD TimeOut=0;	
 I2C3CON&=0xffc0;
 Delay_uS(20);	
 I2C3CONbits.PEN=1;
 while(I2C3CONbits.PEN && TimeOut++<5)Delay_uS(20);

 I2C3STATbits.S=0;
}


BYTE I2C3_Is_AckBit(void)  //return the ACK status
{

 if(I2C3STATbits.ACKSTAT==ACK)
 	return 1;
 else return 0;

 
}

void I2C3_Send_Ack(void)
{
 I2C3CON&=0xffe0;
 I2C3STATbits.S=0;	
 I2C3CONbits.ACKDT=0;
 I2C3CONbits.ACKEN=1;
}

void I2C3_Send_NAck(void)
{
 WORD TimeOut=0;
 I2C3CON&=0xffe0;
 I2C3STATbits.S=0;
 I2C3CONbits.ACKDT=1;
 I2C3CONbits.ACKEN=1;
 //Delay_uS(20);
 //while(!I2C3_Flag);
 //I2C3_Flag=0; //reset flag
  while(I2C3CONbits.ACKEN && TimeOut++<5)Delay_uS(20);
}


void I2C3_MasterReceive_Enable(void)
{
 I2C3CONbits.RCEN=1;
 }

void I2C3_Send_Byte(BYTE Data)
{
 WORD TimeOut=0;
 I2C3TRN=Data;
 while(I2C3STATbits.TBF&& TimeOut++<5)Delay_uS(20);
}

BYTE I2C3_Receive_Byte(void)
{
 WORD TimeOut=0;
 BYTE RxBuffer;
 while(!I2C3STATbits.RBF&& TimeOut++<5)Delay_uS(20);
 RxBuffer=I2C3RCV;	
 return RxBuffer;
 
}
BYTE I2C23Master_Poll_Slave(BYTE Address)
{
//	Address|=1;
	I2C3_startBit();
 	I2C3_Idle_Bus(); 
	I2C3_Send_Byte(Address);
	Delay_uS(20);		
	if(I2C3_Is_AckBit())
		return 1;
	else return 0;
}

void Flush_I2C3RxBuffer(void)
{
 BYTE c;
 for(c=0;c<MAX_I2C3_RXBUFF;c++)
 I2C3_dataBuffer[c]=0;
 I2C3_dataBuffer_Cnt=0;
}
BYTE *Return_I2C3RxBuffer(void)
{
	return &I2C3_dataBuffer[0];
}
void __attribute__((interrupt,no_auto_psv)) _Interrupt85 (void)
{
 I2C3_Flag=1;
 IFS5bits.MI2C3IF=0;
}
void I2C3_Open (void)
{
	I2C3CONbits.I2CEN=1;			//enable pin 5 (SCL3) and pin 4(SDA3) as I2C pin
	Delay_uS(20);
}

void I2C3_Close(void)
{
	I2C3CONbits.I2CEN=0;			//enable pin 5 (SCL3) and pin 4(SDA3) as I2C pin
	Delay_uS(20);
}
