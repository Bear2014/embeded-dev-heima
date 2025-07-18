#include "lib/STC8G_H_GPIO.h"
#include "lib/STC8G_H_Delay.h"
#include "lib/STC8G_H_UART.h"
#include "lib/STC8G_H_Switch.h"
#include "lib/STC8G_H_ADC.h"
#include "lib/STC8G_H_NVIC.h"


void GPIO_Config();
void uart_Config();
void ADC_Config();
int search_temp_table(int);


void main() {
	  u16 adc_value;
	  float v_res,o_res;
	  int cur_temp;

		EA = 1;
	  GPIO_Config();
	
	  uart_Config();
	
	  ADC_Config();
	  
	  printf("start...\n");
	
	
	  while(1) {
			
			//1.获取P04引脚的测量值
			adc_value = Get_ADCResult(ADC_CH12);
			printf("adc_value=%d\n",adc_value);
			
			//2.换算成电压
			v_res = adc_value * 2.5 / 4096;
			printf("v_res=%.2fv\n", v_res);
			
			/**
			 * 3.计算电阻
			 * 公式：串联电路，分压
			 *  3.3v - ntc电压  ntc电压
			 *  ------------ = --------
			 *      1Ok         ntc电阻
			 */
			 o_res = v_res * 10 / (3.3 - v_res);
			 printf("o_res=%.2fv\n", o_res);
			 
			 //4.最后根据的得到的电阻查表查出当前的温度
			cur_temp = search_temp_table(o_res*100) - 55;
			printf("cur_temp=%d\n",cur_temp);
			
			delay_ms(250);
			delay_ms(250);
			delay_ms(250);
			delay_ms(250);
		}
	
}



//配置P04
void GPIO_Config() {
	GPIO_InitTypeDef gpio_init;
	gpio_init.Mode = GPIO_HighZ; //设置为高阻输出
	gpio_init.Pin = GPIO_Pin_4;
	GPIO_Inilize(GPIO_P0,&gpio_init);
}



//配置串口
void uart_Config() {
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



//配置ADC
void ADC_Config(){
	ADC_InitTypeDef adc_init;
	
	adc_init.ADC_SMPduty = 31;		//ADC 模拟信号采样时间控制, 0~31（注意： SMPDUTY 一定不能设置小于 10）
	adc_init.ADC_Speed = ADC_SPEED_2X1T;			//设置 ADC 工作时钟频率	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	
	//adc采集出来的数据只有12位，装这个采集数据，采用16位来装
	adc_init.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC结果调整,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	adc_init.ADC_CsSetup = 0;		//ADC 通道选择时间控制 0(默认),1
	adc_init.ADC_CsHold = 1;
	
	ADC_Inilize(&adc_init);
	
	//电源使用
	ADC_PowerControl(ENABLE);
	
	//中断使用
	//NVIC_ADC_Init(DISABLE,Priority_1); //中断使能，一般不写，写了会看到不一样的结果！！！！，ADC不能打开中断！！！
}


//配置温度遍历表 关键字：code xdata 
u16 xdata temp_table[]= {
	58354, // -55
	55464, // -54
	52698, // -53
	50048, // -52
	47515, // -51
	45097, // -50
	42789, // -49
	40589, // -48
	38492, // -47
	36496, // -46
	34597, // -45
	32791, // -44
	31075, // -43
	29444, // -42
	27896, // -41
	26427, // -40
	25034, // -39
	23713, // -38
	22460, // -37
	21273, // -36
	20148, // -35
	19083, // -34
	18075, // -33
	17120, // -32
	16216, // -31
	15361, // -30
	14551, // -29
	13785, // -28
	13061, // -27
	12376, // -26
	11728, // -25
	11114, // -24
	10535, // -23
	9986,  // -22
	9468,  // -21
	8977,  // -20
	8513,  // -19
	8075,  // -18
	7660,  // -17
	7267,  // -16
	6896,  // -15
	6545,  // -14
	6212,  // -13
	5898,  // -12
	5601,  // -11
	5319,  // -10
	5053,  // -9
	4801,  // -8
	4562,  // -7
	4336,  // -6
	4122,  // -5
	3920,  // -4
	3728,  // -3
	3546,  // -2
	3374,  // -1
	3211,  // 0
	3057,  // 1
	2910,  // 2
	2771,  // 3
	2639,  // 4
	2515,  // 5
	2396,  // 6
	2284,  // 7
	2177,  // 8
	2076,  // 9
	1978,  // 10
	1889,  // 11
	1802,  // 12
	1720,  // 13
	1642,  // 14
	1568,  // 15
	1497,  // 16
	1430,  // 17
	1366,  // 18
	1306,  // 19
	1248,  // 20
	1193,  // 21
	1141,  // 22
	1092,  // 23
	1044,  // 24
	1000,  // 25
	957,   // 26
	916,   // 27
	877,   // 28
	840,   // 29
	805,   // 30
	771,   // 31
	739,   // 32
	709,   // 33
	679,   // 34
	652,   // 35
	625,   // 36
	600,   // 37
	576,   // 38
	552,   // 39
	530,   // 40
	509,   // 41
	489,   // 42
	470,   // 43
	452,   // 44
	434,   // 45
	417,   // 46
	401,   // 47
	386,   // 48
	371,   // 49
	358,   // 50
	344,   // 51
	331,   // 52
	318,   // 53
	306,   // 54
	295,   // 55
	284,   // 56
	274,   // 57
	264,   // 58
	254,   // 59
	245,   // 60
	236,   // 61
	228,   // 62
	220,   // 63
	212,   // 64
	205,   // 65
	198,   // 66
	191,   // 67
	184,   // 68
	178,   // 69
	172,   // 70
	166,   // 71
	160,   // 72
	155,   // 73
	150,   // 74
	145,   // 75
	140,   // 76
	135,   // 77
	131,   // 78
	126,   // 79
	122,   // 80
	118,   // 81
	115,   // 82
	111,   // 83
	107,   // 84
	104,   // 85
	101,   // 86
	97,    // 87
	94,    // 88
	91,    // 89
	89,    // 90
	86,    // 91
	83,    // 92
	81,    // 93
	78,    // 94
	76,    // 95
	74,    // 96
	71,    // 97
	69,    // 98
	67,    // 99
	65,    // 100
	63,    // 101
	61,    // 102
	60,    // 103
	58,    // 104
	56,    // 105
	55,    // 106
	53,    // 107
	52,    // 108
	50,    // 109
	49,    // 110
	47,    // 111
	46,    // 112
	45,    // 113
	43,    // 114
	42,    // 115
	41,    // 116
	40,    // 117
	39,    // 118
	38,    // 119
	37,    // 120
	36,    // 121
	35,    // 122
	34,    // 123
	33,    // 124
	32,    // 125
};


//检查温度表
int search_temp_table(res_RX10) {
  int i,min_index=0;
	float current_abs=0.00;
	
	int len = sizeof(temp_table) / sizeof(u16);
	
	float min_abs = abs(res_RX10 - temp_table[0]);
	for(i=1;i<len;i++) {
		float current_abs = abs(res_RX10 - temp_table[i]);
		if(min_abs > current_abs) {
			 min_abs = current_abs;
			 min_index = i;
		} 
	}
	
	return min_index;
}