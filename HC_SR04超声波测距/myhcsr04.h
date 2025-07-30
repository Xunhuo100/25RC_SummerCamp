#ifndef __MYHCSR04_H
#define __MYHCSR04_H

#define Trig_Port GPIOA
#define Trig_Pin GPIO_PIN_1

#define Echo_Port GPIOA
#define Echo_Pin GPIO_PIN_0
#define Echo_Max_Delay 3

#define Max_Time 5
#define Max_Distance 999.0//只是一个大数，无实际意义

#define HCSR04_IC_Tim htim2
#define HCSR04_IC_Channel TIM_CHANNEL_1

void HCSR04_IT_Start();
void HCSR04_Triger();

#endif

