/*
 * my_uart7.h
 *
 *  Created on: 2024��3��7��
 *      Author: 86173
 */

#ifndef MY_WIRELESS_H_
#define MY_WIRELESS_H_

#include "zf_common_headfile.h"


float Get_intData(uint8 RXnum);                      //��ȡ����ľ�������
void WIRELESS_Param_Adjust(uint8 RXnum);           //�����������ַ�������ֵ
void wireless_uart_handle(uint8 * dat);     //���ߵ��εĴ����ж�

#endif /* MY_WIRELESS_H_ */
