#ifndef __COMMUTATOR_H
#define __COMMUTATOR_H

// Includes
#include "stdinc.h"
#include "CommutationTable.h"

// Functions
//
void COMM_DisconnectAllRelay();
void COMM_ConnectRelayGroup(uint8_t Group);
void COMM_SetRelayFromRAW();

#endif // __COMMUTATOR_H
