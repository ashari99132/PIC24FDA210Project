#ifndef __EVENTRTC_H
#define __EVENTRTC_H

#define MINUTE		60
#define HOUR		3600
#define TOTAL_EVENT_RTC 8

enum __RTC_Event_Id_ {

IDLE_COMPRESSOR_RTC_ID=0,
UV_RUNTIME_RTC_ID,
GROWLIGHT_RUNTIME_RTC_ID,
NORMAL_MODE_ID,
CTL_ENABLE_ID,
COLD_CTL_ENABLE_ID,
PUMP_ON_ID,
PUMP_OFF_ID,
TEMP_SUPERVISORY
};
void EventRTC (void);
void EventIntRTC (void);
void StartTimerRTC(BYTE rtc_id, BYTE type, WORD period);
void StopTimerRTC(BYTE rtc_id);
BYTE ReturnTimerRTCENDIS(BYTE rtc_id);
#endif
