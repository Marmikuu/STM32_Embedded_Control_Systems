/*
 * PWM output signal library
 *
 *  Created on: Mar 2, 2026
 *      Author: Marcin Mikula (Marmikuu)
 *      github.com/Marmikuu/
 */

#ifndef INC_PWM_OUTPUT_H_
#define INC_PWM_OUTPUT_H_

#include "stm32l4xx_hal.h"


uint32_t PWM_calc_output(float U_percent, TIM_HandleTypeDef *htim); /// convert PWM duty cycle in [%] to timer period value

void PWM_set_output(float U_percent, TIM_HandleTypeDef *htim, uint32_t channel); //// set



#endif /* INC_PWM_OUTPUT_H_ */
