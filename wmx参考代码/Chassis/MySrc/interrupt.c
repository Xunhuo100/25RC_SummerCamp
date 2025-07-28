#include "main.h"
#include "mypid.h"
#include "mymotor.h"
#include "mychassis.h"
#include "usart.h"
#include "tim.h"
#include "myuart.h"

extern MOTOR motor[4];
extern char command;
int LED_Loading;
int8_t SpeedPulseInfo[4]={0,0,0,0}; 
int8_t TransInfo[4]={0,0,0,0};
int InterruptCount;
uint8_t rxdatas[5];
extern uint8_t 	MotorChoice;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	int i=0;
	for(i=0;i<4;i++)
	{
		if(GPIO_Pin==motor[i].EA_GPIO_Pin)
		{
			if(HAL_GPIO_ReadPin(motor[i].EB_GPIO_Port,motor[i].EB_GPIO_Pin)==1)
				motor[i].MotorPulse--;
			else
				motor[i].MotorPulse++;
		}
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1) 
	{
		//HAL_UART_Receive_IT(huart,rxdatas,5);
		if(rxdatas[0]==1)//1为调节指定电机目标转速，2为调节指定电机PID参数，3为指定运动模式
			//HAL_UART_Transmit(&huart1,(uint8_t*)"Receive 1",sizeof("Receive 1"),HAL_MAX_DELAY);
			Command_RenewTarget(rxdatas[1],rxdatas[2],rxdatas[3]);
		if(rxdatas[0]==2){
			//HAL_UART_Transmit(&huart1,(uint8_t*)"Receive 2",sizeof("Receive 2"),HAL_MAX_DELAY);
			HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
			Command_RenewPiD(rxdatas[1],rxdatas[2],rxdatas[3],rxdatas[4]);}
		if (rxdatas[0]==3)
			//HAL_UART_Transmit(&huart1,(uint8_t*)"Receive 3",sizeof("Receive 3"),HAL_MAX_DELAY);
			Command_RenewChassisMode();
		HAL_UART_Receive_IT(&huart1,rxdatas,5);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim4)
	{
		if(InterruptCount<10)
		{
			InterruptCount++;
		}
		else
		{	
			int i=0;
			for(i=0;i<4;i++)
			{
				motor[i].MotorPID.Actual=motor[i].MotorPulse;
				motor[i].MotorPulse=0;
				__HAL_TIM_SET_COMPARE(&htim4,motor[i].TimChannel,200);
				MotorPWMOutput(&motor[i]);
				InterruptCount=0;
				TransInfo[i]=motor[i].MotorPID.Actual;
			}	
		}
		if(MotorChoice>0&&MotorChoice<=4)
    	{
     	 	TransInfo[0]=motor[MotorChoice-1].MotorPID.Target;
			TransInfo[1]=motor[MotorChoice-1].MotorPID.Actual;
			HAL_UART_Transmit(&huart3,(uint8_t*)TransInfo,sizeof(TransInfo),HAL_MAX_DELAY);
    	}
		
	}
}
