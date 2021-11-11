#include "stm32f1xx_hal.h"
#include "data.h"

void GetSpeed(void);

moto_data_t moto_left;
moto_data_t moto_right;

PID_t moto_left_pid;
PID_t moto_right_pid;

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
uint16_t ADC_Values[2]={0};
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6) //TIM6准备用来做ADC读取
	{
		moto_left_pid.Tdata++;
		moto_right_pid.Tdata++;
	}
	if(htim->Instance == TIM7) //中断频率为10Hz
	{
		GetSpeed(); //获取左右轮子绝对速度（编码器值）
	}
}

void GetSpeed(void)
{
	static int32_t speed_left;
	static int32_t speed_right;
	
	speed_left = __HAL_TIM_GET_COUNTER(&htim3);
	speed_right = __HAL_TIM_GET_COUNTER(&htim4);
	if(speed_left>60000)
		speed_left = -(65565-speed_left);
		if(speed_right>60000)
	speed_right = -(65565-speed_right);
	__HAL_TIM_SET_COUNTER(&htim3,0);
	__HAL_TIM_SET_COUNTER(&htim4,0);
	
	moto_left.now_speed = speed_left;
	moto_right.now_speed = speed_right;
}
