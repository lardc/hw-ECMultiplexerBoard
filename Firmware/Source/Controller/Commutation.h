#ifndef __COMMUTATOR_H
#define __COMMUTATOR_H

// Includes
#include "stdinc.h"
#include "CommutationTable.h"

// Variable
bool COMM_ReturnResultConnectGroup(bool *FastSwitch);
bool COMM_HVFastSwitch();

// Functions
void COMM_DisconnectSimpleRelays();
void COMM_DisconnectBistableRelays();
void COMM_SwitchBistableRelay(uint8_t IndexRelay, bool NewState);
void COMM_SwitchSimpleRelay(uint8_t IndexRelay, bool NewState);
void COMM_DisconnectAllRelay();
void COMM_CommutateGroupOnTableNumber(uint16_t NumbOfTable, bool IsDiag);

#endif // __COMMUTATOR_H
