#include "lib/STC8G_H_GPIO.h"
#include "lib/STC8G_H_Delay.h"
#include "lib/STC8H_PWM.h"
#include "lib/STC8G_H_Switch.h"
#include "lib/STC8G_H_NVIC.h"

#define motor P01

void GPIO_Config();
void PWM_Config();

#define PERIOD ((MAIN_Fosc / 1000) - 1)
PWMx_Duty  duty;

void main() {
	int percent = 0;
	int direction = 1;
	
  EA = 1;
	GPIO_Config();
	
	EAXSFR();		/* ��չ�Ĵ�������ʹ�� */
	PWM_Config();
	
	while(1) {
		percent +=  direction;
		if(percent == 100) {
			delay_ms(100);
		  direction = -1;
		} else if(percent == 0){
			delay_ms(100);
			direction = 1;
		}
		
//		 if(percent > 100) {
//         percent = 0;
//     }
		
		duty.PWM6_Duty = PERIOD * percent / 100;
		UpdatePwm(PWM6, &duty);
		
		delay_ms(10);
	}
}


void GPIO_Config() {
	GPIO_InitTypeDef GPIO_InitTypeDef;

	GPIO_InitTypeDef.Mode = GPIO_OUT_PP;
	GPIO_InitTypeDef.Pin = GPIO_Pin_1;
	GPIO_Inilize(GPIO_P0,&GPIO_InitTypeDef);
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
