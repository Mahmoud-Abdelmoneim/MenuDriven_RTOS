/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LCD_interface.h"
#include "queue.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct{
	uint32_t ID;
	uint8_t name[20];
}student_t;


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define FRAME_ONE         0x00
#define FRAME_TWO         0x01
#define FRAME_THREE       0x02
#define FRAME_FOUR        0x03
#define FRAME_FIVE        0x04



/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
const uint8_t *FrameBufferFirstScreen[5][2]={

		{"Status1          ","Temperature   "},
		{"Status2          ","Pressure      "},
		{"Status3          ","option....    "},
		{"Status4          ","option....    "}
};

const uint8_t *FrameBufferScoundScreen[5][2]={

		{"Mode Temperature ","Temperature ="},
		{"Mode Pressure    ","Pressure =   "},
		{"Mode3           ","Value = ...   "},
		{"Mode4           ","Value = ...   "}
};

uint8_t CurrentFram=0;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
  .name = "myTask02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal1,
};
/* Definitions for Data_Queue */
osMessageQueueId_t Data_QueueHandle;
const osMessageQueueAttr_t Data_Queue_attributes = {
  .name = "Data_Queue"
};
/* Definitions for Temperature */
osSemaphoreId_t TemperatureHandle;
const osSemaphoreAttr_t Temperature_attributes = {
  .name = "Temperature"
};
/* Definitions for pressure */
osSemaphoreId_t pressureHandle;
const osSemaphoreAttr_t pressure_attributes = {
  .name = "pressure"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void Fram_FristScreen(u8 fram);
void Fram_ScoundScreen(uint8_t fram);
/* USER CODE END FunctionPrototypes */

void Task_1(void *argument);
void Task_2(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of Temperature */
  TemperatureHandle = osSemaphoreNew(1, 1, &Temperature_attributes);

  /* creation of pressure */
  pressureHandle = osSemaphoreNew(1, 1, &pressure_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of Data_Queue */
  Data_QueueHandle = osMessageQueueNew (5, sizeof(uint8_t), &Data_Queue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */

  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(Task_1, NULL, &defaultTask_attributes);

  /* creation of myTask02 */
  myTask02Handle = osThreadNew(Task_2, NULL, &myTask02_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */

  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Task_1 */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Task_1 */

/*Task one : control the menu and send message Queue */
void Task_1(void *argument)
{
  /* USER CODE BEGIN Task_1 */
	BaseType_t RetVal=pdTRUE; //has the status of sending message 
	uint8_t state_ButtonIncrement=0; //has the status of the increment Button 
	uint8_t state_ButtonDecrement=0; //has the status of the decrement Button 
	uint8_t Choise=0;								 //has the status if context to secound task or no
  /* Infinite loop */
  for(;;)
  {

  	/*print the crrent ram in the lcd*/
	  Fram_FristScreen(CurrentFram);
	  /*read the status of push button pins*/
	  Choise = MGPIO_u8GetPinValue(PORTB,PIN5);
	  state_ButtonIncrement = MGPIO_u8GetPinValue(PORTB,PIN3);
	  state_ButtonDecrement = MGPIO_u8GetPinValue(PORTB,PIN4);

		if(state_ButtonIncrement == 1)
		{
			MGPIO_voidSetPinValue(PORTC,PIN13, GPIO_HIGH);

			if(CurrentFram == 4){
				CurrentFram = FRAME_ONE;
			}
			else
			{
				CurrentFram++;
			}
		}
		else{
			MGPIO_voidSetPinValue(PORTC,PIN13, GPIO_LOW);
		}
		if(state_ButtonDecrement == 1)
		{
			if(CurrentFram == FRAME_ONE)
			{
				CurrentFram =FRAME_FOUR;
			}
			else{
				CurrentFram-- ;
			}
		}
		if(Choise == 1)
		{
			RetVal = xQueueSendToFront(Data_QueueHandle,(void *)&CurrentFram,1000);
			vTaskPrioritySet( myTask02Handle,osPriorityHigh);
			

		}
		HAL_Delay(10);
  }
  /* USER CODE END Task_1 */
}

/* USER CODE BEGIN Header_Task_2 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_2 */
void Task_2(void *argument)
{
  /* USER CODE BEGIN Task_2 */
	BaseType_t RetVal=pdTRUE;
	uint8_t message=0;
	uint8_t Choise=0;
  /* Infinite loop */

  for(;;)
  {
	  HAL_Delay(100);
	  Choise = MGPIO_u8GetPinValue(PORTB,PIN5);
	  RetVal= xQueueReceive(Data_QueueHandle, &message, 0);

	  if(pdTRUE == RetVal)
	  {
		  switch(message)
		  {
		  	  case 0:
		  		  Fram_ScoundScreen(FRAME_ONE);
		  		  break;
		  	  case 1:
		  		  Fram_ScoundScreen(FRAME_TWO);
		  		  break;
		  	  case 2:
		  		  Fram_ScoundScreen(FRAME_THREE);
		  		  break;
		  	  case 3:
		  		  Fram_ScoundScreen(FRAME_FOUR);
		  		  break;
		  }
	  }
	  else{

	  }
	  RetVal = xQueueSendToFront(Data_QueueHandle,(void *)&message,1000);

	  if(Choise == 1)
	  {
		  vTaskPrioritySet(defaultTaskHandle,osPriorityHigh);
		  vTaskPrioritySet( myTask02Handle,osPriorityAboveNormal1);
	  }

  }


  /* USER CODE END Task_2 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void Fram_FristScreen(uint8_t fram)
{


	LCD_Send_String_Pos(FrameBufferFirstScreen[fram][0],1,1);

	LCD_Send_String_Pos(FrameBufferFirstScreen[fram][1],2,1);

}


void Fram_ScoundScreen(uint8_t fram){
	LCD_Send_String_Pos(FrameBufferScoundScreen[fram][0],1,1);
	LCD_Send_String_Pos(FrameBufferScoundScreen[fram][1],2,1);

}

/* USER CODE END Application */

