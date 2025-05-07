#include "shell_extend.h"

#include <FreeRTOS.h>
#include <stdio.h>
#include <task.h>

#include "gpio.h"
#include "semphr.h"
#include "shell.h"
#include "task.h"

void shell_contrel_led(void)
{
    Shell *shell = shellGetCurrent();
    //    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC) | SHELL_CMD_DISABLE_RETURN, led,
                 shell_contrel_led, contrel_led);

/******************************************************************************************************
** @brief
*
*
*
*******************************************************************************************************/
void list_thread(int argc, char *agrv[])
{
    static char vTask_buffer[4096] = {0};

    vTaskList(vTask_buffer);
    printf("-------------------------------------------------------------------------------- \r\n");
    printf("Task Name       State  Prio     Stack  Num \r\n");
    printf("%s    \r\n", vTask_buffer);
    printf("-------------------------------------------------------------------------------- \r\n");
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN) | SHELL_CMD_DISABLE_RETURN, thread,
                 list_thread, show freertos list thread information);

