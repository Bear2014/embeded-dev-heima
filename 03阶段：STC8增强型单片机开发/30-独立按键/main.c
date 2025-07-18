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

u8 key1_last_state = 1; //��ţ̌��״̬

void main() {
	  EAXSFR();
    GPIO_Config();
	  UART_Config();
	
	  EA = 1;
	
	  LED_SW = 0;
	  LED1 = 1;
	
	  printf("starting...\r\n");
	
	  while(1) {
		
			if(KEY1 == 1 && key1_last_state == 0) { //��ţ̌���˲��
			   printf("key up\r\n");
				 key1_last_state = 1;
			} else if(KEY1 == 0 && key1_last_state == 1) { //��ť���µ�˲��
				 printf("key down\r\n");
				 key1_last_state = 0;
				 LED1 = !LED1;
			}
		
			delay_ms(250);
		} 

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