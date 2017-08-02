#ifndef __P24FJ256DA210_I2C3_H
#define __P24FJ256DA210_I2C3_H

#define NACK				1
#define ACK     			0
#define OMB_ADDRESS 		0x90
#define READ				0x01
#define WRITE				0x00
#define MAX_I2C3_RXBUFF     30



void Initialize_I2C3_Module( void );
void I2C3_startBit(void);
void I2C3_Idle_Bus(void);
void I2C3_REstartBit(void);
void I2C3_stopBit(void);
BYTE I2C3_Is_AckBit(void);
void I2C3_Send_Byte(BYTE Data);
void I2C3_Send_Ack(void);
void I2C3_Send_NAck(void);
void I2C3_MasterReceive_Enable(void);
BYTE I2C3_Receive_Byte(void);
void I2C3_Send_Byte(BYTE Data);
BYTE I2C23Master_Poll_Slave(BYTE Address);
void I2C3Master_Read_Data(BYTE *DataTx, BYTE *DataRx, BYTE TxLen, BYTE RxLen);
void Flush_I2C3RxBuffer(void);
BYTE *Return_I2C3RxBuffer(void);
void __attribute__((interrupt,no_auto_psv)) _Interrupt85(void);
void I2C3_Open (void);
void I2C3_Close (void);

#endif


