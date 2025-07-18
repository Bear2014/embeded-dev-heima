#include "STC8H.H"
#include "Config.h"
#include "STC8G_H_GPIO.H" 
#include "STC8G_H_Delay.H"

void GPIO_config();

void main() {
	
	  GPIO_config();
    
	  while(1) {
			P34 = 0; //开灯
			delay_ms(250);
      delay_ms(250);
			
			P34 = 1; //熄灯
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
//GPIO配置
//GPIO：通用输入输出，用来控制端口引脚的输入输出模式
//===============================================
void GPIO_config(){
   	GPIO_InitTypeDef  GPIO_Init;   //alt + 左键
		GPIO_Init.Mode = GPIO_PullUp;		//IO模式,  		GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
		GPIO_Init.Pin = GPIO_Pin_4;		 //要设置的引脚
    GPIO_Inilize(GPIO_P3, &GPIO_Init);
}