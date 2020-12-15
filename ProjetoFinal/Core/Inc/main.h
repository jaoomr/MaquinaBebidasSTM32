/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PRESS_WATER_Pin GPIO_PIN_14
#define PRESS_WATER_GPIO_Port GPIOC
#define PRESS_CO2_Pin GPIO_PIN_15
#define PRESS_CO2_GPIO_Port GPIOC
#define READ_Pin GPIO_PIN_7
#define READ_GPIO_Port GPIOA
#define VALV_WATER_Pin GPIO_PIN_0
#define VALV_WATER_GPIO_Port GPIOB
#define VALV_CO2_Pin GPIO_PIN_1
#define VALV_CO2_GPIO_Port GPIOB
#define VALV_HOT_WATER_Pin GPIO_PIN_10
#define VALV_HOT_WATER_GPIO_Port GPIOB
#define VALV_COLD_WATER_Pin GPIO_PIN_11
#define VALV_COLD_WATER_GPIO_Port GPIOB
#define CANCEL_Pin GPIO_PIN_12
#define CANCEL_GPIO_Port GPIOB
#define ADD_Pin GPIO_PIN_13
#define ADD_GPIO_Port GPIOB
#define SUB_Pin GPIO_PIN_14
#define SUB_GPIO_Port GPIOB
#define CONFIRM_Pin GPIO_PIN_15
#define CONFIRM_GPIO_Port GPIOB
#define OPT_READ1_Pin GPIO_PIN_8
#define OPT_READ1_GPIO_Port GPIOA
#define OPT_READ2_Pin GPIO_PIN_9
#define OPT_READ2_GPIO_Port GPIOA
#define OPT_READ3_Pin GPIO_PIN_10
#define OPT_READ3_GPIO_Port GPIOA
#define B0_Pin GPIO_PIN_11
#define B0_GPIO_Port GPIOA
#define B1_Pin GPIO_PIN_12
#define B1_GPIO_Port GPIOA
#define B2_Pin GPIO_PIN_15
#define B2_GPIO_Port GPIOA
#define B3_Pin GPIO_PIN_3
#define B3_GPIO_Port GPIOB
#define B4_Pin GPIO_PIN_4
#define B4_GPIO_Port GPIOB
#define B5_Pin GPIO_PIN_5
#define B5_GPIO_Port GPIOB
#define B6_Pin GPIO_PIN_6
#define B6_GPIO_Port GPIOB
#define B7_Pin GPIO_PIN_7
#define B7_GPIO_Port GPIOB
#define RS_Pin GPIO_PIN_8
#define RS_GPIO_Port GPIOB
#define E_Pin GPIO_PIN_9
#define E_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
