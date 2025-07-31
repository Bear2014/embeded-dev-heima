#include "lib/Config.h"
#include "lib/STC8G_H_GPIO.h"
#include "lib/STC8G_H_Delay.h"

#include "lib/STC8G_H_I2C.h"
#include "lib/STC8G_H_UART.h"
#include "lib/STC8G_H_NVIC.h"
#include "lib/STC8G_H_Switch.h"


/**
 * ˼·��
 * 1.��ʼ��IO�ڣ���P32,P33��ʼ��Ϊ��©ODģʽ
 * 2.��ʼ��I2CЭ�顢UART
 * 3.ͨ��I2C��ȡRTCʱ��оƬ������
 * 4.ͨ��I2C��RTCʱ��оƬд���� 
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
	
	printf("---read---\n"); // ��Ҫע�⣬�����Ǵ��ڴ�ӡ����Ҫ�޸�ʹ�õ��Ĵ����飬�ڿ⺯��STC8G_H_UART.h��29��
	
	//3.ͨ��I2C��ȡRTCʱ��оƬ������
	
	
	//4.ͨ��I2C��RTCʱ��оƬд���� 
	
	while(1) {}

}

void GPIO_Config() {
	GPIO_InitTypeDef GPIO_InitTypeDef;

	GPIO_InitTypeDef.Mode = GPIO_OUT_OD; //��©ģʽ
	GPIO_InitTypeDef.Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Inilize(GPIO_P2,&GPIO_InitTypeDef);
}


void UART_config(void)
{
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


void I2C_Config()
{
	  I2C_InitTypeDef I2C_init;
	  I2C_init.I2C_Mode = I2C_Mode_Master;  //�����豸ѡ�� I2C_Mode_Master, I2C_Mode_Slave
	  I2C_init.I2C_Enable = ENABLE;         //I2C����ʹ�ã�ENABLE,DISABLE
	  I2C_init.I2C_MS_WDTA = DISABLE;       //����ʹ���Զ����ͣ�ENABLE,DISABLE(���һ��ʱ���Զ�����)
	  I2C_init.I2C_Speed = 13;              //�����ٶ�=Fosc/2/(Speed*2+4)   ��Χ��0~63
	                                        //�̶����㷽ʽ�� 400K = 24M / 2 / (Speed*2 + 4) 
	  I2C_Init(&I2C_init);
	
	
	  NVIC_I2C_Init(I2C_Mode_Master,DISABLE,Priority_0); //����ģʽ��I2C_Mode_Master, I2C_Mode_Slave;�ж�ʹ�ã�ENABLE,DISABLE�����ȼ����͵��ߣ�Priority_0,Priority_1,Priority_3
	  I2C_SW(I2C_P33_P32);
}
