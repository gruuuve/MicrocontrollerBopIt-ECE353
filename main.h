/*
 * main.h
 *
 *  Created on: Dec 4, 2020
 *      Author: Carly
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "msp.h"
#include "msp432p401r.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

//task headers
#include <task_accelerometer.h>
#include <task_amb_light.h>
#include <task_bop_it.h>
#include <task_buttons.h>
#include <task_action_timer.h>

//bitmap headers
#include <bopit_bitmap.h>
//#include <letters_bitmap.h>
#include <button1_bitmap.h>
#include <button2_bitmap.h>
#include <arrow_up_bitmap.h>
#include <arrow_right_bitmap.h>
#include <arrow_down_bitmap.h>
#include <arrow_left_bitmap.h>
#include <lightbulb_bitmap.h>

//extra peripheral communication headers
#include <lcd.h>
#include <i2c.h>
#include <buzzer.h>

#endif /* MAIN_H_ */
