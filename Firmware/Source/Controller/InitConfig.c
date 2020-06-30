#include "InitConfig.h"
#include "Board.h"
#include "SysConfig.h"

// Functions
//
Boolean INITCONFIG_SysClk()
{
	return RCC_PLL_HSE_Config(QUARTZ_FREQUENCY, PREDIV_4, PLL_14);
}
//------------------------------------------------

void INITCONFIG_InterruptEnable()
{
	EXTI_Config(EXTI_PA, EXTI_8, RISE_TRIG, 0);
	EXTI_EnableInterrupt(EXTI3_IRQn, 0, true);
}
//------------------------------------------------

void INITCONFIG_IO()
{
	// ��������� ������������ ������
	RCC_GPIO_Clk_EN(PORTA);
	RCC_GPIO_Clk_EN(PORTB);
	
	// ������
	GPIO_InitPushPullOutput(GPIO_LED_EXT_RED);
	GPIO_InitPushPullOutput(GPIO_LED_EXT_GREEN);
	GPIO_InitPushPullOutput(GPIO_SET);
	GPIO_InitPushPullOutput(GPIO_CLK);
	GPIO_InitPushPullOutput(GPIO_DATA);
	GPIO_InitPushPullOutput(GPIO_CTRL_SYNC_1);
	GPIO_InitPushPullOutput(GPIO_CTRL_SYNC_2);
	GPIO_InitPushPullOutput(GPIO_LOCK_1);
	GPIO_InitPushPullOutput(GPIO_LOCK_2);
	GPIO_InitPushPullOutput(GPIO_RESET);
	GPIO_InitPushPullOutput(GPIO_OE);
	
	// �������������� �������
	GPIO_InitAltFunction(GPIO_ALT_CAN_RX, AltFn_9);
	GPIO_InitAltFunction(GPIO_ALT_CAN_TX, AltFn_9);
	GPIO_InitAltFunction(GPIO_ALT_UART_RX, AltFn_7);
	GPIO_InitAltFunction(GPIO_ALT_UART_TX, AltFn_7);
}
//------------------------------------------------
void INITCONFIG_SPI()
{
	SPI_Init(SPI1, SPI_CR1_BR, FALSE);
}

//------------------------------------------------
void INITCONFIG_CAN()
{
	RCC_CAN_Clk_EN(CAN_1_ClkEN);
	NCAN_Init(SYSCLK, CAN_BAUDRATE, FALSE);
	NCAN_FIFOInterrupt(TRUE);
	NCAN_FilterInit(0, 0, 0); // ������ 0 ���������� ��� ���������
}
//------------------------------------------------

void INITCONFIG_UART()
{
	USART_Init(USART1, SYSCLK, USART_BAUDRATE);
	USART_Recieve_Interupt(USART1, 0, true);
}
//------------------------------------------------

void INITCONFIG_Timer7()
{
	TIM_Clock_En(TIM_7);
	TIM_Config(TIM7, SYSCLK, TIMER7_uS);
	TIM_Interupt(TIM7, 0, true);
	TIM_Start(TIM7);
}
//------------------------------------------------

void INITCONFIG_WatchDog()
{
	IWDG_Config();
	IWDG_ConfigureFastUpdate();
}
//------------------------------------------------
