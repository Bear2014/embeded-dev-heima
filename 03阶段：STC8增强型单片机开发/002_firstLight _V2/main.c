#include <intrins.h>

sfr  P3M1 = 0xb1;
sfr  P3M0 = 0xb2;

sfr  P3 = 0xb0;
sbit P34 = P3^4;

void Delay1000ms(void)	//@24.000MHz
{
	 unsigned char data i, j, k;
	
	 int m;
	 for(m=0;m<=11000;m++) {
		  _nop_();
   }	

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

void main() {
	  P3M1 = 1;
	  P3M0 = 0;                                //设置P0.0~P0.7为双向口模式
    
	  while(1) {
			P34 = 1;
			Delay1000ms();
			
			P34 = 0;
			Delay1000ms();
		}
}