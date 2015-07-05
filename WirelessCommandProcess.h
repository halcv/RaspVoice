#ifndef _WIRELESS_COMMAND_PROCESS_H_
#define _WIRELESS_COMMAND_PROCESS_H_

#include "MySystype.h"
#include "Board.h"

VOID vWirelessCommandProcess_Initialize();
VOID vWirelessCommandProcess_Main();
VOID vWirelessCommandProcess_RequestReceiveComplete();
VOID vWirelessCommandProcess_RequestTransmit();
E_STATE eWirelessCommandProcess_GetState();

#endif // _WIRELESS_COMMAND_PROCESS_H_
