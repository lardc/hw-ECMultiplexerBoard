#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// �������
#define ACT_ENABLE_POWER				1	// ������� � ��������� ��������
#define ACT_DISABLE_POWER				2	// ���������� �����
#define ACT_FAULT_CLEAR					3	// ������� fault
#define ACT_WARNING_CLEAR				4	// ������� warning

#define ACT_SET_RELAY_GROUP				20 	// ���������� ������ ����
#define ACT_SET_RELAY_NONE				21 	// ��������� ��� �����

#define ACT_DBG_LED_RED_IMPULSE			50	// ��������� ������� ���� �������� ����������
#define ACT_DBG_LED_GREEN_IMPULSE		51	// ��������� ������� ���� ������� ����������
#define ACT_DBG_SYNC_1_IMPULSE			52	// ��������� ������� ���� SYNC_1
#define ACT_DBG_SYNC_2_IMPULSE			53	// ��������� ������� ���� SYNC_2
#define ACT_DBG_LOCK_1_IMPULSE			54	// ��������� ������� ���� LOCK1
#define ACT_DBG_LOCK_2_IMPULSE			55	// ��������� ������� ���� LOCK2
#define ACT_DBG_SIMPLE_RELAY_ON 		10	// �������� ���� ������� ����
#define ACT_DBG_SIMPLE_RELAY_OFF 		11	// ��������� ���� �������� ����
#define ACT_DBG_BISTABLE_RELAY_ON 		12	// �������� ���� ������������ ����
#define ACT_DBG_BISTABLE_RELAY_OFF		13	// ��������� ���� ������������ ����

#define ACT_SAVE_TO_ROM					200	// ���������� ���������������� ������ �� FLASH ����������
#define ACT_RESTORE_FROM_ROM			201	// �������������� ������ �� FLASH
#define ACT_RESET_TO_DEFAULT			202	// ����� DataTable � ��������� �� ���������

#define ACT_BOOT_LOADER_REQUEST			320	// ���������� ���������� � ����� ��������������������
// -----------------------------

// ��������
// ����������� ��������

// ������������ �������� ������-������
#define REG_TYPE_MEASURE				130	// ��� ���������
#define REG_TYPE_BODY					131	// ��� �������
#define REG_POSITION_OF_BODY			132	// �������
#define REG_TYPE_SIGNAL_CTRL			133	// ��� ����������
#define REG_TYPE_SIGNAL_AT_LEAKAGE		134	// ��� ������� ��� ������
#define REG_TYPE_POLARITY				135	// ���������� �����������

#define REG_DBG_STATE					150	// ������� ������ �������
#define REG_DBG_RELAY_INDEX				151	// ������� ������ ���� �� CommutateTable

// �������� ������ ������
#define REG_DEV_STATE					192	// ������� ���������
#define REG_FAULT_REASON				193	// ������� Fault
#define REG_DISABLE_REASON				194	// ������� Disable
#define REG_WARNING						195	// ������� Warning
#define REG_PROBLEM						196	// ������� Problem
#define REG_OP_RESULT					197	// ������� ���������� ��������
// -----------------------------

// Operation results
#define OPRESULT_NONE					0	// No information or not finished
#define OPRESULT_OK						1	// Operation was successful
#define OPRESULT_FAIL					2	// Operation failed

//  Fault and disable codes
#define DF_NONE							0

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
