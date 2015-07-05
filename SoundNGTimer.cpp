#include "SoundNGTimer.h"

#define TIME_MAX    (100) // 1s

static INT st_iTime;
static BOOL st_isStart;
static BOOL st_isTimeout;

VOID vSoundNGTimer_Initialize()
{
    st_isStart = false;
    st_iTime = 0;
    st_isTimeout = false;
}

VOID vSoundNGTimer_IncTime()
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

BOOL isSoundNGTimer_CheckTime()
{
    BOOL isRet = st_isTimeout;
    if (isRet == true) {
        vSoundNGTimer_Initialize();
    }

    return isRet;
}

VOID vSoundNGTimer_Start()
{
    st_iTime = 0;
    st_isTimeout = false;
    st_isStart = true;
}
