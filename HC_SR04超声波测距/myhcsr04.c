/**
 * @file myhcsr04.c
 * @author wmx
 * @brief HC_SR04超声波模块测距，设定的最大测量距离在400mm左右，
 *        想改大到.h文件里改Echo_Max_Delay即可，应该能用来做串级
 *        PID，配合OLED食用更佳 :)
 * @version 0.1
 * @date 2025-07-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "myhcsr04.h"
#include "main.h"
#include "tim.h"
#include "OLED.h"

uint8_t Trig_State;//触发脉冲的状态0表示不触发脉冲，1表示触发,2表示触发完毕
uint8_t Echo_State;//接受回声的状态，0可以触发上升沿得输入捕获，1触发下降沿输入捕获，2表示接收完毕
long unsigned int Trig_Lock = 0;//控制是否可以触发脉冲，可触发脉冲时为0，
                                //触发到接收到回声波前或达到最大等却时间前为ARR到达数，
                                //此后即使调用触发函数也无法产生脉冲
                                //同时也兼用于统计ARR清零数用于计时
float Distance_mm;//测得的距离，单位为毫米，超出最远距离直接拉高到999
float Time_ms;//计算的时间，超时时无意义

int rcc1,rcc2;//获取输入捕获出发时的比较值

/**
 * @brief 使能输入捕获和定时器中断
 * 
 */
void HCSR04_IT_Start()
{
    HAL_TIM_IC_Start_IT(&HCSR04_IC_Tim,HCSR04_IC_Channel);
    HAL_TIM_Base_Start_IT(&HCSR04_IC_Tim);
}

/**
 * @brief 在Trig_Lock为0时，指示定时器发送1ms的脉冲信号
 * 
 */
void HCSR04_Triger()
{
    if(Trig_Lock==0)
        Trig_State = 1;
}

/**
 * @brief 定时器中断回调函数，用来精确地计时和发送脉冲
 * 
 * @param htim 
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==&HCSR04_IC_Tim)
    {
        if(Trig_State == 1)
        {
            HAL_GPIO_WritePin(Trig_Port,Trig_Pin,1);
            Trig_Lock = 1;
            Trig_State = 2;
            Echo_State = 0;
        }
        else if(Trig_State == 2)
        {
            HAL_GPIO_WritePin(Trig_Port,Trig_Pin,0);
            Trig_State = 0;
        }
        
        if(Trig_Lock>0&&Trig_Lock<=Echo_Max_Delay)
        {
            Trig_Lock++;
        }
        
    }
}

/**
 * @brief 输入捕获回调函数
 * 
 * @param htim 
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim == &htim2)
    {
        if(Echo_State==0)
        {
            Echo_State = 1;
            Trig_Lock = 1;
            rcc1 = __HAL_TIM_GET_COMPARE(&HCSR04_IC_Tim,HCSR04_IC_Channel);
            __HAL_TIM_SET_CAPTUREPOLARITY(&HCSR04_IC_Tim,HCSR04_IC_Channel,
                                            TIM_CLOCKPOLARITY_FALLING);
        }
        else if(Echo_State==1)
        {
            rcc2 = __HAL_TIM_GET_COMPARE(&HCSR04_IC_Tim,HCSR04_IC_Channel);
            __HAL_TIM_SET_CAPTUREPOLARITY(&HCSR04_IC_Tim,HCSR04_IC_Channel,
                                            TIM_CLOCKPOLARITY_RISING);
            
            if(Trig_Lock<=Echo_Max_Delay)
            {
                Time_ms=((Trig_Lock-1)*1000.0+rcc2-rcc1)/1000.0;
                Distance_mm = Time_ms/2.0*340;
            }   
            else 
            {
                Distance_mm = Max_Distance;
            }
            Trig_Lock = 0;
			Echo_State=2;
            
                
        }
        
    }
}