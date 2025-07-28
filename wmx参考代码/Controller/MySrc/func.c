#include "main.h"
#include "OLED.h"
#include "func.h"
#include "adc.h"
#include "math.h"
#include "usart.h"

union u
{
  float value;
  uint8_t bytes[4];
};

float Values[4][3]={{1.01f,1.0f,1.0f},
					{2.0f,2.0f,2.0f},
					{3.0f,3.0f,3.0f},
					{4.0f,4.0f,4.0f}};

uint32_t ADCValue[3]={0,0,1};

void LED_Init()
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,1);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,1);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,1);
}										

void ResetShow(int motor,int k,int mag)
{
	int i,j;

	switch(motor)
	{
		case 1:
			OLED_ShowString(1,6,"MOTOR 1");
		  	break;
		case 2:
			OLED_ShowString(1,6,"MOTOR 2");
			break;
		case 3:
			OLED_ShowString(1,6,"MOTOR 3");
			break;
		case 4:
			OLED_ShowString(1,6,"MOTOR 4");
			break;
	}
	
	switch(k)
	{	
		case 1:
			OLED_ShowSelectedString(2,1,"kp:");
			OLED_ShowString(3,1,"ki:");
			OLED_ShowString(4,1,"kd:");
			break;
		case 2:
			OLED_ShowSelectedString(3,1,"ki:");
			OLED_ShowString(2,1,"kp:");
			OLED_ShowString(4,1,"kd:");
			break;
		case 3:
			OLED_ShowSelectedString(4,1,"kd:");
			OLED_ShowString(2,1,"kp:");
			OLED_ShowString(3,1,"ki:");
			break;
		default:
			OLED_ShowString(4,1,"kd:");
			OLED_ShowString(2,1,"kp:");
			OLED_ShowString(3,1,"ki:");
	}
	for(i=1;i<=3;i++)
	{
		if(k==i)
		{
			OLED_ShowFloat(i+1,4,Values[motor-1][i-1],2,2,1);
			if(Values[motor-1][i-1]>=0)
				{
				if(mag>0&&mag<=2)
					OLED_ShowNum(i+1,3+mag,(int)(Values[motor-1][i-1]*100)/(pow10(4-mag))%10,1);
				else if(mag>2&&mag<=4)
					OLED_ShowNum(i+1,3+mag+1,(int)(Values[motor-1][i-1]*100)/pow10(4-mag)%10,1);
				}
		}
		else
			OLED_ShowFloat(i+1,4,Values[motor-1][i-1],2,2,0);
			
	}
	
}

uint32_t GetADC()
{
  HAL_ADC_Start(&hadc1);
  HAL_ADC_PollForConversion(&hadc1,HAL_MAX_DELAY);
  return HAL_ADC_GetValue(&hadc1);
}
           
int pow10(int i)
{
	int r=1;
	int n;
	for(n=0;n<i;n++)
		r*=10;
	return r;
}


/**
 * @brief 按下按钮时向底盘发送命令指示PID参数的改变，用的是uart1
 * @param motor 表示所选电机
 * @param k 表示所选参数，1到3分别指示kp ki kd
 * @param mag 表示倍率，1到4从十位到百分位
 * @param way 表示改变方向，1为+1，0为-1
 */
void TransValueCommand(int motor,int k,int mag,int way)
{
	uint8_t info[5];
	info[0]=2;
	info[1]=(uint8_t)motor;
	info[2]=(uint8_t)k;
	info[3]=(uint8_t)mag;
	info[4]=(uint8_t)way;
	HAL_UART_Transmit(&huart1,info,5,HAL_MAX_DELAY);
}

void ReceiveValues(int motor, int k)
{
	union u rxinfo={-1.0f};
	while(rxinfo.value==-1.0f)
		HAL_UART_Receive(&huart1,rxinfo.bytes,4,HAL_MAX_DELAY);
	Values[motor-1][k-1]=rxinfo.value;

}

void SetSpeedCommand(int motor,int speed,int way)//1正2反
{
	if(motor>=1&&motor<=4&&speed>0&&speed<20)
	{
		uint8_t txinfo[5];
		txinfo[0]=1;
		txinfo[1]=motor;
		txinfo[2]=speed;
		txinfo[3]=way;
		txinfo[4]=0;
		HAL_UART_Transmit(&huart1,txinfo,5,HAL_MAX_DELAY);

	}
}

void SetMove(uint8_t command)
{
	uint8_t txinfo[5];
	txinfo[0]=3;
	txinfo[1]=command;
	for(int i=2;i<=4;i++)
		txinfo[i]=0;
	HAL_UART_Transmit(&huart1,txinfo,5,HAL_MAX_DELAY);
}