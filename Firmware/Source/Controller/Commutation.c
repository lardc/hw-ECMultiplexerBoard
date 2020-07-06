// Header
#include "Commutation.h"

#include "CommutationTable.h"

static Int8U COMM_NewOutputValues[SUM_OF_ALL_BYTE_REGISTERS];
static Int8U COMM_CurrentOutputValues[SUM_OF_ALL_BYTE_REGISTERS];
static Int8U COMM_TransferOutputValues[SUM_OF_ALL_BYTE_REGISTERS];

// Function
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

void COMM_CorrectBipolarRelay(Int8U ConnectTable,Int8U DisconnectTable)
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

void COMM_SetRelay(Boolean Force)
{
	if(COMM_ChekNeedChangeStateRelay() || Force)
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

void COMM_CommutateNone()
{
	COMM_RegisterReset();
	COMM_SetRelay(TRUE);
}
// ----------------------------------------
