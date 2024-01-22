/**
 *******************************************************************************
 * @file      : Communication.cpp
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
#include "Communication.h"
#include "Chassis_Calcu.h"
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
uint32_t DR16CallBack();
uint32_t IMUCallBack();
uint32_t VisionCallBack();
uint32_t RefereeCallBack();
void UserCAN1DataUpdate(CANx_Message* CANx_RxMsg);
void UserCAN2DataUpdate(CANx_Message* CANx_RxMsg);

/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
 * @brief
 *   @arg       None
 * @retval      None
 * @note        None
 */
void UserSystemCommInit()
{
    CANInit(&hcan1, UserCAN1RxCpltCallBack);
    CANInit(&hcan2, UserCAN2RxCpltCallBack);
    UserUARTReceiveIT(&huart1, 18, DR16CallBack);
    UserUARTReceiveIT(&huart6, 29, IMUCallBack);
    UserUARTReceiveIT(&huart7, 25, VisionCallBack);
    UserUARTReceiveIT(&huart8, 256, RefereeCallBack);
}

/**
 * @brief       CAN1 call back function
 * @param       CAN_RxBuffer:
 *   @arg       None
 * @retval      None
 * @note        None
 */
void UserCAN1RxCpltCallBack(CAN_RxBuffer* CAN_RxBuffer)
{
    static CANx_Message CAN1_RxMessage;
    CAN1_RxMessage.ID = CAN_RxBuffer->rx_header.StdId;
    CAN1_RxMessage.DLC = CAN_RxBuffer->rx_header.DLC;
    memcpy(CAN1_RxMessage.Data, CAN_RxBuffer->rx_data, CAN1_RxMessage.DLC);

    UserCAN1DataUpdate(&CAN1_RxMessage);
}

/**
 * @brief       CAN2 call back function
 * @param       CAN_RxBuffer:
 *   @arg       None
 * @retval      None
 * @note        None
 */
void UserCAN2RxCpltCallBack(CAN_RxBuffer* CAN_RxBuffer)
{
    static CANx_Message CAN2_RxMessage;
    CAN2_RxMessage.ID = CAN_RxBuffer->rx_header.StdId;
    CAN2_RxMessage.DLC = CAN_RxBuffer->rx_header.DLC;
    memcpy(CAN2_RxMessage.Data, CAN_RxBuffer->rx_data, CAN2_RxMessage.DLC);

    UserCAN2DataUpdate(&CAN2_RxMessage);
}

/**
 * @brief
 * @param       CANx_RxMsg:
 *   @arg       None
 * @retval      None
 * @note        None
 */
void UserCAN1DataUpdate(CANx_Message* CANx_RxMsg)
{
    if(CANx_RxMsg->ID == 0x101)
    {
        boardInteract.receive(CANx_RxMsg->Data);
    }

    switch (CANx_RxMsg->ID - 0x201)
    {
    case 0:
        DriveMotor[AVG_LF].receive.Update(CANx_RxMsg->Data);break;
    case 1:
        DriveMotor[AVG_RF].receive.Update(CANx_RxMsg->Data);break;
    case 2:
        DriveMotor[AVG_LB].receive.Update(CANx_RxMsg->Data);break;
    case 3:
        DriveMotor[AVG_RB].receive.Update(CANx_RxMsg->Data);break;
    default:
        break;
    }
}

/**
 * @brief
 * @param       CANx_RxMsg:
 *   @arg       None
 * @retval      None
 * @note        None
 */
void UserCAN2DataUpdate(CANx_Message* CANx_RxMsg)
{
    if(CANx_RxMsg->ID == 0x312)
    {
        boardInteract.receive(CANx_RxMsg->Data);
    }

    switch (CANx_RxMsg->ID - 0x205)
    {
    case 0:
        SteeringMotor[AVG_LF].receive.Update(CANx_RxMsg->Data);break;
    case 1:
        SteeringMotor[AVG_RF].receive.Update(CANx_RxMsg->Data);break;
    case 2:
        SteeringMotor[AVG_LB].receive.Update(CANx_RxMsg->Data);break;
    case 3:
        SteeringMotor[AVG_RB].receive.Update(CANx_RxMsg->Data);break;
    default:
        break;
    }
    
}

/**
 * @brief       Remote call back function
 *   @arg       None
 * @retval      None
 * @note        None
 */
