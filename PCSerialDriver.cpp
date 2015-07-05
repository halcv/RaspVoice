#include "PCSerialDriver.h"
#include "PCCommandProcess.h"
#include "Board.h"

static UI_8 st_ucRxBuff[PC_BUFF_SIZE];
static UI_8 st_ucTxBuff[PC_BUFF_SIZE];

static S_BUFF_INFO st_sTxBuffInfo;
static S_BUFF_INFO st_sRxBuffInfo;

static INT iPCSerialDriver_WriteDataRxBuff(UI_8 ucData);
static INT iPCSerialDriver_ReadDataTxBuff(UI_8* pData);

VOID vPCSerialDriver_Initialize()
{
	Serial.begin(PC_SERIAL_BAUDRATE);
	vPCSerialDriver_RxBuffClear();
	vPCSerialDriver_TxBuffClear();
}

VOID vPCSerialDriver_RxBuffClear()
{
	st_sRxBuffInfo.iRemain = 0;
	st_sRxBuffInfo.iRead = 0;
	st_sRxBuffInfo.iWrite = 0;
}

VOID vPCSerialDriver_TxBuffClear()
{
	st_sTxBuffInfo.iRemain = 0;
	st_sTxBuffInfo.iRead = 0;
	st_sTxBuffInfo.iWrite = 0;
}

VOID vPCSerialDriver_Read()
{
	if (Serial.available() > 0) {
		UI_8 ucData = Serial.read();
		iPCSerialDriver_WriteDataRxBuff(ucData);
		if (ucData == '\n') {
            vPCCommandProcess_RequestReceiveComplete();
		}
	}
}

VOID vPCSerialDriver_Write()
{
	UI_8 ucData;
	if (iPCSerialDriver_ReadDataTxBuff(&ucData)) {
		Serial.write(ucData);
	}
}

INT iPCSerialDriver_WriteDataRxBuff(UI_8 ucData)
{
	int iRet = 0;
	if (st_sRxBuffInfo.iRemain < PC_BUFF_SIZE) {
		iRet = 1;
		st_ucRxBuff[st_sRxBuffInfo.iWrite] = ucData;
		st_sRxBuffInfo.iRemain++;
		st_sRxBuffInfo.iWrite++;
		if (st_sRxBuffInfo.iWrite >= PC_BUFF_SIZE) {
			st_sRxBuffInfo.iWrite = 0;
		}
	}

	return iRet;
}

INT iPCSerialDriver_ReadDataRxBuff(UI_8* pData)
{
	INT iRet = 0;
	if (st_sRxBuffInfo.iRemain > 0) {
		iRet = 1;
		*pData = st_ucRxBuff[st_sRxBuffInfo.iRead];
		st_sRxBuffInfo.iRemain--;
		st_sRxBuffInfo.iRead++;
		if (st_sRxBuffInfo.iRead >= PC_BUFF_SIZE) {
			st_sRxBuffInfo.iRead = 0;
		}
	}
	
	return iRet;
}

INT iPCSerialDrier_WriteDataTxBuff(UI_8 ucData)
{
	INT iRet = 0;
	if (st_sTxBuffInfo.iRemain < PC_BUFF_SIZE) {
		iRet = 1;
		st_ucTxBuff[st_sTxBuffInfo.iWrite] = ucData;
		st_sTxBuffInfo.iRemain++;
		st_sTxBuffInfo.iWrite++;
		if (st_sTxBuffInfo.iWrite >= PC_BUFF_SIZE) {
			st_sTxBuffInfo.iWrite = 0;
		}
	}
	return iRet;
}

INT iPCSerialDriver_ReadDataTxBuff(UI_8* pData)
{
	INT iRet = 0;
	if (st_sTxBuffInfo.iRemain > 0) {
		iRet = 1;
		*pData = st_ucTxBuff[st_sTxBuffInfo.iRead];
		st_sTxBuffInfo.iRemain--;
		st_sTxBuffInfo.iRead++;
		if (st_sTxBuffInfo.iRead >= PC_BUFF_SIZE) {
			st_sTxBuffInfo.iRead = 0;
		}
	}

	return iRet;
}

VOID vPCSerialDriver_PutStr(const CHAR* pData)
{
	while(*pData != 0) {
		iPCSerialDriver_WriteDataTxBuff(*pData);
		pData++;
	}
}
