#include "STC8H.H"
#include "Config.h"
#include "STC8G_H_GPIO.H" 
#include "STC8G_H_Delay.H"

void GPIO_config();

void main() {
	
	  GPIO_config();
    
	  while(1) {
			P34 = 0; //����
			delay_ms(250);
      delay_ms(250);
			
			P34 = 1; //Ϩ��
//		Delay1000ms();
			delay_ms(250);
			delay_ms(250);
			delay_ms(250);
			delay_ms(250);
			delay_ms(250);
			delay_ms(250);
			delay_ms(250);
			delay_ms(250);
		}
}

//===============================================
//GPIO����
//GPIO��ͨ������������������ƶ˿����ŵ��������ģʽ
//===============================================
void GPIO_config(){
   	GPIO_InitTypeDef  GPIO_Init;   //alt + ���
		GPIO_Init.Mode = GPIO_PullUp;		//IOģʽ,  		GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
		GPIO_Init.Pin = GPIO_Pin_4;		 //Ҫ���õ�����
    GPIO_Inilize(GPIO_P3, &GPIO_Init);
}