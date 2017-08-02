/**
p24FJ256DA210_UART2.c


**/
// local includes
#include "HardwareProfile.h"
#include "p24FJ256DA210_UART2.h"

//global variable
BYTE U2RxBuffer[MAX_U2RXBUFFER];
BYTE U2RxBuf_Counter=0;

void Initialize_UART2_Module (void)
{
	TRISGbits.TRISG9     =  0;  // To make as output for RS485 - O2 - interface
	LATGbits.LATG9 	  	 =  0;     // Drive low by default
	


	U2BRG=BAUD_LOSPEED_9600;//BAUD_LOSPEED_115200;//BAUD_HISPEED_115200// BAUD_LOSPEED_9600;
	U2MODEbits.PDSEL = 0b00; 	// 8bit no parity
	U2MODEbits.STSEL = 0;		// one stop bit	
	
	IEC1bits.U2RXIE = 1;		// enable rx recieved data interrupt	
	IPC7bits.U2RXIP=0b110; //receive interrupt level 6
	
	U2STAbits.UTXISEL1 = 0b00;		
	U2STA &= 0xDFFF;			// clear TXINV by bit masking
	U2STAbits.UTXBRK = 0;		// sync break tx is disabled

	U2STAbits.URXISEL = 0b00;	// interrupt flag bit is set when RXBUF is filled whith 1 character
	U2STAbits.ADDEN = 0;		// address detect mode is disabled

	
	U2MODEbits.USIDL = 0;		// Continue operation at Idlestate
	U2MODEbits.IREN = 0;		// IrDA En/Decoder is disabled
	U2MODEbits.RTSMD = 0; 		// flow control mode
	U2MODEbits.UEN = 0b00;		// UTX, RTX are enabled and on use.
	U2MODEbits.WAKE = 1;		// Wake-up on start bit is disabled
	U2MODEbits.LPBACK = 0;		// Loop-back is disabled - amit enabled for testing purpose.
	U2MODEbits.ABAUD = 0;		// auto baud is disabled
	U2MODEbits.RXINV = 0;		// No RX inversion
	
	U2MODEbits.UARTEN = 1;		// UART2 is Enabled
	U2STAbits.UTXEN = 1;		//transmit  is enabled
	

		


	//IFS1bits.U2RXIF = 0;		// clear interrupt flag of rx
	
//	U2MODE=0x8088;  //enable uart for  8 bit data, no parity, 1 stop bit with inversion bits
//
//
//	
//	
//	
//	U2STA=0;
//	
//	
//	
//	U2STAbits.UTXEN=1;//enable uC UART2 TX
//	IEC1bits.U2RXIE=1;//enable receive interrupt.
//	IFS1bits.U2RXIF=0;//clear receive interrupt flag
//	IFS1bits.U2TXIF=0;//clear receive interrupt flag
//	//U2MODE|=0x0040;  //enable loop back mode

	
	
	

	

}

void U5_Chip_TxEnable (void)
{
	
	LATG|=0x0200;
}
void U5_Chip_RxEnable (void)
{
     
	LATG&=~(0x0200);
	
}
void UART2_TxByte(char Data)
{
   U5_Chip_TxEnable();	
   Delay_UART2(2000);	
   U2TXREG=Data;
   while(U2STAbits.UTXBF); //wait for buffer to be empty
   Delay_UART2(2000);
   U5_Chip_RxEnable();	
		
}

void UART2_TxString(char *String)
{
	
  U5_Chip_TxEnable();	
  Delay_UART2(2000);
	while(*String!='\0')
	{
		UART2_TxByte(*String);
		while(U2STAbits.UTXBF); //wait for buffer to be empty
		Delay_UART2(2000);
		String++;
	}
   
   	U5_Chip_RxEnable();	

}
void UART2_TxData(BYTE *Data, BYTE dataLength)
{
	U5_Chip_TxEnable();
	Delay_UART2(2000);
	while(dataLength>0)
	{
	   	
		U2TXREG=*Data;
		while(U2STAbits.UTXBF);
		while(!U2STAbits.TRMT);
		//Delay_UART2(2000);
   		Data++;
		dataLength--;
	}
	U5_Chip_RxEnable();	
}
//{
//	U5_Chip_TxEnable();
//	Delay_UART2(5000);
//	while(dataLength>0)
//	{
//	   	U3TXREG=*Data;
//		while(U3STAbits.UTXBF);
//		Delay_UART2(5000);
//   		Data++;
//		dataLength--;
//	}
//	U5_Chip_RxEnable();	
//}
//{
//	U5_Chip_TxEnable();
//	Delay_UART2(5000);
//	while(dataLength>0)
//	{
//	   	U4TXREG=*Data;
//		while(U4STAbits.UTXBF);
//		Delay_UART2(5000);
//   		Data++;
//		dataLength--;
//	}
//	U5_Chip_RxEnable();	
//}
BYTE UART2_PollByte (void)
{
	if(U2STAbits.URXDA)	{
			U2RxBuffer[U2RxBuf_Counter]=U2RXREG;
			if(U2RxBuf_Counter<MAX_U2RXBUFFER)U2RxBuf_Counter++;
			else U2RxBuf_Counter=0;
		}	
 return U2RxBuf_Counter;
}
//{
// if(U3STAbits.URXDA)	{
//			U2RxBuffer[U2RxBuf_Counter]=U3RXREG;
//			if(U2RxBuf_Counter<MAX_U2RXBUFFER)U2RxBuf_Counter++;
//			else U2RxBuf_Counter=0;
//		}	
// return U2RxBuf_Counter;
//}
//{
// if(U4STAbits.URXDA)	{
//			U2RxBuffer[U2RxBuf_Counter]=U4RXREG;
//			if(U2RxBuf_Counter<MAX_U2RXBUFFER)U2RxBuf_Counter++;
//			else U2RxBuf_Counter=0;
//		}	
// return U2RxBuf_Counter;
//}

void __attribute__ ((interrupt,auto_psv)) _U2RXInterrupt (void)
{
	//char ReceivedChar=0;
	
	IFS1bits.U2RXIF=0;//clear receive interrupt flag
	
	if(U2STAbits.URXDA==1)
		{
			//ReceivedChar=U2RXREG;
			//UART2_TxByte(ReceivedChar);			
			U2RxBuffer[U2RxBuf_Counter]=U2RXREG;
			if(U2RxBuf_Counter<MAX_U2RXBUFFER)U2RxBuf_Counter++;
			else U2RxBuf_Counter=0;
		}	

	
		
}
void Flush_U2RxBuffer(void)
{
	BYTE c;
	for(c=0;c<MAX_U2RXBUFFER;c++)
		U2RxBuffer[c]=0;
	U2RxBuf_Counter=0;	
}

BYTE *Return_U2RxBuffer (void)
{
	return &U2RxBuffer[0];	
}

BYTE Return_U2RxBufferCounter (void)
{
	return 	U2RxBuf_Counter;
}

void Delay_UART2(LONG Delay)
{
  while (Delay--);
 
}

