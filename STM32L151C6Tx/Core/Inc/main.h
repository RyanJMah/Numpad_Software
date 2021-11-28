/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "stm32l1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_def.h"
#include "usbd_hid.h"
#include "usb_device.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim3;
extern USBD_HandleTypeDef hUsbDeviceFS;
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
#define ROW4_Pin GPIO_PIN_1
#define ROW4_GPIO_Port GPIOA
#define ROW3_Pin GPIO_PIN_2
#define ROW3_GPIO_Port GPIOA
#define ROW2_Pin GPIO_PIN_3
#define ROW2_GPIO_Port GPIOA
#define ROW1_Pin GPIO_PIN_4
#define ROW1_GPIO_Port GPIOA
#define ROW0_Pin GPIO_PIN_5
#define ROW0_GPIO_Port GPIOA
#define COL0_Pin GPIO_PIN_12
#define COL0_GPIO_Port GPIOB
#define COL1_Pin GPIO_PIN_13
#define COL1_GPIO_Port GPIOB
#define COL2_Pin GPIO_PIN_14
#define COL2_GPIO_Port GPIOB
#define COL3_Pin GPIO_PIN_15
#define COL3_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define BITMASK(num_bits) ( (1 << num_bits) - 1 )
#define BIT_IS_SET(x, n) ( ( (x) & (1 << n) ) != 0 )
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
