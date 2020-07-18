#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// �������
#define ACT_ENABLE_POWER				1	// ������� � ��������� ��������
#define ACT_DISABLE_POWER				2	// ���������� �����
#define ACT_FAULT_CLEAR					3	// ������� fault
#define ACT_WARNING_CLEAR				4	// ������� warning

#define ACT_SET_RELAY_GROUP				20 	// ���������� ������ ����
#define ACT_SET_RELAY_NONE				21 	// ��������� ��� �����

#define ACT_SET_RELAY_RAW				30 	// ��������� ���� � ������ (REG_RAW)

#define ACT_DBG_LED_RED_IMPULSE			50	// ��������� ������� ���� �������� ����������
#define ACT_DBG_LED_GREEN_IMPULSE		51	// ��������� ������� ���� ������� ����������
#define ACT_DBG_SYNC_1_IMPULSE			52	// ��������� ������� ���� SYNC_1
#define ACT_DBG_SYNC_2_IMPULSE			53	// ��������� ������� ���� SYNC_2
#define ACT_DBG_LOCK_1_IMPULSE			54	// ��������� ������� ���� LOCK1
#define ACT_DBG_LOCK_2_IMPULSE			55	// ��������� ������� ���� LOCK2
#define ACT_DBG_RESET_IMPULSE			56	// ��������� ������� ���� RESET
#define ACT_DBG_OE_IMPULSE				57	// ��������� ������� ���� OE

#define ACT_SAVE_TO_ROM					200	// ���������� ���������������� ������ �� FLASH ����������
#define ACT_RESTORE_FROM_ROM			201	// �������������� ������ �� FLASH
#define ACT_RESET_TO_DEFAULT			202	// ����� DataTable � ��������� �� ���������

#define ACT_BOOT_LOADER_REQUEST			320	// ���������� ���������� � ����� ��������������������
// -----------------------------

// ��������
// ����������� ��������

// ������������ �������� ������-������
#define REG_DBG_STATE					128	// ������� ������ �������
#define REG_RAW_RELAY_BUS_MINUS_CO		130	// ������� ��������� ���� ������ BUSLV- (Connect)
#define REG_RAW_RELAY_BUS_MINUS_DISCO	131	// ������� ��������� ���� ������ BUSLV- (Disconnect)
#define REG_RAW_RELAY_BUS_PLUS_CO		132	// ������� ��������� ���� ������ BUSLV+ (Connect)
#define REG_RAW_RELAY_BUS_PLUS_DISCO	133	// ������� ��������� ���� ������ BUSLV+ (Disconnect)
#define REG_RAW_RELAY_POT_CTRL			134	// ������� ��������� ���� ������ POT CTR
#define REG_RAW_RELAY_CTRL				135	// ������� ��������� ���� ������ CTRL
#define REG_RAW_RELAY_BUSHV_MINUS		136	// ������� ��������� ���� ������ BUSHV-
#define REG_RAW_RELAY_BUSHV_PLUS		137	// ������� ��������� ���� ������ BUSHV+
#define REG_RAW_RELAY_POT_PLUS			138	// ������� ��������� ���� ������ POT+
#define REG_RAW_RELAY_POT_MINUS			139	// ������� ��������� ���� ������ POT-
#define REG_RAW_RELAY_OUTRELAY			140	// ������� ��������� ���� ������ OutRelay

#define REG_GROUP_RELAY					150	// ������� ��������� ���������������� ������

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
