// Header
#include "Controller.h"
//
// Includes
#include "Board.h"
#include "Delay.h"
#include "DataTable.h"
#include "DeviceProfile.h"
#include "Interrupts.h"
#include "Global.h"
#include "LowLevel.h"
#include "SysConfig.h"
#include "DebugActions.h"

// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
static Boolean CycleActive = false;

volatile Int64U CONTROL_TimeCounter = 0;

volatile Int8U RelayByte[11];

// Forward functions
//
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_SetDeviceState(DeviceState NewState);
void CONTROL_SwitchToFault(Int16U Reason);
void Control_DelayMs(uint32_t Delay);
void CONTROL_WatchDogUpdate();
void CONTROL_ResetToDefaultState();
void CONTROL_ResetHardware();
void CONTROL_UpdateRegisterByteRelay();
void CONTROL_SetRelay(Boolean ResetPolarizedRelay);
void CONTROL_FullSetRelay();
// Functions
//
void CONTROL_Init()
{
	// Конфигурация сервиса работы Data-table и EPROM
	EPROMServiceConfig EPROMService = {(FUNC_EPROM_WriteValues)&NFLASH_WriteDT, (FUNC_EPROM_ReadValues)&NFLASH_ReadDT};
	// Инициализация data table
	DT_Init(EPROMService, false);
	// Инициализация device profile
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	// Сброс значений
	DEVPROFILE_ResetControlSection();
	CONTROL_ResetToDefaultState();
}
//------------------------------------------

void CONTROL_ResetToDefaultState()
{
	DataTable[REG_FAULT_REASON] = DF_NONE;
	DataTable[REG_DISABLE_REASON] = DF_NONE;
	DataTable[REG_WARNING] = WARNING_NONE;
	DataTable[REG_PROBLEM] = PROBLEM_NONE;
	DataTable[REG_OP_RESULT] = OPRESULT_NONE;
	
	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
	
	CONTROL_ResetHardware();
	CONTROL_SetDeviceState(DS_None);
}
//------------------------------------------

void CONTROL_ResetHardware()
{
	
}
//------------------------------------------

void CONTROL_Idle()
{
	DEVPROFILE_ProcessRequests();
	CONTROL_WatchDogUpdate();
}
//------------------------------------------

static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError)
{
	*pUserError = ERR_NONE;
	
	switch (ActionID)
	{
		case ACT_ENABLE_POWER:
			{
				if(CONTROL_State == DS_None)
				{
					CONTROL_SetDeviceState(DS_Enabled);
				}
				else if(CONTROL_State != DS_Enabled)
				{
					*pUserError = ERR_DEVICE_NOT_READY;
				}
				break;
			}

		case ACT_DISABLE_POWER:
			if(CONTROL_State == DS_Enabled)
			{
				CONTROL_SetDeviceState(DS_None);
			}
			else
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_DBG_LED_RED_IMPULSE:
			{
				DBGACT_GenerateImpulseLedRed();
			}
			break;

		case ACT_DBG_LED_GREEN_IMPULSE:
			{
				DBGACT_GenerateImpulseLedGreen();
			}
			break;

		case ACT_DBG_SYNC_1_IMPULSE:
			{
				DBGACT_GenerateImpulseLineSync1();
			}
			break;

		case ACT_DBG_SYNC_2_IMPULSE:
			{
				DBGACT_GenerateImpulseLineSync2();
			}
			break;

		case ACT_DBG_LOCK_1_IMPULSE:
			{
				DBGACT_GenerateImpulseLineLock1();
			}
			break;

		case ACT_DBG_LOCK_2_IMPULSE:
			{
				DBGACT_GenerateImpulseLineLock1();
			}
		case ACT_DBG_RESET_IMPULSE:
			{
				DBGACT_GenerateImpulseLineReset();
			}
			break;

		case ACT_DBG_OE_IMPULSE:
			{
				DBGACT_GenerateImpulseLineOE();
			}
			break;

		case ACT_DBG_SET_RELLAY:
			{
				DBGACT_SetRelay();
			}
			break;
		default:
			return false;

	}
	return true;
}
//-----------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	CONTROL_ResetHardware();
	
	CONTROL_SetDeviceState(DS_Fault);
	DataTable[REG_FAULT_REASON] = Reason;
}
//------------------------------------------

void CONTROL_SetDeviceState(DeviceState NewState)
{
	CONTROL_State = NewState;
	DataTable[REG_DEV_STATE] = NewState;
}
//------------------------------------------

void Control_DelayMs(uint32_t Delay)
{
	uint64_t Counter = (uint64_t)CONTROL_TimeCounter + Delay;
	while(Counter > CONTROL_TimeCounter)
		CONTROL_WatchDogUpdate();
}
//------------------------------------------

void CONTROL_WatchDogUpdate()
{
	if(BOOT_LOADER_VARIABLE != BOOT_LOADER_REQUEST)
		IWDG_Refresh();
}
//------------------------------------------

void CONTROL_UpdateRegisterByteRelay()
{
	Int8U i = 0;
	Int8U ii = 0;
	for(i = REG_DBG_RELLAY_POT_PLUS; i < REG_DBG_RELLAY_CTRLPOT + 1; ++i)
	{
		RelayByte[ii] = DataTable[i];
		ii++;
	}
}
//------------------------------------------

void CONTROL_SetRelay(Boolean ResetPolarizedRelay)
{
	for(Int8U i = 0; i < 11 + 1; ++i)
	{
		if((ResetPolarizedRelay) && ((i == 3) || (i == 4) || (i == 5) || (i == 6)))
		{
			SPI_WriteByte(SPI1, 0);
		}
		else
		{
			SPI_WriteByte(SPI1, RelayByte[i]);
		}
	}
}
//------------------------------------------

void CONTROL_FullSetRelay()
{
	CONTROL_UpdateRegisterByteRelay();
	//Step One - config polarity relay
	CONTROL_SetRelay(FALSE);

	Control_DelayMs(10); // Время уточнить

	//Step two - confgi other relay (polarity relay is 0, but not reset)
	CONTROL_SetRelay(TRUE);
}
//------------------------------------------
