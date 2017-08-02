#ifndef __LTC2439_H
#define __LTC2439_H
//----LTC2439 data format---//
// Bit18	| Bit 17 	| Bit 16	| Bit 15	|...|....|Bit 0
//  /EOC	| (0)	| SIG	|  MSB	|...|....|LSB or NExt/EOC
// SPI Buff 0 = SPI_b7	| SPI_b6	| SPI_b5	| SPI_b4	| SPI_b3	| SPI_b2 |SPI_b1	| SPI_b0
// 			   bit18	   bit17	   bit16 	| bit15	| bit14	| bit13	| bit12	| bit11
// SPI Buff 1 = SPI_b7	| SPI_b6	| SPI_b5	| SPI_b4	| SPI_b3	| SPI_b2 |SPI_b1	| SPI_b0
// 			   bit10	   bit9	   bit8 	| bit7	| bit6	| bit5	| bit4	| bit3
// SPI Buff 2 = SPI_b7	| SPI_b6	| SPI_b5	| SPI_b4	| SPI_b3	| SPI_b2 |SPI_b1	| SPI_b0
// 			   bit2	   bit1	   bit0 	



#define MAX_LTC2439_BUFF	3
#define LTC2439_RESP_BYTES	7		//19 bits
#define COM_PIN				32767   //2.5 Volt common
#define EOC			0x80  //'0' means end of conversion
 	

#define EN			0x20  //new channel selection
#define SGL			0x10  //'1' is single ended, '0' is differential	
//single ended channnel
#define CH0			0x00
#define CH2			0x01		
#define CH4			0x02
#define CH6			0x03			
#define CH8			0x04
#define CH10		0x05
#define CH12		0x06
#define CH14		0x07
#define CH1			0x08
#define CH3			0x09
#define CH5			0x0A
#define CH7			0x0B
#define CH9			0x0C
#define CH11		0x0D
#define CH13		0x0E
#define CH15		0x0F


WORD Read_SingleEndedLTC2439(BYTE channel);
WORD Parse_LTC2439Data(void);
WORD Get_MedianLTC2439Data(void);


BYTE Test_EOC(void);

#endif
