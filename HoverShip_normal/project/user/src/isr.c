/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library 即（CH32V307VCT6 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是CH32V307VCT6 开源库的一部分
*
* CH32V307VCT6 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          isr
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MounRiver Studio V1.8.1
* 适用平台          CH32V307VCT6
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期                                      作者                             备注
* 2022-09-15        大W            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"
#include "my_uart7.h"
#include "key.h"
#include "zf_driver_encoder.h"
#define ENCODER_1                   (TIM1_ENCOEDER)



void NMI_Handler(void)       __attribute__((interrupt()));
void HardFault_Handler(void) __attribute__((interrupt()));

void USART1_IRQHandler(void) __attribute__((interrupt()));
void USART2_IRQHandler(void) __attribute__((interrupt()));
void USART3_IRQHandler(void) __attribute__((interrupt()));
void UART4_IRQHandler (void) __attribute__((interrupt()));
void UART5_IRQHandler (void) __attribute__((interrupt()));
void UART6_IRQHandler (void) __attribute__((interrupt()));
void UART7_IRQHandler (void) __attribute__((interrupt()));
void UART8_IRQHandler (void) __attribute__((interrupt()));
void DVP_IRQHandler (void) __attribute__((interrupt()));
//void TIM1_BRK_IRQHandler        (void)  __attribute__((interrupt()));
void TIM1_UP_IRQHandler         (void)  __attribute__((interrupt()));
//void TIM1_TRG_COM_IRQHandler    (void)  __attribute__((interrupt()));
//void TIM1_CC_IRQHandler         (void)  __attribute__((interrupt()));
void TIM2_IRQHandler            (void)  __attribute__((interrupt()));
void TIM3_IRQHandler            (void)  __attribute__((interrupt()));
void TIM4_IRQHandler            (void)  __attribute__((interrupt()));
void TIM5_IRQHandler            (void)  __attribute__((interrupt()));
void TIM6_IRQHandler            (void)  __attribute__((interrupt()));
void TIM7_IRQHandler            (void)  __attribute__((interrupt()));
//void TIM8_BRK_IRQHandler        (void)  __attribute__((interrupt()));
void TIM8_UP_IRQHandler         (void)  __attribute__((interrupt()));
//void TIM8_TRG_COM_IRQHandler    (void)  __attribute__((interrupt()));
//void TIM8_CC_IRQHandler         (void)  __attribute__((interrupt()));
//void TIM9_BRK_IRQHandler        (void)  __attribute__((interrupt()));
void TIM9_UP_IRQHandler         (void)  __attribute__((interrupt()));
//void TIM9_TRG_COM_IRQHandler    (void)  __attribute__((interrupt()));
//void TIM9_CC_IRQHandler         (void)  __attribute__((interrupt()));
//void TIM10_BRK_IRQHandler       (void)  __attribute__((interrupt()));
void TIM10_UP_IRQHandler        (void)  __attribute__((interrupt()));
//void TIM10_TRG_COM_IRQHandler   (void)  __attribute__((interrupt()));
//void TIM10_CC_IRQHandler        (void)  __attribute__((interrupt()));

void EXTI0_IRQHandler(void) __attribute__((interrupt()));
void EXTI1_IRQHandler(void) __attribute__((interrupt()));
void EXTI2_IRQHandler(void) __attribute__((interrupt()));
void EXTI3_IRQHandler(void) __attribute__((interrupt()));
void EXTI4_IRQHandler(void) __attribute__((interrupt()));
void EXTI9_5_IRQHandler(void) __attribute__((interrupt()));
void EXTI15_10_IRQHandler(void) __attribute__((interrupt()));

void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {

        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}
