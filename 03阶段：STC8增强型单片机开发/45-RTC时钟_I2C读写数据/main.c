#include "lib/Config.h"
#include "lib/STC8G_H_GPIO.h"
#include "lib/STC8G_H_Delay.h"

#include "lib/STC8G_H_I2C.h"
#include "lib/STC8G_H_UART.h"
#include "lib/STC8G_H_NVIC.h"
#include "lib/STC8G_H_Switch.h"


/**
 * 思路：
 * 1.初始化IO口，将P32,P33初始化为开漏OD模式
 * 2.初始化I2C协议、UART
 * 3.通过I2C读取RTC时钟芯片的数据
 * 4.通过I2C向RTC时钟芯片写数据 
 **/


void GPIO_Config();
void UART_Config();
void I2C_Config();


void main() {
	
	EAXSFR();
	
	GPIO_Config();
	UART_Config();
	I2C_Config();
	
	EA = 1;
	
	printf("---read---\n"); // 需要注意，这里是串口打印，需要修改使用到的串口组，在库函数STC8G_H_UART.h第29行
	
	//3.通过I2C读取RTC时钟芯片的数据
	
	
	//4.通过I2C向RTC时钟芯片写数据 
	
	while(1) {}

}

void GPIO_Config() {
	GPIO_InitTypeDef GPIO_InitTypeDef;

	GPIO_InitTypeDef.Mode = GPIO_OUT_OD; //开漏模式
	GPIO_InitTypeDef.Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Inilize(GPIO_P2,&GPIO_InitTypeDef);
}


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


void I2C_Config()
{
	  I2C_InitTypeDef I2C_init;
	  I2C_init.I2C_Mode = I2C_Mode_Master;  //主从设备选择 I2C_Mode_Master, I2C_Mode_Slave
	  I2C_init.I2C_Enable = ENABLE;         //I2C功能使用，ENABLE,DISABLE
	  I2C_init.I2C_MS_WDTA = DISABLE;       //主机使用自动发送，ENABLE,DISABLE(间隔一段时间自动发送)
	  I2C_init.I2C_Speed = 13;              //总线速度=Fosc/2/(Speed*2+4)   范围：0~63
	                                        //固定计算方式： 400K = 24M / 2 / (Speed*2 + 4) 
	  I2C_Init(&I2C_init);
	
	
	  NVIC_I2C_Init(I2C_Mode_Master,DISABLE,Priority_0); //主从模式，I2C_Mode_Master, I2C_Mode_Slave;中断使用：ENABLE,DISABLE；优先级（低到高）Priority_0,Priority_1,Priority_3
	  I2C_SW(I2C_P33_P32);
}
