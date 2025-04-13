/*
 * my_uart7.c
 *
 *  Created on: 2024年3月7日
 *      Author: 86173
 */
#include "my_uart7.h"

extern pid_param_t camera_servo_PID;
uint8 data_buffer[32];      //串口数据缓存
uint8 RXnum = 0;            //指令长度
bool RX_FLag = 0;           //开始接收标志位
extern bool Stop_Flag;
//-------------------------------------------------------------------------------------------------------------------



/**********************************************************************************************************************
 * @brief       获得数字
**********************************************************************************************************************/
float Get_intData(uint8  RXnum)
{
    uint8_t data_Start_Num = 0; // 记录数据位开始的地方
    uint8_t data_End_Num = 0; // 记录数据位结束的地方
    uint8_t decimal_num = 0;
    uint8_t data_Num = 0; // 记录数据位数
    uint8_t minus_Flag = 0; // 判断是不是负数
    bool decimal_flag = 0;
    float data_return = 0; // 解析得到的数据
    for(uint8_t i=0;i<RXnum;i++) // 查找等号和感叹号的位置
    {
        if(data_buffer[i] == '.')   {decimal_flag = 1;decimal_num = i;}
        if(data_buffer[i] == '=')   data_Start_Num = i + 1; // +1是直接定位到数据起始位
        if(data_buffer[i] == '!' && i)
        {
            data_End_Num = i - 1;
            break;
        }
    }
    if(data_Start_Num == 1)                              //data_Start_Num为1说明不需要数字赋值
        return 0;
    if(data_buffer[data_Start_Num] == '-')              // 如果是负数
    {
        data_Start_Num += 1;        // 后移一位到数据位
        minus_Flag = 1;             // 负数flag
    }
    if(decimal_flag)                                    //数据为小数时
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
    else                                                //数据为整数时
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
 * @brief       解析发来的字符串并赋值
**********************************************************************************************************************/
void WIRELESS_Param_Adjust(uint8  RXnum)
{
    float data_Get = Get_intData(RXnum); // 存放接收到的数据
    if(data_buffer[1]=='S' && data_buffer[2]=='k' && data_buffer[3]=='p')           //推进方向PID的kp
    {
        camera_servo_PID.kp = data_Get;
    }
    else if(data_buffer[1]=='S' && data_buffer[2]=='k' && data_buffer[3]=='i')      //推进方向PID的ki
    {
        camera_servo_PID.ki = data_Get;
    }
    else if(data_buffer[1]=='S' && data_buffer[2]=='k' && data_buffer[3]=='d')      //推进方向PID的kd
    {
        camera_servo_PID.kd = data_Get;
    }
    else if(data_buffer[1]=='C' && data_buffer[2]=='k' && data_buffer[3]=='p')           //横向电机PID的kp
    {
        crosswise_pid.kp = data_Get;
    }
    else if(data_buffer[1]=='C' && data_buffer[2]=='k' && data_buffer[3]=='i')      //横向电机PID的ki
    {
        crosswise_pid.ki = data_Get;
    }
    else if(data_buffer[1]=='C' && data_buffer[2]=='k' && data_buffer[3]=='d')      //横向电机PID的kd
    {
        crosswise_pid.kd = data_Get;
    }
    else if(data_buffer[1]=='B' && data_buffer[2]=='R' && data_buffer[3]=='U')      //无刷电机PWM
    {
        BRUSHLESS_PWM = (int)data_Get;
    }
    else if(data_buffer[1]=='M' && data_buffer[2]=='O' && data_buffer[3]=='T')      //推进电机PWM
    {
        L_MOTER_PWM_CENTER = (int)data_Get;
        R_MOTER_PWM_CENTER = L_MOTER_PWM_CENTER;
    }
    else if(data_buffer[1]=='F' && data_buffer[2]=='A' && data_buffer[3]=='N')      //横向电机PWM
    {
        L_FAN_PWM_CENTER = (int)data_Get;
        R_FAN_PWM_CENTER = L_FAN_PWM_CENTER;
    }
    else if(data_buffer[1]=='L' && data_buffer[2]=='M' && data_buffer[3]=='O')      //推进电机左PWM
    {
        L_MOTER_PWM_CENTER = (int)data_Get;
    }
    else if(data_buffer[1]=='R' && data_buffer[2]=='M' && data_buffer[3]=='O')      //推进电机右PWM
    {
        R_MOTER_PWM_CENTER = (int)data_Get;
    }
    else if(data_buffer[1]=='L' && data_buffer[2]=='F' && data_buffer[3]=='A')      //横向电机左PWM
    {
        L_FAN_PWM_CENTER = (int)data_Get;
    }
    else if(data_buffer[1]=='R' && data_buffer[2]=='F' && data_buffer[3]=='A')      //横向电机右PWM
    {
        R_FAN_PWM_CENTER = (int)data_Get;
    }
    else if(data_buffer[1]=='F' && data_buffer[2]=='O' && data_buffer[3]=='N')      //前瞻参数
    {
        dynamic_foresight = (int)data_Get;
    }
    else if(data_buffer[1]=='S' && data_buffer[2]=='P' && data_buffer[3]=='E')      //目标速度
    {
        Motor_Encode.target_encoder = (int)data_Get;
    }
    else if(data_buffer[1]=='E' && data_buffer[2]=='N' && data_buffer[3]=='P')      //速度环P
    {
        Motor_Encode.pid.kp = data_Get;
    }
    else if(data_buffer[1]=='E' && data_buffer[2]=='N' && data_buffer[3]=='I')      //速度环i
    {
        Motor_Encode.pid.ki = data_Get;
    }
    else if(data_buffer[1]=='E' && data_buffer[2]=='N' && data_buffer[3]=='D')      //速度环d
    {
        Motor_Encode.pid.kd = data_Get;
    }
    else if(data_buffer[1]=='S' && data_buffer[2]=='T' && data_buffer[3]=='O' && data_buffer[4]=='P')     //停止运行
    {
        Stop_Flag = !Stop_Flag;
    }
    else if(data_buffer[1]=='B' && data_buffer[2]=='u' && data_buffer[3]=='z')
    {
        gpio_toggle_level(D9);
    }
}

/**********************************************************************************************************************
 * @brief       无线调参的串口中断，每接收到一个字符时就会进入一次，发数据时要以“!data!”的格式发送才能被解析
 * @param       dat        接收到的字符
 * @return      无
**********************************************************************************************************************/
void wireless_uart_handle(uint8* dat)
{
    if(*dat=='!')                  //接收开始标志位'!'
    {
        RX_FLag = 1;                //开始接收数据
    }
    if(RX_FLag)
    {
        RXnum++;
        data_buffer[RXnum-1]=*dat;  //把每次接收到的数据保存到缓存数组
        if(*dat=='!' && RXnum > 1)              //进入条件为接收结束标志位'!'并且不是第一个数据
        {
            wireless_uart_send_buff(data_buffer, RXnum);            // 将收到的消息发送回去
            wireless_uart_send_string("\r\n");
            WIRELESS_Param_Adjust(RXnum);                           //数据解析和参数赋值函数
            memset(data_buffer, 0, 32);                             //清空缓存数组
            RXnum = 0;                                              //清空接收长度
            RX_FLag = 0;                                            //停止接收数据
        }
    }

    *dat = 0;

}

