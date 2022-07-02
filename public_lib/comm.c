#include "comm.h"  

CommType CommData;


uint16_t PackData(uint8_t *data, uint8_t functionCode, uint16_t data_len)
{
     ProtocolHeadType tx_head = {DEVICE_ID, functionCode, data_len}; 
     uint8_t checksum = 0;
     uint16_t i = 0;
     uint16_t tx_len = 0;
     
     CommData.TxBuff[0] = FRAME_HEAD1;
     CommData.TxBuff[1] = FRAME_HEAD2;

     memcpy(&CommData.TxBuff[2], (uint8_t *)&tx_head, PROTOCOL_HEAD_SIZE);

     tx_len = 2 + PROTOCOL_HEAD_SIZE;

     for(i=0; i<data_len; i++){
          CommData.TxBuff[2 + PROTOCOL_HEAD_SIZE + i] = data[i];
          checksum += data[i];
          tx_len++;
     }

     CommData.TxBuff[tx_len] = checksum;
     CommData.TxBuff[tx_len + 1] = FRAME_END1;
     CommData.TxBuff[tx_len + 2] = FRAME_END2;
     tx_len += 3;

     return ((tx_len==(data_len + PROTOCOL_HEAD_SIZE + 5)) ? tx_len : 0);
}

bool UnpackData(uint8_t data)
{
     static uint16_t data_len = 0;
     static uint8_t step = 1, checksum = 0;
     static uint8_t rx_buff[RX_SIZE] = {0};
     ProtocolHeadType rx_head = {0};
     uint8_t last_data;
     uint8_t unpack_result = 0;


     if(data==FRAME_HEAD2 && last_data==FRAME_HEAD1){
          step = 2;
          data_len = 0;
          memset(rx_buff, 0, sizeof(rx_buff));
     }

     if(step == 2){
          rx_buff[data_len] = data;
          data_len++;

          if(data_len == PROTOCOL_HEAD_SIZE){
              memcpy((uint8_t *)&rx_head, rx_buff, PROTOCOL_HEAD_SIZE);
          }

          if((data_len >= PROTOCOL_HEAD_SIZE) && (data_len <= (rx_head.len + PROTOCOL_HEAD_SIZE))){
               checksum += data;
               if((checksum == data) && ((data_len - PROTOCOL_HEAD_SIZE) == rx_head.len)){
                    unpack_result = 1;
                    memcpy(CommData.RxBuff, rx_buff, data_len);
               }
          }else if(data_len > (rx_head.len + PROTOCOL_HEAD_SIZE) || (data_len > (PROTOCOL_HEAD_SIZE + RX_SIZE))){
               unpack_result = 0;
               step = 0;
          }
     }

     last_data = data;

     return unpack_result;

}




