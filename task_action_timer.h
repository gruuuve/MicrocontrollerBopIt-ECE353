/*
 * task_action_timer.h
 *
 *  Created on: Dec 4, 2020
 *      Author: Carly Zlabek and Ben Larson
 */
#ifndef TASK_ACTION_TIMER_H_
#define TASK_ACTION_TIMER_H_

#include "main.h"

extern TaskHandle_t Task_Action_Timer_Handle;
extern uint8_t timer_iter;

/* ******************************************************
 * Busy waits for 100ms
 *
 * Parameters
 *     none
 *
 * Returns
 *     none
 * ******************************************************/
void ece353_T32_1_wait_100ms();

void Task_Action_Timer(void *pvParameters);

#endif /* TASK_ACTION_TIMER_H_ */
