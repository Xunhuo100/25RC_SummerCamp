#ifndef __MYCAN_H
#define __MYCAN_H
/*
    通过位运算在配置参数的相应位写上相应的值（将选择的值按位或组合起来）
*/
// 滤波器编号
#define CAN_FILTER(x) ((x) << 3)//将x左移3位，即将配置参数的第三位及以后写为x

// 接收队列
#define CAN_FIFO_0 (0 << 2)  //将0左移两位，即将第二位写为0，余下同理
#define CAN_FIFO_1 (1 << 2)

//标准帧或扩展帧
#define CAN_STDID (0 << 1)
#define CAN_EXTID (1 << 1)

// 数据帧或遥控帧
#define CAN_DATA_TYPE (0 << 0)
#define CAN_REMOTE_TYPE (1 << 0)

void CAN_Init(CAN_HandleTypeDef *hcan);
void CAN_Filter_Mask_Config(CAN_HandleTypeDef *hcan, uint8_t Object_Para, uint32_t ID, uint32_t Mask_ID);
uint8_t CAN_Send_Data(CAN_HandleTypeDef *hcan, uint16_t ID, uint8_t *Data, uint16_t Length);
void check(uint8_t state);

#endif
