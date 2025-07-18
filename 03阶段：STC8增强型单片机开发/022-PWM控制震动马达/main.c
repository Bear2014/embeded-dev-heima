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
	
	EAXSFR();		/* 扩展寄存器访问使能 */
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

//PWM配置
void PWM_Config() {
		PWMx_InitDefine pwm_init;
	
	  //配置PWM6：对应P01
	  pwm_init.PWM_Mode = CCMRn_PWM_MODE1;
	  pwm_init.PWM_Duty = 0; //关键配置
	  pwm_init.PWM_EnoSelect = ENO6P;	//输出通道选择[对应LED1的输出引脚]
	  PWM_Configuration(PWM6,&pwm_init);
	

	  //配置PWMB!!!!
	  pwm_init.PWM_Period = PERIOD;
	  pwm_init.PWM_DeadTime = 0; //死区发生器，0~255
	  pwm_init.PWM_CEN_Enable = ENABLE; //使能计数器，ENABLE，DISABLE
	  pwm_init.PWM_MainOutEnable = ENABLE; //主输出使用，ENABLE,DISABLE
		PWM_Configuration(PWMB,&pwm_init);

		
		//切换引脚
		PWM6_SW(PWM6_SW_P01);

		
		//中断使能
		NVIC_PWM_Init(PWMA,DISABLE,Priority_0);
}
