/*
 * PID.c
 *
 *  Created on: 2024��3��1��
 *      Author: 86173
 */
#include "PID.h"
#include "Img_proc.h"
extern uint8_t dynamic_foresight;
extern msg_t msg;

/************************************************************************************************************************
 *@brief......PID
 *@param      pid           PID�ĸ���ֵ
 *@param      reference     Ŀ��ֵ
 *@param      feedback      ����ֵ
 *@return.....��
 ***********************************************************************************************************************/

VOID PID_Calc(pid_param_t* pid,float reference ,float feedback)
{
    pid->pre_error = pid->error;    //�����error
    pid->error = reference - feedback;
    //����΢��
    pid->out_d = (pid->error - pid->pre_error) * (pid->kd);
    //�������
    pid->out_p = (pid->error)*(pid->kp);
    //�������
    pid->integral += pid->error*pid->ki;
    //�����޷�
    if(pid->integral > pid->i_max)  pid->integral = pid->i_max;
    else if (pid->integral < -pid->i_max)   pid->integral = -pid->i_max;
    //�������
    pid->output = pid->out_p + pid->out_d + pid->integral;
    //����޷�
    if(pid->output > pid->o_max) pid->output=pid->o_max;
    else if(pid->output < -pid->o_max) pid->output=-pid->o_max;

}

/************************************************************************************************************************
 *@brief......����ʽPID
 *@param      pid           PID�ĸ���ֵ
 *@param      error         ���ֵ
 *@return.....��
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

