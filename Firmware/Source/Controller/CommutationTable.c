// Header
#include "CommutationTable.h"

#define COMM_POTPlusToPOT1 				(uint64_t) 1 << 0
#define COMM_POTPlusToPOT2 				(uint64_t) 1 << 1
#define COMM_POTPlusToPOT3 				(uint64_t) 1 << 2
#define COMM_POTPlusToPOT4 				(uint64_t) 1 << 3
#define COMM_POTPlusToPOT5 				(uint64_t) 1 << 4
#define COMM_POTPlusToPOT6 				(uint64_t) 1 << 5

#define COMM_POTMinusToPOT1 			(uint64_t) 1 << 6
#define COMM_POTMinusToPOT2 			(uint64_t) 1 << 7
#define COMM_POTMinusToPOT3 			(uint64_t) 1 << 8
#define COMM_POTMinusToPOT4 			(uint64_t) 1 << 9
#define COMM_POTMinusToPOT5 			(uint64_t) 1 << 10
#define COMM_POTMinusToPOT6 			(uint64_t) 1 << 11

#define COMM_POTOutToPOT1 				(uint64_t) 1 << 12
#define COMM_POTOutToPOT2 				(uint64_t) 1 << 13
#define COMM_POTOutToPOT3 				(uint64_t) 1 << 14
#define COMM_POTOutToPOT4 				(uint64_t) 1 << 15
#define COMM_POTOutToPOT5 				(uint64_t) 1 << 16
#define COMM_POTOutToPOT6 				(uint64_t) 1 << 17

#define COMM_BUSHVPlusToPOW1 			(uint64_t) 1 << 18
#define COMM_BUSHVPlusToPOW2 			(uint64_t) 1 << 19
#define COMM_BUSHVPlusToPOW3 			(uint64_t) 1 << 20
#define COMM_BUSHVPlusToPOW4 			(uint64_t) 1 << 21
#define COMM_BUSHVPlusToPOW5 			(uint64_t) 1 << 22
#define COMM_BUSHVPlusToPOW6 			(uint64_t) 1 << 23

#define COMM_BUSHVMinusToPOW1			(uint64_t) 1 << 24
#define COMM_BUSHVMinusToPOW2			(uint64_t) 1 << 25
#define COMM_BUSHVMinusToPOW3			(uint64_t) 1 << 26
#define COMM_BUSHVMinusToPOW4			(uint64_t) 1 << 27
#define COMM_BUSHVMinusToPOW5			(uint64_t) 1 << 28
#define COMM_BUSHVMinusToPOW6			(uint64_t) 1 << 29

#define COMM_Ctrl1ToCtrl1 				(uint64_t) 1 << 30
#define COMM_Ctrl1ToCtrl2 				(uint64_t) 1 << 31
#define COMM_Ctrl1ToCtrl3 				(uint64_t) 1 << 32
#define COMM_Ctrl1ToCtrl4 				(uint64_t) 1 << 33
#define COMM_Ctrl2ToCtrl1 				(uint64_t) 1 << 34
#define COMM_Ctrl2ToCtrl2 				(uint64_t) 1 << 35
#define COMM_Ctrl2ToCtrl3 				(uint64_t) 1 << 36
#define COMM_Ctrl2ToCtrl4 				(uint64_t) 1 << 37

#define COMM_PotCtrlPlusToCtrlPot1 		(uint64_t) 1 << 38
#define COMM_PotCtrlPlusToCtrlPot2 		(uint64_t) 1 << 39
#define COMM_PotCtrlPlusToCtrlPot3 		(uint64_t) 1 << 40
#define COMM_PotCtrlPlusToCtrlPot4 		(uint64_t) 1 << 41
#define COMM_PotCtrlMinusToCtrlPot1 	(uint64_t) 1 << 42
#define COMM_PotCtrlMinusToCtrlPot2 	(uint64_t) 1 << 43
#define COMM_PotCtrlMinusToCtrlPot3 	(uint64_t) 1 << 44
#define COMM_PotCtrlMinusToCtrlPot4 	(uint64_t) 1 << 45

