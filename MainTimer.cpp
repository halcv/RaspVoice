#include "MainTimer.h"
#include "ReceiveTimeoutTimer.h"
#include "SoundNGTimer.h"
#include "SoundOKTimer.h"

#define METRO_10MS_INTERVAL    (10)
#define METRO_1S_INTERVAL    (1000)

static Metro st_Metro10ms = Metro(METRO_10MS_INTERVAL);
static Metro st_Metro1s = Metro(METRO_1S_INTERVAL);

static VOID vMainTimer_Interval10msProc();
static VOID vMainTimer_Interval1sProc();

VOID vMainTimer_Initialize()
{
    vReceiveTimeoutTimer_Initialize();
    vSoundNGTimer_Initialize();
    vSoundOKTimer_Initialize();
}

VOID vMainTimer_Main()
{
    if (st_Metro10ms.check() == true) {
        vMainTimer_Interval10msProc();
    }

    if (st_Metro1s.check() == true) {
        vMainTimer_Interval1sProc();
    }
}

static VOID vMainTimer_Interval10msProc()
{
    vSoundNGTimer_IncTime();
    vSoundOKTimer_IncTime();
}

static VOID vMainTimer_Interval1sProc()
{
    vReceiveTimeoutTimer_IncTime();
}
