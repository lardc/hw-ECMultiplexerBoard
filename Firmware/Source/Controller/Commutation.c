// Header
#include "Commutation.h"

// Includes
#include "Global.h"
#include "DataTable.h"
#include "ZwSPI.h"
#include "LowLevel.h"

#define SELECT_ALL_RELAY_IN_REGISTER 0xFF
// Variables
static uint8_t ShiftRegistersState[REGISTERS_NUM] = {0};
static uint8_t BistableBits[REGISTERS_NUM] = {0};

// Forward functions
void COMM_SwitchSimpleDevice(RegisterPin Device, bool State);
void COMM_SwitchBistableDevice(BistableSwitch Device, bool State);
void COMM_ApplyCommutation();
void COMM_DisableCtrlPulseOfBistableRelay();
void COMM_DisconnectAllRelay();
void COMM_CleanShiftRegister();
void COMM_ConnectOneRelay(bool TypeOfRelay, uint8_t IndexRelay, bool NewState);
void COMM_TurnOffAllBistableRelay();
void COMM_FastWriteToBistableRelay(uint8_t RegisterName, uint8_t IndexOfRelayInRegister);

// ----------------------------------------
void COMM_ConnectOneRelay(bool TypeOfRelay, uint8_t IndexRelay, bool NewState)
{
	if(!TypeOfRelay)
	{
		COMM_SwitchSimpleDevice(*COMM_SimpleRelayArray[IndexRelay], NewState);
	}
	else
	{
		COMM_SwitchBistableDevice(*COMM_BistableRelayArray[IndexRelay], NewState);
	}
	COMM_ApplyCommutation();

	CONTROL_DelayMs(TIME_DELAY_TO_SWITCH_BISTABLE_RELAY);

	COMM_DisableCtrlPulseOfBistableRelay();
}

// ----------------------------------------
void COMM_DisconnectAllRelay()
{
	COMM_CleanShiftRegister();
	COMM_TurnOffAllBistableRelay();
}
// ----------------------------------------

void COMM_SwitchSimpleDevice(RegisterPin Device, bool State)
{
	if(State)
		ShiftRegistersState[Device.Register] |= Device.Bit;
	else
		ShiftRegistersState[Device.Register] &= ~Device.Bit;
}
// ----------------------------------------

void COMM_SwitchBistableDevice(BistableSwitch Device, bool State)
{
	if(State)
	{
		ShiftRegistersState[Device.TurnOnPin.Register] |= Device.TurnOnPin.Bit;
		BistableBits[Device.TurnOnPin.Register] |= Device.TurnOnPin.Bit;
	}
	else
	{
		ShiftRegistersState[Device.TurnOffPin.Register] |= Device.TurnOffPin.Bit;
		BistableBits[Device.TurnOffPin.Register] |= Device.TurnOffPin.Bit;
	}
}
// ----------------------------------------

void COMM_ApplyCommutation()
{
	LL_WriteToShiftRegister(ShiftRegistersState, REGISTERS_NUM);
}
// ----------------------------------------
void COMM_TurnOffAllBistableRelay()
{
	COMM_FastWriteToBistableRelay(REGISTER_E, SELECT_ALL_RELAY_IN_REGISTER);
	COMM_FastWriteToBistableRelay(REGISTER_G, SELECT_ALL_RELAY_IN_REGISTER);

	COMM_DisableCtrlPulseOfBistableRelay();
}
// ----------------------------------------

void COMM_FastWriteToBistableRelay(uint8_t RegisterName, uint8_t IndexOfRelayInRegister)
{
	ShiftRegistersState[RegisterName] = IndexOfRelayInRegister;
	BistableBits[RegisterName] = IndexOfRelayInRegister;
	COMM_ApplyCommutation();
	CONTROL_DelayMs(TIME_DELAY_TO_SWITCH_BISTABLE_RELAY);
}
// ----------------------------------------

void COMM_DisableCtrlPulseOfBistableRelay()
{
	for(uint8_t i = 0; i < REGISTERS_NUM; i++)
	{
		ShiftRegistersState[i] &= ~BistableBits[i];
		BistableBits[i] = 0;
	}
	COMM_ApplyCommutation();
}
// ----------------------------------------

void COMM_CleanShiftRegister()
{
	for(uint8_t i = 0; i < REGISTERS_NUM; i++)
	{
		ShiftRegistersState[i] = 0;
	}
}
// ----------------------------------------
