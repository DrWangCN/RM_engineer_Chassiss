/**
 *******************************************************************************
 * @file      : PC_Vision.h
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
#ifndef __PC_VISION_H_
#define __PC_VISION_H_

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/
#include <drv_uart.h>
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
class Vision_Def
{
   public:
    float Yaw_Angle;
    float Pitch_Angle;
    float Distance;

    void DataPack(uint8_t *pData);

   private:
};

/* Exported variables --------------------------------------------------------*/
extern Vision_Def Vision;
/* Exported function prototypes ----------------------------------------------*/

#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __FILE_H_ */
