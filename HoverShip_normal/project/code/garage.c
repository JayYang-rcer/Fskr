/*
 * garage.c
 *
 *  Created on: 2024年5月22日
 *      Author: 86173
 */
#include "garage.h"

extern uint8_t left_line[MT9V03X_DVP_H];                //边线数组
extern uint8_t right_line[MT9V03X_DVP_H];
extern uint8_t middle_line[MT9V03X_DVP_H];
extern float real;             //推进电机差速值
extern float real_cw;      //横向电机PID输出值
extern bool Stop_Flag;
extern straight_t L_stra;           //拟合直线
extern straight_t R_stra;




//编码器
extern int16 enc_sum;
extern bool enc_add;


void garage_check(imag_t* img,enum trace_t* posision)
{
    uint8_t width = 0; //斑马线宽度
    uint8_t num = 0;   //斑马块数量
    uint8_t start = 0; //
    uint8_t end = 0; //
    if(L_stra.variance < 1 && R_stra.variance < 1 && get_lose_line(right_line,120,40) < 2 && get_lose_line(left_line,120,40) < 2)
    {
        for(uint8 i = 65;i < 90;i+=5)
            {
                start = 0;
                end = 0;
                for(uint8 j = left_line[i];j<right_line[i];j++)
                {
                    if(img->pixel[i*MT9V03X_DVP_W + j] == 255 && img->pixel[i*MT9V03X_DVP_W + j + 1] == 0)  start = j;
                    if(img->pixel[i*MT9V03X_DVP_W + j] == 0 && img->pixel[i*MT9V03X_DVP_W + j + 1] == 255)  end = j;
                    if(end > start && end != 0 && start != 0)
                    {
                        if(end - start < 10)
                        {
                            num++;
                            start = 0;
                            end = 0;
                        }
                    }
                    if(num > 5)
                    {
                        *posision = garage;
                        enc_add = 1;
                        gpio_set_level(D9, 1);
                        return;
                    }
                }
            }
    }


}

void garage_handle(enum trace_t* posision)
{
    if(enc_sum > 8000)
    {
        enc_add = 0;
        enc_sum = 0;
        gpio_set_level(D9, 0);
        *posision = normal;
        Stop_Flag = 1;
    }
    calculate_mid_line(MT9V03X_DVP_H-1, dynamic_foresight);             /*计算中线每个点的值*/
    PID_Calc(&camera_servo_PID, 80,middle_line[dynamic_foresight]);             /*带入误差计算差速*/
    PID_Calc(&crosswise_pid, 80, middle_line[dynamic_foresight]);       /*为横向电机所做的专属pid*/
    real_cw = crosswise_pid.output;
    real = camera_servo_PID.output;

}

