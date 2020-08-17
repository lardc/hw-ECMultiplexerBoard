// Header
#include "Commutation.h"

// Includes
#include "Global.h"
#include "DataTable.h"
#include "ZwSPI.h"
#include "LowLevel.h"

#define SELECT_ALL_RELAY_IN_REGISTER 0xFF
#define SPI_DATA_SIZE_IN_16BIT 6

// Variables
volatile static uint8_t ShiftRegistersState[REGISTERS_NUM + 1] = {0};
volatile static uint8_t BistableBits[REGISTERS_NUM + 1] = {0};

volatile static uint16_t DataTransfer[6] = {0};

// Forward functions
void COMM_SwitchSimpleDevice(RegisterPin Device, bool State);
void COMM_SwitchBistableDevice(BistableSwitch Device, bool State);
void COMM_ApplyCommutation();
void COMM_DisableCtrlOfBistableRelay();
void COMM_CleanShiftRegister();
void COMM_CompareDataTo16Bit();

// Functions
void COMM_DisconnectAllRelay()
{
	COMM_DisconnectSimpleRelays();
	COMM_DisconnectBistableRelays();
}
// ----------------------------------------

void COMM_SwitchBistableRelay(uint8_t IndexRelay, bool NewState)
{
	COMM_SwitchBistableDevice(*COMM_BistableRelayArray[IndexRelay], NewState);

	COMM_ApplyCommutation();
	CONTROL_DelayMs(BISTABLE_SWITCH_DELAY);
	COMM_DisableCtrlOfBistableRelay();
}
// ----------------------------------------

void COMM_SwitchSimpleRelay(uint8_t IndexRelay, bool NewState)
{
	COMM_SwitchSimpleDevice(*COMM_SimpleRelayArray[IndexRelay], NewState);
	COMM_ApplyCommutation();
}
// ----------------------------------------

void COMM_DisconnectSimpleRelays()
{
	COMM_CleanShiftRegister();
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
	COMM_CompareDataTo16Bit();
	LL_SetStateReset(FALSE);
	LL_WriteToShiftRegister(DataTransfer, SPI_DATA_SIZE_IN_16BIT);
	LL_SetStateReset(TRUE);
}
// ----------------------------------------

void COMM_DisconnectBistableRelays()
{
	for(uint8_t i = 0; i < BISTABLE_ARRAY_SIZE; i++)
		COMM_SwitchBistableRelay(i, false);
}
// ----------------------------------------

void COMM_DisableCtrlOfBistableRelay()
{
	for(uint8_t i = 0; i < REGISTERS_NUM + 1; i++)
	{
		ShiftRegistersState[i] &= ~BistableBits[i];
		BistableBits[i] = 0;
	}
	COMM_ApplyCommutation();
}
// ----------------------------------------

void COMM_CleanShiftRegister()
{
	for(volatile uint8_t i = 0; i < REGISTERS_NUM; i++)
	{
		ShiftRegistersState[i] = 0;
	}
}
// ----------------------------------------

void COMM_CompareDataTo16Bit()
{
	union __CompareRelay
	{
		struct
		{
			uint8_t Low;
			uint8_t High;
		} Byte;
		uint16_t Word;
	};

	union __CompareRelay CompareRelay;

	CompareRelay.Byte.High = ShiftRegistersState[0];
	CompareRelay.Byte.Low = ShiftRegistersState[1];
	DataTransfer[0] = CompareRelay.Word;

	CompareRelay.Byte.High = ShiftRegistersState[2];
	CompareRelay.Byte.Low = ShiftRegistersState[3];
	DataTransfer[1] = CompareRelay.Word;

	CompareRelay.Byte.High = ShiftRegistersState[4];
	CompareRelay.Byte.Low = ShiftRegistersState[5];
	DataTransfer[2] = CompareRelay.Word;

	CompareRelay.Byte.High = ShiftRegistersState[6];
	CompareRelay.Byte.Low = ShiftRegistersState[7];
	DataTransfer[3] = CompareRelay.Word;

	CompareRelay.Byte.High = ShiftRegistersState[8];
	CompareRelay.Byte.Low = ShiftRegistersState[9];
	DataTransfer[4] = CompareRelay.Word;

	CompareRelay.Byte.High = ShiftRegistersState[10];
	CompareRelay.Byte.Low = ShiftRegistersState[11];
	DataTransfer[5] = CompareRelay.Word;

}
// ----------------------------------------

