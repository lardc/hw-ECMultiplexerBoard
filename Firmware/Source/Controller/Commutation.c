// Header
#include "Commutation.h"

// Includes
#include "Global.h"
#include "DataTable.h"
#include "ZwSPI.h"
#include "LowLevel.h"
#include "Delay.h"

#define SELECT_ALL_RELAY_IN_REGISTER 0xFF
#define SPI_DATA_SIZE_IN_16BIT 6

// Variables
volatile static uint8_t ShiftRegistersState[REGISTERS_NUM + 1] = {0};
volatile static uint8_t BistableBits[REGISTERS_NUM + 1] = {0};
static uint16_t SavedCommutation = MAX_COUNTER_TABLE;

// Forward functions
void COMM_SwitchSimpleDevice(RegisterPin Device, bool State);
void COMM_SwitchBistableDevice(BistableSwitch Device, bool State);
void COMM_ApplyCommutation();
void COMM_DisableCtrlOfBistableRelay();
void COMM_CleanShiftRegister();
void COMM_CommutateGroupOnTableNumber(uint8_t NumbOfTable);
void COMM_CommutateForTableGroupSimpleRelay(uint64_t RelayMask);
void COMM_CommutateForTableGroupBistablRelay(uint64_t RelayMask);
void COMM_DisconnectAllRelay();
void COMM_SwitchBistableRelay(uint8_t IndexRelay, bool NewState);
void COMM_DisconnectBistableRelays();
void COMM_DisconnectSimpleRelays();

// Functions
bool COMM_ReturnResultConnectGroup(bool *FastSwitch)
{
	for(uint8_t i = 0; i < MAX_COUNTER_TABLE; i++)
	{
		if(COMM_Table[i].Active)
			if(DataTable[REG_TYPE_MEASURE] == COMM_Table[i].TypeMeasure)
				if(DataTable[REG_POSITION_OF_CASE] == COMM_Table[i].TypePositionOfCase || COMM_Table[i].TypePositionOfCase == IGNORE)
					if(DataTable[REG_TYPE_SIGNAL_CTRL] == COMM_Table[i].TypeCtrl || COMM_Table[i].TypeCtrl == IGNORE)
						if(DataTable[REG_TYPE_SIGNAL_AT_LEAKAGE] == COMM_Table[i].TypeSignalAsLeakAge || COMM_Table[i].TypeSignalAsLeakAge == IGNORE)
							if(DataTable[REG_TYPE_POLARITY] == COMM_Table[i].SignalDirection || COMM_Table[i].SignalDirection == IGNORE)
							{
								if(i == SavedCommutation)
									*FastSwitch = true;
								else
								{
									if(SavedCommutation != MAX_COUNTER_TABLE)
										COMM_DisconnectAllRelay();

									*FastSwitch = false;
									COMM_CommutateGroupOnTableNumber(i);
									SavedCommutation = i;
									DataTable[REG_LAST_TABLE] = i;
								}
								return true;
							}
	}

	DataTable[REG_LAST_TABLE] = 0;
	return false;
}
// ----------------------------------------

void COMM_CommutateGroupOnTableNumber(uint8_t NumbOfTable)
{
	COMM_CommutateForTableGroupSimpleRelay(COMM_Table[NumbOfTable].Relay & ~COMM_BUSHV);
	COMM_CommutateForTableGroupBistablRelay(COMM_Table[NumbOfTable].Relay >> BISTABLE_RELAY_START_BIT);
}
// ----------------------------------------

bool COMM_HVFastSwitch()
{
	if(SavedCommutation == MAX_COUNTER_TABLE)
		return false;
	else
	{
		COMM_CommutateForTableGroupSimpleRelay(COMM_Table[SavedCommutation].Relay & COMM_BUSHV);
		return true;
	}
}
// ----------------------------------------

void COMM_CommutateForTableGroupSimpleRelay(uint64_t RelayMask)
{
	for(uint8_t i = 0; i < SIMPLE_ARRAY_SIZE; i++)
	{
		if(RelayMask & 1)
			COMM_SwitchSimpleRelay(i, true);
		RelayMask >>= 1;
	}
}
// ----------------------------------------

void COMM_CommutateForTableGroupBistablRelay(uint64_t RelayMask)
{
	for(uint8_t i = 0; i < BISTABLE_ARRAY_SIZE; i++)
	{
		if(RelayMask & 1)
			COMM_SwitchBistableRelay(i, true);
		RelayMask >>= 1;
	}
}
// ----------------------------------------

void COMM_DisconnectAllRelay()
{
	SavedCommutation = MAX_COUNTER_TABLE;

	COMM_DisconnectSimpleRelays();
	COMM_DisconnectBistableRelays();
}
// ----------------------------------------

void COMM_SwitchBistableRelay(uint8_t IndexRelay, bool NewState)
{
	COMM_SwitchBistableDevice(*COMM_BistableRelayArray[IndexRelay], NewState);

	COMM_ApplyCommutation();
	DELAY_MS(BISTABLE_SWITCH_DELAY);
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
	LL_SetStateReset(FALSE);
	LL_WriteToShiftRegister(ShiftRegistersState, REGISTERS_NUM);
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
	for(uint8_t i = 0; i < REGISTERS_NUM + 1; i++)
		ShiftRegistersState[i] = 0;
}
// ----------------------------------------
