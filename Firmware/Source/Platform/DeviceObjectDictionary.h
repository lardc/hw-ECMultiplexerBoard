#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// �������
#define ACT_ENABLE_POWER				1	// ������� � ��������� ��������
#define ACT_DISABLE_POWER				2	// ���������� �����
#define ACT_FAULT_CLEAR					3	// ������� fault
#define ACT_WARNING_CLEAR				4	// ������� warning

#define ACT_DBG_LED_RED_IMPULSE			10	// ��������� ������� ���� �������� ����������
#define ACT_DBG_LED_GREEN_IMPULSE		11	// ��������� ������� ���� ������� ����������
#define ACT_DBG_SYNC_1_IMPULSE			12	// ��������� ������� ���� SYNC_1
#define ACT_DBG_SYNC_2_IMPULSE			13	// ��������� ������� ���� SYNC_2
#define ACT_DBG_LOCK_1_IMPULSE			14	// ��������� ������� ���� LOCK1
#define ACT_DBG_LOCK_2_IMPULSE			15	// ��������� ������� ���� LOCK2
#define ACT_DBG_RESET_IMPULSE			16	// ��������� ������� ���� RESET
#define ACT_DBG_OE_IMPULSE				17	// ��������� ������� ���� OE
#define ACT_DBG_SET_RELLAY				18	// ���������� �����


#define ACT_SAVE_TO_ROM					200	// ���������� ���������������� ������ �� FLASH ����������
#define ACT_RESTORE_FROM_ROM			201	// �������������� ������ �� FLASH
#define ACT_RESET_TO_DEFAULT			202	// ����� DataTable � ��������� �� ���������

#define ACT_BOOT_LOADER_REQUEST			320	// ���������� ���������� � ����� ��������������������
// -----------------------------

// ��������
// ����������� ��������
#define REG_DBG_STATE					0	// ������� ������ �������

// ������������ �������� ������-������
#define REG_DBG_RELLAY_POT				128	// ������� ��������� ���� ������ POT
#define REG_DBG_RELLAY_POW				129	// ������� ������ POW
#define REG_DBG_RELLAY_POWHV			130	// ������� ������ POWHV
#define REG_DBG_RELLAY_CTRL				131	// ������� ������ CTRL
#define REG_DBG_RELLAY_CTRLPOT			132	// ������� ������ CTRLPOT


// �������� ������ ������
#define REG_DEV_STATE					192	// ������� ���������
#define REG_FAULT_REASON				193	// ������� Fault
#define REG_DISABLE_REASON				194	// ������� Disable
#define REG_WARNING						195	// ������� Warning
#define REG_PROBLEM						196	// ������� Problem
#define REG_OP_RESULT					197	// ������� ���������� ��������
//

// -----------------------------

// Operation results
#define OPRESULT_NONE					0	// No information or not finished
#define OPRESULT_OK						1	// Operation was successful
#define OPRESULT_FAIL					2	// Operation failed

//  Fault and disable codes
#define DF_NONE							0
//#define DF_BATTERY						1	// �������� ������ �������

// Problem
#define PROBLEM_NONE					0

//  Warning
#define WARNING_NONE					0

//  User Errors
#define ERR_NONE						0
#define ERR_CONFIGURATION_LOCKED		1	//  ���������� �������� �� ������
#define ERR_OPERATION_BLOCKED			2	//  �������� �� ����� ���� ��������� � ������� ��������� ����������
#define ERR_DEVICE_NOT_READY			3	//  ���������� �� ������ ��� ����� ���������
#define ERR_WRONG_PWD					4	//  ������������ ����

#endif //  __DEV_OBJ_DIC_H
