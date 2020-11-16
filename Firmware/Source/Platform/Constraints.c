// -----------------------------------------
// Global definitions
// ----------------------------------------

// Header
#include "Constraints.h"
#include "CommutationTable.h"

// Constants
//
const TableItemConstraint NVConstraint[DATA_TABLE_NV_SIZE] = {
		{0, 0, 0},																	// 0
		{0, 0, 0},																	// 1
		{0, 0, 0},																	// 2
		{0, 0, 0},																	// 3
		{0, 0, 0},																	// 4
		{0, 0, 0},																	// 5
		{0, 0, 0},																	// 6
		{0, 0, 0},																	// 7
		{0, 0, 0},																	// 8
		{0, 0, 0},																	// 9
		{0, 0, 0},																	// 10
		{0, 0, 0},																	// 11
		{0, 0, 0},																	// 12
		{0, 0, 0},																	// 13
		{0, 0, 0},																	// 14
		{0, 0, 0},																	// 15
		{0, 0, 0},																	// 16
		{0, 0, 0},																	// 17
		{0, 0, 0},																	// 18
		{0, 0, 0},																	// 19
		{0, 0, 0},																	// 20
		{0, 0, 0},																	// 21
		{0, 0, 0},																	// 22
		{0, 0, 0},																	// 23
		{0, 0, 0},																	// 24
		{0, 0, 0},																	// 25
		{0, 0, 0},																	// 26
		{0, 0, 0},																	// 27
		{0, 0, 0},																	// 28
		{0, 0, 0},																	// 29
		{0, 0, 0},																	// 30
		{0, 0, 0},																	// 31
		{0, 0, 0},																	// 32
		{0, 0, 0},																	// 33
		{0, 0, 0},																	// 34
		{0, 0, 0},																	// 35
		{0, 0, 0},																	// 36
		{0, 0, 0},																	// 37
		{0, 0, 0},																	// 38
		{0, 0, 0},																	// 39
		{0, 0, 0},																	// 40
		{0, 0, 0},																	// 41
		{0, 0, 0},																	// 42
		{0, 0, 0},																	// 43
		{0, 0, 0},																	// 44
		{0, 0, 0},																	// 45
		{0, 0, 0},																	// 46
		{0, 0, 0},																	// 47
		{0, 0, 0},																	// 48
		{0, 0, 0},																	// 49
		{0, 0, 0},																	// 50
		{0, 0, 0},																	// 51
		{0, 0, 0},																	// 52
		{0, 0, 0},																	// 53
		{0, 0, 0},																	// 54
		{0, 0, 0},																	// 55
		{0, 0, 0},																	// 56
		{0, 0, 0},																	// 57
		{0, 0, 0},																	// 58
		{0, 0, 0},																	// 59
		{0, 0, 0},																	// 60
		{0, 0, 0},																	// 61
		{0, 0, 0},																	// 62
		{0, 0, 0},																	// 63
		{0, 0, 0},																	// 64
		{0, 0, 0},																	// 65
		{0, 0, 0},																	// 66
		{0, 0, 0},																	// 67
		{0, 0, 0},																	// 68
		{0, 0, 0},																	// 69
		{0, 0, 0},																	// 70
		{0, 0, 0},																	// 71
		{0, 0, 0},																	// 72
		{0, 0, 0},																	// 73
		{0, 0, 0},																	// 74
		{0, 0, 0},																	// 75
		{0, 0, 0},																	// 76
		{0, 0, 0},																	// 77
		{0, 0, 0},																	// 78
		{0, 0, 0},																	// 79
		{0, 0, 0},																	// 80
		{0, 0, 0},																	// 81
		{0, 0, 0},																	// 82
		{0, 0, 0},																	// 83
		{0, 0, 0},																	// 84
		{0, 0, 0},																	// 85
		{0, 0, 0},																	// 86
		{0, 0, 0},																	// 87
		{0, 0, 0},																	// 88
		{0, 0, 0},																	// 89
		{0, 0, 0},																	// 90
		{0, 0, 0},																	// 91
		{0, 0, 0},																	// 92
		{0, 0, 0},																	// 93
		{0, 0, 0},																	// 94
		{0, 0, 0},																	// 95
		{0, 0, 0},																	// 96
		{0, 0, 0},																	// 97
		{0, 0, 0},																	// 98
		{0, 0, 0},																	// 99
		{0, 0, 0},																	// 100
		{0, 0, 0},																	// 101
		{0, 0, 0},																	// 102
		{0, 0, 0},																	// 103
		{0, 0, 0},																	// 104
		{0, 0, 0},																	// 105
		{0, 0, 0},																	// 106
		{0, 0, 0},																	// 107
		{0, 0, 0},																	// 108
		{0, 0, 0},																	// 109
		{0, 0, 0},																	// 110
		{0, 0, 0},																	// 111
		{0, 0, 0},																	// 112
		{0, 0, 0},																	// 113
		{0, 0, 0},																	// 114
		{0, 0, 0},																	// 115
		{0, 0, 0},																	// 116
		{0, 0, 0},																	// 117
		{0, 0, 0},																	// 118
		{0, 0, 0},																	// 119
		{0, 0, 0},																	// 120
		{0, 0, 0},																	// 121
		{0, 0, 0},																	// 122
		{0, 0, 0},																	// 123
		{0, 0, 0},																	// 124
		{0, 0, 0},																	// 125
		{0, 0, 0},																	// 126
		{0, 0, 0}																	// 127
};

