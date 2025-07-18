#include "lib/config.h"
#include "lib/STC8G_H_GPIO.h"
#include "lib/STC8G_H_Delay.h"
#include "lib/STC8G_H_UART.h"
#include "lib/StC8G_H_NVIC.h"
#include "lib/STC8G_H_Switch.h"

void GPIO_Config();
void UART_Config();

#define KEY1   P51
#define KEY2   P52
#define KEY3   P53
#define KEY4   P54

#define KEY_UP 1 //����̧��״̬
#define KEY_DOWN 0 //��������״̬

u8 key_last_state[] = {KEY_UP,KEY_UP,KEY_UP,KEY_UP}; //��ţ̌��״̬

#define is_key_up(i)  key_last_state[i] == KEY_UP
#define is_key_down(i)  key_last_state[i] == KEY_DOWN

void main() {
	  int res;
	  
	  EAXSFR();
    GPIO_Config();
	  UART_Config();
	
	  EA = 1;
	
	  printf("starting...\r\n");
	
//	  res = 2 + 2*2;
//    printf("res=%d",res);	
	
	  while(1) {
		
			if(KEY1 == KEY_UP && is_key_down(0)) { //��ţ̌���˲��
			   printf("key1 up\r\n");
				 key_last_state[0] = KEY_UP;
			} else if(KEY1 == KEY_DOWN && is_key_up(0) == KEY_UP) { //��ť���µ�˲��
				 printf("key1 down\r\n");
				 key_last_state[0] = KEY_DOWN;
			}
			
			//���������⣡����
			if(KEY2 == KEY_UP && is_key_down(1) == KEY_DOWN) { //��ţ̌���˲��
			   printf("key2 up\r\n");
				 key_last_state[1] = KEY_UP;
			} else if(KEY2 == KEY_DOWN && is_key_up(1) == KEY_UP) { //��ť���µ�˲��
				 printf("key2 down\r\n");
				 key_last_state[1] = KEY_DOWN;
			}
			
			
			if(KEY3 == KEY_UP && is_key_down(2) == KEY_DOWN) { //��ţ̌���˲��
			   printf("key3 up\r\n");
				 key_last_state[2] = KEY_UP;
			} else if(KEY3 == KEY_DOWN && is_key_down(2) == KEY_UP) { //��ť���µ�˲��
				 printf("key3 down\r\n");
				 key_last_state[2] = KEY_DOWN;
			}
			
			
			if(KEY4 == KEY_UP && is_key_down(3) == KEY_DOWN) { //��ţ̌���˲��
			   printf("key4 up\r\n");
				 key_last_state[3] = KEY_UP;
			} else if(KEY4 == KEY_DOWN && is_key_down(3) == KEY_UP) { //��ť���µ�˲��
				 printf("key4 down\r\n");
				 key_last_state[3] = KEY_DOWN;
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