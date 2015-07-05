#include "SoundOKTimer.h"

#define TIME_MAX    (5) // 50ms

static BOOL st_isStart;
static INT st_iTime;
static BOOL st_isTimeout;

VOID vSoundOKTimer_Initialize()
{
    st_isStart = false;
    st_iTime = 0;
    st_isTimeout = false;
}

VOID vSoundOKTimer_IncTime()
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

BOOL isSoundOKTimer_CheckTime()
{
    BOOL isRet = st_isTimeout;
    if (isRet == true) {
        vSoundOKTimer_Initialize();
    }

    return isRet;
}

VOID vSoundOKTimer_Start()
{
    st_iTime = 0;
    st_isTimeout = false;
    st_isStart = true;
}

VOID vSoundOKTimer_Stop()
{
    vSoundOKTimer_Initialize();
}
