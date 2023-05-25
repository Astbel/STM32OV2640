/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "ov2640.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
extern DMA_HandleTypeDef hdma_dcmi;
extern DCMI_HandleTypeDef hdcmi;
extern I2C_HandleTypeDef hi2c2;
extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart3_tx;

/* USER CODE END Includes */
/**OV2640 GPIO PIN**/
extern uint8_t mutex ;
extern uint16_t bufferPointer;
extern uint8_t headerFound;
/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern enum imageResolution imgRes;
extern uint8_t frameBuffer[RES_1280x960];
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
/*Camera pin define here*/
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
/*PWDN  PC2*/
#define PWDN_PIN GPIO_PIN_2
#define PWDN_RST_PIN_GPIO_Port GPIOC
/*RST   PC3*/
#define RST_Pin GPIO_PIN_3
/*LED PA5*/
#define LED_PIN GPIO_PIN_5
#define LED_PIN_GPIO_Port GPIOA
/* USER CODE BEGIN EFP */
/**DCMI GPIO Configuration
    PA4     ------> DCMI_HSYNC
    PA6     ------> DCMI_PIXCLK
    PC6     ------> DCMI_D0
    PC7     ------> DCMI_D1
    PC8     ------> DCMI_D2
    PC9     ------> DCMI_D3
    PC11     ------> DCMI_D4
    PB6     ------> DCMI_D5
    PB7     ------> DCMI_VSYNC
    PB8     ------> DCMI_D6
    PB9     ------> DCMI_D7
    */
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