void USART2_IRQHandler(void)
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {


        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }
}
void USART3_IRQHandler(void)
{
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
#if DEBUG_UART_USE_INTERRUPT                                                    // 如果开启 debug 串口中断
        debug_interrupr_handler();                                              // 调用 debug 串口接收处理函数 数据会被 debug 环形缓冲区读取
#endif                                                                          // 如果修改了 DEBUG_UART_INDEX 那这段代码需要放到对应的串口中断去
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    }
}
void UART4_IRQHandler (void)
{
    if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
    {

        USART_ClearITPendingBit(UART4, USART_IT_RXNE);
    }
}
void UART5_IRQHandler (void)
{
    if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
    {
        camera_uart_handler();
        USART_ClearITPendingBit(UART5, USART_IT_RXNE);
    }
}
void UART6_IRQHandler (void)
{
    if(USART_GetITStatus(UART6, USART_IT_RXNE) != RESET)
    {

        USART_ClearITPendingBit(UART6, USART_IT_RXNE);
    }
}
void UART7_IRQHandler (void)
{
    if(USART_GetITStatus(UART7, USART_IT_RXNE) != RESET)
    {
        wireless_module_uart_handler();
        USART_ClearITPendingBit(UART7, USART_IT_RXNE);


    }
}
void UART8_IRQHandler (void)
{
    if(USART_GetITStatus(UART8, USART_IT_RXNE) != RESET)
    {
        gnss_uart_callback();
        USART_ClearITPendingBit(UART8, USART_IT_RXNE);
    }

}



void DVP_IRQHandler(void)
{
    if (DVP->IFR & RB_DVP_IF_FRM_DONE)
    {
        camera_dvp_handler();
        DVP->IFR &= ~RB_DVP_IF_FRM_DONE;
    }
}
void EXTI0_IRQHandler(void)
{
    if(SET == EXTI_GetITStatus(EXTI_Line0))
    {
        EXTI_ClearITPendingBit(EXTI_Line0);

    }
}

void EXTI1_IRQHandler(void)
{
    if(SET == EXTI_GetITStatus(EXTI_Line1))
    {
        EXTI_ClearITPendingBit(EXTI_Line1);

    }
}

void EXTI2_IRQHandler(void)
{
    if(SET == EXTI_GetITStatus(EXTI_Line2))
    {
        EXTI_ClearITPendingBit(EXTI_Line2);

    }
}

void EXTI3_IRQHandler(void)
{
    if(SET == EXTI_GetITStatus(EXTI_Line3))
    {
        EXTI_ClearITPendingBit(EXTI_Line3);

    }
}

void EXTI4_IRQHandler(void)
{
    if(SET == EXTI_GetITStatus(EXTI_Line4))
    {
        EXTI_ClearITPendingBit(EXTI_Line4);

    }
}

void EXTI9_5_IRQHandler(void)
{
    if(SET == EXTI_GetITStatus(EXTI_Line5))
    {
        EXTI_ClearITPendingBit(EXTI_Line5);

    }
    if(SET == EXTI_GetITStatus(EXTI_Line6))
    {
        EXTI_ClearITPendingBit(EXTI_Line6);

    }
    if(SET == EXTI_GetITStatus(EXTI_Line7))
    {
        EXTI_ClearITPendingBit(EXTI_Line7);

    }
    if(SET == EXTI_GetITStatus(EXTI_Line8))
    {
        EXTI_ClearITPendingBit(EXTI_Line8);

    }
    if(SET == EXTI_GetITStatus(EXTI_Line9))
    {
        EXTI_ClearITPendingBit(EXTI_Line9);

    }

}

void EXTI15_10_IRQHandler(void)
{
    if(SET == EXTI_GetITStatus(EXTI_Line10))
    {

        // 此处编写用户代码 (A10/B10..E10) 引脚触发

        // 此处编写用户代码 (A10/B10..E10) 引脚触发

        EXTI_ClearITPendingBit(EXTI_Line10);
    }
    if(SET == EXTI_GetITStatus(EXTI_Line11))
    {
        EXTI_ClearITPendingBit(EXTI_Line11);

    }
    if(SET == EXTI_GetITStatus(EXTI_Line12))
    {
        EXTI_ClearITPendingBit(EXTI_Line12);

    }
    if(SET == EXTI_GetITStatus(EXTI_Line13))
    {
        // -----------------* ToF INT 更新中断 预置中断处理函数 *-----------------
        tof_module_exti_handler();
        // -----------------* ToF INT 更新中断 预置中断处理函数 *-----------------
        // 此处编写用户代码 (A13/B13..E13) 引脚触发

        // 此处编写用户代码 (A13/B13..E13) 引脚触发

        EXTI_ClearITPendingBit(EXTI_Line13);

    }
    if(SET == EXTI_GetITStatus(EXTI_Line14))
    {
        // -----------------* DM1XA 光信号 预置中断处理函数 *-----------------
        dm1xa_light_callback();
        // -----------------* DM1XA 光信号 预置中断处理函数 *-----------------
        EXTI_ClearITPendingBit(EXTI_Line14);
    }
    if(SET == EXTI_GetITStatus(EXTI_Line15))
    {
        // -----------------* DM1XA 声/反馈信号 预置中断处理函数 *-----------------
        dm1xa_sound_callback();
        // -----------------* DM1XA 声/反馈信号 预置中断处理函数 *-----------------
        EXTI_ClearITPendingBit(EXTI_Line15);
    }
}


