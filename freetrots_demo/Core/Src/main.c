#include "main.h"

#include <FreeRTOS.h>
#include <stdio.h>
#include <task.h>

#include "event_groups.h"
#include "gpio.h"
#include "semphr.h"
#include "shell_port.h"
#include "timers_control.h"
#include "usart.h"

static TaskHandle_t m_app_thread;

EventGroupHandle_t xCreatedEventGroup;
// QueueHandle_t xStructQueue = NULL;

// struct AMessage {
//     char ucMessageID;
//     char ucData[20];
// } xMessage;

int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&hlpuart1, (void *)&ch, 1, 0xffff);
    return ch;
}

void SystemClock_Config(void);

void delay_us(uint16_t us)
{
    while (us != 0) {
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();  //
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();  //
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();  //
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();  //
        us--;
    }
}

/**
 * @brief  delay_ms.
 */
void delay_ms(uint16_t ms)
{
    while (ms != 0) {
        delay_us(2600);
        ms--;
    }
}

static void app_thread(void *arg)
{
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

static void app_init()
{
    if (pdPASS != xTaskCreate(app_thread, "app_task", 128, NULL, 2, &m_app_thread)) {
    }
}

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    // xMessage.ucMessageID = 0xab;
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_LPUART1_UART_Init();
    MX_SPI1_Init();
    // xStructQueue = xQueueCreate(10, sizeof(xMessage));
    /* Attempt to create the event group. */
    xCreatedEventGroup = xEventGroupCreate();
    userShellInit();
    BMI160_init();
    timers_control_task_init();
    app_init();

    vTaskStartScheduler();

    for (;;) {
    }
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
    RCC_OscInitStruct.MSIState = RCC_MSI_ON;
    RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_11;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
