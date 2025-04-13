/*
 * Motor.h
 *
 *  Created on: 2024年3月1日
 *      Author: 86173
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "zf_common_headfile.h"



//推进方向左右电机pwm引脚定义
#define R_FAN_PWM_PIN       TIM4_PWM_MAP1_CH3_D14
#define R_FAN_DIR_PIN       C4
#define L_FAN_PWM_PIN       TIM4_PWM_MAP1_CH4_D15
#define L_FAN_DIR_PIN       C3
//横移方向左右电机pwm引脚定义
#define R_MOTER_PWM_PIN     TIM4_PWM_MAP1_CH1_D12
#define R_MOTOR_DIR_PIN     C5
#define L_MOTER_PWM_PIN     TIM4_PWM_MAP1_CH2_D13
#define L_MOTOR_DIR_PIN     C2
//无刷电机左右PWM定义
#define L_BRUSHLESS_PWM_PIN     TIM2_PWM_MAP0_CH1_A0
#define R_BRUSHLESS_PWM_PIN     TIM2_PWM_MAP0_CH2_A1
//电机频率定义
#define BRUSHED_FREQ  10000
#define BRUSHLESS_FREQ  50

typedef struct motor_param
{
    int16_t target_encoder;//目标编码器值
    int16_t real_encoder;//实际编码器值
    int16_t total_encoder_count;//编码器累加记录
    uint8_t total_counter_finish;//结束累加
    int16_t duty;//电机占空比
    int16_t differential_duty;//差速得到的占空比

    pid_param_t pid;
}motor_param_t;

typedef struct speed_param
{
    //基速度
    uint8_t base_speed;
    //三岔第一圈直道速度增量
    uint8_t stra1_increment;
    //三岔第二圈直道速度增量
    uint8_t stra2_increment;
    //经过车库加速量
    uint8_t pass_garage_increment;
    //圆环run速度增量
    uint8_t circle_run_increment;
    //第一圈识别到十字的时候减速
    uint8_t cross_decrement;
}speed_param_t;

#define MOTOR_INIT(_kp, _ki, _kd) \
{.target_encoder =0, \
 .real_encoder =0, \
 .duty =0,\
 .pid =PID_INIT(_kp,_ki,_kd,0,0)}


extern pid_param_t   camera_servo_PID;                   //图像寻迹舵机PID(本质还是电机)
extern pid_param_t crosswise_pid;                         //横向电机pid
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
