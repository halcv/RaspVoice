#include "WirelessCommandManager.h"
#include "WirelessSerialDriver.h"
#include "Board.h"

static UI_8 st_ucTransmitData[WIRELESS_BUFF_SIZE];
static UI_8 st_ucReceiveData[WIRELESS_BUFF_SIZE];

VOID vWirelessCommandManager_Initialize()
{
    vWirelessCommandManager_ClearTransmitData();
    vWirelessCommandManager_ClearReceiveData();
}

VOID vWirelessCommandManager_ClearTransmitData()
{
    for (INT i = 0;i < WIRELESS_BUFF_SIZE;i++) {
        st_ucTransmitData[i] = 0;
    }
    st_ucTransmitData[E_TRANSMIT_DATA_POS_PREFIX]   = '@';
    st_ucTransmitData[E_TRANSMIT_DATA_POS_COMMAND1] = 'D';
    st_ucTransmitData[E_TRANSMIT_DATA_POS_COMMAND2] = 'T';
}

VOID vWirelessCommandManager_ClearReceiveData()
{
    for (INT i = 0;i < WIRELESS_BUFF_SIZE;i++) {
        st_ucReceiveData[i] = 0;
    }
}

VOID vWirelessCommandManager_CreateTransmitData(UI_8* pucData)
{
    vWirelessCommandManager_ClearTransmitData();
     INT iLength = strlen((char*)pucData) - 2; // "\r\n"の２文字分は除外
     UI_8 ucTemp[3];
    sprintf((char*)ucTemp,"%02X",iLength);
    st_ucTransmitData[E_TRANSMIT_DATA_POS_LENGTH1] = ucTemp[0];
    st_ucTransmitData[E_TRANSMIT_DATA_POS_LENGTH2] = ucTemp[1];
    strcpy((char*)(st_ucTransmitData + E_TRANSMIT_DATA_POS_DATA),(char*)pucData);
    vWirelessSerialDriver_PutStr((CHAR*)st_ucTransmitData);
}

UI_8* pucWirelessCommandManager_GetReceiveData()
{
    return st_ucReceiveData;
}

UI_8* pucWirelessCommandManager_GetTransmitData()
{
    return st_ucTransmitData;
}
