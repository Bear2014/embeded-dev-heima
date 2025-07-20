#include "lib/config.h"
#include "lib/STC8G_H_GPIO.h"
#include "lib/STC8G_H_Delay.h"
#include "lib/STC8G_H_UART.h"
#include "lib/StC8G_H_NVIC.h"
#include "lib/STC8G_H_Switch.h"

void GPIO_Config();
void UART_Config();

#define NIX_DI  P44 //数据输入
#define NIX_SCK P42 //移位寄存器
#define NIX_RCK P43 //锁存寄存器


void main() {
  
	  char i;
	
	  GPIO_Config();
	
	  //显示数字7
	  //从高位开始显示：11111000
	  for(i=7;i>=0;i--) {
				if(i<3) {
					NIX_DI = 0;
				} else {
					NIX_DI = 1;
				}
				
				//移位置寄存器(上升沿)
			  NIX_SCK = 0;
		    NOP2();
		    NIX_SCK = 1;
		    NOP2();
		}
		
		//然后再控制哪几个位置显示：7 7 空 7 7 7 7 7
		//与二进制位置相反的顺序
		for(i=7;i>=0;i--) {
			if(i != 2) {
				NIX_DI = 1;
			} else {
				NIX_DI = 0;
			}
			
			//移位置寄存器(上升沿)
			  NIX_SCK = 0;
		    NOP2();
		    NIX_SCK = 1;
		    NOP2();
		}
		
		//锁存操作
		NIX_RCK = 0;
		NOP();
		NIX_RCK = 1;
		NOP2();
		
		while(1) {};
		

}


void GPIO_Config() {
		GPIO_InitTypeDef gpio_init;

	  //推挽模式可以避免反向电流的影响
	  gpio_init.Mode = GPIO_OUT_PP;
	  gpio_init.Pin = GPIO_Pin_4 | GPIO_Pin_2 | GPIO_Pin_3;
	  GPIO_Inilize(GPIO_P4, &gpio_init);
}



//配置串口
void UART_Config() {
	  COMx_InitDefine		COMx_InitStructure;					//结构定义

    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;			//波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
    UART_Configuration(UART1, &COMx_InitStructure);		//初始化串口1 UART1,UART2,UART3,UART4
	
    NVIC_UART1_Init(ENABLE,Priority_1);		//中断使能, ENABLE\DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
    
    UART1_SW(UART1_SW_P30_P31);		//UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
}