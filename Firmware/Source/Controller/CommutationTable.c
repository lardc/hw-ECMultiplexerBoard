// Header
#include "CommutationTable.h"
//
// Defines


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

#define REGISTER_PIN_0		BIT0
#define REGISTER_PIN_1		BIT1
#define REGISTER_PIN_2		BIT2
#define REGISTER_PIN_3		BIT3
#define REGISTER_PIN_4		BIT4
#define REGISTER_PIN_5		BIT5
#define REGISTER_PIN_6		BIT6
#define REGISTER_PIN_7		BIT7

// Constants
//
const CommutationTableItem CommutationTable[COMM_TABLE_SIZE] =
				{

						{REGISTER_F, REGISTER_PIN_0},			// 0	// BUSLV- to POW1 (Connect)
						{REGISTER_F, REGISTER_PIN_1},			// 1	// BUSLV- to POW2 (Connect)
						{REGISTER_F, REGISTER_PIN_2},			// 2	// BUSLV- to POW3 (Connect)
						{REGISTER_F, REGISTER_PIN_3},			// 3	// BUSLV- to POW4 (Connect)
						{REGISTER_F, REGISTER_PIN_4},			// 4	// BUSLV- to POW5 (Connect)
						{REGISTER_F, REGISTER_PIN_5},			// 5	// BUSLV- to POW6 (Connect)
						{REGISTER_F, REGISTER_PIN_6},			// 6	//
						{REGISTER_F, REGISTER_PIN_7},			// 7	//

						{REGISTER_G, REGISTER_PIN_0},			// 8	// BUSLV- to POW1 (Disconnect)
						{REGISTER_G, REGISTER_PIN_1},			// 9	// BUSLV- to POW2 (Disconnect)
						{REGISTER_G, REGISTER_PIN_2},			// 10	// BUSLV- to POW3 (Disconnect)
						{REGISTER_G, REGISTER_PIN_3},			// 11	// BUSLV- to POW4 (Disconnect)
						{REGISTER_G, REGISTER_PIN_4},			// 12	// BUSLV- to POW5 (Disconnect)
						{REGISTER_G, REGISTER_PIN_5},			// 13	// BUSLV- to POW6 (Disconnect)
						{REGISTER_G, REGISTER_PIN_6},			// 14	//
						{REGISTER_G, REGISTER_PIN_7},			// 15	//

						{REGISTER_D, REGISTER_PIN_0},			// 16	// BUSLV+ to POW1 (Connect)
						{REGISTER_D, REGISTER_PIN_1},			// 17	// BUSLV+ to POW2 (Connect)
						{REGISTER_D, REGISTER_PIN_2},			// 18	// BUSLV+ to POW3 (Connect)
						{REGISTER_D, REGISTER_PIN_3},			// 19	// BUSLV+ to POW4 (Connect)
						{REGISTER_D, REGISTER_PIN_4},			// 20	// BUSLV+ to POW5 (Connect)
						{REGISTER_D, REGISTER_PIN_5},			// 21	// BUSLV+ to POW6 (Connect)
						{REGISTER_D, REGISTER_PIN_6},			// 22	//
						{REGISTER_D, REGISTER_PIN_7},			// 23	//

						{REGISTER_E, REGISTER_PIN_0},			// 24	// BUSLV+ to POW1 (Disconnect)
						{REGISTER_E, REGISTER_PIN_1},			// 25   // BUSLV+ to POW2 (Disconnect)
						{REGISTER_E, REGISTER_PIN_2},			// 26   // BUSLV+ to POW3 (Disconnect)
						{REGISTER_E, REGISTER_PIN_3},			// 27   // BUSLV+ to POW4 (Disconnect)
						{REGISTER_E, REGISTER_PIN_4},			// 28   // BUSLV+ to POW5 (Disconnect)
						{REGISTER_E, REGISTER_PIN_5},			// 29   // BUSLV+ to POW6 (Disconnect)
						{REGISTER_E, REGISTER_PIN_6},			// 30   //
						{REGISTER_E, REGISTER_PIN_7},			// 31   //

						{REGISTER_K, REGISTER_PIN_0},			// 32	// POT_CTRL_PLUS to external C1P (CTRL_1_POT)
						{REGISTER_K, REGISTER_PIN_1},			// 33	// POT_CTRL_PLUS to external C2P
						{REGISTER_K, REGISTER_PIN_2},			// 34	// POT_CTRL_PLUS to external C3P
						{REGISTER_K, REGISTER_PIN_3},			// 35	// POT_CTRL_PLUS to external C4P
						{REGISTER_K, REGISTER_PIN_4},			// 36	// POT_CTRL_MINUS to external C1P
						{REGISTER_K, REGISTER_PIN_5},			// 37	// POT_CTRL_MINUS to external C2P
						{REGISTER_K, REGISTER_PIN_6},			// 38	// POT_CTRL_MINUS to external C3P
						{REGISTER_K, REGISTER_PIN_7},			// 39	// POT_CTRL_MINUS to external C4P

						{REGISTER_J, REGISTER_PIN_0},			// 40	// CTRL1 to external CTRL1
						{REGISTER_J, REGISTER_PIN_1},			// 41	// CTRL1 to external CTRL2
						{REGISTER_J, REGISTER_PIN_2},			// 42	// CTRL1 to external CTRL3
						{REGISTER_J, REGISTER_PIN_3},			// 43	// CTRL1 to external CTRL4
						{REGISTER_J, REGISTER_PIN_4},			// 44	// CTRL2 to external CTRL1
						{REGISTER_J, REGISTER_PIN_5},			// 45	// CTRL2 to external CTRL2
						{REGISTER_J, REGISTER_PIN_6},			// 46	// CTRL2 to external CTRL3
						{REGISTER_J, REGISTER_PIN_7},			// 47	// CTRL2 to external CTRL4

						{REGISTER_I, REGISTER_PIN_0},			// 48	// BUSHV- to HVPOW1
						{REGISTER_I, REGISTER_PIN_1},			// 49	// BUSHV- to HVPOW2
						{REGISTER_I, REGISTER_PIN_2},			// 50	// BUSHV- to HVPOW3
						{REGISTER_I, REGISTER_PIN_3},			// 51	// BUSHV- to HVPOW4
						{REGISTER_I, REGISTER_PIN_4},			// 52	// BUSHV- to HVPOW5
						{REGISTER_I, REGISTER_PIN_5},			// 53	// BUSHV- to HVPOW6
						{REGISTER_I, REGISTER_PIN_6},			// 54	//
						{REGISTER_I, REGISTER_PIN_7},			// 55	//

						{REGISTER_H, REGISTER_PIN_0},			// 56	// BUSHV+ to HVPOW1
						{REGISTER_H, REGISTER_PIN_1},			// 57	// BUSHV+ to HVPOW2
						{REGISTER_H, REGISTER_PIN_2},			// 58	// BUSHV+ to HVPOW3
						{REGISTER_H, REGISTER_PIN_3},			// 59	// BUSHV+ to HVPOW4
						{REGISTER_H, REGISTER_PIN_4},			// 60	// BUSHV+ to HVPOW5
						{REGISTER_H, REGISTER_PIN_5},			// 61	// BUSHV+ to HVPOW6
						{REGISTER_H, REGISTER_PIN_6},			// 62	//
						{REGISTER_H, REGISTER_PIN_7},			// 63	//

						{REGISTER_A, REGISTER_PIN_0},			// 64	// POT+ to OutRelay0
						{REGISTER_A, REGISTER_PIN_1},			// 65	// POT+ to OutRelay1
						{REGISTER_A, REGISTER_PIN_2},			// 66	// POT+ to OutRelay2
						{REGISTER_A, REGISTER_PIN_3},			// 67	// POT+ to OutRelay3
						{REGISTER_A, REGISTER_PIN_4},			// 68	// POT+ to OutRelay4
						{REGISTER_A, REGISTER_PIN_5},			// 69	// POT+ to OutRelay5
						{REGISTER_A, REGISTER_PIN_6},			// 70
						{REGISTER_A, REGISTER_PIN_7},			// 71

						{REGISTER_B, REGISTER_PIN_0},			// 72	// POT- to OutRelay0
						{REGISTER_B, REGISTER_PIN_1},			// 73	// POT- to OutRelay1
						{REGISTER_B, REGISTER_PIN_2},			// 74	// POT- to OutRelay2
						{REGISTER_B, REGISTER_PIN_3},			// 75	// POT- to OutRelay3
						{REGISTER_B, REGISTER_PIN_4},			// 76	// POT- to OutRelay4
						{REGISTER_B, REGISTER_PIN_5},			// 77	// POT- to OutRelay5
						{REGISTER_B, REGISTER_PIN_6},			// 78
						{REGISTER_B, REGISTER_PIN_7},			// 79

						{REGISTER_C, REGISTER_PIN_0},			// 80	// OutRelay0 to POT1
						{REGISTER_C, REGISTER_PIN_1},			// 81	// OutRelay1 to POT2
						{REGISTER_C, REGISTER_PIN_2},			// 82	// OutRelay2 to POT3
						{REGISTER_C, REGISTER_PIN_3},			// 83	// OutRelay3 to POT4
						{REGISTER_C, REGISTER_PIN_4},			// 84	// OutRelay4 to POT5
						{REGISTER_C, REGISTER_PIN_5},			// 85	// OutRelay5 to POT6
						{REGISTER_C, REGISTER_PIN_6},			// 86
						{REGISTER_C, REGISTER_PIN_7},			// 87

				};
