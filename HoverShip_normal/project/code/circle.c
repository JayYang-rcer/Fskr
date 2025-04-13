/*
 * circle.c
 *
 *  Created on: 2024年4月19日
 *      Author: 86173
 */

#include "circle.h"


extern uint8_t left_line[MT9V03X_DVP_H];                //边线数组
extern uint8_t right_line[MT9V03X_DVP_H];
extern uint8_t middle_line[MT9V03X_DVP_H];
extern straight_t L_stra;           //拟合直线
extern straight_t R_stra;
extern float mid_deviation;
extern point_t longest_white;    //最长白列
extern float real;             //推进电机差速值
extern float real_cw;      //横向电机PID输出值


bool Rcir_flag = 0;     //右环完成标志位
bool Lcir_flag = 1;     //左环岛完成标志位
bool circle_flag = 0;
bool check_cricle = 0;
enum circle_type_e circle_type;
bool leftcircle_flag = 0;
uint left_align = 40;
uint right_align = 110;
bool scan_flag = 0;         //扫描右上拐点或左上拐点标志位


//编码器
extern int16 enc_sum;
extern bool enc_add;



void circle_check(enum trace_t* posision)
{

    if(R_stra.var_cal == 0 || L_stra.var_cal == 0) return;                   //若没有进行方差计算，直接退出

    if((R_stra.variance <= 2 || L_stra.variance <= 2) && ((left_line[60] == 0) || (right_line[60] == 159)))
        check_cricle = 1;
    if(check_cricle)
    {
        if (L_circle_entry_check(left_line) == 1 && R_stra.variance <= 1 && get_lose_line(right_line,120,60) < 5)
        {
//            fly_flag = 1;
            leftcircle_flag = 1;
            *posision = circle;
            circle_type = CIRCLE_LEFT_ENTER;
            enc_add = 1;
            gpio_set_level(D9, 1);
        }
        if (R_circle_entry_check(right_line) == 1 && L_stra.variance <= 1 && get_lose_line(left_line,120,60) < 5)
        {
//            fly_flag = 1;
            leftcircle_flag = 0;
            *posision = circle;
            circle_type = CIRCLE_RIGHT_ENTER;
            enc_add = 1;
            gpio_set_level(D9, 1);
        }
    }
}


