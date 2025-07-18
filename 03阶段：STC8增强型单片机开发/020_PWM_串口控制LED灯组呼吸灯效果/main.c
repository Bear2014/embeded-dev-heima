#include "STC8h.h"
#include "lib/Config.h"
#include "lib/STC8G_H_GPIO.h"
#include "lib/STC8G_H_Delay.h"
#include "lib/STC8G_H_NVIC.h"
#include "lib/STC8G_H_Switch.h"
#include "lib/STC8H_PWM.h"
#include "lib/STC8G_H_UART.h"

void GPIO_Config();
void UART_Config();
void uart1_recv_dat();

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
	
	  //配置PWM4：对应P27 P26 -->这个配置就是低电平0%
	  pwm_init.PWM_Mode = CCMRn_PWM_MODE2; //底电平
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
	  pwm_init.PWM_Mode = CCMRn_PWM_MODE1;
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

int percent = 0;
int duty_value = 0;
//int direction = 1;
void main() {
	
	//配置GPIO
	GPIO_Config();
	
	UART_Config();

	//打开拓展寄存器使用(pwm专用),且一定要在配置pwm之前打开！！！！！
	EAXSFR();
	
	//配置pwm
	PWM_Config();
	
	//打开全局中断
	EA = 1;
	
  LED_SW = 0;
	
	//LED1 = 0;
	
	while(1) { //此处也可以改成使用定时器来定时获取数据

    /*
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
		*/

		
		uart1_recv_dat();
		
		//delay_ms(25); //避免变化太快
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


//配置串口
void UART_config(void) {
    COMx_InitDefine		COMx_InitStructure;					//结构定义

    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;			//波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
    UART_Configuration(UART1, &COMx_InitStructure);		//初始化串口1 UART1,UART2,UART3,UART4
	
	
    NVIC_UART1_Init(ENABLE,Priority_1);		//中断使能, ENABLE\DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
    
    UART1_SW(UART1_SW_P30_P31);		//UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
}

//接收串口数据
void uart1_recv_dat() {
	  u32 duty_value;
	 
		if(COM1.RX_Cnt > 0) {

			if(RX1_Buffer[0] == 0x00) { //led逐渐边亮
				 percent += 1;
				 if(percent > 100) {
					 percent = 100;
				 }
			}
			
			if(RX1_Buffer[0] == 0x01) { //led逐渐变暗
				 percent -= 1;
				 if(percent < 0) {
					 percent = 0;
				 }
			}
			
			//已经把数据处理好了，计数就要归0
			COM1.RX_Cnt = 0;
			
			printf("percent: %d \n", (int)percent);

			duty_value = PERIOD * percent / 100; //范围0~PERIOD,此值是一直变化的: PERIOD * 百分比
			duty.PWM4_Duty = duty_value;
      duty.PWM3_Duty = duty_value;
		  duty.PWM2_Duty = duty_value;
		  duty.PWM1_Duty = duty_value;
		  UpdatePwm(PWMA, &duty);
		}
}

