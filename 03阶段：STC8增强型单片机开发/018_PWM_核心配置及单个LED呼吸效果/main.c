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
#define LED1 P27

#define PERIOD ((MAIN_Fosc / 1000) - 1)
PWMx_Duty  duty;

/**
 * Ч����ȫok
 */
 
//PWM����
void PWM_Config() {
		PWMx_InitDefine pwm_init;
	
	  //����Ա��ֵ
	  pwm_init.PWM_Mode = CCMRn_PWM_MODE2; //ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	                                       //ģʽ���õ��Ǹߵ͵�Ƶ��CCMRn_PWM_MODE1���ߵ�ƽ �� CCMRn_PWM_MODE2���͵�ƽ
	 	
	  /**
	   * ��Ӧ�ߵ͵�ƽ��ռ�� 
	   *��pwm_init.PWM_Mode = CCMRn_PWM_MODE2 + pwm_init.PWM_Duty = 0���ǵ͵�ƽ��ռ�ñ�����0��Ҳ����ȫ���߸ߵ�ƽ����������
	   */
	  pwm_init.PWM_Duty = 0; 
		//pwm_init.PWM_Duty = duty.PWM4_Duty;
	  //pwm_init.PWM_EnoSelect = ENO4P | ENO4N;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
		pwm_init.PWM_EnoSelect = ENO4N;	//���ͨ��ѡ��[��ӦLED1���������]
		PWM_Configuration(PWM4,&pwm_init);
	
	  /**
	   * �ؼ�����!!!!!
	   * ����ʱ��[һ���ߵ�ƽ��һ���͵�ƽ����һ��ռ�õ�ʱ��]��
	   * �����÷�Χ��0~65535��CPUû��ʱ��ĸ������ ʱ����� ��ͬ�� ���� �ĸ���
	   * ��������ϣ�����Ժ����Ƚ����ף����Ǵ������������Ϊ��1ms[ʱ��]
	   * ���1ms���� ���� �иߵ�ƽ �� �͵�ƽ�ĳ���
	   **/
	  pwm_init.PWM_Period = PERIOD;
	
	  /**
	   * �ؼ����ã�����
	   * ռ�ձ�ʱ��[�ߵ�ƽ��ռ��ʱ��]
	   * �����÷�Χ��0~period��Ҳ�� ���� �ĸ���
	   * ����12000������ռ��0.5
	   * �����þ��ǲ��ϱ仯�����¸ߵ�ƽ����ƽ���仯���Ӷ�����LED�ɰ������ı仯
		 *  һ���ʼֵ��0���������ӣ���ר�ŵĺ���������UpdatePwm()��
	   */
		pwm_init.PWM_DeadTime = 0; //������������0~255
	  pwm_init.PWM_CEN_Enable = ENABLE; //ʹ�ܼ�������ENABLE��DISABLE
	  pwm_init.PWM_MainOutEnable = ENABLE; //�����ʹ�ã�ENABLE,DISABLE
		
		PWM_Configuration(PWMA,&pwm_init);
		
		//�л�����
		PWM4_SW(PWM4_SW_P26_P27);
		
		//�ж�ʹ��
		NVIC_PWM_Init(PWMA,DISABLE,Priority_0);
}


void main() {
	int percent = 0;
  int direction = 1;

	
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
		duty.PWM4_Duty = PERIOD * percent / 100; //��Χ0~PERIOD,��ֵ��һֱ�仯��: PERIOD * �ٷֱ�
		UpdatePwm(PWM4, &duty);
		
		delay_ms(50); //����仯̫��
	}

}

void GPIO_Config() {
	GPIO_InitTypeDef GPIO_InitTypeDef;

	GPIO_InitTypeDef.Mode = GPIO_OUT_PP;
	GPIO_InitTypeDef.Pin = GPIO_Pin_5;
	GPIO_Inilize(GPIO_P4,&GPIO_InitTypeDef);
	
	GPIO_InitTypeDef.Mode = GPIO_OUT_PP;
	GPIO_InitTypeDef.Pin = GPIO_Pin_7;
	GPIO_Inilize(GPIO_P2,&GPIO_InitTypeDef);
}
