#include "Chassis_Calcu.h"
#include "cmath"


Motor_t SteeringMotor[4];
Motor_t DriveMotor[4];
Chassis engineer;

void Chassis::MotorSetInit(void) //要改！！！！
{
    for(int i = 0; i<4; i++){
        SteeringMotor[i].motorType = Motor_t::M6020;
        SteeringMotor[i].Position.Set(30.0f, 0.1f, 2.0f, 10000.0f, 20.0f, 2500.0f, 200000.0f);
        SteeringMotor[i].Speed.Set(30.0f, 0.0f, 2.0f, 20000.0f, 2500.0f, 2500.0f, 200000.0f);

        DriveMotor[i].motorType = Motor_t::M3508;
        DriveMotor[i].Speed.Set(20.0f, 0.0f, 0.0f, 15000.0f, 0.0f, 15000.0f, 16384.0f);
        DriveMotor[i].Current.Set(1.0f, 0.0f, 0.5f, 15000.0f, 0.0f, 10000.0f, 16384.0f);
    }
}

void Chassis::updateState(float data1, float data2, float data3, bool isStop)
{

    AVG_Chassis.X_speed = data1;
    AVG_Chassis.Y_speed = data2;
    AVG_Chassis.Z_speed = data3;

    Chassis_Control(data3, isStop);

}

void Chassis::Chassis_Control(float data3, bool isStop)
{
    if(isStop == true) {
        Stop();

    }else if(isStop == false){
        Judge_Rotate(&AVG_Chassis, data3);
        AVG_Rotate_Only();
        AVG_Get_Translation_Dir();
        AVG_Get_XY_Speed();
        AVG_Get_XY_Z_IncludedAngle();

        for(int i = 0; i<4; i++){
            Get_Target_Angle(&SteeringMotor[i]);
            Get_Target_Speed(&DriveMotor[i]);
        }
    }
}

void Chassis::Stop(void)
{
    SteeringMotor[AVG_LF].XYZ_Angle = 0;
    SteeringMotor[AVG_RF].XYZ_Angle = 90;
    SteeringMotor[AVG_LB].XYZ_Angle = -90;
    SteeringMotor[AVG_RB].XYZ_Angle = 0;

    for(int i = 0; i<4; i++){
        DriveMotor[i].Target_speed = 0;
    }
}

void Chassis::Judge_Rotate(AVG_Chassis_type *p, float data3)
{
    float Sensitivity = 20;   
    if (data3 >= Sensitivity) {
        p->Z_LR = RIGHT;
    } else if (data3 <= -Sensitivity) {
        p->Z_LR = LEFT;
    } else {
        p->Z_LR = NOROTATE;
    }
    //待加键盘
}

void Chassis::AVG_Rotate_Only(void) //仅自旋， 这有问题，改改改
{
    if(AVG_Chassis.Z_LR == RIGHT)
    {
        SteeringMotor[AVG_LF].Z_dir = Angle_Proc(+ 1024);
        SteeringMotor[AVG_RF].Z_dir = Angle_Proc(+ 2048 + 1024);
        SteeringMotor[AVG_LB].Z_dir = Angle_Proc(- 1024);
        SteeringMotor[AVG_RB].Z_dir = Angle_Proc(- 2048 - 1024);
    }
    else if(AVG_Chassis.Z_LR == LEFT)
    {
        SteeringMotor[AVG_LF].Z_dir = Angle_Proc(- 2048 - 1024);
        SteeringMotor[AVG_RF].Z_dir = Angle_Proc(- 1024);
        SteeringMotor[AVG_LB].Z_dir = Angle_Proc(+ 2048 + 1024);
        SteeringMotor[AVG_RB].Z_dir = Angle_Proc(+ 1024);
    }
    else if(AVG_Chassis.Z_LR == NOROTATE)
    {
        SteeringMotor[AVG_LF].Z_dir = 0;
        SteeringMotor[AVG_RF].Z_dir = 0;
        SteeringMotor[AVG_LB].Z_dir = 0;
        SteeringMotor[AVG_RB].Z_dir = 0;
    }
}

