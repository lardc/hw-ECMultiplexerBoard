// Header
#include "Commutation.h"

#include "CommutationTable.h"
#include "Global.h"
#include "DataTable.h"

static Int8U COMM_NewOutputValues[SUM_OF_ALL_BYTE_REGISTERS];
static Int8U COMM_CurrentOutputValues[SUM_OF_ALL_BYTE_REGISTERS];
static Int8U COMM_TransferOutputValues[SUM_OF_ALL_BYTE_REGISTERS];


static uint8_t ShiftRegistersState[REGISTERS_NUM] = {0};
static uint8_t BistableBits[REGISTERS_NUM] = {0};

void COMM_SwitchSimpleDevice(RegisterPin Device, bool State);
void COMM_SwitchBistableDevice(BistableSwitch Device, bool State);
void COMM_ApplyCommutation();
void COMM_DisconnectBistable();

// С помощью этой функции задаём состояние для простых реле на сдвиговом регистре
void COMM_SwitchSimpleDevice(RegisterPin Device, bool State)
{
	if(State)
		ShiftRegistersState[Device.Register] |= Device.Bit;
	else
		ShiftRegistersState[Device.Register] &= ~Device.Bit;
}
// ----------------------------------------

// С помощью этой функции задаём состояние для бистабильного коммутатора,
// состоящего из двух бистабильных реле
void COMM_SwitchBistableDevice(BistableSwitch Device, bool State)
{
	if(State)
	{
		// Уставка битов при включении
		ShiftRegistersState[Device.TurnOn1.Register] |= Device.TurnOn1.Bit;
		ShiftRegistersState[Device.TurnOn2.Register] |= Device.TurnOn2.Bit;

		// Отдельно запоминаем эти биты
		BistableBits[Device.TurnOn1.Register] |= Device.TurnOn1.Bit;
		BistableBits[Device.TurnOn2.Register] |= Device.TurnOn2.Bit;
	}
	else
	{
		// Уставка битов при выключении
		ShiftRegistersState[Device.TurnOff1.Register] |= Device.TurnOff1.Bit;
		ShiftRegistersState[Device.TurnOff2.Register] |= Device.TurnOff2.Bit;

		// Отдельно запоминаем эти биты
		BistableBits[Device.TurnOff1.Register] |= Device.TurnOff1.Bit;
		BistableBits[Device.TurnOff2.Register] |= Device.TurnOff2.Bit;
	}
}
// ----------------------------------------

// Пример выполнения коммутации
void COMM_Examle()
{
	// Формируем битовые значения для сдвиговых регистров и запоминаем бистабильные реле
	COMM_SwitchSimpleDevice(COMM_SwitchPOTPlusToPOT1, true);
	COMM_SwitchBistableDevice(COMM_SwitchBUSLVPlusToPOW1, true);

	// Отправляем уставку в сдвиговые регистры
	COMM_ApplyCommutation();

	// Задержка

	// Отдельно отключаем бистабильные реле
	COMM_DisconnectBistable();
}
// ----------------------------------------

void COMM_ApplyCommutation()
{
	// Здесь идёт запись массива ShiftRegistersState[] по SPI
}
// ----------------------------------------

void COMM_DisconnectBistable()
{
	// Мы запомнили биты, относящиеся к бистабильным реле
	// Теперь их отключаем и очищаем
	for(uint8_t i = 0; i < REGISTERS_NUM; i++)
	{
		ShiftRegistersState[i] &= BistableBits[i];
		BistableBits[i] = 0;
	}

	COMM_ApplyCommutation();
}
// ----------------------------------------

// Function
void COMM_ConnectGroup(Int8U Group)
{
	switch (Group)
	{
		case COMM_CONNECT_GROUP_1:
			{
				COMM_DisconnectAllRelay();
				COMM_OutputValuesCompose(BUSLV_MINUS_TO_POW_2_CON, TRUE);
				COMM_OutputValuesCompose(BUSLV_PLUS_TO_POW_1_CON, TRUE);

				COMM_OutputValuesCompose(POT_CTRL_PLUS_TO_C1P, TRUE);
				COMM_OutputValuesCompose(POT_CTRL_MINUS_TO_C2P, TRUE);

				COMM_OutputValuesCompose(CTRL_1_TO_CTRL1, TRUE);
				COMM_OutputValuesCompose(CTRL_2_TO_CTRL2, TRUE);

				COMM_OutputValuesCompose(POT_PLUS_TO_OUTRELAY1, TRUE);
				COMM_OutputValuesCompose(POT_MINUS_TO_OUTRELAY2, TRUE);

				COMM_OutputValuesCompose(OUTRELAY1_TO_POT_1, TRUE);
				COMM_OutputValuesCompose(OUTRELAY2_TO_POT_2, TRUE);

				COMM_SetRelayInMode(COMM_NORMAL_MODE);
			}
			break;
		case COMM_CONNECT_GROUP_2:
			{
				COMM_DisconnectAllRelay();
				COMM_OutputValuesCompose(BUSHV_PLUS_TO_HVPOW_1, TRUE);
				COMM_OutputValuesCompose(BUSHV_MINUS_TO_HVPOW_2, TRUE);
				COMM_SetRelayInMode(COMM_NORMAL_MODE);
			}
			break;

		default:
			break;
	}
}
void COMM_TransferDataRawToNewOutputValues()
{
	for(Int8U i = REG_RAW_RELAY_BUS_MINUS_CO; i < REG_RAW_RELAY_OUTRELAY; i++)
	{
		COMM_NewOutputValues[i - REG_RAW_RELAY_BUS_MINUS_CO] = DataTable[i];
	}
}
void COMM_OutputValuesCompose(Int8U TableID, Boolean State)
{
	if(State)
		COMM_NewOutputValues[CommutationTable[TableID].TypeRelay] |= CommutationTable[TableID].Bit;
	else
		COMM_NewOutputValues[CommutationTable[TableID].TypeRelay] &= ~CommutationTable[TableID].Bit;
}
// ----------------------------------------

