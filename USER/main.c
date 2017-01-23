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
		Belt_Config();
		LED_GPIO_Config();
		Send_Medicine_Config();
		EXTIX_Init();
    USART1_Config();
    TIM2_Config();
    TIM3_Config();
		delay_ms(1000);
    while(1){
			Respond_Host_Comm();
			CH_Send_Medicine();
			CH_Light_Control();
		}
        
}




