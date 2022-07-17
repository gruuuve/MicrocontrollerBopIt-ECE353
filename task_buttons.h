/*
 * task_buttons.h
 *
 *  Created on: Dec 4, 2020
 *      Author: Carly Zlabek and Ben Larson
 */

#ifndef TASK_BUTTONS_H_
#define TASK_BUTTONS_H_

#include "main.h"

extern TaskHandle_t Task_Buttons_Handle;

/******************************************************
 * Initialize hardware resources used to control S1 and
 * S2 on the MKII
 *****************************************************/
void Task_Buttons_Init(void);

/******************************************************
 * Returns if MKII.S1 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *     true    : Button1 is pressed
 *     false   : Button1 is not pressed
 *****************************************************/
bool ece353_MKII_S1(void);

/******************************************************
 * Returns if MKII.S2 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *     true    : Button2 is pressed
 *     false   : Button2 is not pressed
 *****************************************************/
bool ece353_MKII_S2(void);



void ece353_T32_1_Interrupt_Ms(uint16_t ms);

void Task_Buttons_Bottom_Half(void *pvParameters);

#endif /* TASK_BUTTONS_H_ */
