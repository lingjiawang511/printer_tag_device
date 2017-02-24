#include"HeadType.h"	

//=============================================================================
//函数名称: Printer_GPIO_Config
//功能概要:打印机引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
 void Air_Cylinder_GPIO_Config(void)
{	
	//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	//气缸上部到达输入IO配置
	RCC_APB2PeriphClockCmd(UPPER_REACH_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = UPPER_REACH_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(UPPER_REACH_PORT, &GPIO_InitStructure);
	//气缸贴合到位输入IO配置
	RCC_APB2PeriphClockCmd(FIT_REACH_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = FIT_REACH_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(FIT_REACH_PORT, &GPIO_InitStructure);
	//液袋信号输入IO配置
	RCC_APB2PeriphClockCmd(FLUID_BAG_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = FLUID_BAG_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(FLUID_BAG_PORT, &GPIO_InitStructure);
	//扫描枪信号输入IO配置
	RCC_APB2PeriphClockCmd(SCANNER_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = SCANNER_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SCANNER_PORT, &GPIO_InitStructure);

	//气缸下压输出IO配置
	RCC_APB2PeriphClockCmd(AIR_CYLINDER_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = AIR_CYLINDER_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(AIR_CYLINDER_PORT, &GPIO_InitStructure);
	//气缸吹起输出IO配置
	RCC_APB2PeriphClockCmd(AIR_BLOW_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = AIR_BLOW_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(AIR_BLOW_PORT, &GPIO_InitStructure);
	//气缸吹起输出IO配置
	RCC_APB2PeriphClockCmd(VACUUM_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = VACUUM_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(VACUUM_PORT, &GPIO_InitStructure);
}






