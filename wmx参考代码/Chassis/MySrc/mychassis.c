#include "main.h"
#include "mypid.h"
#include "mymotor.h"
#include "mychassis.h"

MOTOR motor[4];
extern TIM_HandleTypeDef htim4;

void Chassis_MotorBaseInit()
{
	
	int i;
	PID_Init(&(motor[0].MotorPID),4.69f,0.01f,4.30f);
	PID_Init(&(motor[1].MotorPID),4.69f,0.01f,4.30f);
	PID_Init(&(motor[2].MotorPID),4.69f,0.01f,4.30f);
	PID_Init(&(motor[3].MotorPID),4.69f,0.01f,4.30f);

	for(i=0;i<4;i++){
		PID_MaxOutputSet(&(motor[i].MotorPID),500.0f);
		motor[i].MotorPID.Target=0;
		motor[i].MotorPulse=0;
		motor[i].PWM=0;
	}
	motor[0].In1_GPIO_Port=AIN1_GPIO_Port;
	motor[0].In1_GPIO_Pin=AIN1_Pin;
	motor[0].In2_GPIO_Port=AIN2_GPIO_Port;
	motor[0].In2_GPIO_Pin=AIN2_Pin;
	motor[0].EA_GPIO_Port=E1A_GPIO_Port;
	motor[0].EA_GPIO_Pin=E1A_Pin;
	motor[0].EB_GPIO_Port=E1B_GPIO_Port;
	motor[0].EB_GPIO_Pin=E1B_Pin;
	motor[0].pTim=&htim4;
	motor[0].TimChannel=TIM_CHANNEL_1;
	
	motor[1].In1_GPIO_Port=BIN1_GPIO_Port;
	motor[1].In1_GPIO_Pin=BIN1_Pin;
	motor[1].In2_GPIO_Port=BIN2_GPIO_Port;
	motor[1].In2_GPIO_Pin=BIN2_Pin;
	motor[1].EA_GPIO_Port=E2A_GPIO_Port;
	motor[1].EA_GPIO_Pin=E2A_Pin;
	motor[1].EB_GPIO_Port=E2B_GPIO_Port;
	motor[1].EB_GPIO_Pin=E2B_Pin;
	motor[1].pTim=&htim4;
	motor[1].TimChannel=TIM_CHANNEL_2;

	
	motor[2].In1_GPIO_Port=CIN1_GPIO_Port;
	motor[2].In1_GPIO_Pin=CIN1_Pin;
	motor[2].In2_GPIO_Port=CIN2_GPIO_Port;
	motor[2].In2_GPIO_Pin=CIN2_Pin;
	motor[2].EA_GPIO_Port=E3A_GPIO_Port;
	motor[2].EA_GPIO_Pin=E3A_Pin;
	motor[2].EB_GPIO_Port=E3B_GPIO_Port;
	motor[2].EB_GPIO_Pin=E3B_Pin;
	motor[2].pTim=&htim4;
	motor[2].TimChannel=TIM_CHANNEL_3;
	
	motor[3].In1_GPIO_Port=DIN1_GPIO_Port;
	motor[3].In1_GPIO_Pin=DIN1_Pin;
	motor[3].In2_GPIO_Port=DIN2_GPIO_Port;
	motor[3].In2_GPIO_Pin=DIN2_Pin;
	motor[3].EA_GPIO_Port=E4A_GPIO_Port;
	motor[3].EA_GPIO_Pin=E4A_Pin;
	motor[3].EB_GPIO_Port=E4B_GPIO_Port;
	motor[3].EB_GPIO_Pin=E4B_Pin;
	motor[3].pTim=&htim4;
	motor[3].TimChannel=TIM_CHANNEL_4;
}

void Chassis_MotorPWMEnable()
{
	int i;
	for(i=0;i<4;i++)
		HAL_TIM_PWM_Start(motor[i].pTim, motor[i].TimChannel);
}

void ChassisTest_ForwardMove()
{
	MotorSpeedSet(&(motor[0]),5);
	MotorSpeedSet(&(motor[1]),-5);
	MotorSpeedSet(&(motor[2]),-5);
	MotorSpeedSet(&(motor[3]),5);
}

void ChassisTest_BackwardMove()
{
	MotorSpeedSet(&(motor[0]),-5);
	MotorSpeedSet(&(motor[1]),5);
	MotorSpeedSet(&(motor[2]),5);
	MotorSpeedSet(&(motor[3]),-5);
}

void ChassisTest_LeftMove()
{
	MotorSpeedSet(&(motor[0]),-5);
	MotorSpeedSet(&(motor[1]),-5);
	MotorSpeedSet(&(motor[2]),5);
	MotorSpeedSet(&(motor[3]),5);
}

void ChassisTest_RightMove()
{
	MotorSpeedSet(&(motor[0]),5);
	MotorSpeedSet(&(motor[1]),5);
	MotorSpeedSet(&(motor[2]),-5);
	MotorSpeedSet(&(motor[3]),-5);
}

void ChassisTest_DiagonalMove_lf()
{
	MotorSpeedSet(&(motor[0]),0);
	MotorSpeedSet(&(motor[1]),-5);
	MotorSpeedSet(&(motor[2]),0);
	MotorSpeedSet(&(motor[3]),5);
}

void ChassisTest_DiagonalMove_rb()
{
	MotorSpeedSet(&(motor[0]),0);
	MotorSpeedSet(&(motor[1]),5);
	MotorSpeedSet(&(motor[2]),0);
	MotorSpeedSet(&(motor[3]),-5);
}

void ChassisTest_DiagonalMove_rf()
{

	MotorSpeedSet(&(motor[0]),5);
	MotorSpeedSet(&(motor[1]),0);
	MotorSpeedSet(&(motor[2]),-5);
	MotorSpeedSet(&(motor[3]),0);
}

void ChassisTest_DiagonalMove_lb()
{

	MotorSpeedSet(&(motor[0]),-5);
	MotorSpeedSet(&(motor[1]),0);
	MotorSpeedSet(&(motor[2]),5);
	MotorSpeedSet(&(motor[3]),0);
}

void ChassisTest_Turn_Clockwise()
{
	MotorSpeedSet(&(motor[0]),4);
	MotorSpeedSet(&(motor[1]),-4);
	MotorSpeedSet(&(motor[2]),4);
	MotorSpeedSet(&(motor[3]),-4);
}

void ChassisTest_Turn_Anticlockwise()
{
	MotorSpeedSet(&(motor[0]),-4);
	MotorSpeedSet(&(motor[1]),4);
	MotorSpeedSet(&(motor[2]),-4);
	MotorSpeedSet(&(motor[3]),4);
}
