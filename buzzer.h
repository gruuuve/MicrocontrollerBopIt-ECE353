/*
 * buzzer.h
 *
 *  Created on: Dec 4, 2020
 *      Author: Carly Zlabek and Ben Larson
 */
#ifndef BUZZER_H_
#define BUZZER_H_

#include "main.h"

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
void ece353_MKII_Buzzer_init(uint16_t ticks_period);

/******************************************************
 * Turns the buzzer on
 *
 * Parameters
 *     None
 * Returns
 *     None
 *****************************************************/
void ece353_MKII_Buzzer_On(void);

/******************************************************
 * Turns the buzzer off
 *
 * Parameters
 *     None
 * Returns
 *     None
 *****************************************************/
void ece353_MKII_Buzzer_Off(void);

/******************************************************
 * Checks buzzer run status
 *
 * Parameters
 *     None
 * Returns
 *     True if TimerA0 is On
 *     False if TimerA0 is off
 *****************************************************/
bool ece353_MKII_Buzzer_Run_Status(void);

/******************************************************
 * Play the confirmed action sound
 *
 * Parameters
 *     None
 * Returns
 *     None
 *****************************************************/
void buzzer_confirm(void);

/******************************************************
 * Play the failed action sound
 *
 * Parameters
 *     None
 * Returns
 *     None
 *****************************************************/
void buzzer_fail(void);

#endif /* BUZZER_H_ */
