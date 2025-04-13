/*
 * cross.h
 *
 *  Created on: 2024��4��15��
 *      Author: 86173
 */

#ifndef CROSS_H_
#define CROSS_H_

#include "zf_common_headfile.h"


enum cross_type_e {
    CROSS_NONE = 0,       // ��ʮ��ģʽ
    CROSS_ENTERING,          // ����ʮ����
    CROSS_IN,               //��ʮ������
    CROSS_OUTING,           //��ʮ����
};



void cross_check(msg_t* msg,enum trace_t* posision);
void cross_handle(imag_t* imag,msg_t* msg,enum trace_t* posision);


#endif /* CROSS_H_ */
