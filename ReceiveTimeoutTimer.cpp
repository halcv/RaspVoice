#include "ReceiveTimeoutTimer.h"

#define TIME_MAX    (20) // 20s

static BOOL st_isStart;
static INT st_iTime;
static BOOL st_isTimeout;

VOID vReceiveTimeoutTimer_Initialize()
{
    st_isStart = false;
    st_iTime = 0;
    st_isTimeout = false;
}

VOID vReceiveTimeoutTimer_IncTime()
{
    if (st_isStart == false) {
        return;
    }

    if (st_iTime < (TIME_MAX - 1)) {
        st_iTime++;
    } else {
        st_isTimeout = true;
    }
}

BOOL isReceiveTimeoutTimer_CheckTime()
{
    BOOL isRet = st_isTimeout;
    if (isRet == true) {
        vReceiveTimeoutTimer_Initialize();
    }

    return isRet;
}

VOID vReceiveTimeoutTimer_Start()
{
    st_iTime = 0;
    st_isTimeout = false;
    st_isStart = true;
}

VOID vReceiveTimeoutTimer_Stop()
{
    vReceiveTimeoutTimer_Initialize();
}
