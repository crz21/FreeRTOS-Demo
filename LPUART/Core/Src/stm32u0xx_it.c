/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    stm32u0xx_it.c
 * @brief   Interrupt Service Routines.
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
#include "main.h"
#include "stm32u0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern UART_HandleTypeDef usart1;
/* USER CODE BEGIN EV */
uint8_t Buffer[10];
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SVC instruction.
  */
//void SVC_Handler(void)
//{

//}

/**
  * @brief This function handles Pendable request for system service.
  */
//void PendSV_Handler(void)
//{

//}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{

  // HAL_IncTick();

// delay_decrement();
    #if (INCLUDE_xTaskGetSchedulerState == 1)
        if (xTaskgetSchedulerState() != taskSCHEDULER_NOT_STARTED)
        {
    #endif
            xPortSysTickHandler();
    #if (INCLUDE_xTaskGetSchedulerState == 1)    
        }
    #endif
}

/******************************************************************************/
/* STM32U0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32u0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles USART3 (combined with EXTI 24) + LPUART1 global interrupt (combined with EXTI lines 28).
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_LPUART1_IRQn 0 */

  /* USER CODE END USART3_LPUART1_IRQn 0 */
  HAL_UART_IRQHandler(&usart1);
  /* USER CODE BEGIN USART3_LPUART1_IRQn 1 */

  /* USER CODE END USART3_LPUART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);

  if (huart->Instance == USART1)
  {
    HAL_UART_Transmit(&usart1, (uint8_t *)Buffer, 10, 0xFFFF);
  }

  HAL_UART_Receive_IT(&usart1, (uint8_t *)Buffer, 10);
}

/* USER CODE END 1 */
