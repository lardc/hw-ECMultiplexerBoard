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

void LL_SetSync1State(bool State)
{
	GPIO_SetState(GPIO_CTRL_SYNC_1, !State);
}
//-----------------------------

void LL_SetSync2State(bool State)
{
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

void LL_SetStateLock1(bool State)
{
	GPIO_SetState(GPIO_LOCK_1, !State);
}
//-----------------------------

void LL_SetStateLock2(bool State)
{
	GPIO_SetState(GPIO_LOCK_2, !State);
}
//-----------------------------

void LL_SetStateReset(bool State)
{
	GPIO_SetState(GPIO_RESET, State);
}
//-----------------------------

void LL_SetStateOE(bool State)
{
	GPIO_SetState(GPIO_OE, State);
}
//-----------------------------

void LL_SendAndSaveByteToShiftRegister(uint16_t Data)
{
	GPIO_SetState(GPIO_SET, FALSE);
	SPI_WriteByte(SPI1, Data);
	GPIO_SetState(GPIO_SET, TRUE);
}
//-----------------------------

