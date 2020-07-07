#ifndef __COMMUTATIONTABLE_H
#define __COMMUTATIONTABLE_H

#include "stdinc.h"

// Constants
//
#define COMM_CONNECT_GROUP_1					1
#define COMM_CONNECT_GROUP_2					2

#define COMM_NORMAL_MODE 						0
#define COMM_FORCE_MODE 						1

#define SUM_OF_ALL_BYTE_REGISTERS				11
#define COMM_TABLE_SIZE							(SUM_OF_ALL_BYTE_REGISTERS 	* 8)

#define TAB_BIPOLAR_RELAY_BUS_PLUS_CONNECT		2
#define TAB_BIPOLAR_RELAY_BUS_PLUS_DISCONNECT	3
#define TAB_BIPOLAR_RELAY_BUS_MINUS_CONNECT		0
#define TAB_BIPOLAR_RELAY_BUS_MINUS_DISCONNECT	1

// Type Of need comytate line
#define BUSLV_MINUS_TO_POW_1_CON				0
#define BUSLV_MINUS_TO_POW_2_CON				1
#define BUSLV_MINUS_TO_POW_3_CON				2
#define BUSLV_MINUS_TO_POW_4_CON				3
#define BUSLV_MINUS_TO_POW_5_CON				4
#define BUSLV_MINUS_TO_POW_6_CON				5

#define BUSLV_MINUS_TO_POW_1_DIS 				(BUSLV_MINUS_TO_POW_1_CON + 8)
#define BUSLV_MINUS_TO_POW_2_DIS 				(BUSLV_MINUS_TO_POW_2_CON + 8)
#define BUSLV_MINUS_TO_POW_3_DIS 				(BUSLV_MINUS_TO_POW_3_CON + 8)
#define BUSLV_MINUS_TO_POW_4_DIS 				(BUSLV_MINUS_TO_POW_4_CON + 8)
#define BUSLV_MINUS_TO_POW_5_DIS 				(BUSLV_MINUS_TO_POW_5_CON + 8)
#define BUSLV_MINUS_TO_POW_6_DIS 				(BUSLV_MINUS_TO_POW_6_CON + 8)

#define BUSLV_PLUS_TO_POW_1_CON					16
#define BUSLV_PLUS_TO_POW_2_CON					17
#define BUSLV_PLUS_TO_POW_3_CON					18
#define BUSLV_PLUS_TO_POW_4_CON					19
#define BUSLV_PLUS_TO_POW_5_CON					20
#define BUSLV_PLUS_TO_POW_6_CON					21

#define BUS_LV_PLUS_TO_POW_1_DIS 				(BUSLV_PLUS_TO_POW_1_CON + 8)
#define BUS_LV_PLUS_TO_POW_2_DIS 				(BUSLV_PLUS_TO_POW_2_CON + 8)
#define BUS_LV_PLUS_TO_POW_3_DIS 				(BUSLV_PLUS_TO_POW_3_CON + 8)
#define BUS_LV_PLUS_TO_POW_4_DIS 				(BUSLV_PLUS_TO_POW_4_CON + 8)
#define BUS_LV_PLUS_TO_POW_5_DIS 				(BUSLV_PLUS_TO_POW_5_CON + 8)
#define BUS_LV_PLUS_TO_POW_6_DIS 				(BUSLV_PLUS_TO_POW_6_CON + 8)

#define POT_CTRL_PLUS_TO_C1P					32
#define POT_CTRL_PLUS_TO_C2P					33
#define POT_CTRL_PLUS_TO_C3P					34
#define POT_CTRL_PLUS_TO_C4P					35
#define POT_CTRL_MINUS_TO_C1P					36
#define POT_CTRL_MINUS_TO_C2P					37
#define POT_CTRL_MINUS_TO_C3P					38
#define POT_CTRL_MINUS_TO_C4P					39

#define CTRL_1_TO_CTRL1							40
#define CTRL_1_TO_CTRL2							41
#define CTRL_1_TO_CTRL3							42
#define CTRL_1_TO_CTRL4							43
#define CTRL_2_TO_CTRL1							44
#define CTRL_2_TO_CTRL2							45
#define CTRL_2_TO_CTRL3							46
#define CTRL_2_TO_CTRL4							47

#define BUSHV_MINUS_TO_HVPOW_1					48
#define BUSHV_MINUS_TO_HVPOW_2					49
#define BUSHV_MINUS_TO_HVPOW_3					50
#define BUSHV_MINUS_TO_HVPOW_4					51
#define BUSHV_MINUS_TO_HVPOW_5					52
#define BUSHV_MINUS_TO_HVPOW_6					53

#define BUSHV_PLUS_TO_HVPOW_1					56
#define BUSHV_PLUS_TO_HVPOW_2					57
#define BUSHV_PLUS_TO_HVPOW_3					58
#define BUSHV_PLUS_TO_HVPOW_4					59
#define BUSHV_PLUS_TO_HVPOW_5					60
#define BUSHV_PLUS_TO_HVPOW_6					61

#define POT_PLUS_TO_OUTRELAY1					64
#define POT_PLUS_TO_OUTRELAY2					65
#define POT_PLUS_TO_OUTRELAY3					66
#define POT_PLUS_TO_OUTRELAY4					67
#define POT_PLUS_TO_OUTRELAY5					68
#define POT_PLUS_TO_OUTRELAY6					69

#define POT_MINUS_TO_OUTRELAY1					72
#define POT_MINUS_TO_OUTRELAY2					73
#define POT_MINUS_TO_OUTRELAY3					74
#define POT_MINUS_TO_OUTRELAY4					75
#define POT_MINUS_TO_OUTRELAY5					76
#define POT_MINUS_TO_OUTRELAY6					77

#define OUTRELAY1_TO_POT_1						80
#define OUTRELAY2_TO_POT_2						81
#define OUTRELAY3_TO_POT_3						82
#define OUTRELAY4_TO_POT_4						83
#define OUTRELAY5_TO_POT_5						84
#define OUTRELAY6_TO_POT_6						85

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
