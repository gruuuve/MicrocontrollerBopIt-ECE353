/*
 * task_accelerometer.c
 *
 *  Created on: Dec 4, 2020
 *      Author: Carly Zlabek and Ben Larson
 */
#include <main.h>

TaskHandle_t Task_Accelerometer_Handle;
TaskHandle_t Task_Accelerometer_Timer_Handle;

volatile uint16_t ACCELEROMETER_X_DIR = 0;
volatile uint16_t ACCELEROMETER_Y_DIR = 0;
volatile uint16_t ACCELEROMETER_Z_DIR = 0;

/*
 * Used to initialize resources used for the accelerometer
 *
 * PIN LINEUPS
 *
 * A_X J3.23 -> P6.1 A14
 * A_Y J3.24 -> P4.0 A13
 * A_Z J3.25 -> P4.2 A11
 *
 */
void Task_Accelerometer_Init(void) {
    //accelerometer pin init
    //init x dir
    P6->SEL0 |= BIT1;
    P6->SEL1 &= ~BIT1;

    //init y dir
    P4->SEL0 |= BIT0;
    P4->SEL1 &= ~BIT0;

    //init z dir (needs different sel inputs?)
    P4->SEL0 |= BIT2;
    P4->SEL1 |= BIT2;

    // Configure CTL0 to sample 16-times in pulsed sample mode.
    // NEW -- Indicate that this is a sequence of samples.
    ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_CONSEQ_1;

    // Configure CTL1 to return 12-bit values
    ADC14->CTL1 = ADC14_CTL1_RES_2;         // Use sampling timer, 12-bit conversion results

    //add signals for 3 accelerometer axis
    // X = A14, Y = A13, Z = A11
    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_14;

    ADC14->MCTL[1] |= ADC14_MCTLN_INCH_13 | ADC14_MCTLN_EOS;

    //end of sequence
    //ADC14->MCTL[2] |= ADC14_MCTLN_INCH_11 | ADC14_MCTLN_EOS;

    //EDIT to whatever final accel mem signal
    // Enable interrupts AFTER a value is written into MEM[1].
    ADC14->IER0 |= ADC14_IER0_IE1;

    // Enable ADC Interrupt
    NVIC_EnableIRQ(ADC14_IRQn);

    // Interrupt priorities must NOT be set to 0.  It is preferred if they are set to a value that is > than 1 too.
    NVIC_SetPriority(ADC14_IRQn,2);

    // Turn ADC ON
    ADC14->CTL0 |= ADC14_CTL0_ON;
}

/******************************************************************************
* Used to start an ADC14 Conversion
******************************************************************************/
void Task_Accelerometer_Timer(void *pvParameters) {

    while(1) {
        //start the conversion
        ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;

        //delay 5mS
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

/******************************************************************************
* Bottom Half Task.  Examines the ADC data from the accelerometer on the MKII
******************************************************************************/
void Task_Accelerometer_Bottom_Half(void *pvParameters) {
    uint32_t ulEventsToProcess;
    MSG_t msg;

    while(1) {
        vTaskDelay(pdMS_TO_TICKS(10)); //wait so extra msg's aren't sent

        ulEventsToProcess = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        msg.cmd = CMD_CENTER; //default
        msg.color = LCD_COLOR_BLACK; //accelerometer action = orange image

        if(ACCELEROMETER_X_DIR > 2300) { //RIGHT
            msg.cmd = CMD_RIGHT;
        } else if (ACCELEROMETER_X_DIR < VOLT_1P37) { //LEFT
            msg.cmd = CMD_LEFT;
        }

        if(ACCELEROMETER_Y_DIR > 2300) { //UP
            msg.cmd = CMD_UP;
        } else if (ACCELEROMETER_Y_DIR < VOLT_1P37) { //DOWN
            msg.cmd = CMD_DOWN;
        }

        if(msg.cmd != CMD_CENTER) { //only send cmd when the accelerometer
        xQueueSend(Queue_Bop_It, &msg, portMAX_DELAY); //is actually tilted
        }

        vTaskDelay(pdMS_TO_TICKS(750)); //wait so extra msg's aren't sent
    }
}

/******************************************************************************
* Top Half of ADC14 Handler.
******************************************************************************/
void ADC14_IRQHandler(void) {
    BaseType_t xHigherPriorityTaskWoken = pdTRUE;

    ACCELEROMETER_X_DIR = ADC14->MEM[0]; // read and clear interrupt
    ACCELEROMETER_Y_DIR = ADC14->MEM[1]; // values given in quantized voltage levels
    //ACCELEROMETER_Z_DIR = ADC14->MEM[2]; // stored full accelerometer data, didn't use z axis

    //send task notification to bottom half
    vTaskNotifyGiveFromISR(Task_Accelerometer_Handle, &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

}


