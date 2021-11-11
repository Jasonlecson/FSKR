#include "stdint.h"

typedef struct 
{
	int32_t now_speed;
	int32_t set_speed;
	int8_t now_dirct;
	int8_t set_dirct;
}moto_data_t;

typedef struct
{
	float Kp; //比例系数
	float Ti; //积分时间系数
	float Td; //微分系数
	
	float Set; //设定值
	float Get; //反馈值
	
	float Pout; //比例输出
	float Iout; //积分输出
	float Dout; //微分输出
	
	float T; //计算周期
	uint16_t Tdata; //判断周期是否达到
	
	float E_now; //本次偏差
	float E_last; //上次偏差
	float E_sum; //偏差之和
	
	float Out_Max; //输出限幅
	float Out; //输出
}PID_t;