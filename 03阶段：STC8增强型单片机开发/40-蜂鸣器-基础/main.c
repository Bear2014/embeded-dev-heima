#include "lib/config.h"
#include "lib/STC8G_H_GPIO.h"
#include "lib/STC8G_H_Delay.h"

void GPIO_Config();

#define BUZZER  P00


void main() {

		GPIO_Config();
	
	
	  //有源蜂鸣器，给点就响；无源蜂鸣器，需要提供震荡源，提供交流电才响
    //BUZZER = 1;
	  
	
		while(1) {
			 BUZZER = 1;
		   delay_ms(2);
			
			 BUZZER = 0;
			 delay_ms(2);
		}
		
}


void GPIO_Config() {
		GPIO_InitTypeDef gpio_init;

	  //推挽模式可以避免反向电流的影响
	  gpio_init.Mode = GPIO_OUT_PP;
	  gpio_init.Pin = GPIO_Pin_0;
	  GPIO_Inilize(GPIO_P0, &gpio_init);
}