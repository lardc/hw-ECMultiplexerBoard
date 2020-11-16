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
#include "BCCIxParams.h"

// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
DeviceSubState CONTROL_SubState = DSS_None;
static Boolean CycleActive = false, SafetyActive = false;
volatile Int64U CONTROL_TimeCounter = 0;

// Forward functions
//
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_SwitchToFault(Int16U Reason);
void CONTROL_UpdateWatchDog();
void CONTROL_ResetToDefaultState();
void SFTY_CheckSafety();
void SFTY_DisconnectAndSetStopState();
void CONTROL_ProcessSwitch();
void CONTROL_HandleButtonsAndSensors();
void CONTROL_StopAndDisconnect();

// Functions
//
void CONTROL_Init()
{
	// ������������ ������� ������ Data-table � EPROM
	EPROMServiceConfig EPROMService = {(FUNC_EPROM_WriteValues)&NFLASH_WriteDT, (FUNC_EPROM_ReadValues)&NFLASH_ReadDT};
	// ������������� data table
	DT_Init(EPROMService, false);
	DT_SaveFirmwareInfo(CAN_SLAVE_NID, 0);
	// ������������� device profile
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	// ����� ��������
	DEVPROFILE_ResetControlSection();
	CONTROL_ResetToDefaultState();

	// �������� � ���������� ������
	DataTable[REG_COMM_TABLE_SIZE] = COMM_InitTable();
	COMM_DisconnectAllRelay();
}
//------------------------------------------

void CONTROL_ResetToDefaultState()
{
	DataTable[REG_FAULT_REASON] = DF_NONE;
	DataTable[REG_DISABLE_REASON] = DF_NONE;
	DataTable[REG_PROBLEM] = PROBLEM_NONE;
	DataTable[REG_OP_RESULT] = OPRESULT_NONE;
	DataTable[REG_BUTTON_START] = BUTT_START_IS_UNPRESSED;

	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
	
	COMM_DisconnectAllRelay();
	SFTY_SwitchInterruptState(false);

	CONTROL_SetDeviceState(DS_None, DSS_None);
}
//------------------------------------------

void CONTROL_Idle()
{
	DEVPROFILE_ProcessRequests();
	CONTROL_ProcessSwitch();
	CONTROL_HandleButtonsAndSensors();
	CONTROL_UpdateWatchDog();
}
//------------------------------------------

void CONTROL_ProcessSwitch()
{
	static Int64U Timeout = 0;

	if(CONTROL_State == DS_InProcess)
	{
		switch (CONTROL_SubState)
		{
			case DSS_SwitchStart:
				{
					Timeout = CONTROL_TimeCounter + TIME_TRANSIENT_DELAY;
					CONTROL_SetDeviceState(DS_InProcess, DSS_SwitchWait);
				}
				break;

			case DSS_SwitchWait:
				{
					if(CONTROL_TimeCounter > Timeout)
						CONTROL_SetDeviceState(DS_Ready, DSS_None);
				}
				break;

			default:
				break;
		}
	}
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
					LL_LedGreen(true);
					CONTROL_SetDeviceState(DS_Ready, DSS_None);
				}
				else if(CONTROL_State != DS_Ready)
					*pUserError = ERR_OPERATION_BLOCKED;
			}
			break;
			
		case ACT_DISABLE_POWER:
			CONTROL_ResetToDefaultState();
			break;
			
		case ACT_FAULT_CLEAR:
			{
				if(CONTROL_State == DS_Fault)
					CONTROL_ResetToDefaultState();
			}
			break;

		case ACT_SET_RELAY_GROUP:
			{
				if(CONTROL_State == DS_Ready)
				{
					bool FastSwitch;
					if(COMM_ReturnResultConnectGroup(&FastSwitch))
					{
						LL_LedRed(true);
						if(!FastSwitch)
							CONTROL_SetDeviceState(DS_InProcess, DSS_SwitchStart);
					}
					else
						*pUserError = ERR_BAD_CONFIG;
				}
				else
					*pUserError = ERR_DEVICE_NOT_READY;
			}
			break;

		case ACT_SET_RELAY_NONE:
			{
				if(CONTROL_State == DS_Ready)
					CONTROL_StopAndDisconnect();
				else
					*pUserError = ERR_DEVICE_NOT_READY;
			}
			break;

		case ACT_SAFETY_ACTIVATE:
			{
				if(CONTROL_State == DS_Ready)
					SafetyActive = true;
				else
					*pUserError = ERR_DEVICE_NOT_READY;
			}
			break;

		case ACT_SAFETY_DEACTIVATE:
			{
				if(CONTROL_State == DS_Ready)
					SafetyActive = false;
				else
					*pUserError = ERR_DEVICE_NOT_READY;
			}
			break;

		default:
			return DIAG_HandleDiagnosticAction(ActionID, pUserError);
			
	}
	return true;
}
//------------------------------------------

void CONTROL_StopAndDisconnect()
{
	SafetyActive = false;
	LL_LedRed(false);
	COMM_DisconnectAllRelay();
	CONTROL_SetDeviceState(DS_InProcess, DSS_SwitchStart);
}
//------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	CONTROL_SetDeviceState(DS_Fault, DSS_None);
	DataTable[REG_FAULT_REASON] = Reason;
}
//------------------------------------------

void CONTROL_SetDeviceState(DeviceState NewState, DeviceSubState NewSubState)
{
	if(NewState == DS_None)
	{
		LL_LedGreen(false);
		SafetyActive = false;
	}

	CONTROL_State = NewState;
	DataTable[REG_DEV_STATE] = NewState;

	CONTROL_SubState = NewSubState;
	DataTable[REG_SUB_STATE] = NewSubState;
}
//------------------------------------------

void CONTROL_UpdateWatchDog()
{
	if(BOOT_LOADER_VARIABLE != BOOT_LOADER_REQUEST)
		IWDG_Refresh();
}
//------------------------------------------

void CONTROL_HandleButtonsAndSensors()
{
	bool Stop, TopSensor, BottomSensor;

	DataTable[REG_BUTTON_START] = LL_GetStateButtonStart();
	DataTable[REG_BUTTON_STOP] = (Stop = LL_GetStateButtonStop());
	DataTable[REG_TOP_SENSOR] = (TopSensor = LL_GetStateSens1());
	DataTable[REG_BOTTOM_SENSOR] = (BottomSensor = LL_GetStateSens2());

	if(SafetyActive && (Stop || TopSensor || BottomSensor))
	{
		CONTROL_StopAndDisconnect();
	}
}
//------------------------------------------