void TIM1_UP_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);

    }
}


void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
       TIM_ClearITPendingBit(TIM2, TIM_IT_Update );


    }
}

void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
       TIM_ClearITPendingBit(TIM3, TIM_IT_Update );


    }
}

void TIM4_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
    {
       TIM_ClearITPendingBit(TIM4, TIM_IT_Update );


    }
}


void TIM5_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
    {
       TIM_ClearITPendingBit(TIM5, TIM_IT_Update );
       extern void pit_hanlder (void);
       pit_hanlder();
    }
}

//编码器
int16 encoder_data = 0;
uint16 enc_sum = 0;
uint8 key_num = 0;
uint8 tick_num = 0;
bool enc_add = 0;

bool trans_Flag = 1;    //串口数据传输标志位




extern bool Stop_Flag;
extern bool acc_flag;
extern uint8_t curve_dir;

extern float mid_deviation;  //中线偏差

extern float real;      //推进偏差输出值
extern float real_cw;   //侧向偏差输出值
extern float real_imu660;

extern straight_t L_stra;           //拟合直线
extern straight_t R_stra;
extern msg_t msg;

extern uint16_t mid_state;      //中点黑白状态

extern enum trace_t trace_position;
extern enum circle_type_e circle_type;
extern enum barrier_type_e barrier_type;
extern enum cross_type_e cross_type;

extern uint8_t middle_line[MT9V03X_DVP_H];

void TIM6_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
    {
       TIM_ClearITPendingBit(TIM6, TIM_IT_Update );
       key_num = key_scan();
               switch(key_num)
               {
                   case 1:
                       break;
                   case 2:
                       gpio_toggle_level(D9);
                       break;
                   case 3:
                       gpio_toggle_level(D9);
                       break;
                   case 4:
                       Stop_Flag = !Stop_Flag;
                       break;
                   case 5:
                       gpio_toggle_level(D9);
                       break;
                   case 6:
                       gpio_toggle_level(D9);
                       break;
                   default:
                       break;
               }

       if(trans_Flag)
       {
           if(tick_num++ == 4)      //每60ms发一次数据
           {
//                printf("%.3f,%.3f,%.3f,%.3f,%d,%d,%2d,%2d\n",L_stra.k,L_stra.variance,R_stra.k,R_stra.variance,acc_flag,curve_dir,Motor_Encode.target_encoder,L_MOTER_PWM_CENTER);
//                printf("%d,%d,%3d\n",acc_flag,curve_dir,Motor_Encode.real_encoder);
               printf("%.1f,%d\n",real,trace_position);
//               printf("%.1f,%.1f\n",mid_deviation,real);
//               printf("%4d\n",enc_sum);
//               printf("%2d,%2d,%.1f\n",Motor_Encode.real_encoder,L_MOTER_PWM_CENTER,real);
//               printf("%d,%d,%4d,%3d\n",trace_position,circle_type,enc_sum,Motor_Encode.target_encoder);

               tick_num = 0;
           }
       }
        encoder_data = -encoder_get_count(ENCODER_1);                              // 获取编码器计数
        encoder_clear_count(ENCODER_1);                                             // 清空编码器计数
        if(enc_add)  enc_sum += encoder_data;



        real_cw = crosswise_pid.output;

       if(!Stop_Flag)
       {
           //判断是否加速
//           if(acc_flag) Motor_Encode.target_encoder = acc_speed;
//           else Motor_Encode.target_encoder = speed_target;

           Motor_Encode.target_encoder = 120;
           Motor_Encode.real_encoder = encoder_data;
           int16 Error_Encoder = Motor_Encode.target_encoder - Motor_Encode.real_encoder;
           L_MOTER_PWM_CENTER += Increment_Pid(&Motor_Encode.pid,Error_Encoder);
           R_MOTER_PWM_CENTER = L_MOTER_PWM_CENTER;


//           if((my_abs(mid_deviation) > 45) || ((mid_state == 0) && middle_line[dynamic_foresight] == 80))
//           {
//               L_MOTER_PWM_CENTER = MINMAX(L_MOTER_PWM_CENTER,0,45);//限幅
//               R_MOTER_PWM_CENTER = MINMAX(R_MOTER_PWM_CENTER,0,45);//限幅
//           }
//           else{
               L_MOTER_PWM_CENTER = MINMAX(L_MOTER_PWM_CENTER,0,70);//限幅
               R_MOTER_PWM_CENTER = MINMAX(R_MOTER_PWM_CENTER,0,70);//限幅
//           }

           MOTOR_SET_PWM(real);    //推进方向电机pwm赋值
           FAN_SET_PWM(real_cw,real_imu660);
           BRUSHLESS_SET_PWM(70);

//           if(Motor_Encode.real_encoder > 140 && acc_flag == 0 && (L_stra.variance > 1 || R_stra.variance > 1))  BRUSHLESS_SET_PWM(20);
//           else BRUSHLESS_SET_PWM(65);
       }
       else
       {

           pwm_set_duty(L_MOTER_PWM_PIN, 0);
           pwm_set_duty(R_MOTER_PWM_PIN, 0);
           pwm_set_duty(L_FAN_PWM_PIN, 0);
           pwm_set_duty(R_FAN_PWM_PIN, 0);
           BRUSHLESS_SET_PWM(10);
       }


    }
}

