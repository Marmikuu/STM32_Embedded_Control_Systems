/*
 * PID controller library
 *
 *  Created on: Mar 1, 2026
 *
 *      Author: Marcin Mikula (Marmikuu)
 *      github.com/Marmikuu/
 *
 */

#include "PID_controller.h"

float PID_calc_U(PID_HandleTypeDef *hPID,float y ,float y_set)
{
	float err  = y_set-y;
	float err_diff = err - (hPID->err_old);

	///// Output signal components
	float Up = (hPID -> Kp) * err; /// Proportional part

	float Ui; 		///// Integral part

	if ((hPID ->Ti) <= 0.0f)
	{
		Ui = 0.0f;
	}
	else
	{
		Ui = (hPID->err_sum)*( (hPID->Ts) / hPID-> Ti);
	}


	float Ud = err_diff * (hPID->Kp) * (hPID->Td / hPID->Ts);
	float U = Up + Ui + Ud;

	//////////// Anti-windup method (clamping)

	if (hPID->antiwindup_ON == true)
	{
		if ( (U > hPID->U_min && U < hPID->U_max))
		{
			hPID->err_sum += err;
		}
	}

	///////////// Output signal (U) saturation

	if (U <= hPID->U_min)
	{
		U = hPID->U_min;
	}
	else if(U >= hPID->U_max)
	{
		U = hPID->U_max;
	}


	hPID->err_old = err;

	return U;
}


void PID_controller_init(PID_HandleTypeDef *hPID, float Kp, float Ti , float Td, float Ts, bool antiwindup_ON)
{
	hPID->Kp = Kp;
	hPID -> Ti =Ti;
	hPID ->Td = Td;
	hPID ->Ts = Ts;
	hPID -> antiwindup_ON = antiwindup_ON;

	hPID ->U_max = 100.0f;
	hPID-> U_min = 0.0f;

	hPID->err_old = 0.0f;
	hPID->err_sum = 0.0f;
}

