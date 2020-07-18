// Header
#include "Commutation.h"

// Includes
#include "Global.h"
#include "DataTable.h"
#include "ZwSPI.h"
#include "LowLevel.h"

// Variables
static uint8_t ShiftRegistersState[REGISTERS_NUM] = {0};
static uint8_t BistableBits[REGISTERS_NUM] = {0};
bool IndexRelayIsOk(bool TypeRelayIs, uint8_t IndexRelay);

// Forward functions
void COMM_SwitchSimpleDevice(RegisterPin Device, bool State);
void COMM_SwitchBistableDevice(BistableSwitch Device, bool State);
void COMM_ApplyCommutation();
void COMM_CleanBistable();
void COMM_CommutateGroup1();
void COMM_CommutateGroup2();
void COMM_DisconnectAllRelay();
void COMM_ConnectRelayGroup(uint8_t Group);
void COMM_CleanRegisters();
void COMM_EnableOutShiftRegister();
void COMM_DisableOutShiftRegister();
void COMM_ConnectOneRelay(bool TypeOfRelay, uint8_t IndexRelay, bool NewState);

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

	CONTROL_DelayMs(500);

	COMM_CleanBistable();
	COMM_ApplyCommutation();
}

// ----------------------------------------
void COMM_ConnectRelayGroup(uint8_t Group)
{
	switch (Group)
	{
		case 1:
			{
				COMM_CommutateGroup1();
			}
			break;
		case 2:
			{
				COMM_CommutateGroup2();
			}
			break;
			
		default:
			{
				COMM_DisconnectAllRelay();
			}
			break;
	}
}
// ----------------------------------------

void COMM_CommutateGroup1()
{
	COMM_SwitchSimpleDevice(COMM_SwitchPOTPlusToPOT1, true);
	COMM_SwitchBistableDevice(COMM_SwitchBUSLVPlusToPOW1, true);
	
	COMM_ApplyCommutation();
	
	CONTROL_DelayMs(500);
	
	COMM_CleanBistable();
	COMM_ApplyCommutation();
}
// ----------------------------------------

void COMM_CommutateGroup2()
{
	COMM_SwitchSimpleDevice(COMM_SwitchPOTPlusToPOT1, true);
	COMM_SwitchBistableDevice(COMM_SwitchBUSLVPlusToPOW1, true);
	
	COMM_ApplyCommutation();
	
	CONTROL_DelayMs(500);
	
	COMM_CleanBistable();
	COMM_ApplyCommutation();
}
// ----------------------------------------

void COMM_DisconnectAllRelay()
{
	COMM_CleanRegisters();
	ShiftRegistersState[REGISTER_E] = 0xFF;
	ShiftRegistersState[REGISTER_G] = 0xFF;
	BistableBits[REGISTER_E] = 0xFF;
	BistableBits[REGISTER_G] = 0xFF;
	COMM_ApplyCommutation();
	
	CONTROL_DelayMs(500);
	
	COMM_CleanBistable();
	COMM_ApplyCommutation();
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
	COMM_DisableOutShiftRegister();
	for(uint8_t i = 0; i < REGISTERS_NUM; i++)
	{
		LL_SendAndSaveByteToShiftRegister(ShiftRegistersState[i]);
	}
	COMM_EnableOutShiftRegister();
}
// ----------------------------------------

void COMM_CleanBistable()
{
	for(uint8_t i = 0; i < REGISTERS_NUM; i++)
	{
		ShiftRegistersState[i] &= BistableBits[i];
		BistableBits[i] = 0;
	}
}
// ----------------------------------------

void COMM_CleanRegisters()
{
	for(uint8_t i = 0; i < REGISTERS_NUM; i++)
	{
		ShiftRegistersState[i] = 0;
	}
}
// ----------------------------------------

void COMM_EnableOutShiftRegister()
{
	LL_SetStateOE(FALSE);
}
// ----------------------------------------

void COMM_DisableOutShiftRegister()
{
	LL_SetStateOE(TRUE);
}
// ----------------------------------------
