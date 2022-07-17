/*
 * task_amb_light.h
 *
 *  Created on: Dec 7, 2020
 *      Author: Ben Larson and Carly Zlabek
 */

#ifndef TASK_AMB_LIGHT_H_
#define TASK_AMB_LIGHT_H_

#include "msp.h"
#include "i2c.h"
#include "task_bop_it.h"
#include "lcd.h"
#include <stdint.h>
#include <stdbool.h>

#include <FreeRTOS.h>
#include <task.h>

#define I2C_AMB_ADDR   0x44

#define I2C_AMB_RESULT         0x00
#define I2C_AMB_CONFIG         0x01
#define I2C_AMB_LOW_LIM        0x02
#define I2C_AMB_HIGH_LIM       0x03
#define I2C_AMB_DEV_ID         0x7F

#define OPT3001_AUTO           0xC000
#define OPT3001_CONT           0x0600

extern TaskHandle_t Task_Amb_Light_Handle;

/******************************************************************************
 * Initialize the tmp006 temperature sensor on the MKII.  This function assumes
 * that the I2C interface has already been configured to operate at 100KHz.
 ******************************************************************************/
void opt3001_init(void);

/******************************************************************************
 * Returns the current temperature in degrees C.
 ******************************************************************************/
float opt3001_read_lux(void);

/******************************************************************************
 * Measures the ambient light once a second
 ******************************************************************************/
void Task_Amb_Light(void *pvParameters);


#endif /* TASK_AMB_LIGHT_H_ */
