#include "UartProcess.h"
#include "PCSerialDriver.h"
#include "WirelessSerialDriver.h"

VOID vUartProcess_Initialize()
{
    vPCSerialDriver_Initialize();
    vWirelessSerialDriver_Initialize();
}

VOID vUartProcess_Main()
{
    vPCSerialDriver_Read();
    vPCSerialDriver_Write();
    vWirelessSerialDriver_Read();
    vWirelessSerialDriver_Write();
}
