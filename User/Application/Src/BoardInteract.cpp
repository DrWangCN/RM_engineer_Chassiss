#include "BoardInteract.h"

BoardInteract boardInteract;

void BoardInteract::init(){
    txHeader.DLC = 0x08;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.IDE = CAN_ID_STD;
    txHeader.StdId = 0x312;
}

void BoardInteract::send(uint16_t _data1, uint16_t _data2, uint16_t _data3, uint16_t _data4) {
    sendData[0] = _data1 >> 8;
    sendData[1] = _data1;
    sendData[2] = _data2 >> 8;
    sendData[3] = _data2;
    sendData[4] = _data3 >> 8;
    sendData[5] = _data3;
    sendData[6] = _data4 >> 8;
    sendData[7] = _data4;

    uint32_t send_mail_box;
    HAL_CAN_AddTxMessage(&hcan1, &txHeader, sendData, &send_mail_box);
}

void BoardInteract::receive(uint8_t RawData[]) {
    frontRear = RawData[0] << 8 | RawData[1];
    leftRight = RawData[2] << 8 | RawData[3];
    clockWise = RawData[4] << 8 | RawData[5];
    switch (RawData[6]) {
        case 0b11111111:
            direction = Back;
            break;
        case 0b00001111:
            direction = Lateral;
            break;
        default:
            direction = Front;
    }
    if (RawData[7] >> 4) {
        operateMode = Move;
    } else {
        operateMode = Stop;
    }
    if (RawData[7] & 0b1111) {
        isSuck = true;
    } else {
        isSuck = false;
    }
}

void BoardInteractInit(void)
{
    boardInteract.init();
}

void BoardInteractSend(void)
{
    boardInteract.send(Remote.Pack.ch0, Remote.Pack.ch1,
                        Remote.Pack.ch2, Remote.Pack.ch3);
}
