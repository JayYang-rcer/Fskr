/*
 * cross.c
 *
 *  Created on: 2024��4��15��
 *      Author: 86173
 */
#include "cross.h"

extern uint8_t left_line[MT9V03X_DVP_H];                //��������
extern uint8_t right_line[MT9V03X_DVP_H];
extern uint8_t middle_line[MT9V03X_DVP_H];
extern straight_t L_stra;           //���ֱ��
extern straight_t R_stra;
extern float mid_deviation;
extern float real;             //�ƽ��������ֵ
extern float real_cw;      //������PID���ֵ
//������
extern int16 enc_sum;
extern bool enc_add;
extern int16 target_speed;


bool cross_flag = 0;

enum cross_type_e cross_type;

void cross_check(msg_t* msg,enum trace_t* posision)
{
    find_L_up_straight_inflection(20,75, msg);
    find_R_up_straight_inflection(20,75, msg);
    V_point_check(20,100,left_line,right_line, msg);
    if (msg->L_up_inf.find && get_lose_line(right_line,127,msg->L_up_inf.y+4) > (117-(msg->L_up_inf.y+4)) && get_lose_line(left_line,127,msg->L_up_inf.y+4) > (117-(msg->L_up_inf.y+4))) {
        enc_add = 1;
        *posision = cross;
        cross_type = CROSS_ENTERING;
        gpio_set_level(D9, 1);
    }
    else if(msg->R_up_inf.find && get_lose_line(right_line,127,msg->R_up_inf.y+4) > (117-(msg->R_up_inf.y+4)) && get_lose_line(left_line,127,msg->R_up_inf.y+4) > (117-(msg->R_up_inf.y+4))){
        enc_add = 1;
        *posision = cross;
        cross_type = CROSS_ENTERING;
        gpio_set_level(D9, 1);
    }


}

