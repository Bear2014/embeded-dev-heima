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
 * 效果杠杠的
 */


//PWM配置
void PWM_Config() {
		PWMx_InitDefine pwm_init;
	
	  //配置PWM4：对应P27 P26
	  pwm_init.PWM_Mode = CCMRn_PWM_MODE2;
	  pwm_init.PWM_Duty = 0; //关键配置
		//pwm_init.PWM_Duty = duty.PWM4_Duty;
	  pwm_init.PWM_EnoSelect = ENO4P | ENO4N;	//输出通道选择[对应LED1的输出引脚]
	  PWM_Configuration(PWM4,&pwm_init);
	
	  //配置PWM3:对应P15 P14
	  pwm_init.PWM_Mode = CCMRn_PWM_MODE2;
	  pwm_init.PWM_Duty = 0; //关键配置
	  pwm_init.PWM_EnoSelect = ENO3P | ENO3N;
	  PWM_Configuration(PWM3,&pwm_init);
	
		//配置PWM2:对应P23 P22
	  pwm_init.PWM_Mode = CCMRn_PWM_MODE2;
	  pwm_init.PWM_Duty = 0; //关键配置
	  pwm_init.PWM_EnoSelect = ENO2P| ENO2N;
	  PWM_Configuration(PWM2,&pwm_init);
	
		//配置PWM1:对应P21 P20
	  pwm_init.PWM_Mode = CCMRn_PWM_MODE2;
	  pwm_init.PWM_Duty = 0; //关键配置
	  pwm_init.PWM_EnoSelect = ENO1P| ENO1N;
	  PWM_Configuration(PWM1,&pwm_init);
	

	  //配置PWMA!!!!
	  /**
	   * PWM_Period：关键配置!!!!!
	   * 周期时间[一个高电平和一个低电平加在一起占用的时间]，
	   * 可配置范围：0~65535，CPU没有时间的概念，它的 时间概念 等同于 数数 的概念
	   * 假设我们希望在以后计算比较容易，我们打算把周期设置为：1ms[时间]
	   * 这个1ms代表 里面 有高电平 和 低电平的出现
	   **/
	  pwm_init.PWM_Period = PERIOD;
	  pwm_init.PWM_DeadTime = 0; //死区发生器，0~255
	  pwm_init.PWM_CEN_Enable = ENABLE; //使能计数器，ENABLE，DISABLE
	  pwm_init.PWM_MainOutEnable = ENABLE; //主输出使用，ENABLE,DISABLE
		PWM_Configuration(PWMA,&pwm_init);

		
		//切换引脚
		PWM4_SW(PWM4_SW_P26_P27);
		PWM3_SW(PWM3_SW_P14_P15);
		PWM2_SW(PWM2_SW_P22_P23);
		PWM1_SW(PWM1_SW_P20_P21);

		
		//中断使能
		NVIC_PWM_Init(PWMA,DISABLE,Priority_0);
}


void main() {
	int percent = 0;
  int direction = 1;
	int duty_value = 0;

	
	//配置GPIO
	GPIO_Config();

	//打开拓展寄存器使用(pwm专用),且一定要在配置pwm之前打开！！！！！
	EAXSFR();
	
	//配置pwm
	PWM_Config();
	
	//打开全局中断
	EA = 1;
	
  LED_SW = 0;
	
	//LED1 = 0;
	
	while(1) { //此处也可以改成使用定时器来定时获取数据

		percent += direction;
		if(percent == 100) {
		  direction = -1;
		} else if(percent == 0){
			direction = 1;
		}
		
		//更新占空比：参数1：更新哪一个通道或者哪一个组；参数2：占空比的指针变量
		duty_value = PERIOD * percent / 100; //范围0~PERIOD,此值是一直变化的: PERIOD * 百分比
		
		duty.PWM4_Duty = duty_value;
    duty.PWM3_Duty = duty_value;
		duty.PWM2_Duty = duty_value;
		duty.PWM1_Duty = duty_value;
		UpdatePwm(PWMA, &duty);
		
		delay_ms(25); //避免变化太快
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
