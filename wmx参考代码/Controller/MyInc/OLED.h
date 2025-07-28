#ifndef __OLED_H
#define __OLED_H

#define OLED_W_SCL(x)		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, (x))
#define OLED_W_SDA(x)		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, (x))

void OLED_Init(void);
void OLED_Clear(void);
void OLED_I2C_Start(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowTest(uint8_t Line, uint8_t Column);
void OLED_ShowSelectedChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowSelectedString(uint8_t Line, uint8_t Column, char* string);
void OLED_ShowFloat(uint8_t Line, uint8_t Column, float Float,uint8_t IntLength,uint8_t DecLenth,int SelectState);


#endif
