#include "stm32f1xx_hal.h"
#include "data.h"

void Turning(int8_t angle);


void Turning(int8_t angle)
{
	TIM2->CCR3 = 1000+100*angle;
}
