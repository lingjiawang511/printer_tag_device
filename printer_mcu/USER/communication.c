#include"HeadType.h"

MCU_State_Type MCU_State;
Answer_Type 	 PC_Answer;
COMM_Rec_Union_Type  MCU_Host_Rec;
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



////=============================================================================
////��������:SLAVE_Rec_Comm
////���ܸ�Ҫ:PC��ΪͨѶ����ʱ���յĿ����ִ�����Ӧ
////����˵��:��
////��������:��
////ע��    :��
////=============================================================================
//static u8  SLAVE_Rec_Comm(void)
//{
//	u8 i,res;
//	u16 crc;
//	if(Usart1_Control_Data.rx_count < 18){
//		res = 2;
//		return res;
//	}crc=CRC_GetCCITT(Usart1_Control_Data.rxbuf,Usart1_Control_Data.rx_count-4);//֡����β����У��
//	if((Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_count-3]+\
// 	    Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_count-4]*256 == crc)){	    
//		for(i = 0;i < 18;i++){
//            PC_Host_Rec.send_buf[i] = Usart1_Control_Data.rxbuf[i];
//        }//�����ݸ��Ƹ�����ͨѶ�ṹ��
//		switch(PC_Host_Rec.control.ch1_state){
//		case 0x00:
//							Channel.ch1.send_num = 0;
//							Channel.ch1.state = READY;	 
//							break;
//		case 0x01:Channel.ch1.send_num = PC_Host_Rec.control.ch1_num;	
//							Channel.ch1.send_actual = 0;
//							Channel.ch1.state = READY ;
//							PC_Host_Rec.control.ch1_state = 0;
//							break;
//		default : Channel.ch1.send_num = 0;
//							Channel.ch1.state = READY;
//							break;
//		}
//		switch(PC_Host_Rec.control.ch2_state){
//		case 0x00:	
//							Channel.ch2.send_num = 0;
//							Channel.ch2.state = READY;
//							break;
//		case 0x01:Channel.ch2.send_num = PC_Host_Rec.control.ch2_num;	
//							Channel.ch2.send_actual = 0;
//							Channel.ch2.state = READY ;
//							PC_Host_Rec.control.ch2_state = 0;
//							break;
//		default : Channel.ch2.send_num = 0;
//							Channel.ch2.state = READY;
//							break;
//		}
//		switch(PC_Host_Rec.control.ch3_state){
//		case 0x00:
//							Channel.ch3.send_num = 0;
//							Channel.ch3.state = READY;
//							break;
//		case 0x01:Channel.ch3.send_num = PC_Host_Rec.control.ch3_num;	
//							Channel.ch3.send_actual = 0;
//							Channel.ch3.state = READY ;
//							PC_Host_Rec.control.ch3_state = 0;
//							break;
//		default :
//							Channel.ch3.send_num = 0;
//							Channel.ch3.state = READY;
//							break;
//		}
//		switch(PC_Host_Rec.control.ch4_state){
//		case 0x00:	 
//							Channel.ch4.send_num = 0;
//							Channel.ch4.state = READY;
//							break;
//		case 0x01:Channel.ch4.send_num = PC_Host_Rec.control.ch4_num;	
//							Channel.ch4.send_actual = 0;
//							Channel.ch4.state = READY ;
//							PC_Host_Rec.control.ch4_state = 0;
//							break;
//		default :	Channel.ch4.send_num = 0;
//							Channel.ch4.state = READY;
//							break;
//		}
//		switch(PC_Host_Rec.control.belt_state){
//		case 0x00:	 
//							break;
//		case 0x01:belt.send_time = PC_Host_Rec.control.belt_time;	
//							belt.actual_time = belt.send_time *400; //*2s
//							belt.state = READY ;
//							PC_Host_Rec.control.belt_state = 0;
//							break;
//		default : break;
//		}		
//			res = 0;	
//	}else{
//		 res = 1;
//	}
//	Usart1_Control_Data.tx_count = 0;
//	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x01;
//	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x58;
//	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
//	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x02;
//	if(res == 0)//���յ�������ȷ
//	{
//			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x01;
//			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
//			crc=CRC_GetCCITT(Usart1_Control_Data.txbuf,Usart1_Control_Data.tx_count);
//			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = (crc>>8)&0xFF; ;
//			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = crc&0xFF;	
//	}else if(res == 1){//CRCУ�����
//			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
//			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
//			crc=CRC_GetCCITT(Usart1_Control_Data.txbuf,Usart1_Control_Data.tx_count);
//			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = (crc>>8)&0xFF; ;
//			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = crc&0xFF;
//	}
//	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x0D;
//	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x0A;
//	return res;
//}
//=============================================================================
//��������:SLAVE_Rec_Comm
//���ܸ�Ҫ:PC��ΪͨѶ�ӻ�ʱ���յ����ݣ�������
//����˵��:��
//��������:��
//ע��    :�����������λ��ߵȴ����ճ�ʱ�������ٷ��ͣ�����״̬������ת��Ϊ�ӻ�ģʽ
//=============================================================================
static u8  Host_Rec_Comm(void)
{
	u8 i,res;
	u16 crc;
	if(Usart1_Control_Data.rx_count != 10){
		res = 2;
		return res;
	}crc=CRC_GetCCITT(Usart1_Control_Data.rxbuf,Usart1_Control_Data.rx_count-4);
	if((Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_count-3]+\
 	    Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_count-4]*256 == crc)){	    
		for(i = 0;i < 10;i++){
            MCU_Host_Rec.rec_buf[i] = Usart1_Control_Data.rxbuf[i];
        }//�����ݸ��Ƹ�����ͨѶ�ṹ��
		if(MCU_Host_Rec.control.comm_state == 1){//PC��Ӧ����ȷ����������
				res = 0;	
		}else{
				res = 3;
		}
	}else{
		 res = 1;
	}
	return res;
}
//=============================================================================
//��������:Execute_Host_Comm
//���ܸ�Ҫ:ִ����λ������������
//����˵��:��
//��������:��
//ע��    :��
//=============================================================================
static u8 Execute_Host_Comm(void)
{
	u8 res;
	switch(MCU_State){
	case SLAVE:// res = SLAVE_Rec_Comm();
							if(0 == res){
								Usart1_Control_Data.tx_index = 0;
								USART_SendData(USART1,Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_index++]);
								MCU_State = HOST;		//��ȷ���յ�PC�����͵Ŀ�����Ϣ����Ӧ��״̬����Ϊ����ģʽ
							}else if(1 == res){
								Usart1_Control_Data.tx_index = 0;
								USART_SendData(USART1,Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_index++]);
							}
							break;
	case HOST :	res = Host_Rec_Comm();
							if(( res== 1)||(res == 3)){//����û����ȷ���յ����ݣ����·�������
								Usart1_Control_Data.tx_index = 0;
								Usart1_Control_Data.tx_count = 16;	
								PC_Answer.Nanswer_timeout = NANSWER_TIME;
								if(PC_Answer.answer_numout==0){
									MCU_State = SLAVE;
									PC_Answer.Nanswer_timeout = NANSWER_TIME;
									PC_Answer.answer_numout = NANSWER_NUMOUT;
									PC_Answer.answer_state = 0;
								}else{
									PC_Answer.answer_numout--;
								}
								USART_SendData(USART1,Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_index++]);//ԭ��������û�ı䣬����ֱ�ӷ���
							}else if(res == 0){
								PC_Answer.answer_state = 0;	
								MCU_State = SLAVE;		//��ȷ���յ�PC�����͵Ľ���״̬��Ϣ��ת��Ϊ�ӻ��ȴ���һ��PC���Ϳ�����Ϣ
								PC_Answer.Nanswer_timeout = NANSWER_TIME;
								PC_Answer.answer_numout = NANSWER_NUMOUT;
							}
						break;
	default :MCU_State = SLAVE;		
					 break ;
	}
	return res;
}

//=============================================================================
//��������:Respond_Host_Comm
//���ܸ�Ҫ:��Ӧ��λ���ķ�����������������Ѿ��Ӵ���һ��������
//����˵��:��
//��������:��
//ע��    :��
//=============================================================================
void Respond_Host_Comm(void)
{
    if (1 == Usart1_Control_Data.rx_aframe){    
				Execute_Host_Comm();		
				Usart1_Control_Data.rx_count = 0;
				Auto_Frame_Time1 = AUTO_FRAME_TIMEOUT1;
				Usart1_Control_Data.rx_aframe = 0;
    }else{
        return;
    }
}

















