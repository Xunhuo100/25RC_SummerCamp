#ifndef __FUNC_H
#define __FUNC_H

void ResetShow(int motor,int k,int mag);
void LED_Init();
uint32_t GetADC();
int pow10(int i);
void test();
void DoubleToString(double f,char(*ps)[8]);
void TransValueCommand(int motor,int k,int mag,int way);
void ReceiveValues(int motor, int k);
void SetSpeedCommand(int motor,int speed,int way);
void SetMove(uint8_t command);

#endif
