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
#include "function.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
osThreadId myTask01Handle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE BEGIN PM */
void RTOS_Initliaze(void);
/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );
void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);
/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
void RTOS_Initliaze(void)
{
  // osThreadDef(myTask01, StartDefaultTask, osPriorityNormal, 0, 128);
  // myTask01Handle = osThreadCreate(osThread(myTask01), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityIdle, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  // /* definition and creation of myTask03 */
  // osThreadDef(myTask03, StartTask03, osPriorityIdle, 0, 128);
  // myTask03Handle = osThreadCreate(osThread(myTask03), NULL);
}
/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    // HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
    
  // if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin))
  // {
  //    HAL_GPIO_WritePin(LED_PIN_GPIO_Port,LED_PIN,GPIO_PIN_RESET);
  //     mutex=0;
  // }
  // else
  // {
  //   HAL_GPIO_WritePin(LED_PIN_GPIO_Port,LED_PIN,GPIO_PIN_SET);
  //     mutex=1;
  // }
     
    osDelay(100);
  }
  /* USER CODE END 5 */
}
/* USER CODE END FunctionPrototypes */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {
    // HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
    if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin)==0)
    {
       HAL_GPIO_WritePin(LED_PIN_GPIO_Port,LED_PIN,GPIO_PIN_SET);
			if (mutex == 1) {
				memset(frameBuffer, 0, sizeof frameBuffer);
				OV2640_CaptureSnapshot((uint32_t) frameBuffer, imgRes);

				while (1) {
					if (headerFound == 0 && frameBuffer[bufferPointer] == 0xFF
							&& frameBuffer[bufferPointer + 1] == 0xD8) {
						headerFound = 1;
					#ifdef DEBUG
						my_printf("Found header of JPEG file \r\n");
					#endif
					}
					if (headerFound == 1 && frameBuffer[bufferPointer] == 0xFF
							&& frameBuffer[bufferPointer + 1] == 0xD9) {
						bufferPointer = bufferPointer + 2;
					#ifdef DEBUG
						my_printf("Found EOF of JPEG file \r\n");
						#endif
						headerFound = 0;
						break;
					}

					if (bufferPointer >= 65535) {
						break;
					}
					bufferPointer++;
				}
					#ifdef DEBUG
						my_printf("Image size: %d bytes \r\n",bufferPointer);
					#endif

				// HAL_UART_Transmit_DMA(&huart3, frameBuffer, bufferPointer); //Use of DMA may be necessary for larger data streams.
				bufferPointer = 0;
				mutex = 0;
			}
		} 
    else 
    {
       HAL_GPIO_WritePin(LED_PIN_GPIO_Port,LED_PIN,GPIO_PIN_RESET);
			 mutex = 1;
		}
  }
	osDelay(100);
}
    
  /* USER CODE END StartTask02 */

/* USER CODE END GET_IDLE_TASK_MEMORY */
void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  for(;;)
  {

    osDelay(100);
  }
  /* USER CODE END StartTask03 */
}
/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
