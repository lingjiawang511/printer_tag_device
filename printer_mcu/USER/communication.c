#include"HeadType.h"

//=============================================================================
//��������: Comm_GPIO_Config
//���ܸ�Ҫ:Ӳ��ͨ����������
//��������:��
//��������:��
//ע��    :��
//=============================================================================
 void Communication_GPIO_Config(void)
{	
	//����һ��GPIO_InitTypeDef ���͵Ľṹ�壬���ֽ�GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	//COMMUNICATION_IO1  IO����
	RCC_APB2PeriphClockCmd(COMMUNICATION_IO1_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = COMMUNICATION_IO1_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(COMMUNICATION_IO1_PORT, &GPIO_InitStructure);
	//COMMUNICATION_IO2  IO����
	RCC_APB2PeriphClockCmd(COMMUNICATION_IO2_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = COMMUNICATION_IO2_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(COMMUNICATION_IO2_PORT, &GPIO_InitStructure);
	//COMMUNICATION_IO3  IO����
	RCC_APB2PeriphClockCmd(COMMUNICATION_IO3_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = COMMUNICATION_IO3_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(COMMUNICATION_IO3_PORT, &GPIO_InitStructure);

}




















