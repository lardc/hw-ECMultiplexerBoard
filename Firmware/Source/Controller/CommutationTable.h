#ifndef __COMMUTATIONTABLE_H
#define __COMMUTATIONTABLE_H

#include "stdinc.h"

// Constants
//

#define SUM_OF_ALL_BYTE_REGISTERS		11
#define COMM_TABLE_SIZE					(SUM_OF_ALL_BYTE_REGISTERS 		* 8)

#define TAB_BIPOLAR_RELAY_BUS_PLUS_CONNECT		2
#define TAB_BIPOLAR_RELAY_BUS_PLUS_DISCONNECT	3
#define TAB_BIPOLAR_RELAY_BUS_MINUS_CONNECT		0
#define TAB_BIPOLAR_RELAY_BUS_MINUS_DISCONNECT	1

#define BUS_LV_MINUS_TO_POW_1_CONN				0
#define BUS_LV_PLUS_TO_POW_4_CONN				19

#define POT_PLUS_TO_OUT_RELAY2					66
#define POT_MINUS_TO_OUT_RELAY5					77
#define OUT_RELAY2_TO_POT3						82
#define OUT_RELAY5_TO_POT6						85

#define CTRL_1_TO_CTRL3							42
#define CTRL_2_TO_CTRL1							44

#define POT_CTRL_PLUS_TO_C2P					33
#define POT_CTRL_MINUS_TO_C4P					39

#define BUS_LV_MINUS_TO_POW_1_DISCONN 		(BUS_LV_MINUS_TO_POW_1_CONN + 8)
#define BUS_LV_PLUS_TO_POW_4_DISCONN 		(BUS_LV_PLUS_TO_POW_1_CONN + 8)

// Types
//
typedef struct __CommutationTableItem
{
	Int32U TypeRelay;
	Int32U Bit;
} CommutationTableItem;

// Variables
//
extern const CommutationTableItem CommutationTable[COMM_TABLE_SIZE];

#endif /* CONTROLLER_COMMUTATIONTABLE_H_ */
