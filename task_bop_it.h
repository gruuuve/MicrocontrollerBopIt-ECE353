/*
 * task_bop_it.h
 *
 *  Created on: Dec 7, 2020
 *      Author: Ben Larson and Carly Zlabek
 */

#ifndef TASK_BOP_IT_H_
#define TASK_BOP_IT_H_

#include "msp.h"
#include "i2c.h"
#include "lcd.h"
#include "bopit_bitmap.h"
//#include "letters_bitmap.h"
#include <stdint.h>
#include <stdbool.h>

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

typedef enum {
    CMD_LEFT,
    CMD_RIGHT,
    CMD_UP,
    CMD_DOWN,
    CMD_CENTER,
    CMD_FAILED,
    CMD_LIGHT,
    CMD_BUTTON1,
    CMD_BUTTON2
} CMD_t;

typedef struct {
    CMD_t        cmd;
    uint16_t     color;
}MSG_t;

//action colors
#define ACCELEROMETER_COLOR_UP 0xFBE4 //ORANGE
#define ACCELEROMETER_COLOR_RIGHT 0x7BEF //GREY
#define ACCELEROMETER_COLOR_DOWN 0xFFE0 //YELLOW
#define ACCELEROMETER_COLOR_LEFT 0xA254 //MAGENTA
#define B1_COLOR 0x07E0 //green 1
#define B2_COLOR 0x07FF //cyan (green2 was too similar to green)
#define AMB_LIGHT_COLOR 0x001F //blue 1 (blue)
#define AMB_LIGHT_COLOR_CONFIRMED 0x051D //blue 2    

extern TaskHandle_t Task_Bop_It_Handle;
extern QueueHandle_t Queue_Bop_It;

extern bool passed;

void Task_Bop_It_Init(void);

void Task_Bop_It(void *pvParameters);

void opening_number(void);

#endif /* TASK_BOP_IT_H_ */
