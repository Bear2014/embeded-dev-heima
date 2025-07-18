#include "config.h"
#include "STC8G_H_Delay.h"
#include "STC8G_H_GPIO.h"



/******************* IO配置函数 *******************/
void	GPIO_config(void)
{
    GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义

    GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1;		//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7
    GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);	//初始化
}


void main() {

	
		//1.配置IO模式
    GPIO_config();
	
	  while(1) {
			P34 = 1;
			NOP1();
			P34 = 0;
			NOP1();
		}
	
}