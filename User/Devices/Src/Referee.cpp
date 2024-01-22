/**
 *******************************************************************************
 * @file      : Referee.cpp
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
#include <Referee.h>
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
Referee_Def Referee;
/* Private function prototypes -----------------------------------------------*/

/**
 * @brief
 * @param       pData:
 *   @arg       None
 * @retval      None
 * @note        None
 */
void Referee_Def::DataPack(uint8_t* pData)
{
    uint16_t judge_length;  // 统计一帧数据长度
    //	CmdID = 0; //数据命令码解析
    // 空数据包，则不作任何处理
    if (pData == NULL)
        return;

    // 写入帧头数据(5-byte),用于判断是否开始存储裁判数据
    memcpy(&FrameHeader, pData, LEN_HEADER);

    // 判断帧头数据(0)是否为0xA5
    if (pData[SOF] == JUDGE_FRAME_HEADER) {
        // 帧头CRC8校验
        if (Verify_CRC8_Check_Sum(pData, LEN_HEADER) == TRUE) {
            // 统计一帧数据长度(byte),用于CR16校验
            judge_length = pData[DATA_LENGTH] + LEN_HEADER + LEN_CMDID + LEN_TAIL;
            // 帧尾CRC16校验
            if (Verify_CRC16_Check_Sum(pData, judge_length) == TRUE) {
                // 2个8位拼成16位int
                CmdID = (pData[6] << 8 | pData[5]);
                // 解析数据命令码,将数据拷贝到相应结构体中(注意拷贝数据的长度)
                // 第8个字节开始才是数据 data=7
                switch (CmdID) {
                    case ID_game_state:  // 0x0001
                        memcpy(&GameState, (pData + DATA), LEN_game_state);
                        break;

                    case ID_game_result:  // 0x0002
                        memcpy(&GameResult, (pData + DATA), LEN_game_result);
                        break;

                    case ID_game_robot_survivors:  // 0x0003
                        memcpy(&GameRobotHP, (pData + DATA), LEN_game_robot_HP);
                        break;

                    case ID_event_data:  // 0x0101
                        memcpy(&EventData, (pData + DATA), LEN_event_data);
                        break;

                    case ID_supply_projectile_action:  // 0x0102
                        memcpy(&SupplyProjectileAction, (pData + DATA), LEN_supply_projectile_action);
                        break;

                    case ID_game_robot_state:  // 0x0201
                        memcpy(&GameRobotStat, (pData + DATA), LEN_game_robot_state);
                        break;
                    case ID_power_heat_data:  // 0x0202
                        memcpy(&PowerHeatData, (pData + DATA), LEN_power_heat_data);
                        break;

                    case ID_game_robot_pos:  // 0x0203
                        memcpy(&GameRobotPos, (pData + DATA), LEN_game_robot_pos);
                        break;

                    case ID_buff_musk:  // 0x0204
                        memcpy(&BuffMusk, (pData + DATA), LEN_buff_musk);
                        break;

                    case ID_aerial_robot_energy:  // 0x0205
                        memcpy(&AerialRobotEnergy, (pData + DATA), LEN_aerial_robot_energy);
                        break;

                    case ID_robot_hurt:  // 0x0206
                        memcpy(&RobotHurt, (pData + DATA), LEN_robot_hurt);
                        break;

                    case ID_shoot_data:  // 0x0207
                        memcpy(&ShootData, (pData + DATA), LEN_shoot_data);
                        // JUDGE_ShootNumCount();//发弹量统计
                        break;

                    case ID_command_data:  // 0x0304
                        memcpy(&CommaData, (pData + DATA), LEN_command_data);
                        break;
                }
            }
        }
        // 首地址加帧长度,指向CRC16下一字节,用来判断是否为0xA5,从而判断一个数据包是否有多帧数据
        if (*(pData + sizeof(xFrameHeader) + LEN_CMDID + FrameHeader.DataLength + LEN_TAIL) == 0xA5) {
            // 如果一个数据包出现了多帧数据,则再次调用解析函数,直到所有数据包解析完毕
            DataPack(pData + sizeof(xFrameHeader) + LEN_CMDID + FrameHeader.DataLength + LEN_TAIL);
        }
    }
}
