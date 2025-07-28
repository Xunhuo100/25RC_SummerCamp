#ifndef __MYMOTOR_H
#define __MYMOTOR_H

#include "mypid.h"

typedef struct motor
{
	TIM_HandleTypeDef* pTim;
	uint32_t TimChannel;
	
	GPIO_TypeDef* In1_GPIO_Port;
	uint16_t In1_GPIO_Pin;
	
	GPIO_TypeDef* In2_GPIO_Port;
	uint16_t In2_GPIO_Pin;
	
	GPIO_TypeDef* EA_GPIO_Port;
	uint16_t EA_GPIO_Pin;
	
	GPIO_TypeDef* EB_GPIO_Port;
	uint16_t EB_GPIO_Pin;
	
	int8_t MotorPulse; 
	
	PID MotorPID;
	
	float PWM;
	
} MOTOR; 

float Pulse_To_OutputRound(int8_t Pulse);
float Pulse_To_OutputDegree(int8_t Pulse);
int8_t TargetDistance_To_Pulse(float TargetDistance);
int8_t TargetDegree_To_Pulse(float TargetDegree);
int8_t TargetRound_To_Pulse(float TargetRound);

void MotorPWMGet(MOTOR* mptr);
void MotorPWMOutput(MOTOR* mptr);
void MotorSpeedSet(MOTOR* mptr,int SpeedPulse);

#endif
