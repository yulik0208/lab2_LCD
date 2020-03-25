#ifndef LCD_H
#define LCD_H

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"


#define 		LCD_PORT							GPIOE
#define     LCD_PIN_RS            GPIO_Pin_7  
#define     LCD_PIN_RW            GPIO_Pin_10
#define     LCD_PIN_EN            GPIO_Pin_11          
#define     LCD_PIN_D7            GPIO_Pin_15         
#define     LCD_PIN_D6            GPIO_Pin_14          
#define     LCD_PIN_D5            GPIO_Pin_13         
#define     LCD_PIN_D4            GPIO_Pin_12         
#define     LCD_PIN_MASK  				((LCD_PIN_RS | LCD_PIN_EN | LCD_PIN_D7 | LCD_PIN_D6 | LCD_PIN_D5 | LCD_PIN_D4))
#define 		LCD_PIN_OFFSET  			12

#define 		SW0_PORT 							GPIOC
#define 		SW1_PORT 							GPIOA
#define 	  SW2_PORT 							GPIOC
#define 		SW3_PORT 							GPIOC
#define 		SW4_PORT 							GPIOC
#define 		SW0_PIN 							GPIO_Pin_11
#define 		SW1_PIN 							GPIO_Pin_15
#define 		SW2_PIN 							GPIO_Pin_9
#define 		SW3_PIN 							GPIO_Pin_6
#define 		SW4_PIN 							GPIO_Pin_8

void LCD_Init(void);
void ClearLCD(void);
void LCD_GoToLine(char LineNum);
void Display_Write_Ins(uint8_t data);
void LCD_Pin_Initialize(void);
void lcd_delay(unsigned int p);
void LCD_ShowStr(unsigned char *s);
void LCD_ShowChar(unsigned char c);

#endif //LCD_H