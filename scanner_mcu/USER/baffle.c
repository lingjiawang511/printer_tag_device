#include"HeadType.h"	

//=============================================================================
//��������: Printer_GPIO_Config
//���ܸ�Ҫ:��ӡ����������
//��������:��
//��������:��
//ע��    :��
//=============================================================================
 void Baffle_GPIO_Config(void)
{	
	//����һ��GPIO_InitTypeDef ���͵Ľṹ�壬���ֽ�GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	//�����ⷭ��������IO����
	RCC_APB2PeriphClockCmd(BAFFLE_OUTER_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = BAFFLE_OUTER_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(BAFFLE_OUTER_PORT, &GPIO_InitStructure);
	//�����ڷ���������IO����
	RCC_APB2PeriphClockCmd(BAFFLE_INTER_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = BAFFLE_INTER_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(BAFFLE_INTER_PORT, &GPIO_InitStructure);
	//ɨ��ǹ�ź�����IO����
	RCC_APB2PeriphClockCmd(SCANNER_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = SCANNER_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SCANNER_PORT, &GPIO_InitStructure);

	//�����ŷ����IO����
	RCC_APB2PeriphClockCmd(BAFFLE_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = BAFFLE_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(BAFFLE_PORT, &GPIO_InitStructure);

}






