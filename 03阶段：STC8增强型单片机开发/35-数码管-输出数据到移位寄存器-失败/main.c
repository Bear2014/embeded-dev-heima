#include "lib/config.h"
#include "lib/STC8G_H_GPIO.h"
#include "lib/STC8G_H_Delay.h"
#include "lib/STC8G_H_UART.h"
#include "lib/StC8G_H_NVIC.h"
#include "lib/STC8G_H_Switch.h"

void GPIO_Config();
void UART_Config();

#define NIX_DI  P44 //��������
#define NIX_SCK P42 //��λ�Ĵ���
#define NIX_RCK P43 //����Ĵ���


void main() {
  
	  char i;
	
	  GPIO_Config();
	
	  //��ʾ����7
	  //�Ӹ�λ��ʼ��ʾ��11111000
	  for(i=7;i>=0;i--) {
				if(i<3) {
					NIX_DI = 0;
				} else {
					NIX_DI = 1;
				}
				
				//��λ�üĴ���(������)
			  NIX_SCK = 0;
		    NOP2();
		    NIX_SCK = 1;
		    NOP2();
		}
		
		//Ȼ���ٿ����ļ���λ����ʾ��7 7 �� 7 7 7 7 7
		//�������λ���෴��˳��
		for(i=7;i>=0;i--) {
			if(i != 2) {
				NIX_DI = 1;
			} else {
				NIX_DI = 0;
			}
			
			//��λ�üĴ���(������)
			  NIX_SCK = 0;
		    NOP2();
		    NIX_SCK = 1;
		    NOP2();
		}
		
		//�������
		NIX_RCK = 0;
		NOP();
		NIX_RCK = 1;
		NOP2();
		
		while(1) {};
		

}


void GPIO_Config() {
		GPIO_InitTypeDef gpio_init;

	  //����ģʽ���Ա��ⷴ�������Ӱ��
	  gpio_init.Mode = GPIO_OUT_PP;
	  gpio_init.Pin = GPIO_Pin_4 | GPIO_Pin_2 | GPIO_Pin_3;
	  GPIO_Inilize(GPIO_P4, &gpio_init);
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