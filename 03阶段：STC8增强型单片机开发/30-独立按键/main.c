#include "lib/config.h"
#include "lib/STC8G_H_GPIO.h"
#include "lib/STC8G_H_Delay.h"
#include "lib/STC8G_H_UART.h"
#include "lib/StC8G_H_NVIC.h"
#include "lib/STC8G_H_Switch.h"

void GPIO_Config();
void UART_Config();

#define KEY1   P51
#define LED_SW P45
#define LED1   P27

u8 key1_last_state = 1; //按钮抬起状态

void main() {
	  EAXSFR();
    GPIO_Config();
	  UART_Config();
	
	  EA = 1;
	
	  LED_SW = 0;
	  LED1 = 1;
	
	  printf("starting...\r\n");
	
	  while(1) {
		
			if(KEY1 == 1 && key1_last_state == 0) { //按钮抬起的瞬间
			   printf("key up\r\n");
				 key1_last_state = 1;
			} else if(KEY1 == 0 && key1_last_state == 1) { //按钮按下的瞬间
				 printf("key down\r\n");
				 key1_last_state = 0;
				 LED1 = !LED1;
			}
		
			delay_ms(250);
		} 

}



void GPIO_Config() {
		GPIO_InitTypeDef gpio_init;
	
	  //按钮1:P51
	  gpio_init.Mode = GPIO_PullUp;
	  gpio_init.Pin = GPIO_Pin_1;
	  GPIO_Inilize(GPIO_P5, &gpio_init);
	
	  //LED_SW:P45
	  gpio_init.Mode = GPIO_PullUp;
	  gpio_init.Pin = GPIO_Pin_5;
	  GPIO_Inilize(GPIO_P4, &gpio_init);
	
	  //LED1:P27
	  gpio_init.Mode = GPIO_PullUp;
	  gpio_init.Pin = GPIO_Pin_7;
	  GPIO_Inilize(GPIO_P2, &gpio_init);
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