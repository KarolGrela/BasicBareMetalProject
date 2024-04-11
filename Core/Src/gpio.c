/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
#include "TimerOverflow_t.h"
#include "ButtonPress_t.h"

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LED_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GREEN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = BTN_LEFT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BTN_LEFT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = BTN_RIGHT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BTN_RIGHT_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI2_IRQn, 4, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 4, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

}

/* USER CODE BEGIN 2 */
// Digital Outputs
void gpio_setDigOut(GPIO_TypeDef* port, uint16_t pin)
{
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
}

void gpio_resetDigOut(GPIO_TypeDef* port, uint16_t pin)
{
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
}

void gpio_toggleDigOut(GPIO_TypeDef* port, uint16_t pin)
{
	HAL_GPIO_TogglePin(port, pin);
}


// Digital Inputs
bool gpio_getDigIn(GPIO_TypeDef* port, uint16_t pin)
{
	if (GPIO_PIN_SET == HAL_GPIO_ReadPin(port, pin))
	{
		return false;	// assume pull-up resistors
	}
	else
	{
		return true;
	}
}
/*
// Interrupts resources and Callback
volatile static GpioBtnSet_t btn_left = {.interrupt_flag = false, .state = NOT_PRESSED};
volatile static GpioBtnSet_t btn_right = {.interrupt_flag = false, .state = NOT_PRESSED};

bool gpio_getBtnFlag(enum GPIO_EXTI btn)
{
	bool ret_val = false;
	switch(btn)
	{
		case LEFT:
			ret_val = btn_left.interrupt_flag;
			btn_left.interrupt_flag = false;
			break;
		case RIGHT:
			ret_val = btn_right.interrupt_flag;
			btn_right.interrupt_flag = false;
			break;
		default:
			break;
	}

	return ret_val;
}

enum BUTTON_STATES gpio_getBtnState(enum GPIO_EXTI btn)
{
	bool ret_val = false;
	switch(btn)
	{
		case LEFT:
			return btn_left.state;
		case RIGHT:
			return btn_right.state;
		default:
			break;
	}

	return ret_val;
}

void gpio_setBtnState(enum GPIO_EXTI btn, enum BUTTON_STATES state)
{
	//bool ret_val = false;
	switch(btn)
	{
		case LEFT:
			btn_left.state = state;
		case RIGHT:
			btn_right.state = state;
		default:
			break;
	}

	//return ret_val;
}
*/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (BTN_LEFT_Pin == GPIO_Pin)
  {
	  bool pin_state = gpio_getDigIn(BTN_LEFT_GPIO_Port, BTN_LEFT_Pin);
	  if (pin_state == true)
	  {
		  btp_press(&btp_left);
		  btp_decr_overflow_trigger_count(&btp_left, 10);
	  }
	  else
	  {
		  btp_release(&btp_left);
	  }
  }

  if (BTN_RIGHT_Pin == GPIO_Pin)
  {
	  bool pin_state = gpio_getDigIn(BTN_RIGHT_GPIO_Port, BTN_RIGHT_Pin);
	  if (pin_state == true)
	  {
		  btp_press(&btp_right);
		  btp_incr_overflow_trigger_count(&btp_right, 5);
	  }
	  else
	  {
		  btp_release(&btp_right);
	  }
  }
}

void gpio_InitSequence(unsigned int del_ms, unsigned int blink_count)
{
	gpio_setDigOut(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
	HAL_Delay(del_ms);
	gpio_resetDigOut(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
	for (int i = 0; i < blink_count; i++)
	{
		HAL_Delay(del_ms);
		gpio_toggleDigOut(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		HAL_Delay(del_ms);
		gpio_toggleDigOut(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
	}

	// setup Button_Press_t instances
	btp_Constructor(&btp_left, 10, 100, &tov_left_button, &tov_led);
	btp_Constructor(&btp_right, 10, 100, &tov_right_button, &tov_led);
}

void gpio_pollLedTimer(void)
{
	if (tov_getOverflowFlag(&tov_led) == true)
	{
		gpio_toggleDigOut(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
	}
}

void gpio_pollLeftBtnTimer(void)
{
	if (tov_getOverflowFlag(&tov_left_button) == true)
	{
		btp_decr_overflow_trigger_count(&btp_left, 2);
	}
}

void gpio_pollRightBtnTimer(void)
{
	if (tov_getOverflowFlag(&tov_right_button) == true)
	{
		btp_incr_overflow_trigger_count(&btp_right, 2);
	}
}

/* USER CODE END 2 */