void Chassis::AVG_Get_Translation_Dir(void)
{
    float res, X, Y;
    X = AVG_Chassis.X_speed;
    Y = AVG_Chassis.Y_speed;
    res = atan2(Y, X) * 180 / 3.1415926;

    SteeringMotor[AVG_LF].XY_dir = res * 4096 / 180;
    SteeringMotor[AVG_RF].XY_dir = res * 4096 / 180;
    SteeringMotor[AVG_LB].XY_dir = res * 4096 / 180;
    SteeringMotor[AVG_RB].XY_dir = res * 4096 / 180;
}



void Chassis::AVG_Get_XY_Speed(void)
{
    AVG_Chassis.XY_speed = 
    sqrt(pow(AVG_Chassis.X_speed, 2) + pow(AVG_Chassis.Y_speed, 2));
}


void Chassis::AVG_Get_XY_Z_IncludedAngle(void)
{
    SteeringMotor[AVG_LF].XY_Z_ErrAngle = Angle_Proc(SteeringMotor[AVG_LF].Z_dir - SteeringMotor[AVG_LF].XY_dir);
    SteeringMotor[AVG_LB].XY_Z_ErrAngle = Angle_Proc(SteeringMotor[AVG_LB].Z_dir - SteeringMotor[AVG_LB].XY_dir);
    SteeringMotor[AVG_RF].XY_Z_ErrAngle = Angle_Proc(SteeringMotor[AVG_RF].Z_dir - SteeringMotor[AVG_RF].XY_dir);
    SteeringMotor[AVG_RB].XY_Z_ErrAngle = Angle_Proc(SteeringMotor[AVG_RB].Z_dir - SteeringMotor[AVG_RB].XY_dir);
}

void Chassis::Get_Target_Angle(Motor_t *str)
{
    float b = fabs(AVG_Chassis.Z_speed) * sin(str->XY_Z_ErrAngle * 3.14f / 4096);
        float a = AVG_Chassis.XY_speed + fabs(AVG_Chassis.Z_speed) * cos(str->XY_Z_ErrAngle * 3.14f / 4096);
        float XY_Z_Angle = atan2(b, a);
        str->Last_XYZ_Angle = str->XYZ_Angle;
        str->XYZ_Angle = str->XY_dir * 180 / 4096 + XY_Z_Angle * 180 / 3.14f;
        if ((str->XYZ_Angle - str->Last_XYZ_Angle) >= 300) {
            str->cnt++;
        } else if ((str->XYZ_Angle - str->Last_XYZ_Angle) <= -300) {
            str->cnt--;
        }
}

void Chassis::Get_Target_Speed(Motor_t *str)
{
    float res, a, b;
    a = AVG_Chassis.XY_speed + fabs(AVG_Chassis.Z_speed) * cos(str->XY_Z_ErrAngle * 3.14f / 4096);
    b = fabs(AVG_Chassis.Z_speed) * sin(str->XY_Z_ErrAngle * 3.14f / 4096);
    res = sqrt(a * a + b * b);
    str->Target_speed = res;
}



float Chassis::Angle_Proc(int Angle)
{
    while (Angle > 4096 || Angle < -4096) {
            if (Angle < -4096)
                Angle += 8192;
            if (Angle > 4096)
                Angle -= 8192;
        }
        return Angle;
}

void ChassisInit(void)
{
    engineer.MotorSetInit();
}

void ChassisUpdate(void)
{
    switch(boardInteract.operateMode){
        
        case BoardInteract::Move:
            engineer.updateState(boardInteract.frontRear * 4.0f, 
                        boardInteract.leftRight * 4.0f, 
                        boardInteract.clockWise * 2.5f, 
                        false);
            break;
        case BoardInteract::Stop:
            engineer.updateState(0, 0, 0, true);break;
        default:break;
    }

}
