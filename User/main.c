#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "misc.h"
#include "../LCD.h"


#define BUTTON_INFO() GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)
#define MY_CAST (unsigned char*)


uint16_t delay_count=0;
uint16_t status=0;

void SysTick_Handler(void)//1ms
{
	if (delay_count > 0){delay_count--;}
}

void delay_ms(uint16_t delay_temp)
{
	delay_count = delay_temp;
	while(delay_count){}
}

void Button_Init(void)
{
	GPIO_InitTypeDef 	GPIO_Init_Struct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_Init_Struct.GPIO_Pin = SW0_PIN|SW2_PIN|SW3_PIN;
	GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init_Struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(SW0_PORT, &GPIO_Init_Struct);
	
	GPIO_Init_Struct.GPIO_Pin = SW1_PIN;
	GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init_Struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(SW1_PORT, &GPIO_Init_Struct);
}
extern int8_t mode;

void initEXTI(void)
{
	Button_Init();
	
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn|EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource6);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource8);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource9);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource11);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource15);

	EXTI_InitStruct.EXTI_Line = EXTI_Line6|EXTI_Line8|EXTI_Line9|EXTI_Line11|EXTI_Line15;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
}

void EXTI9_5_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line6) != RESET) {
		mode = 1;
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
	if (EXTI_GetITStatus(EXTI_Line8) != RESET) {
		mode = 2;
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
	if (EXTI_GetITStatus(EXTI_Line9) != RESET) {
		mode = 3;
		EXTI_ClearITPendingBit(EXTI_Line9);
	}
}

void EXTI15_10_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line15) != RESET) {
		mode = 4;
		EXTI_ClearITPendingBit(EXTI_Line15);
	}
	if (EXTI_GetITStatus(EXTI_Line11) != RESET) {
		mode = 5;
		EXTI_ClearITPendingBit(EXTI_Line11);
	}
}

int8_t mode = -1;
int main()
{
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);
	initEXTI();
	LCD_Init();
	while(1){
		switch(mode){
			case 0:
				ClearLCD();
				LCD_ShowStr(MY_CAST"Text1");
				mode = -1;
				break;
			case 1:
				ClearLCD();
				LCD_ShowStr(MY_CAST"Text2");
				mode = -1;
				break;
			case 2:
				ClearLCD();
				LCD_ShowStr(MY_CAST"Text3");
				mode = -1;
				break;
			case 3:
				ClearLCD();
				LCD_ShowStr(MY_CAST"Text4");
				mode = -1;
				break;
			case 4:	
				ClearLCD();
				LCD_ShowStr(MY_CAST"Text5");
				mode = -1;
				break;
		}
	}
	return 0;
}