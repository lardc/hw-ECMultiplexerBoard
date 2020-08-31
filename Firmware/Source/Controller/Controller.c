// Header
#include "Controller.h"
//
// Includes
#include "Board.h"
#include "Delay.h"
#include "DeviceProfile.h"
#include "Interrupts.h"
#include "Global.h"
#include "LowLevel.h"
#include "SysConfig.h"
#include "DebugActions.h"
#include "Commutation.h"
#include "Safety.h"
#include "Diagnostic.h"

#define CTRL_GET_STATE_LOCK			DataTable[REG_STATE_LOCK]
#define CTRL_SET_STATE_LOCK			DataTable[REG_STATE_LOCK] = TRUE
#define CTRL_SET_STATE_UNLOCK		DataTable[REG_STATE_LOCK] = FALSE
#define CTRL_SET_STATE_SENS_ALARM	DataTable[REG_STATE_SENS] = TRUE
#define CTRL_SET_STATE_SENS_CLEAR	DataTable[REG_STATE_SENS] = FALSE

// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
static Boolean CycleActive = false;

volatile Int64U CONTROL_TimeCounter = 0;

/// Forward functions
//
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_SetDeviceState(DeviceState NewState);
void CONTROL_SwitchToFault(Int16U Reason);
void CONTROL_DelayMs(uint32_t Delay);
void CONTROL_UpdateWatchDog();
void CONTROL_ResetToDefaultState();
void CONTROL_Logic();

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

	COMM_InitTable();			// Создание и заполнение таблиц

	COMM_DisconnectAllRelay();
}
//------------------------------------------

void CONTROL_ResetToDefaultState()
{
	DataTable[REG_FAULT_REASON] = DF_NONE;
	DataTable[REG_DISABLE_REASON] = DF_NONE;
	DataTable[REG_WARNING] = WARNING_NONE;
	DataTable[REG_PROBLEM] = PROBLEM_NONE;
	DataTable[REG_OP_RESULT] = OPRESULT_NONE;

	DataTable[REG_STATE_LOCK] = TRUE;
	
	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
	
	CONTROL_SetDeviceState(DS_None);
}

//------------------------------------------

void CONTROL_Idle()
{
	DEVPROFILE_ProcessRequests();
	CONTROL_UpdateWatchDog();
	//CONTROL_Logic();
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
				else if(CONTROL_State == DS_Enabled)
				{
					*pUserError = ERR_OPERATION_BLOCKED;
				}
				break;
			}
			
		case ACT_DISABLE_POWER:
			if((CONTROL_State == DS_None) || (CONTROL_State == DS_Enabled) || (CONTROL_State == DS_ReadyCommutate))
			{
				COMM_DisconnectAllRelay();
				CONTROL_SetDeviceState(DS_None);
			}
			
		case ACT_SET_RELAY_NONE:
			{
				COMM_DisconnectAllRelay();
			}
			break;

		case ACT_SET_RELAY_GROUP:
			{
				if(COMM_ReturnResultConnectGroup())
				{
					DataTable[REG_OP_RESULT] = OPRESULT_OK;
					*pUserError = ERR_NONE;
				}
				else
				{
					DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
					*pUserError = ERR_DEVICE_NOT_READY;
				}
			}
			break;

		default:
			return DIAG_HandleDiagnosticAction(ActionID, pUserError);
			
	}
	return true;
}
//-----------------------------------------------

void CONTROL_Logic()
{
	SFTY_ReadStateSafety();

	if(SFTY_GET_STATE_BUTTON_STOP)
	{
		CTRL_SET_STATE_LOCK;
		DataTable[REG_PROBLEM] = PROBLEM_BUTTON_STOP;
		COMM_DisconnectAllRelay();
	}
	else
	{
		CTRL_SET_STATE_UNLOCK;
		if(SFTY_GET_STATE_BUTTON_START)
		{
			if(SFTY_GET_STATUS)
			{
				SFTY_EnableInterrupt();
				SFTY_ReadStateSafety();

				if(SFTY_GET_STATE_SENS1 || SFTY_GET_STATE_SENS2)
				{
					COMM_DisconnectAllRelay();
					CTRL_SET_STATE_SENS_ALARM;
					return;
				}
			}
			CTRL_SET_STATE_SENS_CLEAR;
			if(CTRL_GET_STATE_LOCK)
			{
				if(COMM_ReturnResultConnectGroup())
				{
					DataTable[REG_OP_RESULT] = OPRESULT_OK;
				}
				else
				{
					DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
				}
			}
		}
	}
}
//-----------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
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

void CONTROL_DelayMs(uint32_t Delay)
{
	uint64_t Counter = (uint64_t)CONTROL_TimeCounter + Delay;
	while(Counter > CONTROL_TimeCounter)
		CONTROL_UpdateWatchDog();
}
//------------------------------------------

void CONTROL_UpdateWatchDog()
{
	if(BOOT_LOADER_VARIABLE != BOOT_LOADER_REQUEST)
		IWDG_Refresh();
}
//------------------------------------------

