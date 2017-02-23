#include"HeadType.h"
/********************ȫ�ֱ�������****************/

//=====================����======================
unsigned char static ComSet[]={0x03, COMM_CONTROL_ANTENNA, 0x03};
 //���ô����ߺ͹ر��Զ�ѭ��
unsigned char static ComSearchCard[]={0x03,COMM_MIFARE_SEARCH_CARD, 0x00};
//Ѱ�����������
//unsigned char static cReadBlock[]={0x0A,COMM_READ_BLOCK, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
//����No.3��1����������Ϳ�����
//unsigned char static ComReadBlock3[]={0x0A,COMM_READ_BLOCK,0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
//����No.1
unsigned char static ComReadBlock1[]={0x0A,COMM_READ_BLOCK,0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
//д��No.1
unsigned char static ComWriteBlock1[]={0X1A,COMM_WRITE_BLOCK, 
	   								0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
       								0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
       								0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

//��ʼ��Ǯ��No.5 ��ֵΪ0x12345678
unsigned char static ComIntiPurse5[]={0x0E,COMM_INIT_PURSE, 
	                                0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 
									0x00, 0x00, 0x00, 0x00};
								    //0xff, 0xff, 0xff, 0x7f};//YZ MAX:0x7FFFFFFF
									//0x00, 0x00, 0x00, 0x80};

//��Ǯ����ֵNo.5
unsigned char static ComReadPurse5[]={0x0A,COMM_READ_PURSE,
									0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 0xff,0xff};

//��Ǯ����ֵNo.6
unsigned char static ComReadPurse6[]={0x0A,COMM_READ_PURSE,
									0x00, 0x06, 0xff, 0xff, 0xff, 0xff, 0xff,0xff};

//Ǯ��ֵ��2	    
unsigned char static ComIncrPurse5[]={0x0E,COMM_INC_VALUE, 
	   								0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
									0x02, 0x00, 0x00, 0x00};
									//0xff, 0xff, 0xff, 0x7f};//YZ MAX:0x7FFFFFFF
									//0x00, 0x00, 0x00, 0x80};
//Ǯ��ֵ��1
unsigned char static ComDecrPurse5[]={0x0E,COMM_DEC_VALUE, 
									0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
									0x01, 0x00, 0x00, 0x00};
									//0xff, 0xff, 0xff, 0x7f};//YZ MAX:0x7FFFFFFF
									//0x00, 0x00, 0x00, 0x80};
//Ǯ������
unsigned char static ComBakPurse56[]={0x0B,COMM_BAK_PURSE, 
	   								0x00, 0x05, 0x06, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
//��Ƭ����
unsigned char static ComHaltCard[]={0x02,COMM_CARD_HALT,0x09};  
//����ģ�����˯��ģʽ
unsigned char static ComHaltMCU[]={0x02,COMM_SET_MCU_IDLE,0x03};	
unsigned char static ComSelfSearchCard[]={0x02,COMM_SELF_SEARCH_CARD,0x0E};

RFID_REC_Type Usart2_RFIDRec;
RFID_REC_Type Usart3_RFIDRec;

USART_WORK_Type Usart_Work_State;					//MCU��Ϊ�������Ǵӻ�״̬
Answer_Type 	 PC_Answer;
COMM_Rec_Union_Type   MCU_Host_Rec;//MCU��Ϊ����ʱ�Ľṹ�����Ӧ�����
COMM_Send_Union_Type  MCU_Host_Send;//MCU��Ϊ����ʱ�Ľṹ�巢������
//=============================================================================
//��������: check_xor_sum
//���ܸ�Ҫ:����У�麯��
//��������:��
//��������:����У����
//ע��    :��
//=============================================================================
static u8 check_xor_sum(u8 len,u8 *pdata){
	u8 checksum=0;
		while(len)
	{
	  checksum ^= (*pdata);
	  pdata++;
	  len--;
	}

	return checksum;
}
//=============================================================================
//��������:Usart2_Send_RFIDCmd
//���ܸ�Ҫ:����2����RFID����
//��������:len:�������ֳ��ȡ�pdata:������
//��������:��
//ע��    :��
//=============================================================================
static void Usart2_Send_RFIDCmd(unsigned char len,unsigned char *pdata)
{
		u8 i;
		Usart2_Control_Data.tx_count = 0;
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = 0x00;
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = 0x00;
		for(i=0;i<len;i++){
			Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = *pdata++;
		}
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = check_xor_sum(len,&Usart2_Control_Data.txbuf[2]);
  	Usart2_Control_Data.tx_index = 0;
		USART_SendData(USART2,Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_index++]);
	
}
//=============================================================================
//��������:Usart3_Send_RFIDCmd
//���ܸ�Ҫ:����3����RFID����
//��������:len:�������ֳ��ȡ�pdata:������
//��������:��
//ע��    :��
//=============================================================================
static void Usart3_Send_RFIDCmd(unsigned char len,unsigned char *pdata)
{
		u8 i;
	 static u8 test = 0;
		Usart3_Control_Data.tx_count = 0;
		Usart3_Control_Data.txbuf[Usart3_Control_Data.tx_count++] = 0x00;
		Usart3_Control_Data.txbuf[Usart3_Control_Data.tx_count++] = 0x00;
		for(i=0;i<len;i++){
			Usart3_Control_Data.txbuf[Usart3_Control_Data.tx_count++] = *pdata++;
		}
		test = check_xor_sum(len,&Usart3_Control_Data.txbuf[2]);
		Usart3_Control_Data.txbuf[Usart3_Control_Data.tx_count++] = test;
  	Usart3_Control_Data.tx_index = 0;
		USART_SendData(USART3,Usart3_Control_Data.txbuf[Usart3_Control_Data.tx_index++]);
	
}
//=============================================================================
//��������:Do_Usrat2_RFIDCmd
//���ܸ�Ҫ:������2����RFID����
//��������:cmd:����
//��������:��
//ע��    :��
//=============================================================================
void Do_Usrat2_RFIDCmd(u8 cmd )
{
	switch(cmd){
	case COMM_SET_MCU_IDLE: //����ģ�����˯��ģʽ
		Usart2_Send_RFIDCmd(ComHaltMCU[0],ComHaltMCU);break ;
	case COMM_CONTROL_ANTENNA://ģ�����߿��ơ��Զ�Ѱ������
		Usart2_Send_RFIDCmd(ComSet[0],ComSet);break ;
	case COMM_MIFARE_SEARCH_CARD://TYPE-AѰ��
		Usart2_Send_RFIDCmd(ComSearchCard[0],ComSearchCard);break ;
	case COMM_READ_BLOCK: //����
		Usart2_Send_RFIDCmd(ComReadBlock1[0],ComReadBlock1);break ;
	case COMM_WRITE_BLOCK://д��
		Usart2_Send_RFIDCmd(ComWriteBlock1[0],ComWriteBlock1);break ;
	case COMM_INIT_PURSE:  //��ʼ��Ǯ��
		Usart2_Send_RFIDCmd(ComIntiPurse5[0],ComIntiPurse5);break ;
	case COMM_READ_PURSE://��ȡǮ��
		Usart2_Send_RFIDCmd(ComReadPurse5[0],ComReadPurse5);break ;
	case COMM_INC_VALUE://��ֵ
		Usart2_Send_RFIDCmd(ComIncrPurse5[0],ComIncrPurse5);break ;
	case COMM_DEC_VALUE: //�ۿ�
		Usart2_Send_RFIDCmd(ComDecrPurse5[0],ComDecrPurse5);break ;
	case COMM_BAK_PURSE:  //����Ǯ��ֵ
		Usart2_Send_RFIDCmd(ComBakPurse56[0],ComBakPurse56);break ;
	case COMM_CARD_HALT://������
		Usart2_Send_RFIDCmd(ComHaltCard[0],ComHaltCard);break ;
	case COMM_SELF_SEARCH_CARD:
		Usart2_Send_RFIDCmd(ComSelfSearchCard[0],ComSelfSearchCard);break ;
	default :break ;
	}	
}
//=============================================================================
//��������:Do_Usrat3_RFIDCmd
//���ܸ�Ҫ:������3����RFID����
//��������:cmd:����
//��������:��
//ע��    :��
//=============================================================================
void Do_Usrat3_RFIDCmd(u8 cmd )
{
	switch(cmd){
	case COMM_SET_MCU_IDLE: //����ģ�����˯��ģʽ
		Usart3_Send_RFIDCmd(ComHaltMCU[0],ComHaltMCU);break ;
	case COMM_CONTROL_ANTENNA://ģ�����߿��ơ��Զ�Ѱ������
		Usart3_Send_RFIDCmd(ComSet[0],ComSet);break ;
	case COMM_MIFARE_SEARCH_CARD://TYPE-AѰ��
		Usart3_Send_RFIDCmd(ComSearchCard[0],ComSearchCard);break ;
	case COMM_READ_BLOCK: //����
		Usart3_Send_RFIDCmd(ComReadBlock1[0],ComReadBlock1);break ;
	case COMM_WRITE_BLOCK://д��
		Usart3_Send_RFIDCmd(ComWriteBlock1[0],ComWriteBlock1);break ;
	case COMM_INIT_PURSE:  //��ʼ��Ǯ��
		Usart3_Send_RFIDCmd(ComIntiPurse5[0],ComIntiPurse5);break ;
	case COMM_READ_PURSE://��ȡǮ��
		Usart3_Send_RFIDCmd(ComReadPurse5[0],ComReadPurse5);
		Usart3_Send_RFIDCmd(ComReadPurse5[0],ComReadPurse6);break ;
	case COMM_INC_VALUE://��ֵ
		Usart3_Send_RFIDCmd(ComIncrPurse5[0],ComIncrPurse5);break ;
	case COMM_DEC_VALUE: //�ۿ�
		Usart3_Send_RFIDCmd(ComDecrPurse5[0],ComDecrPurse5);break ;
	case COMM_BAK_PURSE:  //����Ǯ��ֵ
		Usart3_Send_RFIDCmd(ComBakPurse56[0],ComBakPurse56);break ;
	case COMM_CARD_HALT://������
		Usart3_Send_RFIDCmd(ComHaltCard[0],ComHaltCard);break ;
	case COMM_SELF_SEARCH_CARD:
		Usart3_Send_RFIDCmd(ComSelfSearchCard[0],ComSelfSearchCard);break ;
	default :break ;
	}
}
//=============================================================================
//��������:Usrat2_Rec_RFIDdata
//���ܸ�Ҫ:����2���յ���RFID����
//����˵��:��
//��������:��
//ע��    :��
//=============================================================================
static u8 Usrat2_Rec_RFIDdata(void )
{
	u8 i,res;
	u16 crc;
	if(Usart2_Control_Data.rx_aframe == 1){
		if((Usart2_Control_Data.rx_count < 8)||(Usart2_Control_Data.rxbuf[0] != 0xFE)||(Usart2_Control_Data.rxbuf[2] != 0x03)){//���յ�������λ���ڰ�λ��������ͷ�����ǲ�������
			Usart2_Control_Data.rx_aframe = 0;
			res = 1;
			return res;
		}
		if(Usart2_Control_Data.rxbuf[7] !=check_xor_sum(6,&Usart2_Control_Data.rxbuf[1])){
			Usart2_Control_Data.rx_aframe = 0;
			res = 1;
			return res;
		}
		for(i=0;i<4;i++){
			Usart2_RFIDRec.data[i] = Usart2_Control_Data.rxbuf[i+3];
		}
		Usart1_Control_Data.tx_count = 0;	
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x01;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x58;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x10;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x01;//����RFID����
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Usart2_RFIDRec.data[0];
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Usart2_RFIDRec.data[1];
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Usart2_RFIDRec.data[2];
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Usart2_RFIDRec.data[3];	
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Lock.lock1.lock_check_value;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Lock.lock2.lock_check_value;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Lock.lock3.lock_check_value;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Lock.lock4.lock_check_value;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
		crc=CRC_GetCCITT(Usart1_Control_Data.txbuf,Usart1_Control_Data.tx_count);
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = (crc>>8)&0xFF; 
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = crc&0xFF;
		
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0X0D;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0X0A;
		
		PC_Answer.Nanswer_timeout = NANSWER_TIME;
		PC_Answer.answer_numout = NANSWER_NUMOUT;
		PC_Answer.answer_state = 1;
		Usart1_Control_Data.tx_index = 0;	
		USART_SendData(USART1,Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_index++]);
//		Usart_Work_State = USART2_WORK; //˭�Ƚ��յ�����˭�ȴ���
		Usart2_Control_Data.rx_aframe = 0;
		for(i=0;i<4;i++){
			Usart2_RFIDRec.data[i] = 0;
		}
		res = 0;
	}else{
		res = 1;
	}
	return res;
}
#if 0
//=============================================================================
//��������:Usrat2_Rec_RFIDdata
//���ܸ�Ҫ:����2���յ���RFID����
//����˵��:��
//��������:��
//ע��    :��
//=============================================================================
static u8 Usrat3_Rec_RFIDdata(void )
{
	u8 i,res;
	u16 crc;
	if(Usart3_Control_Data.rx_aframe == 1){
		if((Usart3_Control_Data.rx_count < 8)||(Usart3_Control_Data.rxbuf[0] != 0xFE)||(Usart3_Control_Data.rxbuf[2] != 0x03)){//���յ�������λ���ڰ�λ��������ͷ�����ǲ�������
			Usart3_Control_Data.rx_aframe = 0;
			res = 1;
			return res;
		}
		if(Usart3_Control_Data.rxbuf[7] !=check_xor_sum(6,&Usart3_Control_Data.rxbuf[1])){
			Usart3_Control_Data.rx_aframe = 0;
			res = 1;
			return res;
		}
		for(i=0;i<4;i++){
			Usart3_RFIDRec.data[i] = Usart3_Control_Data.rxbuf[i+3];
		}
		while(Usart1_Control_Data.tx_count != 0); //��һ�����ݱ��봫����ɲſ�����һ�δ���
		Usart1_Control_Data.tx_count = 0;	
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x01;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x58;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x05;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x02;//����ͨ����
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Usart3_RFIDRec.data[0];
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Usart3_RFIDRec.data[1];
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Usart3_RFIDRec.data[2];
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Usart3_RFIDRec.data[3];	
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
		crc=CRC_GetCCITT(Usart1_Control_Data.txbuf,Usart1_Control_Data.tx_count);
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = (crc>>8)&0xFF; 
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = crc&0xFF;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0X0D;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0X0A;
		
		PC_Answer.Nanswer_timeout = NANSWER_TIME;
		PC_Answer.answer_numout = NANSWER_NUMOUT;
		PC_Answer.answer_state = 1;
		Usart1_Control_Data.tx_index = 0;	
		USART_SendData(USART1,Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_index++]);
		Usart_Work_State = USART3_WORK; //˭�Ƚ��յ�����˭�ȴ���
		Usart3_Control_Data.rx_aframe = 0;
		Usart1_Control_Data.rx_aframe = 0;	//��պ�������ͨѶ������ͨѶ����
		Usart1_Control_Data.rx_count = 0;
		res = 0;
	}else{
		res = 1;
	}
	return res;
}

