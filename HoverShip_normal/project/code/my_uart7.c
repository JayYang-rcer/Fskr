/*
 * my_uart7.c
 *
 *  Created on: 2024��3��7��
 *      Author: 86173
 */
#include "my_uart7.h"

extern pid_param_t camera_servo_PID;
uint8 data_buffer[32];      //�������ݻ���
uint8 RXnum = 0;            //ָ���
bool RX_FLag = 0;           //��ʼ���ձ�־λ
extern bool Stop_Flag;
//-------------------------------------------------------------------------------------------------------------------



/**********************************************************************************************************************
 * @brief       �������
**********************************************************************************************************************/
float Get_intData(uint8  RXnum)
{
    uint8_t data_Start_Num = 0; // ��¼����λ��ʼ�ĵط�
    uint8_t data_End_Num = 0; // ��¼����λ�����ĵط�
    uint8_t decimal_num = 0;
    uint8_t data_Num = 0; // ��¼����λ��
    uint8_t minus_Flag = 0; // �ж��ǲ��Ǹ���
    bool decimal_flag = 0;
    float data_return = 0; // �����õ�������
    for(uint8_t i=0;i<RXnum;i++) // ���ҵȺź͸�̾�ŵ�λ��
    {
        if(data_buffer[i] == '.')   {decimal_flag = 1;decimal_num = i;}
        if(data_buffer[i] == '=')   data_Start_Num = i + 1; // +1��ֱ�Ӷ�λ��������ʼλ
        if(data_buffer[i] == '!' && i)
        {
            data_End_Num = i - 1;
            break;
        }
    }
    if(data_Start_Num == 1)                              //data_Start_NumΪ1˵������Ҫ���ָ�ֵ
        return 0;
    if(data_buffer[data_Start_Num] == '-')              // ����Ǹ���
    {
        data_Start_Num += 1;        // ����һλ������λ
        minus_Flag = 1;             // ����flag
    }
    if(decimal_flag)                                    //����ΪС��ʱ
    {
        data_Num = decimal_num - data_Start_Num;
        for(uint8_t j=0;j<data_Num;j++)
        {
            data_return += (data_buffer[decimal_num-1-j]-48)*pow(10,j);
        }
        data_Num = data_End_Num - decimal_num;
        for(uint8_t j=0;j<data_Num;j++)
        {
            data_return += (data_buffer[decimal_num+1+j]-48)*pow(10,-(j+1));
        }
    }
    else                                                //����Ϊ����ʱ
    {
        data_Num = data_End_Num - data_Start_Num + 1;
        for(uint8_t j=0;j<data_Num;j++)
        {
            data_return += (data_buffer[data_End_Num-j]-48)*pow(10,j);
        }
    }


    if(minus_Flag)  data_return = -data_return;
    return data_return;

}

