#include "PCCommandManager.h"
#include "PCSerialDriver.h"
#include "Board.h"

static UI_8 st_ucPCCommandData[PC_BUFF_SIZE];
static UI_8 st_ucPCCommandDataBackup[PC_BUFF_SIZE] = "konnnitiwa\r\n";

static VOID vPCCommandManager_ClearCommandDataBackup();

VOID vPCCommandManager_Initialize()
{
    vPCCommandManager_ClearCommandData();
}

VOID vPCCommandManager_ClearCommandData()
{
    for (INT i = 0;i < PC_BUFF_SIZE;i++) {
        st_ucPCCommandData[i] = 0;
    }
}

UI_8* pucPCCommandManager_GetCommandData()
{
    return st_ucPCCommandData;
}

VOID vPCCommandManager_BackupCommandData()
{
    vPCCommandManager_ClearCommandDataBackup();
    strcpy((char*)st_ucPCCommandDataBackup,(char*)st_ucPCCommandData);
}

static VOID vPCCommandManager_ClearCommandDataBackup()
{
    for (INT i = 0;i < PC_BUFF_SIZE;i++) {
        st_ucPCCommandDataBackup[i] = 0;
    }
}
