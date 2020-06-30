#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "stdinc.h"

// Functions
//
void LL_ToggleBoardLED();
void LL_LedGreen(bool State);
void LL_LedRed(bool State);
void LL_SetStateLock1(bool State);
void LL_SetStateLock2(bool State);
void LL_SoftSpiData(bool State);
void LL_SetSync1State(bool State);
void LL_SetSync2State(bool State);
void LL_SetStateOE(bool State);
void LL_SetStateReset(bool State);

bool LL_GetSync1State();
bool LL_GetSync2State();

#endif //__LOWLEVEL_H
