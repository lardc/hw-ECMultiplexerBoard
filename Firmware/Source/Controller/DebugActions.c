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
void DEBAGACTIONS_GenerateImpulseLedRed()
{
	LL_LedRed(TRUE);
	Delay_mS(10);
	LL_LedRed(FALSE);
}
//-----------------------------

void DEBAGACTIONS_GenerateImpulseLedGreen()
{
	LL_LedGreen(TRUE);
	Delay_mS(10);
	LL_LedGreen(FALSE);
}
//-----------------------------

void DEBAGACTIONS_GenerateImpulseLineSync1()
{
	LL_SetSync1State(TRUE);
	Delay_mS(10);
	LL_SetSync1State(FALSE);
}
//-----------------------------

void DEBAGACTIONS_GenerateImpulseLineSync2()
{
	LL_SetSync2State(TRUE);
	Delay_mS(10);
	LL_SetSync2State(FALSE);
}
//-----------------------------

void DEBAGACTIONS_GenerateImpulseLineLock1()
{
	LL_SetStateLock1(TRUE);
	Delay_mS(10);
	LL_SetStateLock1(FALSE);
}
//-----------------------------

void DEBAGACTIONS_GenerateImpulseLineLock2()
{
	LL_SetStateLock2(TRUE);
	Delay_mS(10);
	LL_SetStateLock2(FALSE);
}
//-----------------------------

void DEBAGACTIONS_GenerateImpulseLineReset()
{
	LL_SetStateReset(TRUE);
	Delay_mS(10);
	LL_SetStateReset(FALSE);
}
//-----------------------------

void DEBAGACTIONS_GenerateImpulseLineOE()
{
	LL_SetStateOE(TRUE);
	Delay_mS(10);
	LL_SetStateOE(FALSE);
}
//-----------------------------

void DEBAGACTIONS_SetRelay()
{
	CONTROL_FullSetRelay();
}
//-----------------------------

