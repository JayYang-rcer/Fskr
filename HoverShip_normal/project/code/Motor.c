/*
 * motor.c
 *
 *  Created on: 2024年3月1日
 *      Author: 86173
 */

#include <Motor.h>
//抑制漂移
pid_param_t crosswise_pid = PID_INIT(4, 0.001, 5, 5, 60);  //横向电机pid
//pid_param_t imu660ra_pid = PID_INIT(0.05,0,5,5,35);       //加速度控制

uint8_t speed_target = 80;
uint8_t acc_speed = 180;

motor_param_t Motor_Encode = MOTOR_INIT(2.0,0.2,0.0); //速度环pid

//图像pid
pid_param_t camera_servo_PID = PID_INIT(0.42,0.01,6.9,5,20);   //推进方向电机转向pid



//推进方向电机正常占空比

int8 L_MOTER_PWM_CENTER = 0;
int8 R_MOTER_PWM_CENTER = 0;



//横向电机正常占空比
int8 L_FAN_PWM_CENTER = 0;
int8 R_FAN_PWM_CENTER = 0;

uint8 FAN_PWM_CENTER = 20;
//无刷电机正常占空比
int8 BRUSHLESS_PWM = 65;


extern uint8_t curve_dir;
/************************************************************************************************************************
 *@brief......三组风扇电机的初始化
 *@return.....无
 ***********************************************************************************************************************/
void motor_init()
{
    //电机方向初始化
    gpio_init(L_MOTOR_DIR_PIN,GPO,1,GPIO_PIN_CONFIG);
    gpio_init(R_MOTOR_DIR_PIN,GPO,0,GPIO_PIN_CONFIG);
    gpio_init(L_FAN_DIR_PIN,GPO,1,GPIO_PIN_CONFIG);
    gpio_init(R_FAN_DIR_PIN,GPO,0,GPIO_PIN_CONFIG);
    //pwm初始化
    pwm_init(L_MOTER_PWM_PIN, BRUSHED_FREQ, 0);
    pwm_init(R_MOTER_PWM_PIN, BRUSHED_FREQ, 0);
    pwm_init(L_FAN_PWM_PIN, BRUSHED_FREQ, 0);
    pwm_init(R_FAN_PWM_PIN, BRUSHED_FREQ, 0);
    //有刷电机占空比0-10000
    pwm_init(L_BRUSHLESS_PWM_PIN, BRUSHLESS_FREQ, 0);
    pwm_init(R_BRUSHLESS_PWM_PIN, BRUSHLESS_FREQ, 0);
    // 计算无刷电调转速   （1ms - 2ms）/20ms * 10000（10000是PWM的满占空比时候的值）
    // 无刷电调转速 0%   为 500
    // 无刷电调转速 20%  为 600
    // 无刷电调转速 40%  为 700
    // 无刷电调转速 60%  为 800
    // 无刷电调转速 80%  为 900
    // 无刷电调转速 100% 为 1000
    //上电后直接给无刷PWM使其浮起来
    pwm_set_duty(L_BRUSHLESS_PWM_PIN, ((BRUSHLESS_PWM * 5)+500));
    pwm_set_duty(R_BRUSHLESS_PWM_PIN, ((BRUSHLESS_PWM * 5)+500));

    Motor_Encode.target_encoder = speed_target;

}


/************************************************************************************************************************
 *@brief......推进方向电机的pwm赋值
 *@param    real    电机pwm差值
 *@return.....无
 ***********************************************************************************************************************/
void MOTOR_SET_PWM(float real)
{
    pwm_set_duty(L_MOTER_PWM_PIN, (L_MOTER_PWM_CENTER-real)* (PWM_DUTY_MAX / 100));
    pwm_set_duty(R_MOTER_PWM_PIN, (R_MOTER_PWM_CENTER+real)* (PWM_DUTY_MAX / 100));

}

/************************************************************************************************************************
 *@brief......横向电机的pwm赋值
 *@param    real    电机pwm差值
 *@return.....无
 ***********************************************************************************************************************/
void FAN_SET_PWM(float real_cw, float real_imu660)
{
//    if(curve_dir == 1)       //左弯道
//    {
//        gpio_set_level(L_FAN_DIR_PIN,0);
//        pwm_set_duty(L_FAN_PWM_PIN, FAN_PWM_CENTER * (PWM_DUTY_MAX / 100));
//        gpio_set_level(R_FAN_DIR_PIN,0);
//        pwm_set_duty(R_FAN_PWM_PIN, FAN_PWM_CENTER * (PWM_DUTY_MAX / 100));
//    }
//    else if(curve_dir == 2)       //右弯道
//    {
//        gpio_set_level(L_FAN_DIR_PIN,1);
//        pwm_set_duty(L_FAN_PWM_PIN, FAN_PWM_CENTER * (PWM_DUTY_MAX / 100));
//        gpio_set_level(R_FAN_DIR_PIN,1);
//        pwm_set_duty(R_FAN_PWM_PIN, FAN_PWM_CENTER * (PWM_DUTY_MAX / 100));
//    }
//    else{                           //正常赛道
//        if(real_cw >= 0 ) //左弯道
//           {
//               gpio_set_level(L_FAN_DIR_PIN,0);
//               pwm_set_duty(L_FAN_PWM_PIN, (real_cw ) * (PWM_DUTY_MAX / 100));
//               gpio_set_level(R_FAN_DIR_PIN,0);
//               pwm_set_duty(R_FAN_PWM_PIN, (real_cw ) * (PWM_DUTY_MAX / 100));
//           }
//           else       //右弯道
//           {
//
//               gpio_set_level(L_FAN_DIR_PIN,1);
//               pwm_set_duty(L_FAN_PWM_PIN, -(real_cw) * (PWM_DUTY_MAX / 100));
//               gpio_set_level(R_FAN_DIR_PIN,1);
//               pwm_set_duty(R_FAN_PWM_PIN, -(real_cw) * (PWM_DUTY_MAX / 100));
//           }
//    }


    if(real_cw >= 0 ) //左弯道
       {
           gpio_set_level(L_FAN_DIR_PIN,0);
           pwm_set_duty(L_FAN_PWM_PIN, (real_cw ) * (PWM_DUTY_MAX / 100));
           gpio_set_level(R_FAN_DIR_PIN,0);
           pwm_set_duty(R_FAN_PWM_PIN, (real_cw ) * (PWM_DUTY_MAX / 100));
       }
       else       //右弯道
       {

           gpio_set_level(L_FAN_DIR_PIN,1);
           pwm_set_duty(L_FAN_PWM_PIN, -(real_cw) * (PWM_DUTY_MAX / 100));
           gpio_set_level(R_FAN_DIR_PIN,1);
           pwm_set_duty(R_FAN_PWM_PIN, -(real_cw) * (PWM_DUTY_MAX / 100));
       }



}


/************************************************************************************************************************
 *@brief......无刷电机的pwm赋值
 *@param    real    无刷电机pwm
 *@return.....无
 ***********************************************************************************************************************/
void BRUSHLESS_SET_PWM(int8 BRUSHLESS_PWM)
{
    pwm_set_duty(L_BRUSHLESS_PWM_PIN, ((BRUSHLESS_PWM * 5)+500));
    pwm_set_duty(R_BRUSHLESS_PWM_PIN, ((BRUSHLESS_PWM * 5)+500));

}

/**********************************************************************************************************************
*  @brief      抑制漂移
*  @param      msg            赛道信息结构体
*  @return     void
***********************************************************************************************************************/
void Drifting_Control(void)
{

}





