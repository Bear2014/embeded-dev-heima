#include "STC8h.h"
#include "lib/Config.h"
#include "lib/STC8G_H_GPIO.h"
#include "lib/STC8G_H_Delay.h"
#include "lib/STC8G_H_NVIC.h"
#include "lib/STC8G_H_Switch.h"
#include "lib/STC8H_PWM.h"
#include "lib/STC8G_H_UART.h"

void GPIO_Config();
void UART_Config();
char recv_dat();
void led_to_left();
void led_to_right();


#define LED_SW P45
#define LED1 P27
#define LED2 P26
#define LED3 P15
#define LED4 P14
#define LED5 P23
#define LED6 P22
#define LED7 P21
#define LED8 P20


void main() {

	//配置GPIO
	GPIO_Config();
	
	//配置uart
	UART_Config();
	EA = 1;
	
  LED_SW = 0;
	
	while(1) { //此处也可以改成使用定时器来定时获取数据
		if(COM1.RX_Cnt > 0) {
			RX1_Buffer[0] == 0x00 ? led_to_right() : led_to_left();
			COM1.RX_Cnt = 0;
		}
		
		delay_ms(25);
	}
	
}

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

//配置串口
void UART_config(void)
{
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


//接收串口数据
char recv_dat() {
		char recv_char;
		if(COM1.RX_Cnt > 0) {
			recv_char = RX1_Buffer[0];

			//已经把数据处理好了，计数就要归0
			COM1.RX_Cnt = 0;
			return recv_char;
		}
		
		return 0x00;
}


//led灯从左到右闪灯
void led_to_right() {
	  u8 i;
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
}

//led灯从右到左闪灯
void led_to_left() {
	  u8 j;
		for(j=8;j>0;j--) {
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

