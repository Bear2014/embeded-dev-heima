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
			
			//��ȡP05���ŵĲ���ֵ
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



//����P05
void GPIO_Config() {
	GPIO_InitTypeDef gpio_init;
	gpio_init.Mode = GPIO_HighZ; //����Ϊ�������
	gpio_init.Pin = GPIO_Pin_5;
	GPIO_Inilize(GPIO_P0,&gpio_init);
}


//���ô���
void uart_Config() {
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


//����ADC
void ADC_Config(){
	ADC_InitTypeDef adc_init;
	
	adc_init.ADC_SMPduty = 31;		//ADC ģ���źŲ���ʱ�����, 0~31��ע�⣺ SMPDUTY һ����������С�� 10��
	adc_init.ADC_Speed = ADC_SPEED_2X1T;			//���� ADC ����ʱ��Ƶ��	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	
	//adc�ɼ�����������ֻ��12λ��װ����ɼ����ݣ�����16λ��װ
	adc_init.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC�������,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	adc_init.ADC_CsSetup = 0;		//ADC ͨ��ѡ��ʱ����� 0(Ĭ��),1
	adc_init.ADC_CsHold = 1;
	
	ADC_Inilize(&adc_init);
	
	//��Դʹ��
	ADC_PowerControl(ENABLE);
	
	//�ж�ʹ��
	NVIC_ADC_Init(DISABLE,Priority_1); //�ж�ʹ�ܣ�һ�㲻д��д�˻ῴ����һ���Ľ����������
}