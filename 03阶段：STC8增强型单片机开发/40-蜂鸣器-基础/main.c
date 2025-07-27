#include "lib/config.h"
#include "lib/STC8G_H_GPIO.h"
#include "lib/STC8G_H_Delay.h"

void GPIO_Config();

#define BUZZER  P00


void main() {

		GPIO_Config();
	
	
	  //��Դ��������������죻��Դ����������Ҫ�ṩ��Դ���ṩ���������
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

	  //����ģʽ���Ա��ⷴ�������Ӱ��
	  gpio_init.Mode = GPIO_OUT_PP;
	  gpio_init.Pin = GPIO_Pin_0;
	  GPIO_Inilize(GPIO_P0, &gpio_init);
}