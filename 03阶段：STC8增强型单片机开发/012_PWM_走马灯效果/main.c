#include "STC8h.h"
#include "lib/Config.h"
#include "lib/STC8G_H_GPIO.h"
#include "lib/STC8G_H_Delay.h"
#include "lib/STC8G_H_NVIC.h"
#include "lib/STC8G_H_Switch.h"
#include "lib/STC8H_PWM.h"

void Delay1000ms();

#define LED_SW P45
#define LED1 P27
#define LED2 P26
#define LED3 P15
#define LED4 P14
#define LED5 P23
#define LED6 P22
#define LED7 P21
#define LED8 P20


void GPIO_Config() {
	GPIO_InitTypeDef GPIO_InitTypeDef;

	GPIO_InitTypeDef.Mode = GPIO_OUT_PP;
	GPIO_InitTypeDef.Pin = GPIO_Pin_5;
	GPIO_Inilize(GPIO_P4,&GPIO_InitTypeDef);
	
	
	GPIO_InitTypeDef.Mode = GPIO_OUT_PP;
	GPIO_InitTypeDef.Pin = GPIO_Pin_7 | GPIO_Pin_6;
	GPIO_Inilize(GPIO_P2,&GPIO_InitTypeDef);
	
	
	GPIO_InitTypeDef.Mode = GPIO_OUT_PP;
	GPIO_InitTypeDef.Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Inilize(GPIO_P1,&GPIO_InitTypeDef);
	
	
	GPIO_InitTypeDef.Mode = GPIO_OUT_PP;
	GPIO_InitTypeDef.Pin = GPIO_Pin_3 | GPIO_Pin_2 | GPIO_Pin_1 | GPIO_Pin_0;
	GPIO_Inilize(GPIO_P2,&GPIO_InitTypeDef);
}



void main() {
	
	long i,j;
	
	EA = 1;
	
	//≈‰÷√GPIO
	GPIO_Config();
	
  LED_SW = 0;

	
	while(1) {
		
//		LED1 = LED2 =	LED3 = LED4 = LED5 = LED6 =	LED7 = LED8 = 0;
//	
//		delay_ms(250);
//		delay_ms(250);
		
//    Delay1000ms();
//	  Delay1000ms();
//	  Delay1000ms();
//	  Delay1000ms();
		
//		LED1 = LED2 =	LED3 = LED4 = LED5 = LED6 = LED7 = LED8 = 1;
		
		for(i=1;i<9;i++) {
			LED1 = i == 1 ? 0 : 1;
			LED2 = i == 2 ? 0 : 1;
			LED3 = i == 3 ? 0 : 1;
			LED4 = i == 4 ? 0 : 1;
			LED5 = i == 5 ? 0 : 1;
			LED6 = i == 6 ? 0 : 1;
			LED7 = i == 7 ? 0 : 1;
			LED8 = i == 8 ? 0 : 1;
      delay_ms(250);
		}
		
		
		for(j=8;i>0;j--) {
			LED1 = j == 1 ? 0 : 1;
			LED2 = j == 2 ? 0 : 1;
			LED3 = j == 3 ? 0 : 1;
			LED4 = j == 4 ? 0 : 1;
			LED5 = j == 5 ? 0 : 1;
			LED6 = j == 6 ? 0 : 1;
			LED7 = j == 7 ? 0 : 1;
			LED8 = j == 8 ? 0 : 1;
      delay_ms(250);
		}
		
	}
	
}


void Delay1000ms(void)	//@24.000MHz
{
	unsigned char data i, j, k;

	i = 122;
	j = 193;
	k = 128;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}