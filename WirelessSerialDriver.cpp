#include "WirelessSerialDriver.h"
#include "WirelessCommandProcess.h"
#include "Board.h"

static UI_8 st_ucRxBuff[WIRELESS_BUFF_SIZE];
static UI_8 st_ucTxBuff[WIRELESS_BUFF_SIZE];

static S_BUFF_INFO st_sTxBuffInfo;
static S_BUFF_INFO st_sRxBuffInfo;

static INT iWirelessSerialDriver_WriteDataRxBuff(UI_8 ucData);
static INT iWirelessSerialDriver_ReadDataTxBuff(UI_8* pData);

VOID vWirelessSerialDriver_Initialize()
{
	Serial1.begin(WIRELESS_SERIAL_BAUDRATE);
	vWirelessSerialDriver_RxBuffClear();
	vWirelessSerialDriver_TxBuffClear();
}

VOID vWirelessSerialDriver_RxBuffClear()
{
	st_sRxBuffInfo.iRemain = 0;
	st_sRxBuffInfo.iRead = 0;
	st_sRxBuffInfo.iWrite = 0;
}

VOID vWirelessSerialDriver_TxBuffClear()
{
	st_sTxBuffInfo.iRemain = 0;
	st_sTxBuffInfo.iRead = 0;
	st_sTxBuffInfo.iWrite = 0;
}

VOID vWirelessSerialDriver_Read()
{
	if (Serial1.available() > 0) {
		UI_8 ucData = Serial1.read();
		iWirelessSerialDriver_WriteDataRxBuff(ucData);
		if (ucData == '\n') {
            vWirelessCommandProcess_RequestReceiveComplete();
		}
	}
}

VOID vWirelessSerialDriver_Write()
{
	UI_8 ucData;
	if (iWirelessSerialDriver_ReadDataTxBuff(&ucData)) {
		Serial1.write(ucData);
	}
}

static INT iWirelessSerialDriver_WriteDataRxBuff(UI_8 ucData)
{
	int iRet = 0;
	if (st_sRxBuffInfo.iRemain < WIRELESS_BUFF_SIZE) {
		iRet = 1;
		st_ucRxBuff[st_sRxBuffInfo.iWrite] = ucData;
		st_sRxBuffInfo.iRemain++;
		st_sRxBuffInfo.iWrite++;
		if (st_sRxBuffInfo.iWrite >= WIRELESS_BUFF_SIZE) {
			st_sRxBuffInfo.iWrite = 0;
		}
	}

	return iRet;
}

INT iWirelessSerialDriver_ReadDataRxBuff(UI_8* pData)
{
	INT iRet = 0;
	if (st_sRxBuffInfo.iRemain > 0) {
		iRet = 1;
		*pData = st_ucRxBuff[st_sRxBuffInfo.iRead];
		st_sRxBuffInfo.iRemain--;
		st_sRxBuffInfo.iRead++;
		if (st_sRxBuffInfo.iRead >= WIRELESS_BUFF_SIZE) {
			st_sRxBuffInfo.iRead = 0;
		}
	}
	
	return iRet;
}

INT iWirelessSerialDriver_WriteDataTxBuff(UI_8 ucData)
{
	INT iRet = 0;
	if (st_sTxBuffInfo.iRemain < WIRELESS_BUFF_SIZE) {
		iRet = 1;
		st_ucTxBuff[st_sTxBuffInfo.iWrite] = ucData;
		st_sTxBuffInfo.iRemain++;
		st_sTxBuffInfo.iWrite++;
		if (st_sTxBuffInfo.iWrite >= WIRELESS_BUFF_SIZE) {
			st_sTxBuffInfo.iWrite = 0;
		}
	}
	return iRet;
}

static INT iWirelessSerialDriver_ReadDataTxBuff(UI_8* pData)
{
	INT iRet = 0;
	if (st_sTxBuffInfo.iRemain > 0) {
		iRet = 1;
		*pData = st_ucTxBuff[st_sTxBuffInfo.iRead];
		st_sTxBuffInfo.iRemain--;
		st_sTxBuffInfo.iRead++;
		if (st_sTxBuffInfo.iRead >= WIRELESS_BUFF_SIZE) {
			st_sTxBuffInfo.iRead = 0;
		}
	}

	return iRet;
}

VOID vWirelessSerialDriver_PutStr(const CHAR* pData)
{
	while(*pData != 0) {
		iWirelessSerialDriver_WriteDataTxBuff(*pData);
		pData++;
	}
}
