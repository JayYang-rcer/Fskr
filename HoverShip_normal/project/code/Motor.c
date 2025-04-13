/*
 * motor.c
 *
 *  Created on: 2024��3��1��
 *      Author: 86173
 */

#include <Motor.h>
//����Ư��
pid_param_t crosswise_pid = PID_INIT(4, 0.001, 5, 5, 60);  //������pid
//pid_param_t imu660ra_pid = PID_INIT(0.05,0,5,5,35);       //���ٶȿ���

uint8_t speed_target = 80;
uint8_t acc_speed = 180;

motor_param_t Motor_Encode = MOTOR_INIT(2.0,0.2,0.0); //�ٶȻ�pid

//ͼ��pid
pid_param_t camera_servo_PID = PID_INIT(0.42,0.01,6.9,5,20);   //�ƽ�������ת��pid



//�ƽ�����������ռ�ձ�

int8 L_MOTER_PWM_CENTER = 0;
int8 R_MOTER_PWM_CENTER = 0;



//����������ռ�ձ�
int8 L_FAN_PWM_CENTER = 0;
int8 R_FAN_PWM_CENTER = 0;

uint8 FAN_PWM_CENTER = 20;
//��ˢ�������ռ�ձ�
int8 BRUSHLESS_PWM = 65;


extern uint8_t curve_dir;
/************************************************************************************************************************
 *@brief......������ȵ���ĳ�ʼ��
 *@return.....��
 ***********************************************************************************************************************/
void motor_init()
{
    //��������ʼ��
    gpio_init(L_MOTOR_DIR_PIN,GPO,1,GPIO_PIN_CONFIG);
    gpio_init(R_MOTOR_DIR_PIN,GPO,0,GPIO_PIN_CONFIG);
    gpio_init(L_FAN_DIR_PIN,GPO,1,GPIO_PIN_CONFIG);
    gpio_init(R_FAN_DIR_PIN,GPO,0,GPIO_PIN_CONFIG);
    //pwm��ʼ��
    pwm_init(L_MOTER_PWM_PIN, BRUSHED_FREQ, 0);
    pwm_init(R_MOTER_PWM_PIN, BRUSHED_FREQ, 0);
    pwm_init(L_FAN_PWM_PIN, BRUSHED_FREQ, 0);
    pwm_init(R_FAN_PWM_PIN, BRUSHED_FREQ, 0);
    //��ˢ���ռ�ձ�0-10000
    pwm_init(L_BRUSHLESS_PWM_PIN, BRUSHLESS_FREQ, 0);
    pwm_init(R_BRUSHLESS_PWM_PIN, BRUSHLESS_FREQ, 0);
    // ������ˢ���ת��   ��1ms - 2ms��/20ms * 10000��10000��PWM����ռ�ձ�ʱ���ֵ��
    // ��ˢ���ת�� 0%   Ϊ 500
    // ��ˢ���ת�� 20%  Ϊ 600
    // ��ˢ���ת�� 40%  Ϊ 700
    // ��ˢ���ת�� 60%  Ϊ 800
    // ��ˢ���ת�� 80%  Ϊ 900
    // ��ˢ���ת�� 100% Ϊ 1000
    //�ϵ��ֱ�Ӹ���ˢPWMʹ�両����
    pwm_set_duty(L_BRUSHLESS_PWM_PIN, ((BRUSHLESS_PWM * 5)+500));
    pwm_set_duty(R_BRUSHLESS_PWM_PIN, ((BRUSHLESS_PWM * 5)+500));

    Motor_Encode.target_encoder = speed_target;

}


/************************************************************************************************************************
 *@brief......�ƽ���������pwm��ֵ
 *@param    real    ���pwm��ֵ
 *@return.....��
 ***********************************************************************************************************************/
void MOTOR_SET_PWM(float real)
{
    pwm_set_duty(L_MOTER_PWM_PIN, (L_MOTER_PWM_CENTER-real)* (PWM_DUTY_MAX / 100));
    pwm_set_duty(R_MOTER_PWM_PIN, (R_MOTER_PWM_CENTER+real)* (PWM_DUTY_MAX / 100));

}

