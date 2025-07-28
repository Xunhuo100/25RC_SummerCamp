#ifndef __MYPID_H
#define __MYPID_H

typedef struct pid
{
	float kp,ki,kd;
	float Target,Actual;
	float Error,iError,dError;
	float Max_iError;
	float MaxOutput;
	
}PID;

void PID_Init(PID* PIDptr,float kp,float ki,float kd);
void PID_ErrorRenew(PID* PIDptr);
void PID_MaxOutputSet(PID* PIDptr,float MaxOutput);
float PID_Output(PID*PIDptr);
void PID_Reset(PID* PIDptr,float kp,float ki,float kd);


#endif
