/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32f7xx_hal.h"

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
#define TOUCH_IRQ_Pin GPIO_PIN_15
#define TOUCH_IRQ_GPIO_Port GPIOC
#define USER_BUTTON_Pin GPIO_PIN_9
#define USER_BUTTON_GPIO_Port GPIOF
#define USER_LED_Pin GPIO_PIN_2
#define USER_LED_GPIO_Port GPIOA
#define LCD_DISP_EN_Pin GPIO_PIN_5
#define LCD_DISP_EN_GPIO_Port GPIOC
#define USB_FAULT_Pin GPIO_PIN_11
#define USB_FAULT_GPIO_Port GPIOD
#define SD_CARD_DETECT_Pin GPIO_PIN_15
#define SD_CARD_DETECT_GPIO_Port GPIOA
#define BACKLIGHT_PWM_Pin GPIO_PIN_4
#define BACKLIGHT_PWM_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
