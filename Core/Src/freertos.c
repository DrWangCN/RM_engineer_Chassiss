/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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
#include "Communication.h"
#include "Chassis_Calcu.h"
#include "MotorControl.h"
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
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId remoteTaskHandle;
osThreadId imuTaskHandle;
osThreadId refereeTaskHandle;
osThreadId visionRecTaskHandle;
osThreadId visionSendTaskHandle;
osThreadId chassisTaskHandle;
osThreadId motorTaskHandle;
osThreadId BoardInteractTaHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartRemoteTask(void const * argument);
void StartIMUTask(void const * argument);
void StartRefereeTask(void const * argument);
void StartVisionRecTask(void const * argument);
void StartVisionSendTask(void const * argument);
void StartChassis(void const * argument);
void StartMotor(void const * argument);
void StartBoardInteract(void const * argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = &xIdleStack[0];
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
    /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

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
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of remoteTask */
  osThreadDef(remoteTask, StartRemoteTask, osPriorityAboveNormal, 0, 128);
  remoteTaskHandle = osThreadCreate(osThread(remoteTask), NULL);

  /* definition and creation of imuTask */
  osThreadDef(imuTask, StartIMUTask, osPriorityAboveNormal, 0, 128);
  imuTaskHandle = osThreadCreate(osThread(imuTask), NULL);

  /* definition and creation of refereeTask */
  osThreadDef(refereeTask, StartRefereeTask, osPriorityIdle, 0, 256);
  refereeTaskHandle = osThreadCreate(osThread(refereeTask), NULL);

  /* definition and creation of visionRecTask */
  osThreadDef(visionRecTask, StartVisionRecTask, osPriorityAboveNormal, 0, 256);
  visionRecTaskHandle = osThreadCreate(osThread(visionRecTask), NULL);

  /* definition and creation of visionSendTask */
  osThreadDef(visionSendTask, StartVisionSendTask, osPriorityAboveNormal, 0, 256);
  visionSendTaskHandle = osThreadCreate(osThread(visionSendTask), NULL);

  /* definition and creation of chassisTask */
  osThreadDef(chassisTask, StartChassis, osPriorityRealtime, 0, 640);
  chassisTaskHandle = osThreadCreate(osThread(chassisTask), NULL);

  /* definition and creation of motorTask */
  osThreadDef(motorTask, StartMotor, osPriorityRealtime, 0, 1280);
  motorTaskHandle = osThreadCreate(osThread(motorTask), NULL);

  /* definition and creation of BoardInteractTa */
  osThreadDef(BoardInteractTa, StartBoardInteract, osPriorityHigh, 0, 256);
  BoardInteractTaHandle = osThreadCreate(osThread(BoardInteractTa), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartDefaultTask */
    /* Infinite loop */
    for (;;) {
        HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_14);
        osDelay(500);
    }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartRemoteTask */
/**
 * @brief Function implementing the RemoteTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartRemoteTask */
void StartRemoteTask(void const * argument)
{
  /* USER CODE BEGIN StartRemoteTask */
    /* Infinite loop */
    for (;;) {
        RemoteTask();
    }
  /* USER CODE END StartRemoteTask */
}

/* USER CODE BEGIN Header_StartIMUTask */
/**
 * @brief Function implementing the IMUTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartIMUTask */
void StartIMUTask(void const * argument)
{
  /* USER CODE BEGIN StartIMUTask */
    /* Infinite loop */
    for (;;) {
        IMUTask();
    }
  /* USER CODE END StartIMUTask */
}

/* USER CODE BEGIN Header_StartRefereeTask */
/**
 * @brief Function implementing the RefereeTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartRefereeTask */
void StartRefereeTask(void const * argument)
{
  /* USER CODE BEGIN StartRefereeTask */
    /* Infinite loop */
    for (;;) {
        RefereeTask();
    }
  /* USER CODE END StartRefereeTask */
}

/* USER CODE BEGIN Header_StartVisionRecTask */
/**
 * @brief Function implementing the visionRecTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartVisionRecTask */
void StartVisionRecTask(void const * argument)
{
  /* USER CODE BEGIN StartVisionRecTask */
    /* Infinite loop */
    for (;;) {
        VisionRecTask();
    }
  /* USER CODE END StartVisionRecTask */
}

/* USER CODE BEGIN Header_StartVisionSendTask */
/**
 * @brief Function implementing the visionSendTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartVisionSendTask */
void StartVisionSendTask(void const * argument)
{
  /* USER CODE BEGIN StartVisionSendTask */
    /* Infinite loop */
    for (;;) {
        VisionSendTask();
        osDelay(10);
    }
  /* USER CODE END StartVisionSendTask */
}

/* USER CODE BEGIN Header_StartChassis */
/**
* @brief Function implementing the chassisTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartChassis */
void StartChassis(void const * argument)
{
  /* USER CODE BEGIN StartChassis */
  ChassisInit();
  /* Infinite loop */
  for(;;)
  {
    ChassisUpdate();
    osDelay(50);
  }
  /* USER CODE END StartChassis */
}

/* USER CODE BEGIN Header_StartMotor */
/**
* @brief Function implementing the motorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMotor */
void StartMotor(void const * argument)
{
  /* USER CODE BEGIN StartMotor */
  /* Infinite loop */
  for(;;)
  {
    MotorSendData();
    osDelay(1);
  }
  /* USER CODE END StartMotor */
}

/* USER CODE BEGIN Header_StartBoardInteract */
/**
* @brief Function implementing the BoardInteractTa thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartBoardInteract */
void StartBoardInteract(void const * argument)
{
  /* USER CODE BEGIN StartBoardInteract */
  BoardInteractInit();
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartBoardInteract */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
