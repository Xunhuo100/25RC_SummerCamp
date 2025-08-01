/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DIN2_Pin GPIO_PIN_0
#define DIN2_GPIO_Port GPIOA
#define DIN1_Pin GPIO_PIN_1
#define DIN1_GPIO_Port GPIOA
#define E4A_Pin GPIO_PIN_2
#define E4A_GPIO_Port GPIOA
#define E4A_EXTI_IRQn EXTI2_IRQn
#define E4B_Pin GPIO_PIN_3
#define E4B_GPIO_Port GPIOA
#define CIN2_Pin GPIO_PIN_4
#define CIN2_GPIO_Port GPIOA
#define CIN1_Pin GPIO_PIN_5
#define CIN1_GPIO_Port GPIOA
#define E3A_Pin GPIO_PIN_6
#define E3A_GPIO_Port GPIOA
#define E3A_EXTI_IRQn EXTI9_5_IRQn
#define E3B_Pin GPIO_PIN_7
#define E3B_GPIO_Port GPIOA
#define E2B_Pin GPIO_PIN_12
#define E2B_GPIO_Port GPIOB
#define E2A_Pin GPIO_PIN_13
#define E2A_GPIO_Port GPIOB
#define E2A_EXTI_IRQn EXTI15_10_IRQn
#define BIN1_Pin GPIO_PIN_14
#define BIN1_GPIO_Port GPIOB
#define BIN2_Pin GPIO_PIN_15
#define BIN2_GPIO_Port GPIOB
#define E1B_Pin GPIO_PIN_8
#define E1B_GPIO_Port GPIOA
#define E1A_Pin GPIO_PIN_11
#define E1A_GPIO_Port GPIOA
#define E1A_EXTI_IRQn EXTI15_10_IRQn
#define AIN1_Pin GPIO_PIN_12
#define AIN1_GPIO_Port GPIOA
#define AIN2_Pin GPIO_PIN_15
#define AIN2_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
