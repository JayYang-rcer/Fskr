/*
 * barrier.c
 *
 *  Created on: 2024年5月21日
 *      Author: 86173
 */
#include "barrier.h"

extern uint8_t left_line[MT9V03X_DVP_H];                //边线数组
extern uint8_t right_line[MT9V03X_DVP_H];
extern straight_t L_stra;           //拟合直线
extern straight_t R_stra;
extern float real;             //推进电机差速值
extern float real_cw;      //横向电机PID输出值

enum barrier_type_e barrier_type;
uint L_align = 65;
uint R_align = 90;
bool barrier_flag = 0;
uint barrier_foresight = 90;
//编码器
extern int16 enc_sum;
extern bool enc_add;


void barrier_check(msg_t* msg,enum trace_t* posision)
{
    if(R_stra.var_cal == 0 || L_stra.var_cal == 0) return;                   //若没有进行方差计算，直接退出
    find_L_up_straight_inflection(60,100, msg);
    find_R_up_straight_inflection(60,100, msg);

    if (msg->L_up_inf.find == 1 && R_stra.variance <= 1 && msg->L_up_inf.x < 80 && get_lose_line(left_line,127,msg->L_up_inf.y+4) < 2)
    {
        *posision = barrier;
        barrier_type = BARRIER_LEFT;
        enc_add = 1;
        gpio_set_level(D9, 1);
    }
    if (msg->R_up_inf.find == 1 && L_stra.variance <= 1 && msg->R_up_inf.x > 80 && get_lose_line(right_line,127,msg->R_up_inf.y+4) < 2)
    {
        *posision = barrier;
        barrier_type = BARRIER_RIGHT;
        enc_add = 1;
        gpio_set_level(D9, 1);
    }

}

void barrier_handle(enum trace_t* posision)
{
    switch(barrier_type)
    {
    case BARRIER_LEFT:
        if(enc_sum > 6000)
        {
            barrier_flag = 1;
            enc_add = 0;
            enc_sum = 0;
            barrier_type = BARRIER_NONE;
            *posision = normal;
            gpio_set_level(D9, 0);
        }
        PID_Calc(&camera_servo_PID, R_align,right_line[barrier_foresight]);             /*带入误差计算差速*/
        PID_Calc(&crosswise_pid, R_align, right_line[dynamic_foresight]);       /*为横向电机所做的专属pid*/

        break;
    case BARRIER_RIGHT:
        if(enc_sum > 6000)
        {
            barrier_flag = 1;
            enc_add = 0;
            enc_sum = 0;
            barrier_type = BARRIER_NONE;
            *posision = normal;
            gpio_set_level(D9, 0);
        }
        calculate_mid_line(MT9V03X_DVP_H-1, dynamic_foresight);             /*计算中线每个点的值*/
        PID_Calc(&camera_servo_PID, L_align,left_line[barrier_foresight]);             /*带入误差计算差速*/
        PID_Calc(&crosswise_pid, L_align, left_line[barrier_foresight]);       /*为横向电机所做的专属pid*/

        break;
    default:
        break;
    }
    real_cw = crosswise_pid.output;
    real = camera_servo_PID.output;

}




