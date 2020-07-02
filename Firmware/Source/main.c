#include "Controller.h"
#include "InitConfig.h"
#include "SysConfig.h"

int main()
{
	__disable_irq();
	SCB->VTOR = (uint32_t)BOOT_LOADER_MAIN_PR_ADDR;
	__enable_irq();
	
	// ��������� ��������� ������� ������������
	INITCFG_ConfigSystemClock();
	
	// ��������� ������
	INITCFG_ConfigIO();
	
	// ��������� SPI
	INITCFG_ConfigSPI();

	// ��������� ������� ����������
	INITCONFIG_InterruptEnable();
	
	// ��������� CAN
	INITCONFIG_CAN();
	
	// ��������� UART
	INITCONFIG_UART();
	
	// ��������� ���������� ��������
	INITCONFIG_Timer7();
	
	// ��������� ����������� �������
	INITCONFIG_WatchDog();
	
	// ������������� ������ �����������
	CONTROL_Init();
	
	// ������� ����
	while(TRUE)
		CONTROL_Idle();
	
	return 0;
}
