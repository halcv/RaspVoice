#ifndef _RECEIVE_TIMEOUT_TIMER_H_
#define _RECEIVE_TIMEOUT_TIMER_H_

#include "MySystype.h"

VOID vReceiveTimeoutTimer_Initialize();
VOID vReceiveTimeoutTimer_IncTime();
BOOL isReceiveTimeoutTimer_CheckTime();
VOID vReceiveTimeoutTimer_Start();
VOID vReceiveTimeoutTimer_Stop();

#endif // _RECEIVE_TIMEOUT_TIMER_H_
