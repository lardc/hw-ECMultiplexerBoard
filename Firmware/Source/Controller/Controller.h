#ifndef __CONTROLLER_H
#define __CONTROLLER_H

// Include
#include "stdinc.h"

// Types
typedef enum __DeviceState
{
	DS_None = 0,
	DS_Fault = 1,
	DS_Disabled = 2,
	DS_Enabled = 3,
	DS_InProcess = 4
} DeviceState;

// Variables
extern volatile Int64U CONTROL_TimeCounter;
extern Int64U CONTROL_LEDTimeout;

// Functions
void CONTROL_Init();
void CONTROL_Idle();
void Control_DelayMs(uint32_t Delay);

void CONTROL_FullSetRelay();

#endif // __CONTROLLER_H
