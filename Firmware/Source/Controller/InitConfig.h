#ifndef __INITCONFIG_H
#define __INITCONFIG_H

#include "stdinc.h"

//Functions
//
Boolean INITCFG_ConfigSystemClock();
void INITCFG_ConfigInterrupt();
void INITCFG_ConfigIO();
void INITCFG_ConfigSPI();
void INITCFG_ConfigCAN();
void INITCFG_ConfigUART();
void INITCFG_ConfigTimer7();
void INITCFG_ConfigWatchDog();

#endif //__INITCONFIG_H