#endif
//=============================================================================
//��������:Respond_Host_Comm
//���ܸ�Ҫ:��Ӧ��λ���ķ�����������������Ѿ��Ӵ���һ��������
//����˵��:��
//��������:��
//ע��    :��
//=============================================================================
u8 Respond_Host_Comm(void)
{
		u8 i,res;
		u16 crc;   
			if(Usart1_Control_Data.rx_count != 14){
//				res = 2;
				res = 0;
				return res;
			}crc=CRC_GetCCITT(Usart1_Control_Data.rxbuf,Usart1_Control_Data.rx_count-4);
			if((Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_count-3]+\
					Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_count-4]*256 == crc)){	    
				for(i = 0;i < 14;i++){
								MCU_Host_Rec.rec_buf[i] = Usart1_Control_Data.rxbuf[i];
						}//�����ݸ��Ƹ�����ͨѶ�ṹ��
					switch(MCU_Host_Rec.control.lock1){
						case 0x00: break;    //������
						case 0x01: 					
					        	LOCK1_ON;										//ִ�п�����ƶ���,�����ú��ٵ��
										Lock.lock1.lock_state = 1;
										Lock.lock1.lock_time = LOCK_TIME;
					        	break;   //����1
						default :break;
					}
					switch(MCU_Host_Rec.control.lock2){
						case 0x00: break;    //������
						case 0x01:
					        	LOCK2_ON;										//ִ�п�����ƶ���,�����ú��ٵ��
										Lock.lock2.lock_state = 1;
										Lock.lock2.lock_time = LOCK_TIME;
					        	break;   //����2
						default :break;
					}
					switch(MCU_Host_Rec.control.lock3){
						case 0x00: break;    //������
						case 0x01: 
					        	LOCK3_ON;										//ִ�п�����ƶ���,�����ú��ٵ��
										Lock.lock3.lock_state = 1;
										Lock.lock3.lock_time = LOCK_TIME;
					        	break;   //����3
						default :break;
					}
					switch(MCU_Host_Rec.control.lock4){
						case 0x00: break;    //������
						case 0x01:
					        	LOCK4_ON;										//ִ�п�����ƶ���,�����ú��ٵ��
										Lock.lock4.lock_state = 1;
										Lock.lock4.lock_time = LOCK_TIME;
					        	break;   //����4
						default :break;
					}
					switch(MCU_Host_Rec.control.RFID){
						case 0x00: break;    //������
						case 0x01:  Beep_Num = BEEP_RIGHT_COUNT;  break;     //RFID��ȷ������������ʾһ��
						case 0x02:	Beep_Num = BEEP_ERROR_COUNT;break;  //RFID��ȷ������������ʾһ��
						default :break;
					}
					switch(MCU_Host_Rec.control.check){
						case 0x00: break;    //������
						case 0x01: Check_State = 1; break;   //���״̬�������ϴ�
						default :break;
					}
					for(i = 0;i < 14;i++){
								MCU_Host_Rec.rec_buf[i] = 0x00;
						}//������֮�󽫿�����������
				}else{
//				 res = 1;
					res = 0;
			}
		res = 0;	
		return res;
}
//=============================================================================
//��������:Execute_Host_Comm
//���ܸ�Ҫ:ִ����λ������������
//����˵��:��
//��������:��
//ע��    :��
//=============================================================================
u8 Execute_Host_Comm(void)
{
	u8 res;
		res = Usrat2_Rec_RFIDdata();//��RFID�ź�ʱ������Ӧ��״̬���ȴ�PC�������ݺ���Ӧ
		if (1 == Usart1_Control_Data.rx_aframe){ 
				res=Respond_Host_Comm();   //�����ջ���Ӧ������ÿ��res���ǵ���0
				Usart1_Control_Data.rx_count = 0;
				Auto_Frame_Time1 = AUTO_FRAME_TIMEOUT1;
				Usart1_Control_Data.rx_aframe = 0;
		}
	return res;
}

