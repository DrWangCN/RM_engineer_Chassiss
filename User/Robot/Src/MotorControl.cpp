#include "MotorControl.h"

void MotorCalcu(int num)
{
    // 转向电机PID计算（位置速度双环控制）
    SteeringMotor[num].Position.fdb = SteeringMotor[num].receive.angle_real;
    SteeringMotor[num].Speed.fdb = SteeringMotor[num].receive.speed_rpm;
    SteeringMotor[num].Position.ref = SteeringMotor[num].XYZ_Angle - 360 * SteeringMotor[num].cnt + SteeringMotor->Mid_Angle[num];
    SteeringMotor[num].Position.NormalCalc();
    SteeringMotor[num].Speed.ref = SteeringMotor[num].Position.output;
    SteeringMotor[num].Speed.NormalCalc();

    // 驱动电机PID计算（速度电流双环控制）
    switch (num)
    {
    case AVG_LF: case AVG_LB:
        DriveMotor[num].Speed.ref = DriveMotor[num].Target_speed * 1.0f;
        DriveMotor[num].Speed.fdb = DriveMotor[num].receive.speed_rpm;
        DriveMotor[num].Speed.NormalCalc();
        DriveMotor[num].Current.ref = DriveMotor[num].Speed.output;
        DriveMotor[num].Current.fdb = DriveMotor->receive.torque_current;
        DriveMotor[num].Current.NormalCalc();
        break;
    
    case AVG_RB: case AVG_RF:
        DriveMotor[num].Speed.ref = -DriveMotor[num].Target_speed * 1.0f;
        DriveMotor[num].Speed.fdb = DriveMotor[num].receive.speed_rpm;
        DriveMotor[num].Speed.NormalCalc();
        DriveMotor[num].Current.ref = DriveMotor[num].Speed.output;
        DriveMotor[num].Current.fdb = DriveMotor->receive.torque_current;
        DriveMotor[num].Current.NormalCalc();
        break;
    
    default:
        break;
    }
}

void MotorSendData(void)
{
    MotorCalcu(AVG_LF);
    MotorCalcu(AVG_RF);
    MotorCalcu(AVG_LB);
    MotorCalcu(AVG_RB);
    CANx_PackProcess_Data(&hcan2, 0x1FF, 0x08, SteeringMotor[AVG_LF].Speed.output, 
                        SteeringMotor[AVG_RF].Speed.output, 
                        SteeringMotor[AVG_LB].Speed.output, 
                        SteeringMotor[AVG_RB].Speed.output);
                        //转向电机控制

    CANx_PackProcess_Data(&hcan1, 0x200, 0x08, DriveMotor[AVG_LF].Current.output, 
                        DriveMotor[AVG_RF].Current.output, 
                        DriveMotor[AVG_LB].Current.output, 
                        DriveMotor[AVG_RB].Current.output);   
                        //驱动电机控制
}
