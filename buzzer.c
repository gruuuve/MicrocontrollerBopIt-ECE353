/*
 * buzzer.c
 *
 *  Created on: Dec 4, 2020
 *      Author: Carly Zlabek and Ben Larson
 */

//reused from previous segments

#include <main.h>

/******************************************************
 * Sets the PWM period of the buzzer. The duty cycle
 * will be set to 50%
 *
 * Parameters
 *     ticks_period    :    Period of the PWM pulse
 *
 * Returns
 *     None
 *****************************************************/
void ece353_MKII_Buzzer_init(uint16_t ticks_period) {
    //set P2.7 to be a GPIO OUTPUT pin
    P2->DIR |= BIT7;
    //the TIMERA PWM controller will control the buzzer on the MKII
    //P2.7 <-->TA0.4
    P2->SEL0 |= BIT7;
    P2->SEL1 &= ~BIT7;
    //Turn off TA0
    TIMER_A0->CTL = 0;
    //Set the period of the timer
    TIMER_A0->CCR[0] = ticks_period - 1;
    //Configure buzzer duty cycle to 50%
    TIMER_A0->CCR[4] = (ticks_period/2) - 1;
    //Configure TA0.4 for RESET/SET mode
    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;
    //Select the master clock as the timer source
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK;
}

void buzzer_period_change(uint16_t ticks_period) {
    //Turn off TA0
    TIMER_A0->CTL = 0;
    //Set the period of the timer
    TIMER_A0->CCR[0] = ticks_period - 1;
    //Configure buzzer duty cycle to 50%
    TIMER_A0->CCR[4] = (ticks_period/2) - 1;

    //not needed below, already set in init
//    //Configure TA0.4 for RESET/SET mode
//    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;
//    //Select the master clock as the timer source
//    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK;
}

/******************************************************
 * Play the confirmed action sound
 *
 * Parameters
 *     None
 * Returns
 *     None
 *****************************************************/
void buzzer_confirm(void) {
    ece353_MKII_Buzzer_init(22944);
    ece353_MKII_Buzzer_On();
    int i = 0;
    for(i = 0; i < 150000; i++) { // busy wait

    }
    ece353_MKII_Buzzer_Off();

    //change to E6
    ece353_MKII_Buzzer_init(18195);
    ece353_MKII_Buzzer_On();
    for(i = 0; i < 250000; i++) { // busy wait

    }
    ece353_MKII_Buzzer_Off();
}

//don't care for either above or below if buzzer is already running, play most recent action sound

/******************************************************
 * Play the failed action sound
 *
 * Parameters
 *     None
 * Returns
 *     None
 *****************************************************/
void buzzer_fail(void) {
    ece353_MKII_Buzzer_init(27272);
    ece353_MKII_Buzzer_On();
    int i = 0;
    for(i = 0; i < 500000; i++) { // busy wait

    }
    ece353_MKII_Buzzer_Off();
}

/******************************************************
 * Turns the buzzer on
 *
 * Parameters
 *     None
 * Returns
 *     None
 *****************************************************/
void ece353_MKII_Buzzer_On(void) {
    //clear the current mode control bits
    TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK;
    //set mode control to UP and clear the current count
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP | TIMER_A_CTL_CLR;
}

/******************************************************
 * Turns the buzzer off
 *
 * Parameters
 *     None
 * Returns
 *     None
 *****************************************************/
void ece353_MKII_Buzzer_Off(void) {
    //turn off the timer
    TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK;
}

/******************************************************
 * Checks buzzer run status
 *
 * Parameters
 *     None
 * Returns
 *     True if TimerA0 is On
 *     False if TimerA0 is off
 *****************************************************/
bool ece353_MKII_Buzzer_Run_Status(void) {
    if((TIMER_A0->CTL & TIMER_A_CTL_MC_MASK) == TIMER_A_CTL_MC__STOP) {
        return false;
    } else {
        return true;
    }
}
