#include"HeadType.h"	
#include "usart.h"
#include "TIM.h"

void delay_ms1(u16 ms)
{
	u16  i;
	u32  j;
	for(i=ms;i>0;i--)
	{
		for(j=5000;j>0;j--)
		;
	}
}
//配置时钟在target宏定义
int main(void)
{
		delay_init();
		LOCK_GPIO_Config();
	  BEEP_GPIO_Config();
	  SENSOR_GPIO_Config();
		USART1_Config();
		USART2_Config();
		LED_GPIO_Config();
//		USART2_Puts("123456");
//		USART2_Puts("123456");
    TIM2_Config();
    TIM3_Config();
		delay_ms(100);
    while(1){
			Execute_Host_Comm();
			Comm_Upload_state();
		}       
}




