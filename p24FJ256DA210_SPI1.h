#ifndef __P24FJ256DA210_SPI1_H
#define __P24FJ256DA210_SPI1_H

#define MAX_SPI1_RXBUFF  	254

void Initialize_SPI1_Module (void);
void SPI1_TxByte(BYTE *Data, BYTE dataLength);
void SPI1_Tx_Only(BYTE *Data, BYTE dataLength);
void SPI1_RxByte(void);
void __attribute__((interrupt,no_auto_psv)) _SPI1Interrupt(void);
BYTE *Return_SPI1_RxBuffer(void);
BYTE Return_SPI1_RxBuffer_Cnt (void);
void Flush_SPI1_RxBuffer(void);
void __Enable_SPI1Master_Interrupt(void);
void __Disable_SPI1Master_Interrupt(void);
void Set_CS_LTC2439 (void);
void Reset_CS_LTC2439 (void);
void Restart_SPI1(void);
void SetEdgeActiveToIdle(void);
void SetEdgeIdleToActive(void);


#endif

