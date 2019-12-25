#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "stm32f10x.h"

//FLASH��ʼ��ַ
#define STM32_FLASH_BASE 			0x08000000     //STM32 FLASH����ʼ��ַ
#define FLASH_START_ADDR    	0X08000000
#define APP_OFFSET 					  (0x4000)		
#define FLASH_SAVE_SIZE 			(0X5000)

//�û������Լ�����Ҫ����
#define STM32_FLASH_SIZE 512 	 		//��ѡSTM32��FLASH������С(��λΪK)
#define STM32_FLASH_WREN 1              //ʹ��FLASHд��(0��������;1��ʹ��)
//////////////////////////////////////////////////////////////////////////////////////////////////////

 

u16 STMFLASH_ReadHalfWord(u32 faddr);		  //��������  
void STMFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);	//ָ����ַ��ʼд��ָ�����ȵ�����
u32 STMFLASH_ReadLenByte(u32 ReadAddr,u16 Len);						//ָ����ַ��ʼ��ȡָ����������
FLASH_Status STMFLASH_Write(u32 WriteAddr,u16 NumToWrite,u16 *pBuffer);		//��ָ����ַ��ʼд��ָ�����ȵ�����
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//��ָ����ַ��ʼ����ָ�����ȵ�����

//����д��
void Test_Write(u32 WriteAddr,u16 WriteData);								   
#endif
















