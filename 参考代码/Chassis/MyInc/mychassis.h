#ifndef __MYCHASSIS_H
#define __MYCHASSIS_H

void Chassis_MotorBaseInit();

void Chassis_MotorPWMEnable();

void ChassisTest_ForwardMove();
void ChassisTest_BackwardMove();
void ChassisTest_LeftMove();
void ChassisTest_RightMove();
void ChassisTest_DiagonalMove_lf();
void ChassisTest_DiagonalMove_rb();
void ChassisTest_DiagonalMove_rf();
void ChassisTest_DiagonalMove_lb();
void ChassisTest_Turn_Clockwise();
void ChassisTest_Turn_Anticlockwise();

#endif
