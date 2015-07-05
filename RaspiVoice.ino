#include <Metro.h>
#include "MySystype.h"
#include "UartProcess.h"
#include "PCCommandProcess.h"
#include "WirelessCommandProcess.h"
#include "MainTimer.h"
#include "PortManager.h"

static VOID vMain_Init();

VOID setup()
{
    vMain_Init();
}

VOID loop()
{
    vMainTimer_Main();
    vUartProcess_Main();
    vPCCommandProcess_Main();
    vWirelessCommandProcess_Main();
}

static VOID vMain_Init()
{
    vPortManager_Initialize();
    vUartProcess_Initialize();
    vPCCommandProcess_Initialize();
    vWirelessCommandProcess_Initialize();
    vMainTimer_Initialize();
}
