#include"HeadType.h"
#include "usart.h"
#include "TIM.h"

Belt_Work_Type belt;
Printer_Type Printer;
Control_Input_Type Control;

void test_cylinder_program(void);
u8 test_program_run_flag = 0;
void delay_ms1(u16 ms)
{
    u16  i;
    u32  j;
    for (i = ms; i > 0; i--) {
        for (j = 5000; j > 0; j--)
            ;
    }
}
//配置时钟在target宏定义
int main(void)
{
    delay_init();
    Key_Light_Init();
    Belt_Config();
    LED_GPIO_Config();
    ROLL_PAPER_GPIO_Config();
    Printer_GPIO_Config();
    Air_Cylinder_GPIO_Config();
    Baffle_GPIO_Config();
    EXTIX_Init();
    USART1_Config();
    TIM2_Config();
    TIM3_Config();
    Baffle_Control.PC_send_process_time = 400;
    Air_Control.PC_send_delay_time = 240;
    param_init();
    delay_ms(1000);
    while (1) {
        if (test_program_run_flag == 0) {
            Roll_Paper_Control();
            Printer_Control();
            Air_Cylinder_Control();
            Baffle_Control_Process();
            Respond_Host_Comm();
        } else {
            test_cylinder_program();
        }
    }

}

void param_init(void)
{

    Air_Control.process = RESERVE;
    Air_Control.complete = 1;
    Air_Control.air_cylinder_position = IN_UP;

    Printer.complete = 0;
    Printer.process = PRINTER_RESERVE;
    PRINTER_START_OFF;
    PRINTER_RESTART_OFF;
    CYLINDER_OUTER;
    cylinder_inter_state_init();

    Control.upper_reach.state = 0;
    Control.upper_reach.backstate = 0;
    Control.scanner.state = 0;
    Control.fit_reach.state = 0;
    Control.fluid_bag.state = 0;
    Printer.color_end.state = 0;
    Printer.color_less.state = 0;
    Printer.end.state = 0;
    Printer.err.state = 0;
    Printer.pinline.state = 0;
    Printer.tag_end.state = 0;
    Printer.input_state = 0;
    MCU_Host_Send.control.err_message = 0;
    Baffle_Control.process_time = Baffle_Control.PC_send_process_time;
    MCU_Host_Send.control.recom_state = 0;
    Baffle_Control.PC_send_scanner_result = 0;
    Baffle_Control.scanner_result_old = 0;
    Update_Baffle_State(1);
    baffle_err_timeout = BAFFLE_ERR_TIMEOUT;
    fluid_bag_state_back = 0;
}

void test_cylinder_program(void)
{
    typedef enum {
        TEST_RESERVE,
        TEST_READY,
        TEST_CYLINDER_INTER,
        TEST_CYLINDER_OUTER,
        TEST_CYLINDER_DOWN,
        TEST_CYLINDER_UP,
        TEST_END,
    } TEST_Work_Enum_Type;
    static TEST_Work_Enum_Type test_state = TEST_RESERVE;
    static UL test_count;
    if (Device_State == 1) {
        Belt_Speed(0, 0, 0);
        switch (test_state) {
            case TEST_RESERVE:
                test_state = TEST_READY;
                break;
            case TEST_READY:
                AIR_CYLINDER_UP;
                CYLINDER_OUTER;
                AIR_BLOW_OFF;
                VACUUM_OFF;
                delay_ms(500);
                test_state = TEST_CYLINDER_INTER;
                break;
            case TEST_CYLINDER_INTER:
                CYLINDER_INTER;
                delay_ms(500);
                test_state = TEST_CYLINDER_OUTER;
                break;
            case TEST_CYLINDER_OUTER:
                CYLINDER_OUTER;
                delay_ms(500);
                test_state = TEST_CYLINDER_DOWN;
                break;
            case TEST_CYLINDER_DOWN:
                AIR_CYLINDER_DOWM;
                delay_ms(500);
                test_state = TEST_CYLINDER_UP;
                break;
            case TEST_CYLINDER_UP:
                AIR_CYLINDER_UP;
                delay_ms(500);
                test_state = TEST_CYLINDER_INTER;

                test_count.ul++;
                Usart1_Control_Data.tx_count = 0;
                Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0xAA;
                Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0xBB;
                Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = test_count.uc[3];
                Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = test_count.uc[2];
                Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = test_count.uc[1];
                Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = test_count.uc[0];
                Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0xDD;
                Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0xEE;
                Usart1_Control_Data.tx_index = 0;
                USART_SendData(USART1, Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_index++]);
                Usart1_Control_Data.rx_count = 0;
                Auto_Frame_Time1 = AUTO_FRAME_TIMEOUT1;
                Usart1_Control_Data.rx_aframe = 0;
                break;
            default:
                break;
        }

    } else {
        test_state = TEST_RESERVE;
        //ROLL_PAPER_OFF;
        AIR_CYLINDER_UP;
        AIR_BLOW_OFF;
        VACUUM_OFF;
        belt.state = END ;     //运输皮带停止
        param_init();
    }
}

