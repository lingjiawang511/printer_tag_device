#include"HeadType.h"	
#include "usart.h"
#include "TIM.h"

void param_init(void);
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
		Key_Light_Init();
		Belt_Config();
		LED_GPIO_Config();
	  ROLL_PAPER_GPIO_Config();
	  Printer_GPIO_Config();
		Air_Cylinder_GPIO_Config();
	  Communication_GPIO_Config();
		EXTIX_Init();
    USART1_Config();
    TIM2_Config();
    TIM3_Config();
		param_init();
		delay_ms(1000);
    while(1){
			Respond_Host_Comm();
			Roll_Paper_Control();
			Printer_Control();
			Air_Cylinder_Control();
		}
        
}

void param_init(void)
{
	Air_Control.process = RESERVE;
	Air_Control.complete = 1;
	Air_Control.air_cylinder_position =IN_UP;

	Printer.complete = 0;
	Printer.process = PRINTER_RESERVE;
	PRINTER_START_OFF;
	
	Control.upper_reach.state = 0;
	Control.scanner.state = 0;
	Control.fit_reach.state = 0;
	Control.fluid_bag.state = 0;
	Printer.color_end.state = 0;
	Printer.color_less.state = 0;
	Printer.end.state = 0;
	Printer.err.state = 0;
	Printer.pinline.state = 0;
	Printer.tag_end.state = 0;
	Printer.input_state = 0;
}


