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
#ifndef __BOARDINTERACT_H_
#define __BOARDINTERACT_H_

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/
#include "CommomInc.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
class BoardInteract{
public:
    int16_t frontRear = 0, leftRight = 0, clockWise = 0;

     enum OperateMode {
        Stop = 0,
        Move
    } operateMode;

    enum Direction {
        Front = 0,
        Lateral,
        Back
    } direction;

    bool isSuck = false;

    void init();
    void receive(uint8_t RawData[]);
    void send(uint16_t _data1, uint16_t _data2, uint16_t _data3, uint16_t _data4);

private:
    CAN_TxHeaderTypeDef txHeader;
    uint8_t sendData[8];
};

/* Exported variables --------------------------------------------------------*/
extern BoardInteract boardInteract;
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

void BoardInteractInit(void);
void BoardInteractSend(void);


#ifdef __cplusplus
}
#endif

#endif /* __FILE_H_ */
