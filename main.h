#ifndef MAIN_H
#define MAIN_H

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "misc.h"
	
void initEXTI(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
#define BUTTON_INFO() GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)

#endif //MAIN_H