// Header
#include "LowLevel.h"
// Include
#include "Board.h"
#include "Delay.h"

// Functions
//
void LL_ToggleBoardLED()
{
	GPIO_Toggle(GPIO_LED);
}
//-----------------------------

void LL_LedGreen(bool State)
{
	GPIO_SetState(GPIO_LED_EXT_GREEN, State);
}
//-----------------------------

void LL_LedRed(bool State)
{
	GPIO_SetState(GPIO_LED_EXT_RED, State);
}

//-----------------------------

void LL_SoftSpiData(bool State)
{
	GPIO_SetState(GPIO_DATA, State);
}
//-----------------------------

void LL_SetSync1State(bool State)
{
	// Синхронизация происходит при низком уровне на пине
	GPIO_SetState(GPIO_CTRL_SYNC_1, !State);
}
//-----------------------------

void LL_SetSync2State(bool State)
{
	// Синхронизация происходит при низком уровне на пине
	GPIO_SetState(GPIO_CTRL_SYNC_2, !State);
}
//-----------------------------

bool LL_GetSync1State()
{
	return GPIO_GetState(GPIO_SYNC_1);
}
//-----------------------------

bool LL_GetSync2State()
{
	return GPIO_GetState(GPIO_SYNC_2);
}
//-----------------------------
