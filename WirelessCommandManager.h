#ifndef _WIRELESS_COMMAND_MANAGER_H_
#define _WIRELESS_COMMAND_MANAGER_H_

#include "MySystype.h"

VOID vWirelessCommandManager_Initialize();
VOID vWirelessCommandManager_ClearTransmitData();
VOID vWirelessCommandManager_ClearReceiveData();
VOID vWirelessCommandManager_CreateTransmitData(UI_8* pucData);
UI_8* pucWirelessCommandManager_GetReceiveData();
UI_8* pucWirelessCommandManager_GetTransmitData();

#endif // _WIRELESS_COMMAND_MANAGER_H_
