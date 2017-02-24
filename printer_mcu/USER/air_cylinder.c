#include"HeadType.h"	

//=============================================================================
//��������: Printer_GPIO_Config
//���ܸ�Ҫ:��ӡ����������
//��������:��
//��������:��
//ע��    :��
//=============================================================================
 void Air_Cylinder_GPIO_Config(void)
{	
	//����һ��GPIO_InitTypeDef ���͵Ľṹ�壬���ֽ�GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	//�����ϲ���������IO����
	RCC_APB2PeriphClockCmd(UPPER_REACH_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = UPPER_REACH_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(UPPER_REACH_PORT, &GPIO_InitStructure);
	//�������ϵ�λ����IO����
	RCC_APB2PeriphClockCmd(FIT_REACH_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = FIT_REACH_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(FIT_REACH_PORT, &GPIO_InitStructure);
	//Һ���ź�����IO����
	RCC_APB2PeriphClockCmd(FLUID_BAG_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = FLUID_BAG_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(FLUID_BAG_PORT, &GPIO_InitStructure);
	//ɨ��ǹ�ź�����IO����
	RCC_APB2PeriphClockCmd(SCANNER_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = SCANNER_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SCANNER_PORT, &GPIO_InitStructure);

	//������ѹ���IO����
	RCC_APB2PeriphClockCmd(AIR_CYLINDER_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = AIR_CYLINDER_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(AIR_CYLINDER_PORT, &GPIO_InitStructure);
	//���״������IO����
	RCC_APB2PeriphClockCmd(AIR_BLOW_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = AIR_BLOW_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(AIR_BLOW_PORT, &GPIO_InitStructure);
	//���״������IO����
	RCC_APB2PeriphClockCmd(VACUUM_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = VACUUM_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(VACUUM_PORT, &GPIO_InitStructure);
}






