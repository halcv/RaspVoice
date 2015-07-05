#include "PCCommandProcess.h"
#include "PCCommandManager.h"
#include "PCSerialDriver.h"
#include "WirelessCommandProcess.h"
#include "Board.h"

static BOOL st_isReceiveComplete;

VOID vPCCommandProcess_Initialize()
{
    st_isReceiveComplete = false;
    vPCCommandManager_Initialize();
}

VOID vPCCommandProcess_Main()
{
    if (st_isReceiveComplete == false) {
        return;
    }
    st_isReceiveComplete = false;

    vPCCommandManager_ClearCommandData();
    UI_8 ucData = 0;
    UI_8* pucData = pucPCCommandManager_GetCommandData();
    do {
        iPCSerialDriver_ReadDataRxBuff(&ucData);
        *pucData = ucData;
        pucData++;
    } while (ucData != '\n');
    vPCSerialDriver_RxBuffClear();
    vPCCommandManager_BackupCommandData();
    vWirelessCommandProcess_RequestTransmit();
}
VOID vPCCommandProcess_RequestReceiveComplete()
{
    if (eWirelessCommandProcess_GetState() == E_STATE_NONE) {
        st_isReceiveComplete = true;
    }
}
