/*
 * @Author: July
 * @Date: 2022-06-20 15:23:52
 * @LastEditors: July
 * @LastEditTime: 2022-07-03 01:52:48
 * @FilePath: \McuBootloader\public_lib\queue.h
 * @Description: 
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include  "mcu_lib.h"

/**
 * @description: 队列状态监控
 * @return {*}
 */
typedef enum {
	Q_INIT_FAIL = 0,//队列初始化失败
	Q_INIT_SUCCES,  //队列初始化成功
	Q_IN,      //进队列
	Q_OUT,     //出队列
	Q_FULL,    //满队列
	Q_EMPTY    //空队列
}QueueState_Type;



/**
 * @description: 
 * @return {*}
 */
typedef struct
{
	QueueState_Type state; //最近一次的队列状态
	u8 head;  //队头序号
	u8 end;   //队尾序号
	u16 size; //单个数据的大小
	u16 count; //数据总个数
	u8* buf; //数据数组指针
}QueueType;

bool Queue_Init(QueueType* queue, void* data_buf, u32 data_buf_size, u32 data_size); //队列初始化
bool InQueue(QueueType* queue, void* pdata); //进队列
bool GetQueueHead(QueueType* queue, void* pdata); //获取队列头数据
bool OutQueue(QueueType* queue); //出队列
u8 GetQueueDataNum(QueueType* queue);//获取队里里面的数据个数
#endif
