#include"HeadType.h"	

//=============================================================================
//函数名称: Printer_GPIO_Config
//功能概要:打印机引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
 void Baffle_GPIO_Config(void)
{	
	//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	//翻板外翻到达输入IO配置
	RCC_APB2PeriphClockCmd(BAFFLE_OUTER_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = BAFFLE_OUTER_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(BAFFLE_OUTER_PORT, &GPIO_InitStructure);
	//翻板内翻到达输入IO配置
	RCC_APB2PeriphClockCmd(BAFFLE_INTER_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = BAFFLE_INTER_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(BAFFLE_INTER_PORT, &GPIO_InitStructure);
	//扫描枪信号输入IO配置
	RCC_APB2PeriphClockCmd(SCANNER_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = SCANNER_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SCANNER_PORT, &GPIO_InitStructure);

	//翻板电磁阀输出IO配置
	RCC_APB2PeriphClockCmd(BAFFLE_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = BAFFLE_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(BAFFLE_PORT, &GPIO_InitStructure);

}






