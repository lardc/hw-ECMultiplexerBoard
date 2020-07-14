#ifndef __COMMUTATOR_H
#define __COMMUTATOR_H

#include "stdinc.h"
#include "ZwSPI.h"


#define REGISTERS_NUM		11

#define REGISTER_A			8
#define REGISTER_B			9
#define REGISTER_C			10
#define REGISTER_D			2
#define REGISTER_E			3
#define REGISTER_F			0
#define REGISTER_G			1
#define REGISTER_H			7
#define REGISTER_I			6
#define REGISTER_J			5
#define REGISTER_K			4

typedef struct __RegisterPin
{
	uint8_t Register;
	uint8_t Bit;
} RegisterPin;
#define COMM_RegisterPin static const RegisterPin

typedef struct __BistableSwitch
{
	RegisterPin TurnOn1;
	RegisterPin TurnOn2;
	RegisterPin TurnOff1;
	RegisterPin TurnOff2;
} BistableSwitch;
#define COMM_BistableSwitch static const BistableSwitch

// Пример инициализации для простого реле
COMM_RegisterPin COMM_SwitchPOTPlusToPOT1 = {REGISTER_A, BIT0};

// Пример инициализации бистабильного ключа
COMM_BistableSwitch COMM_SwitchBUSLVPlusToPOW1 = {{REGISTER_A, BIT1}, {REGISTER_A, BIT2}, {REGISTER_A, BIT3}, {REGISTER_A, BIT4}};


// Macros
//
#define TYPE_RELAY_NORMAL		0
#define TYPE_RELAY_BISTABLE		1

// Functions
//

void COMM_OutputValuesCompose(Int8U TableID, Boolean State);
void COMM_RegisterReset();
void COMM_DisconnectAllRelay();
void COMM_SetRelayInMode(Boolean Mode);
void COMM_OutputValuesReset();
void COMM_CorrectBipolarRelay(Int8U ConnectTable, Int8U DisconnectTable);
void COMM_SendStateToRelay(Boolean TypeRelay);
void COMM_PrepareDataForBistableRelay();
void COMM_ConnectGroup(Int8U Group);
void COMM_TransferDataRawToNewOutputValues();

#endif // __COMMUTATOR_H
