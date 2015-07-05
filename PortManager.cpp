#include "PortManager.h"
#include "Board.h"

VOID vPortManager_Initialize()
{
    pinMode(SOUND_OUT_PORT,OUTPUT);
    digitalWrite(SOUND_OUT_PORT,LOW);
}

VOID vPortManager_SoundON(INT iFreq)
{
    tone(SOUND_OUT_PORT,iFreq);
}

VOID vPortManager_SoundOFF()
{
    noTone(SOUND_OUT_PORT);
}
