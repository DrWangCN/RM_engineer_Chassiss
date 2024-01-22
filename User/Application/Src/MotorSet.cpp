#include "MotorSet.h"

void Motor_t::normalCalc(void){
    Position.NormalCalc();
    Speed.ref = Position.output;
    Speed.NormalCalc();
    output = Speed.output;
}   //好像没用到
