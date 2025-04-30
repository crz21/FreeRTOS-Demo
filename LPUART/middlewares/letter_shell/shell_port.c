/**
 * @file shell_port.c
 * @author Letter (NevermindZZT@gmail.com)
 * @brief letter shell segger rtt demo
 * @version 0.1
 * @date 2024-04-20
 * 
 * @copyright (c) 2024 Letter
 * 
 */

 #include "FreeRTOS.h"
 #include "task.h"
 #include "shell.h"
// #include "serial.h"
#include "stm32u0xx.h"
 #include "usart.h"
// #include "cevent.h"
// #include "log.h"
#include "semphr.h"
#include "stm32u0xx_hal_usart.h"

#define SHELL_BUFFER_SIZE 512

Shell shell;
char shellBuffer[SHELL_BUFFER_SIZE];

static SemaphoreHandle_t shellMutex;

/**
 * @brief rtt shell写
 * 
 * @param data 数据
 * @param len 数据长度
 * 
 * @return short 实际写入的数据长度
 */
short userShellWrite(char *data, unsigned short len)
{
    // serialTransmit(&debugSerial, (uint8_t *)data, len, 0x1FF);
    HAL_UART_Transmit(&usart1, (uint8_t *)data, len, 0x1FF);
    return len;
}


/**
 * @brief rtt shell读
 * 
 * @param data 数据
 * @param len 数据长度
 * 
 * @return short 实际读取的数据长度
 */
short userShellRead(char *data, unsigned short len)
{
    // return serialReceive(&debugSerial, (uint8_t *)data, len, 0);
    return HAL_UART_Receive(&usart1, (uint8_t *)data, len, 0);
}

/**
 * @brief 用户shell上锁
 * 
 * @param shell shell
 * 
 * @return int 0
 */
int userShellLock(Shell *shell)
{
    xSemaphoreTake(shellMutex, portMAX_DELAY);
    return 0;
}

/**
 * @brief 用户shell解锁
 * 
 * @param shell shell
 * 
 * @return int 0
 */
int userShellUnlock(Shell *shell)
{
    xSemaphoreGive(shellMutex);
    return 0;
}

/**
 * @brief 用户shell初始化
 * 
 */
void userShellInit(void)
{
    shellMutex = xSemaphoreCreateMutex();

    shell.write = userShellWrite;
    shell.read = userShellRead;
    shell.lock = userShellLock;
    shell.unlock = userShellUnlock;
    shellInit(&shell, shellBuffer, 512);
    if (xTaskCreate(shellTask, "shell", 256, &shell, 5, NULL) != pdPASS)
    {
        // logError("shell task creat failed");
    }
}