//=============================================================================
//��������:Send_Medicine_Time_ISR
//���ܸ�Ҫ:ͨѶ��ʱ�򳬴�������
//��������:��
//��������:��
//ע��    :��
//=============================================================================
void PC_Communication_Time_ISR(void )
{
	if(PC_Answer.answer_state == 1){
		if(PC_Answer.Nanswer_timeout > 0){
				PC_Answer.Nanswer_timeout--;
		}else{//������ʱû����Ӧ������ȷӦ����MCUת��Ϊ�ӻ�ģʽ��
				Usart_Work_State = NO_USART_WORK;	
				PC_Answer.Nanswer_timeout = NANSWER_TIME;
				PC_Answer.answer_numout = NANSWER_NUMOUT;
				PC_Answer.answer_state = 0;	
				Usart2_Control_Data.rx_aframe = 0;	//�����PCͨѶ��������ˢ����ͨѶ������ֱ����Ӧ����
//				Usart3_Control_Data.rx_aframe = 0;			
		}
		if(PC_Answer.answer_numout > 0){
				PC_Answer.answer_numout=PC_Answer.answer_numout;//�Լ�������������
		}else{//MCU������N��������û����Ӧ��ȷ��Ӧ�𣬵���ȷӦ����MCUת��Ϊ�ӻ�ģʽ��
				Usart_Work_State = NO_USART_WORK;	
				PC_Answer.Nanswer_timeout = NANSWER_TIME;
				PC_Answer.answer_numout = NANSWER_NUMOUT;
				Usart2_Control_Data.rx_aframe = 0;	//�����PCͨѶ��������ˢ����ͨѶ������ֱ����Ӧ����
//				Usart3_Control_Data.rx_aframe = 0;
				PC_Answer.answer_state = 0;				
		}
	}
}

