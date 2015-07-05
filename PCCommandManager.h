#ifndef _PC_COMMAND_MANAGER_H_
#define _PC_COMMAND_MANAGER_H_

#include "MySystype.h"

VOID vPCCommandManager_Initialize();
VOID vPCCommandManager_ClearCommandData();
UI_8* pucPCCommandManager_GetCommandData();
VOID vPCCommandManager_BackupCommandData();

#endif // _PC_COMMAND_MANAGER_H_
