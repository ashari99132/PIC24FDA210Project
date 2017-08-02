#ifndef __EVENTTCPIP_H
#define __EVENTTCPIP_H

#define UDP_LOCAL_PORT				9051
#define UDP_VOYAGER_PORT  			8923
#define TCP_VOYAGER_PORT			8348
#define DUMMY_ADDR_VOYAGER			0x02
#define MAX_NUMBER_OF_REG_FORTCPIP 	21
typedef union Pdu_ModBus_Rx{
BYTE bytes[8];
struct{
		BYTE Address;
		BYTE Function;
		BYTE RegAddress_Hi;
		BYTE RegAddress_Lo;
		BYTE Value_Hi;
		BYTE Value_Lo;
		BYTE CRC_Lo;
		BYTE CRC_Hi;	
	};
}MODBUSPDU_RX;


typedef struct Pdu_Modbus_Tx{
BYTE DataLen;
BYTE Data[50];
}MODBUSPDU_TX,*pMODBUSPDU_TX;

void EventTCPIP (void);
void InitAppConfig(void);
void DisplayIPValue(IP_ADDR IPVal);
void TPCIP_Voyager_Init_Task (void);
void TPCIP_Voyager_Task (void);
void ProcessModBus_TCPIP(pMODBUSPDU_TX TxBuffer);
void Process_ModbusTCP_ReadFunction(pMODBUSPDU_TX TxBuffer);
void Process_ModbusTCP_WriteFunction(pMODBUSPDU_TX TxBuffer);






#endif
