#ifndef __COMMUTATOR_H
#define __COMMUTATOR_H

#include "stdinc.h"
#include "ZwSPI.h"

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
