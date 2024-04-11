/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
/*
enum BUTTON_STATES{
	NOT_PRESSED,
	PRESSED_SHORT,
	PRESSED_LONG
};

typedef struct{
	bool interrupt_flag;
	enum BUTTON_STATES state;
}GpioBtnSet_t;

enum GPIO_EXTI{
	LEFT,
	RIGHT
};
*/
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
// Digital Outputs
void gpio_setDigOut(GPIO_TypeDef* port, uint16_t pin);
void gpio_resetDigOut(GPIO_TypeDef* port, uint16_t pin);
void gpio_toggleDigOut(GPIO_TypeDef* port, uint16_t pin);
// Digital Inputs
bool gpio_getDigIn(GPIO_TypeDef* port, uint16_t pin);
// EXTI
//bool gpio_getBtnFlag(enum GPIO_EXTI btn);
// sequence initialization
void gpio_InitSequence(unsigned int, unsigned int);
// poll led timer
void gpio_pollLedTimer(void);
void gpio_pollLeftBtnTimer(void);
void gpio_pollRightBtnTimer(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

