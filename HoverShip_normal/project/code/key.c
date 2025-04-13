/*
 * key.c
 *
 *  Created on: 2024年3月6日
 *      Author: 86173
 */
#include "key.h"

uint8_t value=0;




//void key_init(void)
//{
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//    gpio_init(KEY1_PIN, GPO, 1, GPIO_INT_CONFIG);//上拉输入，输出高
//    gpio_init(KEY2_PIN, GPO, 1, GPIO_INT_CONFIG);//上拉输入，输出高
//    gpio_init(KEY3_PIN, GPO, 1, GPIO_INT_CONFIG);//上拉输入，输出高
//    gpio_init(KEY4_PIN, GPO, 1, GPIO_INT_CONFIG);//上拉输入，输出高
//    gpio_init(KEY5_PIN, GPO, 1, GPIO_INT_CONFIG);//上拉输入，输出高
//    gpio_init(KEY6_PIN, GPO, 1, GPIO_INT_CONFIG);//上拉输入，输出高
//
//    EXTI_InitTypeDef EXTI_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;
//
//    //PA8外部中断(下降沿触发)
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);
//    EXTI_InitStructure.EXTI_Line =EXTI_Line8;
//    EXTI_InitStructure.EXTI_Mode =EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Falling;
//    EXTI_InitStructure.EXTI_LineCmd =ENABLE;
//    EXTI_Init(&EXTI_InitStructure);
//    //PD8外部中断(下降沿触发)
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource8);
//    EXTI_InitStructure.EXTI_Line =EXTI_Line8;
//    EXTI_Init(&EXTI_InitStructure);
//    //PB12外部中断(下降沿触发)
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource12);
//    EXTI_InitStructure.EXTI_Line =EXTI_Line12;
//    EXTI_Init(&EXTI_InitStructure);
//    //PB0外部中断(下降沿触发)
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
//    EXTI_InitStructure.EXTI_Line =EXTI_Line0;
//    EXTI_Init(&EXTI_InitStructure);
//    //PD5外部中断(下降沿触发)
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource5);
//    EXTI_InitStructure.EXTI_Line =EXTI_Line5;
//    EXTI_Init(&EXTI_InitStructure);
//    //PD10外部中断(下降沿触发)
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource10);
//    EXTI_InitStructure.EXTI_Line =EXTI_Line10;
//    EXTI_Init(&EXTI_InitStructure);
//
//
//    //PA8 NVIC配置
//    NVIC_InitStructure.NVIC_IRQChannel =EXTI9_5_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
//    NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//    //PD8 NVIC配置
//    NVIC_InitStructure.NVIC_IRQChannel =EXTI9_5_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;
//    NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//    //PB12 NVIC配置
//    NVIC_InitStructure.NVIC_IRQChannel =EXTI15_10_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
//    NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//    //PB0 NVIC配置
//    NVIC_InitStructure.NVIC_IRQChannel =EXTI0_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
//    NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//    //PD5 NVIC配置
//    NVIC_InitStructure.NVIC_IRQChannel =EXTI9_5_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
//    NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//    //PD10 NVIC配置
//    NVIC_InitStructure.NVIC_IRQChannel =EXTI15_10_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
//    NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//}


void key_gpio_init()
{
    gpio_init(KEY1_PIN, GPO, 1, GPIO_INT_CONFIG);//上拉输入，输出高
    gpio_init(KEY2_PIN, GPO, 1, GPIO_INT_CONFIG);//上拉输入，输出高
    gpio_init(KEY3_PIN, GPO, 1, GPIO_INT_CONFIG);//上拉输入，输出高
    gpio_init(KEY4_PIN, GPO, 1, GPIO_INT_CONFIG);//上拉输入，输出高
    gpio_init(KEY5_PIN, GPO, 1, GPIO_INT_CONFIG);//上拉输入，输出高
    gpio_init(KEY6_PIN, GPO, 1, GPIO_INT_CONFIG);//上拉输入，输出高
}

uint8_t key_scan()
{
    static u8 count = 0;
    static u8   press_flag = 0;
    value =0;
    if(press_flag)  count++;

    if(count==0 || count >= 40)
        {
        if(count>=40)
            {
                press_flag = 0;
                count = 0;
            }
        if(gpio_get_level(A8) == RESET)
            {
                value = 1;
                press_flag = 1;
            }
            else if(gpio_get_level(D8) == RESET)
            {
                value = 2;
                press_flag = 1;
            }
            else if(gpio_get_level(B12) == RESET)
            {
                value = 3;
                press_flag = 1;
            }
            else if(gpio_get_level(B0) == RESET)
            {
                value = 4;
                press_flag = 1;
            }
            else if(gpio_get_level(D5) == RESET)
            {
                value = 5;
                press_flag = 1;
            }
            else if(gpio_get_level(D10) == RESET)
            {
                value = 6;
                press_flag = 1;
            }
        }

    return value;
}


