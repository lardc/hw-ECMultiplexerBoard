// Header
#include "Safety.h"

// Include
#include "LowLevel.h"
#include "InitConfig.h"
#include "DataTable.h"
#include "stdinc.h"
#include "Commutation.h"
#include "Controller.h"
#include "ZwEXTI.h"
#include "DeviceObjectDictionary.h"
#include "stm32f3xx.h"

// Volatile
extern volatile DeviceState CONTROL_State;

// Forward functions
void SFTY_DisconnectAndSetStopState();
void SFTY_SwitchInterruptState(bool NewState);
void SFTY_CheckSafety();
void SFTY_SetSensState();

volatile Safety SafetyState = {TRUE, {FALSE, FALSE}, {FALSE, FALSE}, {FALSE, FALSE}, {FALSE, FALSE}};

// Functions
void SFTY_CheckSafety()
{

	if(SFTY_GET_STATE_BUTTON_STOP)
	{
		SFTY_DisconnectAndSetStopState();
	}
	else
	{
		if((CONTROL_State != DS_None) && (CONTROL_State != DS_Disabled))
		{
			if(SFTY_GET_STATE_BUTTON_START)
			{
				if(SFTY_GET_STATUS)
				{
					if(SFTY_GET_STATE_SENS1 || SFTY_GET_STATE_SENS2)
					{
						SFTY_SetSensState();
						return;
					}
					else
					{
						CONTROL_SetDeviceState(DS_SafetyEnabled);
					}
				}
				else
				{
					CONTROL_SetDeviceState(DS_Enabled);
				}

				DataTable[REG_BUTTON_START] = BUTT_START_IS_PRESSED;
			}
			else
			{
				DataTable[REG_BUTTON_START] = BUTT_START_IS_UNPRESSED;
			}
		}
	}
}
//-----------------------------------------------

void SFTY_DisconnectAndSetStopState()
{
	CONTROL_SetDeviceState(DS_SafetyDanger);
	DataTable[REG_PROBLEM] = PROBLEM_BUTTON_STOP;
	COMM_DisconnectAllRelay();
}
//-----------------------------------------------

void SFTY_SetSensState()
{
	CONTROL_SetDeviceState(DS_SafetyDanger);
	DataTable[REG_PROBLEM] = PROBLEM_SENS;
}
//-----------------------------------------------

void SFTY_SwitchInterruptState(bool NewState)
{
	if(NewState)
	{
		EXTI_Config(EXTI_PB, EXTI_6, RISE_TRIG, 0);	// GPIO_SFTY_2
		EXTI_Config(EXTI_PB, EXTI_7, RISE_TRIG, 0);	// GPIO_SFTY_1
		EXTI_EnableInterrupt(EXTI9_5_IRQn, 0, true);
	}
	else
	{
		EXTI->IMR |= 0 << EXTI_6;
		EXTI->IMR |= 0 << EXTI_7;
	}
}
//------------------------------------------
