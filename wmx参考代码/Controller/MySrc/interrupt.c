#include "main.h"
#include "tim.h"
#include "adc.h"
#include "gpio.h"
#include "func.h"
#include "OLED.h"
#include "usart.h"
#include "stdlib.h"

extern uint32_t ADCValue[3];
extern float Values[4][3];
int InterrputCount;
int motor;
int k;
int Mag;
uint8_t rx_uart2[2];


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim3)
	{
		int i;
		for(i=0;i<3;i++)
		ADCValue[i]=GetADC();
		
		if(ADCValue[0]/1000>=3)
			motor=4;
		else
			motor=ADCValue[0]/1000+1;
		if(ADCValue[1]/1000>=3)
			k=3;
		else
			k=ADCValue[1]/1000;
		for(i=0;i<5;i++)
		{
			if(ADCValue[2]>=4095/5*i&&ADCValue[2]<=4095/5*(i+1))
				Mag=i;
		}
		
		ResetShow(motor,k,Mag);
	}
	if(k>=1&&Mag>0)
	{
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6))
		{
			
			TransValueCommand(motor,k,Mag,0);
			ReceiveValues(motor,k);
			ResetShow(motor,k,Mag);
		}

		else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7))
		{
			TransValueCommand(motor,k,Mag,1);
			ReceiveValues(motor,k);
			ResetShow(motor,k,Mag);
		}
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART2)
	{
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		switch(rx_uart2[0])
		{
			case 'f':
			case 'b':
			case 'l':
			case 'r':
				SetMove(rx_uart2[0]);
				break;
			case '0':
				SetSpeedCommand(motor,rx_uart2[0],rx_uart2[1]);
			default:
				if(abs(rx_uart2[0])<=20&&motor>=0&&motor<=4)
					SetSpeedCommand(motor,rx_uart2[0],rx_uart2[1]);
				break;

		}
		HAL_UART_Receive_IT(&huart2,rx_uart2,2);
	}
}
