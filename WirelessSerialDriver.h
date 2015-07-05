#ifndef _WIRELESS_SERIAL_DRIVER_H_
#define _WIRELESS_SERIAL_DRIVER_H_

#include "MySystype.h"

VOID vWirelessSerialDriver_Initialize();
VOID vWirelessSerialDriver_Read();
VOID vWirelessSerialDriver_Write();
INT iWirelessSerialDriver_WriteDataTxBuff(UI_8 ucData);
INT iWirelessSerialDriver_ReadDataRxBuff(UI_8* pData);
VOID vWirelessSerialDriver_PutStr(const CHAR *pData);
VOID vWirelessSerialDriver_RxBuffClear();
VOID vWirelessSerialDriver_TxBuffClear();

#endif // _WIRELESS_SERIAL_DRIVER_H_
