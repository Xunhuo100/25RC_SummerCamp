#include "main.h"
#include "mypid.h"
#include "mymotor.h"
#include "stdlib.h"
#include "tim.h"
#include "math.h"
#define R 30
#define Pai 3.1415926

extern uint32_t m;

float Pulse_To_OutputRound(int8_t Pulse)
{
	return ((float)Pulse)/13.0f/20.0f;
}

float Pulse_To_OutputDegree(int8_t Pulse)
{
	return ((float)Pulse)/13.0f*360.0f;
}

int8_t TargetDistance_To_Pulse(float TargetDistance)//��λΪmm,������ǰʱ���ת��Ϊ��
{
	return (int8_t)(TargetDistance/R/360.0f*20.0f*13.0f);
}

int8_t TargetDegree_To_Pulse(float TargetDegree)
{
	return (int8_t)(TargetDegree/360.0f*20.0f*13.0f);
}

int8_t TargetRound_To_Pulse(float TargetRound)
{
	return (int8_t)(TargetRound*20.0f*13.0f);
}

void MotorPWMGet(MOTOR* mptr)//
{
//	if((mptr->PWM+PID_Output(&(mptr->MotorPID)))<(mptr->MotorPID.MaxOutput)&&(mptr->PWM+PID_Output(&(mptr->MotorPID))>0))
//		mptr->PWM+=PID_Output(&(mptr->MotorPID));
//	else if((mptr->PWM+PID_Output(&(mptr->MotorPID)))>(mptr->MotorPID.MaxOutput))
//		mptr->PWM=mptr->MotorPID.MaxOutput;
//	else if((mptr->PWM+PID_Output(&(mptr->MotorPID)))<0)
//		mptr->PWM=0;
	if((fabs(mptr->PWM+PID_Output(&(mptr->MotorPID))))<=mptr->MotorPID.MaxOutput)
		mptr->PWM+=PID_Output(&(mptr->MotorPID));
	else if(mptr->PWM+PID_Output(&(mptr->MotorPID))>mptr->MotorPID.MaxOutput)
		mptr->PWM=mptr->MotorPID.MaxOutput;
	else if(mptr->PWM+PID_Output(&(mptr->MotorPID))<-mptr->MotorPID.MaxOutput)
		mptr->PWM=-mptr->MotorPID.MaxOutput;
}

void MotorSpeedSet(MOTOR* mptr,int SpeedPulse)
{
	if(abs(SpeedPulse)<=20)
		mptr->MotorPID.Target=SpeedPulse;
	else if(SpeedPulse<-20)
		mptr->MotorPID.Target=-20;
	else if(SpeedPulse>20)
		mptr->MotorPID.Target=20;
}

void MotorPWMOutput(MOTOR* mptr)
{
	MotorPWMGet(mptr);
	if (mptr->PWM>0)	
	{
		HAL_GPIO_WritePin(mptr->In1_GPIO_Port,mptr->In1_GPIO_Pin,0);
		HAL_GPIO_WritePin(mptr->In2_GPIO_Port,mptr->In2_GPIO_Pin,1);
	}
	else if(mptr->PWM==0)
	{
		HAL_GPIO_WritePin(mptr->In1_GPIO_Port,mptr->In1_GPIO_Pin,1);
		HAL_GPIO_WritePin(mptr->In2_GPIO_Port,mptr->In2_GPIO_Pin,1);
	}
	else if(mptr->PWM<0)
	{
		HAL_GPIO_WritePin(mptr->In1_GPIO_Port,mptr->In1_GPIO_Pin,1);
		HAL_GPIO_WritePin(mptr->In2_GPIO_Port,mptr->In2_GPIO_Pin,0);
	}
	__HAL_TIM_SET_COMPARE(&htim4,mptr->TimChannel,abs((int)mptr->PWM));
}