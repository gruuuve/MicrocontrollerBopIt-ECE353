/*
 * task_bop_it.c
 *
 *  Created on: Dec 7, 2020
 *      Author: Ben Larson and Carly Zlabek
 */

#include "task_bop_it.h"

TaskHandle_t Task_Bop_It_Handle;
QueueHandle_t Queue_Bop_It;

bool passed = false;

void Task_Bop_It_Init(void) {

    // create Queue
    Queue_Bop_It = xQueueCreate(5,sizeof(MSG_t));

    // initialize the LCD
    Crystalfontz128x128_Init();

}

/******************************************************************************
 * This function will update the location of the x variable
 ******************************************************************************/
uint8_t move_x(uint8_t x, uint8_t y, int dir) {

    lcd_draw_bop_it(LCD_COLOR_BLACK, x, y);

    switch(dir) {

    case CMD_LEFT : // checks for command to move left
        if(x > ((bopitWidthPixels/2) + 45)) {
            x = x - 10; // decrements x if not at boundary
        } else {
            x = (bopitWidthPixels/2) + 35;
        }
        break;
    case CMD_RIGHT : // checks for command to move right
        if(x < (83 - (bopitWidthPixels/2))) {
            x = x + 10; // increments x if not at boundary
        } else {
            x = 93 - (bopitWidthPixels/2);
        }
        break;
    default:
        break;
    }

    return x;

}

/******************************************************************************
 * This function will update the location of the y variable
 ******************************************************************************/
uint8_t move_y(uint8_t y, int dir) {

    switch(dir) {

    case CMD_UP : // checks for command to move left
        if(y > ((bopitHeightPixels/2) + 45)) {
            y = y - 10; // decrements x if not at boundary
        } else {
            y = (bopitHeightPixels/2) + 35;
        }
        break;
    case CMD_DOWN : // checks for command to move right
        if(y < (83 - (bopitHeightPixels/2))) {
            y = y + 10; // increments x if not at boundary
        } else {
            y = 93 - (bopitHeightPixels/2);
        }
        break;
    default:
        break;
    }
    return y;
}

//driver helper functions

//something for assigning an action to do
MSG_t action_assign(void) {
    time_t t;
    srand(0); //init rand seed
    int random = rand();
    int r = random % 20; //random # b/w 0 and 20 (21 elements)
    MSG_t exp_action;

    if(r >= 0 && r <= 2) {
        exp_action.cmd = CMD_LEFT;
        exp_action.color = ACCELEROMETER_COLOR_LEFT;
    } else if(r >= 3 && r <= 5) {
        exp_action.cmd = CMD_RIGHT;
        exp_action.color = ACCELEROMETER_COLOR_RIGHT;
    } else if(r >= 6 && r <= 8) {
        exp_action.cmd = CMD_DOWN;
        exp_action.color = ACCELEROMETER_COLOR_DOWN;
    } else if(r >= 9 && r <= 11) {
        exp_action.cmd = CMD_UP;
        exp_action.color = ACCELEROMETER_COLOR_UP;
    } else if(r >= 12 && r <= 14) {
        exp_action.cmd = CMD_LIGHT;
        exp_action.color = AMB_LIGHT_COLOR;
    } else if(r >= 15 && r <= 17) {
        exp_action.cmd = CMD_BUTTON1;
        exp_action.color = B1_COLOR;
    } else { // r >= 18 && r <= 20
        exp_action.cmd = CMD_BUTTON2;
        exp_action.color = B2_COLOR;
    }
    return exp_action;
}

void Task_Bop_It(void *pvParameters) {

    MSG_t first_timer;
    
    opening_number();
    xQueueReceive(Queue_Bop_It, &first_timer, portMAX_DELAY);
    
    uint8_t x = 64;
    uint8_t y = 64;

    lcd_draw_board(LCD_COLOR_WHITE);
    lcd_draw_bop_it(LCD_COLOR_WHITE, x, y);

    MSG_t msg;
    MSG_t msg_exp;

    while(1) {
        vTaskDelay(pdMS_TO_TICKS(10));

        msg_exp = action_assign(); // randomly assign actions
        passed = false;

        lcd_draw_board(msg_exp.color);
        lcd_draw_bop_it(msg_exp.color, x, y);

        //receive action (failed or action returned)
        xQueueReceive(Queue_Bop_It, &msg, portMAX_DELAY);

        if(msg.cmd == msg_exp.cmd) { //check if input as expected
            passed = true;
            x = move_x(x, y, msg.cmd);
            y = move_y(y, msg.cmd);
            lcd_draw_bop_it(LCD_COLOR_WHITE, x, y);
            buzzer_confirm();
        } else { //failed or cmd's don't match
            lcd_draw_board(LCD_COLOR_RED);
            x = move_x(x, y, msg.cmd);
            lcd_draw_bop_it(LCD_COLOR_RED, x, y);
            buzzer_fail();
            while(1) {} //wait for reset to begin another game
        }
    }
}

void opening_number() {
    uint8_t x1 = 64;
    uint8_t y1 = 13;
    uint8_t x2 = 64;
    uint8_t y2 = 115;
    uint8_t x3 = 21;
    uint8_t y3 = 64;
    uint8_t x4 = 107;
    uint8_t y4 = 64;
    lcd_draw_bop_it(LCD_COLOR_RED, x1, y1);
    lcd_draw_bop_it(LCD_COLOR_YELLOW, x2, y2);
    lcd_draw_bop_it(LCD_COLOR_GREEN, x3, y3);
    lcd_draw_bop_it(LCD_COLOR_BLUE, x4, y4);

    int i = 0;
    for(i = 0; i < 90; i++) {
        lcd_draw_bop_it(LCD_COLOR_BLACK, x1 - 1, y1);
        lcd_draw_bop_it(LCD_COLOR_RED, x1, y1);
        x1++;
    }

    for(i = 0; i < 90; i++) {
        lcd_draw_bop_it(LCD_COLOR_BLACK, x2 + 1, y2);
        lcd_draw_bop_it(LCD_COLOR_YELLOW, x2, y2);
        x2--;
    }

    for(i = 0; i < 90; i++) {
        lcd_draw_bop_it(LCD_COLOR_BLACK, x3, y3 - 1);
        lcd_draw_bop_it(LCD_COLOR_GREEN, x3, y3);
        y3++;
    }

    for(i = 0; i < 90; i++) {
        lcd_draw_bop_it(LCD_COLOR_BLACK, x4, y4 + 1);
        lcd_draw_bop_it(LCD_COLOR_BLUE, x4, y4);
        y4--;
    }

    lcd_draw_rectangle(64, 64, 132, 132, LCD_COLOR_BLACK);

}