uint32_t DR16CallBack()
{
    if (remoteTaskHandle != NULL) {
        osSignalSet(remoteTaskHandle, (uint32_t)UART_Instance[0].rx_buffer);
    }
    return 0;
}

/**
 * @brief       IMU call back function
 *   @arg       None
 * @retval      None
 * @note        None
 */
uint32_t IMUCallBack()
{
    if (imuTaskHandle != NULL) {
        osSignalSet(imuTaskHandle, (uint32_t)UART_Instance[1].rx_buffer);
    }
    return 0;
}

/**
 * @brief       Vision call back function
 *   @arg       None
 * @retval      None
 * @note        None
 */
uint32_t VisionCallBack()
{
    if (visionRecTaskHandle != NULL) {
        osSignalSet(visionRecTaskHandle, (uint32_t)UART_Instance[2].rx_buffer);
    }
    return 0;
}

/**
 * @brief       Referee call back function
 *   @arg       None
 * @retval      None
 * @note        None
 */
uint32_t RefereeCallBack()
{
    if (refereeTaskHandle != NULL) {
        osSignalSet(refereeTaskHandle, (uint32_t)UART_Instance[3].rx_buffer);
    }
    return 0;
}

/**
 * @brief       Remote receive function
 *   @arg       None
 * @retval      None
 * @note        None
 */
void RemoteTask()
{
    static uint8_t* Dbus_Buffer;
    static TickType_t xLastWakeTime_t = pdMS_TO_TICKS(10);

    if (xTaskNotifyWait(0x00000000, 0xFFFFFFFF, (uint32_t*)&Dbus_Buffer, xLastWakeTime_t) == pdTRUE) {
        Remote.SbusToRc(Dbus_Buffer);
    }
}

/**
 * @brief       IMU receive task function
 *   @arg       None
 * @retval      None
 * @note        None
 */
void IMUTask()
{
    static uint8_t* IMU_Buffer;
    static TickType_t xLastWakeTime_t = pdMS_TO_TICKS(10);

    if (xTaskNotifyWait(0x00000000, 0xFFFFFFFF, (uint32_t*)&IMU_Buffer, xLastWakeTime_t) == pdTRUE) {
        IMU.DataPack(IMU_Buffer);
    }
}

/**
 * @brief       Referee receive task function
 *   @arg       None
 * @retval      None
 * @note        None
 */
void RefereeTask()
{
    static uint8_t* Referee_Buffer;
    static TickType_t xLastWakeTime_t = pdMS_TO_TICKS(10);

    if (xTaskNotifyWait(0x00000000, 0xFFFFFFFF, (uint32_t*)&Referee_Buffer, xLastWakeTime_t) == pdTRUE) {
        Referee.DataPack(Referee_Buffer);
    }
}

/**
 * @brief       Vision receive task function
 *   @arg       None
 * @retval      None
 * @note        None
 */
void VisionRecTask()
{
    static uint8_t* Vision_Buffer;
    static TickType_t xLastWakeTime_t = pdMS_TO_TICKS(10);

    if (xTaskNotifyWait(0x00000000, 0xFFFFFFFF, (uint32_t*)&Vision_Buffer, xLastWakeTime_t) == pdTRUE) {
        Vision.DataPack(Vision_Buffer);
    }
}

void VisionSendTask()
{
    static uint8_t Tx[13];
    static int SendAngle[2];

    SendAngle[0] = (int)((IMU.Euler[0] + 180) * 10);  // pitch
    SendAngle[1] = (int)((IMU.Yaw + 180) * 10);       // yaw

    Tx[0] = 'R';
    Tx[1] = 'M';
    if (Remote.Pack.s1 == 2 && Remote.Pack.s2 == 2) {
        Tx[2] = 'O';
    } else {
        Tx[2] = 'S';
    }

    Tx[3] = 'H';
    Tx[4] = SendAngle[1] / 1000 + 48;
    Tx[5] = SendAngle[1] % 1000 / 100 + 48;
    Tx[6] = SendAngle[1] % 100 / 10 + 48;
    Tx[7] = SendAngle[1] % 10 + 48;

    Tx[8] = SendAngle[0] / 1000 + 48;
    Tx[9] = SendAngle[0] % 1000 / 100 + 48;
    Tx[10] = SendAngle[0] % 100 / 10 + 48;
    Tx[11] = SendAngle[0] % 10 + 48;
    Tx[12] = '0';

    UserUARTSendData(&huart7, Tx, 13, UART_TRANSMIT_IT);
}