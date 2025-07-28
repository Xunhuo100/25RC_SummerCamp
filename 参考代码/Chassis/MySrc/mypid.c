#include "mypid.h"
#include "main.h"
#include "math.h"

void PID_Init(PID* PIDptr,float kp,float ki,float kd)
{
	PIDptr->kp=kp;
	PIDptr->ki=ki;
	PIDptr->kd=kd;
	
	PIDptr->Actual=0;
	PIDptr->Target=0;
	
	PIDptr->Error=0;
	PIDptr->dError=0;
	PIDptr->iError=0;
	
	PIDptr->Max_iError=20.0f;
	
	PIDptr->MaxOutput=600.0f;
}

void PID_ErrorRenew(PID* PIDptr)
{
	PIDptr->dError=(PIDptr->Actual-PIDptr->Target)-PIDptr->Error;
	PIDptr->Error=PIDptr->Actual-PIDptr->Target;
	//((PIDptr->iError+PIDptr->Error)>=(PIDptr->Max_iError))? PIDptr->Max_iError:PIDptr->iError+PIDptr->Error;
	if(fabs(PIDptr->iError+PIDptr->Error)<=(PIDptr->Max_iError))
		PIDptr->iError+=PIDptr->Error;
	else if((PIDptr->iError+PIDptr->Error)>(PIDptr->Max_iError))
		PIDptr->iError=PIDptr->Max_iError;
	else if((PIDptr->iError+PIDptr->Error)<-(PIDptr->Max_iError))
		PIDptr->iError=-PIDptr->Max_iError;
}

void PID_MaxOutputSet(PID* PIDptr,float MaxOutput)
{
	PIDptr->MaxOutput=MaxOutput;
}

float PID_Output(PID*PIDptr)
{
	float Output;
	PID_ErrorRenew(PIDptr);
	Output=(PIDptr->kp)*(PIDptr->Error)+(PIDptr->ki)*(PIDptr->iError)+(PIDptr->kd)*(PIDptr->dError);
	if(Output>PIDptr->MaxOutput)return PIDptr->MaxOutput;
	else return Output;
}

void PID_Reset(PID* PIDptr,float kp,float ki,float kd)
{
	PIDptr->kp=kp;
	PIDptr->ki=ki;
	PIDptr->kd=kd;
}