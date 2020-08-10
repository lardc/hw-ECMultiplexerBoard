// Header
#include "CommutationTable.h"

const RegisterPin* const COMM_SimpleRelayArray[] = {
		&COMM_SwitchPOTPlusToPOT1,					// 0
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

const BistableSwitch* const COMM_BistableRelayArray[] = {
		&COMM_SwitchBUSLVPlusToPOW1,				// 0
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
