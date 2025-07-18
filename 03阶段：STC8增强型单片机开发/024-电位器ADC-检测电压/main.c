#include "lib/STC8G_H_GPIO.h"
#include "lib/STC8G_H_Delay.h"
#include "lib/STC8G_H_UART.h"
#include "lib/STC8G_H_Switch.h"
#include "lib/STC8G_H_ADC.h"
#include "lib/STC8G_H_NVIC.h"


#define P_ADC P05;

void GPIO_Config();
void uart_Config();
void ADC_Config();


void main() {
	  u16 adc_value;
	  float res;

		EA = 1;
	  GPIO_Config();
	
	  uart_Config();
	
	  ADC_Config();
	  
	  printf("start...\n");
	
	
	  while(1) {
			
			//获取P05引脚的测量值
			adc_value = Get_ADCResult(ADC_CH13);
			printf("adc_value=%d\n",adc_value);
			
			res = adc_value * 2.5 / 4096;
			printf("res=%.2fv\n", res);
			
			
			delay_ms(250);
			delay_ms(250);
			delay_ms(250);
			delay_ms(250);
		}
	
}



//配置P05
void GPIO_Config() {
	GPIO_InitTypeDef gpio_init;
	gpio_init.Mode = GPIO_HighZ; //设置为高阻输出
	gpio_init.Pin = GPIO_Pin_5;
	GPIO_Inilize(GPIO_P0,&gpio_init);
}


//配置串口
void uart_Config() {
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


//配置ADC
void ADC_Config(){
	ADC_InitTypeDef adc_init;
	
	adc_init.ADC_SMPduty = 31;		//ADC 模拟信号采样时间控制, 0~31（注意： SMPDUTY 一定不能设置小于 10）
	adc_init.ADC_Speed = ADC_SPEED_2X1T;			//设置 ADC 工作时钟频率	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	
	//adc采集出来的数据只有12位，装这个采集数据，采用16位来装
	adc_init.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC结果调整,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	adc_init.ADC_CsSetup = 0;		//ADC 通道选择时间控制 0(默认),1
	adc_init.ADC_CsHold = 1;
	
	ADC_Inilize(&adc_init);
	
	//电源使用
	ADC_PowerControl(ENABLE);
	
	//中断使用
	NVIC_ADC_Init(DISABLE,Priority_1); //中断使能，一般不写，写了会看到不一样的结果！！！！
}