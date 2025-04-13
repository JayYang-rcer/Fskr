/*
 * Motor.h
 *
 *  Created on: 2024��3��1��
 *      Author: 86173
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "zf_common_headfile.h"



//�ƽ��������ҵ��pwm���Ŷ���
#define R_FAN_PWM_PIN       TIM4_PWM_MAP1_CH3_D14
#define R_FAN_DIR_PIN       C4
#define L_FAN_PWM_PIN       TIM4_PWM_MAP1_CH4_D15
#define L_FAN_DIR_PIN       C3
//���Ʒ������ҵ��pwm���Ŷ���
#define R_MOTER_PWM_PIN     TIM4_PWM_MAP1_CH1_D12
#define R_MOTOR_DIR_PIN     C5
#define L_MOTER_PWM_PIN     TIM4_PWM_MAP1_CH2_D13
#define L_MOTOR_DIR_PIN     C2
//��ˢ�������PWM����
#define L_BRUSHLESS_PWM_PIN     TIM2_PWM_MAP0_CH1_A0
#define R_BRUSHLESS_PWM_PIN     TIM2_PWM_MAP0_CH2_A1
//���Ƶ�ʶ���
#define BRUSHED_FREQ  10000
#define BRUSHLESS_FREQ  50

typedef struct motor_param
{
    int16_t target_encoder;//Ŀ�������ֵ
    int16_t real_encoder;//ʵ�ʱ�����ֵ
    int16_t total_encoder_count;//�������ۼӼ�¼
    uint8_t total_counter_finish;//�����ۼ�
    int16_t duty;//���ռ�ձ�
    int16_t differential_duty;//���ٵõ���ռ�ձ�

    pid_param_t pid;
}motor_param_t;

typedef struct speed_param
{
    //���ٶ�
    uint8_t base_speed;
    //�����һȦֱ���ٶ�����
    uint8_t stra1_increment;
    //����ڶ�Ȧֱ���ٶ�����
    uint8_t stra2_increment;
    //�������������
    uint8_t pass_garage_increment;
    //Բ��run�ٶ�����
    uint8_t circle_run_increment;
    //��һȦʶ��ʮ�ֵ�ʱ�����
    uint8_t cross_decrement;
}speed_param_t;

#define MOTOR_INIT(_kp, _ki, _kd) \
{.target_encoder =0, \
 .real_encoder =0, \
 .duty =0,\
 .pid =PID_INIT(_kp,_ki,_kd,0,0)}


extern pid_param_t   camera_servo_PID;                   //ͼ��Ѱ�����PID(���ʻ��ǵ��)
extern pid_param_t crosswise_pid;                         //������pid
extern pid_param_t imu660ra_pid;
extern int8 L_MOTER_PWM_CENTER;
extern int8 R_MOTER_PWM_CENTER;
extern int8 L_FAN_PWM_CENTER;
extern int8 R_FAN_PWM_CENTER;
extern int8 BRUSHLESS_PWM;
extern uint8_t acc_speed;
extern uint8_t speed_target;
extern motor_param_t Motor_Encode;


void speed_init(void);
void motor_init(void);
void MOTOR_SET_PWM(float real);
void FAN_SET_PWM(float real, float real_cw);
void BRUSHLESS_SET_PWM(int8 BRUSHLESS_PWM);
void Drifting_Control(void);













#endif /* MOTOR_H_ */