#define COMM_BUSLVPlusToPOW1 			(uint64_t) 1 << 46
#define COMM_BUSLVPlusToPOW2 			(uint64_t) 1 << 47
#define COMM_BUSLVPlusToPOW3 			(uint64_t) 1 << 48
#define COMM_BUSLVPlusToPOW4 			(uint64_t) 1 << 49
#define COMM_BUSLVPlusToPOW5 			(uint64_t) 1 << 50
#define COMM_BUSLVPlusToPOW6 			(uint64_t) 1 << 51

#define COMM_BUSLVMinusToPOW1 			(uint64_t) 1 << 52
#define COMM_BUSLVMinusToPOW2 			(uint64_t) 1 << 53
#define COMM_BUSLVMinusToPOW3 			(uint64_t) 1 << 54
#define COMM_BUSLVMinusToPOW4 			(uint64_t) 1 << 55
#define COMM_BUSLVMinusToPOW5 			(uint64_t) 1 << 56
#define COMM_BUSLVMinusToPOW6 			(uint64_t) 1 << 57

const RegisterPin* const COMM_SimpleRelayArray[] = {&COMM_SwitchPOTPlusToPOT1,					// 0
		&COMM_SwitchPOTPlusToPOT2,					// 1
		&COMM_SwitchPOTPlusToPOT3,					// 2
		&COMM_SwitchPOTPlusToPOT4,					// 3
		&COMM_SwitchPOTPlusToPOT5,					// 4
		&COMM_SwitchPOTPlusToPOT6,					// 5

		&COMM_SwitchPOTMinusToPOT1,					// 6
		&COMM_SwitchPOTMinusToPOT2,					// 7
		&COMM_SwitchPOTMinusToPOT3,					// 8
		&COMM_SwitchPOTMinusToPOT4,					// 9
		&COMM_SwitchPOTMinusToPOT5,					// 10
		&COMM_SwitchPOTMinusToPOT6,					// 11

		&COMM_SwitchPOTOutToPOT1,					// 12
		&COMM_SwitchPOTOutToPOT2,					// 13
		&COMM_SwitchPOTOutToPOT3,					// 14
		&COMM_SwitchPOTOutToPOT4,					// 15
		&COMM_SwitchPOTOutToPOT5,					// 16
		&COMM_SwitchPOTOutToPOT6,					// 17

		&COMM_SwitchBUSHVPlusToPOW1,				// 18
		&COMM_SwitchBUSHVPlusToPOW2,				// 19
		&COMM_SwitchBUSHVPlusToPOW3,				// 20
		&COMM_SwitchBUSHVPlusToPOW4,				// 21
		&COMM_SwitchBUSHVPlusToPOW5,				// 22
		&COMM_SwitchBUSHVPlusToPOW6,				// 23

		&COMM_SwitchBUSHVMinusToPOW1,				// 24
		&COMM_SwitchBUSHVMinusToPOW2,				// 25
		&COMM_SwitchBUSHVMinusToPOW3,				// 26
		&COMM_SwitchBUSHVMinusToPOW4,				// 27
		&COMM_SwitchBUSHVMinusToPOW5,				// 28
		&COMM_SwitchBUSHVMinusToPOW6,				// 29

		&COMM_SwitchCtrl1ToCtrl1,					// 30
		&COMM_SwitchCtrl1ToCtrl2,					// 31
		&COMM_SwitchCtrl1ToCtrl3,					// 32
		&COMM_SwitchCtrl1ToCtrl4,					// 33
		&COMM_SwitchCtrl2ToCtrl1,					// 34
		&COMM_SwitchCtrl2ToCtrl2,					// 35
		&COMM_SwitchCtrl2ToCtrl3,					// 36
		&COMM_SwitchCtrl2ToCtrl4,					// 37

		&COMM_SwitchPotCtrlPlusToCtrlPot1,			// 38
		&COMM_SwitchPotCtrlPlusToCtrlPot2,			// 39
		&COMM_SwitchPotCtrlPlusToCtrlPot3,			// 40
		&COMM_SwitchPotCtrlPlusToCtrlPot4,			// 41
		&COMM_SwitchPotCtrlMinusToCtrlPot1,			// 42
		&COMM_SwitchPotCtrlMinusToCtrlPot2,			// 43
		&COMM_SwitchPotCtrlMinusToCtrlPot3,			// 44
		&COMM_SwitchPotCtrlMinusToCtrlPot4			// 45
		};