void COMM_CopyCurrentOutputValuesToTransferOutputValues()
{
	for(Int8U i = 0; i < SUM_OF_ALL_BYTE_REGISTERS; i++)
	{
		COMM_TransferOutputValues[i] = COMM_CurrentOutputValues[i];
	}
}

void COMM_UpdateCurrentOutputValues()
{
	for(Int8U i = 0; i < SUM_OF_ALL_BYTE_REGISTERS; i++)
	{
		COMM_CurrentOutputValues[i] = COMM_NewOutputValues[i];
	}
}

// ----------------------------------------
void COMM_PrepareDataForBistableRelay()
{
	COMM_CorrectBipolarRelay(TAB_BIPOLAR_RELAY_BUS_PLUS_CONNECT, TAB_BIPOLAR_RELAY_BUS_PLUS_DISCONNECT);
	COMM_CorrectBipolarRelay(TAB_BIPOLAR_RELAY_BUS_MINUS_CONNECT, TAB_BIPOLAR_RELAY_BUS_MINUS_DISCONNECT);
}
// ----------------------------------------
void COMM_DisableBipolarRelay()
{
	COMM_TransferOutputValues[TAB_BIPOLAR_RELAY_BUS_PLUS_CONNECT] = 0;
	COMM_TransferOutputValues[TAB_BIPOLAR_RELAY_BUS_PLUS_DISCONNECT] = 0;
	COMM_TransferOutputValues[TAB_BIPOLAR_RELAY_BUS_MINUS_CONNECT] = 0;
	COMM_TransferOutputValues[TAB_BIPOLAR_RELAY_BUS_MINUS_DISCONNECT] = 0;
}

void COMM_TernOffBipolarRelay()
{
	COMM_TransferOutputValues[TAB_BIPOLAR_RELAY_BUS_PLUS_CONNECT] = 0xFF;
	COMM_TransferOutputValues[TAB_BIPOLAR_RELAY_BUS_PLUS_DISCONNECT] = 0xFF;
	COMM_TransferOutputValues[TAB_BIPOLAR_RELAY_BUS_MINUS_CONNECT] = 0xFF;
	COMM_TransferOutputValues[TAB_BIPOLAR_RELAY_BUS_MINUS_DISCONNECT] = 0xFF;
}

// ----------------------------------------
void COMM_SendStateToRelay(Boolean IsNormalRelay)
{
	COMM_CopyCurrentOutputValuesToTransferOutputValues();
	if(IsNormalRelay == TYPE_RELAY_NORMAL)
	{
		COMM_DisableBipolarRelay();
	}
	else
	{
		COMM_PrepareDataForBistableRelay();
	}

	for(Int8U i = 0; i < SUM_OF_ALL_BYTE_REGISTERS; i++)
	{
		SPI_WriteByte(SPI1, COMM_TransferOutputValues[i]);
	}
}
// ----------------------------------------

void COMM_OutputValuesReset()
{
	for(Int8U i = 0; i < SUM_OF_ALL_BYTE_REGISTERS; i++)
	{
		COMM_NewOutputValues[i] = 0;
	}
}

Int8U COMM_FaindChangeRelay(Int16U Table)
{
	return (COMM_CurrentOutputValues[Table] ^ COMM_NewOutputValues[Table]);
}
// ----------------------------------------

void COMM_CorrectBipolarRelay(Int8U ConnectTable, Int8U DisconnectTable)
{
	Int16U MaskChangeRelayState = COMM_FaindChangeRelay(ConnectTable);
	for(Int8U i = 0; i < 8; i++)
	{
		if(MaskChangeRelayState & (1 << i))
		{
			if((COMM_CurrentOutputValues[ConnectTable] & (1 << i)) == (MaskChangeRelayState & (1 << i)))
			{
				COMM_TransferOutputValues[DisconnectTable] |= COMM_CurrentOutputValues[i] & (1 << i);
			}
			else
			{
				COMM_TransferOutputValues[ConnectTable] |= 1 << i;
			}
		}
	}
}
// ----------------------------------------

Boolean COMM_ChekNeedChangeStateRelay()
{
	for(Int8U i = 0; i < SUM_OF_ALL_BYTE_REGISTERS; i++)
	{
		if(COMM_NewOutputValues[i] != COMM_CurrentOutputValues[i])
		{
			return 1;
		}
	}
	return 0;
}
// ----------------------------------------

void COMM_SetRelayInMode(Boolean Mode)
{
	if(COMM_ChekNeedChangeStateRelay() || Mode)
	{
		COMM_SendStateToRelay(TYPE_RELAY_BISTABLE); // Atention! Bistable relay need disable(!) after use (connect or disconnect).
		COMM_SendStateToRelay(TYPE_RELAY_NORMAL);

		COMM_UpdateCurrentOutputValues();
	}
}
// ----------------------------------------
void COMM_RegisterReset()
{
	COMM_OutputValuesReset();
}
// ----------------------------------------

void COMM_DisconnectAllRelay()
{
	COMM_RegisterReset();
	COMM_TernOffBipolarRelay();
	COMM_SetRelayInMode(COMM_FORCE_MODE);
}
// ----------------------------------------
