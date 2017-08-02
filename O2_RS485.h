#ifndef __O2_RS485_H
#define __O2_RS485_H
#define OXYRS485_ADDR          1
#define MAX_O2RS485_REG		5
////Modbus function
#define READ_INPUT_REGISTER 0x04
#define READ_HOLDING_REGISTER 0x03
#define WRITE_HOLDING_REGISTER 0x06
//
////DS0058 OXY LC TABLE REGISTER  -- INPUT REGISTER
#define O2_AVERAGE      0x7531        //2070 means 20.7%
#define O2_RAW          0x7532
#define O2_ASSYMETRY       0x7533
#define O2_SYTEM_STATUS    0x7534
  //value for SYTEM_STATUS    
   #define O2RS485_IDLE          0
   #define O2RS485_START_UP      1
   #define O2RS485_IN_OPERATION  2
   #define O2RS485_SHUT_DOWN     3
   #define O2RS485_STANDING_BY   4
#define O2_ERROR_WARNING   0x7535

   #define O2RS485_PUMP_ERROR           0x01
   #define O2RS485_HEATER_VOLT_ERROR    0x02
   #define O2RS485_ASSYMETRY_WARNING    0x04
   #define O2_BELOW_PT1_WARNING 0x08

#define O2_HEATER_VOLTAGE  0x7536 
#define O2_PRESSURE        0x7540 
#define O2_TEMPERATURE     0x7541      //value is 2's complement
#define O2_CALIB_STATUS    0x7542



////DS0058 OXY LC TABLE REGISTER  -- HOLDING  REGISTER
 #define O2RS485_SENSOR_POWER     0x9C41
//  //value for SENSOR_POWER
   #define SENSOR_OFF    0
   #define SENSOR_ON     1
   #define SENSOR_STANDY 2
#define O2_CLEAR_ERR_FLAG    0x9C42
//  //value for CLEAR_ERR_FLAG
   #define O2_IDLE          0
   #define O2_CLEAR         1  
//#define O2_SHUTDOWN_DELAY    0x9C43      //0-65535 seconds
#define O2_CALIB_CONTROL     0x9C44
//  //value for CALIB_CONTROL     
   #define DFLT_COND            0
   #define ACTIVE_COND          1
   #define RESET_STATUS_CALIB   2
#define O2_CALIB_VALUE       0x9C45      //0-65535 (2070 is 20.7%)
//#define O2_ADDRESS_DEVICE    0x9C46      //1-247  (default is 1)
//#define O2_BAUD_DEVICE       0x9C47      //default is 2
//  //value BAUD_DEVICE       
//   #define BAUD_2400            0
//   #define BAUD_4800            1
//   #define BAUD_9600            2
//   #define BAUD_19200           3           
//   #define BAUD_38400           4 
//   #define BAUD_57600           5 
//   #define BAUD_115200          6  
//#define O2_PARITY_DEVICE     0x9C48    //default 0
//  //value for PARITY_DEVICE     
//   #define NONE                 0
//   #define ODD                  1
//   #define EVEN                 2
//#define O2_STOPBIT_DEVICE    0x9C49
//    //value STOPBIT_DEVICE    
//   #define NONE                 0
//   #define ODD                  1
//   #define EVEN                 2
//#define O2_RS485COM_SAVEDATA 0x9C4A
//#define O2_APPLIED_HEATER_VOLTAGE    0x9C4B
//#define O2_HEATER_SAVEDATA   0x9C4C
//    //value HEATER_SAVEDATA   
//   #define VOLT_400               0
//   #define VOLT_420               1
//   #define VOLT_435               2
//   #define VOLT_455               2
//
//#define SAVE_DATA 2
void Initialize_O2RS485 (void);
void EventUpdateRS485O2Sensor (void);
void EventWriteRS485O2Sensor(WORD startRegister, WORD Value);
void Stop_O2RS485 (void);
void Calibrate_O2RS485 (WORD Value);
void RS485O2SensorCmd(BYTE function, WORD startRegister, WORD Parameter);
BYTE RS485_ProcessFrame(BYTE function, WORD startRegister, WORD Parameter);
BYTE RS485O2_ProcessReadFunc(WORD startRegister, WORD RegLength);
BYTE RS485O2_ProcessWriteFunc(WORD startRegister, WORD Value);
WORD returnO2RS485RegIndex (WORD RegAddress);
void EventUpdateRS485O2Sensor_RxUpdate(void);

#endif
