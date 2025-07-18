#include "lib/STC8G_H_GPIO.h"
#include "lib/STC8G_H_Delay.h"
#include "lib/STC8H_PWM.h"
#include "lib/STC8G_H_Switch.h"
#include "lib/STC8G_H_NVIC.h"
#include "lib/STC8G_H_UART.h"

/**
 * ��������0x00��ʱ�򣬲���ֹͣ������0x01��ʱ���������𶯣�Ч��ʧ�ܣ�������������������
 **/

#define Motor P01

void GPIO_Config();
void UART_Config();
void PWM_Config();
void Stop_Motor();

#define PERIOD ((MAIN_Fosc / 1000) - 1)
PWMx_Duty  duty;

int isUpdate = 1;
void main() {
	int percent = 0;
	int direction = 1;
	
  EA = 1;
	GPIO_Config();
	
	EAXSFR();		/* ��չ�Ĵ�������ʹ�� */
	PWM_Config();
	
	while(1) {
    if(isUpdate) {
			percent +=  direction;
			if(percent == 100) {
				direction = -1;
			} else if(percent == 0){
				direction = 1;
			}
			
			duty.PWM6_Duty = PERIOD * percent / 100;
			UpdatePwm(PWM6, &duty);		
		}
		
		
		//���ܴ�����������
		if(COM1.RX_Cnt>0 && --COM1.RX_TimeOut==0) {
			if(RX1_Buffer[0] == 0x00) { //ֹͣ��
				TX1_write2buff(RX1_Buffer[0]); //��ӡ���ܵ�������
				
				Stop_Motor();
				isUpdate = 0;
			} else if(RX1_Buffer[0] == 0x01) { //������
				PWM_Config();
				
				isUpdate = 1;
				percent = 0;
				direction = 1;
			}
			
			COM1.RX_Cnt = 0;
		}
		
		delay_ms(20);
	}
	
}


void GPIO_Config() {
	GPIO_InitTypeDef GPIO_InitTypeDef;

	GPIO_InitTypeDef.Mode = GPIO_OUT_PP;
	GPIO_InitTypeDef.Pin = GPIO_Pin_1;
	GPIO_Inilize(GPIO_P0,&GPIO_InitTypeDef);
}


void UART_config() {
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


//PWM����
void PWM_Config() {
		PWMx_InitDefine pwm_init;
	
	  //����PWM6����ӦP01
	  pwm_init.PWM_Mode = CCMRn_PWM_MODE1;
	  pwm_init.PWM_Duty = 0; //�ؼ�����
	  pwm_init.PWM_EnoSelect = ENO6P;	//���ͨ��ѡ��[��ӦLED1���������]
	  PWM_Configuration(PWM6,&pwm_init);
	
	  //����PWMB!!!!
	  pwm_init.PWM_Period = PERIOD;
	  pwm_init.PWM_DeadTime = 0; //������������0~255
	  pwm_init.PWM_CEN_Enable = ENABLE; //ʹ�ܼ�������ENABLE��DISABLE
	  pwm_init.PWM_MainOutEnable = ENABLE; //�����ʹ�ã�ENABLE,DISABLE
		PWM_Configuration(PWMB,&pwm_init);

		//�л�����
		PWM6_SW(PWM6_SW_P01);

		//�ж�ʹ��
		NVIC_PWM_Init(PWMA,DISABLE,Priority_0);
}

void Stop_Motor() {
		PWMx_InitDefine pwm_init;
	  PWM_Configuration(PWM6,&pwm_init);
}
