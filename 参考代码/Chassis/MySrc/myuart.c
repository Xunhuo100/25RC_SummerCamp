#include "main.h"
#include "mypid.h"
#include "mymotor.h"
#include "mychassis.h"
#include "usart.h"
#include "tim.h"
#include "mypid.h"

extern MOTOR motor[4];
extern uint8_t MotorChoice;

int pow10(int i)
{
	int r=1;
	int n;
	for(n=0;n<i;n++)
		r*=10;
	return r;
}
void ChangeBytes(uint8_t bytes[4])
{
    uint8_t tmp;
    tmp= bytes[0];
    bytes[0]=bytes[3];
    bytes[3]=tmp;

    tmp= bytes[1];
    bytes[1]=bytes[2];
    bytes[2]=tmp;
}

void Command_RenewPiD(int m,int k,int mag,int way)
{
    int value;
    union 
    {
      float value;
      uint8_t bytes[4];  
    }rxinfo;
    
    switch(k)
    {
        case 1:
            value=(int)(motor[m-1].MotorPID.kp*100.0f);
            rxinfo.value=motor[m-1].MotorPID.kp;
            break;
        case 2:
            value=(int)(motor[m-1].MotorPID.ki*100.0f);
            rxinfo.value=motor[m-1].MotorPID.ki;
            break;
        case 3:
            value=(int)(motor[m-1].MotorPID.kd*100.0f);
            rxinfo.value=motor[m-1].MotorPID.kd;
            break;
    }

    if(way == 1)
    {
        if (value/pow10(4-mag)%10<9)
        {
            switch(k)
            {
                case 1:
                    motor[m-1].MotorPID.kp=((float)(value+pow10(4-mag)))/(100.0f);
                    rxinfo.value=motor[m-1].MotorPID.kp;
                    break;
                case 2:
                    motor[m-1].MotorPID.ki=((float)(value+pow10(4-mag)))/(100.0f);
                    rxinfo.value=motor[m-1].MotorPID.ki;
                    break;
                case 3:
                    motor[m-1].MotorPID.kd=((float)(value+pow10(4-mag)))/(100.0f);
                    rxinfo.value=motor[m-1].MotorPID.kd;
                    break;
            }
        }
        HAL_UART_Transmit(&huart1,rxinfo.bytes,4,HAL_MAX_DELAY);
    }
    else if(way == 0)
    {
        if (value/pow10(4-mag)%10>0)
        {
            switch(k)
            {
                case 1:
                    motor[m-1].MotorPID.kp=((float)(value-pow10(4-mag)))/(100.0f);
                    rxinfo.value=motor[m-1].MotorPID.kp;
                    break;
                case 2:
                    motor[m-1].MotorPID.ki=((float)(value-pow10(4-mag)))/(100.0f);
                    rxinfo.value=motor[m-1].MotorPID.ki;
                    break;
                case 3:
                    motor[m-1].MotorPID.kd=((float)(value-pow10(4-mag)))/(100.0f);
                    rxinfo.value=motor[m-1].MotorPID.kd;
                    break;
            }
        }
        HAL_UART_Transmit(&huart1,rxinfo.bytes,4,HAL_MAX_DELAY);
    }
}

void Command_RenewTarget(int m,int target,int way)
{
    if(target!='0'&&target>=0&&target<=20)
    {
        if(way==1)
            motor[m-1].MotorPID.Target=target;
        else if(way ==2 )
            motor[m-1].MotorPID.Target=-target;
    }

    else if(target=='0')
        motor[m-1].MotorPID.Target=0;
    MotorChoice=m;
}

void Command_RenewChassisMode()
{

}