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
		Baffle_GPIO_Config();
		USART1_Config();
		USART2_Config();
		EXTIX_Init();
		LED_GPIO_Config();
    TIM2_Config();
    TIM3_Config();
		delay_ms(100);
    while(1){
        Dispose_Data_For_Host();
        Respond_Host_Comm();
		}       
}




