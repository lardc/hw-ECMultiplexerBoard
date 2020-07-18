#ifndef __COMMUTATOR_H
#define __COMMUTATOR_H

// Includes
#include "stdinc.h"
#include "CommutationTable.h"

// Functions
//
void COMM_DisconnectAllRelay();
void COMM_ConnectOneRelay(bool TypeOfRelay, uint8_t IndexRelay, bool NewState);
#endif // __COMMUTATOR_H
