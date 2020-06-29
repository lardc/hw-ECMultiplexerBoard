#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "stdinc.h"

// Functions
//
void LL_ToggleBoardLED();

void LL_ExternalLED(bool State);

void LL_SoftSpiSRCK(bool State);
void LL_SoftSpiRCK(bool State);
void LL_SoftSpiData(bool State);
void LL_WriteToGateRegister(uint16_t Data);
void LL_SetSyncState(bool State);
bool LL_GetSyncState();

#endif //__LOWLEVEL_H
