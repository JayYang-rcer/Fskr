/*
 * my_uart7.h
 *
 *  Created on: 2024年3月7日
 *      Author: 86173
 */

#ifndef MY_WIRELESS_H_
#define MY_WIRELESS_H_

#include "zf_common_headfile.h"


float Get_intData(uint8 RXnum);                      //获取传输的具体数字
void WIRELESS_Param_Adjust(uint8 RXnum);           //解析发来的字符串并赋值
void wireless_uart_handle(uint8 * dat);     //无线调参的串口中断

#endif /* MY_WIRELESS_H_ */
