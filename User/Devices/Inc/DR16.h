/**
 *******************************************************************************
 * @file      : DR16.h
 * @brief     :
 * @history   :
 *  Version     Date            Author          Note
 *  V0.9.0      2023-05-03    Jerry Gong        1. <note>
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2023 Reborn Team, USTB.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DR16_H_
#define __DR16_H_

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/
#include <drv_uart.h>

/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
struct DR16_DatePack_t {
    int16_t ch0;
    int16_t ch1;
    int16_t ch2;
    int16_t ch3;
    uint8_t s1;
    uint8_t s2;
    int16_t mouse_x;
    int16_t mouse_y;
    int16_t mouse_z;
    uint8_t press_l;
    uint8_t press_r;
    uint16_t key;
};
class DBUS_Def
{
   public:
    DR16_DatePack_t Pack;
    void SbusToRc(uint8_t *pData);

   private:
};

/* Exported variables --------------------------------------------------------*/
extern DBUS_Def Remote;
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