void cross_handle(imag_t* imag,msg_t* msg,enum trace_t* posision)
{
    switch(cross_type)
        {
        case CROSS_ENTERING:
            regression(127, 80, left_line, &L_stra);         //������ֱ��
            calculate_variance(127, 80, left_line, &L_stra); //���㷽��
            regression(127, 80, right_line, &R_stra);         //����ұ�ֱ��
            calculate_variance(127, 80, right_line, &R_stra); //���㷽��
            find_L_up_straight_inflection(10,100, msg);
            find_R_up_straight_inflection(10,100, msg);
            find_L_down_straight_inflection(120, 55, msg);
            find_R_down_straight_inflection(120, 55, msg);
            V_point_check(20,100,left_line,right_line, msg);
            if(enc_sum > 2000 && msg->v_L_point.find == 0 && get_lose_line(right_line,127,100) < 5 && R_stra.variance < 0.5)
            {
                enc_add = 0;
                enc_sum = 0;
                cross_flag = 1;
                cross_type = CROSS_IN;
//                speed_decision.base_speed = 120;
            }
            else if(enc_sum > 2000 && msg->v_R_point.find == 0 && get_lose_line(left_line,127,100) < 5 && L_stra.variance < 0.5)
            {
                enc_add = 0;
                enc_sum = 0;
                cross_flag = 1;
                cross_type = CROSS_IN;
//                speed_decision.base_speed = 120;
            }
            //����ұ����������յ㶼����
            else if (msg->L_up_inf.find && msg->L_down_inf.find && msg->R_up_inf.find && msg->R_down_inf.find)
            {
                two_points_fitting_line(msg->L_up_inf.y, msg->L_up_inf.x, msg->L_down_inf.y, msg->L_down_inf.x, &L_stra);
                two_points_fitting_line(msg->R_up_inf.y, msg->R_up_inf.x, msg->R_down_inf.y, msg->R_down_inf.x, &R_stra);

                line_assignment(msg->L_down_inf.y, msg->L_up_inf.y, left_line, &L_stra);
                line_assignment(msg->R_down_inf.y, msg->R_up_inf.y, right_line, &R_stra);

            }
            //���¹յ��Ҳ���
            else if (msg->L_down_inf.find && msg->R_up_inf.find && msg->L_up_inf.find)
            {
                two_points_fitting_line(msg->L_up_inf.y, msg->L_up_inf.x, msg->L_down_inf.y, msg->L_down_inf.x, &L_stra);
                two_points_fitting_line(msg->R_up_inf.y, msg->R_up_inf.x, msg->L_down_inf.y, 159, &R_stra);

                line_assignment(msg->L_down_inf.y, msg->L_up_inf.y, left_line, &L_stra);
                line_assignment(msg->L_down_inf.y, msg->R_up_inf.y, right_line, &R_stra);

            }
            //���¹յ��Ҳ���
            else if (msg->R_down_inf.find && msg->L_up_inf.find && msg->R_up_inf.find)
            {
                two_points_fitting_line(msg->L_up_inf.y, msg->L_up_inf.x, msg->R_down_inf.y, 0, &L_stra);
                two_points_fitting_line(msg->R_up_inf.y, msg->R_up_inf.x, msg->R_down_inf.y, msg->R_down_inf.x, &R_stra);

                line_assignment(msg->R_down_inf.y, msg->L_up_inf.y, left_line, &L_stra);
                line_assignment(msg->R_down_inf.y, msg->R_up_inf.y, right_line, &R_stra);
            }
            //�����¹յ��Ҳ���
            else if(msg->L_up_inf.find && msg->R_up_inf.find)
            {
                two_points_fitting_line(msg->L_up_inf.y, msg->L_up_inf.x, 127, 0, &L_stra);
                two_points_fitting_line(msg->R_up_inf.y, msg->R_up_inf.x, 127, 159, &R_stra);

                line_assignment(127, msg->L_up_inf.y, left_line, &L_stra);
                line_assignment(127, msg->R_up_inf.y, right_line, &R_stra);
            }
            //ֻ�����Ϲյ�
            else if(msg->L_up_inf.find)
            {
                two_points_fitting_line(msg->L_up_inf.y, msg->L_up_inf.x, 127, 0, &L_stra);
                two_points_fitting_line(msg->L_up_inf.y, 159, 127, 159, &R_stra);

                line_assignment(127, msg->L_up_inf.y, left_line, &L_stra);
                line_assignment(127, msg->L_up_inf.y, right_line, &R_stra);

            }
            //ֻ�����Ϲյ�
            else if(msg->R_up_inf.find)
            {
                two_points_fitting_line(msg->R_up_inf.y, 0, 127, 0, &L_stra);
                two_points_fitting_line(msg->R_up_inf.y, msg->R_up_inf.x, 127, 159, &R_stra);

                line_assignment(127, msg->R_up_inf.y, left_line, &L_stra);
                line_assignment(127, msg->R_up_inf.y, right_line, &R_stra);

            }
            //ֻ������V�͹յ�
            else if(msg->v_L_point.find)
            {
                two_points_fitting_line(msg->v_L_point.y, msg->v_L_point.x, 127, 0, &L_stra);
                two_points_fitting_line(msg->v_L_point.y, right_line[msg->L_up_inf.y], 127, 159, &R_stra);

                line_assignment(127, msg->v_L_point.y, left_line, &L_stra);
                line_assignment(127, msg->v_L_point.y, right_line, &R_stra);
            }
            //ֻ������V�͹յ�
            else if(msg->v_R_point.find)
            {
                two_points_fitting_line(msg->v_R_point.y, left_line[msg->v_R_point.y], 127, 0, &L_stra);
                two_points_fitting_line(msg->v_R_point.y, msg->v_R_point.x, 127, 159, &R_stra);

                line_assignment(127, msg->v_R_point.y, left_line, &L_stra);
                line_assignment(127, msg->v_R_point.y, right_line, &R_stra);
            }
            break;
        case CROSS_IN:
            find_L_up_straight_inflection(20,75, msg);
            find_R_up_straight_inflection(20,75, msg);
            V_point_check(20,100,left_line,right_line, msg);
            if (msg->L_up_inf.find && get_lose_line(right_line,127,msg->L_up_inf.y+4) > (117-(msg->L_up_inf.y+4)) && get_lose_line(left_line,127,msg->L_up_inf.y+4) > (117-(msg->L_up_inf.y+4))) {
                enc_add = 1;
                cross_type = CROSS_OUTING;
            }
            else if(msg->R_up_inf.find && get_lose_line(right_line,127,msg->R_up_inf.y+4) > (117-(msg->R_up_inf.y+4)) && get_lose_line(left_line,127,msg->R_up_inf.y+4) > (117-(msg->R_up_inf.y+4))){
                enc_add = 1;
                cross_type = CROSS_OUTING;
            }
            else if(msg->v_L_point.find)
            {
                enc_add = 1;
                cross_type = CROSS_OUTING;
            }
            //ֻ������V�͹յ�
            else if(msg->v_R_point.find)
            {
                enc_add = 1;
                cross_type = CROSS_OUTING;
            }
            break;
        case CROSS_OUTING:
            regression(127, 80, left_line, &L_stra);         //������ֱ��
            calculate_variance(127, 80, left_line, &L_stra); //���㷽��
            regression(127, 80, right_line, &R_stra);         //����ұ�ֱ��3
            calculate_variance(127, 80, right_line, &R_stra); //���㷽��
            find_L_up_straight_inflection(10,100, msg);
            find_R_up_straight_inflection(10,100, msg);
            find_L_down_straight_inflection(120, 55, msg);
            find_R_down_straight_inflection(120, 55, msg);
            V_point_check(20,100,left_line,right_line, msg);
            if(enc_sum > 3000 && msg->v_L_point.find == 0 && get_lose_line(right_line,127,100) < 5 && R_stra.variance < 0.5)
            {
                enc_add = 0;
                enc_sum = 0;
                cross_flag = 1;
                cross_type = CROSS_NONE;
                *posision = normal;
//                speed_decision.base_speed = 140;
                gpio_set_level(D9, 0);
            }
            else if(enc_sum > 3000 && msg->v_R_point.find == 0 && get_lose_line(left_line,127,100) < 5 && L_stra.variance < 0.5)
            {
                enc_add = 0;
                enc_sum = 0;
                cross_flag = 1;
                cross_type = CROSS_NONE;
                *posision = normal;
                gpio_set_level(D9, 0);
//                speed_decision.base_speed = 140;
            }
            //����ұ����������յ㶼����
            else if (msg->L_up_inf.find && msg->L_down_inf.find && msg->R_up_inf.find && msg->R_down_inf.find)
            {
                two_points_fitting_line(msg->L_up_inf.y, msg->L_up_inf.x, msg->L_down_inf.y, msg->L_down_inf.x, &L_stra);
                two_points_fitting_line(msg->R_up_inf.y, msg->R_up_inf.x, msg->R_down_inf.y, msg->R_down_inf.x, &R_stra);

                line_assignment(msg->L_down_inf.y, msg->L_up_inf.y, left_line, &L_stra);
                line_assignment(msg->R_down_inf.y, msg->R_up_inf.y, right_line, &R_stra);

            }
            //���¹յ��Ҳ���
            else if (msg->L_down_inf.find && msg->R_up_inf.find && msg->L_up_inf.find)
            {
                two_points_fitting_line(msg->L_up_inf.y, msg->L_up_inf.x, msg->L_down_inf.y, msg->L_down_inf.x, &L_stra);
                two_points_fitting_line(msg->R_up_inf.y, msg->R_up_inf.x, msg->L_down_inf.y, 159, &R_stra);

                line_assignment(msg->L_down_inf.y, msg->L_up_inf.y, left_line, &L_stra);
                line_assignment(msg->L_down_inf.y, msg->R_up_inf.y, right_line, &R_stra);

            }
            //���¹յ��Ҳ���
            else if (msg->R_down_inf.find && msg->L_up_inf.find && msg->R_up_inf.find)
            {
                two_points_fitting_line(msg->L_up_inf.y, msg->L_up_inf.x, msg->R_down_inf.y, 0, &L_stra);
                two_points_fitting_line(msg->R_up_inf.y, msg->R_up_inf.x, msg->R_down_inf.y, msg->R_down_inf.x, &R_stra);

                line_assignment(msg->R_down_inf.y, msg->L_up_inf.y, left_line, &L_stra);
                line_assignment(msg->R_down_inf.y, msg->R_up_inf.y, right_line, &R_stra);
            }
            //�����¹յ��Ҳ���
            else if(msg->L_up_inf.find && msg->R_up_inf.find)
            {
                two_points_fitting_line(msg->L_up_inf.y, msg->L_up_inf.x, 127, 0, &L_stra);
                two_points_fitting_line(msg->R_up_inf.y, msg->R_up_inf.x, 127, 159, &R_stra);

                line_assignment(127, msg->L_up_inf.y, left_line, &L_stra);
                line_assignment(127, msg->R_up_inf.y, right_line, &R_stra);
            }
            //ֻ�����Ϲյ�
            else if(msg->L_up_inf.find)
            {
                two_points_fitting_line(msg->L_up_inf.y, msg->L_up_inf.x, 127, 0, &L_stra);
                two_points_fitting_line(msg->L_up_inf.y, 159, 127, 159, &R_stra);

                line_assignment(127, msg->L_up_inf.y, left_line, &L_stra);
                line_assignment(127, msg->L_up_inf.y, right_line, &R_stra);

            }
            //ֻ�����Ϲյ�
            else if(msg->R_up_inf.find)
            {
                two_points_fitting_line(msg->R_up_inf.y, 0, 127, 0, &L_stra);
                two_points_fitting_line(msg->R_up_inf.y, msg->R_up_inf.x, 127, 159, &R_stra);

                line_assignment(127, msg->R_up_inf.y, left_line, &L_stra);
                line_assignment(127, msg->R_up_inf.y, right_line, &R_stra);

            }
            //ֻ������V�͹յ�
            else if(msg->v_L_point.find)
            {
                two_points_fitting_line(msg->v_L_point.y, msg->v_L_point.x, 127, 0, &L_stra);
                two_points_fitting_line(msg->v_L_point.y, right_line[msg->L_up_inf.y], 127, 159, &R_stra);

                line_assignment(127, msg->v_L_point.y, left_line, &L_stra);
                line_assignment(127, msg->v_L_point.y, right_line, &R_stra);
            }
            //ֻ������V�͹յ�
            else if(msg->v_R_point.find)
            {
                two_points_fitting_line(msg->v_R_point.y, left_line[msg->v_R_point.y], 127, 0, &L_stra);
                two_points_fitting_line(msg->v_R_point.y, msg->v_R_point.x, 127, 159, &R_stra);

                line_assignment(127, msg->v_R_point.y, left_line, &L_stra);
                line_assignment(127, msg->v_R_point.y, right_line, &R_stra);
            }break;

        default:
            break;
        }



    calculate_mid_line(MT9V03X_DVP_H-1, dynamic_foresight);             /*��������ÿ�����ֵ*/
    PID_Calc(&camera_servo_PID, 80,middle_line[dynamic_foresight]);             /*�������������*/
    PID_Calc(&crosswise_pid, 80, middle_line[dynamic_foresight]);       /*Ϊ������������ר��pid*/
    real_cw = crosswise_pid.output;
    real = camera_servo_PID.output;

}

