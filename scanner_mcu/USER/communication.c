#include"HeadType.h"
/********************全局变量定义****************/

//=====================命令======================
unsigned char static ComSet[]={0x03, COMM_CONTROL_ANTENNA, 0x03};
 //设置打开天线和关闭自动循卡
unsigned char static ComSearchCard[]={0x03,COMM_MIFARE_SEARCH_CARD, 0x00};
//寻卡后读出卡号
//unsigned char static cReadBlock[]={0x0A,COMM_READ_BLOCK, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
//读块No.3第1扇区的密码和控制字
//unsigned char static ComReadBlock3[]={0x0A,COMM_READ_BLOCK,0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
//读块No.1
unsigned char static ComReadBlock1[]={0x0A,COMM_READ_BLOCK,0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
//写块No.1
unsigned char static ComWriteBlock1[]={0X1A,COMM_WRITE_BLOCK, 
	   								0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
       								0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
       								0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

//初始化钱包No.5 的值为0x12345678
unsigned char static ComIntiPurse5[]={0x0E,COMM_INIT_PURSE, 
	                                0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff , 
									0x00, 0x00, 0x00, 0x00};
								    //0xff, 0xff, 0xff, 0x7f};//YZ MAX:0x7FFFFFFF
									//0x00, 0x00, 0x00, 0x80};

//读钱包的值No.5
unsigned char static ComReadPurse5[]={0x0A,COMM_READ_PURSE,
									0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 0xff,0xff};

//读钱包的值No.6
unsigned char static ComReadPurse6[]={0x0A,COMM_READ_PURSE,
									0x00, 0x06, 0xff, 0xff, 0xff, 0xff, 0xff,0xff};

//钱包值加2	    
unsigned char static ComIncrPurse5[]={0x0E,COMM_INC_VALUE, 
	   								0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
									0x02, 0x00, 0x00, 0x00};
									//0xff, 0xff, 0xff, 0x7f};//YZ MAX:0x7FFFFFFF
									//0x00, 0x00, 0x00, 0x80};
//钱包值减1
unsigned char static ComDecrPurse5[]={0x0E,COMM_DEC_VALUE, 
									0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
									0x01, 0x00, 0x00, 0x00};
									//0xff, 0xff, 0xff, 0x7f};//YZ MAX:0x7FFFFFFF
									//0x00, 0x00, 0x00, 0x80};
//钱包备份
unsigned char static ComBakPurse56[]={0x0B,COMM_BAK_PURSE, 
	   								0x00, 0x05, 0x06, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
//卡片休眠
unsigned char static ComHaltCard[]={0x02,COMM_CARD_HALT,0x09};  
//设置模块空闲睡眠模式
unsigned char static ComHaltMCU[]={0x02,COMM_SET_MCU_IDLE,0x03};	
unsigned char static ComSelfSearchCard[]={0x02,COMM_SELF_SEARCH_CARD,0x0E};

RFID_REC_Type Usart2_RFIDRec;
RFID_REC_Type Usart3_RFIDRec;

USART_WORK_Type Usart_Work_State;					//MCU作为主机还是从机状态
Answer_Type 	 PC_Answer;
COMM_Rec_Union_Type   MCU_Host_Rec;//MCU作为主机时的结构体接收应答变量
COMM_Send_Union_Type  MCU_Host_Send;//MCU作为主机时的结构体发送数据
//=============================================================================
//函数名称: check_xor_sum
//功能概要:异或和校验函数
//参数名称:无
//函数返回:返回校验结果
//注意    :无
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
//函数名称:Usart2_Send_RFIDCmd
//功能概要:串口2发送RFID命令
//参数名称:len:命令数字长度。pdata:命令字
//函数返回:无
//注意    :无
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
//函数名称:Usart3_Send_RFIDCmd
//功能概要:串口3发送RFID命令
//参数名称:len:命令数字长度。pdata:命令字
//函数返回:无
//注意    :无
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
//函数名称:Do_Usrat2_RFIDCmd
//功能概要:处理串口2发送RFID命令
//参数名称:cmd:命令
//函数返回:无
//注意    :无
//=============================================================================
void Do_Usrat2_RFIDCmd(u8 cmd )
{
	switch(cmd){
	case COMM_SET_MCU_IDLE: //设置模块空闲睡眠模式
		Usart2_Send_RFIDCmd(ComHaltMCU[0],ComHaltMCU);break ;
	case COMM_CONTROL_ANTENNA://模块天线控制、自动寻卡设置
		Usart2_Send_RFIDCmd(ComSet[0],ComSet);break ;
	case COMM_MIFARE_SEARCH_CARD://TYPE-A寻卡
		Usart2_Send_RFIDCmd(ComSearchCard[0],ComSearchCard);break ;
	case COMM_READ_BLOCK: //读块
		Usart2_Send_RFIDCmd(ComReadBlock1[0],ComReadBlock1);break ;
	case COMM_WRITE_BLOCK://写块
		Usart2_Send_RFIDCmd(ComWriteBlock1[0],ComWriteBlock1);break ;
	case COMM_INIT_PURSE:  //初始化钱包
		Usart2_Send_RFIDCmd(ComIntiPurse5[0],ComIntiPurse5);break ;
	case COMM_READ_PURSE://读取钱包
		Usart2_Send_RFIDCmd(ComReadPurse5[0],ComReadPurse5);break ;
	case COMM_INC_VALUE://充值
		Usart2_Send_RFIDCmd(ComIncrPurse5[0],ComIncrPurse5);break ;
	case COMM_DEC_VALUE: //扣款
		Usart2_Send_RFIDCmd(ComDecrPurse5[0],ComDecrPurse5);break ;
	case COMM_BAK_PURSE:  //备份钱包值
		Usart2_Send_RFIDCmd(ComBakPurse56[0],ComBakPurse56);break ;
	case COMM_CARD_HALT://卡休眠
		Usart2_Send_RFIDCmd(ComHaltCard[0],ComHaltCard);break ;
	case COMM_SELF_SEARCH_CARD:
		Usart2_Send_RFIDCmd(ComSelfSearchCard[0],ComSelfSearchCard);break ;
	default :break ;
	}	
}
//=============================================================================
//函数名称:Do_Usrat3_RFIDCmd
//功能概要:处理串口3发送RFID命令
//参数名称:cmd:命令
//函数返回:无
//注意    :无
//=============================================================================
void Do_Usrat3_RFIDCmd(u8 cmd )
{
	switch(cmd){
	case COMM_SET_MCU_IDLE: //设置模块空闲睡眠模式
		Usart3_Send_RFIDCmd(ComHaltMCU[0],ComHaltMCU);break ;
	case COMM_CONTROL_ANTENNA://模块天线控制、自动寻卡设置
		Usart3_Send_RFIDCmd(ComSet[0],ComSet);break ;
	case COMM_MIFARE_SEARCH_CARD://TYPE-A寻卡
		Usart3_Send_RFIDCmd(ComSearchCard[0],ComSearchCard);break ;
	case COMM_READ_BLOCK: //读块
		Usart3_Send_RFIDCmd(ComReadBlock1[0],ComReadBlock1);break ;
	case COMM_WRITE_BLOCK://写块
		Usart3_Send_RFIDCmd(ComWriteBlock1[0],ComWriteBlock1);break ;
	case COMM_INIT_PURSE:  //初始化钱包
		Usart3_Send_RFIDCmd(ComIntiPurse5[0],ComIntiPurse5);break ;
	case COMM_READ_PURSE://读取钱包
		Usart3_Send_RFIDCmd(ComReadPurse5[0],ComReadPurse5);
		Usart3_Send_RFIDCmd(ComReadPurse5[0],ComReadPurse6);break ;
	case COMM_INC_VALUE://充值
		Usart3_Send_RFIDCmd(ComIncrPurse5[0],ComIncrPurse5);break ;
	case COMM_DEC_VALUE: //扣款
		Usart3_Send_RFIDCmd(ComDecrPurse5[0],ComDecrPurse5);break ;
	case COMM_BAK_PURSE:  //备份钱包值
		Usart3_Send_RFIDCmd(ComBakPurse56[0],ComBakPurse56);break ;
	case COMM_CARD_HALT://卡休眠
		Usart3_Send_RFIDCmd(ComHaltCard[0],ComHaltCard);break ;
	case COMM_SELF_SEARCH_CARD:
		Usart3_Send_RFIDCmd(ComSelfSearchCard[0],ComSelfSearchCard);break ;
	default :break ;
	}
}
//=============================================================================
//函数名称:Usrat2_Rec_RFIDdata
//功能概要:串口2接收到的RFID数据
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
static u8 Usrat2_Rec_RFIDdata(void )
{
	u8 i,res;
	u16 crc;
	if(Usart2_Control_Data.rx_aframe == 1){
		if((Usart2_Control_Data.rx_count < 8)||(Usart2_Control_Data.rxbuf[0] != 0xFE)||(Usart2_Control_Data.rxbuf[2] != 0x03)){//接收到的数据位少于八位或者数据头不对是不正常的
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
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x01;//有无RFID读卡
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
//		Usart_Work_State = USART2_WORK; //谁先接收到数据谁先传输
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
//函数名称:Usrat2_Rec_RFIDdata
//功能概要:串口2接收到的RFID数据
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
static u8 Usrat3_Rec_RFIDdata(void )
{
	u8 i,res;
	u16 crc;
	if(Usart3_Control_Data.rx_aframe == 1){
		if((Usart3_Control_Data.rx_count < 8)||(Usart3_Control_Data.rxbuf[0] != 0xFE)||(Usart3_Control_Data.rxbuf[2] != 0x03)){//接收到的数据位少于八位或者数据头不对是不正常的
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
		while(Usart1_Control_Data.tx_count != 0); //上一次数据必须传输完成才可以下一次传输
		Usart1_Control_Data.tx_count = 0;	
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x01;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x58;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x05;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x02;//卡的通道号
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
		Usart_Work_State = USART3_WORK; //谁先接收到数据谁先传输
		Usart3_Control_Data.rx_aframe = 0;
		Usart1_Control_Data.rx_aframe = 0;	//清空和主机的通讯，避免通讯错误
		Usart1_Control_Data.rx_count = 0;
		res = 0;
	}else{
		res = 1;
	}
	return res;
}

#endif
//=============================================================================
//函数名称:Respond_Host_Comm
//功能概要:响应上位机的发出的数据命令，数据已经从串口一接收完整
//参数说明:无
//函数返回:无
//注意    :无
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
						}//把数据复制给主机通讯结构体
					switch(MCU_Host_Rec.control.lock1){
						case 0x00: break;    //不处理
						case 0x01: 					
					        	LOCK1_ON;										//执行开锁点灯动作,锁开好后再点灯
										Lock.lock1.lock_state = 1;
										Lock.lock1.lock_time = LOCK_TIME;
					        	break;   //开锁1
						default :break;
					}
					switch(MCU_Host_Rec.control.lock2){
						case 0x00: break;    //不处理
						case 0x01:
					        	LOCK2_ON;										//执行开锁点灯动作,锁开好后再点灯
										Lock.lock2.lock_state = 1;
										Lock.lock2.lock_time = LOCK_TIME;
					        	break;   //开锁2
						default :break;
					}
					switch(MCU_Host_Rec.control.lock3){
						case 0x00: break;    //不处理
						case 0x01: 
					        	LOCK3_ON;										//执行开锁点灯动作,锁开好后再点灯
										Lock.lock3.lock_state = 1;
										Lock.lock3.lock_time = LOCK_TIME;
					        	break;   //开锁3
						default :break;
					}
					switch(MCU_Host_Rec.control.lock4){
						case 0x00: break;    //不处理
						case 0x01:
					        	LOCK4_ON;										//执行开锁点灯动作,锁开好后再点灯
										Lock.lock4.lock_state = 1;
										Lock.lock4.lock_time = LOCK_TIME;
					        	break;   //开锁4
						default :break;
					}
					switch(MCU_Host_Rec.control.RFID){
						case 0x00: break;    //不处理
						case 0x01:  Beep_Num = BEEP_RIGHT_COUNT;  break;     //RFID正确，蜂鸣器响提示一下
						case 0x02:	Beep_Num = BEEP_ERROR_COUNT;break;  //RFID正确，蜂鸣器响提示一下
						default :break;
					}
					switch(MCU_Host_Rec.control.check){
						case 0x00: break;    //不处理
						case 0x01: Check_State = 1; break;   //检查状态，主动上传
						default :break;
					}
					for(i = 0;i < 14;i++){
								MCU_Host_Rec.rec_buf[i] = 0x00;
						}//处理完之后将控制数据清零
				}else{
//				 res = 1;
					res = 0;
			}
		res = 0;	
		return res;
}
//=============================================================================
//函数名称:Execute_Host_Comm
//功能概要:执行上位机发出的命令
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
u8 Execute_Host_Comm(void)
{
	u8 res;
		res = Usrat2_Rec_RFIDdata();//有RFID信号时跳到相应的状态机等待PC接收数据后响应
		if (1 == Usart1_Control_Data.rx_aframe){ 
				res=Respond_Host_Comm();   //不做闭环响应，所以每次res都是等于0
				Usart1_Control_Data.rx_count = 0;
				Auto_Frame_Time1 = AUTO_FRAME_TIMEOUT1;
				Usart1_Control_Data.rx_aframe = 0;
		}
	return res;
}

//=============================================================================
//函数名称:Send_Medicine_Time_ISR
//功能概要:通讯超时或超次数控制
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void PC_Communication_Time_ISR(void )
{
	if(PC_Answer.answer_state == 1){
		if(PC_Answer.Nanswer_timeout > 0){
				PC_Answer.Nanswer_timeout--;
		}else{//主机超时没有响应，当正确应答处理，MCU转化为从机模式。
				Usart_Work_State = NO_USART_WORK;	
				PC_Answer.Nanswer_timeout = NANSWER_TIME;
				PC_Answer.answer_numout = NANSWER_NUMOUT;
				PC_Answer.answer_state = 0;	
				Usart2_Control_Data.rx_aframe = 0;	//避免和PC通讯过程有人刷卡，通讯结束后直接响应开门
//				Usart3_Control_Data.rx_aframe = 0;			
		}
		if(PC_Answer.answer_numout > 0){
				PC_Answer.answer_numout=PC_Answer.answer_numout;//自减操作不在这里
		}else{//MCU发送了N此主机都没有响应正确的应答，当正确应答处理，MCU转化为从机模式。
				Usart_Work_State = NO_USART_WORK;	
				PC_Answer.Nanswer_timeout = NANSWER_TIME;
				PC_Answer.answer_numout = NANSWER_NUMOUT;
				Usart2_Control_Data.rx_aframe = 0;	//避免和PC通讯过程有人刷卡，通讯结束后直接响应开门
//				Usart3_Control_Data.rx_aframe = 0;
				PC_Answer.answer_state = 0;				
		}
	}
}

//=============================================================================
//函数名称:Comm_Upload_state
//功能概要:通讯主动上传MCU外设状态
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void Comm_Upload_state(void)
{
	u16 crc;   
	
	if((Lock_Check_state ==1)||(Check_State ==1)||(Sensor_State ==1)){	
		while(Usart1_Control_Data.tx_count != 0);		//上一次数据必须传输完成才可以下一次传输
		Usart1_Control_Data.tx_count = 0;	
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x01;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x58;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x10;
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;//有无RFID读卡
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Usart2_RFIDRec.data[0];	//需要清零
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Usart2_RFIDRec.data[1];
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Usart2_RFIDRec.data[2];
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Usart2_RFIDRec.data[3];	
		Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Lock.lock1.lock_check_value;  //不允许请零
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











