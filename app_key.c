#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "dev_io.h"
#include <stdio.h>

#define QUEUE_LENGTH 5
#define QUEUE_ITEM_SIZE sizeof(KeyEvent)

QueueHandle_t xKeyQueue;
TaskHandle_t keyTaskHandle;

void KeyTask(void *parameter)
{
	KeyEvent key = {0};
	ptIODev keyDev = IODev_GetDev(KEY);
	if(keyDev != NULL)
	{
		keyDev->Init(keyDev);
	}
	else
	{
		printf("Key Device not found.\r\n");
	}
	
	xKeyQueue = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
	if(xKeyQueue == NULL)
	{
		printf("Create Key Queue failed.\r\n");
		vTaskSuspend(keyTaskHandle);
	}
	
	while(1)
	{
		if(keyDev->Read(keyDev, (uint8_t*)&key, sizeof(KeyEvent)) == 0)
		{
			if(xQueueSendToBack(xKeyQueue, (uint8_t*)&key, 10) != pdPASS)
			{
				printf("Key Queue Send full.\r\n");
			}
		}
		vTaskDelay(1);
	}
}

void vStartKeyTasks(uint16_t usTaskStackSize, UBaseType_t uxTaskPriority)
{
	BaseType_t x = 0L;

	if(xTaskCreate(KeyTask,		/* The function that implements the task. */
			"Key",				/* Just a text name for the task to aid debugging. */
			usTaskStackSize,	/* The stack size is defined in FreeRTOSIPConfig.h. */
			(void *)x,			/* The task parameter, not used in this case. */
			uxTaskPriority,		/* The priority assigned to the task is defined in FreeRTOSConfig.h. */
			&keyTaskHandle) == pdPASS)	/* The task handle is not used. */
			{
				printf("Create Key Task success.\r\n");
			}
	else
	{
		printf("Create Key Task failed.\r\n");
	}
}





