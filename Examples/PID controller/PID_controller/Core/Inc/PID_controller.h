/*
 * PID controller library
 *
 *  Created on: Mar 1, 2026
 *
 *      Author: Marcin Mikula
 *
 */

#ifndef INC_PID_CONTROLLER_H_
#define INC_PID_CONTROLLER_H_


#include "stm32l4xx_hal.h"
#include <stdbool.h>

typedef struct {

	float Kp; //// Gain [-]
	float Ti; /// Integral time constant [s]
	float Td;  //// Derivative time constant  [s]

	float err_sum;
	float err_old;

	bool antiwindup_ON;

	float Ts; //// sampling time [s]

	float U_min;/// [%]
	float U_max; /// [%]


	////// PWM output signal generation
	TIM_HandleTypeDef *htim;
	uint32_t channel;

} PID_HandleTypeDef;


float PID_calc_U(PID_HandleTypeDef *hPID,float y ,float y_set);

uint32_t PWM_calc_output(float U_percent, TIM_HandleTypeDef *htim);

void PWM_set_output(float U_percent, PID_HandleTypeDef *hPID);

void PID_controller_init(PID_HandleTypeDef *hPID, float Kp, float Ti , float Td, float Ts, bool Antiwindup_ON, TIM_HandleTypeDef *htim,uint32_t channel );

#endif /* INC_PID_CONTROLLER_H_ */
