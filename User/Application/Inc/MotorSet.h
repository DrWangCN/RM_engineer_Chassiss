/**
 *******************************************************************************
 * @file      : PID.h
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
#ifndef __MOTORSET_H_
#define __MOTORSET_H_

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/
#include "Dji_Motor.h"
#include "PID.h"
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

//四个轮正向时的码盘值（需要改）
#define LF_F_MidAngle     120.0f//329
#define RF_F_MidAngle     119.0f
#define LB_F_MidAngle     239.0f//297
#define RB_F_MidAngle     59.0f

/* Exported types ------------------------------------------------------------*/
class Motor_t{
public:
    PID_Def Speed;
    PID_Def Position;
    PID_Def Current;

    float output;
    int Z_dir;
    float XY_dir;
    float XY_Z_ErrAngle;
    float XYZ_Angle;
    float Last_XYZ_Angle;
    float Target_speed;
    int cnt = 0;
    float Mid_Angle[4] = {LF_F_MidAngle, RF_F_MidAngle, LB_F_MidAngle, RB_F_MidAngle};

    Dji_Motor receive;

    enum Motor_Type{
        M3508 = 1,
        M2006 = 2,
        M6020 = 3
    } motorType;

    void normalCalc(void);
private:

};
/* Exported variables --------------------------------------------------------*/
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
