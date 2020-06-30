#ifndef __INITCONFIG_H
#define __INITCONFIG_H

#include "stdinc.h"

//Functions
//
Boolean INITCONFIG_SysClk();
void INITCONFIG_InterruptEnable();
void INITCONFIG_IO();
void INITCONFIG_SPI();
void INITCONFIG_CAN();
void INITCONFIG_UART();
void INITCONFIG_Timer7();
void INITCONFIG_WatchDog();

#endif //__INITCONFIG_H
