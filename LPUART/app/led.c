#include "led.h"

#include <FreeRTOS.h>
#include <stdio.h>
#include <task.h>

#include "gpio.h"
#include "semphr.h"

static TaskHandle_t m_led1_thread;
static TaskHandle_t m_led2_thread;
static SemaphoreHandle_t g_test_mutex;
extern void delay_ms(uint16_t ms);

void led1_thread(void *arg)
{
    for (;;) {
        if (xSemaphoreTake(g_test_mutex, portMAX_DELAY)) {
            // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
            xSemaphoreGive(g_test_mutex);
            vTaskDelay(pdMS_TO_TICKS(200));
            // delay_ms(100);
        }
    }
}

void led2_thread(void *arg)
{
    for (;;) {
        if (xSemaphoreTake(g_test_mutex, portMAX_DELAY)) {
            // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
            xSemaphoreGive(g_test_mutex);
            vTaskDelay(pdMS_TO_TICKS(200));
            // delay_ms(100);
        }
    }
}

void led_init(void)
{
    g_test_mutex = xSemaphoreCreateMutex();
    xTaskCreate(led1_thread, "led1_task", 128, NULL, 8, &m_led1_thread);
    xTaskCreate(led2_thread, "led2_task", 128, NULL, 8, &m_led2_thread);
}
