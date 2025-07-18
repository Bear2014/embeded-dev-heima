#include "stc8h.h"

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

void main() {
	
	  P3M1 &= ~0x10, P3M0 &= ~0x10;  //准双向
//	  P3M1 &= ~0x10, P3M0 |= 0x10;  //推挽输出
//	  P3M1 |= 0x10, P3M0 &= ~0x10;  //高阻
//	  P3M1 |= 0x10, P3M0 |= 0x10;  //开漏

//	  P3M1 = 0x00, P3M0 = 0x00;  //准双向
//	  P3M1 = 0x00, P3M0 = 0x10;  //推挽输出
//	  P3M1 = 0x10, P3M0 = 0x00;  //高阻
//	  P3M1 = 0x10, P3M0 = 0x10;  //开漏
	
	
	  while(1) {
			P34 = 1;
			Delay1000ms();
			
			P34 = 0;
			Delay1000ms();
		}
}