//=============================================================================
//��������:Comm_Upload_state
//���ܸ�Ҫ:ͨѶ�����ϴ�MCU����״̬
//��������:��
//��������:��
//ע��    :��
//=============================================================================
void Comm_Upload_state(void)
{
	u16 crc;   
	
	if((Lock_Check_state ==1)||(Check_State ==1)||(Sensor_State ==1)){	
		while(Usart1_Control_Data.tx_count != 0);		//��һ�����ݱ��봫����ɲſ�����һ�δ���
		Usart1_Control_Data.tx_count = 0;	
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x01;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x58;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x10;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;//����RFID����
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Usart2_RFIDRec.data[0];	//��Ҫ����
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Usart2_RFIDRec.data[1];
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Usart2_RFIDRec.data[2];
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Usart2_RFIDRec.data[3];	
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Lock.lock1.lock_check_value;  //����������
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Lock.lock2.lock_check_value;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Lock.lock3.lock_check_value;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Lock.lock4.lock_check_value;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Sensor_State;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Sonser.sensor1.sensor_check_value;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Sonser.sensor2.sensor_check_value;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Sonser.sensor3.sensor_check_value;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Sonser.sensor4.sensor_check_value;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Sonser.sensor5.sensor_check_value;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Sonser.sensor6.sensor_check_value;
		crc=CRC_GetCCITT(Usart1_Control_Data.txbuf,Usart1_Control_Data.tx_count);
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = (crc>>8)&0xFF; 
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = crc&0xFF;
		
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0X0D;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0X0A;
		
		PC_Answer.Nanswer_timeout = NANSWER_TIME;
		PC_Answer.answer_numout = NANSWER_NUMOUT;
		PC_Answer.answer_state = 1;
		Usart1_Control_Data.tx_index = 0;	
		USART_SendData(USART1,Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_index++]);	
		
		RESET_LOCK_CHECK_STATE;
		RESET_SENSOR_CHECK_VALUE;
		Check_State = 0;
		Sensor_State = 0;
		Lock_Check_state = 0;
		
	}

}











