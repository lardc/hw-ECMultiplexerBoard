#ifndef __INITCONFIG_H
#define __INITCONFIG_H

#include "stdinc.h"

//Functions
//
Boolean INITCFG_ConfigSystemClock();
void INITCFG_ConfigInterrupt();
void INITCFG_ConfigIO();
void INITCFG_ConfigSPI();
void INITCONFIG_CAN();
void INITCONFIG_UART();
void INITCONFIG_Timer7();
void INITCONFIG_WatchDog();

#endif //__INITCONFIG_H
