// Header
#include "Commutation.h"

// Includes
#include "Global.h"
#include "DataTable.h"
#include "ZwSPI.h"
#include "LowLevel.h"

// Variables
//
static uint8_t ShiftRegistersState[REGISTERS_NUM] = {0};
static uint8_t BistableBits[REGISTERS_NUM] = {0};

// Forward functions
//
void COMM_SwitchSimpleDevice(RegisterPin Device, bool State);
void COMM_SwitchBistableDevice(BistableSwitch Device, bool State);
void COMM_ApplyCommutation();
void COMM_CleanBistable();

void COMM_CommutateGroup1();
void COMM_CommutateGroup2();
void COMM_DisconnectAllRelay();
void COMM_ConnectRelayGroup(uint8_t Group);
void COMM_TransferDataRawToShiftRegistersState();
void COMM_SetRelayFromRAW();
void COMM_PrepareFromRAW();
void COMM_CleanRegisters();
void COMM_EnableOutShiftRegister();
void COMM_DisableOutShiftRegister();

// Functions
//
void COMM_SetRelayFromRAW()
{
	COMM_PrepareFromRAW();
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

void COMM_PrepareFromRAW()
{
	for(uint8_t i = REG_RAW_RELAY_BUS_MINUS_CO; i < REG_RAW_RELAY_BUS_PLUS_DISCO; i++)
	{
		ShiftRegistersState[i - REG_RAW_RELAY_BUS_MINUS_CO] = DataTable[i];
		BistableBits[i - REG_RAW_RELAY_BUS_MINUS_CO] = DataTable[i];
	}
	
	for(uint8_t i = REG_RAW_RELAY_POT_CTRL; i < REG_RAW_RELAY_OUTRELAY; i++)
	{
		ShiftRegistersState[i - REG_RAW_RELAY_POT_CTRL] = DataTable[i];
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