/************************************************************************************************************************
 *@brief......��������pwm��ֵ
 *@param    real    ���pwm��ֵ
 *@return.....��
 ***********************************************************************************************************************/
void FAN_SET_PWM(float real_cw, float real_imu660)
{
//    if(curve_dir == 1)       //�����
//    {
//        gpio_set_level(L_FAN_DIR_PIN,0);
//        pwm_set_duty(L_FAN_PWM_PIN, FAN_PWM_CENTER * (PWM_DUTY_MAX / 100));
//        gpio_set_level(R_FAN_DIR_PIN,0);
//        pwm_set_duty(R_FAN_PWM_PIN, FAN_PWM_CENTER * (PWM_DUTY_MAX / 100));
//    }
//    else if(curve_dir == 2)       //�����
//    {
//        gpio_set_level(L_FAN_DIR_PIN,1);
//        pwm_set_duty(L_FAN_PWM_PIN, FAN_PWM_CENTER * (PWM_DUTY_MAX / 100));
//        gpio_set_level(R_FAN_DIR_PIN,1);
//        pwm_set_duty(R_FAN_PWM_PIN, FAN_PWM_CENTER * (PWM_DUTY_MAX / 100));
//    }
//    else{                           //��������
//        if(real_cw >= 0 ) //�����
//           {
//               gpio_set_level(L_FAN_DIR_PIN,0);
//               pwm_set_duty(L_FAN_PWM_PIN, (real_cw ) * (PWM_DUTY_MAX / 100));
//               gpio_set_level(R_FAN_DIR_PIN,0);
//               pwm_set_duty(R_FAN_PWM_PIN, (real_cw ) * (PWM_DUTY_MAX / 100));
//           }
//           else       //�����
//           {
//
//               gpio_set_level(L_FAN_DIR_PIN,1);
//               pwm_set_duty(L_FAN_PWM_PIN, -(real_cw) * (PWM_DUTY_MAX / 100));
//               gpio_set_level(R_FAN_DIR_PIN,1);
//               pwm_set_duty(R_FAN_PWM_PIN, -(real_cw) * (PWM_DUTY_MAX / 100));
//           }
//    }


    if(real_cw >= 0 ) //�����
       {
           gpio_set_level(L_FAN_DIR_PIN,0);
           pwm_set_duty(L_FAN_PWM_PIN, (real_cw ) * (PWM_DUTY_MAX / 100));
           gpio_set_level(R_FAN_DIR_PIN,0);
           pwm_set_duty(R_FAN_PWM_PIN, (real_cw ) * (PWM_DUTY_MAX / 100));
       }
       else       //�����
       {

           gpio_set_level(L_FAN_DIR_PIN,1);
           pwm_set_duty(L_FAN_PWM_PIN, -(real_cw) * (PWM_DUTY_MAX / 100));
           gpio_set_level(R_FAN_DIR_PIN,1);
           pwm_set_duty(R_FAN_PWM_PIN, -(real_cw) * (PWM_DUTY_MAX / 100));
       }



}


/************************************************************************************************************************
 *@brief......��ˢ�����pwm��ֵ
 *@param    real    ��ˢ���pwm
 *@return.....��
 ***********************************************************************************************************************/
void BRUSHLESS_SET_PWM(int8 BRUSHLESS_PWM)
{
    pwm_set_duty(L_BRUSHLESS_PWM_PIN, ((BRUSHLESS_PWM * 5)+500));
    pwm_set_duty(R_BRUSHLESS_PWM_PIN, ((BRUSHLESS_PWM * 5)+500));

}

/**********************************************************************************************************************
*  @brief      ����Ư��
*  @param      msg            ������Ϣ�ṹ��
*  @return     void
***********************************************************************************************************************/
void Drifting_Control(void)
{

}





