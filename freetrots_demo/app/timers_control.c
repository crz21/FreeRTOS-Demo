#include "timers_control.h"

#include "FreeRTOS.h"
#include "gpio.h"
#include "timers.h"

static TimerHandle_t xCreatedTimer1;
// static TimerHandle_t xCreatedTimer2;
// static TimerHandle_t xCreatedTimer3;
// static TimerHandle_t xCreatedTimer4;
#define OSTIMER_WAIT_FOR_QUEUE 2 /**< Number of ticks to wait for the timer queue to be ready */

#define xTimer1Period (500)
// #define xTimer2Period (600)
// #define xTimer3Period (700)
// #define xTimer4Period (800)

void v_timer1_callback(TimerHandle_t xTimer)
{
    const uint32_t ulMaxExpiryCountBeforeStopping = 10;
    uint32_t ulCount;

    /* Optionally do something if the pxTimer parameter is NULL. */
    configASSERT(xTimer);

    /* The number of times this timer has expired is saved as the
       timer's ID. Obtain the count. */
    //  ulCount = (uint32_t)pvTimerGetTimerID(xTimer);

    /* Increment the count, then test to see if the timer has expired
       ulMaxExpiryCountBeforeStopping yet. */
    ulCount++;

    /* If the timer has expired 10 times then stop it from running. */
    if (ulCount >= ulMaxExpiryCountBeforeStopping) {
        /* Do not use a block time if calling a timer API function
           from a timer callback function, as doing so could cause a
           deadlock! */
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        //   xTimerStop(xTimer, 0);
    } else {
        /* Store the incremented count back into the timer's ID field
           so it can be read back again the next time this software timer
           expires. */
        //   vTimerSetTimerID(xTimer, (void *)ulCount);
    }
}

void timers_control_task_init(void)
{
    xCreatedTimer1 = xTimerCreate("timer_1", xTimer1Period, pdTRUE, (void *)0, v_timer1_callback);
    if (xCreatedTimer1 != NULL) xTimerStart(xCreatedTimer1, OSTIMER_WAIT_FOR_QUEUE);
}
