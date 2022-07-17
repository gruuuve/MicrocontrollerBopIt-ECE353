/*
 * task_action_timer.c
 *
 *  Created on: Dec 4, 2020
 *      Author: Carly Zlabek and Ben Larson
 */

#include "task_action_timer.h"

TaskHandle_t Task_Action_Timer_Handle;
uint8_t timer_iter = 50; //start w/ 5 sec timer (50 * 100ms)
// subtract 100 ms each successful action (timer_value--)




///* ******************************************************
// * Busy waits for 100ms
// *
// * Parameters
// *     none
// *
// * Returns
// *     none
// * ******************************************************/
//void ece353_T32_1_wait_100ms() {
//
//    //stop the timer
//    TIMER32_1->CONTROL = 0;
//    //set the timer to be a 32-bit, one-shot
//    TIMER32_1->CONTROL = TIMER32_CONTROL_ONESHOT | TIMER32_CONTROL_SIZE;
//    //set the load register
////    desired_freq = 10; //100ms
////    calc_ticks = SystemCoreClock / desired_freq = 2400000
//    TIMER32_1->LOAD = 2400000;
//    //start the timer
//    TIMER32_1->CONTROL |= TIMER32_CONTROL_ENABLE;
//    //wait until it reaches 0
//    while(TIMER32_1->VALUE != 0) {
//        //timer is still counting, so wait
//    }
//}

void Task_Action_Timer(void *pvParameters) {
    int i;
    MSG_t msg;

    while(1) {
        msg.color = LCD_COLOR_RED;
        msg.cmd = CMD_FAILED;
        for(i = 0; i < timer_iter; i++) {
            // used vTaskDelay instead of T32 so T32 could be used w/ button task
            vTaskDelay(pdMS_TO_TICKS(100));
            if(passed) {
                break;
            }
        }
        if(!passed) {
            xQueueSend(Queue_Bop_It, &msg, portMAX_DELAY);
        }
        timer_iter--; //shorten the timer each successful action
    }
}
