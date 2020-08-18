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
void COMM_CommutateGroup(uint8_t NumbOfTable);
bool COMM_ReturnResultConnectGroup();
bool COMM_ReturnResultChekExistParametrs();


// Functions
// ----------------------------------------
bool COMM_ReturnResultConnectGroup()
{
	return (COMM_ReturnResultChekExistParametrs());
}
// ----------------------------------------
bool COMM_ReturnResultChekExistParametrs()
{
	for(uint8_t i = 0; i < MAX_COUNTER_TABLE + 1; i++)
	{
		if(DataTable[REG_TYPE_MEASURE] == COMM_Table[i].TypeMeasure)
		{
			if(DataTable[REG_TYPE_BODY] == COMM_Table[i].TypeBody)
			{
				if(DataTable[REG_POSITION_OF_BODY] == COMM_Table[i].TypePositionOfBody)
				{
					if(DataTable[REG_TYPE_SIGNAL_CTRL] == COMM_Table[i].TypeCtrl)
					{
						if(DataTable[REG_TYPE_SIGNAL_AT_LEAKAGE] == COMM_Table[i].TypeSignalAsLeakAge)
						{
							if(DataTable[REG_TYPE_POLARITY] == COMM_Table[i].SignalDirection)
							{
								COMM_CommutateGroup(i);
								return 1;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
// ----------------------------------------

void COMM_CommutateGroup(uint8_t NumbOfTable)
{
	uint64_t Relay = COMM_Table[NumbOfTable].Relay;
	for(uint8_t i = 0; i < 45 ; i++)
	{
		if(Relay & 1)
		{
			COMM_SwitchSimpleRelay(i, true);
		}
		Relay >>= 1;
	}

	for(uint8_t i = 0; i < 11; i++)
	{
		if(Relay & 1)
		{
			COMM_SwitchBistableRelay(i, true);
		}
		Relay >>= 1;
	}
}
// ----------------------------------------

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

