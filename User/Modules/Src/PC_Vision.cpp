/**
 *******************************************************************************
 * @file      : PC_Vision.cpp
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
/* Includes ------------------------------------------------------------------*/
#include <PC_Vision.h>

/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
Vision_Def Vision;
/* Private function prototypes -----------------------------------------------*/

/**
 * @brief
 * @param       *pData:
 *   @arg       None
 * @retval      None
 * @note        None
 */
void Vision_Def::DataPack(uint8_t *pData)
{
    static float Vision_Last[3];

    if (pData[0] == 'R' && pData[1] == 'M') {
        if (pData[2] != 'A' && pData[3] != 'A') {
            Yaw_Angle = (float)(int16_t)(pData[3] << 8 | pData[2]) / 100.0f;
            Pitch_Angle = (float)(int16_t)(pData[5] << 8 | pData[4]) / 100.0f;
            Distance = (float)(int16_t)(pData[6]) * 10.0f;

            Vision_Last[0] = Yaw_Angle;
            Vision_Last[1] = Pitch_Angle;
            Vision_Last[2] = Distance;
        } else {
            Yaw_Angle = 0.0f;
            Pitch_Angle = Vision_Last[1];
            Distance = Vision_Last[2];
        }
    }
}
