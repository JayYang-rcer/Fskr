/*
 * barrier.h
 *
 *  Created on: 2024��5��21��
 *      Author: 86173
 */

#ifndef BARRIER_H_
#define BARRIER_H_

#include "zf_common_headfile.h"

enum barrier_type_e {
    BARRIER_NONE = 0,       // �Ǳ���ģʽ
    BARRIER_LEFT,                // ʶ�����ϰ�
    BARRIER_RIGHT,                // ʶ�����ϰ�
};

void barrier_check(msg_t* msg,enum trace_t* posision);
void barrier_handle(enum trace_t* posision);


#endif /* BARRIER_H_ */
