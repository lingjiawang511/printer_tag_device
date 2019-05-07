#include"HeadType.h"	

#define PRINTER_START_DELAY_TIME  6;
u8 fluid_bag_state_back = 0;
u16 printer_roll_delay = PRINTER_ROLL_DELAY_TIME;
//=============================================================================
//∫Ø ˝√˚≥∆: Printer_GPIO_Config
//π¶ƒ‹∏≈“™:¥Ú”°ª˙“˝Ω≈≈‰÷√
//≤Œ ˝√˚≥∆:Œﬁ
//∫Ø ˝∑µªÿ:Œﬁ
//◊¢“‚    :Œﬁ
//=============================================================================
 void Printer_GPIO_Config(void)
{	
	//∂®“Â“ª∏ˆGPIO_InitTypeDef ¿‡–ÕµƒΩ·ππÃÂ£¨√˚◊÷Ω–GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	//¥Ú”°ª˙π ’œ ‰»ÎIO≈‰÷√
	RCC_APB2PeriphClockCmd(PRINTER_ERR_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_ERR_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_ERR_PORT, &GPIO_InitStructure);
	//¥Ú”°ª˙¥Ú”°Ω· ¯ ‰»ÎIO≈‰÷√
	RCC_APB2PeriphClockCmd(PRINTER_END_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_END_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_END_PORT, &GPIO_InitStructure);
	//¥Ú”°ª˙‘⁄œﬂ ‰»ÎIO≈‰÷√
	RCC_APB2PeriphClockCmd(PRINTER_INLINE_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_INLINE_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_INLINE_PORT, &GPIO_InitStructure);
	//¥Ú”°ª˙±Í«©”√ÕÍ ‰»ÎIO≈‰÷√
	RCC_APB2PeriphClockCmd(PRINTER_TAGEND_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_TAGEND_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_TAGEND_PORT, &GPIO_InitStructure);
	//¥Ú”°ª˙…´¥¯”√ÕÍ ‰»ÎIO≈‰÷√
	RCC_APB2PeriphClockCmd(PRINTER_COEND_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_COEND_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_COEND_PORT, &GPIO_InitStructure);
	//¥Ú”°ª˙…´¥¯…Ÿ ‰»ÎIO≈‰÷√
	RCC_APB2PeriphClockCmd(PRINTER_COLESS_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_COLESS_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_COLESS_PORT, &GPIO_InitStructure);	
	
	//¥Ú”°ª˙∆Ù∂Ø ‰≥ˆIO≈‰÷√
	RCC_APB2PeriphClockCmd(PRINTER_START_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_START_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_START_PORT, &GPIO_InitStructure);
	//¥Ú”°ª˙÷ÿ∏¥∆Ù∂Ø ‰≥ˆIO≈‰÷√
	RCC_APB2PeriphClockCmd(PRINTER_RESTART_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_RESTART_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_RESTART_PORT, &GPIO_InitStructure);
  
  PRINTER_RESTART_OFF;//¥Ú”°ª˙÷ÿ∆Ù–≈∫≈∏ƒŒ™æÌ÷ΩµÁª˙∆Ù∂Ø–≈∫≈”√£¨¥Ú”°µƒ ±∫ÚæÕ∆Ù∂ØæÌ÷Ω°£
	

}
static void Printer_Input_Scan(void)
{
   if((Printer.err.state == 0)&&(Printer.tag_end.state == 0)&&(Printer.color_end.state == 0)){
			Printer.input_state = 1;
		}else{ //”–¥ÌŒÛ±ÿ–Î π…Ë±∏ª÷∏¥µΩ¥˝ª˙◊¥Ã¨ªÚ’ﬂ∆Ù∂Ø◊¥Ã¨≤≈ø…“‘»°œ˚¥ÌŒÛ◊¥Ã¨
			Printer.input_state = 0;
		}

}
static u8 Printer_Process_Input(void)
{
	 u8 res;
	 Printer_Input_Scan();
	 if(Device_State == 1){  //…Ë±∏∆Ù∂Ø
			if(Printer.input_state == 1){  //¥Ú”°ª˙ ‰»Î◊¥Ã¨OK
//				if(Printer.process == 1){      //¥Ú”°ª˙∆Ù∂Ø¥Ú”°
//					PRINTER_START_ON;
//				}
				res = 0;
			}else{
				Device_State = 3;
				MCU_Host_Send.control.err_message |=0x10;
				res = 1;
			}
		  return res;
		}else if(Device_State == 2){ //…Ë±∏Õ£÷π
			 PRINTER_START_OFF;
       PRINTER_RESTART_OFF;
			 Printer.err.state = 0;
			 Printer.tag_end.state = 0;
			 Printer.color_end.state = 0;
			 Printer.pinline.state = 0;
		}else{
			 PRINTER_START_OFF;
       PRINTER_RESTART_OFF;
			 Printer.err.state = 0;
			 Printer.tag_end.state = 0;
			 Printer.color_end.state = 0;
			 Printer.pinline.state = 0;
		}
		res = 1;
		return res;

}
void Printer_Control(void)
{
	static u8 working_err = 0;
	static u8 pinter_roll_skip = 0;
	if(1 == Printer_Process_Input()){		//√ø∏ˆπ˝≥Ã∂º–Ë“™≤È—Ø“ªœ¬¥Ú”°ª˙◊¥Ã¨∫Õ…Ë±∏◊¥Ã¨ «∑ÒOK
			Printer.process = PRINTER_RESERVE;		
	}else{
			Printer.process = Printer.process;	
	}
	switch(Printer.process){
		case PRINTER_RESERVE:		
													if(Device_State == 1){  //…Ë±∏∆Ù∂Ø
															if(0 == Printer_Process_Input()){		//¥Ú”°ª˙OKƒ
																Printer.process = PRINTER_READY;		
															}else{
																printer_roll_delay = 0;
																pinter_roll_skip = 0;							
															}
													}
													baffle_err_timeout = BAFFLE_ERR_TIMEOUT;
													printer_roll_delay = 0;
													pinter_roll_skip = 0;
													break ;
		case PRINTER_READY:   
														if(Printer.fluid_bag_timeout==0){
																Control.fluid_bag.state = 0;  //“ª∂Œ ±º‰ƒ⁄¥Ú”°ª˙√ª∑¥”¶£¨œ¬—π∆¯∏◊”–Œ Ã‚£¨–Ë“™«Â¡„’‚∏ˆ◊¥Ã¨£¨∑Ò‘Úœ¬¥Œ∆Ù∂Ø¥Ú”°ª˙ª·¥Ú”°
															}
															if(1 == Read_Baffle_State()){ //√ª¥Ú”°«∞Ω” ’µΩ…®√Ë«π¥ÌŒÛ£¨¬Ì…œÕ£÷π
																if(baffle_err_timeout == 0){
																	Device_State = 3;
																	MCU_Host_Send.control.err_message |=0x20;
																	Printer.process = PRINTER_RESERVE;
																	break ;
																}
															}	
														if((Air_Control.complete == 1)&&(fluid_bag_state_back == 1)&&(Control.fluid_bag.state == 0)){
															Control.fluid_bag.state =1;
														}
 														if((Air_Control.complete == 1)&&(Control.fluid_bag.state == 1)&&(READ_UPPER_REACH==0)){  //ø™ º¥Ú”°µƒ ±∫ÚæÕ∞—“∫¥¸ ‰»Î–≈∫≈÷√Œª£¨ø…“‘Ω” ’œ¬“ª¥Œ–≈∫≈ ‰»Î
															if(1 == Read_Baffle_State()){ //√ª¥Ú”°«∞Ω” ’µΩ…®√Ë«π¥ÌŒÛ£¨¬Ì…œÕ£÷π
																	Device_State = 3;
																  MCU_Host_Send.control.err_message |=0x20;
																	Printer.process = PRINTER_RESERVE;
																	break ;
																}
																Printer.process = PRINTER_WORKING;
																Printer.start_delay_time = PRINTER_START_DELAY_TIME;																																
																AIR_BLOW_ON;
																VACUUM_ON;
																PRINTER_START_ON;
																pinter_roll_skip = 0;
																printer_roll_delay = PRINTER_ROLL_DELAY_TIME;
																fluid_bag_state_back = 0;
//                                 PRINTER_RESTART_ON;
																Air_Control.complete = 0;
															  Printer.printer_work_timeout = 100;
                                uiRoll_Paper_ON_Delay = 400;//æÌ÷ΩµÁª˙ø™∆Ù◊Ó¥Û—” ±2S£¨’˝≥£æÌ÷ΩµÁª˙Õ£÷π”¶∏√ «∆¯∏◊œ¬—π ±
															  MCU_Host_Send.control.err_message &=0xF7;
//																Control.fluid_bag.state = 0;
														}													
														break ;
		case PRINTER_WORKING:   if(Printer.end.state == 1){
															Printer.process = PRINTER_END;
															Printer.complete = 1;														
															Control.fluid_bag.state = 0;
															Printer.end.state = 0;
															working_err = 0;
													  }else{
															if(Printer.printer_work_timeout == 0){
																	if(READ_PRINTER_END == SET){//¥Ú”°÷–£¨µ´ «√ª”–»ŒŒÒ£¨À˘“‘Œ™∏ﬂµÁ∆Ω
																		Printer.process = PRINTER_END;
																		Printer.complete = 1;
																		AIR_BLOW_OFF;
																		VACUUM_OFF;
																		AIR_BLOW_OFF;
																		Control.fluid_bag.state = 0;
																		Printer.end.state = 0;
																		working_err++;
																		if(working_err > 3){//¡¨–¯3¥Œ∑¢ÀÕ¥Ú”°≤Ÿ◊˜£¨µ´ «√ª”–¥Ú”°»ŒŒÒ£¨“≤æÕ «√ª”–¥Ú”°Ω· ¯–≈∫≈£¨…Ë÷√Œ™π ’œ±®æØ
																			Device_State = 3;
																			working_err = 0;	
																			MCU_Host_Send.control.err_message |=0x08;
																		}
																	}
															}
														}
														if(printer_roll_delay == 0){
															 PRINTER_RESTART_ON;
														}
					break ;
		case PRINTER_END: 
											if(printer_roll_delay != 0){
												  pinter_roll_skip = 1;
													break;
											}
											if(pinter_roll_skip == 1){
													if(printer_roll_delay == 0){
														PRINTER_RESTART_ON;
														pinter_roll_skip = 0;
													}
											}
											if(Device_State == 1){  //…Ë±∏∆Ù∂Ø     
													Printer.process = PRINTER_READY; 
											}else{
													Printer.process = PRINTER_RESERVE;	
											}
					break ;
		default :break ;
	}
}




















