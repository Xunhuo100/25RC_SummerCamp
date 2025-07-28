#ifndef __MYUART_H
#define __MYUART_H

int pow10(int i);
void Command_RenewPiD(int m,int k,int mag,int way);
void Command_RenewTarget(int m,int target,int way);
void Command_RenewChassisMode();
void ChangeBytes(uint8_t bytes[4]);

#endif