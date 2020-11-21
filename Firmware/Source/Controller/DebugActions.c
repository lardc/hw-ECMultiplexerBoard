// Header
#include "DebugActions.h"

// Include
#include "LowLevel.h"
#include "Board.h"
#include "Delay.h"
#include "Controller.h"
#include "DataTable.h"

// Functions
//
void DBGACT_GenerateImpulseLedRed()
{
	LL_LedRed(TRUE);
	DELAY_MS(1000);
	LL_LedRed(FALSE);
}
//-----------------------------

void DBGACT_GenerateImpulseLedGreen()
{
	LL_LedGreen(TRUE);
	DELAY_MS(1000);
	LL_LedGreen(FALSE);
}
//-----------------------------

void DBGACT_GenerateImpulseLineSync1()
{
	LL_SetSync1State(FALSE);
	DELAY_MS(10);
	LL_SetSync1State(TRUE);
}
//-----------------------------

void DBGACT_GenerateImpulseLineSync2()
{
	LL_SetSync2State(FALSE);
	DELAY_MS(10);
	LL_SetSync2State(TRUE);
}
//-----------------------------

void DBGACT_GenerateImpulseLineLock1()
{
	LL_SetStateLock1(TRUE);
	DELAY_MS(10);
	LL_SetStateLock1(FALSE);
}
//-----------------------------

void DBGACT_GenerateImpulseLineLock2()
{
	LL_SetStateLock2(TRUE);
	DELAY_MS(10);
	LL_SetStateLock2(FALSE);
}
//-----------------------------
