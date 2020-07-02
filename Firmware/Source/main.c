#include "Controller.h"
#include "InitConfig.h"
#include "SysConfig.h"

int main()
{
	__disable_irq();
	SCB->VTOR = (uint32_t)BOOT_LOADER_MAIN_PR_ADDR;
	__enable_irq();
	
	// Настройка системной частоты тактирования
	INITCFG_ConfigSystemClock();
	
	// Настройка портов
	INITCFG_ConfigIO();
	
	// Настройка SPI
	INITCFG_ConfigSPI();

	// Настройка внешних прерываний
	INITCONFIG_InterruptEnable();
	
	// Настройка CAN
	INITCONFIG_CAN();
	
	// Настройка UART
	INITCONFIG_UART();
	
	// Настройка системного счетчика
	INITCONFIG_Timer7();
	
	// Настройка сторожевого таймера
	INITCONFIG_WatchDog();
	
	// Инициализация логики контроллера
	CONTROL_Init();
	
	// Фоновый цикл
	while(TRUE)
		CONTROL_Idle();
	
	return 0;
}
