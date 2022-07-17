/*
 * task_buttons.c
 *
 *  Created on: Dec 4, 2020
 *      Author: Carly Zlabek and Ben Larson
 */

//reused code segments from ice's and ex's

#include <main.h>

TaskHandle_t Task_Buttons_Handle;
volatile bool ALERT_S1 = false;
volatile bool ALERT_S2 = false;

/******************************************************
 * Initialize hardware resources used to control S1 and
 * S2 on the MKII
 *****************************************************/
void Task_Buttons_Init(void) {
    //configure as input
    P5->DIR &= ~BIT1; //init S1

    //init S2
    P3->DIR &= ~BIT5;

    ece353_T32_1_Interrupt_Ms(10);
}

/******************************************************
 * Returns if MKII.S1 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *     true    : Button1 is pressed
 *     false   : Button1 is not pressed
 *****************************************************/
bool ece353_MKII_S1(void) {
    //active low
    if((P5->IN & BIT1) == 0) {
        return true;
    } else {
        return false;
    }
}

/******************************************************
 * Returns if MKII.S2 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *     true    : Button2 is pressed
 *     false   : Button2 is not pressed
 *****************************************************/
bool ece353_MKII_S2(void) {
    //active low
    if((P3->IN & BIT5) == 0) {
        return true;
    } else {
        return false;
    }
}

/*****************************************************
 * Configures Timer32_1 to generate a periodic interrupt
 *
 * Parameters
 *      ticks   :   Number of milliseconds per interrupt
 * Returns
 *      None
 *****************************************************/
void ece353_T32_1_Interrupt_Ms(uint16_t ms) {
    // ticks = desired period / core clock period
    // 20e-3/(1/3e6) = (3e6 * 20)/1000
    uint32_t ticks = ((SystemCoreClock * ms)/1000) - 1;

    // Stop the timer
    TIMER32_1->CONTROL = 0;

    // Set the load register
    TIMER32_1->LOAD = ticks;

    // Enable the Timer32 interrupt in NVIC
    __enable_irq();
    NVIC_EnableIRQ(T32_INT1_IRQn);
    NVIC_SetPriority(T32_INT1_IRQn, 2);

    // Start Timer32 and enable interrupt
    TIMER32_1->CONTROL = TIMER32_CONTROL_ENABLE |   // turn timer on
                         TIMER32_CONTROL_MODE |     // periodic mode
                         TIMER32_CONTROL_SIZE |     // 32 bit timer
                         TIMER32_CONTROL_IE;        // enable interrupts
}


void Task_Buttons_Bottom_Half(void *pvParameters) {
    MSG_t msg;
    uint32_t ulEventsToProcess;

    while(1) { //send msg whenever a button is hit
        //wait for task from isr
        ulEventsToProcess = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        if(ALERT_S1) {
            msg.cmd = CMD_BUTTON1;
            msg.color = B1_COLOR;
            xQueueSend(Queue_Bop_It, &msg, portMAX_DELAY);
            ALERT_S1 = false;
        }
        if(ALERT_S2) {
            msg.cmd = CMD_BUTTON2;
            msg.color = B2_COLOR;
            xQueueSend(Queue_Bop_It, &msg, portMAX_DELAY);
            ALERT_S2 = false;
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void T32_INT1_IRQHandler(void) {
    BaseType_t xHigherPriorityTaskWoken = pdTRUE;

//    ALERT_S1 = debounce_s1(); moved debounce logic into handler
//    ALERT_S2 = debounce_s2();

    // clear the interrupt
    TIMER32_1->INTCLR = BIT0;

    if(!ALERT_S1) {
        static uint8_t debounce1_state = 0x00;
        // Shift the de-bounce variable to the right
        debounce1_state = debounce1_state << 1;

        // If S1 is being pressed, set the LSBit of debounce_state to a 1;
        if(ece353_MKII_S1()) {
            debounce1_state |= 0x01;
        }

        // If the de-bounce variable is equal to 0x7F, change the color of the tri-color LED.
        if(debounce1_state == 0x7F) {
            ALERT_S1 = true;
            vTaskNotifyGiveFromISR(Task_Buttons_Handle, &xHigherPriorityTaskWoken);
            portYIELD_FROM_ISR( xHigherPriorityTaskWoken);
        }
    }

    if(!ALERT_S2) {
        static uint8_t debounce2_state = 0x00;
        // Shift the de-bounce variable to the right
        debounce2_state = debounce2_state << 1;

        // If S1 is being pressed, set the LSBit of debounce_state to a 1;
        if(ece353_MKII_S2()) {
            debounce2_state |= 0x01;
        }

        // If the de-bounce variable is equal to 0x7F, change the color of the tri-color LED.
        if(debounce2_state == 0x7F) {
            ALERT_S2 = true;
            vTaskNotifyGiveFromISR(Task_Buttons_Handle, &xHigherPriorityTaskWoken);
            portYIELD_FROM_ISR( xHigherPriorityTaskWoken);
        }
    }
}


