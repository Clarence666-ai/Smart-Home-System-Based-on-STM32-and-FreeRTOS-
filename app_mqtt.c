/* Standard includes. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "MQTTClient.h"
#include "dev_io.h"

extern TaskHandle_t ledTaskHandle;
extern QueueHandle_t xKeyQueue;

const static char clientID[] = "ipioqFsPt70.MiniBoard|securemode=2,signmethod=hmacsha256,timestamp=1688263257335|";
const static char username[] = "MiniBoard&ipioqFsPt70";
const static char password[] = "e8adc3d646361964283393584822e166239a281d310e129f6d9892f0e18b2f0d";

const static char LedTopic[] = "/ipioqFsPt70/MiniBoard/user/getledCmd";
const static char KeyTopic[] = "/ipioqFsPt70/MiniBoard/user/keyInfo";
	
void messageArrived(MessageData* data)
{
	printf("Message arrived on topic %.*s: %.*s\n", data->topicName->lenstring.len, data->topicName->lenstring.data,
		data->message->payloadlen, data->message->payload);
	
	if(strstr(data->topicName->lenstring.data, LedTopic) != 0)
	{

		if(strstr(data->message->payload, "led on") != 0)
		{
			xTaskNotify(ledTaskHandle, 1, eSetValueWithOverwrite);
		}
		else if(strstr(data->message->payload, "led off") != 0)
		{
			xTaskNotify(ledTaskHandle, 0, eSetValueWithOverwrite);
		}
	}
}

static void prvMQTTEchoTask(void *pvParameters)
{
	KeyEvent key = {0};
	/* connect to m2m.eclipse.org, subscribe to a topic, send and receive messages regularly every 1 sec */
	MQTTClient client;
	Network network;
	unsigned char sendbuf[256], readbuf[256];
	int rc = 0;
	MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;

	pvParameters = 0;
	NetworkInit(&network);
	
	MQTTClientInit(&client, &network, 30000, sendbuf, sizeof(sendbuf), readbuf, sizeof(readbuf));

	char* address = "iot-06z00c8s11l5o02.mqtt.iothub.aliyuncs.com";
	if ((rc = NetworkConnect(&network, address, 1883)) != 0)
		printf("Return code from network connect is %d\n", rc);

#if defined(MQTT_TASK)
	if ((rc = MQTTStartTask(&client)) != pdPASS)
		printf("Return code from start tasks is %d\n", rc);
#endif

	connectData.MQTTVersion = 3;
	connectData.clientID.cstring = (char*)clientID;
	connectData.username.cstring = (char*)username;
	connectData.password.cstring = (char*)password;
	
	if ((rc = MQTTConnect(&client, &connectData)) != 0)
		printf("Return code from MQTT connect is %d\n", rc);
	else
		printf("MQTT Connected\n");

	if ((rc = MQTTSubscribe(&client, LedTopic, 0, messageArrived)) != 0)
		printf("Return code from MQTT subscribe is %d\n", rc);

	while (1)
	{
		if(xKeyQueue != NULL && xQueueReceive(xKeyQueue, (uint8_t*)&key, 10) == pdPASS)
		{
			MQTTMessage message;
			char payload[64];

			message.qos = 0;
			message.retained = 0;
			message.payload = payload;
			sprintf(payload, "key number %d, Press time:%d ms", key.num, key.time);
			message.payloadlen = strlen(payload);
			printf("%s\r\n", payload);
			
			if ((rc = MQTTPublish(&client, KeyTopic, &message)) != 0)
				printf("Return code from MQTT publish is %d\n", rc);
					
		}
		

		
#if !defined(MQTT_TASK)
		if ((rc = MQTTYield(&client, 100)) != 0)
			printf("Return code from yield is %d\n", rc);
#endif
		vTaskDelay(1);
	}

	/* do not return */
}

void vStartMQTTTasks(uint16_t usTaskStackSize, UBaseType_t uxTaskPriority)
{
	BaseType_t x = 0L;

	if(xTaskCreate(prvMQTTEchoTask,	/* The function that implements the task. */
			"MQTTEcho0",			/* Just a text name for the task to aid debugging. */
			usTaskStackSize,	/* The stack size is defined in FreeRTOSIPConfig.h. */
			(void *)x,		/* The task parameter, not used in this case. */
			uxTaskPriority,		/* The priority assigned to the task is defined in FreeRTOSConfig.h. */
			NULL) == pdPASS)				/* The task handle is not used. */
			{
				printf("Create MQTT Task success.\r\n");
			}
	else
	{
		printf("Create MQTT Task failed.\r\n");
	}
}
  
  
  
  
  
  
