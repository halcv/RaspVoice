#ifndef _SOUND_OK_TIMER_H_
#define _SOUND_OK_TIMER_H_

#include "MySystype.h"

VOID vSoundOKTimer_Initialize();
VOID vSoundOKTimer_IncTime();
BOOL isSoundOKTimer_CheckTime();
VOID vSoundOKTimer_Start();
VOID vSoundOKTimer_Stop();

#endif // _SOUND_OK_TIMER_H_