/**********************************************************************************************************************
 * @brief       �����������ַ�������ֵ
**********************************************************************************************************************/
void WIRELESS_Param_Adjust(uint8  RXnum)
{
    float data_Get = Get_intData(RXnum); // ��Ž��յ�������
    if(data_buffer[1]=='S' && data_buffer[2]=='k' && data_buffer[3]=='p')           //�ƽ�����PID��kp
    {
        camera_servo_PID.kp = data_Get;
    }
    else if(data_buffer[1]=='S' && data_buffer[2]=='k' && data_buffer[3]=='i')      //�ƽ�����PID��ki
    {
        camera_servo_PID.ki = data_Get;
    }
    else if(data_buffer[1]=='S' && data_buffer[2]=='k' && data_buffer[3]=='d')      //�ƽ�����PID��kd
    {
        camera_servo_PID.kd = data_Get;
    }
    else if(data_buffer[1]=='C' && data_buffer[2]=='k' && data_buffer[3]=='p')           //������PID��kp
    {
        crosswise_pid.kp = data_Get;
    }
    else if(data_buffer[1]=='C' && data_buffer[2]=='k' && data_buffer[3]=='i')      //������PID��ki
    {
        crosswise_pid.ki = data_Get;
    }
    else if(data_buffer[1]=='C' && data_buffer[2]=='k' && data_buffer[3]=='d')      //������PID��kd
    {
        crosswise_pid.kd = data_Get;
    }
    else if(data_buffer[1]=='B' && data_buffer[2]=='R' && data_buffer[3]=='U')      //��ˢ���PWM
    {
        BRUSHLESS_PWM = (int)data_Get;
    }
    else if(data_buffer[1]=='M' && data_buffer[2]=='O' && data_buffer[3]=='T')      //�ƽ����PWM
    {
        L_MOTER_PWM_CENTER = (int)data_Get;
        R_MOTER_PWM_CENTER = L_MOTER_PWM_CENTER;
    }
    else if(data_buffer[1]=='F' && data_buffer[2]=='A' && data_buffer[3]=='N')      //������PWM
    {
        L_FAN_PWM_CENTER = (int)data_Get;
        R_FAN_PWM_CENTER = L_FAN_PWM_CENTER;
    }
    else if(data_buffer[1]=='L' && data_buffer[2]=='M' && data_buffer[3]=='O')      //�ƽ������PWM
    {
        L_MOTER_PWM_CENTER = (int)data_Get;
    }
    else if(data_buffer[1]=='R' && data_buffer[2]=='M' && data_buffer[3]=='O')      //�ƽ������PWM
    {
        R_MOTER_PWM_CENTER = (int)data_Get;
    }
    else if(data_buffer[1]=='L' && data_buffer[2]=='F' && data_buffer[3]=='A')      //��������PWM
    {
        L_FAN_PWM_CENTER = (int)data_Get;
    }
    else if(data_buffer[1]=='R' && data_buffer[2]=='F' && data_buffer[3]=='A')      //��������PWM
    {
        R_FAN_PWM_CENTER = (int)data_Get;
    }
    else if(data_buffer[1]=='F' && data_buffer[2]=='O' && data_buffer[3]=='N')      //ǰհ����
    {
        dynamic_foresight = (int)data_Get;
    }
    else if(data_buffer[1]=='S' && data_buffer[2]=='P' && data_buffer[3]=='E')      //Ŀ���ٶ�
    {
        Motor_Encode.target_encoder = (int)data_Get;
    }
    else if(data_buffer[1]=='E' && data_buffer[2]=='N' && data_buffer[3]=='P')      //�ٶȻ�P
    {
        Motor_Encode.pid.kp = data_Get;
    }
    else if(data_buffer[1]=='E' && data_buffer[2]=='N' && data_buffer[3]=='I')      //�ٶȻ�i
    {
        Motor_Encode.pid.ki = data_Get;
    }
    else if(data_buffer[1]=='E' && data_buffer[2]=='N' && data_buffer[3]=='D')      //�ٶȻ�d
    {
        Motor_Encode.pid.kd = data_Get;
    }
    else if(data_buffer[1]=='S' && data_buffer[2]=='T' && data_buffer[3]=='O' && data_buffer[4]=='P')     //ֹͣ����
    {
        Stop_Flag = !Stop_Flag;
    }
    else if(data_buffer[1]=='B' && data_buffer[2]=='u' && data_buffer[3]=='z')
    {
        gpio_toggle_level(D9);
    }
}

/**********************************************************************************************************************
 * @brief       ���ߵ��εĴ����жϣ�ÿ���յ�һ���ַ�ʱ�ͻ����һ�Σ�������ʱҪ�ԡ�!data!���ĸ�ʽ���Ͳ��ܱ�����
 * @param       dat        ���յ����ַ�
 * @return      ��
**********************************************************************************************************************/
void wireless_uart_handle(uint8* dat)
{
    if(*dat=='!')                  //���տ�ʼ��־λ'!'
    {
        RX_FLag = 1;                //��ʼ��������
    }
    if(RX_FLag)
    {
        RXnum++;
        data_buffer[RXnum-1]=*dat;  //��ÿ�ν��յ������ݱ��浽��������
        if(*dat=='!' && RXnum > 1)              //��������Ϊ���ս�����־λ'!'���Ҳ��ǵ�һ������
        {
            wireless_uart_send_buff(data_buffer, RXnum);            // ���յ�����Ϣ���ͻ�ȥ
            wireless_uart_send_string("\r\n");
            WIRELESS_Param_Adjust(RXnum);                           //���ݽ����Ͳ�����ֵ����
            memset(data_buffer, 0, 32);                             //��ջ�������
            RXnum = 0;                                              //��ս��ճ���
            RX_FLag = 0;                                            //ֹͣ��������
        }
    }

    *dat = 0;

}

