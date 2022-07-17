/*
 * task_accelerometer.h
 *
 *  Created on: Dec 4, 2020
 *      Author: Carly Zlabek and Ben Larson
 */

#ifndef TASK_ACCELEROMETER_H_
#define TASK_ACCELEROMETER_H_


#include "main.h"

//using the same bounds as for joystick
#define VOLT_1P37  1700      // 0.85 /(3.3/4096)
#define VOLT_2P01  2500      // 2.50 /(3.3/4096)

extern TaskHandle_t Task_Accelerometer_Handle;
extern TaskHandle_t Task_Accelerometer_Timer_Handle;

/*
 * Used to initialize adc used for the accelerometer
 *
 */
void Task_Accelerometer_Init(void);

/******************************************************************************
* Bottom Half Task.  Examines the ADC data from the accelerometer on the MKII
******************************************************************************/
void Task_Accelerometer_Bottom_Half(void *pvParameters);

/******************************************************************************
* Used to start an ADC14 Conversion
******************************************************************************/
void Task_Accelerometer_Timer(void *pvParameters);

#endif /* TASK_ACCELEROMETER_H_ */
