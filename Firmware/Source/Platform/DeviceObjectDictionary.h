#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// Команды
#define ACT_ENABLE_POWER				1	// Переход в состояние ожидания
#define ACT_DISABLE_POWER				2	// Отключение блока
#define ACT_FAULT_CLEAR					3	// Очистка fault
#define ACT_WARNING_CLEAR				4	// Очистка warning

#define ACT_SET_RELAY_GROUP				20 	// Подключить группу реле
#define ACT_SET_RELAY_NONE				21 	// Отключить все релле

#define ACT_SET_RELAY_RAW				30 	// Подкючить реле в ручную (REG_RAW)

#define ACT_DBG_LED_RED_IMPULSE			50	// Одиночный импусль цепи красного индикатора
#define ACT_DBG_LED_GREEN_IMPULSE		51	// Одиночный импусль цепи зелёного индикатора
#define ACT_DBG_SYNC_1_IMPULSE			52	// Одиночный импусль цепи SYNC_1
#define ACT_DBG_SYNC_2_IMPULSE			53	// Одиночный импусль цепи SYNC_2
#define ACT_DBG_LOCK_1_IMPULSE			54	// Одиночный импусль цепи LOCK1
#define ACT_DBG_LOCK_2_IMPULSE			55	// Одиночный импусль цепи LOCK2
#define ACT_DBG_RESET_IMPULSE			56	// Одиночный импусль цепи RESET
#define ACT_DBG_OE_IMPULSE				57	// Одиночный импусль цепи OE

#define ACT_SAVE_TO_ROM					200	// Сохранение пользовательских данных во FLASH процессора
#define ACT_RESTORE_FROM_ROM			201	// Восстановление данных из FLASH
#define ACT_RESET_TO_DEFAULT			202	// Сброс DataTable в состояние по умолчанию

#define ACT_BOOT_LOADER_REQUEST			320	// Перезапуск процессора с целью перепрограммирования
// -----------------------------

// Регистры
// Сохраняемые регистры

// Несохраняемы регистры чтения-записи
#define REG_DBG_STATE					128	// Регистр режима Отладки
#define REG_RAW_RELAY_BUS_MINUS_CO		130	// Регистр установки реле группы BUSLV- (Connect)
#define REG_RAW_RELAY_BUS_MINUS_DISCO	131	// Регистр установки реле группы BUSLV- (Disconnect)
#define REG_RAW_RELAY_BUS_PLUS_CO		132	// Регистр установки реле группы BUSLV+ (Connect)
#define REG_RAW_RELAY_BUS_PLUS_DISCO	133	// Регистр установки реле группы BUSLV+ (Disconnect)
#define REG_RAW_RELAY_POT_CTRL			134	// Регистр установки реле группы POT CTR
#define REG_RAW_RELAY_CTRL				135	// Регистр установки реле группы CTRL
#define REG_RAW_RELAY_BUSHV_MINUS		136	// Регистр установки реле группы BUSHV-
#define REG_RAW_RELAY_BUSHV_PLUS		137	// Регистр установки реле группы BUSHV+
#define REG_RAW_RELAY_POT_PLUS			138	// Регистр установки реле группы POT+
#define REG_RAW_RELAY_POT_MINUS			139	// Регистр установки реле группы POT-
#define REG_RAW_RELAY_OUTRELAY			140	// Регистр установки реле группы OutRelay

#define REG_GROUP_RELAY					150	// Регистр установки предопределенной группы

// Регистры только чтение
#define REG_DEV_STATE					192	// Регистр состояния
#define REG_FAULT_REASON				193	// Регистр Fault
#define REG_DISABLE_REASON				194	// Регистр Disable
#define REG_WARNING						195	// Регистр Warning
#define REG_PROBLEM						196	// Регистр Problem
#define REG_OP_RESULT					197	// Регистр результата операции
// -----------------------------

// Operation results
#define OPRESULT_NONE					0	// No information or not finished
#define OPRESULT_OK						1	// Operation was successful
#define OPRESULT_FAIL					2	// Operation failed

//  Fault and disable codes
#define DF_NONE							0

// Problem
#define PROBLEM_NONE					0

//  Warning
#define WARNING_NONE					0

//  User Errors
#define ERR_NONE						0
#define ERR_CONFIGURATION_LOCKED		1	//  Устройство защищено от записи
#define ERR_OPERATION_BLOCKED			2	//  Операция не может быть выполнена в текущем состоянии устройства
#define ERR_DEVICE_NOT_READY			3	//  Устройство не готово для смены состояния
#define ERR_WRONG_PWD					4	//  Неправильный ключ

#endif //  __DEV_OBJ_DIC_H
