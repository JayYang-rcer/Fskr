/*
 * PID.c
 *
 *  Created on: 2024年3月1日
 *      Author: 86173
 */
#include "PID.h"
#include "Img_proc.h"
extern uint8_t dynamic_foresight;
extern msg_t msg;

/************************************************************************************************************************
 *@brief......PID
 *@param      pid           PID的各项值
 *@param      reference     目标值
 *@param      feedback      反馈值
 *@return.....无
 ***********************************************************************************************************************/

VOID PID_Calc(pid_param_t* pid,float reference ,float feedback)
{
    pid->pre_error = pid->error;    //保存就error
    pid->error = reference - feedback;
    //计算微分
    pid->out_d = (pid->error - pid->pre_error) * (pid->kd);
    //计算比例
    pid->out_p = (pid->error)*(pid->kp);
    //计算积分
    pid->integral += pid->error*pid->ki;
    //积分限幅
    if(pid->integral > pid->i_max)  pid->integral = pid->i_max;
    else if (pid->integral < -pid->i_max)   pid->integral = -pid->i_max;
    //计算输出
    pid->output = pid->out_p + pid->out_d + pid->integral;
    //输出限幅
    if(pid->output > pid->o_max) pid->output=pid->o_max;
    else if(pid->output < -pid->o_max) pid->output=-pid->o_max;

}

/************************************************************************************************************************
 *@brief......增量式PID
 *@param      pid           PID的各项值
 *@param      error         误差值
 *@return.....无
 ***********************************************************************************************************************/

float Increment_Pid(pid_param_t *pid, int16_t error)
{
    pid->out_d = pid->kd * (error - 2 * pid->pre_error + pid->pre_pre_error);
    pid->out_p = pid->kp * (error - pid->pre_error);
    pid->out_i = pid->ki * error;

    pid->pre_pre_error = pid->pre_error;
    pid->pre_error = error;

    return (pid->out_i + pid->out_d + pid->out_p) ;
}

