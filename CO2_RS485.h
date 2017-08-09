#ifndef __CO2_RS485_H
#define __CO2_RS485_H

#define MAX_CO2RS485_BUFF     8
#define CO2RS485_INVALID_READ_MAX_CNT   30
void EventUpdateRS485CO2Sensor (void);
void EventRS485CO2Sensor_RxUpdate (void);


#endif
