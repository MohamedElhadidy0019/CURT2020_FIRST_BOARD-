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
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart3;
/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define APPS1_Pin GPIO_PIN_0
#define APPS1_GPIO_Port GPIOA
#define APPS2_Pin GPIO_PIN_1
#define APPS2_GPIO_Port GPIOA
#define RTDS_Pin GPIO_PIN_2
#define RTDS_GPIO_Port GPIOA
#define EVMS_RELAY_Pin GPIO_PIN_3
#define EVMS_RELAY_GPIO_Port GPIOA
#define PUMP_Pin GPIO_PIN_4
#define PUMP_GPIO_Port GPIOA
#define BRAKES_ANGLE_SENSOR_Pin GPIO_PIN_5
#define BRAKES_ANGLE_SENSOR_GPIO_Port GPIOA
#define RFE_ENABLE_Pin GPIO_PIN_6
#define RFE_ENABLE_GPIO_Port GPIOA
#define DRIVE_ENABLE_Pin GPIO_PIN_7
#define DRIVE_ENABLE_GPIO_Port GPIOA
#define MOTOR_PWM_OUTPUT_Pin GPIO_PIN_0
#define MOTOR_PWM_OUTPUT_GPIO_Port GPIOB
#define START_BTN_Pin GPIO_PIN_12
#define START_BTN_GPIO_Port GPIOB
#define RTD_BTN_Pin GPIO_PIN_13
#define RTD_BTN_GPIO_Port GPIOB
#define ENDURANCE_BTN_Pin GPIO_PIN_14
#define ENDURANCE_BTN_GPIO_Port GPIOB
#define ACCELERATION_BTN_Pin GPIO_PIN_15
#define ACCELERATION_BTN_GPIO_Port GPIOB
#define SKIDPAD_BTN_Pin GPIO_PIN_8
#define SKIDPAD_BTN_GPIO_Port GPIOA
#define PRE_CHARGE_FB_Pin GPIO_PIN_9
#define PRE_CHARGE_FB_GPIO_Port GPIOA
#define AIR_POSITIVE_FB_Pin GPIO_PIN_10
#define AIR_POSITIVE_FB_GPIO_Port GPIOA
#define AIR_NEGATIVE_FB_Pin GPIO_PIN_15
#define AIR_NEGATIVE_FB_GPIO_Port GPIOA
#define DC60_INPUT_Pin GPIO_PIN_3
#define DC60_INPUT_GPIO_Port GPIOB
#define DC90_INPUT_Pin GPIO_PIN_4
#define DC90_INPUT_GPIO_Port GPIOB
#define BAMOCAR_ERR_Pin GPIO_PIN_5
#define BAMOCAR_ERR_GPIO_Port GPIOB
#define PRECHARGE_RELAY_Pin GPIO_PIN_6
#define PRECHARGE_RELAY_GPIO_Port GPIOB
#define AIR_POSITIVE_Pin GPIO_PIN_7
#define AIR_POSITIVE_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
