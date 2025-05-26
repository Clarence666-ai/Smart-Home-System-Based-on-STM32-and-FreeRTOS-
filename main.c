#include "main.h"

#include "dev_io.h"
#include "dev_net.h"

#include "stdio.h"
#include "string.h"

#include "FreeRTOS.h"
#include "task.h"
void SystemClock_Config(void);
extern void vStartMQTTTasks(uint16_t usTaskStackSize, UBaseType_t uxTaskPriority);
extern void vStartLEDTasks(uint16_t usTaskStackSize, UBaseType_t uxTaskPriority);
extern void vStartKeyTasks(uint16_t usTaskStackSize, UBaseType_t uxTaskPriority);
int main(void)
{
	HAL_Init();
	SystemClock_Config();
	
	ptIODev dbgoutDev = NULL;
	dbgoutDev = IODev_GetDev(DBGOUT);
	if(dbgoutDev != NULL)
		dbgoutDev->Init(dbgoutDev);
	

	vStartMQTTTasks(512, 10);
	vStartLEDTasks(128, 1);//数字越低，任务优先级越低。
	vStartKeyTasks(128, 2);
	vTaskStartScheduler();
	while(1)
	{
		
		
	}
	//return 0;
}

void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);
	
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);	
}
