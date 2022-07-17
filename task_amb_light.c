/*
 * task_amb_light.c
 *
 *  Created on: Dec 7, 2020
 *      Author: Ben Larson and Carly Zlabek
 */

#include "task_amb_light.h"


TaskHandle_t Task_Amb_Light_Handle;

/******************************************************************************
 * Initialize the opt3001 temperature sensor on the MKII.  This function assumes
 * that the I2C interface has already been configured to operate at 100KHz.
 ******************************************************************************/
void opt3001_init(void)
{

    // Program the CONFIG register to AUTO and be in continuous mode
    i2c_write_16(I2C_AMB_ADDR, I2C_AMB_CONFIG, (OPT3001_AUTO | OPT3001_CONT));
}

/******************************************************************************
 * Returns the current ambient light in lux
 ******************************************************************************/
float opt3001_read_lux(void)
{

    // Read the ambient light
    uint16_t lux = i2c_read_16(I2C_AMB_ADDR, I2C_AMB_RESULT);

    // bits [15:12] used as exponent
    double exponent = (lux >> 12);

    double LSB_Size = 0.01;

    // calculate conversion rate
    while(exponent != 0) {

        LSB_Size = LSB_Size * 2;

        exponent--;
    }

    // Return the data in degrees lux
    return (float)((lux & 0x0FFF) * LSB_Size);
}

/******************************************************************************
 * Measures the ambient light once a second
 ******************************************************************************/
void Task_Amb_Light(void *pvParameters)
 {

    float lux = 0.0;

    MSG_t msg;

     while(1)
     {
         vTaskDelay(pdMS_TO_TICKS(10));
         /*
          * Read the ambient light
          */
         lux = opt3001_read_lux();

         msg.cmd = CMD_LIGHT;
         msg.color = LCD_COLOR_BLUE; //default ambient color

//         if(lux > 100) {
//             msg.color = LCD_COLOR_YELLOW;
//         } else if(lux > 60) {
//             msg.color = LCD_COLOR_GREEN;
//         } else if(lux > 20) {
//             msg.color = LCD_COLOR_GREEN2;
//         } else {
//             msg.color = LCD_COLOR_BLUE2;
//         }

         if(lux < 15) { //action complete or failed decision
             msg.color = LCD_COLOR_BLUE2;
             xQueueSend(Queue_Bop_It, &msg, portMAX_DELAY);
         }



         /*
          * Delay a half second
          */
         vTaskDelay(pdMS_TO_TICKS(1000));

     }
 }



