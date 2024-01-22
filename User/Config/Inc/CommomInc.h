/**
 *******************************************************************************
 * @file      : Com_Inc.h
 * @brief     :
 * @history   :
 *  Version     Date            Author          Note
 *  V0.9.0      yyyy-mm-dd      <author>        1. <note>
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2023 Reborn Team, USTB.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMOMINC_H_
#define __COMMOMINC_H_

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/
#include "DR16.h"
//#include "Dji_Motor.h"
#include "MotorSet.h"
#include "IMU.h"
#include "PC_Vision.h"
//#include "PID.h"
#include "Referee.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/

#endif  // DEBUG

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cmsis_os.h"
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern osThreadId defaultTaskHandle;
extern osThreadId remoteTaskHandle;
extern osThreadId imuTaskHandle;
extern osThreadId refereeTaskHandle;
extern osThreadId visionRecTaskHandle;
extern osThreadId visionSendTaskHandle;

/* Exported function prototypes ----------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __FILE_H_ */
