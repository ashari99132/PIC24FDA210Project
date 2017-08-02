/**
p24FJ256DA210_UART1.c


**/
// local includes
#include "HardwareProfile.h"
#include "p24FJ256DA210_UART1.h"

//global variable
BYTE U1RxBuffer[MAX_U1RXBUFFER];
BYTE U1RxBuf_Counter=0;
void Initialize_UART1_Module (void)
{
	
	U1BRG=BAUD_LOSPEED_19200;//(BAUD_LOSPEED_115200); 
	IPC2bits.U1RXIP=0b011; //receive interrupt level 2
	
	
	U1STA=0;
	U1MODE=0x8000;  //enable uart for  8 bit data, no parity, 1 stop bit
	
	U1STAbits.UTXEN=1;//enable uC UART1 TX
	IEC0bits.U1RXIE=1;//enable receive interrupt.
	IFS0bits.U1RXIF=0;//clear receive interrupt flag
	
	TRISC&=~(0x2000); //specific board for chip enable. .
	LATCbits.LATC13=0; 	 
}

void U4_Chip_TxEnable (void)
{
  
  LATCbits.LATC13=1; 	 //TX_ENABLE	
}
void U4_Chip_RxEnable  (void)
{  
  LATCbits.LATC13=0; 	 //RX_ENABLE		
}


void UART1_TxByte(char Data)
{
  U4_Chip_TxEnable();
  Delay_UART1(5000);
  U1TXREG=Data;
  while(U1STAbits.UTXBF); //wait for buffer to be empty
  Delay_UART1(5000);	
  U4_Chip_RxEnable();	
}

void UART1_TxString(char *String)
{
	U4_Chip_TxEnable();
	Delay_UART1(5000);
	while(*String!='\0')
	{
	   	
		U1TXREG=*String;
		while(U1STAbits.UTXBF);
	   	Delay_UART1(5000);
		String++;
	}
	U4_Chip_RxEnable();	
}
void UART1_TxData(BYTE *Data, BYTE dataLength)
{
	U4_Chip_TxEnable();
	Delay_UART1(5000);
	while(dataLength>0)
	{
	   	
		U1TXREG=*Data;
		while(U1STAbits.UTXBF);
		Delay_UART1(5000);
   		Data++;
		dataLength--;
	}
	U4_Chip_RxEnable();	
}

void __attribute__ ((interrupt,no_auto_psv)) _U1RXInterrupt (void)
{
	IFS0bits.U1RXIF=0;//clear receive interrupt flag
	if(U1STAbits.URXDA)
		{
			U1RxBuffer[U1RxBuf_Counter]=U1RXREG;
			if(U1RxBuf_Counter<MAX_U1RXBUFFER)U1RxBuf_Counter++;
			else U1RxBuf_Counter=0;
			
		}	
	
		
}

void Flush_U1RxBuffer(void)
{
	BYTE c;
	for(c=0;c<MAX_U1RXBUFFER;c++)
		U1RxBuffer[c]=0;
	U1RxBuf_Counter=0;	
}

BYTE *Return_U1RxBuffer (void)
{
	return &U1RxBuffer[0];	
}

BYTE Return_U1RxBufferCounter (void)
{
	return 	U1RxBuf_Counter;
}

void Delay_UART1(LONG Delay)
{
  while (Delay--);
 
}
