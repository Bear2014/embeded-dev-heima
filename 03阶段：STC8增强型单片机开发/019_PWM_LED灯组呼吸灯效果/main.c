#include "STC8h.h"
#include "lib/Config.h"
#include "lib/STC8G_H_GPIO.h"
#include "lib/STC8G_H_Delay.h"
#include "lib/STC8G_H_NVIC.h"
#include "lib/STC8G_H_Switch.h"
#include "lib/STC8H_PWM.h"
#include "lib/STC8G_H_UART.h"

void GPIO_Config();

#define LED_SW P45
#define LED1    P27
#define LED2		P26
#define LED3		P15
#define LED4		P14
#define LED5		P23
#define LED6		P22
#define LED7		P21
#define LED8		P20

#define PERIOD ((MAIN_Fosc / 1000) - 1)
PWMx_Duty  duty;

/**
 * Ч���ܸܵ�
 */


//PWM����
void PWM_Config() {
		PWMx_InitDefine pwm_init;
	
	  //����PWM4����ӦP27 P26
	  pwm_init.PWM_Mode = CCMRn_PWM_MODE2;
	  pwm_init.PWM_Duty = 0; //�ؼ�����
		//pwm_init.PWM_Duty = duty.PWM4_Duty;
	  pwm_init.PWM_EnoSelect = ENO4P | ENO4N;	//���ͨ��ѡ��[��ӦLED1���������]
	  PWM_Configuration(PWM4,&pwm_init);
	
	  //����PWM3:��ӦP15 P14
	  pwm_init.PWM_Mode = CCMRn_PWM_MODE2;
	  pwm_init.PWM_Duty = 0; //�ؼ�����
	  pwm_init.PWM_EnoSelect = ENO3P | ENO3N;
	  PWM_Configuration(PWM3,&pwm_init);
	
		//����PWM2:��ӦP23 P22
	  pwm_init.PWM_Mode = CCMRn_PWM_MODE2;
	  pwm_init.PWM_Duty = 0; //�ؼ�����
	  pwm_init.PWM_EnoSelect = ENO2P| ENO2N;
	  PWM_Configuration(PWM2,&pwm_init);
	
		//����PWM1:��ӦP21 P20
	  pwm_init.PWM_Mode = CCMRn_PWM_MODE2;
	  pwm_init.PWM_Duty = 0; //�ؼ�����
	  pwm_init.PWM_EnoSelect = ENO1P| ENO1N;
	  PWM_Configuration(PWM1,&pwm_init);
	

	  //����PWMA!!!!
	  /**
	   * PWM_Period���ؼ�����!!!!!
	   * ����ʱ��[һ���ߵ�ƽ��һ���͵�ƽ����һ��ռ�õ�ʱ��]��
	   * �����÷�Χ��0~65535��CPUû��ʱ��ĸ������ ʱ����� ��ͬ�� ���� �ĸ���
	   * ��������ϣ�����Ժ����Ƚ����ף����Ǵ������������Ϊ��1ms[ʱ��]
	   * ���1ms���� ���� �иߵ�ƽ �� �͵�ƽ�ĳ���
	   **/
	  pwm_init.PWM_Period = PERIOD;
	  pwm_init.PWM_DeadTime = 0; //������������0~255
	  pwm_init.PWM_CEN_Enable = ENABLE; //ʹ�ܼ�������ENABLE��DISABLE
	  pwm_init.PWM_MainOutEnable = ENABLE; //�����ʹ�ã�ENABLE,DISABLE
		PWM_Configuration(PWMA,&pwm_init);

		
		//�л�����
		PWM4_SW(PWM4_SW_P26_P27);
		PWM3_SW(PWM3_SW_P14_P15);
		PWM2_SW(PWM2_SW_P22_P23);
		PWM1_SW(PWM1_SW_P20_P21);

		
		//�ж�ʹ��
		NVIC_PWM_Init(PWMA,DISABLE,Priority_0);
}


void main() {
	int percent = 0;
  int direction = 1;
	int duty_value = 0;

	
	//����GPIO
	GPIO_Config();

	//����չ�Ĵ���ʹ��(pwmר��),��һ��Ҫ������pwm֮ǰ�򿪣���������
	EAXSFR();
	
	//����pwm
	PWM_Config();
	
	//��ȫ���ж�
	EA = 1;
	
  LED_SW = 0;
	
	//LED1 = 0;
	
	while(1) { //�˴�Ҳ���Ըĳ�ʹ�ö�ʱ������ʱ��ȡ����

		percent += direction;
		if(percent == 100) {
		  direction = -1;
		} else if(percent == 0){
			direction = 1;
		}
		
		//����ռ�ձȣ�����1��������һ��ͨ��������һ���飻����2��ռ�ձȵ�ָ�����
		duty_value = PERIOD * percent / 100; //��Χ0~PERIOD,��ֵ��һֱ�仯��: PERIOD * �ٷֱ�
		
		duty.PWM4_Duty = duty_value;
    duty.PWM3_Duty = duty_value;
		duty.PWM2_Duty = duty_value;
		duty.PWM1_Duty = duty_value;
		UpdatePwm(PWMA, &duty);
		
		delay_ms(25); //����仯̫��
	}

}

void GPIO_Config() {
	GPIO_InitTypeDef GPIO_InitTypeDef;

	GPIO_InitTypeDef.Mode = GPIO_OUT_PP;
	GPIO_InitTypeDef.Pin = GPIO_Pin_5;
	GPIO_Inilize(GPIO_P4,&GPIO_InitTypeDef);
	
	GPIO_InitTypeDef.Mode = GPIO_OUT_PP;
	GPIO_InitTypeDef.Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_3 | GPIO_Pin_2 | GPIO_Pin_1 | GPIO_Pin_0;
	GPIO_Inilize(GPIO_P2,&GPIO_InitTypeDef);
	
	GPIO_InitTypeDef.Mode = GPIO_OUT_PP;
	GPIO_InitTypeDef.Pin = GPIO_Pin_5 | GPIO_Pin_4;
	GPIO_Inilize(GPIO_P1,&GPIO_InitTypeDef);
}
