#include "lib/STC8G_H_GPIO.h"
#include "lib/STC8G_H_Delay.h"

#define motor P01

void GPIO_Config() {
	GPIO_InitTypeDef GPIO_InitTypeDef;

	GPIO_InitTypeDef.Mode = GPIO_OUT_PP;
	GPIO_InitTypeDef.Pin = GPIO_Pin_1;
	GPIO_Inilize(GPIO_P0,&GPIO_InitTypeDef);
}

void main() {
  EA = 1;
	
	GPIO_Config();
	
	while(1) {
		
		//Æô¶¯
		motor = 1;
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		
		//Í£Ö¹
		motor = 0;
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
	}
}
