#ifndef _PC_SERIAL_DRIVER_H_
#define _PC_SERIAL_DRIVER_H_

#include "MySystype.h"

VOID vPCSerialDriver_Initialize();
VOID vPCSerialDriver_Read();
VOID vPCSerialDriver_Write();
INT iPCSerialDriver_WriteDataTxBuff(UI_8 ucData);
INT iPCSerialDriver_ReadDataRxBuff(UI_8* pData);
VOID vPCSerialDriver_Driver_PutStr(const CHAR *pData);
VOID vPCSerialDriver_RxBuffClear();
VOID vPCSerialDriver_TxBuffClear();

#endif // _PC_SERIAL_DRIVER_H_