const TableItemConstraint VConstraint[DATA_TABLE_WP_START - DATA_TABLE_WR_START] = {
		{0, 0, 0},																	// 128
		{0, 0, 0},																	// 129
		{COMM_MEAS_CURR_LEAK, COMM_CALIBRATE_CURRENT, COMM_MEAS_CURR_LEAK},			// 130
		{CASE_A1, CASE_D192, CASE_A1},												// 131
		{POS_1, POS_3, POS_1},														// 132
		{CTRL_DC_V, CTRL_AC_V, CTRL_DC_V},											// 133
		{LEAK_DC, LEAK_AC, LEAK_DC},												// 134
		{DIRECT, REVERSE, DIRECT},													// 135
		{NO, YES, NO},																// 136
		{0, 0, 0},																	// 137
		{0, 0, 0},																	// 138
		{0, 0, 0},																	// 139
		{0, MAX_COUNTER_TABLE, 0},													// 140
		{0, 0, 0},																	// 141
		{0, 0, 0},																	// 142
		{0, 0, 0},																	// 143
		{0, 0, 0},																	// 144
		{0, 0, 0},																	// 145
		{0, 0, 0},																	// 146
		{0, 0, 0},																	// 147
		{0, 0, 0},																	// 148
		{0, 0, 0},																	// 149
		{NO, YES, NO},																// 150
		{0, MAX_NUM_RELAY, 0},														// 151
		{0, 0, 0},																	// 152
		{0, 0, 0},																	// 153
		{0, 0, 0},																	// 154
		{0, 0, 0},																	// 155
		{0, 0, 0},																	// 156
		{0, 0, 0},																	// 157
		{0, 0, 0},																	// 158
		{0, 0, 0},																	// 159
		{0, 0, 0},																	// 160
		{0, 0, 0},																	// 161
		{0, 0, 0},																	// 162
		{0, 0, 0},																	// 163
		{0, 0, 0},																	// 164
		{0, 0, 0},																	// 165
		{0, 0, 0},																	// 166
		{0, 0, 0},																	// 167
		{0, 0, 0},																	// 168
		{0, 0, 0},																	// 169
		{0, 0, 0},																	// 170
		{0, 0, 0},																	// 171
		{0, 0, 0},																	// 172
		{0, 0, 0},																	// 173
		{0, 0, 0},																	// 174
		{0, 0, 0},																	// 175
		{0, 0, 0},																	// 176
		{0, 0, 0},																	// 177
		{0, 0, 0},																	// 178
		{0, 0, 0},																	// 179
		{0, 0, 0},																	// 180
		{0, 0, 0},																	// 181
		{0, 0, 0},																	// 182
		{0, 0, 0},																	// 183
		{0, 0, 0},																	// 184
		{0, 0, 0},																	// 185
		{0, 0, 0},																	// 186
		{0, 0, 0},																	// 187
		{0, 0, 0},																	// 188
		{0, 0, 0},																	// 189
		{0, 0, 0},																	// 190
		{0, 0, 0}																	// 191
};
