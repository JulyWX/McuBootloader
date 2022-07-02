/*
 * @Author:July
 * @Date: 2022-06-20 15:23:52
 * @LastEditors: July
 * @LastEditTime: 2022-07-03 01:50:41
 * @FilePath: \McuBootloader\public_lib\queue.c
 * @Description: 
 */

#include "queue.h"

/**
 * @description: 
 * @param {QueueType*} queue：  队列变量
 * @param {void*} data_buf：    数据数组变量，用于存储入队列的数据
 * @param {u32} data_buf_size： 数据数组大小，用于计算队列数据单元个数
 * @param {u32} data_size：     设置入队列数据的大小，也代表队列里面每个数据单元的大小
 * @return {*}
 */
bool Queue_Init(QueueType* queue, void* data_buf, u32 data_buf_size, u32 data_size)
{
    if(queue == NULL || data_buf == NULL || data_size == 0 || data_buf_size/data_size < 2)
    {
		queue->state = Q_INIT_FAIL;
        return false;
    }
    
    queue->head = 0;
    queue->end = queue->head;
    queue->size = data_size;
    queue->count = data_buf_size/data_size;
    queue->buf = (u8*)data_buf;
	queue->state = Q_INIT_SUCCES;
    
    return true;
}

/**
 * @description: 
 * @param {QueueType*} queue：队列变量
 * @param {void*} pdata： 入队数据变量
 * @param {  } queue
 * @return {*} 
 */
bool InQueue(QueueType* queue, void* pdata)
{
	if(queue->state == Q_INIT_FAIL || pdata == NULL)
		return false;
		
    if(queue->head == queue->end)
    {
		queue->state = Q_FULL;
        return false;
    }
    
    memcpy(&(queue->buf[queue->end]), pdata, queue->size);
    
    queue->end = (queue->end + 1) % queue->count;
	
	queue->state = Q_IN;
    return true;
}

/**
 * @description: 
 * @param {QueueType*} queue： 队列变量
 * @param {void*} pdata： 获取队列数据的变量
 * @return {*}
 */
bool GetQueueHead(QueueType* queue, void* pdata)
{
	if(queue->state == Q_INIT_FAIL)
		return false;
		
    if(queue->head == queue->end)
    {
		queue->state = Q_EMPTY;
        return false;
    }
    
    if(pdata != NULL)
    {
        memcpy(pdata, &(queue->buf[queue->head]), queue->size);
    }
    
	queue->state = Q_OUT;
    return true;
}


/**
 * @description: 
 * @param {QueueType*} queue
 * @param {	 } queue
 * @return {*}
 */
bool OutQueue(QueueType* queue)
{
	if(queue->state == Q_INIT_FAIL)
		return false;
		
    if(queue->head == queue->end)
    {
        return false;
    }
    
    memset(&(queue->buf[queue->head]), 0, queue->size);//GetQueueHead???????
	
	  queue->head = (queue->head + 1) % queue->count;
    
    return true;
}

/**
 * @description: 
 * @param {QueueType*} queue
 * @return {*}
 */
u8 GetQueueDataNum(QueueType* queue)
{
	return abs(queue->head - queue->end);
}
