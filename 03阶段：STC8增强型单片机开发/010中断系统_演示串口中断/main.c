sfr		P3M1 	= 0xb1;  // 这四个对应的灯地址不对，所以
sfr		P3M0 	= 0xb2;
sfr		P3 		= 0xb0;
sbit	P34		= P3^4;

sfr     T2L     =   0xd7;
sfr     T2H     =   0xd6;
sfr     AUXR    =   0x8e;

sfr		IE		= 0xA8;
sbit	EA		= IE^7;
sbit	ES		= IE^4;

sfr		SCON	= 0x98;
sfr		SBUF	= 0x99;
sbit	RI		= SCON^0;
sbit	TI		= SCON^1;


//当TI = 1的时候，会自动触发此中断函数
void uart_hello(void) interrupt 4 {
	if(RI) {
    // 如果接收寄存器RI触发了中断，打开灯
		RI = 0;
		P34 = 1;//开
	} 
	
	if(TI) {
        // 如果发送寄存器TI触发了中断，关掉灯
		TI = 0;
		P34 = 0;//关
	}
}


void Delay1000ms(void)	//@24.000MHz
{
	unsigned char data i, j, k;
	
	i = 122;
	j = 193;
	k = 128;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

int main() {
	P3M1 &= ~0x08,	P3M0 |=  0x08; //推挽输出
	
	SCON = 0x50;
	T2L = 0xe8; //65536-11059200/115200/4=0FFE8H
	T2H = 0xff;
	AUXR = 0x15;//启动定时器
	
	EA = 1; //全局中断
	ES = 1;
	
	P34 = 0;
	
	while(1) {
        // 休眠1000ms
		Delay1000ms();
		Delay1000ms();
		Delay1000ms();
		Delay1000ms();
		Delay1000ms();
        // 发送一个数据0x11
		SBUF = 0x11;
        // 将TI位寄存器置为1 (这里可以不设置, 只要给SBUF赋值了, TI也会自动变为1)
		TI = 1;
	}
}