/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "PID_controller.h"
#include "tim.h"



/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

float setpoint_gl; /// global setpoint variable



/* USER CODE END Variables */
/* Definitions for LED_task */
osThreadId_t LED_taskHandle;
const osThreadAttr_t LED_task_attributes = {
  .name = "LED_task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for PID_task */
osThreadId_t PID_taskHandle;
const osThreadAttr_t PID_task_attributes = {
  .name = "PID_task",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Setpoint_task */
osThreadId_t Setpoint_taskHandle;
const osThreadAttr_t Setpoint_task_attributes = {
  .name = "Setpoint_task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void LED_task_init(void *argument);
void PID_task_init(void *argument);
void Setpoint_task_init(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of LED_task */
  LED_taskHandle = osThreadNew(LED_task_init, NULL, &LED_task_attributes);

  /* creation of PID_task */
  PID_taskHandle = osThreadNew(PID_task_init, NULL, &PID_task_attributes);

  /* creation of Setpoint_task */
  Setpoint_taskHandle = osThreadNew(Setpoint_task_init, NULL, &Setpoint_task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_LED_task_init */
/**
  * @brief  Function implementing the LED_task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_LED_task_init */
void LED_task_init(void *argument)
{
  /* USER CODE BEGIN LED_task_init */
  /* Infinite loop */
  for(;;)
  {
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    osDelay(500);
  }
  /* USER CODE END LED_task_init */
}

/* USER CODE BEGIN Header_PID_task_init */
/**
* @brief Function implementing the PID_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_PID_task_init */
void PID_task_init(void *argument)
{
  /* USER CODE BEGIN PID_task_init */
	PID_HandleTypeDef hPID1;
	const float Kp = 1.0;
	const float Ti = 5.0;
	const float Td = 0.0;
	const float Ts = 0.1;

	float _y_set = 0.0f;
	float _y =  0.0f;

	PID_controller_init(&hPID1, Kp, Ti, Td, Ts, true, &htim16, TIM_CHANNEL_1);
	uint32_t tick = osKernelGetTickCount();


  /* Infinite loop */
  for(;;)
  {
	  float U = PID_calc_U(&hPID1, _y, _y_set);
	  PWM_set_output(U, &hPID1);

	  tick+= (100 * osKernelGetTickFreq())/ 1000;

    osDelayUntil(tick);
  }
  /* USER CODE END PID_task_init */
}

/* USER CODE BEGIN Header_Setpoint_task_init */
/**
* @brief Function implementing the Setpoint_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Setpoint_task_init */
void Setpoint_task_init(void *argument)
{
  /* USER CODE BEGIN Setpoint_task_init */

	uint16_t y_max = 300; /// eg. maximum expected DC motor speed in [RPM]

	float setpoint_array[5] = {0.0, 0.5, 1.0, 0.5, 0.8}; /// varying setpoint levels

	uint8_t i = 0;
  /* Infinite loop */
  for(;;)
  {

	setpoint_gl = setpoint_array[i++] * y_max;

	if (i>=5)
	{
		i = 0;
	}
    osDelay(5000); /// Setpoint value changes every 5 seconds

  }
  /* USER CODE END Setpoint_task_init */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */



/* USER CODE END Application */

