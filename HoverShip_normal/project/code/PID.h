/*
 * PID.h
 *
 *  Created on: 2024��3��1��
 *      Author: 86173
 */

#ifndef PID_H_
#define PID_H_

#include "stdint.h"

//�޷�
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MINMAX(input, low, upper) MIN(MAX(input, low), upper)

//pid�ṹ��
typedef struct {
    float kp;    //P
    float ki;    //I
    float kd;    //D
    float integral,i_max; //integrator_max

    float out_p;    //���pid��ֵ
    float out_i;
    float out_d;
    float output;
    float o_max;    //pid����޶�

    float error;
    float pre_error;
    float pre_pre_error;
    float servo_section_scale;
}pid_param_t;

//pid��ʼ��
#define PID_INIT(_kp, _ki, _kd, max_i, max_o)   \
    {                                    \
        .kp = _kp,                       \
        .ki = _ki,                       \
        .kd = _kd,                       \
        .out_p = 0,                      \
        .out_i = 0,                      \
        .out_d = 0,                      \
        .i_max = max_i,                  \
        .o_max = max_o,                  \
    }


//λ��ʽPID
void PID_Calc(pid_param_t* pid,float reference ,float feedback);
//����ʽPID
float Increment_Pid(pid_param_t *pid, int16_t error);

#endif /* PID_H_ */