void TIM7_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
    {
       TIM_ClearITPendingBit(TIM7, TIM_IT_Update );
    }
}


void TIM8_UP_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM8, TIM_IT_Update);

    }
}


void TIM9_UP_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM9, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM9, TIM_IT_Update);

    }
}


void TIM10_UP_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM10, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM10, TIM_IT_Update);

    }
}



//.section    .text.vector_handler, "ax", @progbits

//   .weak   EXTI0_IRQHandler           /* EXTI Line 0 */
//   .weak   EXTI1_IRQHandler           /* EXTI Line 1 */
//   .weak   EXTI2_IRQHandler           /* EXTI Line 2 */
//   .weak   EXTI3_IRQHandler           /* EXTI Line 3 */
//   .weak   EXTI4_IRQHandler           /* EXTI Line 4 */
//   .weak   DMA1_Channel1_IRQHandler   /* DMA1 Channel 1 */
//   .weak   DMA1_Channel2_IRQHandler   /* DMA1 Channel 2 */
//   .weak   DMA1_Channel3_IRQHandler   /* DMA1 Channel 3 */
//   .weak   DMA1_Channel4_IRQHandler   /* DMA1 Channel 4 */
//   .weak   DMA1_Channel5_IRQHandler   /* DMA1 Channel 5 */
//   .weak   DMA1_Channel6_IRQHandler   /* DMA1 Channel 6 */
//   .weak   DMA1_Channel7_IRQHandler   /* DMA1 Channel 7 */
//   .weak   ADC1_2_IRQHandler          /* ADC1_2 */
//   .weak   USB_HP_CAN1_TX_IRQHandler  /* USB HP and CAN1 TX */
//   .weak   USB_LP_CAN1_RX0_IRQHandler /* USB LP and CAN1RX0 */
//   .weak   CAN1_RX1_IRQHandler        /* CAN1 RX1 */
//   .weak   CAN1_SCE_IRQHandler        /* CAN1 SCE */
//   .weak   EXTI9_5_IRQHandler         /* EXTI Line 9..5 */
//   .weak   TIM1_BRK_IRQHandler        /* TIM1 Break */
//   .weak   TIM1_UP_IRQHandler         /* TIM1 Update */
//   .weak   TIM1_TRG_COM_IRQHandler    /* TIM1 Trigger and Commutation */
//   .weak   TIM1_CC_IRQHandler         /* TIM1 Capture Compare */
//   .weak   TIM2_IRQHandler            /* TIM2 */
//   .weak   TIM3_IRQHandler            /* TIM3 */
//   .weak   TIM4_IRQHandler            /* TIM4 */
//   .weak   I2C1_EV_IRQHandler         /* I2C1 Event */
//   .weak   I2C1_ER_IRQHandler         /* I2C1 Error */
//   .weak   I2C2_EV_IRQHandler         /* I2C2 Event */
//   .weak   I2C2_ER_IRQHandler         /* I2C2 Error */
//   .weak   SPI1_IRQHandler            /* SPI1 */
//   .weak   SPI2_IRQHandler            /* SPI2 */
//   .weak   USART1_IRQHandler          /* USART1 */
//   .weak   USART2_IRQHandler          /* USART2 */
//   .weak   USART3_IRQHandler          /* USART3 */
//   .weak   EXTI15_10_IRQHandler       /* EXTI Line 15..10 */
//   .weak   RTCAlarm_IRQHandler        /* RTC Alarm through EXTI Line */
//   .weak   USBWakeUp_IRQHandler       /* USB Wakeup from suspend */
//   .weak   TIM8_BRK_IRQHandler        /* TIM8 Break */
//   .weak   TIM8_UP_IRQHandler         /* TIM8 Update */
//   .weak   TIM8_TRG_COM_IRQHandler    /* TIM8 Trigger and Commutation */
//   .weak   TIM8_CC_IRQHandler         /* TIM8 Capture Compare */
//   .weak   RNG_IRQHandler             /* RNG */
//   .weak   FSMC_IRQHandler            /* FSMC */
//   .weak   SDIO_IRQHandler            /* SDIO */
//   .weak   TIM5_IRQHandler            /* TIM5 */
//   .weak   SPI3_IRQHandler            /* SPI3 */
//   .weak   UART4_IRQHandler           /* UART4 */
//   .weak   UART5_IRQHandler           /* UART5 */
//   .weak   TIM6_IRQHandler            /* TIM6 */
//   .weak   TIM7_IRQHandler            /* TIM7 */
//   .weak   DMA2_Channel1_IRQHandler   /* DMA2 Channel 1 */
//   .weak   DMA2_Channel2_IRQHandler   /* DMA2 Channel 2 */
//   .weak   DMA2_Channel3_IRQHandler   /* DMA2 Channel 3 */
//   .weak   DMA2_Channel4_IRQHandler   /* DMA2 Channel 4 */
//   .weak   DMA2_Channel5_IRQHandler   /* DMA2 Channel 5 */
//   .weak   ETH_IRQHandler             /* ETH */
//   .weak   ETH_WKUP_IRQHandler        /* ETH WakeUp */
//   .weak   CAN2_TX_IRQHandler         /* CAN2 TX */
//   .weak   CAN2_RX0_IRQHandler        /* CAN2 RX0 */
//   .weak   CAN2_RX1_IRQHandler        /* CAN2 RX1 */
//   .weak   CAN2_SCE_IRQHandler        /* CAN2 SCE */
//   .weak   OTG_FS_IRQHandler          /* OTGFS */
//   .weak   USBHSWakeup_IRQHandler     /* USBHS Wakeup */
//   .weak   USBHS_IRQHandler           /* USBHS */
//   .weak   DVP_IRQHandler             /* DVP */
//   .weak   UART6_IRQHandler           /* UART6 */
//   .weak   UART7_IRQHandler           /* UART7 */
//   .weak   UART8_IRQHandler           /* UART8 */
//   .weak   TIM9_BRK_IRQHandler        /* TIM9 Break */
//   .weak   TIM9_UP_IRQHandler         /* TIM9 Update */
//   .weak   TIM9_TRG_COM_IRQHandler    /* TIM9 Trigger and Commutation */
//   .weak   TIM9_CC_IRQHandler         /* TIM9 Capture Compare */
//   .weak   TIM10_BRK_IRQHandler       /* TIM10 Break */
//   .weak   TIM10_UP_IRQHandler        /* TIM10 Update */
//   .weak   TIM10_TRG_COM_IRQHandler   /* TIM10 Trigger and Commutation */
//   .weak   TIM10_CC_IRQHandler        /* TIM10 Capture Compare */
//   .weak   DMA2_Channel6_IRQHandler   /* DMA2 Channel 6 */
//   .weak   DMA2_Channel7_IRQHandler   /* DMA2 Channel 7 */
//   .weak   DMA2_Channel8_IRQHandler   /* DMA2 Channel 8 */
//   .weak   DMA2_Channel9_IRQHandler   /* DMA2 Channel 9 */
//   .weak   DMA2_Channel10_IRQHandler  /* DMA2 Channel 10 */
//   .weak   DMA2_Channel11_IRQHandler  /* DMA2 Channel 11 */

/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Return         : None
*******************************************************************************/
void NMI_Handler(void)
{
}

/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.
* Input          : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{
  while (1)
  {
  }
}


