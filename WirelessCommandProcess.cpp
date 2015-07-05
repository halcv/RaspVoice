#include "WirelessCommandProcess.h"
#include "WirelessCommandManager.h"
#include "WirelessSerialDriver.h"
#include "PCCommandManager.h"
#include "PCSerialDriver.h"
#include "ReceiveTimeoutTimer.h"
#include "SoundNGTimer.h"
#include "PortManager.h"
#include "SoundOKTimer.h"

static BOOL st_isReceiveComplete;
static E_STATE st_eState;
static INT st_iSoundCount;
static const INT st_iSoundTable[SOUND_TABLE_SIZE] = {
    262,294,330,349,392,440,494,523,
    262,294,330,349,392,440,494,523
};

static VOID vWirelessCommandProcess_Transmit();
static VOID vWirelessCommandProcess_ReceiveStart();
static VOID vWirelessCommandProcess_Receive();
static VOID vWirelessCommandProcess_ReceiveOKStart();
static VOID vWirelessCommandProcess_ReceiveOK();
static VOID vWirelessCommandProcess_ReceiveNGStart();
static VOID vWirelessCommandProcess_ReceiveNG();
static VOID vWirelessCommandProcess_CheckCommand();

VOID vWirelessCommandProcess_Initialize()
{
    st_isReceiveComplete = false;
    st_eState = E_STATE_NONE;
    st_iSoundCount = 0;
    vWirelessCommandManager_Initialize();
}

VOID vWirelessCommandProcess_Main()
{
    switch (st_eState) {
    case E_STATE_NONE:
        break;
    case E_STATE_TRANSMIT:
        vWirelessCommandProcess_Transmit();
        break;
    case E_STATE_RECEIVE_START:
        vWirelessCommandProcess_ReceiveStart();
        break;
    case E_STATE_RECEIVE:
        vWirelessCommandProcess_Receive();
        break;
    case E_STATE_RECEIVE_OK_START:
        vWirelessCommandProcess_ReceiveOKStart();
        break;
    case E_STATE_RECEIVE_OK:
        vWirelessCommandProcess_ReceiveOK();
        break;
    case E_STATE_RECEIVE_NG_START:
        vWirelessCommandProcess_ReceiveNGStart();
        break;
    case E_STATE_RECEIVE_NG:
        vWirelessCommandProcess_ReceiveNG();
        break;
    default:
        break;
    }
}

VOID vWirelessCommandProcess_RequestReceiveComplete()
{
    st_isReceiveComplete = true;
}

E_STATE eWirelessCommandProcess_GetState()
{
    return st_eState;
}

VOID vWirelessCommandProcess_RequestTransmit()
{
    st_eState = E_STATE_TRANSMIT;
}

static VOID vWirelessCommandProcess_Transmit()
{
    vWirelessCommandManager_CreateTransmitData(pucPCCommandManager_GetCommandData());
    st_eState = E_STATE_RECEIVE_START;
}

static VOID vWirelessCommandProcess_ReceiveStart()
{
    vReceiveTimeoutTimer_Start();
    st_eState = E_STATE_RECEIVE;
}

static VOID vWirelessCommandProcess_Receive()
{
    if (isReceiveTimeoutTimer_CheckTime() == true) {
        st_eState = E_STATE_RECEIVE_NG_START;
        return;
    }
    
    if (st_isReceiveComplete == false) {
        return;
    }
    st_isReceiveComplete = false;
    vWirelessCommandManager_ClearReceiveData();
    UI_8* pucData = pucWirelessCommandManager_GetReceiveData();
    UI_8 ucData = 0;
    do {
        iWirelessSerialDriver_ReadDataRxBuff(&ucData);
        *(pucData) = ucData;
        pucData++;
    } while (ucData != '\n');
    vWirelessSerialDriver_RxBuffClear();
    vWirelessCommandProcess_CheckCommand();
}

static VOID vWirelessCommandProcess_CheckCommand()
{
    UI_8* pucReceiveData = pucWirelessCommandManager_GetReceiveData();
    UI_8* pucTransmitData = pucWirelessCommandManager_GetTransmitData();
    if (*(pucReceiveData)     == '*' &&
        *(pucReceiveData + 1) == 'D' &&
        *(pucReceiveData + 2) == 'T' &&
        *(pucReceiveData + 3) == '=' &&
        *(pucReceiveData + 4) == *(pucTransmitData + (E_TRANSMIT_DATA_POS_LENGTH1)) &&
        *(pucReceiveData + 5) == *(pucTransmitData + (E_TRANSMIT_DATA_POS_LENGTH2))) {
    } else if (*(pucReceiveData)     == '*' &&
               *(pucReceiveData + 1) == 'D' &&
               *(pucReceiveData + 2) == 'R' &&
               *(pucReceiveData + 3) == '=' &&
               *(pucReceiveData + 4) == '0' &&
               *(pucReceiveData + 5) == '2' &&
               *(pucReceiveData + 6) == 'O' &&
               *(pucReceiveData + 7) == 'K') {
        st_eState = E_STATE_RECEIVE_OK_START;
    } else {
        vReceiveTimeoutTimer_Stop();
        st_eState = E_STATE_RECEIVE_NG_START;
    }
}

static VOID vWirelessCommandProcess_ReceiveOKStart()
{
    st_iSoundCount = 0;
    vSoundOKTimer_Start();
    st_eState = E_STATE_RECEIVE_OK;
}

static VOID vWirelessCommandProcess_ReceiveOK()
{
    if (isSoundOKTimer_CheckTime() == false) {
        return;
    }
    if (st_iSoundCount >= SOUND_TABLE_SIZE) {
        vPortManager_SoundOFF();
        vSoundOKTimer_Stop();
        st_eState = E_STATE_NONE;
    } else {
        vPortManager_SoundON(st_iSoundTable[st_iSoundCount]);
        st_iSoundCount++;
    }
}

static VOID vWirelessCommandProcess_ReceiveNGStart()
{
    vSoundNGTimer_Start();
    vPortManager_SoundON(262);
    st_eState = E_STATE_RECEIVE_NG;
}

static VOID vWirelessCommandProcess_ReceiveNG()
{
    if (isSoundNGTimer_CheckTime() == false) {
        return;
    }

    vPortManager_SoundOFF();
    st_eState = E_STATE_NONE;
}