void circle_handle(msg_t* msg,enum trace_t* posision)
{

    if(leftcircle_flag)
    {
        switch(circle_type)
        {
        case CIRCLE_LEFT_ENTER:
            if(enc_sum > 8000)
            {
                enc_add = 0;
                enc_sum = 0;
                scan_flag = 1;
            }
            if(scan_flag)   find_circle_L_up(left_line, msg);
            if(msg->L_up_point.find)
            {
                circle_type = CIRCLE_ENTERING;
            }
            calculate_mid_line(MT9V03X_DVP_H-1, dynamic_foresight);             /*计算中线每个点的值*/
            PID_Calc(&camera_servo_PID, right_align,right_line[dynamic_foresight]);             /*带入误差计算差速*/
            PID_Calc(&crosswise_pid, right_align, right_line[dynamic_foresight]);       /*为横向电机所做的专属pid*/

            break;
        case CIRCLE_ENTERING:
            find_circle_L_up(left_line, msg);
            if(msg->L_up_point.find)
            {
                two_points_fitting_line(msg->L_up_point.y, msg->L_up_point.x, 125, right_line[125], &R_stra);
                line_assignment(125, msg->L_up_point.y, right_line, &R_stra);
                calculate_mid_line(MT9V03X_DVP_H-1, dynamic_foresight);             /*计算中线每个点的值*/
                PID_Calc(&camera_servo_PID, 80,middle_line[dynamic_foresight]);             /*带入误差计算差速*/
                PID_Calc(&crosswise_pid, 80, middle_line[dynamic_foresight]);       /*为横向电机所做的专属pid*/
            }
            else if(msg->L_up_point.find == 0 && get_lose_line(right_line,125,90) < 5 && longest_white.x < 60)
            {
                scan_flag = 0;
                circle_type = CIRCLE_IN;
            }
            else {
                calculate_mid_line(MT9V03X_DVP_H-1, dynamic_foresight);             /*计算中线每个点的值*/
                if(left_line[dynamic_foresight] > 80)  left_line[dynamic_foresight] = 0;
                PID_Calc(&camera_servo_PID, left_align,left_line[dynamic_foresight]);             /*带入误差计算差速*/
                PID_Calc(&crosswise_pid, left_align, left_line[dynamic_foresight]);       /*为横向电机所做的专属pid*/
            }
            break;
        case CIRCLE_IN:
            find_circle_R_down(125,80,msg);
            if(msg->R_down_point.find == 1)
            {
                enc_add = 1;
                circle_type = CIRCLE_OUTING;
            }
            calculate_mid_line(MT9V03X_DVP_H-1, dynamic_foresight);             /*计算中线每个点的值*/
            if(left_line[dynamic_foresight] < 30)  middle_line[dynamic_foresight] = 40;
            PID_Calc(&camera_servo_PID, 80,middle_line[dynamic_foresight]);             /*带入误差计算差速*/
            PID_Calc(&crosswise_pid, 80, middle_line[dynamic_foresight]);       /*为横向电机所做的专属pid*/

            break;
        case CIRCLE_OUTING:
//            if(get_lose_line(right_line,125,10) < 5 && R_stra.variance <= 1)
            if(enc_sum > 5000)
            {
                enc_sum = 0;
                enc_add = 0;
                circle_type = CIRCLE_END;
            }
            calculate_mid_line(MT9V03X_DVP_H-1, dynamic_foresight);             /*计算中线每个点的值*/
            PID_Calc(&camera_servo_PID, left_align,left_line[dynamic_foresight]);             /*带入误差计算差速*/
            PID_Calc(&crosswise_pid, left_align, left_line[dynamic_foresight]);       /*为横向电机所做的专属pid*/

            break;
        case CIRCLE_END:
            find_circle_L_up(left_line, msg);
            regression(120, 60, left_line, &L_stra);         //拟合左边直线
            if(get_lose_line(left_line,120,60) < 5 && L_stra.k < 0 && msg->L_up_point.find == 0)
            {
                circle_flag = 1;
                circle_type = CIRCLE_NONE;
                *posision = normal;
                gpio_set_level(D9, 0);

            }
            calculate_mid_line(MT9V03X_DVP_H-1, dynamic_foresight);             /*计算中线每个点的值*/
            PID_Calc(&camera_servo_PID, right_align,right_line[dynamic_foresight]);             /*带入误差计算差速*/
            PID_Calc(&crosswise_pid, right_align, right_line[dynamic_foresight]);       /*为横向电机所做的专属pid*/
            break;
        default:
            break;

        }
    }

    else{
        switch(circle_type)
        {
        case CIRCLE_RIGHT_ENTER:
            if(enc_sum > 8000)
            {
                enc_add = 0;
                enc_sum = 0;
                scan_flag = 1;
            }
            if(scan_flag)   find_circle_R_up(right_line, msg);
            if(msg->R_up_point.find)
            {
                circle_type = CIRCLE_ENTERING;
            }
            calculate_mid_line(MT9V03X_DVP_H-1, dynamic_foresight);             /*计算中线每个点的值*/
            PID_Calc(&camera_servo_PID, left_align,left_line[dynamic_foresight]);             /*带入误差计算差速*/
            PID_Calc(&crosswise_pid, left_align, left_line[dynamic_foresight]);       /*为横向电机所做的专属pid*/
            real_cw = crosswise_pid.output;
            real = camera_servo_PID.output;
            break;
        case CIRCLE_ENTERING:
            find_circle_R_up(right_line, msg);
            if(msg->R_up_point.find)
            {
                two_points_fitting_line(msg->R_up_point.y, msg->R_up_point.x, 125, left_line[125], &L_stra);
                line_assignment(125, msg->R_up_point.y, left_line, &L_stra);
                calculate_mid_line(MT9V03X_DVP_H-1, dynamic_foresight);             /*计算中线每个点的值*/
                PID_Calc(&camera_servo_PID, 80,middle_line[dynamic_foresight]);             /*带入误差计算差速*/
                PID_Calc(&crosswise_pid, 80, middle_line[dynamic_foresight]);       /*为横向电机所做的专属pid*/
                real_cw = crosswise_pid.output;
                real = camera_servo_PID.output;
            }
            else if(msg->R_up_point.find == 0 && get_lose_line(left_line,125,90) < 5 && longest_white.x > 60)
            {
                scan_flag = 0;
                circle_type = CIRCLE_IN;
            }
            else {
                calculate_mid_line(MT9V03X_DVP_H-1, dynamic_foresight);             /*计算中线每个点的值*/
                if(right_line[dynamic_foresight] < 80)  right_line[dynamic_foresight] = 159;
                PID_Calc(&camera_servo_PID, right_align,right_line[dynamic_foresight]);             /*带入误差计算差速*/
                PID_Calc(&crosswise_pid, right_align, right_line[dynamic_foresight]);       /*为横向电机所做的专属pid*/
                real_cw = crosswise_pid.output;
                real = camera_servo_PID.output;
            }
            break;
        case CIRCLE_IN:
            find_circle_L_down(125,80,msg);
            if(msg->L_down_point.find == 1)
            {
                circle_type = CIRCLE_OUTING;
                enc_add = 1;
            }
            calculate_mid_line(MT9V03X_DVP_H-1, dynamic_foresight);             /*计算中线每个点的值*/
            if(right_line[dynamic_foresight] < 30)  middle_line[dynamic_foresight] = 120;
            PID_Calc(&camera_servo_PID, 80,middle_line[dynamic_foresight]);             /*带入误差计算差速*/
            PID_Calc(&crosswise_pid, 80, middle_line[dynamic_foresight]);       /*为横向电机所做的专属pid*/
            real_cw = crosswise_pid.output;
            real = camera_servo_PID.output;

            break;
        case CIRCLE_OUTING:
//            if(get_lose_line(left_line,125,10) < 5 && L_stra.variance <= 1)
            if(enc_sum > 5000)
            {
                enc_sum = 0;
                enc_add = 0;
                circle_type = CIRCLE_END;
            }
            calculate_mid_line(MT9V03X_DVP_H-1, dynamic_foresight);             /*计算中线每个点的值*/
            PID_Calc(&camera_servo_PID, right_align,right_line[dynamic_foresight]);             /*带入误差计算差速*/
            PID_Calc(&crosswise_pid, right_align, right_line[dynamic_foresight]);       /*为横向电机所做的专属pid*/
            real_cw = crosswise_pid.output;
            real = camera_servo_PID.output;

            break;
        case CIRCLE_END:
            find_circle_R_up(right_line, msg);
            regression(120, 60, right_line, &R_stra);         //拟合右边直线
            if(get_lose_line(right_line,120,60) < 5 && R_stra.k > 0 && msg->R_up_point.find == 0)
            {
                enc_add = 1;
                circle_flag = 1;
                circle_type = CIRCLE_NONE;
                *posision = normal;
                gpio_set_level(D9, 0);
            }
            calculate_mid_line(MT9V03X_DVP_H-1, dynamic_foresight);             /*计算中线每个点的值*/
            PID_Calc(&camera_servo_PID, left_align,left_line[dynamic_foresight]);             /*带入误差计算差速*/
            PID_Calc(&crosswise_pid, left_align, left_line[dynamic_foresight]);       /*为横向电机所做的专属pid*/
            real_cw = crosswise_pid.output;
            real = camera_servo_PID.output;
            break;
        default:
            break;

        }
    }

}