const BistableSwitch* const COMM_BistableRelayArray[] = {&COMM_SwitchBUSLVPlusToPOW1,				// 0
		&COMM_SwitchBUSLVPlusToPOW2,				// 1
		&COMM_SwitchBUSLVPlusToPOW3,				// 2
		&COMM_SwitchBUSLVPlusToPOW4,				// 3
		&COMM_SwitchBUSLVPlusToPOW5,				// 4
		&COMM_SwitchBUSLVPlusToPOW6,				// 5

		&COMM_SwitchBUSLVMinusToPOW1,				// 6
		&COMM_SwitchBUSLVMinusToPOW2,				// 7
		&COMM_SwitchBUSLVMinusToPOW3,				// 8
		&COMM_SwitchBUSLVMinusToPOW4,				// 9
		&COMM_SwitchBUSLVMinusToPOW5,				// 10
		&COMM_SwitchBUSLVMinusToPOW6				// 11
		};

void COMM_MakeMeasCommutateTable(uint8_t NumbTable, uint8_t TypeMeasure, uint8_t TypeBody, uint8_t TypePositionOfBody,
		uint8_t TypeCtrl, uint8_t TypeSignalAsLeakAge, uint8_t SignalDirection, uint64_t NumRelay);

void COMM_InitTable();

void COMM_InitTable()
{
//MEAS_CURR_LEAK
	COMM_MakeMeasCommutateTable(0, COMM_MEAS_CURR_LEAK, BODY_A1, POS_1, CTRL_DC_V, LEAK_DC, FORVARD, COMM_BUSHVPlusToPOW1 | COMM_BUSHVMinusToPOW2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2	| COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

	COMM_MakeMeasCommutateTable(1, COMM_MEAS_CURR_LEAK, BODY_A1, POS_1, CTRL_DC_V, LEAK_DC, REVERS, 	COMM_BUSHVPlusToPOW2 | COMM_BUSHVMinusToPOW1 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2	| COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

//	MEAS_IN_VOLT
	COMM_MakeMeasCommutateTable(2, COMM_MEAS_IN_VOLT, BODY_A1, POS_1, CTRL_DC_V, LEAK_NO, FORVARD, COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1 | COMM_PotCtrlMinusToCtrlPot2);

// MEAS_DROP_VOLT
	COMM_MakeMeasCommutateTable(3, COMM_MEAS_DROP_VOLT, BODY_A1, POS_1, CTRL_DC_V, LEAK_NO, FORVARD, COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTOutToPOT1 | COMM_POTMinusToPOT2| COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1| COMM_PotCtrlMinusToCtrlPot2);

// MEAS_VOLT_BAN
	COMM_MakeMeasCommutateTable(4, COMM_MEAS_VOLT_BAN, BODY_A1, POS_1, CTRL_DC_V, LEAK_NO, FORVARD,	COMM_BUSLVPlusToPOW1 | COMM_BUSLVMinusToPOW2 | COMM_POTPlusToPOT1 | COMM_POTOutToPOT1 | COMM_POTMinusToPOT2| COMM_POTOutToPOT2 | COMM_Ctrl1ToCtrl1 | COMM_Ctrl2ToCtrl2 | COMM_PotCtrlPlusToCtrlPot1| COMM_PotCtrlMinusToCtrlPot2);
}

void COMM_MakeMeasCommutateTable(uint8_t NumbTable, uint8_t TypeMeasure, uint8_t TypeBody, uint8_t TypePositionOfBody,
		uint8_t TypeCtrl, uint8_t TypeSignalAsLeakAge, uint8_t SignalDirection, uint64_t NumRelay)
{
	COMM_Table[NumbTable].TypeMeasure = TypeMeasure;
	COMM_Table[NumbTable].TypeBody = TypeBody;
	COMM_Table[NumbTable].TypePositionOfBody = TypePositionOfBody;
	COMM_Table[NumbTable].TypeCtrl = TypeCtrl;
	COMM_Table[NumbTable].TypeSignalAsLeakAge = TypeSignalAsLeakAge;
	COMM_Table[NumbTable].SignalDirection = SignalDirection;
	COMM_Table[NumbTable].Relay = NumRelay;
}
