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
#ifndef __CHASSIS_CALCU_H_
#define __CHASSIS_CALCU_H_

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/
#include "BoardInteract.h"
#include "CommomInc.h"

/* Exported variables --------------------------------------------------------*/
#define AVG_LF     0
#define AVG_RF     1
#define AVG_LB     2
#define AVG_RB     3


class Chassis{
public:
//values

    
//functions
    void MotorSetInit(void);//转向电机和驱动电机初始化
    void updateState(float data1, float data2, float data3, bool isStop);

private:
//values

    typedef enum {
        LEFT = -1,
        RIGHT = 1,
        NOROTATE = 0,
        XTL = 2,
    } Z_LR_dir_t;

    typedef struct {
        float Mech;
        float X_speed;
        float Y_speed;
        float Z_speed;
        float XY_speed;
        float XYZ_Fusion_speed;
        Z_LR_dir_t Z_LR;
        float Z_dir;
        float direction;
        float XTL_XY_dir;
    } AVG_Chassis_type;
    AVG_Chassis_type AVG_Chassis;


//functions
    void Stop(void);
    void Chassis_Control(float data3, bool isStop);
    void Judge_Rotate(AVG_Chassis_type *p, float data3);
    void AVG_Rotate_Only(void);
    float Angle_Proc(int Angle);
    void AVG_Get_Translation_Dir(void);
    void AVG_Get_XY_Speed(void);
    void AVG_Get_XY_Z_IncludedAngle(void);
    void Get_Target_Angle(Motor_t *str);
    void Get_Target_Speed(Motor_t *str);

};

/* Exported function prototypes ----------------------------------------------*/
extern Motor_t SteeringMotor[4];
extern Motor_t DriveMotor[4];
extern Chassis engineer;

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

void ChassisInit(void);
void ChassisUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /* __FILE_H_ */
