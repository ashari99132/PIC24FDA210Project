#ifndef __P24FJ256DA210_I2C1_H
#define __P24FJ256DA210_I2C1_H
#define 	OMB_I2C1_ADD 		(0x90)>>1


#define MAX_I2C1_RXBUFF         16
#define MAX_I2C1_TXBUFF         200

void Initialize_I2C1_Module (void);
void __Disable_I2C1Slave_Interrupt(void);
void __Enable_I2C1Slave_Interrupt(void);
void __Set_I2C1Slave_Interrupt(void);
void __Clear_I2C1Slave_Interrupt(void);
void Tx_I2C1SlaveData(void);
void __attribute__((interrupt,no_auto_psv)) _SI2C1Interrupt (void);
BYTE *ReturnI2C1_RxDataBuffer(void);
BYTE *ReturnI2C1_TxBuffer(void);
BYTE ReturnCounter_I2C1RxBuffer(void);
BYTE ReturnCounter_I21TxBuffer(void);
void Flush_I2C1RxBuffer (void);

#endif




