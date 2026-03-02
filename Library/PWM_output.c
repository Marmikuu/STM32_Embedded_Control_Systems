/*
 * PWM output signal library
 *
 *  Created on: Mar 2, 2026
 *      Author: Marcin Mikula (Marmikuu)
 *      github.com/Marmikuu/
 */

#include "PWM_output.h"


uint32_t PWM_calc_output(float U_percent, TIM_HandleTypeDef *htim)
{

	//// Calculate PWM duty cycle from PID controller output signal in [%]
	uint32_t counter_period = ( __HAL_TIM_GET_AUTORELOAD(htim) );/// ARR - autoreload register

	return (uint32_t)(U_percent *  (counter_period+1) /100.f);
}

void PWM_set_output(float U_percent, TIM_HandleTypeDef *htim,uint32_t channel)
{
	__HAL_TIM_SET_COMPARE( htim, channel ,PWM_calc_output(U_percent, htim));
}

