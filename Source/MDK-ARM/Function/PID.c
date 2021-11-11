#include "data.h"

void PID_Init(float Kp,float Ti,float Td,float T,float Out_Max,PID_t *pid_struct);
void PID_Calc(PID_t *pid_struct);

void PID_Init(float Kp,float Ti,float Td,float T,float Out_Max,PID_t *pid_struct)
{
	pid_struct->Kp = Kp;
	pid_struct->Ti = Ti;
	pid_struct->Td = Td;
	
	pid_struct->T = T;
	pid_struct->Out_Max = Out_Max;
}

void PID_Calc(PID_t *pid_struct)
{
	float deltaE;
	float ki;
	float td;
	float out;
	
	if(pid_struct->Tdata < pid_struct->T)
		return; //如果不到计算周期则退出
	
	pid_struct->E_now = pid_struct->Set - pid_struct->Get; //当前偏差
	pid_struct->E_sum += pid_struct->E_now; //历史偏差之和
	pid_struct->Pout = pid_struct->E_now*pid_struct->Kp; //P输出
	
	deltaE = pid_struct->E_now - pid_struct->E_now; //偏差之差，求斜率用
	
	ki = pid_struct->T / pid_struct->Ti * pid_struct->Kp;
	pid_struct->Iout = ki * pid_struct->E_sum; //积分输出
	
	td = pid_struct->Td / pid_struct->T * pid_struct->Kp;
	pid_struct->Dout = td * deltaE; //微分输出
	
	out = pid_struct->Pout + pid_struct->Iout + pid_struct->Dout; //PID输出
	
	pid_struct->E_last = pid_struct->E_now; //更新偏差
	
	if(out > pid_struct->Out_Max)
		pid_struct->Out = pid_struct->Out_Max; //判断是否超出输出限幅
	else pid_struct->Out = out; //输出

}
