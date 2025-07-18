#include "lib/config.h"
#include "lib/STC8G_H_GPIO.h"
#include "lib/STC8G_H_Delay.h"
#include "lib/STC8G_H_UART.h"
#include "lib/StC8G_H_NVIC.h"
#include "lib/STC8G_H_Switch.h"


void GPIO_Config();
void UART_Config();

#define key_last_state ox0f;

#define is_key_up(i)  key_last_state && (1 << i) == 0   
#define is_key_down(i) key_last_state && (1 << i) > 0


void main() {
  
	  u8 v = oxOf;
	  
	

}



void GPIO_Config() {
		GPIO_InitTypeDef gpio_init;
	
	  //��ť1:P51
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



//���ô���
void UART_Config() {
	  COMx_InitDefine		COMx_InitStructure;					//�ṹ����

    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;			//������, һ�� 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE
    UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������1 UART1,UART2,UART3,UART4
	
    NVIC_UART1_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE\DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    
    UART1_SW(UART1_SW_P30_P31);		//UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
}