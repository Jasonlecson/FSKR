#include "stm32f1xx_hal.h"
#include "gpio.h"

void ADC_Init(void);
void Encoder_Init(void);
void GPIO_Init(void);
void PWM_Init(void);
void System_Init(void);
void TIM_IT_Init(void);

extern uint16_t ADC_Values[2];

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;

void PWM_Init(void)
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1); //左电机PWM
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4); //右电机PWM
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3); //舵机PWM
	TIM1->CCR1 = 0;//左电机
	TIM1->CCR4 = 0;//右电机
	TIM2->CCR3 = 1000;//舵机
}
void GPIO_Init(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET);
}
void Encoder_Init(void)
{
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL); //TIM3是左轮双相霍尔编码器
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL); //右轮双相霍尔编码器
}
void ADC_Init(void)
{
	HAL_ADCEx_Calibration_Start(&hadc1);
}
void TIM_IT_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim6); //ADC
	HAL_TIM_Base_Start_IT(&htim7); //测速
}
void System_Init(void)
{
	Encoder_Init();
	ADC_Init();
	PWM_Init();
	TIM_IT_Init();
	GPIO_Init();
}