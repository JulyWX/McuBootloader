#ifndef _COMM_H_
#define _COMM_H_

#include "mcu_lib.h"

#define FRAME_HEAD1 0xA5
#define FRAME_HEAD2 0x5A
#define FRAME_END1  0xB5
#define FRAME_END2  0x5B

#define TX_SIZE 256
#define RX_SIZE 256

#define DEVICE_ID 0xAA

typedef struct{
    uint8_t TxBuff[TX_SIZE];
    uint8_t RxBuff[TX_SIZE];
}CommType;

typedef struct{
    uint8_t deviceAddress;
    uint8_t functionCode;
    uint32_t len;
}ProtocolHeadType;



#define PROTOCOL_HEAD_SIZE  sizeof(ProtocolHeadType)

#endif
