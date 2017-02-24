#include"HeadType.h"	


//=============================================================================
//函数名称: Printer_GPIO_Config
//功能概要:打印机引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
 void Printer_GPIO_Config(void)
{	
	//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	//打印机故障输入IO配置
	RCC_APB2PeriphClockCmd(PRINTER_ERR_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_ERR_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_ERR_PORT, &GPIO_InitStructure);
	//打印机打印结束输入IO配置
	RCC_APB2PeriphClockCmd(PRINTER_END_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_END_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_END_PORT, &GPIO_InitStructure);
	//打印机在线输入IO配置
	RCC_APB2PeriphClockCmd(PRINTER_INLINE_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_INLINE_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_INLINE_PORT, &GPIO_InitStructure);
	//打印机标签用完输入IO配置
	RCC_APB2PeriphClockCmd(PRINTER_TAGEND_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_TAGEND_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_TAGEND_PORT, &GPIO_InitStructure);
	//打印机色带用完输入IO配置
	RCC_APB2PeriphClockCmd(PRINTER_COEND_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_COEND_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_COEND_PORT, &GPIO_InitStructure);
	//打印机色带少输入IO配置
	RCC_APB2PeriphClockCmd(PRINTER_COLESS_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_COLESS_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_COLESS_PORT, &GPIO_InitStructure);	
	
	//打印机启动输出IO配置
	RCC_APB2PeriphClockCmd(PRINTER_START_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_START_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_START_PORT, &GPIO_InitStructure);
	//打印机重复启动输出IO配置
	RCC_APB2PeriphClockCmd(PRINTER_RESTART_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_RESTART_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_RESTART_PORT, &GPIO_InitStructure);
	
}






















